
// FUNC: drfti1
void __cdecl drfti1(int n, float *wa, int *ifac)
{
  int v3; // ecx
  int v4; // esi
  int v5; // edi
  int *v6; // ebx
  int v7; // eax
  int *v8; // ebx
  int *v9; // ecx
  int v10; // edx
  bool v12; // zf
  int v13; // edi
  double v14; // st7
  int v15; // ebx
  int v16; // esi
  int v17; // eax
  int *v18; // edi
  int v19; // ebp
  float *v20; // edi
  double v21; // st7
  float *v22; // ecx
  unsigned int v23; // edx
  long double v24; // st6
  int ld; // [esp+10h] [ebp-14h]
  int *v26; // [esp+14h] [ebp-10h]
  int *v27; // [esp+14h] [ebp-10h]
  int nl; // [esp+18h] [ebp-Ch]
  float argh; // [esp+1Ch] [ebp-8h]
  float argld; // [esp+20h] [ebp-4h]
  int *ifaca; // [esp+30h] [ebp+Ch]

  v3 = n;
  v4 = 0;
  v5 = 0;
  v6 = &ntryh[-1];
  do
  {
L101:
    v26 = ++v6;
    if ( (int)v6 >= (int)&tpi )
      v4 += 2;
    else
      v4 = *v6;
    v7 = v3 / v4;
  }
  while ( v3 % v4 );
  v8 = &ifac[v5];
  while ( 1 )
  {
    ++v8;
    ++v5;
    v3 = v7;
    v8[1] = v4;
    if ( v4 == 2 && v5 != 1 )
    {
      if ( v5 > 1 )
      {
        v9 = v8;
        v10 = v5 - 1;
        do
        {
          v9[1] = *v9;
          --v9;
          --v10;
        }
        while ( v10 );
        v3 = v7;
      }
      ifac[2] = 2;
    }
    if ( v7 == 1 )
      break;
    v7 /= v4;
    if ( v3 != v4 * v7 )
    {
      v6 = v26;
      goto L101;
    }
  }
  ifac[1] = v5;
  v12 = v5 == 1;
  v13 = v5 - 1;
  v14 = tpi / (double)n;
  *ifac = n;
  ifaca = 0;
  v15 = 1;
  argh = v14;
  if ( !v12 && v13 > 0 )
  {
    v27 = ifac + 2;
    nl = v13;
    do
    {
      v16 = v15 * *v27;
      v17 = n / v16;
      ld = 0;
      if ( *v27 - 1 > 0 )
      {
        v18 = ifaca;
        v19 = *v27 - 1;
        ifaca = (int *)((char *)ifaca + v17 * v19);
        v20 = &wa[(_DWORD)v18];
        do
        {
          ld += v15;
          v21 = 0.0;
          if ( v17 > 2 )
          {
            v22 = v20;
            v23 = ((unsigned int)(v17 - 3) >> 1) + 1;
            do
            {
              v21 = v21 + 1.0;
              v22 += 2;
              --v23;
              argld = (double)ld * argh;
              v24 = argld * v21;
              *(v22 - 2) = cos(v24);
              *(v22 - 1) = sin(v24);
            }
            while ( v23 );
          }
          v20 += v17;
          --v19;
        }
        while ( v19 );
      }
      ++v27;
      v12 = nl-- == 1;
      v15 = v16;
    }
    while ( !v12 );
  }
}

// FUNC: dradf2
void __usercall dradf2(int ido@<ecx>, float *cc@<eax>, float *ch@<edx>, int l1, float *wa1)
{
  int v5; // ebp
  int v6; // esi
  int v8; // edx
  float *v9; // ebx
  double v10; // st7
  int v11; // edx
  double v12; // st7
  int v13; // esi
  float *v14; // ebx
  double v15; // st7
  int v16; // edx
  double v17; // st7
  int v18; // esi
  float *v19; // ebx
  double v20; // st7
  int v21; // edx
  double v22; // st7
  int v23; // esi
  float *v24; // ebx
  double v25; // st7
  double v26; // st7
  float *v27; // ebx
  float *v28; // esi
  float *v29; // esi
  float *v30; // ebx
  float *v31; // edx
  double v32; // st7
  double v33; // st7
  bool v34; // zf
  double v35; // st6
  int v36; // ebx
  int v37; // esi
  int v38; // edx
  double v39; // st7
  int v40; // esi
  int v41; // edx
  int v42; // ebx
  int v43; // esi
  int v44; // edx
  int v45; // ebx
  int v46; // esi
  int v47; // edx
  int v48; // ebx
  int v49; // ebp
  float *v50; // ebx
  float *v51; // eax
  int v52; // ecx
  int v53; // esi
  float *v54; // edx
  double v55; // st7
  int k; // [esp+10h] [ebp-24h]
  float *ka; // [esp+10h] [ebp-24h]
  int kb; // [esp+10h] [ebp-24h]
  float *v59; // [esp+14h] [ebp-20h]
  float *v60; // [esp+14h] [ebp-20h]
  float *v61; // [esp+18h] [ebp-1Ch]
  float *v62; // [esp+1Ch] [ebp-18h]
  int v63; // [esp+20h] [ebp-14h]
  float *v64; // [esp+20h] [ebp-14h]
  unsigned int v65; // [esp+24h] [ebp-10h]
  float *v66; // [esp+24h] [ebp-10h]
  float *v67; // [esp+24h] [ebp-10h]
  unsigned int v68; // [esp+28h] [ebp-Ch]
  int v69; // [esp+2Ch] [ebp-8h]
  int t0; // [esp+30h] [ebp-4h]
  int t0a; // [esp+30h] [ebp-4h]

  v5 = l1;
  v6 = l1 * ido;
  v8 = 0;
  t0 = l1 * ido;
  k = 0;
  if ( l1 >= 4 )
  {
    v65 = ((unsigned int)(l1 - 4) >> 2) + 1;
    v9 = &ch[2 * ido - 1];
    k = 4 * v65;
    do
    {
      ch[2 * v8] = cc[v6] + cc[v8];
      v10 = cc[v8];
      v11 = ido + v8;
      v12 = v10 - cc[v6];
      v13 = ido + v6;
      *v9 = v12;
      v14 = &v9[2 * ido];
      ch[2 * v11] = cc[v13] + cc[v11];
      v15 = cc[v11];
      v16 = ido + v11;
      v17 = v15 - cc[v13];
      v18 = ido + v13;
      *v14 = v17;
      v19 = &v14[2 * ido];
      ch[2 * v16] = cc[v18] + cc[v16];
      v20 = cc[v16];
      v21 = ido + v16;
      v22 = v20 - cc[v18];
      v23 = ido + v18;
      *v19 = v22;
      v24 = &v19[2 * ido];
      ch[2 * v21] = cc[v23] + cc[v21];
      v25 = cc[v21];
      v8 = ido + v21;
      v26 = v25 - cc[v23];
      v6 = ido + v23;
      *v24 = v26;
      v9 = &v24[2 * ido];
      --v65;
    }
    while ( v65 );
    v5 = l1;
  }
  if ( k < v5 )
  {
    v27 = &cc[v8];
    v66 = &ch[2 * v8];
    v59 = &ch[2 * ido - 1 + 2 * v8];
    v28 = &cc[v6];
    v63 = l1 - k;
    do
    {
      *v66 = *v27 + *v28;
      *v59 = *v27 - *v28;
      v59 += 2 * ido;
      v66 += 2 * ido;
      v27 += ido;
      v28 += ido;
      --v63;
    }
    while ( v63 );
    v5 = l1;
  }
  if ( ido >= 2 )
  {
    if ( ido == 2 )
      goto L105;
    if ( v5 > 0 )
    {
      v64 = &cc[t0];
      v67 = ch;
      v62 = cc;
      v61 = &ch[2 * ido];
      v69 = v5;
      do
      {
        v29 = v62;
        ka = v61;
        v30 = wa1 + 1;
        v60 = v67;
        v31 = v64;
        v68 = ((unsigned int)(ido - 3) >> 1) + 1;
        do
        {
          v32 = *(v30 - 1) * v31[1];
          v31 += 2;
          ka -= 2;
          v29 += 2;
          v60 += 2;
          v33 = v32 + *v30 * *v31;
          v30 += 2;
          v34 = v68-- == 1;
          v35 = *(v30 - 3) * *v31 - *(v30 - 2) * *(v31 - 1);
          *v60 = v35 + *v29;
          *ka = v35 - *v29;
          *(v60 - 1) = v33 + *(v29 - 1);
          *(ka - 1) = *(v29 - 1) - v33;
        }
        while ( !v34 );
        v5 = l1;
        v61 += 2 * ido;
        v67 += 2 * ido;
        v62 += ido;
        v64 += ido;
        --v69;
      }
      while ( v69 );
    }
    if ( (ido & 1) != 1 )
    {
L105:
      v36 = ido - 1;
      v37 = t0 + ido - 1;
      v38 = ido;
      kb = 0;
      if ( v5 >= 4 )
      {
        t0a = ((unsigned int)(l1 - 4) >> 2) + 1;
        kb = 4 * t0a;
        do
        {
          v39 = cc[v37];
          v40 = ido + v37;
          ch[v38] = -v39;
          ch[v38 - 1] = cc[v36];
          v41 = 2 * ido + v38;
          ch[v41] = -cc[v40];
          v42 = ido + v36;
          ch[v41 - 1] = cc[v42];
          v43 = ido + v40;
          v44 = 2 * ido + v41;
          ch[v44] = -cc[v43];
          v45 = ido + v42;
          ch[v44 - 1] = cc[v45];
          v46 = ido + v43;
          v47 = 2 * ido + v44;
          v48 = ido + v45;
          ch[v47] = -cc[v46];
          ch[v47 - 1] = cc[v48];
          v38 = 2 * ido + v47;
          v37 = ido + v46;
          v36 = ido + v48;
          --t0a;
        }
        while ( t0a );
        v5 = l1;
      }
      if ( kb < v5 )
      {
        v49 = 8 * ido;
        v50 = &cc[v36];
        v51 = &cc[v37];
        v52 = 4 * ido;
        v53 = l1 - kb;
        v54 = &ch[v38];
        do
        {
          v55 = *v51;
          v51 = (float *)((char *)v51 + v52);
          *v54 = -v55;
          *(v54 - 1) = *v50;
          v54 = (float *)((char *)v54 + v49);
          v50 = (float *)((char *)v50 + v52);
          --v53;
        }
        while ( v53 );
      }
    }
  }
}

