
// FUNC: public: virtual void __thiscall idAASFileLocal::Optimize(void)
void __thiscall idAASFileLocal::Optimize(idAASFileLocal *this)
{
  int num; // esi
  int v2; // esi
  int v3; // esi
  int v4; // esi
  int v5; // esi
  int v6; // esi
  int v7; // esi
  _DWORD *v8; // eax
  _DWORD *v9; // edi
  int v10; // esi
  _DWORD *v11; // ebx
  int v12; // eax
  int v13; // esi
  char *v14; // ebp
  int v15; // eax
  unsigned int v16; // eax
  aasFace_s *v17; // ebp
  char *v18; // edi
  int v19; // ebx
  int v20; // esi
  _DWORD *v21; // eax
  int v22; // ecx
  _DWORD *v23; // edx
  int v24; // esi
  int v25; // eax
  _BYTE *v26; // esi
  char *v27; // eax
  int v28; // ecx
  int v29; // edx
  char *v30; // ebx
  int v31; // edi
  char *v32; // edx
  int v33; // ebx
  char *v34; // eax
  int v35; // ebx
  void *v36; // edi
  int v37; // esi
  __int64 v38; // rax
  int v39; // eax
  aasEdge_s *v40; // ebp
  int v41; // esi
  idVec3 *v42; // esi
  _DWORD *v43; // eax
  int v44; // esi
  _DWORD *v45; // ecx
  int v46; // edi
  int v47; // edx
  int v48; // eax
  int v49; // edx
  int v50; // eax
  _BYTE *v51; // edi
  _DWORD *v52; // eax
  _DWORD *v53; // ecx
  int v54; // esi
  _DWORD *v55; // edx
  int v56; // eax
  float *v57; // eax
  float z; // ecx
  int v59; // edx
  idVec3 *v60; // esi
  _DWORD *v61; // eax
  int v62; // esi
  _DWORD *v63; // ecx
  int v64; // edi
  int v65; // edx
  int v66; // eax
  int v67; // edx
  int v68; // eax
  _BYTE *v69; // edi
  _DWORD *v70; // eax
  _DWORD *v71; // ecx
  int v72; // esi
  _DWORD *v73; // edx
  int v74; // eax
  float *v75; // eax
  float v76; // ecx
  _DWORD *v77; // eax
  int v78; // ecx
  int v79; // edx
  int v80; // eax
  _BYTE *v81; // esi
  _DWORD *v82; // eax
  int v83; // edx
  int v84; // ecx
  int v85; // eax
  _BYTE *v86; // ecx
  int v87; // eax
  int v88; // edx
  int v89; // eax
  int v90; // ebp
  _BYTE *v91; // esi
  _DWORD *v92; // eax
  int v93; // ecx
  int v94; // edx
  char *v95; // eax
  int v96; // ebx
  int v97; // edi
  void *v98; // ecx
  int v99; // eax
  int v100; // edx
  int v101; // eax
  _BYTE *v102; // esi
  _DWORD *v103; // eax
  int v104; // ecx
  int v105; // edx
  void *v106; // ebx
  int v107; // esi
  int v108; // eax
  int v109; // eax
  _BYTE *v110; // esi
  _DWORD *v111; // eax
  int v112; // ecx
  int v113; // edx
  bool v114; // cc
  idReachability *reach; // ecx
  __int64 v116; // rax
  idVec3 *v117; // eax
  int v118; // edx
  _DWORD *v119; // ecx
  _DWORD *v120; // eax
  int m; // eax
  aasEdge_s *list; // edx
  int n; // eax
  aasFace_s *v124; // eax
  int v125; // ecx
  unsigned int v126; // eax
  aasFace_s *v127; // esi
  int v128; // eax
  void *v129; // ecx
  int newFaceIndex; // [esp+14h] [ebp-BCh]
  int newFaceIndex_4; // [esp+18h] [ebp-B8h]
  void *newFaceIndex_12; // [esp+20h] [ebp-B0h]
  int newVertices; // [esp+24h] [ebp-ACh]
  int newVertices_4; // [esp+28h] [ebp-A8h]
  _DWORD *newVertices_12; // [esp+30h] [ebp-A0h]
  int newEdges; // [esp+34h] [ebp-9Ch]
  int newEdges_4; // [esp+38h] [ebp-98h]
  void *newEdges_12; // [esp+40h] [ebp-90h]
  int newEdgeIndex; // [esp+44h] [ebp-8Ch]
  int newEdgeIndex_4; // [esp+48h] [ebp-88h]
  _BYTE *newEdgeIndex_12; // [esp+50h] [ebp-80h]
  int newFaces; // [esp+54h] [ebp-7Ch]
  int newFaces_4; // [esp+58h] [ebp-78h]
  char *newFaces_12; // [esp+60h] [ebp-70h]
  idVec3 *v146; // [esp+64h] [ebp-6Ch]
  idVec3 *v147; // [esp+64h] [ebp-6Ch]
  aasFace_s *face; // [esp+6Ch] [ebp-64h]
  int *edgeRemap_12; // [esp+7Ch] [ebp-54h]
  int k; // [esp+80h] [ebp-50h]
  int j; // [esp+84h] [ebp-4Ch]
  unsigned int v152; // [esp+88h] [ebp-48h]
  int i; // [esp+8Ch] [ebp-44h]
  void *faceRemap_12; // [esp+9Ch] [ebp-34h]
  aasArea_s *area; // [esp+A0h] [ebp-30h]
  void *vertexRemap_12; // [esp+B0h] [ebp-20h]
  int areaFirstFace; // [esp+B4h] [ebp-1Ch]
  int faceFirstEdge; // [esp+B8h] [ebp-18h]
  int faceNum; // [esp+BCh] [ebp-14h]
  int v160; // [esp+C0h] [ebp-10h]

  vertexRemap_12 = 0;
  edgeRemap_12 = 0;
  faceRemap_12 = 0;
  newVertices = 0;
  newEdgeIndex = 0;
  newFaceIndex = 0;
  num = this->vertices.num;
  if ( num > 0 )
  {
    v2 = num + 15 - (num + 15) % 16;
    vertexRemap_12 = v2 > 0 ? Memory::Allocate(4 * v2) : 0;
    if ( v2 > 0 )
      memset(vertexRemap_12, 0xFFu, 4 * v2);
  }
  v3 = this->edges.num;
  if ( v3 > 0 )
  {
    v4 = v3 + 15 - (v3 + 15) % 16;
    edgeRemap_12 = v4 > 0 ? (int *)Memory::Allocate(4 * v4) : 0;
    if ( v4 > 0 )
      memset(edgeRemap_12, 0, 4 * v4);
  }
  v5 = this->faces.num;
  if ( v5 > 0 )
  {
    v6 = v5 + 15 - (v5 + 15) % 16;
    faceRemap_12 = v6 > 0 ? Memory::Allocate(4 * v6) : 0;
    if ( v6 > 0 )
      memset(faceRemap_12, 0, 4 * v6);
  }
  v7 = this->vertices.num;
  if ( v7 > 0 )
  {
    newVertices_4 = this->vertices.num;
    v8 = Memory::Allocate(12 * v7);
    v9 = v8;
    if ( v8 )
      `vector constructor iterator'(v8, 0xCu, v7, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
    else
      v9 = 0;
    newVertices_12 = v9;
  }
  else
  {
    newVertices_12 = 0;
    newVertices = 0;
    newVertices_4 = 0;
  }
  v10 = this->edges.num;
  if ( v10 <= 0 )
  {
    newEdges_4 = 1;
    v11 = Memory::Allocate(8u);
  }
  else
  {
    newEdges_4 = this->edges.num;
    v11 = Memory::Allocate(8 * v10);
  }
  newEdges_12 = v11;
  *v11 = 0;
  v11[1] = 0;
  v12 = this->edgeIndex.num;
  newEdges = 1;
  if ( v12 > 0 )
  {
    newEdgeIndex_4 = this->edgeIndex.num;
    newEdgeIndex_12 = Memory::Allocate(4 * v12);
  }
  else
  {
    newEdgeIndex_12 = 0;
    newEdgeIndex = 0;
    newEdgeIndex_4 = 0;
  }
  v13 = this->faces.num;
  if ( v13 <= 0 )
  {
    newFaces_4 = 1;
    v14 = (char *)Memory::Allocate(0x10u);
  }
  else
  {
    newFaces_4 = this->faces.num;
    v14 = (char *)Memory::Allocate(16 * v13);
  }
  newFaces_12 = v14;
  *(_DWORD *)v14 = 0;
  *((_DWORD *)v14 + 1) = 0;
  *((_DWORD *)v14 + 2) = 0;
  *((_DWORD *)v14 + 3) = 0;
  v15 = this->faceIndex.num;
  newFaces = 1;
  if ( v15 > 0 )
  {
    newFaceIndex_4 = this->faceIndex.num;
    newFaceIndex_12 = Memory::Allocate(4 * v15);
  }
  else
  {
    newFaceIndex_12 = 0;
    newFaceIndex = 0;
    newFaceIndex_4 = 0;
  }
  i = 0;
  if ( this->areas.num > 0 )
  {
    while ( 1 )
    {
      area = &this->areas.list[i];
      areaFirstFace = newFaceIndex;
      j = 0;
      if ( area->numFaces > 0 )
        break;
LABEL_208:
      area->firstFace = areaFirstFace;
      reach = area->reach;
      for ( area->numFaces = newFaceIndex - areaFirstFace; reach; reach = reach->next )
      {
        v116 = edgeRemap_12[reach->edgeNum];
        reach->edgeNum = (HIDWORD(v116) ^ v116) - HIDWORD(v116);
      }
      if ( ++i >= this->areas.num )
        goto LABEL_211;
    }
    while ( 1 )
    {
      faceNum = this->faceIndex.list[j + area->firstFace];
      v16 = abs32(faceNum);
      v17 = &this->faces.list[v16];
      v152 = v16;
      face = v17;
      if ( !*((_DWORD *)faceRemap_12 + v16) )
      {
        v18 = newFaces_12;
        v19 = newFaces;
        v20 = newFaces_4;
        *((_DWORD *)faceRemap_12 + v16) = newFaces;
        if ( !newFaces_12 && newFaces_4 != 16 )
        {
          v20 = 16;
          newFaces_4 = 16;
          if ( newFaces > 16 )
          {
            v19 = 16;
            newFaces = 16;
          }
          v18 = (char *)Memory::Allocate(0x100u);
          newFaces_12 = v18;
          if ( v19 > 0 )
          {
            v21 = 0;
            v22 = v19;
            do
            {
              v23 = (_DWORD *)((char *)v21 + (_DWORD)v18);
              *v23 = *v21;
              v23[1] = v21[1];
              v23[2] = v21[2];
              v24 = v21[3];
              v21 += 4;
              --v22;
              v23[3] = v24;
            }
            while ( v22 );
            v20 = 16;
          }
        }
        if ( v19 == v20 )
        {
          v25 = v20 + 16 - (v20 + 16) % 16;
          if ( v25 > 0 )
          {
            if ( v25 != v20 )
            {
              v26 = v18;
              newFaces_4 = v25;
              if ( v25 < v19 )
              {
                v19 = v25;
                newFaces = v25;
              }
              v27 = (char *)Memory::Allocate(16 * v25);
              v18 = v27;
              newFaces_12 = v27;
              if ( v19 > 0 )
              {
                v28 = v26 - v27;
                v29 = v19;
                do
                {
                  v30 = v27;
                  *(_DWORD *)v27 = *(_DWORD *)&v27[v28];
                  *((_DWORD *)v27 + 1) = *(_DWORD *)&v27[v28 + 4];
                  *((_DWORD *)v27 + 2) = *(_DWORD *)&v27[v28 + 8];
                  v31 = *(_DWORD *)&v27[v28 + 12];
                  v27 += 16;
                  --v29;
                  *((_DWORD *)v30 + 3) = v31;
                }
                while ( v29 );
                v19 = newFaces;
                v18 = newFaces_12;
              }
              if ( v26 )
                Memory::Free(v26);
            }
          }
          else
          {
            if ( v18 )
              Memory::Free(v18);
            v19 = 0;
            v18 = 0;
            newFaces_12 = 0;
            newFaces_4 = 0;
          }
        }
        v32 = &v18[16 * v19];
        *(_DWORD *)v32 = *(_DWORD *)&v17->planeNum;
        *((_DWORD *)v32 + 1) = v17->numEdges;
        *((_DWORD *)v32 + 2) = v17->firstEdge;
        v33 = v19 + 1;
        *((_DWORD *)v32 + 3) = *(_DWORD *)v17->areas;
        newFaces = v33;
        if ( (v17->flags & 6) != 0 )
        {
          faceFirstEdge = newEdgeIndex;
          k = 0;
          if ( v17->numEdges > 0 )
          {
            v35 = newVertices;
            v36 = newEdges_12;
            do
            {
              v37 = newEdgeIndex;
              v38 = this->edgeIndex.list[k + face->firstEdge];
              v39 = (HIDWORD(v38) ^ v38) - HIDWORD(v38);
              v40 = &this->edges.list[v39];
              v160 = v39;
              if ( !edgeRemap_12[v39] )
              {
                v41 = newEdges;
                if ( this->edgeIndex.list[k + face->firstEdge] >= 0 )
                  edgeRemap_12[v39] = newEdges;
                else
                  edgeRemap_12[v39] = -newEdges;
                if ( *((_DWORD *)vertexRemap_12 + v40->vertexNum[0]) == -1 )
                {
                  *((_DWORD *)vertexRemap_12 + v40->vertexNum[0]) = v35;
                  v42 = &this->vertices.list[v40->vertexNum[0]];
                  v146 = v42;
                  if ( !newVertices_12 && newVertices_4 != 16 )
                  {
                    newVertices_4 = 16;
                    if ( v35 > 16 )
                      v35 = 16;
                    v43 = Memory::Allocate(0xC0u);
                    newVertices_12 = v43;
                    if ( v35 > 0 )
                    {
                      v44 = -4 - (_DWORD)v43;
                      v45 = v43 + 2;
                      v46 = -8 - (_DWORD)v43;
                      v47 = 8;
                      v48 = v35;
                      do
                      {
                        *(v45 - 2) = *(_DWORD *)((char *)v45 + v46);
                        *(v45 - 1) = *(_DWORD *)((char *)v45 + v44);
                        *v45 = *(_DWORD *)v47;
                        v45 += 3;
                        v47 += 12;
                        --v48;
                      }
                      while ( v48 );
                      v42 = v146;
                    }
                  }
                  if ( v35 == newVertices_4 )
                  {
                    v49 = (newVertices_4 + 16) % 16;
                    v50 = newVertices_4 + 16 - v49;
                    if ( v50 > 0 )
                    {
                      if ( v50 != newVertices_4 )
                      {
                        v51 = newVertices_12;
                        newVertices_4 = newVertices_4 + 16 - v49;
                        if ( v50 < v35 )
                          v35 = v50;
                        v52 = Memory::Allocate(12 * v50);
                        newVertices_12 = v52;
                        if ( v35 > 0 )
                        {
                          v53 = v52 + 1;
                          v54 = v51 - (_BYTE *)v52;
                          v55 = v51;
                          v56 = v35;
                          do
                          {
                            *(v53 - 1) = *v55;
                            *v53 = *(_DWORD *)((char *)v53 + v54);
                            v53[1] = v55[2];
                            v55 += 3;
                            v53 += 3;
                            --v56;
                          }
                          while ( v56 );
                          v42 = v146;
                        }
                        if ( v51 )
                          Memory::Free(v51);
                      }
                    }
                    else
                    {
                      if ( newVertices_12 )
                        Memory::Free(newVertices_12);
                      newVertices_12 = 0;
                      v35 = 0;
                      newVertices_4 = 0;
                    }
                  }
                  v36 = newEdges_12;
                  v57 = (float *)&newVertices_12[3 * v35];
                  *v57 = v42->x;
                  v57[1] = v42->y;
                  z = v42->z;
                  v41 = newEdges;
                  ++v35;
                  v57[2] = z;
                  newVertices = v35;
                }
                v59 = v40->vertexNum[1];
                if ( *((_DWORD *)vertexRemap_12 + v59) == -1 )
                {
                  *((_DWORD *)vertexRemap_12 + v59) = v35;
                  v60 = &this->vertices.list[v40->vertexNum[1]];
                  v147 = v60;
                  if ( !newVertices_12 && newVertices_4 != 16 )
                  {
                    newVertices_4 = 16;
                    if ( v35 > 16 )
                      v35 = 16;
                    v61 = Memory::Allocate(0xC0u);
                    newVertices_12 = v61;
                    if ( v35 > 0 )
                    {
                      v62 = -4 - (_DWORD)v61;
                      v63 = v61 + 2;
                      v64 = -8 - (_DWORD)v61;
                      v65 = 8;
                      v66 = v35;
                      do
                      {
                        *(v63 - 2) = *(_DWORD *)((char *)v63 + v64);
                        *(v63 - 1) = *(_DWORD *)((char *)v63 + v62);
                        *v63 = *(_DWORD *)v65;
                        v63 += 3;
                        v65 += 12;
                        --v66;
                      }
                      while ( v66 );
                      v60 = v147;
                    }
                  }
                  if ( v35 == newVertices_4 )
                  {
                    v67 = (newVertices_4 + 16) % 16;
                    v68 = newVertices_4 + 16 - v67;
                    if ( v68 > 0 )
                    {
                      if ( v68 != newVertices_4 )
                      {
                        v69 = newVertices_12;
                        newVertices_4 = newVertices_4 + 16 - v67;
                        if ( v68 < v35 )
                          v35 = v68;
                        v70 = Memory::Allocate(12 * v68);
                        newVertices_12 = v70;
                        if ( v35 > 0 )
                        {
                          v71 = v70 + 1;
                          v72 = v69 - (_BYTE *)v70;
                          v73 = v69;
                          v74 = v35;
                          do
                          {
                            *(v71 - 1) = *v73;
                            *v71 = *(_DWORD *)((char *)v71 + v72);
                            v71[1] = v73[2];
                            v73 += 3;
                            v71 += 3;
                            --v74;
                          }
                          while ( v74 );
                          v60 = v147;
                        }
                        if ( v69 )
                          Memory::Free(v69);
                      }
                    }
                    else
                    {
                      if ( newVertices_12 )
                        Memory::Free(newVertices_12);
                      newVertices_12 = 0;
                      v35 = 0;
                      newVertices_4 = 0;
                    }
                  }
                  v36 = newEdges_12;
                  v75 = (float *)&newVertices_12[3 * v35];
                  *v75 = v60->x;
                  v75[1] = v60->y;
                  v76 = v60->z;
                  v41 = newEdges;
                  ++v35;
                  v75[2] = v76;
                  newVertices = v35;
                }
                if ( !v36 && newEdges_4 != 16 )
                {
                  newEdges_4 = 16;
                  if ( v41 > 16 )
                  {
                    v41 = 16;
                    newEdges = 16;
                  }
                  v36 = Memory::Allocate(0x80u);
                  newEdges_12 = v36;
                  if ( v41 > 0 )
                  {
                    v77 = 0;
                    v78 = v41;
                    do
                    {
                      *(_DWORD *)((char *)v77 + (_DWORD)v36) = *v77;
                      *(_DWORD *)((char *)v77 + (_DWORD)v36 + 4) = v77[1];
                      v77 += 2;
                      --v78;
                    }
                    while ( v78 );
                  }
                }
                if ( v41 == newEdges_4 )
                {
                  v79 = (newEdges_4 + 16) % 16;
                  v80 = newEdges_4 + 16 - v79;
                  if ( v80 > 0 )
                  {
                    if ( v80 != newEdges_4 )
                    {
                      v81 = v36;
                      newEdges_4 = newEdges_4 + 16 - v79;
                      if ( v80 < newEdges )
                        newEdges = v80;
                      v82 = Memory::Allocate(8 * v80);
                      v36 = v82;
                      newEdges_12 = v82;
                      if ( newEdges > 0 )
                      {
                        v83 = newEdges;
                        v84 = v81 - (_BYTE *)v82;
                        do
                        {
                          *v82 = *(_DWORD *)((char *)v82 + v84);
                          v82[1] = *(_DWORD *)((char *)v82 + v84 + 4);
                          v82 += 2;
                          --v83;
                        }
                        while ( v83 );
                        v36 = newEdges_12;
                      }
                      if ( v81 )
                        Memory::Free(v81);
                    }
                  }
                  else
                  {
                    if ( v36 )
                      Memory::Free(v36);
                    v36 = 0;
                    newEdges_12 = 0;
                    newEdges = 0;
                    newEdges_4 = 0;
                  }
                }
                v37 = newEdgeIndex;
                *((_DWORD *)v36 + 2 * newEdges) = v40->vertexNum[0];
                *((_DWORD *)v36 + 2 * newEdges + 1) = v40->vertexNum[1];
                v85 = newEdges + 1;
                *((_DWORD *)v36 + 2 * v85 - 2) = *((_DWORD *)vertexRemap_12 + v40->vertexNum[0]);
                ++newEdges;
                *((_DWORD *)v36 + 2 * v85 - 1) = *((_DWORD *)vertexRemap_12 + v40->vertexNum[1]);
              }
              if ( !newEdgeIndex_12 && newEdgeIndex_4 != 16 )
              {
                newEdgeIndex_4 = 16;
                if ( v37 > 16 )
                {
                  v37 = 16;
                  newEdgeIndex = 16;
                }
                v86 = Memory::Allocate(0x40u);
                v87 = 0;
                for ( newEdgeIndex_12 = v86; v87 < v37; ++v87 )
                  *(_DWORD *)&v86[4 * v87] = *(_DWORD *)(4 * v87);
              }
              if ( v37 == newEdgeIndex_4 )
              {
                v88 = (newEdgeIndex_4 + 16) % 16;
                v89 = newEdgeIndex_4 + 16 - v88;
                if ( v89 > 0 )
                {
                  if ( v89 != newEdgeIndex_4 )
                  {
                    v90 = newEdgeIndex;
                    v91 = newEdgeIndex_12;
                    newEdgeIndex_4 = newEdgeIndex_4 + 16 - v88;
                    if ( v89 < newEdgeIndex )
                    {
                      v90 = v89;
                      newEdgeIndex = v89;
                    }
                    v92 = Memory::Allocate(4 * v89);
                    newEdgeIndex_12 = v92;
                    if ( v90 > 0 )
                    {
                      v93 = v91 - (_BYTE *)v92;
                      v94 = v90;
                      do
                      {
                        *v92 = *(_DWORD *)((char *)v92 + v93);
                        ++v92;
                        --v94;
                      }
                      while ( v94 );
                    }
                    if ( v91 )
                      Memory::Free(v91);
                  }
                }
                else
                {
                  if ( newEdgeIndex_12 )
                    Memory::Free(newEdgeIndex_12);
                  newEdgeIndex_12 = 0;
                  newEdgeIndex = 0;
                  newEdgeIndex_4 = 0;
                }
              }
              *(_DWORD *)&newEdgeIndex_12[4 * newEdgeIndex++] = edgeRemap_12[v160];
              ++k;
            }
            while ( k < face->numEdges );
          }
          v95 = &newFaces_12[16 * newFaces];
          *((_DWORD *)v95 - 2) = faceFirstEdge;
          *((_DWORD *)v95 - 3) = newEdgeIndex - faceFirstEdge;
        }
        else
        {
          v34 = &v18[16 * v33];
          *((_DWORD *)v34 - 2) = 0;
          *((_DWORD *)v34 - 3) = 0;
        }
        v16 = v152;
      }
      if ( faceNum >= 0 )
      {
        v106 = newFaceIndex_12;
        v107 = newFaceIndex_4;
        if ( newFaceIndex_12 || newFaceIndex_4 == 16 )
        {
          v97 = newFaceIndex;
        }
        else
        {
          v97 = newFaceIndex;
          v107 = 16;
          newFaceIndex_4 = 16;
          if ( newFaceIndex > 16 )
            v97 = 16;
          v106 = Memory::Allocate(0x40u);
          v108 = 0;
          for ( newFaceIndex_12 = v106; v108 < v97; ++v108 )
            *((_DWORD *)v106 + v108) = *(_DWORD *)(4 * v108);
        }
        if ( v97 == v107 )
        {
          v109 = v107 + 16 - (v107 + 16) % 16;
          if ( v109 > 0 )
          {
            if ( v109 != v107 )
            {
              v110 = v106;
              newFaceIndex_4 = v109;
              if ( v109 < v97 )
                v97 = v109;
              v111 = Memory::Allocate(4 * v109);
              v106 = v111;
              newFaceIndex_12 = v111;
              if ( v97 > 0 )
              {
                v112 = v110 - (_BYTE *)v111;
                v113 = v97;
                do
                {
                  *v111 = *(_DWORD *)((char *)v111 + v112);
                  ++v111;
                  --v113;
                }
                while ( v113 );
              }
              if ( v110 )
                Memory::Free(v110);
            }
          }
          else
          {
            if ( v106 )
              Memory::Free(v106);
            v106 = 0;
            newFaceIndex_12 = 0;
            v97 = 0;
            newFaceIndex_4 = 0;
          }
        }
        *((_DWORD *)v106 + v97) = *((_DWORD *)faceRemap_12 + v152);
        goto LABEL_207;
      }
      v96 = -*((_DWORD *)faceRemap_12 + v16);
      if ( newFaceIndex_12 || newFaceIndex_4 == 16 )
      {
        v97 = newFaceIndex;
      }
      else
      {
        v97 = newFaceIndex;
        newFaceIndex_4 = 16;
        if ( newFaceIndex > 16 )
          v97 = 16;
        v98 = Memory::Allocate(0x40u);
        v99 = 0;
        for ( newFaceIndex_12 = v98; v99 < v97; ++v99 )
          *((_DWORD *)v98 + v99) = *(_DWORD *)(4 * v99);
      }
      if ( v97 == newFaceIndex_4 )
      {
        v100 = (newFaceIndex_4 + 16) % 16;
        v101 = newFaceIndex_4 + 16 - v100;
        if ( v101 <= 0 )
        {
          if ( newFaceIndex_12 )
            Memory::Free(newFaceIndex_12);
          v97 = 0;
          newFaceIndex_12 = 0;
          newFaceIndex_4 = 0;
          MEMORY[0] = v96;
          goto LABEL_207;
        }
        if ( v101 != newFaceIndex_4 )
        {
          v102 = newFaceIndex_12;
          newFaceIndex_4 = newFaceIndex_4 + 16 - v100;
          if ( v101 < v97 )
            v97 = v101;
          v103 = Memory::Allocate(4 * v101);
          newFaceIndex_12 = v103;
          if ( v97 > 0 )
          {
            v104 = v102 - (_BYTE *)v103;
            v105 = v97;
            do
            {
              *v103 = *(_DWORD *)((char *)v103 + v104);
              ++v103;
              --v105;
            }
            while ( v105 );
          }
          if ( v102 )
            Memory::Free(v102);
        }
      }
      *((_DWORD *)newFaceIndex_12 + v97) = v96;
LABEL_207:
      v114 = j + 1 < area->numFaces;
      newFaceIndex = v97 + 1;
      ++j;
      if ( !v114 )
        goto LABEL_208;
    }
  }
LABEL_211:
  if ( this->vertices.list )
    Memory::Free(this->vertices.list);
  this->vertices.list = 0;
  this->vertices.num = newVertices;
  this->vertices.size = newVertices_4;
  this->vertices.granularity = 16;
  if ( newVertices_4 )
  {
    v117 = (idVec3 *)Memory::Allocate(12 * newVertices_4);
    v118 = 0;
    v114 = this->vertices.num <= 0;
    this->vertices.list = v117;
    if ( !v114 )
    {
      v119 = newVertices_12 + 2;
      do
      {
        v120 = (_DWORD *)((char *)&this->vertices.list->x + (unsigned int)v119 - 8 - (_DWORD)newVertices_12);
        ++v118;
        *v120 = *(v119 - 2);
        v120[1] = *(v119 - 1);
        v120[2] = *v119;
        v119 += 3;
      }
      while ( v118 < this->vertices.num );
    }
  }
  if ( this->edges.list )
    Memory::Free(this->edges.list);
  this->edges.list = 0;
  this->edges.num = newEdges;
  this->edges.size = newEdges_4;
  this->edges.granularity = 16;
  if ( newEdges_4 )
  {
    this->edges.list = (aasEdge_s *)Memory::Allocate(8 * newEdges_4);
    for ( m = 0; m < this->edges.num; ++m )
    {
      list = this->edges.list;
      list[m].vertexNum[0] = *((_DWORD *)newEdges_12 + 2 * m);
      list[m].vertexNum[1] = *((_DWORD *)newEdges_12 + 2 * m + 1);
    }
  }
  if ( this->edgeIndex.list )
    Memory::Free(this->edgeIndex.list);
  this->edgeIndex.num = newEdgeIndex;
  this->edgeIndex.list = 0;
  this->edgeIndex.size = newEdgeIndex_4;
  this->edgeIndex.granularity = 16;
  if ( newEdgeIndex_4 )
  {
    this->edgeIndex.list = (int *)Memory::Allocate(4 * newEdgeIndex_4);
    for ( n = 0; n < this->edgeIndex.num; ++n )
      this->edgeIndex.list[n] = *(_DWORD *)&newEdgeIndex_12[4 * n];
  }
  if ( this->faces.list )
    Memory::Free(this->faces.list);
  this->faces.num = newFaces;
  this->faces.list = 0;
  this->faces.size = newFaces_4;
  this->faces.granularity = 16;
  if ( newFaces_4 )
  {
    v124 = (aasFace_s *)Memory::Allocate(16 * newFaces_4);
    v125 = 0;
    v114 = this->faces.num <= 0;
    this->faces.list = v124;
    if ( !v114 )
    {
      v126 = 0;
      do
      {
        v127 = &this->faces.list[v126 / 0x10];
        *(_DWORD *)&v127->planeNum = *(_DWORD *)&newFaces_12[v126];
        v127->numEdges = *(_DWORD *)&newFaces_12[v126 + 4];
        v127->firstEdge = *(_DWORD *)&newFaces_12[v126 + 8];
        *(_DWORD *)v127->areas = *(_DWORD *)&newFaces_12[v126 + 12];
        ++v125;
        v126 += 16;
      }
      while ( v125 < this->faces.num );
    }
  }
  if ( this->faceIndex.list )
    Memory::Free(this->faceIndex.list);
  this->faceIndex.num = newFaceIndex;
  this->faceIndex.list = 0;
  this->faceIndex.size = newFaceIndex_4;
  this->faceIndex.granularity = 16;
  if ( newFaceIndex_4
    && (this->faceIndex.list = (int *)Memory::Allocate(4 * newFaceIndex_4), v128 = 0, this->faceIndex.num > 0) )
  {
    v129 = newFaceIndex_12;
    do
    {
      this->faceIndex.list[v128] = *((_DWORD *)newFaceIndex_12 + v128);
      ++v128;
    }
    while ( v128 < this->faceIndex.num );
  }
  else
  {
    v129 = newFaceIndex_12;
  }
  if ( v129 )
    Memory::Free(v129);
  if ( newFaces_12 )
    Memory::Free(newFaces_12);
  if ( newEdgeIndex_12 )
    Memory::Free(newEdgeIndex_12);
  if ( newEdges_12 )
    Memory::Free(newEdges_12);
  if ( newVertices_12 )
    Memory::Free(newVertices_12);
  if ( faceRemap_12 )
    Memory::Free(faceRemap_12);
  if ( edgeRemap_12 )
    Memory::Free(edgeRemap_12);
  if ( vertexRemap_12 )
    Memory::Free(vertexRemap_12);
}
