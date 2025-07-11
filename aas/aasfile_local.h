
// FUNC: public: virtual class idAASSettings & __thiscall idAASFileLocal::GetSettings(void)
idAASSettings *__thiscall idAASFileLocal::GetSettings(idAASFileLocal *this)
{
  return &this->settings;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumPlanes(void)const
int __thiscall idAASFileLocal::GetNumPlanes(idAASFileLocal *this)
{
  return this->planeList.num;
}

// FUNC: public: virtual class idPlane & __thiscall idAASFileLocal::GetPlane(int)
idPlane *__thiscall idAASFileLocal::GetPlane(idAASFileLocal *this, int index)
{
  return &this->planeList.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumVertices(void)const
int __thiscall idAASFileLocal::GetNumVertices(idAASFileLocal *this)
{
  return this->vertices.num;
}

// FUNC: public: virtual class idVec3 & __thiscall idAASFileLocal::GetVertex(int)
idVec3 *__thiscall idAASFileLocal::GetVertex(idAASFileLocal *this, int index)
{
  return &this->vertices.list[index];
}

// FUNC: public: virtual class idJointQuat const * __thiscall idRenderModelMD5::GetDefaultPose(void)const
const idJointQuat *__thiscall idRenderModelMD5::GetDefaultPose(idRenderModelMD5 *this)
{
  return this->defaultPose;
}

// FUNC: public: virtual struct aasEdge_s & __thiscall idAASFileLocal::GetEdge(int)
aasEdge_s *__thiscall idAASFileLocal::GetEdge(idAASFileLocal *this, int index)
{
  return &this->edges.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendEdge(struct aasEdge_s &)
int __thiscall idAASFileLocal::AppendEdge(idAASFileLocal *this, aasEdge_s *edge)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  aasEdge_s *list; // ecx
  int num; // ebx
  int size; // eax
  int v9; // ecx
  aasEdge_s *v10; // edi
  int j; // eax
  aasEdge_s *v12; // ecx

  if ( !this->edges.list )
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
  num = this->edges.num;
  size = this->edges.size;
  if ( num == size )
  {
    if ( !this->edges.granularity )
      this->edges.granularity = 16;
    v9 = size + this->edges.granularity - (size + this->edges.granularity) % this->edges.granularity;
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
  this->edges.list[this->edges.num++] = *edge;
  return this->edges.num - 1;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumEdgeIndexes(void)const
int __thiscall idAASFileLocal::GetNumEdgeIndexes(idAASFileLocal *this)
{
  return this->edgeIndex.num;
}

// FUNC: public: virtual int & __thiscall idAASFileLocal::GetEdgeIndex(int)
int *__thiscall idAASFileLocal::GetEdgeIndex(idAASFileLocal *this, int index)
{
  return &this->edgeIndex.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendEdgeIndex(int &)
int __thiscall idAASFileLocal::AppendEdgeIndex(idAASFileLocal *this, int *edgeIdx)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  int *list; // edi
  int j; // eax

  if ( !this->edgeIndex.list )
  {
    granularity = this->edgeIndex.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->edgeIndex.size )
      {
        v4 = granularity < this->edgeIndex.num;
        this->edgeIndex.size = granularity;
        if ( v4 )
          this->edgeIndex.num = granularity;
        this->edgeIndex.list = (int *)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->edgeIndex.num; ++i )
          this->edgeIndex.list[i] = *(_DWORD *)(4 * i);
      }
    }
    else
    {
      this->edgeIndex.list = 0;
      this->edgeIndex.num = 0;
      this->edgeIndex.size = 0;
    }
  }
  num = this->edgeIndex.num;
  size = this->edgeIndex.size;
  if ( num == size )
  {
    if ( !this->edgeIndex.granularity )
      this->edgeIndex.granularity = 16;
    v8 = size + this->edgeIndex.granularity - (size + this->edgeIndex.granularity) % this->edgeIndex.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->edgeIndex.size )
      {
        list = this->edgeIndex.list;
        this->edgeIndex.size = v8;
        if ( v8 < num )
          this->edgeIndex.num = v8;
        this->edgeIndex.list = (int *)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->edgeIndex.num; ++j )
          this->edgeIndex.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->edgeIndex.list )
        Memory::Free(this->edgeIndex.list);
      this->edgeIndex.list = 0;
      this->edgeIndex.num = 0;
      this->edgeIndex.size = 0;
    }
  }
  this->edgeIndex.list[this->edgeIndex.num++] = *edgeIdx;
  return this->edgeIndex.num - 1;
}

// FUNC: public: int __thiscall rvServerScan::GetNumServers(void)
int __thiscall rvServerScan::GetNumServers(rvServerScan *this)
{
  return this->numServers;
}

