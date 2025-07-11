
// FUNC: private: bool __thiscall idAASSettings::ParseBool(class Lexer &,bool &)
char __thiscall idAASSettings::ParseBool(idAASSettings *this, Lexer *src, bool *b)
{
  if ( !Lexer::ExpectTokenString(src, "=") )
    return 0;
  *b = Lexer::ParseBool(src);
  return 1;
}

// FUNC: private: bool __thiscall idAASSettings::ParseInt(class Lexer &,int &)
char __thiscall idAASSettings::ParseInt(idAASSettings *this, Lexer *src, int *i)
{
  if ( !Lexer::ExpectTokenString(src, "=") )
    return 0;
  *i = Lexer::ParseInt(src);
  return 1;
}

// FUNC: private: bool __thiscall idAASSettings::ParseFloat(class Lexer &,float &)
char __thiscall idAASSettings::ParseFloat(idAASSettings *this, Lexer *src, float *f)
{
  if ( !Lexer::ExpectTokenString(src, "=") )
    return 0;
  *f = Lexer::ParseFloat(src, 0);
  return 1;
}

// FUNC: public: virtual bool __thiscall idAASFileLocal::IsDummyFile(unsigned int)
bool __thiscall idAASFileLocal::IsDummyFile(idAASFileLocal *this, unsigned int mapFileCRC)
{
  int v2; // eax

  v2 = 0;
  while ( this->isDummy[v2] )
  {
    if ( ++v2 >= 11 )
      return this->crc == mapFileCRC;
  }
  return 0;
}

// FUNC: bool __cdecl Reachability_Special_Write(class idFile *,class idReachability_Special *)
char __cdecl Reachability_Special_Write(idFile *fp, idReachability_Special *reach)
{
  int i; // esi
  idKeyValue *v3; // eax

  fp->WriteFloatString(fp, "\n\t\t{\n");
  for ( i = 0; i < reach->dict.args.num; ++i )
  {
    if ( i < 0 || i >= reach->dict.args.num )
      v3 = 0;
    else
      v3 = &reach->dict.args.list[i];
    fp->WriteFloatString(fp, "\t\t\t\"%s\" \"%s\"\n", v3->key->data, v3->value->data);
  }
  fp->WriteFloatString(fp, "\t\t}\n");
  return 1;
}

// FUNC: bool __cdecl Reachability_Special_Read(class Lexer &,class idReachability_Special *)
char __cdecl Reachability_Special_Read(Lexer *src, idReachability_Special *reach)
{
  idToken key; // [esp+4h] [ebp-ACh] BYREF
  idToken value; // [esp+54h] [ebp-5Ch] BYREF
  int v5; // [esp+ACh] [ebp-4h]

  key.floatvalue = 0.0;
  key.len = 0;
  key.alloced = 20;
  key.data = key.baseBuffer;
  key.baseBuffer[0] = 0;
  value.floatvalue = 0.0;
  v5 = 1;
  value.len = 0;
  value.alloced = 20;
  value.data = value.baseBuffer;
  value.baseBuffer[0] = 0;
  Lexer::ExpectTokenString(src, "{");
  if ( Lexer::ReadToken(src, &key) )
  {
    while ( idStr::Cmp(key.data, "}") )
    {
      Lexer::ExpectTokenType(src, 1, 0, &value);
      idDict::Set(&reach->dict, key.data, value.data);
      if ( !Lexer::ReadToken(src, &key) )
        goto LABEL_4;
    }
    LOBYTE(v5) = 0;
    idStr::FreeData(&value);
    v5 = -1;
    idStr::FreeData(&key);
    return 1;
  }
  else
  {
LABEL_4:
    LOBYTE(v5) = 0;
    idStr::FreeData(&value);
    v5 = -1;
    idStr::FreeData(&key);
    return 0;
  }
}