// FUNC: dradf4
void __usercall dradf4(int ido@<ecx>, float *cc@<eax>, float *ch@<edx>, int l1, float *wa1, float *wa2, float *wa3)
{
  int v7; // ebx
  int v8; // edi
  int v9; // esi
  int v10; // ebp
  double v11; // st7
  double v12; // st6
  int v13; // ebx
  double v14; // st7
  int v15; // esi
  double v16; // st7
  int v17; // edi
  double v18; // st7
  double v19; // st6
  int v20; // ebx
  double v21; // st7
  int v22; // esi
  double v23; // st7
  int v24; // edi
  double v25; // st7
  double v26; // st6
  int v27; // ebx
  int v28; // edi
  double v29; // st7
  int v30; // esi
  double v31; // st6
  int v32; // ebx
  int v33; // ebp
  double v34; // st7
  double v35; // st7
  bool v36; // zf
  float *v37; // edi
  int v38; // ebp
  double v39; // st7
  double v40; // st6
  int v41; // ebx
  float *v42; // edi
  double v43; // st7
  float *v44; // edi
  double v45; // st7
  int v46; // ebx
  int v47; // esi
  float *v48; // esi
  float *v49; // edi
  float *v50; // ebx
  double v51; // st7
  double v52; // st7
  double v53; // st6
  double v54; // st5
  double v55; // st7
  double v56; // st6
  double v57; // st5
  double v58; // st4
  double v59; // st3
  int v60; // esi
  int v61; // edi
  int v62; // ebx
  double v63; // st7
  double v64; // st6
  int v65; // esi
  double v66; // st6
  int v67; // edi
  double v68; // st7
  double v69; // st6
  int v70; // esi
  float *v71; // ebp
  double v72; // st6
  float *v73; // ebx
  int v74; // edi
  int v75; // ebp
  double v76; // st7
  double v77; // st6
  int v78; // esi
  double v79; // st6
  float *v80; // ebp
  double v81; // st6
  float *v82; // ebx
  int v83; // edi
  int v84; // ebp
  double v85; // st7
  double v86; // st7
  double v87; // st6
  double v88; // st6
  float *v89; // ebx
  int v90; // ebp
  int v91; // ecx
  float *v92; // edi
  float *v93; // edx
  float *v94; // ebx
  float *v95; // ecx
  float *v96; // eax
  double v97; // st7
  double v98; // st6
  double v99; // st6
  double v100; // st6
  double v101; // st5
  double v102; // st7
  int t2; // [esp+10h] [ebp-60h]
  int t2c; // [esp+10h] [ebp-60h]
  int t2d; // [esp+10h] [ebp-60h]
  float *t2a; // [esp+10h] [ebp-60h]
  int t2b; // [esp+10h] [ebp-60h]
  int t2e; // [esp+10h] [ebp-60h]
  int t4; // [esp+14h] [ebp-5Ch]
  int t4c; // [esp+14h] [ebp-5Ch]
  int t4d; // [esp+14h] [ebp-5Ch]
  float *t4a; // [esp+14h] [ebp-5Ch]
  float *t4b; // [esp+14h] [ebp-5Ch]
  float *t4e; // [esp+14h] [ebp-5Ch]
  float *v115; // [esp+18h] [ebp-58h]
  float *v116; // [esp+18h] [ebp-58h]
  float *v117; // [esp+1Ch] [ebp-54h]
  float *v118; // [esp+1Ch] [ebp-54h]
  float *v119; // [esp+1Ch] [ebp-54h]
  float *v120; // [esp+1Ch] [ebp-54h]
  float *v121; // [esp+1Ch] [ebp-54h]
  float *v122; // [esp+1Ch] [ebp-54h]
  float *t6; // [esp+20h] [ebp-50h]
  float *t6a; // [esp+20h] [ebp-50h]
  int t6b; // [esp+20h] [ebp-50h]
  int k; // [esp+24h] [ebp-4Ch]
  float *ka; // [esp+24h] [ebp-4Ch]
  int kb; // [esp+24h] [ebp-4Ch]
  int t0; // [esp+28h] [ebp-48h]
  float ci4a; // [esp+2Ch] [ebp-44h]
  int ci4; // [esp+2Ch] [ebp-44h]
  float *v132; // [esp+30h] [ebp-40h]
  float *v133; // [esp+34h] [ebp-3Ch]
  int v134; // [esp+38h] [ebp-38h]
  float *v135; // [esp+38h] [ebp-38h]
  unsigned int v136; // [esp+3Ch] [ebp-34h]
  float *v137; // [esp+3Ch] [ebp-34h]
  float *v138; // [esp+3Ch] [ebp-34h]
  float *v139; // [esp+3Ch] [ebp-34h]
  int v140; // [esp+40h] [ebp-30h]
  int v141; // [esp+44h] [ebp-2Ch]
  int v142; // [esp+48h] [ebp-28h]
  float ci3; // [esp+4Ch] [ebp-24h]
  float cr3; // [esp+50h] [ebp-20h]
  float tr4; // [esp+54h] [ebp-1Ch]
  float tr1; // [esp+58h] [ebp-18h]
  float ti1; // [esp+5Ch] [ebp-14h]
  unsigned int v148; // [esp+60h] [ebp-10h]
  int t1; // [esp+64h] [ebp-Ch]
  int v150; // [esp+68h] [ebp-8h]
  unsigned int v151; // [esp+68h] [ebp-8h]
  int v152; // [esp+68h] [ebp-8h]
  int l1a; // [esp+74h] [ebp+4h]

  v7 = l1;
  t0 = l1 * ido;
  v8 = l1 * ido;
  t4 = 2 * l1 * ido;
  v9 = 0;
  v10 = 3 * l1 * ido;
  t2 = v10;
  k = 0;
  if ( l1 >= 4 )
  {
    v136 = ((unsigned int)(l1 - 4) >> 2) + 1;
    k = 4 * v136;
    do
    {
      v11 = cc[v10] + cc[v8];
      v12 = cc[v9] + cc[t4];
      ch[4 * v9] = v12 + v11;
      ch[4 * v9 - 1 + 4 * ido] = v12 - v11;
      v13 = 2 * ido + 4 * v9;
      v14 = cc[v9];
      v15 = ido + v9;
      ch[v13 - 1] = v14 - cc[t4];
      v16 = cc[t2] - cc[v8];
      v17 = ido + v8;
      t2c = ido + t2;
      ch[v13] = v16;
      v18 = cc[t2c] + cc[v17];
      t4c = ido + t4;
      v19 = cc[v15] + cc[t4c];
      ch[4 * v15] = v19 + v18;
      ch[4 * v15 - 1 + 4 * ido] = v19 - v18;
      v20 = 2 * ido + 4 * v15;
      v21 = cc[v15];
      v22 = ido + v15;
      ch[v20 - 1] = v21 - cc[t4c];
      v23 = cc[t2c] - cc[v17];
      v24 = ido + v17;
      t2d = ido + t2c;
      ch[v20] = v23;
      v25 = cc[t2d] + cc[v24];
      t4d = ido + t4c;
      v26 = cc[v22] + cc[t4d];
      ch[4 * v22] = v26 + v25;
      ch[4 * v22 - 1 + 4 * ido] = v26 - v25;
      v27 = 2 * ido + 4 * v22;
      ch[v27 - 1] = cc[v22] - cc[t4d];
      ch[v27] = cc[t2d] - cc[v24];
      v28 = ido + v24;
      v29 = cc[ido + t2d] + cc[v28];
      v30 = ido + v22;
      v31 = cc[v30] + cc[ido + t4d];
      ch[4 * v30] = v31 + v29;
      ch[4 * v30 - 1 + 4 * ido] = v31 - v29;
      v32 = 2 * ido + 4 * v30;
      v33 = ido + t4d;
      t4 = ido + ido + t4d;
      v34 = cc[v30] - cc[v33];
      v9 = ido + v30;
      ch[v32 - 1] = v34;
      v10 = ido + ido + t2d;
      v35 = cc[ido + t2d] - cc[v28];
      v8 = ido + v28;
      v36 = v136-- == 1;
      t2 = v10;
      ch[v32] = v35;
    }
    while ( !v36 );
    v7 = l1;
  }
  if ( k < v7 )
  {
    t6 = &cc[t2];
    v117 = &cc[t4];
    v37 = &cc[v8];
    v38 = 4 * ido;
    v137 = v37;
    v134 = l1 - k;
    do
    {
      v39 = *v37 + *t6;
      v40 = cc[v9] + *v117;
      ch[4 * v9] = v40 + v39;
      ch[4 * v9 - 1 + v38] = v40 - v39;
      v41 = 2 * ido + 4 * v9;
      v42 = v117;
      v117 = (float *)((char *)v117 + v38);
      v43 = cc[v9] - *v42;
      v44 = t6;
      t6 = (float *)((char *)t6 + v38);
      v9 += ido;
      ch[v41 - 1] = v43;
      v45 = *v44 - *v137;
      v37 = &v137[v38 / 4u];
      v36 = v134-- == 1;
      v137 = (float *)((char *)v137 + v38);
      ch[v41] = v45;
    }
    while ( !v36 );
  }
  if ( ido >= 2 )
  {
    if ( ido == 2 )
      goto L105_0;
    v46 = 0;
    t1 = 0;
    if ( l1 > 0 )
    {
      v135 = &cc[t0];
      v133 = ch;
      v138 = &cc[3 * t0];
      v150 = l1;
      do
      {
        v47 = 2 * ido + 4 * v46;
        t2a = &ch[v47];
        t4a = t2a;
        ka = &cc[2 * t0 + v46];
        v141 = (char *)wa2 - (char *)wa1;
        v142 = (char *)wa3 - (char *)wa1;
        v132 = &ch[2 * ido + v47];
        v115 = v133;
        v140 = (char *)wa2 - (char *)wa3;
        t6a = wa3;
        v48 = wa1 + 1;
        v118 = &cc[v46];
        v49 = v135;
        v148 = ((unsigned int)(ido - 3) >> 1) + 1;
        v50 = v138;
        do
        {
          ka += 2;
          v51 = v49[1] * *(v48 - 1);
          v49 += 2;
          v118 += 2;
          v115 += 2;
          t2a += 2;
          v52 = v51 + *v49 * *v48;
          t4a -= 2;
          v132 -= 2;
          v53 = *(v48 - 1) * *v49 - *(v49 - 1) * *v48;
          cr3 = *(float *)((char *)t6a + v140) * *(ka - 1) + *(float *)((char *)v48 + v141) * *ka;
          v50 += 2;
          ci3 = *ka * *(float *)((char *)t6a + v140) - *(float *)((char *)v48 + v141) * *(ka - 1);
          v54 = *v50 * *(float *)((char *)v48 + v142) + *t6a * *(v50 - 1);
          ci4a = *v50 * *t6a - *(v50 - 1) * *(float *)((char *)v48 + v142);
          tr1 = v54 + v52;
          tr4 = v54 - v52;
          ti1 = ci4a + v53;
          v55 = v53 - ci4a;
          v56 = ci3 + *v118;
          v57 = *v118 - ci3;
          v58 = cr3 + *(v118 - 1);
          v59 = *(v118 - 1) - cr3;
          *(v115 - 1) = v58 + tr1;
          *v115 = v56 + ti1;
          t6a += 2;
          v48 += 2;
          v36 = v148-- == 1;
          *(t4a - 1) = v59 - v55;
          *t4a = tr4 - v57;
          *(t2a - 1) = v59 + v55;
          *t2a = v57 + tr4;
          *(v132 - 1) = v58 - tr1;
          *v132 = ti1 - v56;
        }
        while ( !v36 );
        v133 += 4 * ido;
        v135 += ido;
        v138 += ido;
        v46 = ido + t1;
        v36 = v150-- == 1;
        t1 += ido;
      }
      while ( !v36 );
    }
    if ( (ido & 1) == 0 )
    {
L105_0:
      v60 = t0 + ido - 1;
      t2b = v60 + 2 * t0;
      v61 = ido;
      t6b = ido;
      kb = 0;
      if ( l1 >= 4 )
      {
        t4b = &ch[3 * ido];
        v116 = &cc[v60 + t0];
        ci4 = 4 * ido;
        v62 = ido;
        v119 = &cc[ido - 1];
        v151 = ((unsigned int)(l1 - 4) >> 2) + 1;
        kb = 4 * v151;
        do
        {
          v63 = -((cc[t2b] + cc[v60]) * hsqt2);
          v64 = cc[v60];
          v65 = ido + v60;
          v66 = (v64 - cc[t2b]) * hsqt2;
          ch[v61 - 1] = v66 + *v119;
          *(t4b - 1) = *v119 - v66;
          ch[v61] = v63 - *v116;
          v67 = 4 * ido + v61;
          *t4b = v63 + *v116;
          v120 = &v119[ido];
          v68 = -((cc[ido + t2b] + cc[v65]) * hsqt2);
          v69 = cc[v65];
          v70 = ido + v65;
          v71 = &t4b[ci4];
          v72 = (v69 - cc[ido + t2b]) * hsqt2;
          ch[v67 - 1] = v72 + *v120;
          v73 = &v116[v62];
          *(v71 - 1) = *v120 - v72;
          ch[v67] = v68 - *v73;
          *v71 = v68 + *v73;
          v74 = 4 * ido + v67;
          v75 = ido + ido + t2b;
          v121 = &v120[ido];
          v76 = -((cc[v75] + cc[v70]) * hsqt2);
          t2e = ido + v75;
          v77 = cc[v70];
          v78 = ido + v70;
          v79 = v77 - cc[v75];
          v80 = &t4b[ci4 + ci4];
          t6b += ido + ido + ido + ido;
          v81 = v79 * hsqt2;
          ch[v74 - 1] = v81 + *v121;
          v82 = &v73[ido];
          *(v80 - 1) = *v121 - v81;
          ch[v74] = v76 - *v82;
          *v80 = v76 + *v82;
          v83 = 4 * ido + v74;
          t4e = &v80[ci4];
          v84 = t2e;
          v122 = &v121[ido];
          v85 = cc[t2e] + cc[v78];
          t2b = ido + t2e;
          v86 = -(v85 * hsqt2);
          v87 = cc[v78];
          v60 = ido + v78;
          v88 = (v87 - cc[v84]) * hsqt2;
          ch[v83 - 1] = v88 + *v122;
          v89 = &v82[ido];
          *(t4e - 1) = *v122 - v88;
          ch[v83] = v86 - *v89;
          *t4e = v86 + *v89;
          v116 = &v89[ido];
          v61 = 4 * ido + v83;
          t4b = &t4e[ci4];
          v62 = ido;
          v119 = &v122[ido];
          --v151;
        }
        while ( v151 );
      }
      if ( kb < l1 )
      {
        v152 = 16 * ido;
        v90 = 4 * ido;
        v91 = v61 + 2 * ido;
        v92 = &ch[v61];
        v93 = &ch[v91];
        v139 = &cc[t2b];
        v94 = &cc[v60];
        v95 = &cc[t0 + v60];
        v96 = &cc[t6b - 1];
        l1a = l1 - kb;
        do
        {
          v97 = -((*v139 + *v94) * hsqt2);
          v98 = *v94;
          v94 = (float *)((char *)v94 + v90);
          v99 = v98 - *v139;
          v139 = (float *)((char *)v139 + v90);
          v100 = v99 * hsqt2;
          *(v92 - 1) = v100 + *v96;
          v101 = *v96;
          v96 = (float *)((char *)v96 + v90);
          *(v93 - 1) = v101 - v100;
          *v92 = v97 - *v95;
          v92 = (float *)((char *)v92 + v152);
          v102 = v97 + *v95;
          v95 = (float *)((char *)v95 + v90);
          *v93 = v102;
          v93 = (float *)((char *)v93 + v152);
          --l1a;
        }
        while ( l1a );
      }
    }
  }
}

