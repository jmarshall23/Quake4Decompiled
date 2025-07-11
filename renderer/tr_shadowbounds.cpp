
// FUNC: class idVec3 __cdecl homogeneous_difference(class idVec4,class idVec4)
idVec3 *__cdecl homogeneous_difference(idVec3 *result, idVec4 a, idVec4 b)
{
  idVec3 *v3; // eax
  idVec3 v; // [esp+0h] [ebp-Ch]

  v3 = result;
  v.x = a.w * b.x - b.w * a.x;
  v.y = b.y * a.w - a.y * b.w;
  v.z = b.z * a.w - a.z * b.w;
  *result = v;
  return v3;
}

// FUNC: class idVec4 __cdecl compute_homogeneous_plane(class idVec4,class idVec4,class idVec4)
idVec4 *__cdecl compute_homogeneous_plane(idVec4 *result, idVec4 a, idVec4 b, idVec4 c)
{
  float w; // ebx
  float y; // edi
  float z; // esi
  float x; // ebp
  float v8; // edx
  float v9; // ecx
  float v10; // ecx
  float v11; // ecx
  float v12; // ecx
  float v13; // eax
  float v14; // eax
  float v15; // ecx
  double v16; // st7
  double v17; // st6
  double v18; // st5
  long double v19; // st4
  long double v20; // st4
  idVec4 *v21; // eax
  idVec4 v22; // [esp-30h] [ebp-4Ch]
  idVec4 v23; // [esp-30h] [ebp-4Ch]
  idVec4 v24; // [esp-20h] [ebp-3Ch]
  idVec3 vb; // [esp+0h] [ebp-1Ch] BYREF
  idVec4 v; // [esp+Ch] [ebp-10h] BYREF

  if ( a.w == 0.0 )
  {
    w = b.w;
    y = b.y;
    z = b.z;
    x = b.x;
    v.y = a.y;
    v.z = a.z;
    v8 = c.x;
    c.x = a.x;
    v.w = a.w;
    v9 = c.y;
    c.y = a.y;
    a.w = b.w;
    b.y = v9;
    v10 = c.z;
    c.z = a.z;
    b.z = v10;
    v11 = c.w;
    c.w = v.w;
    a.x = b.x;
    a.y = y;
    a.z = z;
    if ( b.w == 0.0 )
    {
      x = v8;
      v8 = c.x;
      c.x = b.x;
      v.w = b.w;
      w = v11;
      v12 = c.y;
      v.y = y;
      v13 = y;
      y = b.y;
      c.y = v13;
      v.z = z;
      v14 = z;
      z = b.z;
      a.w = w;
      b.y = v12;
      v15 = c.z;
      c.z = v14;
      b.z = v15;
      v11 = c.w;
      c.w = b.w;
      a.x = x;
      a.y = y;
      a.z = z;
      if ( w == 0.0 )
        goto LABEL_9;
    }
  }
  else
  {
    v11 = b.w;
    v8 = b.x;
    z = a.z;
    y = a.y;
    w = a.w;
    x = a.x;
  }
  *(_QWORD *)&v24.x = __PAIR64__(LODWORD(b.y), LODWORD(v8));
  *(_QWORD *)&v24.z = __PAIR64__(LODWORD(v11), LODWORD(b.z));
  *(_QWORD *)&v22.x = __PAIR64__(LODWORD(y), LODWORD(x));
  *(_QWORD *)&v22.z = __PAIR64__(LODWORD(w), LODWORD(z));
  homogeneous_difference(&vb, v22, v24);
  *(_QWORD *)&v23.x = __PAIR64__(LODWORD(y), LODWORD(x));
  *(_QWORD *)&v23.z = __PAIR64__(LODWORD(w), LODWORD(z));
  homogeneous_difference((idVec3 *)&v, v23, c);
  v16 = v.z * vb.y - vb.z * v.y;
  v17 = vb.z * v.x - v.z * vb.x;
  v18 = v.y * vb.x - vb.y * v.x;
  v19 = v18 * v18 + v17 * v17 + v16 * v16;
  if ( v19 != 0.0 )
  {
    v20 = 1.0 / sqrt(v19);
    v16 = v16 * v20;
    v17 = v17 * v20;
    v18 = v18 * v20;
  }
  v.x = v16;
  v.y = v17;
  v.z = v18;
  v.w = -((a.z * v18 + a.y * v17 + a.x * v16) / a.w);
LABEL_9:
  v21 = result;
  *result = v;
  return v21;
}

// FUNC: public: void __thiscall polyhedron::discard_neighbor_info(void)
void __thiscall polyhedron::discard_neighbor_info(polyhedron *this)
{
  unsigned int v1; // esi
  int *p_s; // edx
  unsigned int i; // eax

  v1 = 0;
  if ( this->p.s )
  {
    p_s = &this->p.v[0].ni.s;
    do
    {
      for ( i = 0; i < *p_s; ++i )
        p_s[i - 4] = -1;
      ++v1;
      p_s += 14;
    }
    while ( v1 < this->p.s );
  }
}

// FUNC: public: void __thiscall polyhedron::compute_neighbors(void)
void __thiscall polyhedron::compute_neighbors(polyhedron *this)
{
  polyhedron *v1; // ebp
  int v2; // esi
  int s; // edi
  int v4; // ebx
  MyArray<int,4> *p_ni; // eax
  int v6; // ecx
  int v7; // ebp
  int v8; // eax
  poly *v9; // esi
  int v10; // ecx
  int v11; // edi
  int v12; // eax
  int v13; // edx
  int v14; // edi
  edge *v15; // ebp
  int *v16; // [esp+Ch] [ebp-2Ch]
  int i; // [esp+10h] [ebp-28h]
  int ii1; // [esp+14h] [ebp-24h]
  int j; // [esp+1Ch] [ebp-1Ch]
  int Sj; // [esp+20h] [ebp-18h]
  int P; // [esp+24h] [ebp-14h]
  int ii; // [esp+28h] [ebp-10h]
  int v24; // [esp+2Ch] [ebp-Ch]
  int v25; // [esp+30h] [ebp-8h]
  int v26; // [esp+34h] [ebp-4h]

  v1 = this;
  v2 = 0;
  this->e.s = 0;
  polyhedron::discard_neighbor_info(this);
  s = v1->p.s;
  P = s;
  i = 0;
  if ( s - 1 > 0 )
  {
    while ( 1 )
    {
      v4 = (int)&v1->p.v[v2];
      p_ni = &v1->p.v[v2].ni;
      v6 = v1->p.v[v2].vi.s;
      v7 = 0;
      v24 = v6;
      ii = 0;
      if ( v6 > 0 )
      {
        v16 = (int *)p_ni;
        v25 = v4 - (_DWORD)p_ni;
        do
        {
          v26 = v7 + 1;
          ii1 = (v7 + 1) % v24;
          if ( *v16 == -1 )
          {
            v8 = v2 + 1;
            j = v2 + 1;
            if ( v2 + 1 < s )
            {
              v9 = &this->p.v[v8];
              do
              {
                v10 = 0;
                Sj = v9->vi.s;
                if ( Sj > 0 )
                {
                  while ( 1 )
                  {
                    v11 = v10 + 1;
                    v12 = *(_DWORD *)(v4 + 4 * v7);
                    v13 = v9->vi.v[(v10 + 1) % Sj];
                    if ( v12 == v13 )
                    {
                      if ( *(_DWORD *)(v4 + 4 * ii1) == v9->vi.v[v10] )
                      {
                        v14 = *(_DWORD *)(v4 + 4 * ii1);
                        v15 = &this->e.v[this->e.s];
                        v15->vi[0] = *(int *)((char *)v16 + v25);
                        v15->vi[1] = v14;
                        v15->pi[0] = i;
                        v15->pi[1] = j;
                        ++this->e.s;
                        *v16 = j;
                        v9->ni.v[v10] = i;
                        s = P;
                        goto LABEL_21;
                      }
                      v7 = ii;
                    }
                    if ( v12 == v9->vi.v[v10] && *(_DWORD *)(v4 + 4 * ii1) == v13 )
                      fprintf(&stru_103E23C0, "why am I here?\n");
                    v10 = v11;
                    if ( v11 >= Sj )
                    {
                      s = P;
                      v8 = j;
                      break;
                    }
                  }
                }
                ++v8;
                ++v9;
                j = v8;
              }
              while ( v8 < s );
LABEL_21:
              v2 = i;
            }
          }
          v7 = v26;
          ++v16;
          ii = v26;
        }
        while ( v26 < v24 );
      }
      i = ++v2;
      if ( v2 >= s - 1 )
        break;
      v1 = this;
    }
  }
}