// FUNC: public: virtual struct aasFace_s & __thiscall idAASFileLocal::GetFace(int)
aasFace_s *__thiscall idAASFileLocal::GetFace(idAASFileLocal *this, int index)
{
  return &this->faces.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendFace(struct aasFace_s &)
int __thiscall idAASFileLocal::AppendFace(idAASFileLocal *this, aasFace_s *face)
{
  int granularity; // eax
  bool v4; // cc
  aasFace_s *v5; // eax
  int v6; // ecx
  _DWORD *v7; // eax
  aasFace_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  aasFace_s *list; // edi
  aasFace_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  aasFace_s *v16; // ebx

  if ( !this->faces.list )
  {
    granularity = this->faces.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->faces.size )
      {
        v4 = granularity < this->faces.num;
        this->faces.size = granularity;
        if ( v4 )
          this->faces.num = granularity;
        v5 = (aasFace_s *)Memory::Allocate(16 * granularity);
        v6 = 0;
        v4 = this->faces.num <= 0;
        this->faces.list = v5;
        if ( !v4 )
        {
          v7 = 0;
          do
          {
            v8 = (aasFace_s *)((char *)v7 + (unsigned int)this->faces.list);
            *(_DWORD *)&v8->planeNum = *v7;
            v8->numEdges = v7[1];
            v8->firstEdge = v7[2];
            ++v6;
            *(_DWORD *)v8->areas = v7[3];
            v7 += 4;
          }
          while ( v6 < this->faces.num );
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
    v11 = this->faces.granularity + size - (this->faces.granularity + size) % this->faces.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->faces.size )
      {
        list = this->faces.list;
        this->faces.size = v11;
        if ( v11 < num )
          this->faces.num = v11;
        v13 = (aasFace_s *)Memory::Allocate(16 * v11);
        v14 = 0;
        v4 = this->faces.num <= 0;
        this->faces.list = v13;
        if ( !v4 )
        {
          v15 = 0;
          do
          {
            v16 = &this->faces.list[v15];
            *(_DWORD *)&v16->planeNum = *(_DWORD *)&list[v15].planeNum;
            v16->numEdges = list[v15].numEdges;
            v16->firstEdge = list[v15].firstEdge;
            ++v14;
            *(_DWORD *)v16->areas = *(_DWORD *)list[v15++].areas;
          }
          while ( v14 < this->faces.num );
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
  }
  this->faces.list[this->faces.num++] = *face;
  return this->faces.num - 1;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumFaceIndexes(void)const
int __thiscall idAASFileLocal::GetNumFaceIndexes(idAASFileLocal *this)
{
  return this->faceIndex.num;
}

// FUNC: public: virtual int & __thiscall idAASFileLocal::GetFaceIndex(int)
int *__thiscall idAASFileLocal::GetFaceIndex(idAASFileLocal *this, int index)
{
  return &this->faceIndex.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendFaceIndex(int &)
int __thiscall idAASFileLocal::AppendFaceIndex(idAASFileLocal *this, int *faceIdx)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  int *list; // edi
  int j; // eax

  if ( !this->faceIndex.list )
  {
    granularity = this->faceIndex.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->faceIndex.size )
      {
        v4 = granularity < this->faceIndex.num;
        this->faceIndex.size = granularity;
        if ( v4 )
          this->faceIndex.num = granularity;
        this->faceIndex.list = (int *)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->faceIndex.num; ++i )
          this->faceIndex.list[i] = *(_DWORD *)(4 * i);
      }
    }
    else
    {
      this->faceIndex.list = 0;
      this->faceIndex.num = 0;
      this->faceIndex.size = 0;
    }
  }
  num = this->faceIndex.num;
  size = this->faceIndex.size;
  if ( num == size )
  {
    if ( !this->faceIndex.granularity )
      this->faceIndex.granularity = 16;
    v8 = size + this->faceIndex.granularity - (size + this->faceIndex.granularity) % this->faceIndex.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->faceIndex.size )
      {
        list = this->faceIndex.list;
        this->faceIndex.size = v8;
        if ( v8 < num )
          this->faceIndex.num = v8;
        this->faceIndex.list = (int *)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->faceIndex.num; ++j )
          this->faceIndex.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->faceIndex.list )
        Memory::Free(this->faceIndex.list);
      this->faceIndex.list = 0;
      this->faceIndex.num = 0;
      this->faceIndex.size = 0;
    }
  }
  this->faceIndex.list[this->faceIndex.num++] = *faceIdx;
  return this->faceIndex.num - 1;
}