// FUNC: dradfg
void __usercall dradfg(
        int ido@<edx>,
        float *c1@<ecx>,
        float *ch@<eax>,
        int ip,
        int l1,
        int idl1,
        float *cc,
        float *c2,
        float *ch2,
        float *wa)
{
  long double v10; // st7
  int v11; // ebx
  int v12; // ebp
  float *v13; // edi
  float *v14; // esi
  float *v15; // esi
  int v16; // edi
  int v17; // esi
  int v18; // edi
  int v19; // esi
  unsigned int v20; // ebp
  int v21; // esi
  int v22; // esi
  int v23; // esi
  int v24; // ebp
  int v25; // edi
  float *v26; // esi
  int v27; // ebp
  float *v28; // edi
  float *v29; // ebp
  float *v30; // edi
  float *v31; // edi
  float *v32; // esi
  double v33; // st7
  double v34; // st6
  double v35; // st6
  bool v36; // zf
  int v37; // esi
  int v38; // ebp
  float *v39; // edi
  int v40; // esi
  unsigned int v41; // ebp
  int v42; // esi
  int v43; // esi
  int v44; // esi
  float *v45; // ebp
  float *v46; // esi
  double v47; // st7
  double v48; // st6
  int v49; // ebp
  int v50; // ebp
  int v51; // edi
  int v52; // esi
  int v53; // edi
  int v54; // ebp
  unsigned int v55; // ebp
  int v56; // edi
  int v57; // esi
  double v58; // st7
  int v59; // esi
  int v60; // edi
  double v61; // st7
  int v62; // esi
  int v63; // edi
  double v64; // st7
  int v65; // ebx
  float *v66; // esi
  float *v67; // edi
  double v68; // st7
  float *v69; // edi
  float *v70; // edi
  float *v71; // esi
  unsigned int v72; // ebp
  double v73; // st7
  float *v74; // edi
  int v75; // ebp
  float *v76; // esi
  int v77; // ebp
  float *v78; // esi
  int v79; // esi
  int v80; // edi
  int v81; // esi
  int v82; // esi
  int v83; // edi
  unsigned int v84; // ebp
  int v85; // edi
  int v86; // esi
  double v87; // st7
  int v88; // esi
  int v89; // edi
  double v90; // st7
  int v91; // esi
  int v92; // edi
  double v93; // st7
  float *v94; // esi
  float *v95; // edi
  double v96; // st7
  double v97; // st7
  double v98; // st7
  int v99; // ecx
  int v100; // ebp
  double v101; // st6
  int v102; // ecx
  int v103; // edi
  unsigned int v104; // ecx
  int v105; // esi
  float *v106; // ebp
  double v107; // st5
  float *v108; // ebp
  double v109; // st5
  float *v110; // ebp
  float *v111; // ecx
  double v112; // st5
  float *v113; // esi
  float *v114; // esi
  double v115; // st5
  float *v116; // esi
  double v117; // st5
  double v118; // st4
  int v119; // esi
  int v120; // edi
  int v121; // ecx
  int v122; // esi
  unsigned int v123; // ebx
  int v124; // ecx
  float *v125; // ebp
  double v126; // st3
  float *v127; // ebp
  float *v128; // ecx
  int v129; // esi
  float *v130; // edi
  double v131; // st3
  float *v132; // ebp
  double v133; // st3
  float *v134; // ebp
  float *v135; // ebp
  int v136; // ecx
  signed int v137; // esi
  float *v138; // ecx
  unsigned int v139; // edi
  double v140; // st7
  double v141; // st7
  float *v142; // ecx
  double v143; // st7
  int v144; // edi
  int v145; // ecx
  int v146; // esi
  int v147; // ecx
  int v148; // esi
  int v149; // ecx
  int v150; // esi
  int v151; // ecx
  int v152; // esi
  int v153; // ecx
  float *v154; // esi
  int v155; // ebp
  int v156; // edi
  int v157; // ebx
  int v158; // ecx
  float *v159; // ebx
  float *v160; // esi
  unsigned int v161; // ecx
  float *v162; // edi
  float *v163; // esi
  int v164; // ecx
  int v165; // ebp
  int v166; // ecx
  int v167; // esi
  int v168; // edi
  float *v169; // ebx
  int v170; // ecx
  int v171; // esi
  int v172; // edi
  int v173; // ebp
  int v174; // ecx
  int v175; // esi
  int v176; // edi
  int v177; // ecx
  int v178; // esi
  int v179; // edi
  int v180; // ecx
  int v181; // esi
  int v182; // edi
  int v183; // esi
  int v184; // ebp
  float *v185; // ecx
  int v186; // edi
  int v187; // edi
  int v188; // ebx
  int v189; // edi
  int v190; // esi
  int v191; // ebp
  int v192; // ecx
  int v193; // ebx
  int v194; // esi
  int v195; // ebp
  int v196; // edi
  int v197; // ebx
  int v198; // esi
  double v199; // st7
  int v200; // esi
  double v201; // st7
  int v202; // ecx
  int v203; // edi
  int v204; // ebx
  double v205; // st7
  int v206; // esi
  double v207; // st7
  int v208; // ecx
  int v209; // edi
  int v210; // ebx
  double v211; // st7
  int v212; // esi
  double v213; // st7
  int v214; // ecx
  int v215; // edi
  int v216; // ebx
  double v217; // st7
  double v218; // st7
  float *v219; // ebp
  float *v220; // edi
  int v221; // ebx
  float *v222; // ecx
  float *v223; // esi
  int v224; // ecx
  int v225; // esi
  float *v226; // ebp
  int v227; // esi
  float *v228; // ecx
  int v229; // eax
  float *v230; // ebx
  unsigned int v231; // edi
  double v232; // st7
  int ar1h; // [esp+0h] [ebp-68h]
  signed int ar1ha; // [esp+0h] [ebp-68h]
  signed int ar1hb; // [esp+0h] [ebp-68h]
  signed int ar1hc; // [esp+0h] [ebp-68h]
  float ar1hd; // [esp+0h] [ebp-68h]
  int ar1he; // [esp+0h] [ebp-68h]
  int ar1hf; // [esp+0h] [ebp-68h]
  int ar1hg; // [esp+0h] [ebp-68h]
  int t1; // [esp+4h] [ebp-64h]
  int t1a; // [esp+4h] [ebp-64h]
  int t1b; // [esp+4h] [ebp-64h]
  int t1c; // [esp+4h] [ebp-64h]
  int t1d; // [esp+4h] [ebp-64h]
  int t1e; // [esp+4h] [ebp-64h]
  int t1f; // [esp+4h] [ebp-64h]
  int ipph; // [esp+8h] [ebp-60h]
  int t2; // [esp+Ch] [ebp-5Ch]
  int t2a; // [esp+Ch] [ebp-5Ch]
  int t2b; // [esp+Ch] [ebp-5Ch]
  int t10; // [esp+10h] [ebp-58h]
  int t0; // [esp+14h] [ebp-54h]
  int t4; // [esp+18h] [ebp-50h]
  int t4a; // [esp+18h] [ebp-50h]
  int t4b; // [esp+18h] [ebp-50h]
  int t4c; // [esp+18h] [ebp-50h]
  int t4d; // [esp+18h] [ebp-50h]
  int t5; // [esp+1Ch] [ebp-4Ch]
  int t5a; // [esp+1Ch] [ebp-4Ch]
  int t5b; // [esp+1Ch] [ebp-4Ch]
  int t5c; // [esp+1Ch] [ebp-4Ch]
  int t5d; // [esp+1Ch] [ebp-4Ch]
  int t5e; // [esp+1Ch] [ebp-4Ch]
  int t7; // [esp+20h] [ebp-48h]
  int t7a; // [esp+20h] [ebp-48h]
  int t7b; // [esp+20h] [ebp-48h]
  int t7c; // [esp+20h] [ebp-48h]
  int ar2h; // [esp+24h] [ebp-44h]
  float *ar2ha; // [esp+24h] [ebp-44h]
  float *ar2hb; // [esp+24h] [ebp-44h]
  float ar2hc; // [esp+24h] [ebp-44h]
  int v273; // [esp+28h] [ebp-40h]
  float *v274; // [esp+28h] [ebp-40h]
  float *v275; // [esp+28h] [ebp-40h]
  float *v276; // [esp+28h] [ebp-40h]
  float *v277; // [esp+28h] [ebp-40h]
  unsigned int v278; // [esp+2Ch] [ebp-3Ch]
  int v279; // [esp+2Ch] [ebp-3Ch]
  float *v280; // [esp+2Ch] [ebp-3Ch]
  float *v281; // [esp+2Ch] [ebp-3Ch]
  float *v282; // [esp+2Ch] [ebp-3Ch]
  float *v283; // [esp+2Ch] [ebp-3Ch]
  float *v284; // [esp+2Ch] [ebp-3Ch]
  float *v285; // [esp+2Ch] [ebp-3Ch]
  unsigned int v286; // [esp+30h] [ebp-38h]
  float *v287; // [esp+30h] [ebp-38h]
  float *v288; // [esp+30h] [ebp-38h]
  float *v289; // [esp+30h] [ebp-38h]
  float *v290; // [esp+30h] [ebp-38h]
  float *v291; // [esp+34h] [ebp-34h]
  int v292; // [esp+34h] [ebp-34h]
  int v293; // [esp+34h] [ebp-34h]
  float *v294; // [esp+34h] [ebp-34h]
  int v295; // [esp+34h] [ebp-34h]
  float *v296; // [esp+38h] [ebp-30h]
  unsigned int v297; // [esp+38h] [ebp-30h]
  float *v298; // [esp+38h] [ebp-30h]
  float *v299; // [esp+38h] [ebp-30h]
  int v300; // [esp+38h] [ebp-30h]
  float *v301; // [esp+38h] [ebp-30h]
  int ik; // [esp+3Ch] [ebp-2Ch]
  float *ika; // [esp+3Ch] [ebp-2Ch]
  float *ikb; // [esp+3Ch] [ebp-2Ch]
  float *ikc; // [esp+3Ch] [ebp-2Ch]
  float *ikd; // [esp+3Ch] [ebp-2Ch]
  int ike; // [esp+3Ch] [ebp-2Ch]
  int ikf; // [esp+3Ch] [ebp-2Ch]
  float *ikg; // [esp+3Ch] [ebp-2Ch]
  int ikh; // [esp+3Ch] [ebp-2Ch]
  int i; // [esp+40h] [ebp-28h]
  int ia; // [esp+40h] [ebp-28h]
  int ib; // [esp+40h] [ebp-28h]
  float *ic; // [esp+40h] [ebp-28h]
  int id; // [esp+40h] [ebp-28h]
  int ie; // [esp+40h] [ebp-28h]
  float *ig; // [esp+40h] [ebp-28h]
  int ih; // [esp+40h] [ebp-28h]
  float *ii; // [esp+40h] [ebp-28h]
  int ij; // [esp+40h] [ebp-28h]
  int il; // [esp+40h] [ebp-28h]
  float *im; // [esp+40h] [ebp-28h]
  int in; // [esp+40h] [ebp-28h]
  unsigned int v324; // [esp+44h] [ebp-24h]
  int v325; // [esp+44h] [ebp-24h]
  float *v326; // [esp+44h] [ebp-24h]
  int v327; // [esp+44h] [ebp-24h]
  int v328; // [esp+44h] [ebp-24h]
  float *v329; // [esp+44h] [ebp-24h]
  unsigned int v330; // [esp+44h] [ebp-24h]
  int v331; // [esp+44h] [ebp-24h]
  int v332; // [esp+44h] [ebp-24h]
  float *v333; // [esp+44h] [ebp-24h]
  float *v334; // [esp+44h] [ebp-24h]
  float *v335; // [esp+44h] [ebp-24h]
  int v336; // [esp+44h] [ebp-24h]
  float *v337; // [esp+44h] [ebp-24h]
  int nbd; // [esp+48h] [ebp-20h]
  int nbda; // [esp+48h] [ebp-20h]
  float *nbdb; // [esp+48h] [ebp-20h]
  float dsp; // [esp+4Ch] [ebp-1Ch]
  float dcp; // [esp+50h] [ebp-18h]
  int dcpa; // [esp+50h] [ebp-18h]
  int t9; // [esp+54h] [ebp-14h]
  int t9a; // [esp+54h] [ebp-14h]
  int is; // [esp+58h] [ebp-10h]
  int isa; // [esp+58h] [ebp-10h]
  int isb; // [esp+58h] [ebp-10h]
  int ar1; // [esp+5Ch] [ebp-Ch]
  int ar1a; // [esp+5Ch] [ebp-Ch]
  int ar1b; // [esp+5Ch] [ebp-Ch]
  int ar1c; // [esp+5Ch] [ebp-Ch]
  float *v353; // [esp+60h] [ebp-8h]
  int v354; // [esp+60h] [ebp-8h]
  int v355; // [esp+60h] [ebp-8h]
  float *v356; // [esp+60h] [ebp-8h]
  int v357; // [esp+60h] [ebp-8h]
  int v358; // [esp+60h] [ebp-8h]
  float *v359; // [esp+60h] [ebp-8h]
  int v360; // [esp+60h] [ebp-8h]
  int v361; // [esp+60h] [ebp-8h]
  float *v362; // [esp+60h] [ebp-8h]
  int v363; // [esp+60h] [ebp-8h]
  float *ar2; // [esp+64h] [ebp-4h]
  int ar2a; // [esp+64h] [ebp-4h]
  int ar2b; // [esp+64h] [ebp-4h]
  unsigned int v367; // [esp+6Ch] [ebp+4h]
  unsigned int v368; // [esp+6Ch] [ebp+4h]
  int v369; // [esp+6Ch] [ebp+4h]
  float *v370; // [esp+6Ch] [ebp+4h]
  int idl1a; // [esp+74h] [ebp+Ch]
  int idl1b; // [esp+74h] [ebp+Ch]
  float *idl1c; // [esp+74h] [ebp+Ch]
  int idl1d; // [esp+74h] [ebp+Ch]
  int idl1e; // [esp+74h] [ebp+Ch]
  int idl1f; // [esp+74h] [ebp+Ch]
  float *idl1g; // [esp+74h] [ebp+Ch]

  v10 = tpi_0 / (double)ip;
  ipph = (ip + 1) >> 1;
  v11 = idl1;
  nbd = (ido - 1) >> 1;
  t0 = l1 * ido;
  dcp = cos(v10);
  t10 = ip * ido;
  dsp = sin(v10);
  if ( ido != 1 )
  {
    v12 = 0;
    if ( idl1 >= 4 )
    {
      v13 = c2 + 3;
      v14 = ch2 + 1;
      v324 = ((unsigned int)(idl1 - 4) >> 2) + 1;
      ik = 4 * v324;
      do
      {
        *(v14 - 1) = *(v13 - 3);
        *v14 = *(float *)((char *)v14 + (char *)c2 - (char *)ch2);
        v14[1] = *(v13 - 1);
        v14[2] = *v13;
        v14 += 4;
        v13 += 4;
        --v324;
      }
      while ( v324 );
      v12 = ik;
    }
    if ( v12 < idl1 )
    {
      v15 = &ch2[v12];
      v16 = idl1 - v12;
      do
      {
        *v15 = *(float *)((char *)v15 + (char *)c2 - (char *)ch2);
        ++v15;
        --v16;
      }
      while ( v16 );
    }
    v17 = 0;
    if ( ip > 1 )
    {
      v325 = ip - 1;
      v18 = l1;
      while ( 1 )
      {
        v19 = t0 + v17;
        t1 = v19;
        ar1h = 0;
        if ( v18 >= 4 )
        {
          v20 = ((unsigned int)(v18 - 4) >> 2) + 1;
          ar1h = 4 * v20;
          do
          {
            ch[v19] = c1[v19];
            v21 = ido + v19;
            ch[v21] = c1[v21];
            v22 = ido + v21;
            ch[v22] = c1[v22];
            v23 = ido + v22;
            ch[v23] = c1[v23];
            v19 = ido + v23;
            --v20;
          }
          while ( v20 );
          v18 = l1;
        }
        if ( ar1h < v18 )
        {
          v24 = (char *)c1 - (char *)ch;
          v25 = v18 - ar1h;
          v26 = &ch[v19];
          while ( 1 )
          {
            *v26 = *(float *)((char *)v26 + v24);
            v26 += ido;
            if ( !--v25 )
              break;
            v24 = (char *)c1 - (char *)ch;
          }
          v18 = l1;
        }
        if ( !--v325 )
          break;
        v17 = t1;
      }
    }
    v27 = -ido;
    t1a = 0;
    if ( nbd <= l1 )
    {
      if ( ip > 1 )
      {
        ia = v27 - 1;
        ikb = &wa[-ido - 1];
        v292 = ip - 1;
        do
        {
          ia += ido;
          ikb += ido;
          v37 = t0 + t1a;
          v27 += ido;
          is = v27;
          t1a += t0;
          if ( ido > 2 )
          {
            v38 = ia - v27 + v37 + 1;
            v39 = ikb;
            v297 = ((unsigned int)(ido - 3) >> 1) + 1;
            while ( 1 )
            {
              v39 += 2;
              v354 = v38 + 2;
              v40 = v38 + 2;
              ar1ha = 0;
              if ( l1 >= 4 )
              {
                ar1ha = 4 * (((unsigned int)(l1 - 4) >> 2) + 1);
                v41 = ((unsigned int)(l1 - 4) >> 2) + 1;
                do
                {
                  ch[v40 - 1] = *(v39 - 1) * c1[v40 - 1] + *v39 * c1[v40];
                  ch[v40] = *(v39 - 1) * c1[v40] - *v39 * c1[v40 - 1];
                  v42 = ido + v40;
                  ch[v42 - 1] = *(v39 - 1) * c1[v42 - 1] + *v39 * c1[v42];
                  ch[v42] = *(v39 - 1) * c1[v42] - *v39 * c1[v42 - 1];
                  v43 = ido + v42;
                  ch[v43 - 1] = *(v39 - 1) * c1[v43 - 1] + *v39 * c1[v43];
                  ch[v43] = *(v39 - 1) * c1[v43] - *v39 * c1[v43 - 1];
                  v44 = ido + v43;
                  ch[v44 - 1] = *(v39 - 1) * c1[v44 - 1] + *v39 * c1[v44];
                  ch[v44] = *(v39 - 1) * c1[v44] - *v39 * c1[v44 - 1];
                  v40 = ido + v44;
                  --v41;
                }
                while ( v41 );
              }
              if ( ar1ha < l1 )
              {
                v45 = &ch[v40];
                v46 = &c1[v40 - 1];
                v327 = l1 - ar1ha;
                do
                {
                  *(float *)((char *)v46 + (char *)ch - (char *)c1) = *v39 * v46[1] + *v46 * *(v39 - 1);
                  v47 = *(v39 - 1) * v46[1];
                  v48 = *v46;
                  v46 += ido;
                  *v45 = v47 - v48 * *v39;
                  v45 += ido;
                  --v327;
                }
                while ( v327 );
                v11 = idl1;
              }
              if ( !--v297 )
                break;
              v38 = v354;
            }
            v27 = is;
          }
          --v292;
        }
        while ( v292 );
      }
    }
    else if ( ip > 1 )
    {
      ika = &wa[-ido - 1];
      v28 = &ch[-ido];
      v29 = &c1[-ido - 1];
      ar2h = ip - 1;
      while ( 1 )
      {
        v30 = &v28[t0];
        v29 += t0;
        ika += ido;
        v326 = v30;
        v353 = v29;
        if ( l1 > 0 )
        {
          i = (int)v30;
          v296 = v29;
          v273 = l1;
          do
          {
            i += 4 * ido;
            v296 += ido;
            if ( ido > 2 )
            {
              v31 = ika;
              v291 = (float *)i;
              v32 = v296;
              v278 = ((unsigned int)(ido - 3) >> 1) + 1;
              do
              {
                v33 = v32[2] * v31[1];
                v291 += 2;
                v34 = v32[3];
                v32 += 2;
                v35 = v34 * v31[2];
                v31 += 2;
                v36 = v278-- == 1;
                *(float *)((char *)v32 + (char *)ch - (char *)c1) = v33 + v35;
                *v291 = v32[1] * *(v31 - 1) - *v31 * *v32;
              }
              while ( !v36 );
              v29 = v353;
            }
            --v273;
          }
          while ( v273 );
        }
        if ( !--ar2h )
          break;
        v28 = v326;
      }
    }
    v49 = ip * t0;
    t1b = 0;
    if ( nbd >= l1 )
    {
      if ( ipph > 1 )
      {
        ikd = &c1[v49];
        v299 = &ch[v49 - 1];
        ic = ch - 1;
        v69 = c1;
        t4 = ipph - 1;
        do
        {
          ic += t0;
          ikd -= t0;
          v299 -= t0;
          v69 += t0;
          v356 = v69;
          if ( l1 > 0 )
          {
            v274 = ic;
            v280 = v69;
            v70 = v299;
            ar2ha = ikd;
            v329 = v299;
            t7 = l1;
            do
            {
              if ( ido > 2 )
              {
                v294 = v280;
                v287 = ar2ha;
                v71 = v274;
                t5a = (char *)c1 - (char *)ch;
                v72 = ((unsigned int)(ido - 3) >> 1) + 1;
                do
                {
                  v73 = v71[2] + v70[2];
                  v294 += 2;
                  v287 += 2;
                  v71 += 2;
                  v70 += 2;
                  *(float *)((char *)v71 + t5a) = v73;
                  --v72;
                  *(float *)((char *)v70 + t5a) = v71[1] - v70[1];
                  *v294 = v70[1] + v71[1];
                  *v287 = *v70 - *v71;
                }
                while ( v72 );
                v11 = idl1;
              }
              v280 += ido;
              v274 += ido;
              ar2ha += ido;
              v70 = &v329[ido];
              v36 = t7-- == 1;
              v329 = v70;
            }
            while ( !v36 );
            v69 = v356;
          }
          --t4;
        }
        while ( t4 );
      }
    }
    else if ( ipph > 1 )
    {
      ib = -ido;
      v279 = ipph - 1;
      do
      {
        t1b += t0;
        ib += t0;
        v49 -= t0;
        t2 = v49;
        if ( ido > 2 )
        {
          v50 = v49 - t1b;
          v51 = ib;
          v355 = v50;
          v286 = ((unsigned int)(ido - 3) >> 1) + 1;
          while ( 1 )
          {
            v293 = v51 + 2;
            v52 = v51 + 2;
            v53 = v50 + v51 + 2;
            v54 = l1;
            ar1hb = 0;
            if ( l1 >= 4 )
            {
              ar1hb = 4 * (((unsigned int)(l1 - 4) >> 2) + 1);
              v55 = ((unsigned int)(l1 - 4) >> 2) + 1;
              do
              {
                v56 = ido + v53;
                v57 = ido + v52;
                c1[v57 - 1] = ch[v56 - 1] + ch[v57 - 1];
                c1[v56 - 1] = ch[v57] - ch[v56];
                c1[v57] = ch[v57] + ch[v56];
                v58 = ch[v56 - 1] - ch[v57 - 1];
                v59 = ido + v57;
                c1[v56] = v58;
                v60 = ido + v56;
                c1[v59 - 1] = ch[v60 - 1] + ch[v59 - 1];
                c1[v60 - 1] = ch[v59] - ch[v60];
                c1[v59] = ch[v59] + ch[v60];
                v61 = ch[v60 - 1] - ch[v59 - 1];
                v62 = ido + v59;
                c1[v60] = v61;
                v63 = ido + v60;
                c1[v62 - 1] = ch[v63 - 1] + ch[v62 - 1];
                c1[v63 - 1] = ch[v62] - ch[v63];
                c1[v62] = ch[v62] + ch[v63];
                v64 = ch[v63 - 1] - ch[v62 - 1];
                v52 = ido + v62;
                c1[v63] = v64;
                v53 = ido + v63;
                --v55;
                c1[v52 - 1] = ch[v53 - 1] + ch[v52 - 1];
                c1[v53 - 1] = ch[v52] - ch[v53];
                c1[v52] = ch[v52] + ch[v53];
                c1[v53] = ch[v53 - 1] - ch[v52 - 1];
              }
              while ( v55 );
              v54 = l1;
            }
            if ( ar1hb < v54 )
            {
              v298 = &c1[v53];
              ikc = &c1[v52];
              t5 = (char *)c1 - (char *)ch;
              v65 = 4 * ido;
              v66 = &ch[v52 - 1];
              v67 = &ch[v53 - 1];
              v328 = l1 - ar1hb;
              do
              {
                v68 = v66[ido] + v67[ido];
                ikc = (float *)((char *)ikc + v65);
                v298 = (float *)((char *)v298 + v65);
                v66 = (float *)((char *)v66 + v65);
                v67 = (float *)((char *)v67 + v65);
                *(float *)((char *)v66 + t5) = v68;
                v36 = v328-- == 1;
                *(float *)((char *)v67 + t5) = v66[1] - v67[1];
                *ikc = v67[1] + v66[1];
                *v298 = *v67 - *v66;
              }
              while ( !v36 );
              v11 = idl1;
            }
            v36 = v286-- == 1;
            v51 = v293;
            if ( v36 )
              break;
            v50 = v355;
          }
          v49 = t2;
        }
        --v279;
      }
      while ( v279 );
    }
  }
  v74 = ch2;
  v75 = 0;
  if ( v11 >= 4 )
  {
    v281 = ch2 + 3;
    v330 = ((unsigned int)(v11 - 4) >> 2) + 1;
    v76 = c2 + 1;
    ike = 4 * v330;
    do
    {
      *(v76 - 1) = *(v281 - 3);
      *v76 = *(float *)((char *)v76 + (char *)ch2 - (char *)c2);
      v76[1] = *(v281 - 1);
      v77 = *(_DWORD *)v281;
      v281 += 4;
      *((_DWORD *)v76 + 2) = v77;
      v76 += 4;
      --v330;
    }
    while ( v330 );
    v75 = ike;
  }
  if ( v75 < v11 )
  {
    v331 = v11 - v75;
    v78 = &c2[v75];
    do
    {
      *v78 = *(float *)((char *)v78 + (char *)ch2 - (char *)c2);
      ++v78;
      --v331;
    }
    while ( v331 );
  }
  v79 = v11 * ip;
  if ( ipph > 1 )
  {
    v80 = v79 - ido;
    v81 = -ido;
    id = ipph - 1;
    while ( 1 )
    {
      v82 = t0 + v81;
      v83 = v80 - t0;
      v357 = v82;
      ar1 = v83;
      ar1hc = 0;
      if ( l1 >= 4 )
      {
        ar1hc = 4 * (((unsigned int)(l1 - 4) >> 2) + 1);
        v84 = ((unsigned int)(l1 - 4) >> 2) + 1;
        do
        {
          v85 = ido + v83;
          v86 = ido + v82;
          c1[v86] = ch[v85] + ch[v86];
          v87 = ch[v85] - ch[v86];
          v88 = ido + v86;
          c1[v85] = v87;
          v89 = ido + v85;
          c1[v88] = ch[v89] + ch[v88];
          v90 = ch[v89] - ch[v88];
          v91 = ido + v88;
          c1[v89] = v90;
          v92 = ido + v89;
          c1[v91] = ch[v92] + ch[v91];
          v93 = ch[v92] - ch[v91];
          v82 = ido + v91;
          c1[v92] = v93;
          v83 = ido + v92;
          --v84;
          c1[v82] = ch[v83] + ch[v82];
          c1[v83] = ch[v83] - ch[v82];
        }
        while ( v84 );
      }
      if ( ar1hc < l1 )
      {
        t5b = (char *)c1 - (char *)ch;
        v94 = &ch[v82];
        v95 = &ch[v83];
        v332 = l1 - ar1hc;
        do
        {
          v96 = v95[ido];
          v95 += ido;
          v97 = v96 + v94[ido];
          v94 += ido;
          v36 = v332-- == 1;
          *(float *)((char *)v94 + t5b) = v97;
          *(float *)((char *)v95 + t5b) = *v95 - *v94;
        }
        while ( !v36 );
      }
      if ( !--id )
        break;
      v81 = v357;
      v80 = ar1;
    }
    v79 = v11 * ip;
    v74 = ch2;
  }
  v98 = 0.0;
  v295 = v11 * (ip - 1);
  v99 = (ip + 1) >> 1;
  v100 = 0;
  t2a = v79;
  if ( ipph > 1 )
  {
    v101 = 1.0;
    ikf = (int)(v74 + 2);
    v300 = (int)&v74[v79 + 2];
    v358 = ipph - 1;
    do
    {
      ikf += 4 * v11;
      v300 -= 4 * v11;
      v100 += v11;
      t2a -= v11;
      v102 = t2a;
      ar1hd = dcp * v101 - v98 * dsp;
      v103 = 0;
      t1c = v100;
      t4a = v100;
      ie = v295;
      t7a = v11;
      v98 = v101 * dsp + v98 * dcp;
      v101 = ar1hd;
      if ( v11 >= 4 )
      {
        v288 = (float *)v300;
        v275 = &c2[v11 + 2];
        v104 = ((unsigned int)(v11 - 4) >> 2) + 1;
        v282 = c2 + 2;
        v103 = 4 * v104;
        t4a = 4 * v104 + v100;
        t5c = 4 * v104 + t2a;
        ie = 4 * v104 + v295;
        ar2hb = &c2[v295 + 2];
        v105 = ikf;
        t7a = 4 * v104 + v11;
        do
        {
          v105 += 16;
          *(float *)(v105 - 24) = ar1hd * *(v275 - 2) + *(v282 - 2);
          *(v288 - 2) = v98 * *(ar2hb - 2);
          *(float *)(v105 - 20) = ar1hd * *(v275 - 1) + *(v282 - 1);
          *(v288 - 1) = v98 * *(ar2hb - 1);
          *(float *)(v105 - 16) = ar1hd * *v275 + *v282;
          *v288 = v98 * *ar2hb;
          v106 = v275;
          v275 += 4;
          v107 = ar1hd * v106[1];
          v108 = v282;
          v282 += 4;
          v109 = v107 + v108[1];
          v110 = ar2hb;
          ar2hb += 4;
          *(float *)(v105 - 12) = v109;
          --v104;
          v288[1] = v98 * v110[1];
          v288 += 4;
        }
        while ( v104 );
        v100 = t1c;
        v102 = t5c;
      }
      if ( v103 < v11 )
      {
        v289 = &ch2[v102];
        v283 = &c2[ie];
        ig = &ch2[t4a];
        v111 = &c2[t7a];
        do
        {
          v112 = ar1hd * *v111;
          ++v103;
          ++v111;
          v113 = ig++;
          *v113 = v112 + c2[v103 - 1];
          v114 = v283++;
          v115 = v98 * *v114;
          v116 = v289++;
          *v116 = v115;
        }
        while ( v103 < v11 );
      }
      v117 = v98;
      t4b = v11;
      t5d = v295;
      if ( ipph > 2 )
      {
        v118 = ar1hd;
        v290 = &c2[v295 + 2];
        v333 = &c2[v11 + 2];
        ar1a = ipph - 2;
        do
        {
          t5d -= v11;
          v119 = t2a;
          t4b += v11;
          isa = t4b;
          v333 += v11;
          v290 -= v11;
          ar2hc = ar1hd * v118 - v117 * v98;
          t9 = t5d;
          v120 = 0;
          v121 = v100;
          v117 = v117 * ar1hd + v118 * v98;
          v118 = ar2hc;
          if ( v11 >= 4 )
          {
            v122 = v300;
            v123 = ((unsigned int)(v11 - 4) >> 2) + 1;
            v284 = v333;
            v120 = 4 * v123;
            ih = 4 * v123 + v100;
            t7b = 4 * v123 + t2a;
            isa = 4 * v123 + t4b;
            v276 = v290;
            v124 = ikf;
            t9 = 4 * v123 + t5d;
            do
            {
              v124 += 16;
              v122 += 16;
              *(float *)(v124 - 24) = ar2hc * *(v284 - 2) + *(float *)(v124 - 24);
              *(float *)(v122 - 24) = v117 * *(v276 - 2) + *(float *)(v122 - 24);
              *(float *)(v124 - 20) = ar2hc * *(v284 - 1) + *(float *)(v124 - 20);
              *(float *)(v122 - 20) = v117 * *(v276 - 1) + *(float *)(v122 - 20);
              *(float *)(v124 - 16) = ar2hc * *v284 + *(float *)(v124 - 16);
              v125 = v284;
              v284 += 4;
              *(float *)(v122 - 16) = v117 * *v276 + *(float *)(v122 - 16);
              v126 = ar2hc * v125[1];
              v127 = v276;
              v276 += 4;
              --v123;
              *(float *)(v124 - 12) = v126 + *(float *)(v124 - 12);
              *(float *)(v122 - 12) = v117 * v127[1] + *(float *)(v122 - 12);
            }
            while ( v123 );
            v119 = t7b;
            v121 = ih;
            v11 = idl1;
            v100 = t1c;
          }
          if ( v120 < v11 )
          {
            v277 = &ch2[v119];
            v285 = &c2[t9];
            v128 = &ch2[v121];
            ii = &c2[isa];
            v129 = v11 - v120;
            v130 = v277;
            do
            {
              v131 = ar2hc * *ii;
              v132 = v285;
              ++ii;
              ++v285;
              v133 = v131 + *v128++;
              ++v130;
              --v129;
              *(v128 - 1) = v133;
              *(v130 - 1) = v117 * *v132 + *(v130 - 1);
            }
            while ( v129 );
            v100 = t1c;
          }
          --ar1a;
        }
        while ( ar1a );
      }
      --v358;
    }
    while ( v358 );
    v74 = ch2;
    v99 = (ip + 1) >> 1;
  }
  t1d = 0;
  if ( v99 > 1 )
  {
    v134 = c2 + 2;
    idl1a = ipph - 1;
    while ( 1 )
    {
      v135 = &v134[v11];
      t1d += v11;
      v136 = t1d;
      v137 = 0;
      ar2 = v135;
      if ( v11 >= 4 )
      {
        v138 = v74 + 2;
        v137 = 4 * (((unsigned int)(v11 - 4) >> 2) + 1);
        v139 = ((unsigned int)(v11 - 4) >> 2) + 1;
        do
        {
          v140 = *(v135 - 2);
          v135 += 4;
          v141 = v140 + *(v138 - 2);
          v138 += 4;
          --v139;
          *(v138 - 6) = v141;
          *(v138 - 5) = *(v135 - 5) + *(v138 - 5);
          *(v138 - 4) = *(v135 - 4) + *(v138 - 4);
          *(v138 - 3) = *(v135 - 3) + *(v138 - 3);
        }
        while ( v139 );
        v74 = ch2;
        v136 = v137 + t1d;
      }
      if ( v137 < v11 )
      {
        v142 = &c2[v136];
        do
        {
          v143 = *v142++ + v74[v137++];
          v74[v137 - 1] = v143;
        }
        while ( v137 < v11 );
      }
      if ( !--idl1a )
        break;
      v134 = ar2;
    }
  }
  v144 = l1;
  if ( ido >= l1 )
  {
    v155 = 0;
    t1e = 0;
    t2b = 0;
    if ( l1 > 0 )
    {
      v334 = ch + 2;
      ikg = cc + 2;
      v360 = l1;
      do
      {
        v156 = t2b;
        v157 = 0;
        v158 = v155;
        if ( ido >= 4 )
        {
          v159 = ikg;
          v160 = v334;
          v161 = ((unsigned int)(ido - 4) >> 2) + 1;
          idl1d = 4 * v161 + v155;
          il = 4 * v161;
          v156 = t2b + 4 * v161;
          do
          {
            *(v159 - 2) = *(v160 - 2);
            *(v159 - 1) = *(v160 - 1);
            *v159 = *v160;
            v159[1] = v160[1];
            v160 += 4;
            v159 += 4;
            --v161;
          }
          while ( v161 );
          v157 = il;
          v158 = idl1d;
          v155 = t1e;
        }
        if ( v157 < ido )
        {
          v162 = &cc[v156];
          v163 = &ch[v158];
          v164 = ido - v157;
          do
          {
            *v162++ = *v163++;
            --v164;
          }
          while ( v164 );
        }
        v334 += ido;
        t2b += t10;
        ikg += t10;
        v155 += ido;
        v36 = v360-- == 1;
        t1e = v155;
      }
      while ( !v36 );
    }
  }
  else
  {
    v145 = 0;
    for ( ij = 0; ij < ido; ++ij )
    {
      v146 = v145;
      ar1he = 0;
      if ( v144 >= 4 )
      {
        idl1b = ((unsigned int)(v144 - 4) >> 2) + 1;
        ar1he = 4 * idl1b;
        do
        {
          cc[v146] = ch[v145];
          v147 = ido + v145;
          v148 = t10 + v146;
          cc[v148] = ch[v147];
          v149 = ido + v147;
          v150 = t10 + v148;
          cc[v150] = ch[v149];
          v151 = ido + v149;
          v152 = t10 + v150;
          cc[v152] = ch[v151];
          v145 = ido + v151;
          v146 = t10 + v152;
          --idl1b;
        }
        while ( idl1b );
        v144 = l1;
      }
      if ( ar1he < v144 )
      {
        idl1c = &ch[v145];
        v153 = l1 - ar1he;
        v154 = &cc[v146];
        v359 = v154;
        do
        {
          *v154 = *idl1c;
          idl1c += ido;
          v154 = &v359[t10];
          --v153;
          v359 = v154;
        }
        while ( v153 );
        v144 = l1;
      }
      v145 = ij + 1;
    }
  }
  v165 = ip * t0;
  v166 = 0;
  v167 = 0;
  ar2a = ip * t0;
  v168 = ip * t0;
  if ( ipph > 1 )
  {
    v361 = ipph - 1;
    v169 = cc;
    while ( 1 )
    {
      v170 = 2 * ido + v166;
      v171 = t0 + v167;
      v172 = v168 - t0;
      v173 = l1;
      t1f = v170;
      idl1e = v171;
      t4c = v172;
      ar1hf = 0;
      if ( l1 >= 4 )
      {
        v367 = ((unsigned int)(l1 - 4) >> 2) + 1;
        ar1hf = 4 * v367;
        do
        {
          v169[v170 - 1] = ch[v171];
          v169[v170] = ch[v172];
          v174 = t10 + v170;
          v175 = ido + v171;
          v169[v174 - 1] = ch[v175];
          v176 = ido + v172;
          v169[v174] = ch[v176];
          v177 = t10 + v174;
          v178 = ido + v175;
          v169[v177 - 1] = ch[v178];
          v179 = ido + v176;
          v169[v177] = ch[v179];
          v180 = t10 + v177;
          v181 = ido + v178;
          v182 = ido + v179;
          v169[v180 - 1] = ch[v181];
          v169[v180] = ch[v182];
          v170 = t10 + v180;
          v171 = ido + v181;
          v172 = ido + v182;
          --v367;
        }
        while ( v367 );
        v173 = l1;
      }
      if ( ar1hf >= v173 )
      {
        v169 = cc;
      }
      else
      {
        v335 = &ch[v171];
        v183 = l1 - ar1hf;
        v169 = cc;
        v184 = 4 * ido;
        v185 = &cc[v170];
        im = &ch[v172];
        do
        {
          v186 = *(_DWORD *)v335;
          v335 = (float *)((char *)v335 + v184);
          *((_DWORD *)v185 - 1) = v186;
          v187 = *(_DWORD *)im;
          im = (float *)((char *)im + v184);
          *(_DWORD *)v185 = v187;
          v185 += t10;
          --v183;
        }
        while ( v183 );
      }
      if ( !--v361 )
        break;
      v168 = t4c;
      v167 = idl1e;
      v166 = t1f;
    }
    v165 = ar2a;
  }
  if ( ido != 1 )
  {
    if ( nbd >= l1 )
    {
      if ( ipph > 1 )
      {
        v337 = &ch[v165 + 2];
        v370 = ch + 2;
        idl1g = cc - 2;
        v224 = 4 * t0;
        v225 = 8 * ido;
        nbdb = cc + 2;
        ar1c = ipph - 1;
        while ( 1 )
        {
          idl1g = (float *)((char *)idl1g + v225);
          nbdb = (float *)((char *)nbdb + v225);
          v370 = (float *)((char *)v370 + v224);
          v337 = (float *)((char *)v337 - v224);
          if ( l1 > 0 )
          {
            v226 = nbdb;
            ikh = (int)v370;
            in = (int)idl1g;
            v301 = v337;
            v363 = l1;
            do
            {
              if ( ido > 2 )
              {
                v227 = ikh;
                v228 = v301;
                v229 = in;
                v230 = v226;
                v231 = ((unsigned int)(ido - 3) >> 1) + 1;
                do
                {
                  v230 += 2;
                  v232 = *(float *)(v227 - 4) + *(v228 - 1);
                  v228 += 2;
                  v227 += 8;
                  v229 -= 8;
                  --v231;
                  *(v230 - 3) = v232;
                  *(float *)(v229 + 4) = *(float *)(v227 - 12) - *(v228 - 3);
                  *(v230 - 2) = *(float *)(v227 - 8) + *(v228 - 2);
                  *(float *)(v229 + 8) = *(v228 - 2) - *(float *)(v227 - 8);
                }
                while ( v231 );
              }
              in += 4 * t10;
              v226 += t10;
              ikh += 4 * ido;
              v301 += ido;
              --v363;
            }
            while ( v363 );
          }
          if ( !--ar1c )
            break;
          v225 = 8 * ido;
          v224 = 4 * t0;
        }
      }
    }
    else
    {
      v188 = 0;
      v189 = 0;
      v190 = v165;
      if ( ipph > 1 )
      {
        v191 = -2;
        t9a = ipph - 1;
        do
        {
          v191 += 2 * ido;
          v188 += 2 * ido;
          v189 += t0;
          v190 -= t0;
          v336 = v191;
          idl1f = v188;
          t4d = v189;
          t5e = v190;
          if ( ido > 2 )
          {
            v192 = v189 + 2;
            v193 = v188 - v189;
            v194 = v190 - v189;
            ar1b = v189 + 2;
            nbda = v191;
            dcpa = v193;
            ar2b = v194;
            isb = ((unsigned int)(ido - 3) >> 1) + 1;
            while ( 1 )
            {
              v195 = l1;
              v196 = nbda;
              v197 = v192 + v193;
              v198 = v192 + v194;
              t7c = v197;
              ar1hg = 0;
              if ( l1 >= 4 )
              {
                v368 = ((unsigned int)(l1 - 4) >> 2) + 1;
                ar1hg = 4 * v368;
                do
                {
                  cc[v197 - 1] = ch[v198 - 1] + ch[v192 - 1];
                  cc[v196 - 1] = ch[v192 - 1] - ch[v198 - 1];
                  cc[v197] = ch[v198] + ch[v192];
                  v199 = ch[v198];
                  v200 = ido + v198;
                  v201 = v199 - ch[v192];
                  v202 = ido + v192;
                  cc[v196] = v201;
                  v203 = t10 + v196;
                  v204 = t10 + v197;
                  cc[v204 - 1] = ch[v200 - 1] + ch[v202 - 1];
                  cc[v203 - 1] = ch[v202 - 1] - ch[v200 - 1];
                  cc[v204] = ch[v200] + ch[v202];
                  v205 = ch[v200];
                  v206 = ido + v200;
                  v207 = v205 - ch[v202];
                  v208 = ido + v202;
                  cc[v203] = v207;
                  v209 = t10 + v203;
                  v210 = t10 + v204;
                  cc[v210 - 1] = ch[v206 - 1] + ch[v208 - 1];
                  cc[v209 - 1] = ch[v208 - 1] - ch[v206 - 1];
                  cc[v210] = ch[v206] + ch[v208];
                  v211 = ch[v206];
                  v212 = ido + v206;
                  v213 = v211 - ch[v208];
                  v214 = ido + v208;
                  cc[v209] = v213;
                  v215 = t10 + v209;
                  v216 = t10 + v210;
                  cc[v216 - 1] = ch[v212 - 1] + ch[v214 - 1];
                  cc[v215 - 1] = ch[v214 - 1] - ch[v212 - 1];
                  cc[v216] = ch[v212] + ch[v214];
                  v217 = ch[v212];
                  v198 = ido + v212;
                  v218 = v217 - ch[v214];
                  v192 = ido + v214;
                  cc[v215] = v218;
                  v196 = t10 + v215;
                  v197 = t10 + v216;
                  --v368;
                }
                while ( v368 );
                v195 = l1;
                t7c = v197;
              }
              if ( ar1hg < v195 )
              {
                v369 = 4 * t10;
                v219 = &cc[t7c];
                v220 = &cc[v196];
                v221 = l1 - ar1hg;
                v222 = &ch[v192];
                v223 = &ch[v198];
                v362 = v219;
                while ( 1 )
                {
                  *(v219 - 1) = *(v222 - 1) + *(v223 - 1);
                  *(v220 - 1) = *(v222 - 1) - *(v223 - 1);
                  *v219 = *v222 + *v223;
                  v219 = &v362[v369 / 4u];
                  v362 = (float *)((char *)v362 + v369);
                  *v220 = *v223 - *v222;
                  v222 += ido;
                  v223 += ido;
                  if ( !--v221 )
                    break;
                  v220 = (float *)((char *)v220 + v369);
                }
              }
              nbda -= 2;
              v192 = ar1b + 2;
              v36 = isb-- == 1;
              ar1b += 2;
              if ( v36 )
                break;
              v194 = ar2b;
              v193 = dcpa;
            }
            v188 = idl1f;
            v189 = t4d;
            v190 = t5e;
            v191 = v336;
          }
          --t9a;
        }
        while ( t9a );
      }
    }
  }
}