// FUNC: public: void __thiscall polyhedron::recompute_planes(void)
void __thiscall polyhedron::recompute_planes(polyhedron *this)
{
  unsigned int v2; // ebx
  int *v3; // esi
  idVec4 result; // [esp+Ch] [ebp-10h] BYREF

  v2 = 0;
  if ( this->p.s )
  {
    v3 = &this->p.v[0].vi.v[1];
    do
    {
      *(idVec4 *)(v3 + 9) = *compute_homogeneous_plane(&result, this->v.v[*(v3 - 1)], this->v.v[*v3], this->v.v[v3[1]]);
      ++v2;
      v3 += 14;
    }
    while ( v2 < this->p.s );
  }
}

// FUNC: public: void __thiscall polyhedron::transform(class idMat4 const &)
void __thiscall polyhedron::transform(polyhedron *this, const idMat4 *m)
{
  unsigned int v2; // esi
  float *p_z; // edx
  double v4; // st7
  double v5; // st7
  double v6; // st6
  float v7; // [esp+4h] [ebp-10h]
  float v8; // [esp+8h] [ebp-Ch]
  float v9; // [esp+Ch] [ebp-8h]
  float v10; // [esp+10h] [ebp-4h]

  v2 = 0;
  if ( this->v.s )
  {
    p_z = &this->v.v[0].z;
    do
    {
      ++v2;
      v4 = *(p_z - 1) * m->mat[0].y;
      p_z += 4;
      v7 = v4 + *(p_z - 4) * m->mat[0].z + *(p_z - 3) * m->mat[0].w + *(p_z - 6) * m->mat[0].x;
      v8 = *(p_z - 5) * m->mat[1].y + m->mat[1].z * *(p_z - 4) + *(p_z - 6) * m->mat[1].x + *(p_z - 3) * m->mat[1].w;
      v9 = *(p_z - 3) * m->mat[2].w + *(p_z - 6) * m->mat[2].x + *(p_z - 4) * m->mat[2].z + *(p_z - 5) * m->mat[2].y;
      v5 = *(p_z - 5) * m->mat[3].y + *(p_z - 3) * m->mat[3].w + m->mat[3].x * *(p_z - 6);
      v6 = *(p_z - 4) * m->mat[3].z;
      *(p_z - 6) = v7;
      *(p_z - 5) = v8;
      *(p_z - 4) = v9;
      v10 = v5 + v6;
      *(p_z - 3) = v10;
    }
    while ( v2 < this->v.s );
  }
  polyhedron::recompute_planes(this);
}

// FUNC: void __cdecl polyhedron_edges(struct polyhedron &,struct MyArray<class idVec4,36> &)
void __cdecl polyhedron_edges(polyhedron *a, MyArray<idVec4,36> *e)
{
  unsigned int v2; // edx
  int *v3; // ecx
  _DWORD *p_x; // eax
  _DWORD *v5; // ebx
  _DWORD *v6; // ebx
  _DWORD *v7; // eax

  e->s = 0;
  if ( !a->e.s && a->p.s )
    polyhedron::compute_neighbors(a);
  v2 = 0;
  if ( a->e.s )
  {
    v3 = &a->e.v[0].vi[1];
    do
    {
      p_x = (_DWORD *)&a->v.v[*(v3 - 1)].x;
      v5 = (_DWORD *)&e->v[e->s].x;
      *v5 = *p_x;
      v5[1] = p_x[1];
      v5[2] = p_x[2];
      v5[3] = p_x[3];
      ++e->s;
      v6 = (_DWORD *)&a->v.v[*v3].x;
      v7 = (_DWORD *)&e->v[e->s].x;
      *v7 = *v6;
      v7[1] = v6[1];
      v7[2] = v6[2];
      v7[3] = v6[3];
      ++e->s;
      ++v2;
      v3 += 4;
    }
    while ( v2 < a->e.s );
  }
}

// FUNC: void __cdecl clip_segments(struct polyhedron const &,struct MyArray<class idVec4,36> &,struct MyArray<class idVec4,36> &)
void __cdecl clip_segments(const polyhedron *ph, MyArray<idVec4,36> *is, MyArray<idVec4,36> *os)
{
  MyArray<idVec4,36> *v3; // eax
  float x; // edx
  float z; // esi
  float w; // ecx
  float *p_x; // eax
  float v8; // esi
  float v9; // edi
  float v10; // ebx
  float v11; // ebp
  float *p_z; // ecx
  int v13; // eax
  double v14; // st7
  double v15; // st5
  double v16; // st7
  double v17; // st5
  float *v18; // eax
  float *v19; // eax
  float a; // [esp+0h] [ebp-E0h]
  float a_4; // [esp+4h] [ebp-DCh]
  float a_8; // [esp+8h] [ebp-D8h]
  float a_12; // [esp+Ch] [ebp-D4h]
  float rdw; // [esp+10h] [ebp-D0h]
  float db; // [esp+14h] [ebp-CCh]
  float da; // [esp+18h] [ebp-C8h]
  int code; // [esp+1Ch] [ebp-C4h]
  MyArray<idVec4,36> *k; // [esp+20h] [ebp-C0h]
  float *v29; // [esp+24h] [ebp-BCh]
  float b; // [esp+28h] [ebp-B8h]
  float b_4; // [esp+2Ch] [ebp-B4h]
  float b_8; // [esp+30h] [ebp-B0h]
  float b_12; // [esp+34h] [ebp-ACh]
  unsigned int j; // [esp+38h] [ebp-A8h]
  unsigned int i; // [esp+3Ch] [ebp-A4h]
  float v36; // [esp+40h] [ebp-A0h]
  float v37; // [esp+44h] [ebp-9Ch]
  float v38; // [esp+48h] [ebp-98h]
  float v39; // [esp+4Ch] [ebp-94h]
  float v40; // [esp+70h] [ebp-70h]
  float v41; // [esp+74h] [ebp-6Ch]
  float v42; // [esp+78h] [ebp-68h]
  float v43; // [esp+7Ch] [ebp-64h]
  float v44; // [esp+90h] [ebp-50h]
  float v45; // [esp+94h] [ebp-4Ch]
  float v46; // [esp+98h] [ebp-48h]
  float v47; // [esp+9Ch] [ebp-44h]
  float v48; // [esp+A0h] [ebp-40h]
  float v49; // [esp+A4h] [ebp-3Ch]
  float v50; // [esp+A8h] [ebp-38h]
  float v51; // [esp+ACh] [ebp-34h]
  float v52; // [esp+C4h] [ebp-1Ch]
  float v53; // [esp+C8h] [ebp-18h]
  float v54; // [esp+CCh] [ebp-14h]
  float v55; // [esp+D4h] [ebp-Ch]
  float v56; // [esp+D8h] [ebp-8h]
  float v57; // [esp+DCh] [ebp-4h]

  v3 = is;
  i = 0;
  if ( is->s )
  {
    for ( k = is; ; v3 = k )
    {
      x = v3->v[0].x;
      a_4 = v3->v[0].y;
      z = v3->v[0].z;
      w = v3->v[0].w;
      p_x = &v3->v[1].x;
      a_8 = z;
      v8 = *p_x;
      v9 = p_x[1];
      v10 = p_x[2];
      v11 = p_x[3];
      a_12 = w;
      a = x;
      b = *p_x;
      b_4 = v9;
      b_8 = v10;
      b_12 = v11;
      j = 0;
      if ( ph->p.s )
      {
        p_z = &ph->p.v[0].plane.z;
        v29 = &ph->p.v[0].plane.z;
        while ( 1 )
        {
          code = 0;
          da = a_4 * *(p_z - 1) + a_12 * p_z[1] + a * *(p_z - 2) + a_8 * *p_z;
          db = b_4 * *(p_z - 1) + b_12 * p_z[1] + b * *(p_z - 2) + b_8 * *p_z;
          rdw = 1.0 / (da - db);
          if ( da > 0.0 )
            code = 2;
          v13 = code;
          if ( db > 0.0 )
            LOBYTE(v13) = code | 1;
          switch ( v13 )
          {
            case 0:
              goto $L113985;
            case 1:
              v16 = rdw * da;
              v55 = v9 * v16;
              v56 = v10 * v16;
              v57 = v11 * v16;
              v17 = -(rdw * db);
              v40 = x * v17;
              v41 = a_4 * v17;
              v42 = a_8 * v17;
              v43 = a_12 * v17;
              v44 = v40 + v8 * v16;
              v8 = v44;
              b = v44;
              v45 = v41 + v55;
              v9 = v45;
              b_4 = v45;
              v46 = v42 + v56;
              v10 = v46;
              b_8 = v46;
              v47 = v43 + v57;
              v11 = v47;
              b_12 = v47;
              goto $L113985;
            case 2:
              v14 = rdw * da;
              v52 = v9 * v14;
              v53 = v10 * v14;
              v54 = v11 * v14;
              v15 = -(rdw * db);
              v48 = x * v15;
              v49 = a_4 * v15;
              v50 = a_8 * v15;
              v51 = a_12 * v15;
              v36 = v48 + v8 * v14;
              a = v36;
              v37 = v49 + v52;
              a_4 = v37;
              v38 = v50 + v53;
              a_8 = v38;
              v39 = v51 + v54;
              a_12 = v39;
              goto LABEL_15;
            case 3:
              goto $L113968;
            default:
              (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                common.type,
                "bad clip code!\n");
              p_z = v29;
LABEL_15:
              x = a;
$L113985:
              v29 = p_z + 14;
              if ( ++j >= ph->p.s )
                goto LABEL_17;
              p_z += 14;
              break;
          }
        }
      }
LABEL_17:
      v18 = &os->v[os->s].x;
      *v18 = x;
      v18[1] = a_4;
      v18[2] = a_8;
      v18[3] = a_12;
      v19 = &os->v[++os->s].x;
      *v19 = v8;
      v19[1] = v9;
      v19[2] = v10;
      v19[3] = v11;
      ++os->s;
$L113968:
      k = (MyArray<idVec4,36> *)((char *)k + 32);
      i += 2;
      if ( i >= is->s )
        break;
    }
  }
}