// FUNC: public: virtual struct aasArea_s & __thiscall idAASFileLocal::GetArea(int)
aasArea_s *__thiscall idAASFileLocal::GetArea(idAASFileLocal *this, int index)
{
  return &this->areas.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumNodes(void)const
int __thiscall idAASFileLocal::GetNumNodes(idAASFileLocal *this)
{
  return this->nodes.num;
}

// FUNC: public: virtual struct aasNode_s & __thiscall idAASFileLocal::GetNode(int)
aasNode_s *__thiscall idAASFileLocal::GetNode(idAASFileLocal *this, int index)
{
  return &this->nodes.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendNode(struct aasNode_s &)
int __thiscall idAASFileLocal::AppendNode(idAASFileLocal *this, aasNode_s *node)
{
  int granularity; // eax
  bool v4; // cc
  aasNode_s *v5; // eax
  int v6; // ecx
  _DWORD *v7; // eax
  aasNode_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  aasNode_s *list; // edi
  aasNode_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  aasNode_s *v16; // ebx

  if ( !this->nodes.list )
  {
    granularity = this->nodes.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->nodes.size )
      {
        v4 = granularity < this->nodes.num;
        this->nodes.size = granularity;
        if ( v4 )
          this->nodes.num = granularity;
        v5 = (aasNode_s *)Memory::Allocate(12 * granularity);
        v6 = 0;
        v4 = this->nodes.num <= 0;
        this->nodes.list = v5;
        if ( !v4 )
        {
          v7 = 0;
          do
          {
            v8 = (aasNode_s *)((char *)v7 + (unsigned int)this->nodes.list);
            *(_DWORD *)&v8->planeNum = *v7;
            v8->children[0] = v7[1];
            ++v6;
            v8->children[1] = v7[2];
            v7 += 3;
          }
          while ( v6 < this->nodes.num );
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
    v11 = this->nodes.granularity + size - (this->nodes.granularity + size) % this->nodes.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->nodes.size )
      {
        list = this->nodes.list;
        this->nodes.size = v11;
        if ( v11 < num )
          this->nodes.num = v11;
        v13 = (aasNode_s *)Memory::Allocate(12 * v11);
        v14 = 0;
        v4 = this->nodes.num <= 0;
        this->nodes.list = v13;
        if ( !v4 )
        {
          v15 = 0;
          do
          {
            v16 = &this->nodes.list[v15];
            *(_DWORD *)&v16->planeNum = *(_DWORD *)&list[v15].planeNum;
            v16->children[0] = list[v15].children[0];
            ++v14;
            v16->children[1] = list[v15++].children[1];
          }
          while ( v14 < this->nodes.num );
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
  }
  this->nodes.list[this->nodes.num++] = *node;
  return this->nodes.num - 1;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::SetNumNodes(int)
void __thiscall idAASFileLocal::SetNumNodes(idAASFileLocal *this, int num)
{
  bool v4; // cc
  aasNode_s *list; // ebx
  aasNode_s *v6; // eax
  int v7; // ecx
  int v8; // eax
  aasNode_s *v9; // edx
  aasNode_s *v10; // ebx
  int numa; // [esp+10h] [ebp+4h]

  if ( num > 0 )
  {
    if ( num != this->nodes.size )
    {
      v4 = num < this->nodes.num;
      list = this->nodes.list;
      numa = (int)list;
      this->nodes.size = num;
      if ( v4 )
        this->nodes.num = num;
      v6 = (aasNode_s *)Memory::Allocate(12 * num);
      v7 = 0;
      v4 = this->nodes.num <= 0;
      this->nodes.list = v6;
      if ( !v4 )
      {
        v8 = 0;
        do
        {
          v9 = &list[v8];
          v10 = &this->nodes.list[v8];
          *(_DWORD *)&v10->planeNum = *(_DWORD *)&v9->planeNum;
          v10->children[0] = v9->children[0];
          v10->children[1] = v9->children[1];
          list = (aasNode_s *)numa;
          ++v7;
          ++v8;
        }
        while ( v7 < this->nodes.num );
      }
      if ( list )
        Memory::Free(list);
    }
    this->nodes.num = num;
  }
  else
  {
    if ( this->nodes.list )
      Memory::Free(this->nodes.list);
    this->nodes.num = 0;
    this->nodes.num = num;
    this->nodes.list = 0;
    this->nodes.size = 0;
  }
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumPortals(void)const
int __thiscall idAASFileLocal::GetNumPortals(idAASFileLocal *this)
{
  return this->portals.num;
}

// FUNC: public: virtual struct aasPortal_s & __thiscall idAASFileLocal::GetPortal(int)
aasPortal_s *__thiscall idAASFileLocal::GetPortal(idAASFileLocal *this, int index)
{
  return &this->portals.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendPortal(struct aasPortal_s &)
int __thiscall idAASFileLocal::AppendPortal(idAASFileLocal *this, aasPortal_s *portal)
{
  int granularity; // eax
  bool v4; // cc
  aasPortal_s *v5; // eax
  int v6; // ecx
  _DWORD *v7; // eax
  aasPortal_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  aasPortal_s *list; // edi
  aasPortal_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  aasPortal_s *v16; // ebx

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
        list = this->portals.list;
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
            *(_DWORD *)&v16->areaNum = *(_DWORD *)&list[v15].areaNum;
            *(_DWORD *)&v16->clusters[1] = *(_DWORD *)&list[v15].clusters[1];
            ++v14;
            *(_DWORD *)&v16->clusterAreaNum[1] = *(_DWORD *)&list[v15++].clusterAreaNum[1];
          }
          while ( v14 < this->portals.num );
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
  }
  this->portals.list[this->portals.num++] = *portal;
  return this->portals.num - 1;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumPortalIndexes(void)const
int __thiscall idAASFileLocal::GetNumPortalIndexes(idAASFileLocal *this)
{
  return this->portalIndex.num;
}

// FUNC: public: virtual int & __thiscall idAASFileLocal::GetPortalIndex(int)
int *__thiscall idAASFileLocal::GetPortalIndex(idAASFileLocal *this, int index)
{
  return &this->portalIndex.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendPortalIndex(int &,int)
int __thiscall idAASFileLocal::AppendPortalIndex(idAASFileLocal *this, int *portalIdx, int clusterNum)
{
  int granularity; // eax
  bool v5; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v9; // ecx
  int *list; // edi
  int j; // eax

  ++this->clusters.list[clusterNum].numPortals;
  if ( !this->portalIndex.list )
  {
    granularity = this->portalIndex.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->portalIndex.size )
      {
        v5 = granularity < this->portalIndex.num;
        this->portalIndex.size = granularity;
        if ( v5 )
          this->portalIndex.num = granularity;
        this->portalIndex.list = (int *)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->portalIndex.num; ++i )
          this->portalIndex.list[i] = *(_DWORD *)(4 * i);
      }
    }
    else
    {
      this->portalIndex.list = 0;
      this->portalIndex.num = 0;
      this->portalIndex.size = 0;
    }
  }
  num = this->portalIndex.num;
  size = this->portalIndex.size;
  if ( num == size )
  {
    if ( !this->portalIndex.granularity )
      this->portalIndex.granularity = 16;
    v9 = size + this->portalIndex.granularity - (size + this->portalIndex.granularity) % this->portalIndex.granularity;
    if ( v9 > 0 )
    {
      if ( v9 != this->portalIndex.size )
      {
        list = this->portalIndex.list;
        this->portalIndex.size = v9;
        if ( v9 < num )
          this->portalIndex.num = v9;
        this->portalIndex.list = (int *)Memory::Allocate(4 * v9);
        for ( j = 0; j < this->portalIndex.num; ++j )
          this->portalIndex.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->portalIndex.list )
        Memory::Free(this->portalIndex.list);
      this->portalIndex.list = 0;
      this->portalIndex.num = 0;
      this->portalIndex.size = 0;
    }
  }
  this->portalIndex.list[this->portalIndex.num++] = *portalIdx;
  return this->portalIndex.num - 1;
}

// FUNC: public: virtual struct aasCluster_s & __thiscall idAASFileLocal::GetCluster(int)
aasCluster_s *__thiscall idAASFileLocal::GetCluster(idAASFileLocal *this, int index)
{
  return &this->clusters.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendCluster(struct aasCluster_s &)
int __thiscall idAASFileLocal::AppendCluster(idAASFileLocal *this, aasCluster_s *cluster)
{
  int granularity; // eax
  bool v4; // cc
  aasCluster_s *v5; // eax
  int v6; // ecx
  int *v7; // eax
  aasCluster_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  aasCluster_s *list; // edi
  aasCluster_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  aasCluster_s *v16; // ebx

  if ( !this->clusters.list )
  {
    granularity = this->clusters.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->clusters.size )
      {
        v4 = granularity < this->clusters.num;
        this->clusters.size = granularity;
        if ( v4 )
          this->clusters.num = granularity;
        v5 = (aasCluster_s *)Memory::Allocate(16 * granularity);
        v6 = 0;
        v4 = this->clusters.num <= 0;
        this->clusters.list = v5;
        if ( !v4 )
        {
          v7 = 0;
          do
          {
            v8 = (aasCluster_s *)((char *)v7 + (unsigned int)this->clusters.list);
            v8->numAreas = *v7;
            v8->numReachableAreas = v7[1];
            v8->numPortals = v7[2];
            ++v6;
            v8->firstPortal = v7[3];
            v7 += 4;
          }
          while ( v6 < this->clusters.num );
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
    v11 = this->clusters.granularity + size - (this->clusters.granularity + size) % this->clusters.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->clusters.size )
      {
        list = this->clusters.list;
        this->clusters.size = v11;
        if ( v11 < num )
          this->clusters.num = v11;
        v13 = (aasCluster_s *)Memory::Allocate(16 * v11);
        v14 = 0;
        v4 = this->clusters.num <= 0;
        this->clusters.list = v13;
        if ( !v4 )
        {
          v15 = 0;
          do
          {
            v16 = &this->clusters.list[v15];
            v16->numAreas = list[v15].numAreas;
            v16->numReachableAreas = list[v15].numReachableAreas;
            v16->numPortals = list[v15].numPortals;
            ++v14;
            v16->firstPortal = list[v15++].firstPortal;
          }
          while ( v14 < this->clusters.num );
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
  }
  this->clusters.list[this->clusters.num++] = *cluster;
  return this->clusters.num - 1;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::ClearTactical(void)
void __thiscall idAASFileLocal::ClearTactical(idAASFileLocal *this)
{
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
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumFeatureIndexes(void)const
int __thiscall idAASFileLocal::GetNumFeatureIndexes(idAASFileLocal *this)
{
  return this->featureIndex.num;
}

// FUNC: public: virtual int & __thiscall idAASFileLocal::GetFeatureIndex(int)
int *__thiscall idAASFileLocal::GetFeatureIndex(idAASFileLocal *this, int index)
{
  return &this->featureIndex.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendFeatureIndex(int &)
int __thiscall idAASFileLocal::AppendFeatureIndex(idAASFileLocal *this, int *featureIdx)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  int *list; // edi
  int j; // eax

  if ( !this->featureIndex.list )
  {
    granularity = this->featureIndex.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->featureIndex.size )
      {
        v4 = granularity < this->featureIndex.num;
        this->featureIndex.size = granularity;
        if ( v4 )
          this->featureIndex.num = granularity;
        this->featureIndex.list = (int *)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->featureIndex.num; ++i )
          this->featureIndex.list[i] = *(_DWORD *)(4 * i);
      }
    }
    else
    {
      this->featureIndex.list = 0;
      this->featureIndex.num = 0;
      this->featureIndex.size = 0;
    }
  }
  num = this->featureIndex.num;
  size = this->featureIndex.size;
  if ( num == size )
  {
    if ( !this->featureIndex.granularity )
      this->featureIndex.granularity = 16;
    v8 = size
       + this->featureIndex.granularity
       - (size + this->featureIndex.granularity) % this->featureIndex.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->featureIndex.size )
      {
        list = this->featureIndex.list;
        this->featureIndex.size = v8;
        if ( v8 < num )
          this->featureIndex.num = v8;
        this->featureIndex.list = (int *)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->featureIndex.num; ++j )
          this->featureIndex.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->featureIndex.list )
        Memory::Free(this->featureIndex.list);
      this->featureIndex.list = 0;
      this->featureIndex.num = 0;
      this->featureIndex.size = 0;
    }
  }
  this->featureIndex.list[this->featureIndex.num++] = *featureIdx;
  return this->featureIndex.num - 1;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumFeatures(void)const
int __thiscall idAASFileLocal::GetNumFeatures(idAASFileLocal *this)
{
  return this->features.num;
}

// FUNC: public: virtual struct aasFeature_s & __thiscall idAASFileLocal::GetFeature(int)
aasFeature_s *__thiscall idAASFileLocal::GetFeature(idAASFileLocal *this, int index)
{
  return &this->features.list[index];
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendFeature(struct aasFeature_s &)
int __thiscall idAASFileLocal::AppendFeature(idAASFileLocal *this, aasFeature_s *feature)
{
  int granularity; // eax
  bool v4; // cc
  aasFeature_s *v5; // eax
  int v6; // ecx
  _DWORD *v7; // eax
  aasFeature_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  aasFeature_s *list; // edi
  aasFeature_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  aasFeature_s *v16; // ebx

  if ( !this->features.list )
  {
    granularity = this->features.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->features.size )
      {
        v4 = granularity < this->features.num;
        this->features.size = granularity;
        if ( v4 )
          this->features.num = granularity;
        v5 = (aasFeature_s *)Memory::Allocate(12 * granularity);
        v6 = 0;
        v4 = this->features.num <= 0;
        this->features.list = v5;
        if ( !v4 )
        {
          v7 = 0;
          do
          {
            v8 = (aasFeature_s *)((char *)v7 + (unsigned int)this->features.list);
            *(_DWORD *)&v8->x = *v7;
            *(_DWORD *)&v8->z = v7[1];
            ++v6;
            *(_DWORD *)&v8->normalx = v7[2];
            v7 += 3;
          }
          while ( v6 < this->features.num );
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
    v11 = this->features.granularity + size - (this->features.granularity + size) % this->features.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->features.size )
      {
        list = this->features.list;
        this->features.size = v11;
        if ( v11 < num )
          this->features.num = v11;
        v13 = (aasFeature_s *)Memory::Allocate(12 * v11);
        v14 = 0;
        v4 = this->features.num <= 0;
        this->features.list = v13;
        if ( !v4 )
        {
          v15 = 0;
          do
          {
            v16 = &this->features.list[v15];
            *(_DWORD *)&v16->x = *(_DWORD *)&list[v15].x;
            *(_DWORD *)&v16->z = *(_DWORD *)&list[v15].z;
            ++v14;
            *(_DWORD *)&v16->normalx = *(_DWORD *)&list[v15++].normalx;
          }
          while ( v14 < this->features.num );
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
  }
  this->features.list[this->features.num++] = *feature;
  return this->features.num - 1;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::SetPortalMaxTravelTime(int,int)
void __thiscall idAASFileLocal::SetPortalMaxTravelTime(idAASFileLocal *this, int index, unsigned __int16 time)
{
  this->portals.list[index].maxAreaTravelTime = time;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::SetAreaTravelFlag(int,int)
void __thiscall idAASFileLocal::SetAreaTravelFlag(idAASFileLocal *this, int index, int flag)
{
  this->areas.list[index].travelFlags |= flag;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::RemoveAreaTravelFlag(int,int)
void __thiscall idAASFileLocal::RemoveAreaTravelFlag(idAASFileLocal *this, int index, int flag)
{
  int *p_travelFlags; // eax

  p_travelFlags = &this->areas.list[index].travelFlags;
  *p_travelFlags &= ~flag;
}

// FUNC: public: virtual class idAASSettings * __thiscall idAASFileLocal::CreateAASSettings(void)
void __thiscall idAASFileLocal::CreateAASSettings(idAASFileLocal *this)
{
  idAASSettings *v1; // eax

  v1 = (idAASSettings *)Memory::Allocate(0xF0u);
  if ( v1 )
    idAASSettings::idAASSettings(v1);
}

// FUNC: public: virtual int __thiscall idAASFileLocal::FindPlane(class idPlane const &,float,float)
int __thiscall idAASFileLocal::FindPlane(idAASFileLocal *this, idPlane *plane, float normalEps, float distEps)
{
  idPlaneSet *p_planeList; // esi
  idHashIndex *p_hash; // edi
  int v7; // eax
  int v8; // edx
  float *v9; // ecx
  int v10; // ecx
  float *v11; // eax
  int v12; // ebp
  int v13; // eax
  int v15; // eax
  int v16; // eax
  float *v17; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int size; // ecx
  float *p_a; // eax
  int v23; // ebp
  int indexSize; // eax
  int v25; // eax
  int v26; // eax
  float *v27; // ecx
  int v28; // ebx
  int num; // eax
  int v30; // eax
  int v31; // [esp+Ch] [ebp-24h]
  float v32; // [esp+10h] [ebp-20h]
  float v33; // [esp+14h] [ebp-1Ch]
  float v34; // [esp+18h] [ebp-18h]
  int v35; // [esp+1Ch] [ebp-14h]
  float v36; // [esp+20h] [ebp-10h]
  float v37; // [esp+20h] [ebp-10h]
  float v38; // [esp+24h] [ebp-Ch]
  float v39; // [esp+24h] [ebp-Ch]
  float v40; // [esp+28h] [ebp-8h]
  float v41; // [esp+28h] [ebp-8h]
  float v42; // [esp+2Ch] [ebp-4h]
  float v43; // [esp+2Ch] [ebp-4h]
  float planea; // [esp+34h] [ebp+4h]
  float planeb; // [esp+34h] [ebp+4h]

  planea = -plane->d;
  p_planeList = &this->planeList;
  HIBYTE(planea) &= ~0x80u;
  p_hash = &this->planeList.hash;
  v7 = -1;
  v35 = -1;
  v31 = (int)(planea * 0.125);
  while ( 1 )
  {
    v8 = p_hash->hash[p_hash->hashMask & p_hash->lookupMask & (v7 + v31)];
    if ( v8 >= 0 )
      break;
LABEL_9:
    v35 = ++v7;
    if ( v7 > 1 )
    {
      if ( idPlane::Type(plane) < 3 || idPlane::Type(plane) >= 6 )
      {
        if ( !p_planeList->list )
          idList<idPlane>::Resize(p_planeList, p_planeList->granularity);
        size = p_planeList->size;
        if ( p_planeList->num == size )
        {
          if ( !p_planeList->granularity )
            p_planeList->granularity = 16;
          idList<idPlane>::Resize(
            p_planeList,
            p_planeList->granularity + size - (p_planeList->granularity + size) % p_planeList->granularity);
        }
        p_a = &p_planeList->list[p_planeList->num].a;
        *p_a = plane->a;
        p_a[1] = plane->b;
        p_a[2] = plane->c;
        p_a[3] = plane->d;
        v23 = p_planeList->num++;
        if ( p_hash->hash == idHashIndex::INVALID_INDEX )
        {
          indexSize = p_hash->indexSize;
          if ( v23 >= indexSize )
            indexSize = p_planeList->num;
          idHashIndex::Allocate(p_hash, p_hash->hashSize, indexSize);
        }
        else if ( v23 >= p_hash->indexSize )
        {
          idHashIndex::ResizeIndex(p_hash, p_planeList->num);
        }
        v25 = v31 & p_hash->hashMask;
        p_hash->indexChain[v23] = p_hash->hash[v25];
        p_hash->hash[v25] = v23;
        v37 = -plane->a;
        v39 = -plane->b;
        v41 = -plane->c;
        v43 = -plane->d;
        if ( !p_planeList->list )
          idList<idPlane>::Resize(p_planeList, p_planeList->granularity);
        v26 = p_planeList->size;
        if ( p_planeList->num == v26 )
        {
          if ( !p_planeList->granularity )
            p_planeList->granularity = 16;
          idList<idPlane>::Resize(
            p_planeList,
            v26 + p_planeList->granularity - (v26 + p_planeList->granularity) % p_planeList->granularity);
        }
        v27 = &p_planeList->list[p_planeList->num].a;
        *v27 = v37;
        v27[1] = v39;
        v27[2] = v41;
        v27[3] = v43;
        v28 = p_planeList->num++;
        if ( p_hash->hash == idHashIndex::INVALID_INDEX )
        {
          num = p_hash->indexSize;
          if ( v28 >= num )
            num = p_planeList->num;
          idHashIndex::Allocate(p_hash, p_hash->hashSize, num);
        }
        else if ( v28 >= p_hash->indexSize )
        {
          idHashIndex::ResizeIndex(p_hash, p_planeList->num);
        }
        v30 = v31 & p_hash->hashMask;
        p_hash->indexChain[v28] = p_hash->hash[v30];
        p_hash->hash[v30] = v28;
        return p_planeList->num - 2;
      }
      else
      {
        v36 = -plane->a;
        v38 = -plane->b;
        v40 = -plane->c;
        v42 = -plane->d;
        if ( !p_planeList->list )
          idList<idPlane>::Resize(p_planeList, p_planeList->granularity);
        v10 = p_planeList->size;
        if ( p_planeList->num == v10 )
        {
          if ( !p_planeList->granularity )
            p_planeList->granularity = 16;
          idList<idPlane>::Resize(
            p_planeList,
            p_planeList->granularity + v10 - (p_planeList->granularity + v10) % p_planeList->granularity);
        }
        v11 = &p_planeList->list[p_planeList->num].a;
        *v11 = v36;
        v11[1] = v38;
        v11[2] = v40;
        v11[3] = v42;
        v12 = p_planeList->num++;
        if ( p_hash->hash == idHashIndex::INVALID_INDEX )
        {
          v13 = p_hash->indexSize;
          if ( v12 >= v13 )
            v13 = p_planeList->num;
          idHashIndex::Allocate(p_hash, p_hash->hashSize, v13);
        }
        else if ( v12 >= p_hash->indexSize )
        {
          idHashIndex::ResizeIndex(p_hash, p_planeList->num);
        }
        v15 = v31 & p_hash->hashMask;
        p_hash->indexChain[v12] = p_hash->hash[v15];
        p_hash->hash[v15] = v12;
        if ( !p_planeList->list )
          idList<idPlane>::Resize(p_planeList, p_planeList->granularity);
        v16 = p_planeList->size;
        if ( p_planeList->num == v16 )
        {
          if ( !p_planeList->granularity )
            p_planeList->granularity = 16;
          idList<idPlane>::Resize(
            p_planeList,
            v16 + p_planeList->granularity - (v16 + p_planeList->granularity) % p_planeList->granularity);
        }
        v17 = &p_planeList->list[p_planeList->num].a;
        *v17 = plane->a;
        v17[1] = plane->b;
        v17[2] = plane->c;
        v17[3] = plane->d;
        v18 = p_planeList->num++;
        if ( p_hash->hash == idHashIndex::INVALID_INDEX )
        {
          v19 = p_hash->indexSize;
          if ( v18 >= v19 )
            v19 = p_planeList->num;
          idHashIndex::Allocate(p_hash, p_hash->hashSize, v19);
        }
        else if ( v18 >= p_hash->indexSize )
        {
          idHashIndex::ResizeIndex(p_hash, p_planeList->num);
        }
        v20 = v31 & p_hash->hashMask;
        p_hash->indexChain[v18] = p_hash->hash[v20];
        p_hash->hash[v20] = v18;
        return p_planeList->num - 1;
      }
    }
  }
  while ( 1 )
  {
    v9 = &p_planeList->list[v8].a;
    planeb = v9[3] - plane->d;
    HIBYTE(planeb) &= ~0x80u;
    if ( planeb <= (double)distEps )
    {
      v32 = *v9 - plane->a;
      HIBYTE(v32) &= ~0x80u;
      if ( v32 <= (double)normalEps )
      {
        v33 = v9[1] - plane->b;
        HIBYTE(v33) &= ~0x80u;
        if ( v33 <= (double)normalEps )
        {
          v34 = v9[2] - plane->c;
          HIBYTE(v34) &= ~0x80u;
          if ( v34 <= (double)normalEps )
            return v8;
        }
      }
    }
    v8 = p_hash->indexChain[v8 & p_hash->lookupMask];
    if ( v8 < 0 )
    {
      v7 = v35;
      goto LABEL_9;
    }
  }
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendVertex(class idVec3 &)
int __thiscall idAASFileLocal::AppendVertex(idAASFileLocal *this, idVec3 *vert)
{
  idList<idAngles> *p_vertices; // esi
  int size; // eax

  p_vertices = (idList<idAngles> *)&this->vertices;
  if ( !this->vertices.list )
    idList<idVec3>::Resize((idList<idAngles> *)&this->vertices, this->vertices.granularity);
  size = p_vertices->size;
  if ( p_vertices->num == size )
  {
    if ( !p_vertices->granularity )
      p_vertices->granularity = 16;
    idList<idVec3>::Resize(
      p_vertices,
      size + p_vertices->granularity - (size + p_vertices->granularity) % p_vertices->granularity);
  }
  p_vertices->list[p_vertices->num++] = (idAngles)*vert;
  return p_vertices->num - 1;
}

// FUNC: public: virtual bool __thiscall idAASFileLocal::FromParser(class idAASSettings *,class Lexer &)
char __thiscall idAASFileLocal::FromParser(idAASFileLocal *this, idAASSettings *edit, Lexer *src)
{
  return idAASSettings::FromParser(edit, src);
}

// FUNC: public: virtual int __thiscall idAASFileLocal::AppendArea(struct aasArea_s &)
int __thiscall idAASFileLocal::AppendArea(idAASFileLocal *this, aasArea_s *area)
{
  idList<aasArea_s> *p_areas; // esi
  int size; // eax

  p_areas = &this->areas;
  if ( !this->areas.list )
    idList<aasArea_s>::Resize(&this->areas, this->areas.granularity);
  size = p_areas->size;
  if ( p_areas->num == size )
  {
    if ( !p_areas->granularity )
      p_areas->granularity = 16;
    idList<aasArea_s>::Resize(
      p_areas,
      size + p_areas->granularity - (size + p_areas->granularity) % p_areas->granularity);
  }
  aasArea_s::operator=(&p_areas->list[p_areas->num].numFaces, (int)area);
  return p_areas->num++;
}

// FUNC: public: virtual void __thiscall idAASFileLocal::SetSettings(class idAASSettings const &)
void __thiscall idAASFileLocal::SetSettings(idAASFileLocal *this, const idAASSettings *in)
{
  idAASSettings::operator=((char *)&this->settings, (int)in);
}

// FUNC: public: virtual class idAASFile * __thiscall idAASFileLocal::CreateNew(void)
void __thiscall idAASFileLocal::CreateNew(idAASFileLocal *this)
{
  idAASFileLocal *v1; // eax

  v1 = (idAASFileLocal *)Memory::Allocate(0x230u);
  if ( v1 )
    idAASFileLocal::idAASFileLocal(v1);
}
