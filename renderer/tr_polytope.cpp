
// FUNC: struct srfTriangles_s * __cdecl R_PolytopeSurface(int,class idPlane const *,class idWinding * *)
srfTriangles_s *__cdecl R_PolytopeSurface(int numPlanes, idVec3 *planes, idWinding **windings)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  int v5; // edi
  const idVec3 *v6; // eax
  idWinding *v7; // ebp
  float *p_z; // esi
  int j; // edi
  double v10; // st7
  double v11; // st6
  double v12; // st5
  int numPoints; // eax
  srfTriangles_s *v14; // esi
  char *v15; // edi
  int v16; // edx
  int v17; // eax
  _DWORD *v18; // ecx
  _DWORD *p_x; // eax
  int k; // eax
  idWinding *v21; // ebp
  int v22; // eax
  bool v23; // cc
  int v24; // eax
  int v25; // eax
  _DWORD *v26; // ecx
  _DWORD *v27; // edx
  float dist; // [esp+0h] [ebp-1EA4h]
  int numIndexes; // [esp+14h] [ebp-1E90h]
  int numIndexesa; // [esp+14h] [ebp-1E90h]
  int numIndexesb; // [esp+14h] [ebp-1E90h]
  int v33; // [esp+18h] [ebp-1E8Ch]
  int v34; // [esp+18h] [ebp-1E8Ch]
  int numVerts; // [esp+1Ch] [ebp-1E88h]
  int numVertsa; // [esp+1Ch] [ebp-1E88h]
  const idPlane *i; // [esp+20h] [ebp-1E84h]
  idPlane plane; // [esp+28h] [ebp-1E7Ch] BYREF
  char ptr[4]; // [esp+38h] [ebp-1E6Ch] BYREF
  char v40; // [esp+3Ch] [ebp-1E68h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v41; // [esp+1E98h] [ebp-Ch]
  void *v42; // [esp+1E9Ch] [ebp-8h]
  int v43; // [esp+1EA0h] [ebp-4h]

  v43 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v42 = &_ehhandler__R_PolytopeSurface__YAPAUsrfTriangles_s__HPBVidPlane__PAPAVidWinding___Z;
  v41 = ExceptionList;
  v4 = alloca(7812);
  `eh vector constructor iterator'(
    ptr,
    0x510u,
    6,
    (void (__thiscall *)(void *))idFixedWinding::idFixedWinding,
    (void (__thiscall *)(void *))idFixedWinding::~idFixedWinding);
  v5 = numPlanes;
  v43 = 0;
  if ( numPlanes > 6 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_PolytopeSurface: more than %d planes",
      6);
  numVerts = 0;
  numIndexes = 0;
  v33 = 0;
  if ( numPlanes > 0 )
  {
    v6 = planes;
    v7 = (idWinding *)ptr;
    for ( i = (const idPlane *)planes; ; v6 = (const idVec3 *)i )
    {
      dist = -v6[1].x;
      idWinding::BaseForPlane(v7, v6, dist);
      p_z = &planes->z;
      for ( j = 0; j < numPlanes; ++j )
      {
        if ( j != v33 )
        {
          v10 = -p_z[1];
          v11 = -*p_z;
          v12 = -*(p_z - 1);
          plane.a = -*(p_z - 2);
          plane.b = v12;
          plane.c = v11;
          plane.d = v10;
          if ( !idWinding::ClipInPlace(v7, &plane, 0.1, 0) )
            break;
        }
        p_z += 4;
      }
      if ( v7->numPoints > 2 )
      {
        numPoints = v7->numPoints;
        numVerts += numPoints;
        numIndexes = numPoints + numIndexes - 2 + 2 * numPoints - 4;
      }
      ++i;
      v7 += 81;
      if ( ++v33 >= numPlanes )
        break;
    }
    v5 = numPlanes;
  }
  v14 = R_AllocStaticTriSurf();
  R_AllocStaticTriSurfVerts(v14, numVerts);
  R_AllocStaticTriSurfIndexes(v14, numIndexes);
  v34 = 0;
  if ( v5 > 0 )
  {
    v15 = &v40;
    do
    {
      if ( *(_DWORD *)v15 )
      {
        v16 = 0;
        if ( *(int *)v15 > 0 )
        {
          numIndexesa = 0;
          do
          {
            v17 = (int)&v14->verts[v16 + v14->numVerts];
            *(_DWORD *)(v17 + 8) = 0;
            *(_DWORD *)(v17 + 4) = 0;
            *(_DWORD *)v17 = 0;
            *(_DWORD *)(v17 + 60) = 0;
            *(_DWORD *)(v17 + 56) = 0;
            *(_DWORD *)(v17 + 24) = 0;
            *(_DWORD *)(v17 + 20) = 0;
            *(_DWORD *)(v17 + 16) = 0;
            *(_DWORD *)(v17 + 40) = 0;
            *(_DWORD *)(v17 + 36) = 0;
            *(_DWORD *)(v17 + 32) = 0;
            *(_DWORD *)(v17 + 52) = 0;
            *(_DWORD *)(v17 + 48) = 0;
            *(_DWORD *)(v17 + 44) = 0;
            *(_BYTE *)(v17 + 15) = 0;
            *(_BYTE *)(v17 + 14) = 0;
            *(_BYTE *)(v17 + 13) = 0;
            *(_BYTE *)(v17 + 12) = 0;
            v18 = (_DWORD *)(numIndexesa + *((_DWORD *)v15 + 1));
            numIndexesa += 20;
            p_x = (_DWORD *)&v14->verts[v16 + v14->numVerts].xyz.x;
            ++v16;
            *p_x = *v18;
            p_x[1] = v18[1];
            p_x[2] = v18[2];
          }
          while ( v16 < *(_DWORD *)v15 );
        }
        for ( k = 1; k < *(_DWORD *)v15 - 1; ++k )
        {
          v14->indexes[v14->numIndexes] = v14->numVerts;
          v14->indexes[v14->numIndexes + 1] = k + v14->numVerts;
          v14->indexes[v14->numIndexes + 2] = v14->numVerts + k + 1;
          v14->numIndexes += 3;
        }
        v14->numVerts += *(_DWORD *)v15;
        if ( windings )
        {
          v21 = (idWinding *)Memory::Allocate(0x10u);
          LOBYTE(v43) = 1;
          if ( v21 )
          {
            v22 = *(_DWORD *)v15;
            v23 = *(_DWORD *)v15 <= 0;
            v21->__vftable = (idWinding_vtbl *)&idWinding::`vftable';
            v21->allocedSize = 0;
            v21->numPoints = 0;
            v21->p = 0;
            if ( !v23 )
              idWinding::ReAllocate(v21, v22, 0);
          }
          else
          {
            v21 = 0;
          }
          windings[v34] = v21;
          v24 = *(_DWORD *)v15;
          v23 = *(_DWORD *)v15 <= v21->allocedSize;
          numIndexesb = (int)v21;
          LOBYTE(v43) = 0;
          if ( v23 || v21->ReAllocate(v21, v24, 0) )
          {
            numVertsa = 0;
            if ( *(int *)v15 > 0 )
            {
              v25 = 0;
              do
              {
                v26 = (_DWORD *)(v25 * 20 + *((_DWORD *)v15 + 1));
                v27 = (_DWORD *)&v21->p[v25].x;
                *v27 = *v26;
                v27[1] = v26[1];
                v27[2] = v26[2];
                v27[3] = v26[3];
                v21 = (idWinding *)numIndexesb;
                v27[4] = v26[4];
                ++v25;
                ++numVertsa;
              }
              while ( numVertsa < *(_DWORD *)v15 );
            }
            v21->numPoints = *(_DWORD *)v15;
          }
          else
          {
            v21->numPoints = 0;
          }
        }
      }
      v15 += 1296;
      ++v34;
    }
    while ( v34 < numPlanes );
  }
  R_BoundTriSurf(v14);
  v43 = -1;
  `eh vector destructor iterator'(ptr, 0x510u, 6, (void (__thiscall *)(void *))idFixedWinding::~idFixedWinding);
  return v14;
}