// FUNC: class idMat4 __cdecl make_idMat4(float const *)
idMat4 *__cdecl make_idMat4(idMat4 *result, float *m)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st4
  double v6; // st3
  double v7; // st2
  double v8; // st1
  float v9; // edx
  idMat4 *v10; // eax
  float v11; // [esp+4h] [ebp-1Ch]
  float v12; // [esp+8h] [ebp-18h]
  idVec4 v13; // [esp+Ch] [ebp-14h]
  float v14; // [esp+1Ch] [ebp-4h]

  v2 = m[15];
  v3 = m[11];
  v4 = m[7];
  v14 = m[2];
  v5 = m[3];
  v6 = m[14];
  v13.w = m[13];
  v7 = m[10];
  v8 = m[6];
  v13.z = m[9];
  v13.y = m[5];
  v13.x = m[1];
  v12 = m[12];
  v9 = m[4];
  v11 = m[8];
  v10 = result;
  result->mat[0].x = *m;
  result->mat[0].y = v9;
  result->mat[0].z = v11;
  result->mat[0].w = v12;
  result->mat[1] = v13;
  result->mat[2].x = v14;
  result->mat[2].y = v8;
  result->mat[2].z = v7;
  result->mat[2].w = v6;
  result->mat[3].x = v5;
  result->mat[3].y = v4;
  result->mat[3].z = v3;
  result->mat[3].w = v2;
  return v10;
}

// FUNC: void __cdecl draw_polyhedron(struct viewDef_s const *,struct polyhedron const &,class idVec4)
void __cdecl draw_polyhedron(const viewDef_s *viewDef, const polyhedron *p, idVec4 color)
{
  unsigned int v4; // ebx
  MyArray<edge,15> *p_e; // edi
  int v6; // eax
  double v7; // st7
  float *v8; // eax
  idRenderWorldLocal *renderWorld; // ecx
  double v10; // st7
  double v11; // st6
  double v12; // st5
  float *p_x; // eax
  double v14; // st7
  double v15; // st7
  double v16; // st6
  float v17[3]; // [esp+8h] [ebp-18h] BYREF
  float v18[3]; // [esp+14h] [ebp-Ch] BYREF
  float pa; // [esp+28h] [ebp+8h]
  float pb; // [esp+28h] [ebp+8h]

  v4 = 0;
  if ( p->e.s )
  {
    p_e = &p->e;
    do
    {
      v6 = p_e->v[0].vi[1];
      v7 = 1.0 / p->v.v[v6].w;
      v8 = (float *)((char *)p + v6 * 16);
      renderWorld = viewDef->renderWorld;
      pa = v7;
      v10 = v7 * v8[2];
      v11 = pa * v8[1];
      v12 = pa * *v8;
      p_x = &p->v.v[p_e->v[0].vi[0]].x;
      v17[0] = v12;
      v17[1] = v11;
      v17[2] = v10;
      v14 = 1.0 / p_x[3];
      pb = v14;
      v15 = v14 * p_x[2];
      v16 = pb * p_x[1];
      v18[0] = pb * *p_x;
      v18[1] = v16;
      v18[2] = v15;
      renderWorld->DebugLine(renderWorld, &color, (const idVec3 *)v18, (const idVec3 *)v17, 0, 0);
      ++v4;
      p_e = (MyArray<edge,15> *)((char *)p_e + 16);
    }
    while ( v4 < p->e.s );
  }
}

// FUNC: void __cdecl draw_segments(struct viewDef_s const *,struct MyArray<class idVec4,36> const &,class idVec4)
void __cdecl draw_segments(const viewDef_s *viewDef, const MyArray<idVec4,36> *s, idVec4 color)
{
  unsigned int v3; // edi
  float *p_w; // esi
  idRenderWorldLocal *renderWorld; // ecx
  double v6; // st7
  double v7; // st7
  float v8[3]; // [esp+8h] [ebp-18h] BYREF
  float v9[3]; // [esp+14h] [ebp-Ch] BYREF

  v3 = 0;
  if ( s->s )
  {
    p_w = &s->v[1].w;
    do
    {
      renderWorld = viewDef->renderWorld;
      v6 = 1.0 / *p_w;
      v8[0] = v6 * *(p_w - 3);
      v8[1] = v6 * *(p_w - 2);
      v8[2] = v6 * *(p_w - 1);
      v7 = 1.0 / *(p_w - 4);
      v9[0] = v7 * *(p_w - 7);
      v9[1] = v7 * *(p_w - 6);
      v9[2] = v7 * *(p_w - 5);
      renderWorld->DebugLine(renderWorld, &color, (const idVec3 *)v9, (const idVec3 *)v8, 0, 0);
      v3 += 2;
      p_w += 8;
    }
    while ( v3 < s->s );
  }
}

// FUNC: void __cdecl world_to_hclip(struct viewDef_s const *,class idVec4 const &,class idVec4 &)
void __cdecl world_to_hclip(const viewDef_s *viewDef, const idVec4 *global, idVec4 *clip)
{
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st4

  v3 = viewDef->worldSpace.modelViewMatrix[4] * global->y
     + viewDef->worldSpace.modelViewMatrix[0] * global->x
     + viewDef->worldSpace.modelViewMatrix[12] * global->w
     + viewDef->worldSpace.modelViewMatrix[8] * global->z;
  v4 = viewDef->worldSpace.modelViewMatrix[5] * global->y
     + viewDef->worldSpace.modelViewMatrix[1] * global->x
     + viewDef->worldSpace.modelViewMatrix[13] * global->w
     + viewDef->worldSpace.modelViewMatrix[9] * global->z;
  v5 = viewDef->worldSpace.modelViewMatrix[6] * global->y
     + viewDef->worldSpace.modelViewMatrix[2] * global->x
     + viewDef->worldSpace.modelViewMatrix[14] * global->w
     + viewDef->worldSpace.modelViewMatrix[10] * global->z;
  v6 = viewDef->worldSpace.modelViewMatrix[7] * global->y
     + viewDef->worldSpace.modelViewMatrix[3] * global->x
     + viewDef->worldSpace.modelViewMatrix[15] * global->w
     + viewDef->worldSpace.modelViewMatrix[11] * global->z;
  clip->x = v3 * viewDef->projectionMatrix[0]
          + v4 * viewDef->projectionMatrix[4]
          + v5 * viewDef->projectionMatrix[8]
          + v6 * viewDef->projectionMatrix[12];
  clip->y = v3 * viewDef->projectionMatrix[1]
          + v4 * viewDef->projectionMatrix[5]
          + v5 * viewDef->projectionMatrix[9]
          + v6 * viewDef->projectionMatrix[13];
  clip->z = v3 * viewDef->projectionMatrix[2]
          + v4 * viewDef->projectionMatrix[6]
          + v5 * viewDef->projectionMatrix[10]
          + v6 * viewDef->projectionMatrix[14];
  clip->w = v3 * viewDef->projectionMatrix[3]
          + v4 * viewDef->projectionMatrix[7]
          + v5 * viewDef->projectionMatrix[11]
          + v6 * viewDef->projectionMatrix[15];
}