// FUNC: public: __thiscall idAASSettings::idAASSettings(void)
void __thiscall idAASSettings::idAASSettings(idAASSettings *this)
{
  idBounds *boundingBoxes; // edi
  idBounds *v3; // ebx
  int v4; // ebp
  long double v5; // st4
  long double v6; // st7
  long double v7; // st6
  double x; // st7
  double y; // st6
  float v10; // [esp+1Ch] [ebp-14h]

  boundingBoxes = this->boundingBoxes;
  v3 = this->boundingBoxes;
  v4 = 4;
  do
  {
    `vector constructor iterator'(v3++, 0xCu, 2, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
    --v4;
  }
  while ( v4 );
  this->fileExtension.len = 0;
  this->fileExtension.alloced = 20;
  this->fileExtension.data = this->fileExtension.baseBuffer;
  this->fileExtension.baseBuffer[0] = 0;
  this->numBoundingBoxes = 1;
  boundingBoxes->b[0].x = -16.0;
  boundingBoxes->b[0].y = -16.0;
  boundingBoxes->b[0].z = 0.0;
  boundingBoxes->b[1].z = 72.0;
  boundingBoxes->b[1].x = 16.0;
  boundingBoxes->b[1].y = 16.0;
  this->usePatches = 0;
  this->writeBrushMap = 0;
  this->playerFlood = 0;
  this->noOptimize = 0;
  this->allowSwimReachabilities = 0;
  this->allowFlyReachabilities = 0;
  idStr::operator=(&this->fileExtension, "aas48");
  this->gravity.x = 0.0;
  this->gravity.y = 0.0;
  this->gravity.z = -1066.0;
  this->gravityDir.x = 0.0;
  this->gravityDir.y = this->gravity.y;
  this->gravityDir.z = this->gravity.z;
  v5 = this->gravityDir.x * this->gravityDir.x
     + this->gravityDir.y * this->gravityDir.y
     + this->gravityDir.z * this->gravityDir.z;
  if ( v5 == 0.0 )
  {
    v6 = 0.0;
  }
  else
  {
    v7 = 1.0 / sqrt(v5);
    this->gravityDir.x = v7 * this->gravityDir.x;
    this->gravityDir.y = v7 * this->gravityDir.y;
    this->gravityDir.z = v7 * this->gravityDir.z;
    v6 = v5 * v7;
  }
  this->gravityValue = v6;
  x = this->gravityDir.x;
  y = this->gravityDir.y;
  v10 = -this->gravityDir.z;
  this->invGravityDir.z = v10;
  this->invGravityDir.x = -x;
  this->invGravityDir.y = -y;
  this->tt_barrierJump = 100;
  this->tt_startCrouching = 100;
  this->tt_waterJump = 100;
  this->tt_startWalkOffLedge = 100;
  this->debugColor.x = 1.0;
  this->debugColor.y = 0.0;
  this->debugColor.z = 0.0;
  this->debugColor.w = 1.0;
  this->generateTacticalFeatures = 0;
  this->iAASOnly = 0;
  this->maxStepHeight = 14.0;
  this->maxBarrierHeight = 32.0;
  this->maxWaterJumpHeight = 20.0;
  this->maxFallHeight = 64.0;
  this->minFloorCos = 0.69999999;
  this->debugDraw = 1;
}

// FUNC: private: bool __thiscall idAASSettings::ParseVector(class Lexer &,class idVec3 &)
bool __thiscall idAASSettings::ParseVector(idAASSettings *this, Lexer *src, idVec3 *vec)
{
  return Lexer::ExpectTokenString(src, "=") && Lexer::Parse1DMatrix(src, 3, &vec->x) != 0;
}

// FUNC: private: bool __thiscall idAASSettings::ParseBBoxes(class Lexer &)
char __thiscall idAASSettings::ParseBBoxes(idAASSettings *this, Lexer *src)
{
  idBounds *v3; // eax
  idBounds bounds; // [esp+8h] [ebp-74h] BYREF
  idToken token; // [esp+20h] [ebp-5Ch] BYREF
  int v7; // [esp+78h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v7 = 0;
  this->numBoundingBoxes = 0;
  if ( Lexer::ExpectTokenString(src, "{") && Lexer::ReadToken(src, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      Lexer::UnreadToken(src, &token);
      Lexer::Parse1DMatrix(src, 3, (float *)&bounds);
      if ( Lexer::ExpectTokenString(src, "-") )
      {
        Lexer::Parse1DMatrix(src, 3, &bounds.b[1].x);
        v3 = &this->boundingBoxes[this->numBoundingBoxes++];
        *v3 = bounds;
        if ( Lexer::ReadToken(src, &token) )
          continue;
      }
      goto LABEL_6;
    }
    v7 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_6:
    v7 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall idAASSettings::WriteToFile(class idFile *)const
char __thiscall idAASSettings::WriteToFile(idAASSettings *this, idFile *fp)
{
  float *p_y; // edi
  int i; // [esp+3Ch] [ebp-4h]

  fp->WriteFloatString(fp, "{\n");
  fp->WriteFloatString(fp, "\tbboxes\n\t{\n");
  i = 0;
  if ( this->numBoundingBoxes > 0 )
  {
    p_y = &this->boundingBoxes[0].b[1].y;
    do
    {
      fp->WriteFloatString(
        fp,
        "\t\t(%f %f %f)-(%f %f %f)\n",
        *(p_y - 4),
        *(p_y - 3),
        *(p_y - 2),
        *(p_y - 1),
        *p_y,
        p_y[1]);
      p_y += 6;
      ++i;
    }
    while ( i < this->numBoundingBoxes );
  }
  fp->WriteFloatString(fp, "\t}\n");
  fp->WriteFloatString(fp, "\tusePatches = %d\n", this->usePatches);
  fp->WriteFloatString(fp, "\twriteBrushMap = %d\n", this->writeBrushMap);
  fp->WriteFloatString(fp, "\tplayerFlood = %d\n", this->playerFlood);
  fp->WriteFloatString(fp, "\tallowSwimReachabilities = %d\n", this->allowSwimReachabilities);
  fp->WriteFloatString(fp, "\tallowFlyReachabilities = %d\n", this->allowFlyReachabilities);
  fp->WriteFloatString(fp, "\tgenerateTacticalFeatures = %d\n", this->generateTacticalFeatures);
  fp->WriteFloatString(fp, "\tfileExtension = \"%s\"\n", this->fileExtension.data);
  fp->WriteFloatString(fp, "\tgravity = (%f %f %f)\n", this->gravity.x, this->gravity.y, this->gravity.z);
  fp->WriteFloatString(fp, "\tmaxStepHeight = %f\n", this->maxStepHeight);
  fp->WriteFloatString(fp, "\tmaxBarrierHeight = %f\n", this->maxBarrierHeight);
  fp->WriteFloatString(fp, "\tmaxWaterJumpHeight = %f\n", this->maxWaterJumpHeight);
  fp->WriteFloatString(fp, "\tmaxFallHeight = %f\n", this->maxFallHeight);
  fp->WriteFloatString(fp, "\tminFloorCos = %f\n", this->minFloorCos);
  fp->WriteFloatString(fp, "\ttt_barrierJump = %d\n", this->tt_barrierJump);
  fp->WriteFloatString(fp, "\ttt_startCrouching = %d\n", this->tt_startCrouching);
  fp->WriteFloatString(fp, "\ttt_waterJump = %d\n", this->tt_waterJump);
  fp->WriteFloatString(fp, "\ttt_startWalkOffLedge = %d\n", this->tt_startWalkOffLedge);
  fp->WriteFloatString(fp, "}\n");
  return 1;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::Clear(void)
void __thiscall idAASFileLocal::Clear(idAASFileLocal *this)
{
  if ( this->planeList.list )
    Memory::Free(this->planeList.list);
  this->planeList.list = 0;
  this->planeList.num = 0;
  this->planeList.size = 0;
  idHashIndex::Free(&this->planeList.hash);
  if ( this->vertices.list )
    Memory::Free(this->vertices.list);
  this->vertices.list = 0;
  this->vertices.num = 0;
  this->vertices.size = 0;
  if ( this->edges.list )
    Memory::Free(this->edges.list);
  this->edges.list = 0;
  this->edges.num = 0;
  this->edges.size = 0;
  if ( this->edgeIndex.list )
    Memory::Free(this->edgeIndex.list);
  this->edgeIndex.list = 0;
  this->edgeIndex.num = 0;
  this->edgeIndex.size = 0;
  if ( this->faces.list )
    Memory::Free(this->faces.list);
  this->faces.list = 0;
  this->faces.num = 0;
  this->faces.size = 0;
  if ( this->faceIndex.list )
    Memory::Free(this->faceIndex.list);
  this->faceIndex.list = 0;
  this->faceIndex.num = 0;
  this->faceIndex.size = 0;
  if ( this->areas.list )
    Memory::Free(this->areas.list);
  this->areas.list = 0;
  this->areas.num = 0;
  this->areas.size = 0;
  if ( this->nodes.list )
    Memory::Free(this->nodes.list);
  this->nodes.list = 0;
  this->nodes.num = 0;
  this->nodes.size = 0;
  if ( this->portals.list )
    Memory::Free(this->portals.list);
  this->portals.list = 0;
  this->portals.num = 0;
  this->portals.size = 0;
  if ( this->portalIndex.list )
    Memory::Free(this->portalIndex.list);
  this->portalIndex.list = 0;
  this->portalIndex.num = 0;
  this->portalIndex.size = 0;
  if ( this->clusters.list )
    Memory::Free(this->clusters.list);
  this->clusters.list = 0;
  this->clusters.num = 0;
  this->clusters.size = 0;
  if ( this->featureIndex.list )
    Memory::Free(this->featureIndex.list);
  this->featureIndex.list = 0;
  this->featureIndex.num = 0;
  this->featureIndex.size = 0;
  if ( this->features.list )
    Memory::Free(this->features.list);
  this->features.list = 0;
  this->features.num = 0;
  this->features.size = 0;
  SIMDProcessor->Memset(SIMDProcessor, this->isDummy, 0, 11);
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseIndex(class Lexer &,class idList<int> &,int)
char __thiscall idAASFileLocal::ParseIndex(idAASFileLocal *this, Lexer *src, int indexes, int idx)
{
  int v5; // eax
  int v7; // ebx
  bool v8; // cc
  int *v9; // edi
  int i; // eax
  int v11; // eax
  int j; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // ecx
  int *v16; // edi
  int k; // eax
  int numIndexes; // [esp+10h] [ebp-8h]
  Lexer *srca; // [esp+1Ch] [ebp+4h]
  int index; // [esp+20h] [ebp+8h]

  v5 = Lexer::ParseInt(src);
  v7 = v5;
  numIndexes = v5;
  if ( v5 > 0 )
  {
    if ( v5 != *(_DWORD *)(indexes + 4) )
    {
      v8 = v5 < *(_DWORD *)indexes;
      v9 = *(int **)(indexes + 12);
      *(_DWORD *)(indexes + 4) = v5;
      if ( v8 )
        *(_DWORD *)indexes = v5;
      *(_DWORD *)(indexes + 12) = Memory::Allocate(4 * v5);
      for ( i = 0; i < *(_DWORD *)indexes; ++i )
        *(_DWORD *)(*(_DWORD *)(indexes + 12) + 4 * i) = v9[i];
      if ( v9 )
        Memory::Free(v9);
    }
  }
  else
  {
    if ( *(_DWORD *)(indexes + 12) )
      Memory::Free(*(void **)(indexes + 12));
    *(_DWORD *)(indexes + 12) = 0;
    *(_DWORD *)indexes = 0;
    *(_DWORD *)(indexes + 4) = 0;
  }
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  if ( v7 > 0 )
  {
    index = v7;
    do
    {
      Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, "(");
      srca = (Lexer *)Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, ")");
      if ( !*(_DWORD *)(indexes + 12) )
      {
        v11 = *(_DWORD *)(indexes + 8);
        if ( v11 > 0 )
        {
          if ( v11 != *(_DWORD *)(indexes + 4) )
          {
            v8 = v11 < *(_DWORD *)indexes;
            *(_DWORD *)(indexes + 4) = v11;
            if ( v8 )
              *(_DWORD *)indexes = v11;
            *(_DWORD *)(indexes + 12) = Memory::Allocate(4 * v11);
            for ( j = 0; j < *(_DWORD *)indexes; ++j )
              *(_DWORD *)(*(_DWORD *)(indexes + 12) + 4 * j) = *(_DWORD *)(4 * j);
          }
        }
        else
        {
          *(_DWORD *)(indexes + 12) = 0;
          *(_DWORD *)indexes = 0;
          *(_DWORD *)(indexes + 4) = 0;
        }
      }
      v13 = *(_DWORD *)indexes;
      v14 = *(_DWORD *)(indexes + 4);
      if ( *(_DWORD *)indexes == v14 )
      {
        if ( !*(_DWORD *)(indexes + 8) )
          *(_DWORD *)(indexes + 8) = 16;
        v15 = *(_DWORD *)(indexes + 8) + v14 - (*(_DWORD *)(indexes + 8) + v14) % *(_DWORD *)(indexes + 8);
        if ( v15 > 0 )
        {
          if ( v15 != *(_DWORD *)(indexes + 4) )
          {
            v16 = *(int **)(indexes + 12);
            *(_DWORD *)(indexes + 4) = v15;
            if ( v15 < v13 )
              *(_DWORD *)indexes = v15;
            *(_DWORD *)(indexes + 12) = Memory::Allocate(4 * v15);
            for ( k = 0; k < *(_DWORD *)indexes; ++k )
              *(_DWORD *)(*(_DWORD *)(indexes + 12) + 4 * k) = v16[k];
            if ( v16 )
              Memory::Free(v16);
          }
        }
        else
        {
          if ( *(_DWORD *)(indexes + 12) )
            Memory::Free(*(void **)(indexes + 12));
          *(_DWORD *)(indexes + 12) = 0;
          *(_DWORD *)indexes = 0;
          *(_DWORD *)(indexes + 4) = 0;
        }
      }
      *(_DWORD *)(*(_DWORD *)(indexes + 12) + 4 * (*(_DWORD *)indexes)++) = srca;
      --index;
    }
    while ( index );
    v7 = numIndexes;
  }
  if ( !Lexer::ExpectTokenString(src, "}") )
    return 0;
  if ( !v7 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseEdges(class Lexer &,int)
char __thiscall idAASFileLocal::ParseEdges(idAASFileLocal *this, Lexer *src, int idx)
{
  int v5; // eax
  int v6; // ebp
  bool v7; // cc
  aasEdge_s *list; // edi
  int i; // eax
  aasEdge_s *v10; // ecx
  int granularity; // eax
  int j; // eax
  aasEdge_s *v13; // ecx
  int num; // ebp
  int size; // eax
  int v16; // ecx
  aasEdge_s *v17; // edi
  int k; // eax
  aasEdge_s *v19; // ecx
  int v20; // eax
  aasEdge_s *v21; // ecx
  int numEdges; // [esp+10h] [ebp-Ch]
  int edge; // [esp+14h] [ebp-8h]
  int edge_4; // [esp+18h] [ebp-4h]
  Lexer *srca; // [esp+20h] [ebp+4h]

  v5 = Lexer::ParseInt(src);
  v6 = v5;
  numEdges = v5;
  if ( v5 > 0 )
  {
    if ( v5 != this->edges.size )
    {
      v7 = v5 < this->edges.num;
      list = this->edges.list;
      this->edges.size = v5;
      if ( v7 )
        this->edges.num = v5;
      this->edges.list = (aasEdge_s *)Memory::Allocate(8 * v5);
      for ( i = 0; i < this->edges.num; ++i )
      {
        v10 = this->edges.list;
        v10[i].vertexNum[0] = list[i].vertexNum[0];
        v10[i].vertexNum[1] = list[i].vertexNum[1];
      }
      if ( list )
        Memory::Free(list);
    }
  }
  else
  {
    if ( this->edges.list )
      Memory::Free(this->edges.list);
    this->edges.list = 0;
    this->edges.num = 0;
    this->edges.size = 0;
  }
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  if ( v6 > 0 )
  {
    srca = (Lexer *)v6;
    do
    {
      Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, "(");
      edge = Lexer::ParseInt(src);
      edge_4 = Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, ")");
      if ( !this->edges.list )
      {
        granularity = this->edges.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->edges.size )
          {
            v7 = granularity < this->edges.num;
            this->edges.size = granularity;
            if ( v7 )
              this->edges.num = granularity;
            this->edges.list = (aasEdge_s *)Memory::Allocate(8 * granularity);
            for ( j = 0; j < this->edges.num; ++j )
            {
              v13 = this->edges.list;
              v13[j].vertexNum[0] = *(_DWORD *)(8 * j);
              v13[j].vertexNum[1] = *(_DWORD *)(8 * j + 4);
            }
          }
        }
        else
        {
          this->edges.list = 0;
          this->edges.num = 0;
          this->edges.size = 0;
        }
      }
      num = this->edges.num;
      size = this->edges.size;
      if ( num == size )
      {
        if ( !this->edges.granularity )
          this->edges.granularity = 16;
        v16 = size + this->edges.granularity - (size + this->edges.granularity) % this->edges.granularity;
        if ( v16 > 0 )
        {
          if ( v16 != this->edges.size )
          {
            v17 = this->edges.list;
            this->edges.size = v16;
            if ( v16 < num )
              this->edges.num = v16;
            this->edges.list = (aasEdge_s *)Memory::Allocate(8 * v16);
            for ( k = 0; k < this->edges.num; ++k )
            {
              v19 = this->edges.list;
              v19[k].vertexNum[0] = v17[k].vertexNum[0];
              v19[k].vertexNum[1] = v17[k].vertexNum[1];
            }
            if ( v17 )
              Memory::Free(v17);
          }
        }
        else
        {
          if ( this->edges.list )
            Memory::Free(this->edges.list);
          this->edges.list = 0;
          this->edges.num = 0;
          this->edges.size = 0;
        }
      }
      v20 = this->edges.num;
      v21 = this->edges.list;
      v21[v20].vertexNum[0] = edge;
      v21[v20].vertexNum[1] = edge_4;
      ++this->edges.num;
      srca = (Lexer *)((char *)srca - 1);
    }
    while ( srca );
    v6 = numEdges;
  }
  if ( !Lexer::ExpectTokenString(src, "}") )
    return 0;
  if ( !v6 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseFaces(class Lexer &,int)
char __thiscall idAASFileLocal::ParseFaces(idAASFileLocal *this, Lexer *src, int idx)
{
  int v5; // eax
  int v6; // ebx
  bool v7; // cc
  aasFace_s *list; // edi
  aasFace_s *v9; // eax
  int v10; // ecx
  int v11; // eax
  aasFace_s *v12; // edx
  aasFace_s *v13; // edi
  int granularity; // eax
  aasFace_s *v15; // eax
  int v16; // ecx
  _DWORD *v17; // eax
  aasFace_s *v18; // edx
  int num; // ebx
  int size; // ecx
  int v21; // eax
  aasFace_s *v22; // edi
  aasFace_s *v23; // eax
  int v24; // ecx
  int v25; // eax
  aasFace_s *v26; // edx
  aasFace_s *v27; // edi
  aasFace_s *v28; // eax
  int v30; // [esp+10h] [ebp-18h]
  int numFaces; // [esp+14h] [ebp-14h]
  int face; // [esp+18h] [ebp-10h]
  int face_4; // [esp+1Ch] [ebp-Ch]
  int face_8; // [esp+20h] [ebp-8h]
  int face_12; // [esp+24h] [ebp-4h]
  Lexer *srca; // [esp+2Ch] [ebp+4h]
  Lexer *srcb; // [esp+2Ch] [ebp+4h]

  v5 = Lexer::ParseInt(src);
  v6 = v5;
  numFaces = v5;
  if ( v5 > 0 )
  {
    if ( v5 != this->faces.size )
    {
      v7 = v5 < this->faces.num;
      list = this->faces.list;
      srca = (Lexer *)list;
      this->faces.size = v5;
      if ( v7 )
        this->faces.num = v5;
      v9 = (aasFace_s *)Memory::Allocate(16 * v5);
      v10 = 0;
      v7 = this->faces.num <= 0;
      this->faces.list = v9;
      if ( !v7 )
      {
        v11 = 0;
        do
        {
          v12 = &list[v11];
          v13 = &this->faces.list[v11];
          *(_DWORD *)&v13->planeNum = *(_DWORD *)&v12->planeNum;
          v13->numEdges = v12->numEdges;
          v13->firstEdge = v12->firstEdge;
          *(_DWORD *)v13->areas = *(_DWORD *)v12->areas;
          list = (aasFace_s *)srca;
          ++v10;
          ++v11;
        }
        while ( v10 < this->faces.num );
        v6 = numFaces;
      }
      if ( list )
        Memory::Free(list);
    }
  }
  else
  {
    if ( this->faces.list )
      Memory::Free(this->faces.list);
    this->faces.list = 0;
    this->faces.num = 0;
    this->faces.size = 0;
  }
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  if ( v6 > 0 )
  {
    v30 = v6;
    do
    {
      Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, "(");
      LOWORD(face) = Lexer::ParseInt(src);
      HIWORD(face) = Lexer::ParseInt(src);
      LOWORD(face_12) = Lexer::ParseInt(src);
      HIWORD(face_12) = Lexer::ParseInt(src);
      face_8 = Lexer::ParseInt(src);
      face_4 = Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, ")");
      if ( !this->faces.list )
      {
        granularity = this->faces.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->faces.size )
          {
            v7 = granularity < this->faces.num;
            this->faces.size = granularity;
            if ( v7 )
              this->faces.num = granularity;
            v15 = (aasFace_s *)Memory::Allocate(16 * granularity);
            v16 = 0;
            v7 = this->faces.num <= 0;
            this->faces.list = v15;
            if ( !v7 )
            {
              v17 = 0;
              do
              {
                v18 = (aasFace_s *)((char *)v17 + (unsigned int)this->faces.list);
                *(_DWORD *)&v18->planeNum = *v17;
                v18->numEdges = v17[1];
                v18->firstEdge = v17[2];
                ++v16;
                *(_DWORD *)v18->areas = v17[3];
                v17 += 4;
              }
              while ( v16 < this->faces.num );
            }
          }
        }
        else
        {
          this->faces.list = 0;
          this->faces.num = 0;
          this->faces.size = 0;
        }
      }
      num = this->faces.num;
      size = this->faces.size;
      if ( num == size )
      {
        if ( !this->faces.granularity )
          this->faces.granularity = 16;
        v21 = this->faces.granularity + size - (this->faces.granularity + size) % this->faces.granularity;
        if ( v21 > 0 )
        {
          if ( v21 != this->faces.size )
          {
            v22 = this->faces.list;
            srcb = (Lexer *)v22;
            this->faces.size = v21;
            if ( v21 < num )
              this->faces.num = v21;
            v23 = (aasFace_s *)Memory::Allocate(16 * v21);
            v24 = 0;
            v7 = this->faces.num <= 0;
            this->faces.list = v23;
            if ( !v7 )
            {
              v25 = 0;
              do
              {
                v26 = &v22[v25];
                v27 = &this->faces.list[v25];
                *(_DWORD *)&v27->planeNum = *(_DWORD *)&v26->planeNum;
                v27->numEdges = v26->numEdges;
                v27->firstEdge = v26->firstEdge;
                *(_DWORD *)v27->areas = *(_DWORD *)v26->areas;
                v22 = (aasFace_s *)srcb;
                ++v24;
                ++v25;
              }
              while ( v24 < this->faces.num );
            }
            if ( v22 )
              Memory::Free(v22);
          }
        }
        else
        {
          if ( this->faces.list )
            Memory::Free(this->faces.list);
          this->faces.list = 0;
          this->faces.num = 0;
          this->faces.size = 0;
        }
      }
      v28 = &this->faces.list[this->faces.num];
      *(_DWORD *)&v28->planeNum = face;
      v28->numEdges = face_4;
      v28->firstEdge = face_8;
      *(_DWORD *)v28->areas = face_12;
      ++this->faces.num;
      --v30;
    }
    while ( v30 );
    v6 = numFaces;
  }
  if ( !Lexer::ExpectTokenString(src, "}") )
    return 0;
  if ( !v6 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::LinkReversedReachability(void)
void __thiscall idAASFileLocal::LinkReversedReachability(idAASFileLocal *this)
{
  int v1; // ebx
  int v2; // edi
  idReachability *i; // edx
  int toAreaNum; // eax

  v1 = 0;
  if ( this->areas.num > 0 )
  {
    v2 = 0;
    do
    {
      for ( i = this->areas.list[v2].reach; i; i = i->next )
      {
        toAreaNum = i->toAreaNum;
        i->rev_next = this->areas.list[toAreaNum].rev_reach;
        this->areas.list[toAreaNum].rev_reach = i;
      }
      ++v1;
      ++v2;
    }
    while ( v1 < this->areas.num );
  }
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseNodes(class Lexer &,int)
char __thiscall idAASFileLocal::ParseNodes(idAASFileLocal *this, Lexer *src, int idx)
{
  Lexer *v3; // ebp
  int v5; // eax
  int v6; // ebx
  bool v7; // cc
  aasNode_s *list; // edi
  aasNode_s *v9; // eax
  int v10; // ecx
  int v11; // eax
  aasNode_s *v12; // ebx
  int granularity; // eax
  aasNode_s *v14; // eax
  int v15; // ecx
  _DWORD *v16; // eax
  aasNode_s *v17; // edx
  int num; // ebx
  int size; // ecx
  int v20; // eax
  aasNode_s *v21; // edi
  aasNode_s *v22; // eax
  int v23; // ecx
  int v24; // eax
  aasNode_s *v25; // ebx
  aasNode_s *v26; // edx
  int v28; // [esp+10h] [ebp-14h]
  int numNodes; // [esp+14h] [ebp-10h]
  int node; // [esp+18h] [ebp-Ch]
  int node_4; // [esp+1Ch] [ebp-8h]
  int node_8; // [esp+20h] [ebp-4h]

  v3 = src;
  v5 = Lexer::ParseInt(src);
  v6 = v5;
  numNodes = v5;
  if ( v5 > 0 )
  {
    if ( v5 != this->nodes.size )
    {
      v7 = v5 < this->nodes.num;
      list = this->nodes.list;
      this->nodes.size = v5;
      if ( v7 )
        this->nodes.num = v5;
      v9 = (aasNode_s *)Memory::Allocate(12 * v5);
      v10 = 0;
      v7 = this->nodes.num <= 0;
      this->nodes.list = v9;
      if ( !v7 )
      {
        v11 = 0;
        do
        {
          v12 = &this->nodes.list[v11];
          *(_DWORD *)&v12->planeNum = *(_DWORD *)&list[v11].planeNum;
          v12->children[0] = list[v11].children[0];
          ++v10;
          v12->children[1] = list[v11++].children[1];
        }
        while ( v10 < this->nodes.num );
        v3 = src;
        v6 = numNodes;
      }
      if ( list )
        Memory::Free(list);
    }
  }
  else
  {
    if ( this->nodes.list )
      Memory::Free(this->nodes.list);
    this->nodes.list = 0;
    this->nodes.num = 0;
    this->nodes.size = 0;
  }
  if ( !Lexer::ExpectTokenString(v3, "{") )
    return 0;
  if ( v6 > 0 )
  {
    v28 = v6;
    do
    {
      Lexer::ParseInt(v3);
      Lexer::ExpectTokenString(v3, "(");
      LOWORD(node) = Lexer::ParseInt(v3);
      node_4 = Lexer::ParseInt(v3);
      node_8 = Lexer::ParseInt(v3);
      Lexer::ExpectTokenString(v3, ")");
      if ( !this->nodes.list )
      {
        granularity = this->nodes.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->nodes.size )
          {
            v7 = granularity < this->nodes.num;
            this->nodes.size = granularity;
            if ( v7 )
              this->nodes.num = granularity;
            v14 = (aasNode_s *)Memory::Allocate(12 * granularity);
            v15 = 0;
            v7 = this->nodes.num <= 0;
            this->nodes.list = v14;
            if ( !v7 )
            {
              v16 = 0;
              do
              {
                v17 = (aasNode_s *)((char *)v16 + (unsigned int)this->nodes.list);
                *(_DWORD *)&v17->planeNum = *v16;
                v17->children[0] = v16[1];
                ++v15;
                v17->children[1] = v16[2];
                v16 += 3;
              }
              while ( v15 < this->nodes.num );
            }
          }
        }
        else
        {
          this->nodes.list = 0;
          this->nodes.num = 0;
          this->nodes.size = 0;
        }
      }
      num = this->nodes.num;
      size = this->nodes.size;
      if ( num == size )
      {
        if ( !this->nodes.granularity )
          this->nodes.granularity = 16;
        v20 = this->nodes.granularity + size - (this->nodes.granularity + size) % this->nodes.granularity;
        if ( v20 > 0 )
        {
          if ( v20 != this->nodes.size )
          {
            v21 = this->nodes.list;
            this->nodes.size = v20;
            if ( v20 < num )
              this->nodes.num = v20;
            v22 = (aasNode_s *)Memory::Allocate(12 * v20);
            v23 = 0;
            v7 = this->nodes.num <= 0;
            this->nodes.list = v22;
            if ( !v7 )
            {
              v24 = 0;
              do
              {
                v25 = &this->nodes.list[v24];
                *(_DWORD *)&v25->planeNum = *(_DWORD *)&v21[v24].planeNum;
                v25->children[0] = v21[v24].children[0];
                ++v23;
                v25->children[1] = v21[v24++].children[1];
              }
              while ( v23 < this->nodes.num );
              v3 = src;
            }
            if ( v21 )
              Memory::Free(v21);
          }
        }
        else
        {
          if ( this->nodes.list )
            Memory::Free(this->nodes.list);
          this->nodes.list = 0;
          this->nodes.num = 0;
          this->nodes.size = 0;
        }
      }
      v26 = &this->nodes.list[this->nodes.num];
      *(_DWORD *)&v26->planeNum = node;
      v26->children[0] = node_4;
      v26->children[1] = node_8;
      ++this->nodes.num;
      --v28;
    }
    while ( v28 );
    v6 = numNodes;
  }
  if ( !Lexer::ExpectTokenString(v3, "}") )
    return 0;
  if ( !v6 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParsePortals(class Lexer &,int)
char __thiscall idAASFileLocal::ParsePortals(idAASFileLocal *this, Lexer *src, int idx)
{
  Lexer *v3; // ebp
  int v5; // eax
  int v6; // ebx
  bool v7; // cc
  aasPortal_s *list; // edi
  aasPortal_s *v9; // eax
  int v10; // ecx
  int v11; // eax
  aasPortal_s *v12; // ebx
  int granularity; // eax
  aasPortal_s *v14; // eax
  int v15; // ecx
  _DWORD *v16; // eax
  aasPortal_s *v17; // edx
  int num; // ebx
  int size; // ecx
  int v20; // eax
  aasPortal_s *v21; // edi
  aasPortal_s *v22; // eax
  int v23; // ecx
  int v24; // eax
  aasPortal_s *v25; // ebx
  aasPortal_s *v26; // edx
  int v28; // [esp+10h] [ebp-14h]
  int numPortals; // [esp+14h] [ebp-10h]
  int portal; // [esp+18h] [ebp-Ch]
  int portal_4; // [esp+1Ch] [ebp-8h]
  int portal_8; // [esp+20h] [ebp-4h]

  v3 = src;
  v5 = Lexer::ParseInt(src);
  v6 = v5;
  numPortals = v5;
  if ( v5 > 0 )
  {
    if ( v5 != this->portals.size )
    {
      v7 = v5 < this->portals.num;
      list = this->portals.list;
      this->portals.size = v5;
      if ( v7 )
        this->portals.num = v5;
      v9 = (aasPortal_s *)Memory::Allocate(12 * v5);
      v10 = 0;
      v7 = this->portals.num <= 0;
      this->portals.list = v9;
      if ( !v7 )
      {
        v11 = 0;
        do
        {
          v12 = &this->portals.list[v11];
          *(_DWORD *)&v12->areaNum = *(_DWORD *)&list[v11].areaNum;
          *(_DWORD *)&v12->clusters[1] = *(_DWORD *)&list[v11].clusters[1];
          ++v10;
          *(_DWORD *)&v12->clusterAreaNum[1] = *(_DWORD *)&list[v11++].clusterAreaNum[1];
        }
        while ( v10 < this->portals.num );
        v3 = src;
        v6 = numPortals;
      }
      if ( list )
        Memory::Free(list);
    }
  }
  else
  {
    if ( this->portals.list )
      Memory::Free(this->portals.list);
    this->portals.list = 0;
    this->portals.num = 0;
    this->portals.size = 0;
  }
  if ( !Lexer::ExpectTokenString(v3, "{") )
    return 0;
  if ( v6 > 0 )
  {
    v28 = v6;
    do
    {
      Lexer::ParseInt(v3);
      Lexer::ExpectTokenString(v3, "(");
      LOWORD(portal) = Lexer::ParseInt(v3);
      HIWORD(portal) = Lexer::ParseInt(v3);
      LOWORD(portal_4) = Lexer::ParseInt(v3);
      HIWORD(portal_4) = Lexer::ParseInt(v3);
      LOWORD(portal_8) = Lexer::ParseInt(v3);
      Lexer::ExpectTokenString(v3, ")");
      if ( !this->portals.list )
      {
        granularity = this->portals.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->portals.size )
          {
            v7 = granularity < this->portals.num;
            this->portals.size = granularity;
            if ( v7 )
              this->portals.num = granularity;
            v14 = (aasPortal_s *)Memory::Allocate(12 * granularity);
            v15 = 0;
            v7 = this->portals.num <= 0;
            this->portals.list = v14;
            if ( !v7 )
            {
              v16 = 0;
              do
              {
                v17 = (aasPortal_s *)((char *)v16 + (unsigned int)this->portals.list);
                *(_DWORD *)&v17->areaNum = *v16;
                *(_DWORD *)&v17->clusters[1] = v16[1];
                ++v15;
                *(_DWORD *)&v17->clusterAreaNum[1] = v16[2];
                v16 += 3;
              }
              while ( v15 < this->portals.num );
            }
          }
        }
        else
        {
          this->portals.list = 0;
          this->portals.num = 0;
          this->portals.size = 0;
        }
      }
      num = this->portals.num;
      size = this->portals.size;
      if ( num == size )
      {
        if ( !this->portals.granularity )
          this->portals.granularity = 16;
        v20 = this->portals.granularity + size - (this->portals.granularity + size) % this->portals.granularity;
        if ( v20 > 0 )
        {
          if ( v20 != this->portals.size )
          {
            v21 = this->portals.list;
            this->portals.size = v20;
            if ( v20 < num )
              this->portals.num = v20;
            v22 = (aasPortal_s *)Memory::Allocate(12 * v20);
            v23 = 0;
            v7 = this->portals.num <= 0;
            this->portals.list = v22;
            if ( !v7 )
            {
              v24 = 0;
              do
              {
                v25 = &this->portals.list[v24];
                *(_DWORD *)&v25->areaNum = *(_DWORD *)&v21[v24].areaNum;
                *(_DWORD *)&v25->clusters[1] = *(_DWORD *)&v21[v24].clusters[1];
                ++v23;
                *(_DWORD *)&v25->clusterAreaNum[1] = *(_DWORD *)&v21[v24++].clusterAreaNum[1];
              }
              while ( v23 < this->portals.num );
              v3 = src;
            }
            if ( v21 )
              Memory::Free(v21);
          }
        }
        else
        {
          if ( this->portals.list )
            Memory::Free(this->portals.list);
          this->portals.list = 0;
          this->portals.num = 0;
          this->portals.size = 0;
        }
      }
      v26 = &this->portals.list[this->portals.num];
      *(_DWORD *)&v26->areaNum = portal;
      *(_DWORD *)&v26->clusters[1] = portal_4;
      *(_DWORD *)&v26->clusterAreaNum[1] = portal_8;
      ++this->portals.num;
      --v28;
    }
    while ( v28 );
    v6 = numPortals;
  }
  if ( !Lexer::ExpectTokenString(v3, "}") )
    return 0;
  if ( !v6 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseClusters(class Lexer &,int)
char __thiscall idAASFileLocal::ParseClusters(idAASFileLocal *this, Lexer *src, int idx)
{
  int v5; // eax
  int v6; // ebx
  bool v7; // cc
  aasCluster_s *list; // edi
  aasCluster_s *v9; // eax
  int v10; // ecx
  int v11; // eax
  aasCluster_s *v12; // edx
  aasCluster_s *v13; // edi
  int granularity; // eax
  aasCluster_s *v15; // eax
  int v16; // ecx
  int *v17; // eax
  aasCluster_s *v18; // edx
  int num; // ebx
  int size; // ecx
  int v21; // eax
  aasCluster_s *v22; // edi
  aasCluster_s *v23; // eax
  int v24; // ecx
  int v25; // eax
  aasCluster_s *v26; // edx
  aasCluster_s *v27; // edi
  aasCluster_s *v28; // eax
  int v30; // [esp+10h] [ebp-18h]
  int numClusters; // [esp+14h] [ebp-14h]
  int cluster; // [esp+18h] [ebp-10h]
  int cluster_4; // [esp+1Ch] [ebp-Ch]
  int cluster_8; // [esp+20h] [ebp-8h]
  int cluster_12; // [esp+24h] [ebp-4h]
  Lexer *srca; // [esp+2Ch] [ebp+4h]
  Lexer *srcb; // [esp+2Ch] [ebp+4h]

  v5 = Lexer::ParseInt(src);
  v6 = v5;
  numClusters = v5;
  if ( v5 > 0 )
  {
    if ( v5 != this->clusters.size )
    {
      v7 = v5 < this->clusters.num;
      list = this->clusters.list;
      srca = (Lexer *)list;
      this->clusters.size = v5;
      if ( v7 )
        this->clusters.num = v5;
      v9 = (aasCluster_s *)Memory::Allocate(16 * v5);
      v10 = 0;
      v7 = this->clusters.num <= 0;
      this->clusters.list = v9;
      if ( !v7 )
      {
        v11 = 0;
        do
        {
          v12 = &list[v11];
          v13 = &this->clusters.list[v11];
          v13->numAreas = v12->numAreas;
          v13->numReachableAreas = v12->numReachableAreas;
          v13->numPortals = v12->numPortals;
          v13->firstPortal = v12->firstPortal;
          list = (aasCluster_s *)srca;
          ++v10;
          ++v11;
        }
        while ( v10 < this->clusters.num );
        v6 = numClusters;
      }
      if ( list )
        Memory::Free(list);
    }
  }
  else
  {
    if ( this->clusters.list )
      Memory::Free(this->clusters.list);
    this->clusters.list = 0;
    this->clusters.num = 0;
    this->clusters.size = 0;
  }
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  if ( v6 > 0 )
  {
    v30 = v6;
    do
    {
      Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, "(");
      cluster = Lexer::ParseInt(src);
      cluster_4 = Lexer::ParseInt(src);
      cluster_12 = Lexer::ParseInt(src);
      cluster_8 = Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, ")");
      if ( !this->clusters.list )
      {
        granularity = this->clusters.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->clusters.size )
          {
            v7 = granularity < this->clusters.num;
            this->clusters.size = granularity;
            if ( v7 )
              this->clusters.num = granularity;
            v15 = (aasCluster_s *)Memory::Allocate(16 * granularity);
            v16 = 0;
            v7 = this->clusters.num <= 0;
            this->clusters.list = v15;
            if ( !v7 )
            {
              v17 = 0;
              do
              {
                v18 = (aasCluster_s *)((char *)v17 + (unsigned int)this->clusters.list);
                v18->numAreas = *v17;
                v18->numReachableAreas = v17[1];
                v18->numPortals = v17[2];
                ++v16;
                v18->firstPortal = v17[3];
                v17 += 4;
              }
              while ( v16 < this->clusters.num );
            }
          }
        }
        else
        {
          this->clusters.list = 0;
          this->clusters.num = 0;
          this->clusters.size = 0;
        }
      }
      num = this->clusters.num;
      size = this->clusters.size;
      if ( num == size )
      {
        if ( !this->clusters.granularity )
          this->clusters.granularity = 16;
        v21 = this->clusters.granularity + size - (this->clusters.granularity + size) % this->clusters.granularity;
        if ( v21 > 0 )
        {
          if ( v21 != this->clusters.size )
          {
            v22 = this->clusters.list;
            srcb = (Lexer *)v22;
            this->clusters.size = v21;
            if ( v21 < num )
              this->clusters.num = v21;
            v23 = (aasCluster_s *)Memory::Allocate(16 * v21);
            v24 = 0;
            v7 = this->clusters.num <= 0;
            this->clusters.list = v23;
            if ( !v7 )
            {
              v25 = 0;
              do
              {
                v26 = &v22[v25];
                v27 = &this->clusters.list[v25];
                v27->numAreas = v26->numAreas;
                v27->numReachableAreas = v26->numReachableAreas;
                v27->numPortals = v26->numPortals;
                v27->firstPortal = v26->firstPortal;
                v22 = (aasCluster_s *)srcb;
                ++v24;
                ++v25;
              }
              while ( v24 < this->clusters.num );
            }
            if ( v22 )
              Memory::Free(v22);
          }
        }
        else
        {
          if ( this->clusters.list )
            Memory::Free(this->clusters.list);
          this->clusters.list = 0;
          this->clusters.num = 0;
          this->clusters.size = 0;
        }
      }
      v28 = &this->clusters.list[this->clusters.num];
      v28->numAreas = cluster;
      v28->numReachableAreas = cluster_4;
      v28->numPortals = cluster_8;
      v28->firstPortal = cluster_12;
      ++this->clusters.num;
      --v30;
    }
    while ( v30 );
    v6 = numClusters;
  }
  if ( !Lexer::ExpectTokenString(src, "}") )
    return 0;
  if ( !v6 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseFeatures(class Lexer &)
bool __thiscall idAASFileLocal::ParseFeatures(idAASFileLocal *this, Lexer *src)
{
  Lexer *v2; // ebx
  int v4; // eax
  int v5; // edi
  bool v6; // cc
  aasFeature_s *list; // ebp
  aasFeature_s *v8; // eax
  int v9; // ecx
  int v10; // eax
  aasFeature_s *v11; // ebx
  int v12; // edx
  int granularity; // eax
  aasFeature_s *v15; // eax
  int v16; // ecx
  _DWORD *v17; // eax
  aasFeature_s *v18; // edx
  int num; // ebp
  int size; // ecx
  int v21; // eax
  aasFeature_s *v22; // edi
  aasFeature_s *v23; // eax
  int v24; // ecx
  int v25; // eax
  aasFeature_s *v26; // ebx
  aasFeature_s *v27; // edx
  aasFeature_s *v28; // [esp+10h] [ebp-10h]
  int v29; // [esp+10h] [ebp-10h]
  int feature; // [esp+14h] [ebp-Ch]
  int feature_4; // [esp+18h] [ebp-8h]
  int feature_8; // [esp+1Ch] [ebp-4h]

  v2 = src;
  v4 = Lexer::ParseInt(src);
  v5 = v4;
  if ( v4 > 0 )
  {
    if ( v4 != this->features.size )
    {
      v6 = v4 < this->features.num;
      list = this->features.list;
      v28 = list;
      this->features.size = v4;
      if ( v6 )
        this->features.num = v4;
      v8 = (aasFeature_s *)Memory::Allocate(12 * v4);
      v9 = 0;
      v6 = this->features.num <= 0;
      this->features.list = v8;
      if ( !v6 )
      {
        v10 = 0;
        do
        {
          v11 = &this->features.list[v10];
          *(_DWORD *)&v11->x = *(_DWORD *)&list[v10].x;
          *(_DWORD *)&v11->z = *(_DWORD *)&list[v10].z;
          v12 = *(_DWORD *)&list[v10].normalx;
          list = v28;
          ++v9;
          *(_DWORD *)&v11->normalx = v12;
          ++v10;
        }
        while ( v9 < this->features.num );
        v2 = src;
      }
      if ( list )
        Memory::Free(list);
    }
  }
  else
  {
    if ( this->features.list )
      Memory::Free(this->features.list);
    this->features.list = 0;
    this->features.num = 0;
    this->features.size = 0;
  }
  if ( !Lexer::ExpectTokenString(v2, "{") )
    return 0;
  if ( v5 > 0 )
  {
    HIBYTE(feature_8) = 0;
    v29 = v5;
    do
    {
      Lexer::ParseInt(v2);
      Lexer::ExpectTokenString(v2, "(");
      HIWORD(feature_4) = Lexer::ParseInt(v2);
      BYTE2(feature_8) = Lexer::ParseInt(v2);
      LOBYTE(feature_8) = Lexer::ParseInt(v2);
      BYTE1(feature_8) = Lexer::ParseInt(v2);
      LOWORD(feature) = Lexer::ParseInt(v2);
      HIWORD(feature) = Lexer::ParseInt(v2);
      LOWORD(feature_4) = Lexer::ParseInt(v2);
      Lexer::ExpectTokenString(v2, ")");
      if ( !this->features.list )
      {
        granularity = this->features.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->features.size )
          {
            v6 = granularity < this->features.num;
            this->features.size = granularity;
            if ( v6 )
              this->features.num = granularity;
            v15 = (aasFeature_s *)Memory::Allocate(12 * granularity);
            v16 = 0;
            v6 = this->features.num <= 0;
            this->features.list = v15;
            if ( !v6 )
            {
              v17 = 0;
              do
              {
                v18 = (aasFeature_s *)((char *)v17 + (unsigned int)this->features.list);
                *(_DWORD *)&v18->x = *v17;
                *(_DWORD *)&v18->z = v17[1];
                ++v16;
                *(_DWORD *)&v18->normalx = v17[2];
                v17 += 3;
              }
              while ( v16 < this->features.num );
            }
          }
        }
        else
        {
          this->features.list = 0;
          this->features.num = 0;
          this->features.size = 0;
        }
      }
      num = this->features.num;
      size = this->features.size;
      if ( num == size )
      {
        if ( !this->features.granularity )
          this->features.granularity = 16;
        v21 = this->features.granularity + size - (this->features.granularity + size) % this->features.granularity;
        if ( v21 > 0 )
        {
          if ( v21 != this->features.size )
          {
            v22 = this->features.list;
            this->features.size = v21;
            if ( v21 < num )
              this->features.num = v21;
            v23 = (aasFeature_s *)Memory::Allocate(12 * v21);
            v24 = 0;
            v6 = this->features.num <= 0;
            this->features.list = v23;
            if ( !v6 )
            {
              v25 = 0;
              do
              {
                v26 = &this->features.list[v25];
                *(_DWORD *)&v26->x = *(_DWORD *)&v22[v25].x;
                *(_DWORD *)&v26->z = *(_DWORD *)&v22[v25].z;
                ++v24;
                *(_DWORD *)&v26->normalx = *(_DWORD *)&v22[v25++].normalx;
              }
              while ( v24 < this->features.num );
              v2 = src;
            }
            if ( v22 )
              Memory::Free(v22);
          }
        }
        else
        {
          if ( this->features.list )
            Memory::Free(this->features.list);
          this->features.list = 0;
          this->features.num = 0;
          this->features.size = 0;
        }
      }
      v27 = &this->features.list[this->features.num];
      *(_DWORD *)&v27->x = feature;
      *(_DWORD *)&v27->z = feature_4;
      *(_DWORD *)&v27->normalx = feature_8;
      ++this->features.num;
      --v29;
    }
    while ( v29 );
  }
  return Lexer::ExpectTokenString(v2, "}") != 0;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::FinishAreas(void)
void __thiscall idAASFileLocal::FinishAreas(idAASFileLocal *this)
{
  int v1; // ebx
  int num; // eax
  int v4; // edx
  int v5; // ecx
  aasArea_s *v6; // eax
  aasArea_s *v7; // eax
  float *p_bounds; // eax
  int v9; // ebp
  aasArea_s *v10; // edi
  aasArea_s *v11; // edi
  idBounds *v12; // eax
  int v13; // ebp
  int v14; // edi
  aasArea_s *list; // ecx
  idAASFileLocal_vtbl *v16; // edx
  aasArea_s *v17; // eax
  double v18; // st7
  idAASFileLocal_vtbl *v19; // edx
  int numAreas; // edx
  int v21; // ecx
  int v22; // eax
  bool clamped; // [esp+15h] [ebp-FDh]
  idVec3 end; // [esp+16h] [ebp-FCh] BYREF
  aasTrace_s tr; // [esp+22h] [ebp-F0h] BYREF
  idVec3 point; // [esp+5Ah] [ebp-B8h] BYREF
  int trAreas[10]; // [esp+72h] [ebp-A0h] BYREF
  idVec3 points[10]; // [esp+9Ah] [ebp-78h] BYREF

  v1 = 0;
  num = this->areas.num;
  tr.areas = 0;
  tr.points = 0;
  memset(&tr, 0, 16);
  if ( num >= 2 )
  {
    v9 = 0;
    do
    {
      v10 = &this->areas.list[v1];
      v10->center = *idAASFileLocal::AreaReachableGoal(this, &end, v9);
      v11 = &this->areas.list[v1];
      v12 = this->AreaBounds(this, &point, v9);
      v11->bounds.b[0].x = v12->b[0].x;
      v11->bounds.b[0].y = v12->b[0].y;
      v11->bounds.b[0].z = v12->b[0].z;
      v11->bounds.b[1].x = v12->b[1].x;
      v11->bounds.b[1].y = v12->b[1].y;
      ++v9;
      v11->bounds.b[1].z = v12->b[1].z;
      ++v1;
    }
    while ( v9 < this->areas.num );
    v13 = 0;
    if ( this->areas.num > 0 )
    {
      v14 = 0;
      do
      {
        list = this->areas.list;
        if ( (list[v14].flags & 1) != 0 )
        {
          end.x = list[v14].center.x;
          end.y = list[v14].center.y;
          v17 = this->areas.list;
          end.z = list[v14].center.z;
          v18 = v17[v14].center.z + 500.0;
          tr.areas = trAreas;
          end.z = v18;
          tr.points = points;
          v19 = this->__vftable;
          tr.maxAreas = 10;
          v19->Trace(this, &tr, &v17[v14].center, &end);
          numAreas = tr.numAreas;
          clamped = 0;
          if ( tr.numAreas <= 1 )
            goto LABEL_18;
          v21 = 0;
          v22 = 0;
          do
          {
            if ( tr.areas[v21] != v13 )
            {
              this->areas.list[v14].ceiling = tr.points[v22].z;
              numAreas = tr.numAreas;
              clamped = 1;
            }
            ++v21;
            ++v22;
          }
          while ( v21 < numAreas );
          if ( !clamped )
LABEL_18:
            this->areas.list[v14].ceiling = tr.endpos.z;
        }
        else
        {
          v16 = this->__vftable;
          point.x = 0.0;
          point.y = 0.0;
          point.z = 131072.0;
          v16->PushPointIntoAreaNum(this, v13, &point);
          this->areas.list[v14].ceiling = point.z;
        }
        ++v13;
        ++v14;
      }
      while ( v13 < this->areas.num );
    }
  }
  else
  {
    v4 = 0;
    if ( num > 0 )
    {
      v5 = 0;
      do
      {
        v6 = this->areas.list;
        v6[v5].center.z = 0.0;
        v6[v5].center.y = 0.0;
        v6[v5].center.x = 0.0;
        v7 = this->areas.list;
        v7[v5].bounds.b[0].z = idMath::INFINITY;
        p_bounds = (float *)&v7[v5].bounds;
        p_bounds[1] = idMath::INFINITY;
        *p_bounds = idMath::INFINITY;
        ++v4;
        p_bounds[5] = -1.0e30;
        ++v5;
        p_bounds[4] = -1.0e30;
        p_bounds[3] = -1.0e30;
        this->areas.list[v5 - 1].ceiling = 0.0;
      }
      while ( v4 < this->areas.num );
    }
  }
}

// FUNC: private: int __thiscall idAASFileLocal::NumReachabilities(void)const
int __thiscall idAASFileLocal::NumReachabilities(idAASFileLocal *this)
{
  int num; // esi
  int result; // eax
  idReachability **p_reach; // edx
  idReachability *i; // ecx

  num = this->areas.num;
  result = 0;
  if ( num > 0 )
  {
    p_reach = &this->areas.list->reach;
    do
    {
      for ( i = *p_reach; i; ++result )
        i = i->next;
      p_reach += 19;
      --num;
    }
    while ( num );
  }
  return result;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::ReportRoutingEfficiency(void)const
void __thiscall idAASFileLocal::ReportRoutingEfficiency(idAASFileLocal *this)
{
  int num; // edi
  int v3; // edx
  int v4; // ebx
  int *p_numReachableAreas; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  idReachability **p_reach; // esi
  int v10; // edx
  idReachability *i; // eax

  num = this->clusters.num;
  v3 = 0;
  v4 = 0;
  if ( num > 0 )
  {
    p_numReachableAreas = &this->clusters.list->numReachableAreas;
    do
    {
      v3 += *p_numReachableAreas;
      v4 += *p_numReachableAreas * *p_numReachableAreas;
      p_numReachableAreas += 4;
      --num;
    }
    while ( num );
  }
  v6 = v3 * this->portals.num + v4;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d reachable areas\n",
    v3);
  v7 = this->areas.num;
  v8 = 0;
  if ( v7 > 0 )
  {
    p_reach = &this->areas.list->reach;
    v10 = v7;
    do
    {
      for ( i = *p_reach; i; ++v8 )
        i = i->next;
      p_reach += 19;
      --v10;
    }
    while ( v10 );
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%6d reachabilities\n", v8);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d KB max routing cache\n",
    (3 * v6) >> 10);
}

// FUNC: public: virtual void __thiscall idAASFileLocal::DeleteReachabilities(void)
void __thiscall idAASFileLocal::DeleteReachabilities(idAASFileLocal *this)
{
  int v2; // ebp
  int v3; // edi
  idReachability *reach; // eax
  idReachability *next; // ebx

  v2 = 0;
  if ( this->areas.num > 0 )
  {
    v3 = 0;
    do
    {
      reach = this->areas.list[v3].reach;
      if ( reach )
      {
        do
        {
          next = reach->next;
          Memory::Free(reach);
          reach = next;
        }
        while ( next );
      }
      this->areas.list[v3].reach = 0;
      this->areas.list[v3].rev_reach = 0;
      ++v2;
      ++v3;
    }
    while ( v2 < this->areas.num );
  }
}

// FUNC: public: virtual void __thiscall idAASFileLocal::DeleteClusters(void)
void __thiscall idAASFileLocal::DeleteClusters(idAASFileLocal *this)
{
  aasPortal_s *list; // eax
  int granularity; // eax
  bool v4; // cc
  aasPortal_s *v5; // eax
  int v6; // ecx
  _DWORD *v7; // eax
  aasPortal_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  aasPortal_s *v12; // edi
  aasPortal_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  aasPortal_s *v16; // ebx
  int v17; // eax
  aasCluster_s *v18; // eax
  int v19; // ecx
  int *v20; // eax
  aasCluster_s *v21; // edx
  int v22; // ebx
  int v23; // ecx
  int v24; // ecx
  aasCluster_s *v25; // edi
  aasCluster_s *v26; // eax
  int v27; // ecx
  int v28; // eax
  aasCluster_s *v29; // ebx
  aasCluster_s *v30; // ecx
  aasPortal_s portal; // [esp+10h] [ebp-Ch] BYREF

  list = this->portals.list;
  memset(&portal, 0, sizeof(portal));
  if ( list )
    Memory::Free(list);
  this->portals.list = 0;
  this->portals.num = 0;
  this->portals.size = 0;
  if ( this->portalIndex.list )
    Memory::Free(this->portalIndex.list);
  this->portalIndex.list = 0;
  this->portalIndex.num = 0;
  this->portalIndex.size = 0;
  if ( this->clusters.list )
    Memory::Free(this->clusters.list);
  this->clusters.list = 0;
  this->clusters.num = 0;
  this->clusters.size = 0;
  if ( !this->portals.list )
  {
    granularity = this->portals.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->portals.size )
      {
        v4 = granularity < this->portals.num;
        this->portals.size = granularity;
        if ( v4 )
          this->portals.num = granularity;
        v5 = (aasPortal_s *)Memory::Allocate(12 * granularity);
        v6 = 0;
        v4 = this->portals.num <= 0;
        this->portals.list = v5;
        if ( !v4 )
        {
          v7 = 0;
          do
          {
            v8 = (aasPortal_s *)((char *)v7 + (unsigned int)this->portals.list);
            *(_DWORD *)&v8->areaNum = *v7;
            *(_DWORD *)&v8->clusters[1] = v7[1];
            ++v6;
            *(_DWORD *)&v8->clusterAreaNum[1] = v7[2];
            v7 += 3;
          }
          while ( v6 < this->portals.num );
        }
      }
    }
    else
    {
      this->portals.list = 0;
      this->portals.num = 0;
      this->portals.size = 0;
    }
  }
  num = this->portals.num;
  size = this->portals.size;
  if ( num == size )
  {
    if ( !this->portals.granularity )
      this->portals.granularity = 16;
    v11 = this->portals.granularity + size - (this->portals.granularity + size) % this->portals.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->portals.size )
      {
        v12 = this->portals.list;
        this->portals.size = v11;
        if ( v11 < num )
          this->portals.num = v11;
        v13 = (aasPortal_s *)Memory::Allocate(12 * v11);
        v14 = 0;
        v4 = this->portals.num <= 0;
        this->portals.list = v13;
        if ( !v4 )
        {
          v15 = 0;
          do
          {
            v16 = &this->portals.list[v15];
            *(_DWORD *)&v16->areaNum = *(_DWORD *)&v12[v15].areaNum;
            *(_DWORD *)&v16->clusters[1] = *(_DWORD *)&v12[v15].clusters[1];
            ++v14;
            *(_DWORD *)&v16->clusterAreaNum[1] = *(_DWORD *)&v12[v15++].clusterAreaNum[1];
          }
          while ( v14 < this->portals.num );
        }
        if ( v12 )
          Memory::Free(v12);
      }
    }
    else
    {
      if ( this->portals.list )
        Memory::Free(this->portals.list);
      this->portals.list = 0;
      this->portals.num = 0;
      this->portals.size = 0;
    }
  }
  this->portals.list[this->portals.num++] = portal;
  if ( !this->clusters.list )
  {
    v17 = this->clusters.granularity;
    if ( v17 > 0 )
    {
      if ( v17 != this->clusters.size )
      {
        v4 = v17 < this->clusters.num;
        this->clusters.size = v17;
        if ( v4 )
          this->clusters.num = v17;
        v18 = (aasCluster_s *)Memory::Allocate(16 * v17);
        v19 = 0;
        v4 = this->clusters.num <= 0;
        this->clusters.list = v18;
        if ( !v4 )
        {
          v20 = 0;
          do
          {
            v21 = (aasCluster_s *)((char *)v20 + (unsigned int)this->clusters.list);
            v21->numAreas = *v20;
            v21->numReachableAreas = v20[1];
            v21->numPortals = v20[2];
            ++v19;
            v21->firstPortal = v20[3];
            v20 += 4;
          }
          while ( v19 < this->clusters.num );
        }
      }
    }
    else
    {
      this->clusters.list = 0;
      this->clusters.num = 0;
      this->clusters.size = 0;
    }
  }
  v22 = this->clusters.num;
  v23 = this->clusters.size;
  if ( v22 == v23 )
  {
    if ( !this->clusters.granularity )
      this->clusters.granularity = 16;
    v24 = this->clusters.granularity + v23 - (this->clusters.granularity + v23) % this->clusters.granularity;
    if ( v24 > 0 )
    {
      if ( v24 != this->clusters.size )
      {
        v25 = this->clusters.list;
        this->clusters.size = v24;
        if ( v24 < v22 )
          this->clusters.num = v24;
        v26 = (aasCluster_s *)Memory::Allocate(16 * v24);
        v27 = 0;
        v4 = this->clusters.num <= 0;
        this->clusters.list = v26;
        if ( !v4 )
        {
          v28 = 0;
          do
          {
            v29 = &this->clusters.list[v28];
            v29->numAreas = v25[v28].numAreas;
            v29->numReachableAreas = v25[v28].numReachableAreas;
            v29->numPortals = v25[v28].numPortals;
            ++v27;
            v29->firstPortal = v25[v28++].firstPortal;
          }
          while ( v27 < this->clusters.num );
        }
        if ( v25 )
          Memory::Free(v25);
      }
    }
    else
    {
      if ( this->clusters.list )
        Memory::Free(this->clusters.list);
      this->clusters.list = 0;
      this->clusters.num = 0;
      this->clusters.size = 0;
    }
  }
  v30 = &this->clusters.list[this->clusters.num];
  v30->numAreas = 0;
  v30->numReachableAreas = 0;
  v30->numPortals = 0;
  v30->firstPortal = 0;
  ++this->clusters.num;
}

// FUNC: public: bool __thiscall idAASSettings::FromParser(class Lexer &)
char __thiscall idAASSettings::FromParser(idAASSettings *this, Lexer *src)
{
  char v5; // al
  int len; // esi
  long double v7; // st4
  long double v8; // st7
  long double v9; // st6
  double v10; // st7
  double v11; // st6
  idDict *v12; // esi
  float y; // edx
  float z; // eax
  idVec3 tempColor; // [esp+8h] [ebp-68h] BYREF
  idToken token; // [esp+14h] [ebp-5Ch] BYREF
  int v17; // [esp+6Ch] [ebp-4h]
  int srca; // [esp+74h] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v17 = 0;
  if ( !Lexer::ExpectTokenString(src, "{") )
  {
LABEL_2:
    v17 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  while ( Lexer::ReadToken(src, &token) )
  {
    if ( !idStr::Cmp(token.data, "}") )
      break;
    if ( idStr::Cmp(token.data, "bboxes") )
    {
      if ( idStr::Cmp(token.data, "usePatches") )
      {
        if ( idStr::Cmp(token.data, "writeBrushMap") )
        {
          if ( idStr::Cmp(token.data, "playerFlood") )
          {
            if ( idStr::Cmp(token.data, "allowSwimReachabilities") )
            {
              if ( !idStr::Cmp(token.data, "allowFlyReachabilities") )
              {
                v5 = idAASSettings::ParseBool(this, src, &this->allowFlyReachabilities);
                goto LABEL_22;
              }
              if ( !idStr::Cmp(token.data, "generateTacticalFeatures") )
              {
                v5 = idAASSettings::ParseBool(this, src, &this->generateTacticalFeatures);
                goto LABEL_22;
              }
              if ( idStr::Cmp(token.data, "fileExtension") )
              {
                if ( idStr::Cmp(token.data, "gravity") )
                {
                  if ( !idStr::Cmp(token.data, "maxStepHeight") )
                  {
                    v5 = idAASSettings::ParseFloat(this, src, &this->maxStepHeight);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "maxBarrierHeight") )
                  {
                    v5 = idAASSettings::ParseFloat(this, src, &this->maxBarrierHeight);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "maxWaterJumpHeight") )
                  {
                    v5 = idAASSettings::ParseFloat(this, src, &this->maxWaterJumpHeight);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "maxFallHeight") )
                  {
                    v5 = idAASSettings::ParseFloat(this, src, &this->maxFallHeight);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "minFloorCos") )
                  {
                    v5 = idAASSettings::ParseFloat(this, src, &this->minFloorCos);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "tt_barrierJump") )
                  {
                    v5 = idAASSettings::ParseInt(this, src, &this->tt_barrierJump);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "tt_startCrouching") )
                  {
                    v5 = idAASSettings::ParseInt(this, src, &this->tt_startCrouching);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "tt_waterJump") )
                  {
                    v5 = idAASSettings::ParseInt(this, src, &this->tt_waterJump);
                    goto LABEL_22;
                  }
                  if ( !idStr::Cmp(token.data, "tt_startWalkOffLedge") )
                  {
                    v5 = idAASSettings::ParseInt(this, src, &this->tt_startWalkOffLedge);
LABEL_22:
                    if ( !v5 )
                      goto LABEL_2;
                    continue;
                  }
                  Lexer::Error(src, "invalid token '%s'", token.data);
                }
                else
                {
                  idAASSettings::ParseVector(this, src, &this->gravity);
                  this->gravityDir.x = this->gravity.x;
                  this->gravityDir.y = this->gravity.y;
                  this->gravityDir.z = this->gravity.z;
                  v7 = this->gravityDir.x * this->gravityDir.x
                     + this->gravityDir.y * this->gravityDir.y
                     + this->gravityDir.z * this->gravityDir.z;
                  if ( v7 == 0.0 )
                  {
                    v8 = 0.0;
                  }
                  else
                  {
                    v9 = 1.0 / sqrt(v7);
                    this->gravityDir.x = v9 * this->gravityDir.x;
                    this->gravityDir.y = v9 * this->gravityDir.y;
                    this->gravityDir.z = v9 * this->gravityDir.z;
                    v8 = v7 * v9;
                  }
                  this->gravityValue = v8;
                  v10 = -this->gravityDir.z;
                  v11 = -this->gravityDir.y;
                  this->invGravityDir.x = -this->gravityDir.x;
                  this->invGravityDir.y = v11;
                  this->invGravityDir.z = v10;
                }
              }
              else
              {
                Lexer::ExpectTokenString(src, "=");
                Lexer::ExpectTokenType(src, 1, 0, &token);
                len = token.len;
                srca = token.len;
                if ( token.len + 1 > this->fileExtension.alloced )
                  idStr::ReAllocate(&this->fileExtension, token.len + 1, 0);
                qmemcpy(this->fileExtension.data, token.data, len);
                this->fileExtension.data[srca] = 0;
                this->fileExtension.len = srca;
              }
            }
            else
            {
              if ( !Lexer::ExpectTokenString(src, "=") )
                goto LABEL_2;
              this->allowSwimReachabilities = Lexer::ParseBool(src);
            }
          }
          else
          {
            if ( !Lexer::ExpectTokenString(src, "=") )
              goto LABEL_2;
            this->playerFlood = Lexer::ParseBool(src);
          }
        }
        else
        {
          if ( !Lexer::ExpectTokenString(src, "=") )
            goto LABEL_2;
          this->writeBrushMap = Lexer::ParseBool(src);
        }
      }
      else
      {
        if ( !Lexer::ExpectTokenString(src, "=") )
          goto LABEL_2;
        this->usePatches = Lexer::ParseBool(src);
      }
    }
    else if ( !idAASSettings::ParseBBoxes(this, src) )
    {
      goto LABEL_2;
    }
  }
  if ( this->numBoundingBoxes <= 0 )
    Lexer::Error(src, "no valid bounding box");
  v12 = (idDict *)gameEdit->FindEntityDefDict(gameEdit, this->fileExtension.data, 0);
  if ( v12 )
  {
    if ( idDict::GetVector(v12, "debugColor", "1.0 0.0 0.0", &tempColor) )
    {
      y = tempColor.y;
      z = tempColor.z;
      this->debugColor.x = tempColor.x;
      this->debugColor.y = y;
      this->debugColor.z = z;
      this->debugColor.w = 1.0;
    }
    idDict::GetBool(v12, "debugDraw", "1", &this->debugDraw);
  }
  idDict::GetBool(v12, "generateTacticalFeatures", "0", &this->generateTacticalFeatures);
  v17 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual __thiscall idAASFileLocal::~idAASFileLocal(void)
void __thiscall idAASFileLocal::~idAASFileLocal(idAASFileLocal *this)
{
  int v2; // ebp
  idReachability *reach; // eax
  idReachability *next; // edi
  aasFeature_s *list; // eax
  int *v6; // eax
  aasCluster_s *v7; // eax
  int *v8; // eax
  aasPortal_s *v9; // eax
  aasNode_s *v10; // eax
  aasArea_s *v11; // eax
  int *v12; // eax
  aasFace_s *v13; // eax
  int *v14; // eax
  aasEdge_s *v15; // eax
  idVec3 *v16; // eax
  int v17; // [esp+Ch] [ebp-14h]

  this->__vftable = (idAASFileLocal_vtbl *)&idAASFileLocal::`vftable';
  v2 = 0;
  if ( this->areas.num > 0 )
  {
    v17 = 0;
    do
    {
      reach = this->areas.list[v17].reach;
      if ( reach )
      {
        do
        {
          next = reach->next;
          Memory::Free(reach);
          reach = next;
        }
        while ( next );
      }
      ++v17;
      ++v2;
    }
    while ( v2 < this->areas.num );
  }
  idStr::FreeData(&this->settings.fileExtension);
  list = this->features.list;
  if ( list )
    Memory::Free(list);
  this->features.list = 0;
  this->features.num = 0;
  this->features.size = 0;
  v6 = this->featureIndex.list;
  if ( v6 )
    Memory::Free(v6);
  this->featureIndex.list = 0;
  this->featureIndex.num = 0;
  this->featureIndex.size = 0;
  v7 = this->clusters.list;
  if ( v7 )
    Memory::Free(v7);
  this->clusters.list = 0;
  this->clusters.num = 0;
  this->clusters.size = 0;
  v8 = this->portalIndex.list;
  if ( v8 )
    Memory::Free(v8);
  this->portalIndex.list = 0;
  this->portalIndex.num = 0;
  this->portalIndex.size = 0;
  v9 = this->portals.list;
  if ( v9 )
    Memory::Free(v9);
  this->portals.list = 0;
  this->portals.num = 0;
  this->portals.size = 0;
  v10 = this->nodes.list;
  if ( v10 )
    Memory::Free(v10);
  this->nodes.list = 0;
  this->nodes.num = 0;
  this->nodes.size = 0;
  v11 = this->areas.list;
  if ( v11 )
    Memory::Free(v11);
  this->areas.list = 0;
  this->areas.num = 0;
  this->areas.size = 0;
  v12 = this->faceIndex.list;
  if ( v12 )
    Memory::Free(v12);
  this->faceIndex.list = 0;
  this->faceIndex.num = 0;
  this->faceIndex.size = 0;
  v13 = this->faces.list;
  if ( v13 )
    Memory::Free(v13);
  this->faces.list = 0;
  this->faces.num = 0;
  this->faces.size = 0;
  v14 = this->edgeIndex.list;
  if ( v14 )
    Memory::Free(v14);
  this->edgeIndex.list = 0;
  this->edgeIndex.num = 0;
  this->edgeIndex.size = 0;
  v15 = this->edges.list;
  if ( v15 )
    Memory::Free(v15);
  this->edges.list = 0;
  this->edges.num = 0;
  this->edges.size = 0;
  v16 = this->vertices.list;
  if ( v16 )
    Memory::Free(v16);
  this->vertices.list = 0;
  this->vertices.num = 0;
  this->vertices.size = 0;
  idPlaneSet::~idPlaneSet(&this->planeList);
  idStr::FreeData(&this->version);
  idStr::FreeData(&this->name);
  this->__vftable = (idAASFileLocal_vtbl *)&idAASFile::`vftable';
}

// FUNC: public: virtual bool __thiscall idAASFileLocal::Write(class idStr const &,unsigned int)
char __thiscall idAASFileLocal::Write(idAASFileLocal *this, const idStr *fileName, unsigned int mapFileCRC)
{
  int len; // ecx
  int v5; // eax
  idFile *v6; // eax
  idFile *v7; // esi
  int v9; // edi
  int v10; // edi
  int j; // edi
  int k; // edi
  int v13; // edi
  aasFace_s *v14; // eax
  int m; // edi
  int v16; // edi
  char *v17; // eax
  int v18; // ecx
  int ii; // edx
  idReachability_Special *jj; // edi
  int v21; // edi
  int v22; // edi
  aasPortal_s *v23; // eax
  int kk; // edi
  int v25; // edi
  int mm; // edi
  int v27; // edi
  aasFeature_s *v28; // eax
  int i; // [esp+54h] [ebp-8h]
  int ia; // [esp+54h] [ebp-8h]
  int ib; // [esp+54h] [ebp-8h]
  int ic; // [esp+54h] [ebp-8h]
  int v33; // [esp+58h] [ebp-4h]
  int n; // [esp+58h] [ebp-4h]
  int v35; // [esp+58h] [ebp-4h]
  int v36; // [esp+58h] [ebp-4h]
  int v37; // [esp+58h] [ebp-4h]
  int v38; // [esp+58h] [ebp-4h]

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "[Write AAS]\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "writing %s\n",
    fileName->data);
  len = fileName->len;
  v5 = fileName->len + 1;
  v33 = fileName->len;
  if ( v5 > this->name.alloced )
  {
    idStr::ReAllocate(&this->name, v5, 0);
    len = v33;
  }
  qmemcpy(this->name.data, fileName->data, len);
  this->name.data[v33] = 0;
  this->name.len = v33;
  this->crc = mapFileCRC;
  v6 = fileSystem->OpenFileWrite(fileSystem, fileName->data, "fs_devpath", 0);
  v7 = v6;
  if ( v6 )
  {
    v6->WriteFloatString(v6, "%s \"%s\"\n\n", "DewmAAS", "1.08");
    v7->WriteFloatString(v7, "%u\n\n", mapFileCRC);
    v7->WriteFloatString(v7, "settings\n");
    idAASSettings::WriteToFile(&this->settings, v7);
    v7->WriteFloatString(v7, "planes %d {\n", this->planeList.num);
    v9 = 0;
    if ( this->planeList.num > 0 )
    {
      i = 0;
      do
      {
        v7->WriteFloatString(
          v7,
          "\t%d ( %f %f %f %f )\n",
          v9,
          this->planeList.list[i].a,
          this->planeList.list[i].b,
          this->planeList.list[i].c,
          -this->planeList.list[i].d);
        ++i;
        ++v9;
      }
      while ( v9 < this->planeList.num );
    }
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "vertices %d {\n", this->vertices.num);
    v10 = 0;
    if ( this->vertices.num > 0 )
    {
      ia = 0;
      do
      {
        v7->WriteFloatString(
          v7,
          "\t%d ( %f %f %f )\n",
          v10,
          this->vertices.list[ia].x,
          this->vertices.list[ia].y,
          this->vertices.list[ia].z);
        ++ia;
        ++v10;
      }
      while ( v10 < this->vertices.num );
    }
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "edges %d {\n", this->edges.num);
    for ( j = 0; j < this->edges.num; ++j )
      v7->WriteFloatString(v7, "\t%d ( %d %d )\n", j, *(_QWORD *)&this->edges.list[j]);
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "edgeIndex %d {\n", this->edgeIndex.num);
    for ( k = 0; k < this->edgeIndex.num; ++k )
      v7->WriteFloatString(v7, "\t%d ( %d )\n", k, this->edgeIndex.list[k]);
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "faces %d {\n", this->faces.num);
    v13 = 0;
    if ( this->faces.num > 0 )
    {
      ib = 0;
      do
      {
        v14 = &this->faces.list[ib];
        v7->WriteFloatString(
          v7,
          "\t%d ( %d %d %d %d %d %d )\n",
          v13,
          v14->planeNum,
          v14->flags,
          v14->areas[0],
          v14->areas[1],
          v14->firstEdge,
          v14->numEdges);
        ++ib;
        ++v13;
      }
      while ( v13 < this->faces.num );
    }
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "faceIndex %d {\n", this->faceIndex.num);
    for ( m = 0; m < this->faceIndex.num; ++m )
      v7->WriteFloatString(v7, "\t%d ( %d )\n", m, this->faceIndex.list[m]);
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "areas %d {\n", this->areas.num);
    v16 = 0;
    ic = 0;
    if ( this->areas.num > 0 )
    {
      for ( n = 0; ; v16 = n )
      {
        v17 = (char *)this->areas.list + v16;
        v18 = *((_DWORD *)v17 + 15);
        for ( ii = 0; v18; ++ii )
          v18 = *(_DWORD *)(v18 + 40);
        v7->WriteFloatString(
          v7,
          "\t%d ( %d %d %d %d %d %d %d %d ) %d {\n",
          ic,
          *((unsigned __int16 *)v17 + 24),
          *((unsigned __int16 *)v17 + 25),
          *((_DWORD *)v17 + 1),
          *(_DWORD *)v17,
          *((__int16 *)v17 + 26),
          *((__int16 *)v17 + 27),
          *((unsigned __int16 *)v17 + 34),
          *((unsigned __int16 *)v17 + 35),
          ii);
        for ( jj = *(idReachability_Special **)((char *)&this->areas.list->reach + v16);
              jj;
              jj = (idReachability_Special *)jj->next )
        {
          v7->WriteFloatString(
            v7,
            "\t\t%d %d (%f %f %f) (%f %f %f) %d %d",
            jj->travelType,
            jj->toAreaNum,
            jj->start.x,
            jj->start.y,
            jj->start.z,
            jj->end.x,
            jj->end.y,
            jj->end.z,
            jj->edgeNum,
            jj->travelTime);
          if ( jj->travelType == 4096 )
            Reachability_Special_Write(v7, jj);
          v7->WriteFloatString(v7, "\n");
        }
        v7->WriteFloatString(v7, "\t}\n");
        n += 76;
        if ( ++ic >= this->areas.num )
          break;
      }
    }
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "nodes %d {\n", this->nodes.num);
    v21 = 0;
    if ( this->nodes.num > 0 )
    {
      v35 = 0;
      do
      {
        v7->WriteFloatString(
          v7,
          "\t%d ( %d %d %d )\n",
          v21,
          this->nodes.list[v35].planeNum,
          this->nodes.list[v35].children[0],
          this->nodes.list[v35].children[1]);
        ++v35;
        ++v21;
      }
      while ( v21 < this->nodes.num );
    }
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "portals %d {\n", this->portals.num);
    v22 = 0;
    if ( this->portals.num > 0 )
    {
      v36 = 0;
      do
      {
        v23 = &this->portals.list[v36];
        v7->WriteFloatString(
          v7,
          "\t%d ( %d %d %d %d %d )\n",
          v22,
          v23->areaNum,
          v23->clusters[0],
          v23->clusters[1],
          v23->clusterAreaNum[0],
          v23->clusterAreaNum[1]);
        ++v36;
        ++v22;
      }
      while ( v22 < this->portals.num );
    }
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "portalIndex %d {\n", this->portalIndex.num);
    for ( kk = 0; kk < this->portalIndex.num; ++kk )
      v7->WriteFloatString(v7, "\t%d ( %d )\n", kk, this->portalIndex.list[kk]);
    v7->WriteFloatString(v7, "}\n");
    v7->WriteFloatString(v7, "clusters %d {\n", this->clusters.num);
    v25 = 0;
    if ( this->clusters.num > 0 )
    {
      v37 = 0;
      do
      {
        v7->WriteFloatString(
          v7,
          "\t%d ( %d %d %d %d )\n",
          v25,
          this->clusters.list[v37].numAreas,
          this->clusters.list[v37].numReachableAreas,
          this->clusters.list[v37].firstPortal,
          this->clusters.list[v37].numPortals);
        ++v37;
        ++v25;
      }
      while ( v25 < this->clusters.num );
    }
    v7->WriteFloatString(v7, "}\n");
    if ( this->features.num )
    {
      v7->WriteFloatString(v7, "featureIndex %d {\n", this->featureIndex.num);
      for ( mm = 0; mm < this->featureIndex.num; ++mm )
        v7->WriteFloatString(v7, "\t%d ( %d )\n", mm, this->featureIndex.list[mm]);
      v7->WriteFloatString(v7, "}\n");
      v7->WriteFloatString(v7, "features %d {\n", this->features.num);
      v27 = 0;
      if ( this->features.num > 0 )
      {
        v38 = 0;
        do
        {
          v28 = &this->features.list[v38];
          v7->WriteFloatString(
            v7,
            "\t%d ( %d %d %d %d %d %d %d )\n",
            v27,
            v28->flags,
            v28->height,
            v28->normalx,
            v28->normaly,
            v28->x,
            v28->y,
            v28->z);
          ++v38;
          ++v27;
        }
        while ( v27 < this->features.num );
      }
      v7->WriteFloatString(v7, "}\n");
    }
    fileSystem->CloseFile(fileSystem, v7);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "done.\n");
    return 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Error opening %s",
      fileName->data);
    return 0;
  }
}

// FUNC: private: bool __thiscall idAASFileLocal::ParsePlanes(class Lexer &,int)
char __thiscall idAASFileLocal::ParsePlanes(idAASFileLocal *this, Lexer *src, int idx)
{
  Lexer *v3; // edi
  int v5; // ebx
  idPlaneSet *p_planeList; // esi
  int i; // ebp
  int size; // eax
  int v10; // edx
  float plane; // [esp+10h] [ebp-20h]
  float plane_4; // [esp+14h] [ebp-1Ch]
  float plane_8; // [esp+18h] [ebp-18h]
  float plane_12; // [esp+1Ch] [ebp-14h]
  idVec4 vec; // [esp+20h] [ebp-10h] BYREF

  v3 = src;
  v5 = Lexer::ParseInt(src);
  p_planeList = &this->planeList;
  idList<idPlane>::Resize(p_planeList, v5);
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  for ( i = 0; i < v5; ++p_planeList->num )
  {
    Lexer::ParseInt(v3);
    if ( !Lexer::Parse1DMatrix(v3, 4, &vec.x) )
      return 0;
    plane_12 = -vec.w;
    plane = vec.x;
    plane_4 = vec.y;
    plane_8 = vec.z;
    if ( !p_planeList->list )
      idList<idPlane>::Resize(p_planeList, p_planeList->granularity);
    size = p_planeList->size;
    if ( p_planeList->num == size )
    {
      if ( !p_planeList->granularity )
        p_planeList->granularity = 16;
      idList<idPlane>::Resize(
        p_planeList,
        size + p_planeList->granularity - (size + p_planeList->granularity) % p_planeList->granularity);
      v3 = src;
    }
    v10 = (int)&p_planeList->list[p_planeList->num];
    ++i;
    *(float *)v10 = plane;
    *(float *)(v10 + 4) = plane_4;
    *(float *)(v10 + 8) = plane_8;
    *(float *)(v10 + 12) = plane_12;
  }
  if ( !Lexer::ExpectTokenString(v3, "}") )
    return 0;
  if ( !v5 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseVertices(class Lexer &,int)
char __thiscall idAASFileLocal::ParseVertices(idAASFileLocal *this, Lexer *src, int idx)
{
  Lexer *v3; // edi
  int v5; // ebp
  idList<idAngles> *p_vertices; // esi
  int v8; // ebx
  int size; // eax
  idVec3 vec; // [esp+10h] [ebp-Ch] BYREF

  v3 = src;
  v5 = Lexer::ParseInt(src);
  p_vertices = (idList<idAngles> *)&this->vertices;
  idList<idVec3>::Resize(p_vertices, v5);
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  v8 = 0;
  if ( v5 > 0 )
  {
    do
    {
      Lexer::ParseInt(v3);
      if ( !Lexer::Parse1DMatrix(v3, 3, &vec.x) )
        return 0;
      if ( !p_vertices->list )
        idList<idVec3>::Resize(p_vertices, p_vertices->granularity);
      size = p_vertices->size;
      if ( p_vertices->num == size )
      {
        if ( !p_vertices->granularity )
          p_vertices->granularity = 16;
        idList<idVec3>::Resize(
          p_vertices,
          size + p_vertices->granularity - (size + p_vertices->granularity) % p_vertices->granularity);
        v3 = src;
      }
      p_vertices->list[p_vertices->num++] = (idAngles)vec;
    }
    while ( ++v8 < v5 );
  }
  if ( !Lexer::ExpectTokenString(v3, "}") )
    return 0;
  if ( !v5 && idx != 11 )
    this->isDummy[idx] = 1;
  return 1;
}

// FUNC: public: int __thiscall idAASFileLocal::MemorySize(void)const
int __thiscall idAASFileLocal::MemorySize(idAASFileLocal *this)
{
  return 4
       * (this->edgeIndex.size
        + this->faceIndex.size
        + this->portalIndex.size
        + this->featureIndex.size
        + 19 * this->areas.size
        + 3 * (this->vertices.size + this->nodes.size + this->portals.size + this->features.size)
        + 13 * (idAASFileLocal::NumReachabilities(this) + 4)
        + 2 * (this->edges.size + 2 * (this->planeList.size + this->faces.size + this->clusters.size)));
}

// FUNC: public: virtual void __thiscall idAASFileLocal::PrintInfo(void)const
void __thiscall idAASFileLocal::PrintInfo(idAASFileLocal *this)
{
  netadrtype_t type; // edi
  int v2; // ebx
  int v4; // eax
  int v5; // edi
  int v6; // eax

  type = common.type;
  v2 = *(_DWORD *)common.type;
  v4 = idAASFileLocal::MemorySize(this);
  (*(void (**)(netadrtype_t, const char *, ...))(v2 + 124))(type, "%6d KB file size\n", v4 >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d areas\n",
    this->areas.num);
  v5 = *(_DWORD *)common.type;
  v6 = idAASFileLocal::MaxTreeDepth(this);
  (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(common.type, "%6d max tree depth\n", v6);
  this->ReportRoutingEfficiency(this);
}

// FUNC: public: virtual unsigned int __thiscall idAASFileLocal::GetMemorySize(void)
int __thiscall idAASFileLocal::GetMemorySize(idAASFileLocal *this)
{
  int num; // edx
  int v3; // edi
  int v4; // esi
  int *p_numReachableAreas; // ecx

  num = this->clusters.num;
  v3 = 0;
  v4 = 0;
  if ( num > 0 )
  {
    p_numReachableAreas = &this->clusters.list->numReachableAreas;
    do
    {
      v4 += *p_numReachableAreas;
      v3 += *p_numReachableAreas * *p_numReachableAreas;
      p_numReachableAreas += 4;
      --num;
    }
    while ( num );
  }
  return v3 + idAASFileLocal::MemorySize(this) + 3 * v4 * this->portals.num;
}

// FUNC: public: virtual class idReachability * __thiscall idAASFileLocal::CreateReachability(int)
void __thiscall idAASFileLocal::CreateReachability(idAASFileLocal *this, int type)
{
  idReachability_Special *v2; // eax

  switch ( type )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      Memory::Allocate(0x34u);
      break;
    case 6:
      v2 = (idReachability_Special *)Memory::Allocate(0x60u);
      if ( v2 )
        idReachability_Special::idReachability_Special(v2);
      break;
    default:
      return;
  }
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseReachabilities(class Lexer &,int)
char __thiscall idAASFileLocal::ParseReachabilities(idAASFileLocal *this, Lexer *src, int areaNum)
{
  aasArea_s *v5; // ebx
  idReachability_Special *v6; // esi
  idReachability_Special *v7; // eax
  idReachability_Special *v8; // eax
  bool v9; // zf
  idReachability reach; // [esp+10h] [ebp-40h] BYREF
  int v12; // [esp+4Ch] [ebp-4h]
  int areaNuma; // [esp+58h] [ebp+8h]

  v5 = &this->areas.list[areaNum];
  areaNuma = Lexer::ParseInt(src);
  Lexer::ExpectTokenString(src, "{");
  v5->reach = 0;
  v5->rev_reach = 0;
  v5->travelFlags = idAASFileLocal::AreaContentsTravelFlags(this, areaNum);
  if ( areaNuma > 0 )
  {
    do
    {
      reach.travelType = Lexer::ParseInt(src);
      reach.toAreaNum = Lexer::ParseInt(src);
      Lexer::Parse1DMatrix(src, 3, &reach.start.x);
      Lexer::Parse1DMatrix(src, 3, &reach.end.x);
      reach.edgeNum = Lexer::ParseInt(src);
      reach.travelTime = Lexer::ParseInt(src);
      if ( reach.travelType == 4096 )
      {
        v7 = (idReachability_Special *)Memory::Allocate(0x60u);
        v12 = 0;
        if ( v7 )
          idReachability_Special::idReachability_Special(v7);
        else
          v8 = 0;
        v12 = -1;
        v6 = v8;
        Reachability_Special_Read(src, v8);
      }
      else
      {
        v6 = (idReachability_Special *)Memory::Allocate(0x34u);
      }
      v9 = areaNuma-- == 1;
      v6->travelType = reach.travelType;
      v6->toAreaNum = reach.toAreaNum;
      v6->start = reach.start;
      v6->end = reach.end;
      v6->edgeNum = reach.edgeNum;
      v6->travelTime = reach.travelTime;
      v6->fromAreaNum = areaNum;
      v6->next = v5->reach;
      v5->reach = v6;
    }
    while ( !v9 );
  }
  Lexer::ExpectTokenString(src, "}");
  return 1;
}

// FUNC: private: bool __thiscall idAASFileLocal::ParseAreas(class Lexer &,int)
char __thiscall idAASFileLocal::ParseAreas(idAASFileLocal *this, Lexer *src, int idx)
{
  idAASFileLocal *v4; // ebx
  idList<aasArea_s> *p_areas; // esi
  int i; // ebp
  int size; // ecx
  aasArea_s area; // [esp+10h] [ebp-4Ch] BYREF
  Lexer *srca; // [esp+60h] [ebp+4h]

  v4 = this;
  p_areas = &this->areas;
  srca = (Lexer *)Lexer::ParseInt(src);
  idList<aasArea_s>::Resize(p_areas, (int)srca);
  if ( !Lexer::ExpectTokenString(src, "{") )
    return 0;
  for ( i = 0; i < (int)srca; ++i )
  {
    Lexer::ParseInt(src);
    Lexer::ExpectTokenString(src, "(");
    area.flags = Lexer::ParseInt(src);
    area.contents = Lexer::ParseInt(src);
    area.firstFace = Lexer::ParseInt(src);
    area.numFaces = Lexer::ParseInt(src);
    area.cluster = Lexer::ParseInt(src);
    area.clusterAreaNum = Lexer::ParseInt(src);
    if ( idStr::Cmp(v4->version.data, "1.07") )
    {
      area.numFeatures = Lexer::ParseInt(src);
      area.firstFeature = Lexer::ParseInt(src);
    }
    else
    {
      area.numFeatures = 0;
      area.firstFeature = 0;
    }
    area.firstMarker = 0;
    Lexer::ExpectTokenString(src, ")");
    if ( !p_areas->list )
      idList<aasArea_s>::Resize(p_areas, p_areas->granularity);
    size = p_areas->size;
    if ( p_areas->num == size )
    {
      if ( !p_areas->granularity )
        p_areas->granularity = 16;
      idList<aasArea_s>::Resize(
        p_areas,
        p_areas->granularity + size - (p_areas->granularity + size) % p_areas->granularity);
      v4 = this;
    }
    aasArea_s::operator=(&p_areas->list[p_areas->num].numFaces, (int)&area);
    ++p_areas->num;
    idAASFileLocal::ParseReachabilities(v4, src, i);
  }
  if ( !Lexer::ExpectTokenString(src, "}") )
    return 0;
  if ( srca || idx == 11 )
  {
    v4->LinkReversedReachability(v4);
    return 1;
  }
  else
  {
    v4->isDummy[idx] = 1;
    return 1;
  }
}

// FUNC: public: virtual bool __thiscall idAASFileLocal::Load(class idStr const &,unsigned int)
char __thiscall idAASFileLocal::Load(idAASFileLocal *this, const idStr *fileName, unsigned int mapFileCRC)
{
  Lexer *v4; // ebx
  bool v5; // cc
  int v6; // eax
  int v7; // eax
  unsigned int intvalue; // eax
  char v9; // al
  int v10; // eax
  char *data; // esi
  netadrtype_t type; // edi
  int v13; // ebx
  int v14; // eax
  idAutoPtr<Lexer> lexer; // [esp+10h] [ebp-64h] BYREF
  int len; // [esp+14h] [ebp-60h]
  idToken token; // [esp+18h] [ebp-5Ch] BYREF
  int v19; // [esp+70h] [ebp-4h]

  v4 = LexerFactory::MakeLexer(156);
  lexer.mPtr = v4;
  token.floatvalue = 0.0;
  v19 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  len = fileName->len;
  v5 = len + 1 <= this->name.alloced;
  LOBYTE(v19) = 1;
  if ( !v5 )
    idStr::ReAllocate(&this->name, len + 1, 0);
  v6 = len;
  qmemcpy(this->name.data, fileName->data, len);
  this->name.data[len] = 0;
  this->name.len = v6;
  this->crc = mapFileCRC;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "[Load AAS]\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "loading %s\n",
    this->name.data);
  if ( !Lexer::LoadFile(v4, this->name.data, 0) )
    goto LABEL_13;
  if ( !Lexer::ExpectTokenString(v4, "DewmAAS") )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "Not an AAS file: '%s'",
      this->name.data);
    goto LABEL_13;
  }
  console->SetAASFileOutOfDate(console, 0);
  if ( !Lexer::ReadToken(v4, &token) || idStr::Cmp(token.data, "1.08") )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "AAS file '%s' has version %s instead of %s",
      this->name.data,
      token.data,
      "1.08");
  len = token.len;
  if ( token.len + 1 > this->version.alloced )
    idStr::ReAllocate(&this->version, token.len + 1, 0);
  v7 = len;
  qmemcpy(this->version.data, token.data, len);
  this->version.data[len] = 0;
  this->version.len = v7;
  if ( !Lexer::ExpectTokenType(v4, 3, 1, &token) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "AAS file '%s' has no map file CRC",
      this->name.data);
LABEL_13:
    LOBYTE(v19) = 0;
    idStr::FreeData(&token);
    v19 = -1;
    if ( v4 )
    {
      Lexer::~Lexer(v4);
      Memory::Free(v4);
    }
    return 0;
  }
  if ( token.type == 3 )
  {
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    intvalue = token.intvalue;
  }
  else
  {
    intvalue = 0;
  }
  if ( mapFileCRC && intvalue != mapFileCRC )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "AAS file '%s' is out of date",
      this->name.data);
    console->SetAASFileOutOfDate(console, 1);
    if ( !cvarSystem->GetCVarBool(cvarSystem, "ai_allowOldAAS") )
      goto LABEL_65;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "Using out of date AAS file anyway.");
  }
  this->Clear(this);
  if ( !Lexer::ReadToken(v4, &token) )
  {
LABEL_55:
    this->FinishAreas(this);
    if ( !this->IsDummyFile(this, mapFileCRC) )
    {
      if ( !this->vertices.num || !this->edges.num || !this->faces.num )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "error loading %s (invalid data).\n",
          fileName->data);
        goto LABEL_65;
      }
      v10 = idAASFileLocal::MaxTreeDepth(this);
      if ( v10 > 128 )
        Lexer::Error(v4, "idAASFileLocal::Load: tree depth = %d", v10);
      data = fileName->data;
      type = common.type;
      v13 = *(_DWORD *)common.type;
      v14 = idAASFileLocal::MemorySize(this);
      (*(void (**)(netadrtype_t, const char *, ...))(v13 + 124))(type, "done loading %s (size %d).\n", data, v14);
    }
    LOBYTE(v19) = 0;
    idStr::FreeData(&token);
    v19 = -1;
    idAutoPtr<Lexer>::~idAutoPtr<Lexer>(&lexer);
    return 1;
  }
  while ( !idStr::Cmp(token.data, "settings") )
  {
    v9 = idAASSettings::FromParser(&this->settings, v4);
LABEL_53:
    if ( !v9 )
      goto LABEL_65;
    if ( !Lexer::ReadToken(v4, &token) )
      goto LABEL_55;
  }
  if ( !idStr::Cmp(token.data, "planes") )
  {
    v9 = idAASFileLocal::ParsePlanes(this, v4, 0);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "vertices") )
  {
    v9 = idAASFileLocal::ParseVertices(this, v4, 1);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "edges") )
  {
    v9 = idAASFileLocal::ParseEdges(this, v4, 2);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "edgeIndex") )
  {
    v9 = idAASFileLocal::ParseIndex(this, v4, (int)&this->edgeIndex, 3);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "faces") )
  {
    v9 = idAASFileLocal::ParseFaces(this, v4, 4);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "faceIndex") )
  {
    v9 = idAASFileLocal::ParseIndex(this, v4, (int)&this->faceIndex, 5);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "areas") )
  {
    v9 = idAASFileLocal::ParseAreas(this, v4, 6);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "nodes") )
  {
    v9 = idAASFileLocal::ParseNodes(this, v4, 7);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "portals") )
  {
    v9 = idAASFileLocal::ParsePortals(this, v4, 8);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "portalIndex") )
  {
    v9 = idAASFileLocal::ParseIndex(this, v4, (int)&this->portalIndex, 9);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "clusters") )
  {
    v9 = idAASFileLocal::ParseClusters(this, v4, 10);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "featureIndex") )
  {
    v9 = idAASFileLocal::ParseIndex(this, v4, (int)&this->featureIndex, 11);
    goto LABEL_53;
  }
  if ( !idStr::Cmp(token.data, "features") )
  {
    v9 = idAASFileLocal::ParseFeatures(this, v4);
    goto LABEL_53;
  }
  Lexer::Error(v4, "idAASFileLocal::Load: bad token \"%s\"", token.data);
LABEL_65:
  LOBYTE(v19) = 0;
  idStr::FreeData(&token);
  v19 = -1;
  idAutoPtr<Lexer>::~idAutoPtr<Lexer>(&lexer);
  return 0;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::Init(void)
void __thiscall idAASFileLocal::Init(idAASFileLocal *this)
{
  bool v2; // zf
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  aasEdge_s *list; // ecx
  int size; // ecx
  int num; // ebx
  int v9; // ecx
  aasEdge_s *v10; // edi
  int j; // eax
  aasEdge_s *v12; // ecx
  int v13; // ecx
  aasEdge_s *v14; // edx
  int v15; // eax
  aasFace_s *v16; // eax
  int v17; // ecx
  _DWORD *v18; // eax
  aasFace_s *v19; // edx
  int v20; // ecx
  int v21; // ebx
  int v22; // eax
  aasFace_s *v23; // edi
  aasFace_s *v24; // eax
  int v25; // ecx
  int v26; // eax
  aasFace_s *v27; // ebx
  aasFace_s *v28; // eax
  idList<aasArea_s> *p_areas; // edi
  int v30; // ecx
  int v31; // eax
  aasNode_s *v32; // eax
  int v33; // ecx
  _DWORD *v34; // eax
  aasNode_s *v35; // edx
  int v36; // ecx
  int v37; // ebx
  int v38; // ecx
  aasNode_s *v39; // edi
  aasNode_s *v40; // eax
  int v41; // ecx
  int v42; // eax
  aasNode_s *v43; // ebx
  aasNode_s *v44; // edx
  int node; // [esp+10h] [ebp-68h]
  aasArea_s area; // [esp+2Ch] [ebp-4Ch] BYREF

  memset(&area.ceiling, 0, 32);
  v2 = this->edges.list == 0;
  area.numFaces = 0;
  area.firstFace = 0;
  LOWORD(node) = 0;
  if ( v2 )
  {
    granularity = this->edges.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->edges.size )
      {
        v4 = granularity < this->edges.num;
        this->edges.size = granularity;
        if ( v4 )
          this->edges.num = granularity;
        this->edges.list = (aasEdge_s *)Memory::Allocate(8 * granularity);
        for ( i = 0; i < this->edges.num; ++i )
        {
          list = this->edges.list;
          list[i].vertexNum[0] = *(_DWORD *)(8 * i);
          list[i].vertexNum[1] = *(_DWORD *)(8 * i + 4);
        }
      }
    }
    else
    {
      this->edges.list = 0;
      this->edges.num = 0;
      this->edges.size = 0;
    }
  }
  size = this->edges.size;
  num = this->edges.num;
  if ( num == size )
  {
    if ( !this->edges.granularity )
      this->edges.granularity = 16;
    v9 = this->edges.granularity + size - (this->edges.granularity + size) % this->edges.granularity;
    if ( v9 > 0 )
    {
      if ( v9 != this->edges.size )
      {
        v10 = this->edges.list;
        this->edges.size = v9;
        if ( v9 < num )
          this->edges.num = v9;
        this->edges.list = (aasEdge_s *)Memory::Allocate(8 * v9);
        for ( j = 0; j < this->edges.num; ++j )
        {
          v12 = this->edges.list;
          v12[j].vertexNum[0] = v10[j].vertexNum[0];
          v12[j].vertexNum[1] = v10[j].vertexNum[1];
        }
        if ( v10 )
          Memory::Free(v10);
      }
    }
    else
    {
      if ( this->edges.list )
        Memory::Free(this->edges.list);
      this->edges.list = 0;
      this->edges.num = 0;
      this->edges.size = 0;
    }
  }
  v13 = this->edges.num;
  v14 = this->edges.list;
  v14[v13].vertexNum[0] = 0;
  v14[v13].vertexNum[1] = 0;
  ++this->edges.num;
  if ( !this->faces.list )
  {
    v15 = this->faces.granularity;
    if ( v15 > 0 )
    {
      if ( v15 != this->faces.size )
      {
        v4 = v15 < this->faces.num;
        this->faces.size = v15;
        if ( v4 )
          this->faces.num = v15;
        v16 = (aasFace_s *)Memory::Allocate(16 * v15);
        v17 = 0;
        v4 = this->faces.num <= 0;
        this->faces.list = v16;
        if ( !v4 )
        {
          v18 = 0;
          do
          {
            v19 = (aasFace_s *)((char *)v18 + (unsigned int)this->faces.list);
            *(_DWORD *)&v19->planeNum = *v18;
            v19->numEdges = v18[1];
            v19->firstEdge = v18[2];
            ++v17;
            *(_DWORD *)v19->areas = v18[3];
            v18 += 4;
          }
          while ( v17 < this->faces.num );
        }
      }
    }
    else
    {
      this->faces.list = 0;
      this->faces.num = 0;
      this->faces.size = 0;
    }
  }
  v20 = this->faces.size;
  v21 = this->faces.num;
  if ( v21 == v20 )
  {
    if ( !this->faces.granularity )
      this->faces.granularity = 16;
    v22 = this->faces.granularity + v20 - (this->faces.granularity + v20) % this->faces.granularity;
    if ( v22 > 0 )
    {
      if ( v22 != this->faces.size )
      {
        v23 = this->faces.list;
        this->faces.size = v22;
        if ( v22 < v21 )
          this->faces.num = v22;
        v24 = (aasFace_s *)Memory::Allocate(16 * v22);
        v25 = 0;
        v4 = this->faces.num <= 0;
        this->faces.list = v24;
        if ( !v4 )
        {
          v26 = 0;
          do
          {
            v27 = &this->faces.list[v26];
            *(_DWORD *)&v27->planeNum = *(_DWORD *)&v23[v26].planeNum;
            v27->numEdges = v23[v26].numEdges;
            v27->firstEdge = v23[v26].firstEdge;
            ++v25;
            *(_DWORD *)v27->areas = *(_DWORD *)v23[v26++].areas;
          }
          while ( v25 < this->faces.num );
        }
        if ( v23 )
          Memory::Free(v23);
      }
    }
    else
    {
      if ( this->faces.list )
        Memory::Free(this->faces.list);
      this->faces.list = 0;
      this->faces.num = 0;
      this->faces.size = 0;
    }
  }
  v28 = &this->faces.list[this->faces.num];
  p_areas = &this->areas;
  *(_QWORD *)&v28->planeNum = 0i64;
  *(_QWORD *)&v28->firstEdge = 0i64;
  ++this->faces.num;
  if ( !this->areas.list )
    idList<aasArea_s>::Resize(&this->areas, this->areas.granularity);
  v30 = this->areas.size;
  if ( p_areas->num == v30 )
  {
    if ( !this->areas.granularity )
      this->areas.granularity = 16;
    idList<aasArea_s>::Resize(
      &this->areas,
      this->areas.granularity + v30 - (this->areas.granularity + v30) % this->areas.granularity);
  }
  aasArea_s::operator=(&this->areas.list[p_areas->num].numFaces, (int)&area);
  ++p_areas->num;
  if ( !this->nodes.list )
  {
    v31 = this->nodes.granularity;
    if ( v31 > 0 )
    {
      if ( v31 != this->nodes.size )
      {
        v4 = v31 < this->nodes.num;
        this->nodes.size = v31;
        if ( v4 )
          this->nodes.num = v31;
        v32 = (aasNode_s *)Memory::Allocate(12 * v31);
        v33 = 0;
        v4 = this->nodes.num <= 0;
        this->nodes.list = v32;
        if ( !v4 )
        {
          v34 = 0;
          do
          {
            v35 = (aasNode_s *)((char *)v34 + (unsigned int)this->nodes.list);
            *(_DWORD *)&v35->planeNum = *v34;
            v35->children[0] = v34[1];
            ++v33;
            v35->children[1] = v34[2];
            v34 += 3;
          }
          while ( v33 < this->nodes.num );
        }
      }
    }
    else
    {
      this->nodes.list = 0;
      this->nodes.num = 0;
      this->nodes.size = 0;
    }
  }
  v36 = this->nodes.size;
  v37 = this->nodes.num;
  if ( v37 == v36 )
  {
    if ( !this->nodes.granularity )
      this->nodes.granularity = 16;
    v38 = this->nodes.granularity + v36 - (this->nodes.granularity + v36) % this->nodes.granularity;
    if ( v38 > 0 )
    {
      if ( v38 != this->nodes.size )
      {
        v39 = this->nodes.list;
        this->nodes.size = v38;
        if ( v38 < v37 )
          this->nodes.num = v38;
        v40 = (aasNode_s *)Memory::Allocate(12 * v38);
        v41 = 0;
        v4 = this->nodes.num <= 0;
        this->nodes.list = v40;
        if ( !v4 )
        {
          v42 = 0;
          do
          {
            v43 = &this->nodes.list[v42];
            *(_DWORD *)&v43->planeNum = *(_DWORD *)&v39[v42].planeNum;
            v43->children[0] = v39[v42].children[0];
            ++v41;
            v43->children[1] = v39[v42++].children[1];
          }
          while ( v41 < this->nodes.num );
        }
        if ( v39 )
          Memory::Free(v39);
      }
    }
    else
    {
      if ( this->nodes.list )
        Memory::Free(this->nodes.list);
      this->nodes.list = 0;
      this->nodes.num = 0;
      this->nodes.size = 0;
    }
  }
  v44 = &this->nodes.list[this->nodes.num];
  *(_DWORD *)&v44->planeNum = node;
  v44->children[0] = 0;
  v44->children[1] = 0;
  ++this->nodes.num;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::SetSizes(struct sizeEstimate_s)
void __thiscall idAASFileLocal::SetSizes(idAASFileLocal *this, sizeEstimate_s size)
{
  int v3; // eax
  bool v4; // cc
  aasEdge_s *list; // edi
  int i; // eax
  aasEdge_s *v7; // edx
  int *v8; // edi
  int j; // eax
  aasFace_s *v10; // ebx
  aasFace_s *v11; // eax
  int v12; // ecx
  int v13; // eax
  aasFace_s *v14; // edx
  aasFace_s *v15; // ebx
  int *v16; // ebx
  int k; // eax
  aasNode_s *v18; // edi
  aasNode_s *v19; // eax
  int v20; // ecx
  int v21; // eax
  aasNode_s *v22; // ebx
  int *v23; // edi
  int m; // eax
  aasFeature_s *v25; // edi
  aasFeature_s *v26; // eax
  int v27; // ecx
  int v28; // eax
  aasFeature_s *v29; // ebx
  aasFace_s *v30; // [esp+10h] [ebp-4h]

  idList<idPlane>::Resize(&this->planeList, size.numNodes / 2, 1024);
  idList<idVec3>::Resize(&this->vertices, size.numEdgeIndexes / 3, 1024);
  v3 = size.numEdgeIndexes / 2;
  this->edges.granularity = 1024;
  if ( size.numEdgeIndexes / 2 > 0 )
  {
    v4 = v3 < this->edges.num;
    list = this->edges.list;
    this->edges.size = v3;
    if ( v4 )
      this->edges.num = v3;
    this->edges.list = (aasEdge_s *)Memory::Allocate(8 * v3);
    for ( i = 0; i < this->edges.num; ++i )
    {
      v7 = this->edges.list;
      v7[i].vertexNum[0] = list[i].vertexNum[0];
      v7[i].vertexNum[1] = list[i].vertexNum[1];
    }
    if ( list )
      Memory::Free(list);
  }
  else
  {
    if ( this->edges.list )
      Memory::Free(this->edges.list);
    this->edges.list = 0;
    this->edges.num = 0;
    this->edges.size = 0;
  }
  this->edgeIndex.granularity = 4096;
  if ( size.numEdgeIndexes > 0 )
  {
    v4 = size.numEdgeIndexes < this->edgeIndex.num;
    v8 = this->edgeIndex.list;
    this->edgeIndex.size = size.numEdgeIndexes;
    if ( v4 )
      this->edgeIndex.num = size.numEdgeIndexes;
    this->edgeIndex.list = (int *)Memory::Allocate(4 * size.numEdgeIndexes);
    for ( j = 0; j < this->edgeIndex.num; ++j )
      this->edgeIndex.list[j] = v8[j];
    if ( v8 )
      Memory::Free(v8);
  }
  else
  {
    if ( this->edgeIndex.list )
      Memory::Free(this->edgeIndex.list);
    this->edgeIndex.list = 0;
    this->edgeIndex.num = 0;
    this->edgeIndex.size = 0;
  }
  this->faces.granularity = 1024;
  if ( size.numFaceIndexes > 0 )
  {
    v4 = size.numFaceIndexes < this->faces.num;
    v10 = this->faces.list;
    v30 = v10;
    this->faces.size = size.numFaceIndexes;
    if ( v4 )
      this->faces.num = size.numFaceIndexes;
    v11 = (aasFace_s *)Memory::Allocate(16 * size.numFaceIndexes);
    v12 = 0;
    v4 = this->faces.num <= 0;
    this->faces.list = v11;
    if ( !v4 )
    {
      v13 = 0;
      do
      {
        v14 = &v10[v13];
        v15 = &this->faces.list[v13];
        *(_DWORD *)&v15->planeNum = *(_DWORD *)&v14->planeNum;
        v15->numEdges = v14->numEdges;
        v15->firstEdge = v14->firstEdge;
        *(_DWORD *)v15->areas = *(_DWORD *)v14->areas;
        v10 = v30;
        ++v12;
        ++v13;
      }
      while ( v12 < this->faces.num );
    }
    if ( v10 )
      Memory::Free(v10);
  }
  else
  {
    if ( this->faces.list )
      Memory::Free(this->faces.list);
    this->faces.list = 0;
    this->faces.num = 0;
    this->faces.size = 0;
  }
  this->faceIndex.granularity = 4096;
  if ( size.numFaceIndexes > 0 )
  {
    v4 = size.numFaceIndexes < this->faceIndex.num;
    v16 = this->faceIndex.list;
    this->faceIndex.size = size.numFaceIndexes;
    if ( v4 )
      this->faceIndex.num = size.numFaceIndexes;
    this->faceIndex.list = (int *)Memory::Allocate(4 * size.numFaceIndexes);
    for ( k = 0; k < this->faceIndex.num; ++k )
      this->faceIndex.list[k] = v16[k];
    if ( v16 )
      Memory::Free(v16);
  }
  else
  {
    if ( this->faceIndex.list )
      Memory::Free(this->faceIndex.list);
    this->faceIndex.list = 0;
    this->faceIndex.num = 0;
    this->faceIndex.size = 0;
  }
  idList<aasArea_s>::Resize(&this->areas, size.numAreas, 1024);
  this->nodes.granularity = 1024;
  if ( size.numNodes > 0 )
  {
    v4 = size.numNodes < this->nodes.num;
    v18 = this->nodes.list;
    this->nodes.size = size.numNodes;
    if ( v4 )
      this->nodes.num = size.numNodes;
    v19 = (aasNode_s *)Memory::Allocate(12 * size.numNodes);
    v20 = 0;
    v4 = this->nodes.num <= 0;
    this->nodes.list = v19;
    if ( !v4 )
    {
      v21 = 0;
      do
      {
        v22 = &this->nodes.list[v21];
        *(_DWORD *)&v22->planeNum = *(_DWORD *)&v18[v21].planeNum;
        v22->children[0] = v18[v21].children[0];
        ++v20;
        v22->children[1] = v18[v21++].children[1];
      }
      while ( v20 < this->nodes.num );
    }
    if ( v18 )
      Memory::Free(v18);
  }
  else
  {
    if ( this->nodes.list )
      Memory::Free(this->nodes.list);
    this->nodes.list = 0;
    this->nodes.num = 0;
    this->nodes.size = 0;
  }
  v23 = this->featureIndex.list;
  v4 = this->featureIndex.num <= 2048;
  this->featureIndex.granularity = 2048;
  this->featureIndex.size = 2048;
  if ( !v4 )
    this->featureIndex.num = 2048;
  this->featureIndex.list = (int *)Memory::Allocate(0x2000u);
  for ( m = 0; m < this->featureIndex.num; ++m )
    this->featureIndex.list[m] = v23[m];
  if ( v23 )
    Memory::Free(v23);
  v4 = this->features.num <= 2048;
  v25 = this->features.list;
  this->features.granularity = 2048;
  this->features.size = 2048;
  if ( !v4 )
    this->features.num = 2048;
  v26 = (aasFeature_s *)Memory::Allocate(0x6000u);
  v27 = 0;
  v4 = this->features.num <= 0;
  this->features.list = v26;
  if ( !v4 )
  {
    v28 = 0;
    do
    {
      v29 = &this->features.list[v28];
      *(_DWORD *)&v29->x = *(_DWORD *)&v25[v28].x;
      *(_DWORD *)&v29->z = *(_DWORD *)&v25[v28].z;
      ++v27;
      *(_DWORD *)&v29->normalx = *(_DWORD *)&v25[v28++].normalx;
    }
    while ( v27 < this->features.num );
  }
  if ( v25 )
    Memory::Free(v25);
}

// FUNC: public: __thiscall idAASFileLocal::idAASFileLocal(void)
void __thiscall idAASFileLocal::idAASFileLocal(idAASFileLocal *this)
{
  idPlaneSet *p_planeList; // edi
  idPlane *list; // eax
  int num; // eax
  int v5; // ebp
  idPlane *v6; // eax
  idPlane *v7; // eax
  bool v8; // cc
  int v9; // eax
  _DWORD *p_a; // edx
  idVec3 *v11; // eax
  int v12; // ecx
  int v13; // edi
  idVec3 *v14; // eax
  idVec3 *v15; // ebp
  int v16; // edx
  _DWORD *p_z; // ecx
  _DWORD *v18; // eax
  aasEdge_s *v19; // edi
  int v20; // ecx
  int v21; // eax
  int i; // eax
  aasEdge_s *v23; // ecx
  int *v24; // edi
  int v25; // ecx
  int v26; // eax
  int j; // eax
  aasFace_s *v28; // edi
  int v29; // ecx
  int v30; // eax
  aasFace_s *v31; // eax
  int v32; // ecx
  int v33; // eax
  aasFace_s *v34; // edx
  aasFace_s *v35; // edi
  int *v36; // edi
  int v37; // ecx
  int v38; // eax
  int k; // eax
  aasArea_s *v40; // eax
  int v41; // eax
  int v42; // edi
  aasArea_s *v43; // eax
  aasArea_s *v44; // ebp
  int v45; // ebp
  int v46; // edi
  aasNode_s *v47; // edi
  int v48; // ecx
  int v49; // eax
  aasNode_s *v50; // eax
  int v51; // ecx
  int v52; // eax
  aasNode_s *v53; // edx
  aasNode_s *v54; // edi
  aasPortal_s *v55; // edi
  int v56; // ecx
  int v57; // eax
  aasPortal_s *v58; // eax
  int v59; // ecx
  int v60; // eax
  aasPortal_s *v61; // edx
  aasPortal_s *v62; // edi
  int *v63; // edi
  int v64; // ecx
  int v65; // eax
  int m; // eax
  aasCluster_s *v67; // edi
  int v68; // ecx
  int v69; // eax
  aasCluster_s *v70; // eax
  int v71; // ecx
  int v72; // eax
  aasCluster_s *v73; // edx
  aasCluster_s *v74; // edi
  idPlane *ptr; // [esp+10h] [ebp-18h]
  aasArea_s *ptra; // [esp+10h] [ebp-18h]
  idPlane *v77; // [esp+14h] [ebp-14h]
  char *v78; // [esp+14h] [ebp-14h]
  idVec3 *v79; // [esp+14h] [ebp-14h]
  aasFace_s *v80; // [esp+14h] [ebp-14h]
  aasNode_s *v81; // [esp+14h] [ebp-14h]
  aasPortal_s *v82; // [esp+14h] [ebp-14h]
  aasCluster_s *v83; // [esp+14h] [ebp-14h]

  this->__vftable = (idAASFileLocal_vtbl *)&idAASFileLocal::`vftable';
  this->name.len = 0;
  this->name.alloced = 20;
  this->name.data = this->name.baseBuffer;
  this->name.baseBuffer[0] = 0;
  this->version.len = 0;
  this->version.alloced = 20;
  this->version.data = this->version.baseBuffer;
  this->version.baseBuffer[0] = 0;
  p_planeList = &this->planeList;
  idPlaneSet::idPlaneSet(&this->planeList);
  this->vertices.granularity = 16;
  this->vertices.list = 0;
  this->vertices.num = 0;
  this->vertices.size = 0;
  this->edges.granularity = 16;
  this->edges.list = 0;
  this->edges.num = 0;
  this->edges.size = 0;
  this->edgeIndex.granularity = 16;
  this->edgeIndex.list = 0;
  this->edgeIndex.num = 0;
  this->edgeIndex.size = 0;
  this->faces.granularity = 16;
  this->faces.list = 0;
  this->faces.num = 0;
  this->faces.size = 0;
  this->faceIndex.granularity = 16;
  this->faceIndex.list = 0;
  this->faceIndex.num = 0;
  this->faceIndex.size = 0;
  this->areas.granularity = 16;
  this->areas.list = 0;
  this->areas.num = 0;
  this->areas.size = 0;
  this->nodes.granularity = 16;
  this->nodes.list = 0;
  this->nodes.num = 0;
  this->nodes.size = 0;
  this->portals.granularity = 16;
  this->portals.list = 0;
  this->portals.num = 0;
  this->portals.size = 0;
  this->portalIndex.granularity = 16;
  this->portalIndex.list = 0;
  this->portalIndex.num = 0;
  this->portalIndex.size = 0;
  this->clusters.granularity = 16;
  this->clusters.list = 0;
  this->clusters.num = 0;
  this->clusters.size = 0;
  this->featureIndex.granularity = 16;
  this->featureIndex.list = 0;
  this->featureIndex.num = 0;
  this->featureIndex.size = 0;
  this->features.granularity = 16;
  this->features.list = 0;
  this->features.num = 0;
  this->features.size = 0;
  idAASSettings::idAASSettings(&this->settings);
  list = p_planeList->list;
  p_planeList->granularity = 4096;
  ptr = list;
  if ( list )
  {
    num = p_planeList->num;
    v5 = p_planeList->num + 4095 - (p_planeList->num + 4095) % 4096;
    if ( v5 != p_planeList->size )
    {
      if ( v5 > 0 )
      {
        p_planeList->size = v5;
        if ( v5 < num )
          p_planeList->num = v5;
        v6 = (idPlane *)Memory::Allocate(16 * v5);
        v77 = v6;
        if ( v6 )
        {
          `vector constructor iterator'(v6, 0x10u, v5, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
          v7 = v77;
        }
        else
        {
          v7 = 0;
        }
        v8 = p_planeList->num <= 0;
        p_planeList->list = v7;
        v78 = 0;
        if ( !v8 )
        {
          v9 = 0;
          do
          {
            p_a = (_DWORD *)&p_planeList->list[v9].a;
            *p_a = LODWORD(ptr[v9].a);
            p_a[1] = LODWORD(ptr[v9].b);
            p_a[2] = LODWORD(ptr[v9].c);
            p_a[3] = LODWORD(ptr[v9++].d);
            ++v78;
          }
          while ( (int)v78 < p_planeList->num );
        }
        if ( ptr )
          Memory::Free(ptr);
      }
      else
      {
        Memory::Free(ptr);
        p_planeList->list = 0;
        p_planeList->num = 0;
        p_planeList->size = 0;
      }
    }
  }
  v11 = this->vertices.list;
  this->vertices.granularity = 4096;
  v79 = v11;
  if ( v11 )
  {
    v12 = this->vertices.num;
    v13 = v12 + 4095 - (v12 + 4095) % 4096;
    if ( v13 != this->vertices.size )
    {
      if ( v13 > 0 )
      {
        this->vertices.size = v13;
        if ( v13 < v12 )
          this->vertices.num = v13;
        v14 = (idVec3 *)Memory::Allocate(12 * v13);
        v15 = v14;
        if ( v14 )
          `vector constructor iterator'(v14, 0xCu, v13, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        else
          v15 = 0;
        v16 = 0;
        v8 = this->vertices.num <= 0;
        this->vertices.list = v15;
        if ( !v8 )
        {
          p_z = (_DWORD *)&v79->z;
          do
          {
            v18 = (_DWORD *)((char *)&this->vertices.list->x + (unsigned int)p_z - 8 - (_DWORD)v79);
            ++v16;
            *v18 = *(p_z - 2);
            v18[1] = *(p_z - 1);
            v18[2] = *p_z;
            p_z += 3;
          }
          while ( v16 < this->vertices.num );
        }
        if ( v79 )
          Memory::Free(v79);
      }
      else
      {
        Memory::Free(v11);
        this->vertices.list = 0;
        this->vertices.num = 0;
        this->vertices.size = 0;
      }
    }
  }
  v19 = this->edges.list;
  this->edges.granularity = 4096;
  if ( v19 )
  {
    v20 = this->edges.num;
    v21 = v20 + 4095 - (v20 + 4095) % 4096;
    if ( v21 != this->edges.size )
    {
      if ( v21 > 0 )
      {
        this->edges.size = v21;
        if ( v21 < v20 )
          this->edges.num = v21;
        this->edges.list = (aasEdge_s *)Memory::Allocate(8 * v21);
        for ( i = 0; i < this->edges.num; ++i )
        {
          v23 = this->edges.list;
          v23[i].vertexNum[0] = v19[i].vertexNum[0];
          v23[i].vertexNum[1] = v19[i].vertexNum[1];
        }
        Memory::Free(v19);
      }
      else
      {
        Memory::Free(v19);
        this->edges.list = 0;
        this->edges.num = 0;
        this->edges.size = 0;
      }
    }
  }
  v24 = this->edgeIndex.list;
  this->edgeIndex.granularity = 4096;
  if ( v24 )
  {
    v25 = this->edgeIndex.num;
    v26 = v25 + 4095 - (v25 + 4095) % 4096;
    if ( v26 != this->edgeIndex.size )
    {
      if ( v26 > 0 )
      {
        this->edgeIndex.size = v26;
        if ( v26 < v25 )
          this->edgeIndex.num = v26;
        this->edgeIndex.list = (int *)Memory::Allocate(4 * v26);
        for ( j = 0; j < this->edgeIndex.num; ++j )
          this->edgeIndex.list[j] = v24[j];
        Memory::Free(v24);
      }
      else
      {
        Memory::Free(v24);
        this->edgeIndex.list = 0;
        this->edgeIndex.num = 0;
        this->edgeIndex.size = 0;
      }
    }
  }
  v28 = this->faces.list;
  this->faces.granularity = 1024;
  v80 = v28;
  if ( v28 )
  {
    v29 = this->faces.num;
    v30 = v29 + 1023 - (v29 + 1023) % 1024;
    if ( v30 != this->faces.size )
    {
      if ( v30 > 0 )
      {
        this->faces.size = v30;
        if ( v30 < v29 )
          this->faces.num = v30;
        v31 = (aasFace_s *)Memory::Allocate(16 * v30);
        v32 = 0;
        v8 = this->faces.num <= 0;
        this->faces.list = v31;
        if ( !v8 )
        {
          v33 = 0;
          do
          {
            v34 = &v28[v33];
            v35 = &this->faces.list[v33];
            *(_DWORD *)&v35->planeNum = *(_DWORD *)&v34->planeNum;
            v35->numEdges = v34->numEdges;
            v35->firstEdge = v34->firstEdge;
            *(_DWORD *)v35->areas = *(_DWORD *)v34->areas;
            v28 = v80;
            ++v32;
            ++v33;
          }
          while ( v32 < this->faces.num );
        }
        if ( v28 )
          Memory::Free(v28);
      }
      else
      {
        Memory::Free(v28);
        this->faces.list = 0;
        this->faces.num = 0;
        this->faces.size = 0;
      }
    }
  }
  v36 = this->faceIndex.list;
  this->faceIndex.granularity = 4096;
  if ( v36 )
  {
    v37 = this->faceIndex.num;
    v38 = v37 + 4095 - (v37 + 4095) % 4096;
    if ( v38 != this->faceIndex.size )
    {
      if ( v38 > 0 )
      {
        this->faceIndex.size = v38;
        if ( v38 < v37 )
          this->faceIndex.num = v38;
        this->faceIndex.list = (int *)Memory::Allocate(4 * v38);
        for ( k = 0; k < this->faceIndex.num; ++k )
          this->faceIndex.list[k] = v36[k];
        Memory::Free(v36);
      }
      else
      {
        Memory::Free(v36);
        this->faceIndex.list = 0;
        this->faceIndex.num = 0;
        this->faceIndex.size = 0;
      }
    }
  }
  v40 = this->areas.list;
  this->areas.granularity = 1024;
  ptra = v40;
  if ( v40 )
  {
    v41 = this->areas.num;
    v42 = v41 + 1023 - (v41 + 1023) % 1024;
    if ( v42 != this->areas.size )
    {
      if ( v42 > 0 )
      {
        this->areas.size = v42;
        if ( v42 < v41 )
          this->areas.num = v42;
        v43 = (aasArea_s *)Memory::Allocate(76 * v42);
        v44 = v43;
        if ( v43 )
          `vector constructor iterator'(v43, 0x4Cu, v42, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        else
          v44 = 0;
        this->areas.list = v44;
        v45 = 0;
        if ( this->areas.num > 0 )
        {
          v46 = 0;
          do
          {
            aasArea_s::operator=(&this->areas.list[v46].numFaces, (int)&ptra[v46]);
            ++v45;
            ++v46;
          }
          while ( v45 < this->areas.num );
        }
        if ( ptra )
          Memory::Free(ptra);
      }
      else
      {
        Memory::Free(ptra);
        this->areas.list = 0;
        this->areas.num = 0;
        this->areas.size = 0;
      }
    }
  }
  v47 = this->nodes.list;
  this->nodes.granularity = 1024;
  v81 = v47;
  if ( v47 )
  {
    v48 = this->nodes.num;
    v49 = v48 + 1023 - (v48 + 1023) % 1024;
    if ( v49 != this->nodes.size )
    {
      if ( v49 > 0 )
      {
        this->nodes.size = v49;
        if ( v49 < v48 )
          this->nodes.num = v49;
        v50 = (aasNode_s *)Memory::Allocate(12 * v49);
        v51 = 0;
        v8 = this->nodes.num <= 0;
        this->nodes.list = v50;
        if ( !v8 )
        {
          v52 = 0;
          do
          {
            v53 = &v47[v52];
            v54 = &this->nodes.list[v52];
            *(_DWORD *)&v54->planeNum = *(_DWORD *)&v53->planeNum;
            v54->children[0] = v53->children[0];
            v54->children[1] = v53->children[1];
            v47 = v81;
            ++v51;
            ++v52;
          }
          while ( v51 < this->nodes.num );
        }
        if ( v47 )
          Memory::Free(v47);
      }
      else
      {
        Memory::Free(v47);
        this->nodes.list = 0;
        this->nodes.num = 0;
        this->nodes.size = 0;
      }
    }
  }
  v55 = this->portals.list;
  this->portals.granularity = 1024;
  v82 = v55;
  if ( v55 )
  {
    v56 = this->portals.num;
    v57 = v56 + 1023 - (v56 + 1023) % 1024;
    if ( v57 != this->portals.size )
    {
      if ( v57 > 0 )
      {
        this->portals.size = v57;
        if ( v57 < v56 )
          this->portals.num = v57;
        v58 = (aasPortal_s *)Memory::Allocate(12 * v57);
        v59 = 0;
        v8 = this->portals.num <= 0;
        this->portals.list = v58;
        if ( !v8 )
        {
          v60 = 0;
          do
          {
            v61 = &v55[v60];
            v62 = &this->portals.list[v60];
            *(_DWORD *)&v62->areaNum = *(_DWORD *)&v61->areaNum;
            *(_DWORD *)&v62->clusters[1] = *(_DWORD *)&v61->clusters[1];
            *(_DWORD *)&v62->clusterAreaNum[1] = *(_DWORD *)&v61->clusterAreaNum[1];
            v55 = v82;
            ++v59;
            ++v60;
          }
          while ( v59 < this->portals.num );
        }
        if ( v55 )
          Memory::Free(v55);
      }
      else
      {
        Memory::Free(v55);
        this->portals.list = 0;
        this->portals.num = 0;
        this->portals.size = 0;
      }
    }
  }
  v63 = this->portalIndex.list;
  this->portalIndex.granularity = 4096;
  if ( v63 )
  {
    v64 = this->portalIndex.num;
    v65 = v64 + 4095 - (v64 + 4095) % 4096;
    if ( v65 != this->portalIndex.size )
    {
      if ( v65 > 0 )
      {
        this->portalIndex.size = v65;
        if ( v65 < v64 )
          this->portalIndex.num = v65;
        this->portalIndex.list = (int *)Memory::Allocate(4 * v65);
        for ( m = 0; m < this->portalIndex.num; ++m )
          this->portalIndex.list[m] = v63[m];
        Memory::Free(v63);
      }
      else
      {
        Memory::Free(v63);
        this->portalIndex.list = 0;
        this->portalIndex.num = 0;
        this->portalIndex.size = 0;
      }
    }
  }
  v67 = this->clusters.list;
  this->clusters.granularity = 1024;
  v83 = v67;
  if ( v67 )
  {
    v68 = this->clusters.num;
    v69 = v68 + 1023 - (v68 + 1023) % 1024;
    if ( v69 != this->clusters.size )
    {
      if ( v69 > 0 )
      {
        this->clusters.size = v69;
        if ( v69 < v68 )
          this->clusters.num = v69;
        v70 = (aasCluster_s *)Memory::Allocate(16 * v69);
        v71 = 0;
        v8 = this->clusters.num <= 0;
        this->clusters.list = v70;
        if ( !v8 )
        {
          v72 = 0;
          do
          {
            v73 = &v67[v72];
            v74 = &this->clusters.list[v72];
            v74->numAreas = v73->numAreas;
            v74->numReachableAreas = v73->numReachableAreas;
            v74->numPortals = v73->numPortals;
            v74->firstPortal = v73->firstPortal;
            v67 = v83;
            ++v71;
            ++v72;
          }
          while ( v71 < this->clusters.num );
        }
        if ( v67 )
          Memory::Free(v67);
      }
      else
      {
        Memory::Free(v67);
        this->clusters.list = 0;
        this->clusters.num = 0;
        this->clusters.size = 0;
      }
    }
  }
  *(_DWORD *)this->isDummy = 0;
  *(_DWORD *)&this->isDummy[4] = 0;
  *(_WORD *)&this->isDummy[8] = 0;
  this->isDummy[10] = 0;
}