// FUNC: drftf1
void __usercall drftf1(float *c@<edi>, int *ifac@<ecx>, int n, float *ch, float *wa)
{
  int v5; // eax
  int v6; // esi
  int v7; // ecx
  int v8; // ebx
  int v9; // esi
  int v10; // eax
  float *v11; // edx
  float *v12; // eax
  bool v13; // zf
  int v14; // edx
  int v15; // ecx
  unsigned int v16; // edx
  float *v17; // ecx
  float *v18; // eax
  float *v19; // eax
  int v20; // edx
  float *v21; // [esp-8h] [ebp-24h]
  float *v22; // [esp-8h] [ebp-24h]
  int iw; // [esp+8h] [ebp-14h]
  int na; // [esp+Ch] [ebp-10h]
  int *v25; // [esp+10h] [ebp-Ch]
  int idl1; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int ia; // [esp+18h] [ebp-4h]

  v5 = ifac[1];
  v6 = n;
  na = 1;
  iw = n;
  if ( v5 > 0 )
  {
    v25 = &ifac[v5 + 1];
    i = ifac[1];
    do
    {
      v7 = *v25;
      v8 = v6 / *v25;
      v9 = n / v6;
      idl1 = v8 * v9;
      iw -= v9 * (*v25 - 1);
      v10 = 1 - na;
      na = 1 - na;
      if ( *v25 == 4 )
      {
        if ( na )
        {
          v11 = c;
          v12 = ch;
        }
        else
        {
          v11 = ch;
          v12 = c;
        }
        dradf4(v9, v12, v11, v8, &wa[iw - 1], &wa[v9 - 1 + iw], &wa[v9 - 1 + iw + v9]);
      }
      else if ( v7 == 2 )
      {
        v22 = &wa[iw - 1];
        if ( v10 )
          dradf2(v9, ch, c, v8, v22);
        else
          dradf2(v9, c, ch, v8, v22);
      }
      else
      {
        if ( v9 == 1 )
          v10 = 1 - v10;
        v21 = &wa[iw - 1];
        if ( v10 )
        {
          dradfg(v9, ch, c, v7, v8, idl1, ch, ch, c, v21);
          na = 0;
        }
        else
        {
          dradfg(v9, c, ch, v7, v8, idl1, c, c, ch, v21);
          na = 1;
        }
      }
      --v25;
      v13 = i-- == 1;
      v6 = v8;
    }
    while ( !v13 );
    if ( na != 1 )
    {
      v14 = n;
      v15 = 0;
      if ( n >= 4 )
      {
        v16 = ((unsigned int)(n - 4) >> 2) + 1;
        v17 = ch + 3;
        v18 = c + 1;
        ia = 4 * v16;
        do
        {
          *(v18 - 1) = *(v17 - 3);
          *v18 = *(float *)((char *)v18 + (char *)ch - (char *)c);
          v18[1] = *(v17 - 1);
          v18[2] = *v17;
          v18 += 4;
          v17 += 4;
          --v16;
        }
        while ( v16 );
        v15 = ia;
        v14 = n;
      }
      if ( v15 < v14 )
      {
        v19 = &c[v15];
        v20 = v14 - v15;
        do
        {
          *v19 = *(float *)((char *)v19 + (char *)ch - (char *)c);
          ++v19;
          --v20;
        }
        while ( v20 );
      }
    }
  }
}

// FUNC: _drft_forward
void __cdecl drft_forward(drft_lookup *l, float *data)
{
  if ( l->n != 1 )
    drftf1(data, l->splitcache, l->n, l->trigcache, &l->trigcache[l->n]);
}

// FUNC: _drft_init
void __cdecl drft_init(drft_lookup *l, int n)
{
  int *v2; // eax

  l->n = n;
  l->trigcache = (float *)_decoder_calloc(3 * n, 4u);
  v2 = (int *)_decoder_calloc(0x20u, 4u);
  l->splitcache = v2;
  if ( n != 1 )
    drfti1(n, &l->trigcache[n], v2);
}

// FUNC: _drft_clear
void __cdecl drft_clear(drft_lookup *l)
{
  if ( l )
  {
    if ( l->trigcache )
      _decoder_free(l->trigcache);
    if ( l->splitcache )
      _decoder_free(l->splitcache);
    l->n = 0;
    l->trigcache = 0;
    l->splitcache = 0;
  }
}