// FUNC: public: void __thiscall polyhedron::add_quad(int,int,int,int)
void __thiscall polyhedron::add_quad(polyhedron *this, int va, int vb, int vc, int vd)
{
  MyArray<int,4> *v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int s; // edx
  MyArray<int,4> *v11; // eax
  int v12; // edx
  int v13; // edx
  int v14; // eax
  idVec4 *v15; // esi
  float x; // edx
  idVec4 *v17; // eax
  float y; // ecx
  float z; // edx
  float w; // eax
  poly *v21; // edi
  idVec4 v22; // [esp-10h] [ebp-6Ch]
  MyArray<int,4> result; // [esp+10h] [ebp-4Ch] BYREF
  poly pg; // [esp+24h] [ebp-38h] BYREF

  v6 = four_ints(&result, va, vb, vc, vd);
  v7 = v6->v[1];
  pg.vi.v[0] = v6->v[0];
  v8 = v6->v[2];
  pg.vi.v[1] = v7;
  v9 = v6->v[3];
  pg.vi.v[2] = v8;
  s = v6->s;
  pg.vi.v[3] = v9;
  pg.vi.s = s;
  v11 = four_ints(&result, -1, -1, -1, -1);
  v12 = v11->v[1];
  pg.ni.v[0] = v11->v[0];
  pg.ni.v[2] = v11->v[2];
  pg.ni.v[1] = v12;
  v13 = v11->v[3];
  v14 = v11->s;
  pg.ni.v[3] = v13;
  v15 = &this->v.v[vc];
  x = v15->x;
  pg.ni.s = v14;
  v22.x = x;
  v22.y = v15->y;
  *(_QWORD *)&v22.z = *(_QWORD *)&v15->z;
  v17 = compute_homogeneous_plane((idVec4 *)&result, this->v.v[va], this->v.v[vb], v22);
  y = v17->y;
  pg.plane.x = v17->x;
  z = v17->z;
  w = v17->w;
  pg.plane.y = y;
  pg.plane.w = w;
  v21 = &this->p.v[this->p.s];
  pg.plane.z = z;
  qmemcpy(v21, &pg, sizeof(poly));
  ++this->p.s;
}

// FUNC: struct polyhedron __cdecl make_sv(struct polyhedron const &,class idVec4)
// local variable allocation has failed, the output may be wrong!
polyhedron *__cdecl make_sv(polyhedron *result, const polyhedron *oc, idVec4 light)
{
  int v3; // ebx
  int *p_s; // esi
  int v5; // edi
  int v6; // ecx
  int v7; // ebp
  bool v8; // zf
  polyhedron *v9; // ebp
  int v10; // ecx
  int v11; // edx
  unsigned int v12; // esi
  idVec4 *v13; // eax
  float z; // ebx
  double v15; // st7
  idVec4 *v16; // edi
  float v17; // ebx
  int v18; // ecx
  double v19; // st7
  idVec4 *v20; // ecx
  float v21; // ebx
  int v22; // ecx
  idVec4 *v23; // ecx
  double v24; // st7
  int v25; // ecx
  float v26; // edi
  idVec4 *v27; // ecx
  idVec4 *v28; // eax
  int v29; // ecx
  float v30; // edi
  idVec4 *v31; // esi
  float *p_z; // edx
  int v34; // ecx
  polyhedron *p_vpg; // eax
  int v36; // edx
  float *v37; // edx
  float v38; // edi
  float v39; // edx
  int v40; // eax
  MyArray<edge,15> *p_e; // ebp
  int v42; // ecx
  MyArray<edge,15> *v43; // eax
  int v44; // edx
  int v45; // esi
  char *v46; // esi
  int v47; // eax
  int v48; // ecx
  signed int v49; // eax
  int v50; // ecx
  int *v51; // ebx
  int v52; // edx
  int k; // eax
  int m; // eax
  polyhedron *v55; // edx
  int v56; // ebx
  int v57; // eax
  char *v58; // ebp
  int v59; // ecx
  polyhedron *v60; // eax
  int v61; // edx
  float *v62; // edx
  float v63; // edi
  float v64; // edx
  int v65; // ecx
  MyArray<edge,15> *v66; // eax
  int v67; // edx
  int v68; // esi
  int v69; // ecx
  int v70; // edx
  int v71; // esi
  unsigned int v72; // esi
  idVec4 *v73; // eax
  float v74; // ebp
  idVec4 *v75; // ecx
  double v76; // st7
  float v77; // ebp
  double v78; // st7
  idVec4 *v79; // ecx
  float v80; // ebp
  idVec4 *v81; // ecx
  float v82; // edi
  idVec4 *v83; // ecx
  int v84; // edx
  idVec4 *v85; // eax
  float v86; // ebp
  idVec4 *v87; // ecx
  int v88; // ecx
  int v89; // eax
  char *v90; // esi
  float v91; // edx
  int v92; // eax
  char *v93; // edx
  int v94; // ecx
  polyhedron *v95; // eax
  float x; // [esp+10h] [ebp-8A0h]
  float y; // [esp+14h] [ebp-89Ch]
  float v98; // [esp+18h] [ebp-898h]
  float w; // [esp+1Ch] [ebp-894h]
  int v100; // [esp+20h] [ebp-890h]
  idVec3 v101; // [esp+24h] [ebp-88Ch]
  idVec4 v102; // [esp+30h] [ebp-880h]
  int v103; // [esp+40h] [ebp-870h]
  idVec3 v104; // [esp+44h] [ebp-86Ch]
  int v105; // [esp+50h] [ebp-860h]
  int v106; // [esp+54h] [ebp-85Ch]
  idVec3 proj; // [esp+58h] [ebp-858h] BYREF
  int v108; // [esp+64h] [ebp-84Ch]
  int v109; // [esp+68h] [ebp-848h]
  int j; // [esp+6Ch] [ebp-844h]
  unsigned int i; // [esp+70h] [ebp-840h]
  MyArray<poly,9> *p_p; // [esp+74h] [ebp-83Ch]
  int n; // [esp+78h] [ebp-838h]
  int S; // [esp+7Ch] [ebp-834h]
  int v115; // [esp+80h] [ebp-830h]
  poly pg; // [esp+84h] [ebp-82Ch] BYREF
  polyhedron vpg; // [esp+BCh] [ebp-7F4h] OVERLAPPED BYREF
  char v118[256]; // [esp+4B0h] [ebp-400h] BYREF
  int v119; // [esp+5B0h] [ebp-300h]
  MyArray<poly,9> v120; // [esp+5B4h] [ebp-2FCh] BYREF
  char v121[240]; // [esp+7B0h] [ebp-100h] BYREF
  int v122; // [esp+8A0h] [ebp-10h]
  int v123; // [esp+8ACh] [ebp-4h]

  v3 = 0;
  if ( (_S4_30 & 1) == 0 )
  {
    _S4_30 |= 1u;
    v123 = 0;
    p_s = &lut[0].v.s;
    v5 = 64;
    do
    {
      `vector constructor iterator'((char *)p_s - 256, 0x10u, 16, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
      *p_s = 0;
      `vector constructor iterator'((char *)p_s + 4, 0x38u, 9, (void *(__thiscall *)(void *))poly::poly);
      p_s[127] = 0;
      p_s[188] = 0;
      p_s += 253;
      --v5;
    }
    while ( v5 );
  }
  v6 = light.y * oc->p.v[0].plane.y
     + light.z * oc->p.v[0].plane.z
     + light.w * oc->p.v[0].plane.w
     + light.x * oc->p.v[0].plane.x > 0.0;
  if ( light.y * oc->p.v[1].plane.y
     + light.z * oc->p.v[1].plane.z
     + light.w * oc->p.v[1].plane.w
     + light.x * oc->p.v[1].plane.x > 0.0 )
    v6 |= 2u;
  if ( light.y * oc->p.v[2].plane.y
     + light.z * oc->p.v[2].plane.z
     + light.w * oc->p.v[2].plane.w
     + light.x * oc->p.v[2].plane.x > 0.0 )
    v6 |= 4u;
  if ( light.y * oc->p.v[3].plane.y
     + light.z * oc->p.v[3].plane.z
     + light.w * oc->p.v[3].plane.w
     + light.x * oc->p.v[3].plane.x > 0.0 )
    v6 |= 8u;
  if ( light.y * oc->p.v[4].plane.y
     + light.z * oc->p.v[4].plane.z
     + light.w * oc->p.v[4].plane.w
     + light.x * oc->p.v[4].plane.x > 0.0 )
    v6 |= 0x10u;
  if ( light.y * oc->p.v[5].plane.y
     + light.z * oc->p.v[5].plane.z
     + light.w * oc->p.v[5].plane.w
     + light.x * oc->p.v[5].plane.x > 0.0 )
    v6 |= 0x20u;
  v7 = 1012 * v6;
  v8 = lut[v6].e.s == 0;
  n = 1012 * v6;
  if ( v8 )
  {
    v9 = (polyhedron *)((char *)lut + v7);
    qmemcpy(v9, oc, sizeof(polyhedron));
    v11 = 0;
    v115 = v9->v.s;
    v10 = v115;
    if ( v115 >= 4 )
    {
      v102 = light;
      v12 = ((unsigned int)(v115 - 4) >> 2) + 1;
      v105 = 0;
      j = 4 * v12;
      v13 = &v9->v.v[2];
      do
      {
        x = v13[-2].x;
        y = v13[-2].y;
        z = v13[-2].z;
        w = v13[-2].w;
        v98 = z;
        v101.x = v102.w * x - w * v102.x;
        v101.y = y * v102.w - v102.y * w;
        v101.z = z * v102.w - v102.z * w;
        proj = v101;
        v15 = v102.w;
        v104 = v101;
        v16 = &v9->v.v[v9->v.s];
        v16->x = v101.x;
        *(_QWORD *)&v16->y = *(_QWORD *)&v104.y;
        v16->w = 0.0;
        ++v9->v.s;
        x = v13[-1].x;
        y = v13[-1].y;
        v17 = v13[-1].z;
        w = v13[-1].w;
        v18 = v9->v.s;
        v98 = v17;
        v101.x = v15 * x - w * v102.x;
        v101.y = y * v102.w - v102.y * w;
        v101.z = v17 * v102.w - v102.z * w;
        v19 = v102.w;
        proj = v101;
        v104 = v101;
        v20 = &v9->v.v[v18];
        v20->x = v101.x;
        *(_QWORD *)&v20->y = *(_QWORD *)&v104.y;
        v20->w = 0.0;
        ++v9->v.s;
        x = v13->x;
        y = v13->y;
        v21 = v13->z;
        w = v13->w;
        v22 = v9->v.s;
        v98 = v21;
        v23 = &v9->v.v[v22];
        v101.x = v19 * x - w * v102.x;
        v101.y = y * v102.w - v102.y * w;
        v101.z = v21 * v102.w - v102.z * w;
        proj = v101;
        v24 = v102.w;
        v104 = v101;
        v23->x = v101.x;
        *(_QWORD *)&v23->y = *(_QWORD *)&v104.y;
        v23->w = 0.0;
        v25 = ++v9->v.s;
        x = v13[1].x;
        y = v13[1].y;
        v26 = v13[1].w;
        v98 = v13[1].z;
        w = v26;
        v27 = &v9->v.v[v25];
        v13 += 4;
        v101.x = v24 * x - v26 * v102.x;
        v101.y = y * v102.w - v102.y * v26;
        v101.z = v98 * v102.w - v102.z * v26;
        proj = v101;
        v104 = v101;
        v27->x = v101.x;
        *(_QWORD *)&v27->y = *(_QWORD *)&v104.y;
        v27->w = 0.0;
        ++v9->v.s;
        --v12;
      }
      while ( v12 );
      v10 = v115;
      v11 = j;
    }
    if ( v11 < v10 )
    {
      v102 = light;
      v28 = &v9->v.v[v11];
      v105 = 0;
      v29 = v10 - v11;
      do
      {
        x = v28->x;
        y = v28->y;
        v30 = v28->z;
        w = v28->w;
        v98 = v30;
        ++v28;
        v101.x = v102.w * x - w * v102.x;
        v101.y = y * v102.w - v102.y * w;
        v101.z = v30 * v102.w - v102.z * w;
        proj = v101;
        v104 = v101;
        v31 = &v9->v.v[v9->v.s];
        v31->x = v101.x;
        *(_QWORD *)&v31->y = *(_QWORD *)&v104.y;
        v31->w = 0.0;
        ++v9->v.s;
        --v29;
      }
      while ( v29 );
    }
    v9->p.s = 0;
    v8 = oc->p.s == 0;
    i = 0;
    if ( !v8 )
    {
      p_z = &oc->p.v[0].plane.z;
      do
      {
        if ( light.x * *(p_z - 2) + light.y * *(p_z - 1) + light.w * p_z[1] + light.z * *p_z > 0.0 )
          qmemcpy(&v9->p.v[v9->p.s++], p_z - 12, sizeof(v9->p.v[v9->p.s++]));
        p_z += 14;
      }
      while ( ++i < oc->p.s );
    }
    if ( !v9->p.s )
    {
      vpg.v.s = 0;
      vpg.p.v[0].vi.s = 0;
      vpg.p.v[0].ni.s = 0;
      vpg.p.v[1].vi.s = 0;
      vpg.p.v[1].ni.s = 0;
      vpg.p.v[2].vi.s = 0;
      vpg.p.v[2].ni.s = 0;
      vpg.p.v[3].vi.s = 0;
      vpg.p.v[3].ni.s = 0;
      vpg.p.v[4].vi.s = 0;
      vpg.p.v[4].ni.s = 0;
      vpg.p.v[5].vi.s = 0;
      vpg.p.v[5].ni.s = 0;
      vpg.p.v[6].vi.s = 0;
      vpg.p.v[6].ni.s = 0;
      vpg.p.v[7].vi.s = 0;
      vpg.p.v[7].ni.s = 0;
      vpg.p.v[8].vi.s = 0;
      vpg.p.v[8].ni.s = 0;
      vpg.p.s = 0;
      vpg.e.s = 0;
      qmemcpy(v9, &vpg, sizeof(polyhedron));
      v34 = 0;
      vpg.v.s = v9->v.s;
      if ( vpg.v.s > 0 )
      {
        p_vpg = &vpg;
        v36 = (char *)v9 - (char *)&vpg;
        for ( j = (char *)v9 - (char *)&vpg; ; v36 = j )
        {
          v37 = (float *)((char *)p_vpg + v36);
          p_vpg->v.v[0].x = *v37;
          p_vpg->v.v[0].y = v37[1];
          v38 = v37[2];
          v39 = v37[3];
          p_vpg->v.v[0].z = v38;
          ++v34;
          p_vpg->v.v[0].w = v39;
          p_vpg = (polyhedron *)((char *)p_vpg + 16);
          if ( v34 >= vpg.v.s )
            break;
        }
      }
      MyArray<poly,9>::MyArray<poly,9>(&vpg.p, &v9->p);
      v40 = v9->e.s;
      p_e = &v9->e;
      v42 = 0;
      vpg.e.s = v40;
      if ( v40 > 0 )
      {
        v43 = &vpg.e;
        v44 = (char *)p_e - (char *)&vpg.e;
        do
        {
          v43->v[0].vi[0] = *(int *)((char *)v43->v[0].vi + v44);
          v43->v[0].vi[1] = *(int *)((char *)&v43->v[0].vi[1] + v44);
          v45 = *(int *)((char *)&v43->v[0].pi[1] + v44);
          v43->v[0].pi[0] = *(int *)((char *)v43->v[0].pi + v44);
          ++v42;
          v43->v[0].pi[1] = v45;
          v43 = (MyArray<edge,15> *)((char *)v43 + 16);
        }
        while ( v42 < vpg.e.s );
      }
      v46 = (char *)&vpg;
      goto LABEL_74;
    }
    polyhedron::compute_neighbors(v9);
    v47 = v9->p.s;
    v48 = 0;
    vpg.v.v[1].x = 0.0;
    vpg.v.v[2].y = 0.0;
    vpg.v.v[4].z = 0.0;
    vpg.v.v[5].w = 0.0;
    vpg.v.v[8].x = 0.0;
    vpg.v.v[9].y = 0.0;
    vpg.v.v[11].z = 0.0;
    vpg.v.v[12].w = 0.0;
    vpg.v.v[15].x = 0.0;
    vpg.p.v[0].vi.v[0] = 0;
    vpg.p.v[0].ni.s = 0;
    vpg.p.v[1].vi.v[0] = 0;
    vpg.p.v[1].ni.s = 0;
    vpg.p.v[2].vi.v[0] = 0;
    vpg.p.v[2].ni.s = 0;
    vpg.p.v[3].vi.v[0] = 0;
    vpg.p.v[3].ni.s = 0;
    vpg.p.v[4].vi.v[0] = 0;
    vpg.p.v[4].ni.v[0] = 0;
    if ( v47 > 0 )
    {
      p_p = &v9->p;
      j = v47;
      do
      {
        S = p_p->v[0].vi.s;
        i = 0;
        if ( S > 0 )
        {
          v49 = i;
          v50 = S;
          v51 = (int *)p_p;
          do
          {
            if ( v51[5] == -1 )
            {
              v100 = 4;
              v106 = 4;
              v52 = p_p->v[0].vi.v[(v49 + 1) % v50];
              y = *(float *)v51;
              x = *(float *)&v52;
              LODWORD(v98) = v115 + LODWORD(y);
              LODWORD(w) = v115 + v52;
              for ( k = 0; k < v106; ++k )
                *(&v104.x + k) = *(&x + k);
              pg.vi.v[1] = LODWORD(v104.y);
              pg.vi.v[0] = LODWORD(v104.x);
              pg.vi.v[3] = v105;
              pg.vi.v[2] = LODWORD(v104.z);
              pg.vi.s = v106;
              memset(&proj, 255, sizeof(proj));
              v108 = -1;
              v109 = 4;
              v103 = 4;
              for ( m = 0; m < v103; ++m )
                *((_DWORD *)&v102.x + m) = *((_DWORD *)&proj.x + m);
              *(idVec4 *)pg.ni.v = v102;
              v49 = i;
              pg.ni.s = v103;
              qmemcpy((char *)&vpg + 56 * vpg.p.v[4].ni.v[0]++, &pg, 0x38u);
              v50 = S;
            }
            ++v49;
            ++v51;
            i = v49;
          }
          while ( v49 < v50 );
        }
        p_p = (MyArray<poly,9> *)((char *)p_p + 56);
        --j;
      }
      while ( j );
      v48 = vpg.p.v[4].ni.v[0];
    }
    if ( v48 )
    {
      v55 = &vpg;
      v56 = v48;
      do
      {
        qmemcpy(&v9->p.v[v9->p.s++], v55, sizeof(v9->p.v[v9->p.s++]));
        v55 = (polyhedron *)((char *)v55 + 56);
        --v56;
      }
      while ( v56 );
    }
    polyhedron::compute_neighbors(v9);
    v9->v.s = 0;
    v7 = n;
    v3 = 0;
  }
  v57 = *(_DWORD *)((char *)&lut[0].v.v[16].x + v7);
  v58 = (char *)lut + v7;
  v59 = 0;
  vpg.v.s = v57;
  if ( v57 > 0 )
  {
    v60 = &vpg;
    v61 = v58 - (char *)&vpg;
    for ( n = v58 - (char *)&vpg; ; v61 = n )
    {
      v62 = (float *)((char *)v60 + v61);
      v60->v.v[0].x = *v62;
      v60->v.v[0].y = v62[1];
      v63 = v62[2];
      v64 = v62[3];
      v60->v.v[0].z = v63;
      ++v59;
      v60->v.v[0].w = v64;
      v60 = (polyhedron *)((char *)v60 + 16);
      if ( v59 >= vpg.v.s )
        break;
    }
  }
  MyArray<poly,9>::MyArray<poly,9>(&vpg.p, (const MyArray<poly,9> *)(v58 + 260));
  v65 = 0;
  vpg.e.s = *((_DWORD *)v58 + 252);
  if ( vpg.e.s > 0 )
  {
    v66 = &vpg.e;
    v67 = v58 + 768 - (char *)&vpg.e;
    do
    {
      v66->v[0].vi[0] = *(int *)((char *)v66->v[0].vi + v67);
      v66->v[0].vi[1] = *(int *)((char *)&v66->v[0].vi[1] + v67);
      v68 = *(int *)((char *)&v66->v[0].pi[1] + v67);
      v66->v[0].pi[0] = *(int *)((char *)v66->v[0].pi + v67);
      ++v65;
      v66->v[0].pi[1] = v68;
      v66 = (MyArray<edge,15> *)((char *)v66 + 16);
    }
    while ( v65 < vpg.e.s );
  }
  qmemcpy(&vpg, oc, 0x104u);
  v69 = vpg.v.s;
  v70 = vpg.v.s;
  v71 = 0;
  j = vpg.v.s;
  if ( vpg.v.s >= 4 )
  {
    v105 = 0;
    v102 = light;
    v72 = ((unsigned int)(vpg.v.s - 4) >> 2) + 1;
    n = 4 * v72;
    v73 = &vpg.v.v[2];
    do
    {
      x = v73[-2].x;
      y = v73[-2].y;
      v74 = v73[-2].z;
      w = v73[-2].w;
      v98 = v74;
      v75 = &vpg.v.v[v69];
      proj.x = v102.w * x - w * v102.x;
      proj.y = y * v102.w - v102.y * w;
      proj.z = v74 * v102.w - v102.z * w;
      v101 = proj;
      v76 = v102.w;
      v104 = proj;
      v75->x = proj.x;
      *(_QWORD *)&v75->y = *(_QWORD *)&v104.y;
      v75->w = 0.0;
      ++vpg.v.s;
      x = v73[-1].x;
      y = v73[-1].y;
      v77 = v73[-1].z;
      w = v73[-1].w;
      v98 = v77;
      proj.x = v76 * x - w * v102.x;
      proj.y = y * v102.w - v102.y * w;
      proj.z = v77 * v102.w - v102.z * w;
      v78 = v102.w;
      v101 = proj;
      v104 = proj;
      v79 = &vpg.v.v[vpg.v.s];
      v79->x = proj.x;
      *(_QWORD *)&v79->y = *(_QWORD *)&v104.y;
      v79->w = 0.0;
      ++vpg.v.s;
      x = v73->x;
      y = v73->y;
      v80 = v73->z;
      w = v73->w;
      v98 = v80;
      v81 = &vpg.v.v[vpg.v.s];
      proj.x = v78 * x - w * v102.x;
      proj.y = y * v102.w - v102.y * w;
      proj.z = v80 * v102.w - v102.z * w;
      v101 = proj;
      v104 = proj;
      v81->x = proj.x;
      *(_QWORD *)&v81->y = *(_QWORD *)&v104.y;
      v81->w = 0.0;
      ++vpg.v.s;
      x = v73[1].x;
      y = v73[1].y;
      v82 = v73[1].w;
      v98 = v73[1].z;
      w = v82;
      v83 = &vpg.v.v[vpg.v.s];
      v73 += 4;
      proj.x = v102.w * x - v82 * v102.x;
      proj.y = y * v102.w - v102.y * v82;
      proj.z = v98 * v102.w - v102.z * v82;
      v101 = proj;
      v104 = proj;
      v83->x = proj.x;
      *(_QWORD *)&v83->y = *(_QWORD *)&v104.y;
      v83->w = 0.0;
      v69 = vpg.v.s + 1;
      --v72;
      ++vpg.v.s;
    }
    while ( v72 );
    v71 = n;
    v70 = j;
  }
  if ( v71 < v70 )
  {
    v102 = light;
    v105 = 0;
    v84 = v70 - v71;
    v85 = &vpg.v.v[v71];
    do
    {
      x = v85->x;
      y = v85->y;
      v86 = v85->z;
      w = v85->w;
      v98 = v86;
      v87 = &vpg.v.v[v69];
      ++v85;
      proj.x = v102.w * x - w * v102.x;
      proj.y = y * v102.w - v102.y * w;
      proj.z = v86 * v102.w - v102.z * w;
      v101 = proj;
      v104 = proj;
      v87->x = proj.x;
      *(_QWORD *)&v87->y = *(_QWORD *)&v104.y;
      v87->w = 0.0;
      v69 = vpg.v.s + 1;
      --v84;
      ++vpg.v.s;
    }
    while ( v84 );
  }
  polyhedron::recompute_planes(&vpg);
  v88 = 0;
  v119 = vpg.v.s;
  if ( vpg.v.s > 0 )
  {
    v89 = 0;
    do
    {
      v90 = &v118[v89 * 16];
      *(float *)v90 = vpg.v.v[v89].x;
      *((_DWORD *)v90 + 1) = LODWORD(vpg.v.v[v89].y);
      v91 = vpg.v.v[v89].w;
      *((_DWORD *)v90 + 2) = LODWORD(vpg.v.v[v89].z);
      ++v88;
      *((float *)v90 + 3) = v91;
      ++v89;
    }
    while ( v88 < v119 );
  }
  MyArray<poly,9>::MyArray<poly,9>(&v120, &vpg.p);
  v122 = vpg.e.s;
  if ( vpg.e.s > 0 )
  {
    v92 = 0;
    do
    {
      v93 = &v121[v92 * 16];
      *(_DWORD *)v93 = vpg.e.v[v92].vi[0];
      *((_DWORD *)v93 + 1) = vpg.e.v[v92].vi[1];
      v94 = vpg.e.v[v92].pi[1];
      *((_DWORD *)v93 + 2) = vpg.e.v[v92].pi[0];
      ++v3;
      *((_DWORD *)v93 + 3) = v94;
      ++v92;
    }
    while ( v3 < v122 );
  }
  v46 = v118;
LABEL_74:
  v95 = result;
  qmemcpy(result, v46, sizeof(polyhedron));
  return v95;
}

// FUNC: struct polyhedron __cdecl PolyhedronFromBounds(class idBounds const &)
polyhedron *__cdecl PolyhedronFromBounds(polyhedron *result, const idBounds *b)
{
  _DWORD *p_x; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  float y; // edx
  float z; // ecx
  float v12; // edx
  float v13; // ecx
  float v14; // edx
  float v15; // ecx
  float v16; // edx
  float v17; // ecx
  float v18; // edx
  float v19; // ecx
  float v20; // edx
  float v21; // ecx
  float v22; // edx
  polyhedron *v23; // eax
  float x; // [esp+8h] [ebp-7F8h]
  float v25; // [esp+8h] [ebp-7F8h]
  float v26; // [esp+8h] [ebp-7F8h]
  float v27; // [esp+8h] [ebp-7F8h]
  float v28; // [esp+8h] [ebp-7F8h]
  float v29; // [esp+8h] [ebp-7F8h]
  float v30; // [esp+8h] [ebp-7F8h]
  float v31; // [esp+Ch] [ebp-7F4h]
  float v32; // [esp+Ch] [ebp-7F4h]
  float v33; // [esp+Ch] [ebp-7F4h]
  float v34; // [esp+Ch] [ebp-7F4h]
  float v35; // [esp+10h] [ebp-7F0h]
  float v36; // [esp+10h] [ebp-7F0h]
  polyhedron p2; // [esp+18h] [ebp-7E8h] BYREF
  _BYTE v38[1012]; // [esp+40Ch] [ebp-3F4h] BYREF

  if ( (_S3_2 & 1) == 0 )
  {
    _S3_2 |= 1u;
    p_0.v.s = 0;
    MyArray<poly,9>::MyArray<poly,9>(&p_0.p);
    p_0.e.s = 0;
LABEL_4:
    p_x = (_DWORD *)&p_0.v.v[p_0.v.s].x;
    *p_x = -1082130432;
    p_x[1] = -1082130432;
    p_x[2] = 1065353216;
    p_x[3] = 1065353216;
    v3 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v3 = 1065353216;
    v3[1] = -1082130432;
    v3[2] = 1065353216;
    v3[3] = 1065353216;
    v4 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v4 = 1065353216;
    v4[1] = 1065353216;
    v4[2] = 1065353216;
    v4[3] = 1065353216;
    v5 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v5 = -1082130432;
    v5[1] = 1065353216;
    v5[2] = 1065353216;
    v5[3] = 1065353216;
    v6 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v6 = -1082130432;
    v6[1] = -1082130432;
    v6[2] = -1082130432;
    v6[3] = 1065353216;
    v7 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v7 = 1065353216;
    v7[1] = -1082130432;
    v7[2] = -1082130432;
    v7[3] = 1065353216;
    v8 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v8 = 1065353216;
    v8[1] = 1065353216;
    v8[2] = -1082130432;
    v8[3] = 1065353216;
    v9 = (_DWORD *)&p_0.v.v[++p_0.v.s].x;
    *v9 = -1082130432;
    v9[1] = 1065353216;
    v9[2] = -1082130432;
    v9[3] = 1065353216;
    ++p_0.v.s;
    polyhedron::add_quad(&p_0, 0, 1, 2, 3);
    polyhedron::add_quad(&p_0, 7, 6, 5, 4);
    polyhedron::add_quad(&p_0, 1, 0, 4, 5);
    polyhedron::add_quad(&p_0, 2, 1, 5, 6);
    polyhedron::add_quad(&p_0, 3, 2, 6, 7);
    polyhedron::add_quad(&p_0, 0, 3, 7, 4);
    polyhedron::compute_neighbors(&p_0);
    polyhedron::recompute_planes(&p_0);
    p_0.v.s = 0;
    goto LABEL_5;
  }
  if ( !p_0.e.s )
    goto LABEL_4;
LABEL_5:
  MyArray<idVec4,16>::MyArray<idVec4,16>(&p2.v, &p_0.v);
  MyArray<poly,9>::MyArray<poly,9>(&p2.p, &p_0.p);
  MyArray<edge,15>::MyArray<edge,15>(&p2.e, &p_0.e);
  y = b->b[0].y;
  z = b->b[1].z;
  p2.v.v[0].x = b->b[0].x;
  p2.v.v[0].y = y;
  p2.v.v[0].z = z;
  x = b->b[1].x;
  v35 = b->b[1].z;
  p2.v.v[0].w = 1.0;
  v31 = b->b[0].y;
  p2.v.v[1].x = x;
  p2.v.v[1].y = v31;
  p2.v.v[1].z = v35;
  v25 = b->b[1].x;
  v36 = b->b[1].z;
  p2.v.v[1].w = 1.0;
  v32 = b->b[1].y;
  p2.v.v[2].x = v25;
  p2.v.v[2].y = v32;
  p2.v.v[2].z = v36;
  v12 = b->b[0].x;
  p2.v.v[2].w = 1.0;
  v13 = b->b[1].y;
  v26 = v12;
  v14 = b->b[1].z;
  p2.v.v[3].x = v26;
  p2.v.v[3].y = v13;
  p2.v.v[3].z = v14;
  v27 = b->b[0].x;
  v15 = b->b[0].z;
  p2.v.v[3].w = 1.0;
  v33 = b->b[0].y;
  p2.v.v[4].x = v27;
  p2.v.v[4].y = v33;
  p2.v.v[4].z = v15;
  v28 = b->b[1].x;
  v16 = b->b[0].z;
  p2.v.v[4].w = 1.0;
  v34 = b->b[0].y;
  p2.v.v[5].x = v28;
  p2.v.v[5].y = v34;
  p2.v.v[5].z = v16;
  v17 = b->b[1].x;
  p2.v.v[5].w = 1.0;
  v18 = b->b[1].y;
  v29 = v17;
  v19 = b->b[0].z;
  p2.v.v[6].x = v29;
  p2.v.v[6].y = v18;
  p2.v.v[6].z = v19;
  v20 = b->b[0].x;
  p2.v.v[6].w = 1.0;
  v21 = b->b[1].y;
  v30 = v20;
  v22 = b->b[0].z;
  p2.v.v[7].x = v30;
  p2.v.v[7].y = v21;
  p2.v.v[7].z = v22;
  p2.v.v[7].w = 1.0;
  p2.v.s = 8;
  polyhedron::recompute_planes(&p2);
  MyArray<idVec4,16>::MyArray<idVec4,16>((MyArray<idVec4,16> *)v38, &p2.v);
  MyArray<poly,9>::MyArray<poly,9>((MyArray<poly,9> *)&v38[260], &p2.p);
  MyArray<edge,15>::MyArray<edge,15>((MyArray<edge,15> *)&v38[768], &p2.e);
  v23 = result;
  qmemcpy(result, v38, sizeof(polyhedron));
  return v23;
}

// FUNC: class idScreenRect __cdecl R_CalcIntersectionScissor(class idRenderLightLocal const *,class idRenderEntityLocal const *,struct viewDef_s const *)
idScreenRect *__cdecl R_CalcIntersectionScissor(
        idScreenRect *result,
        const idRenderLightLocal *lightDef,
        const idRenderEntityLocal *entityDef,
        const viewDef_s *viewDef)
{
  unsigned int s; // edi
  polyhedron *v5; // esi
  int v6; // edx
  double v7; // st7
  double v8; // st7
  int x2; // ecx
  int y1; // eax
  int v11; // edx
  double v12; // st7
  double v13; // st6
  idScreenRect *v14; // eax
  idVec4 v15; // [esp-10h] [ebp-1090h]
  float v16; // [esp+Ch] [ebp-1074h]
  float v17; // [esp+10h] [ebp-1070h]
  float v18; // [esp+14h] [ebp-106Ch]
  float v19; // [esp+18h] [ebp-1068h]
  float v20; // [esp+1Ch] [ebp-1064h]
  float v21; // [esp+20h] [ebp-1060h]
  float v22; // [esp+24h] [ebp-105Ch]
  int x1; // [esp+28h] [ebp-1058h]
  float v24; // [esp+28h] [ebp-1058h]
  float v25; // [esp+2Ch] [ebp-1054h]
  float v26; // [esp+30h] [ebp-1050h]
  idScreenRect rect; // [esp+3Ch] [ebp-1044h] BYREF
  int v28; // [esp+4Ch] [ebp-1034h]
  idVec4 clip; // [esp+50h] [ebp-1030h] BYREF
  idMat4 resulta; // [esp+60h] [ebp-1020h] BYREF
  polyhedron p; // [esp+A0h] [ebp-FE0h] BYREF
  polyhedron cpy; // [esp+498h] [ebp-BE8h] BYREF
  polyhedron v33; // [esp+890h] [ebp-7F0h] BYREF
  polyhedron v34; // [esp+C88h] [ebp-3F8h] BYREF

  make_idMat4(&resulta, entityDef->modelMatrix);
  qmemcpy(&cpy, PolyhedronFromBounds(&p, &lightDef->frustumTris->bounds), sizeof(cpy));
  MyArray<idVec4,16>::MyArray<idVec4,16>(&v34.v, &cpy.v);
  MyArray<poly,9>::MyArray<poly,9>(&v34.p, &cpy.p);
  MyArray<edge,15>::MyArray<edge,15>(&v34.e, &cpy.e);
  if ( r_useInteractionScissors.internalVar->integerValue == -2 )
    draw_polyhedron(viewDef, &v34, colorRed);
  qmemcpy(&cpy, PolyhedronFromBounds(&v33, &entityDef->referenceBounds), sizeof(cpy));
  MyArray<idVec4,16>::MyArray<idVec4,16>(&p.v, &cpy.v);
  MyArray<poly,9>::MyArray<poly,9>(&p.p, &cpy.p);
  MyArray<edge,15>::MyArray<edge,15>(&p.e, &cpy.e);
  polyhedron::transform(&p, &resulta);
  if ( r_useInteractionScissors.internalVar->integerValue == -2 )
    draw_polyhedron(viewDef, &p, colorBlue);
  *(_QWORD *)&v15.x = *(_QWORD *)&lightDef->globalLightOrigin.x;
  *(_QWORD *)&v15.z = LODWORD(lightDef->globalLightOrigin.z) | 0x3F80000000000000i64;
  qmemcpy(&p, make_sv(&v33, &p, v15), sizeof(p));
  MyArray<idVec4,16>::MyArray<idVec4,16>(&cpy.v, &p.v);
  MyArray<poly,9>::MyArray<poly,9>(&cpy.p, &p.p);
  MyArray<edge,15>::MyArray<edge,15>(&cpy.e, &p.e);
  p.p.v[5].ni.s = 0;
  v33.p.v[5].ni.s = 0;
  polyhedron_edges(&cpy, (MyArray<idVec4,36> *)&p);
  clip_segments(&v34, (MyArray<idVec4,36> *)&p, (MyArray<idVec4,36> *)&v33);
  polyhedron_edges(&v34, (MyArray<idVec4,36> *)&p);
  clip_segments(&cpy, (MyArray<idVec4,36> *)&p, (MyArray<idVec4,36> *)&v33);
  if ( r_useInteractionScissors.internalVar->integerValue == -2 )
    draw_segments(viewDef, (const MyArray<idVec4,36> *)&v33, colorGreen);
  s = v33.p.v[5].ni.s;
  v22 = -1.0e30;
  v17 = idMath::INFINITY;
  v21 = v22;
  v20 = v22;
  v19 = idMath::INFINITY;
  v18 = idMath::INFINITY;
  if ( v33.p.v[5].ni.s )
  {
    v5 = &v33;
    while ( 1 )
    {
      world_to_hclip(viewDef, v5->v.v, &clip);
      if ( clip.w <= 0.0 )
        break;
      v7 = 1.0 / clip.w;
      v25 = clip.x * v7;
      v26 = clip.y * v7;
      v8 = v7 * clip.z;
      if ( v25 < (double)v17 )
        v17 = v25;
      if ( v25 > (double)v20 )
        v20 = v25;
      if ( v26 < (double)v18 )
        v18 = v26;
      if ( v26 > (double)v21 )
        v21 = v26;
      if ( v8 < v19 )
        v19 = v8;
      if ( v8 > v22 )
        v22 = v8;
      v5 = (polyhedron *)((char *)v5 + 16);
      if ( v6 + 1 >= s )
        goto LABEL_23;
    }
    v14 = result;
    *result = lightDef->viewLight->scissorRect;
  }
  else
  {
LABEL_23:
    if ( v17 < -1.0 )
      v17 = -1.0;
    if ( v20 > 1.0 )
      v20 = 1.0;
    if ( v18 < -1.0 )
      v18 = -1.0;
    if ( v21 > 1.0 )
      v21 = 1.0;
    x2 = viewDef->viewport.x2;
    x1 = viewDef->viewport.x1;
    y1 = viewDef->viewport.y1;
    v11 = viewDef->viewport.y2 - y1;
    v28 = y1;
    v12 = (double)(x2 - x1 + 1) * 0.5;
    v13 = (double)x1;
    v24 = (double)(v11 + 1) * 0.5;
    v16 = (float)y1;
    rect.x1 = (unsigned __int64)((v17 + 1.0) * v12 + v13);
    rect.x2 = (unsigned __int64)((v20 + 1.0) * v12 + v13);
    rect.y1 = (unsigned __int64)((v18 + 1.0) * v24 + v16);
    rect.y2 = (unsigned __int64)((v21 + 1.0) * v24 + v16);
    idScreenRect::Expand(&rect);
    idScreenRect::Intersect(&rect, &lightDef->viewLight->scissorRect);
    if ( r_useInteractionScissors.internalVar->integerValue == -2 && !idScreenRect::IsEmpty(&rect) )
      idRenderWorldLocal::DebugScreenRect(viewDef->renderWorld, &colorYellow, &rect, viewDef, 0);
    v14 = result;
    *result = rect;
  }
  return v14;
}
