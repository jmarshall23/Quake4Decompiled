
// FUNC: __vorbis_window_get
float *__cdecl _vorbis_window_get(int n)
{
  return vwin[n];
}

// FUNC: __vorbis_apply_window
void __cdecl _vorbis_apply_window(float *d, int *winno, float *blocksizes, int lW, int W, float *nW)
{
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  int v10; // kr00_4
  int v11; // ebx
  int v12; // esi
  int v13; // edx
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  float *v17; // ecx
  double v18; // st7
  int v19; // edx
  float *v20; // eax
  float *v21; // ebx
  unsigned int v22; // ecx
  double v23; // st7
  double v24; // st7
  float *v25; // eax
  double v26; // st7
  int *winnoa; // [esp+18h] [ebp+8h]
  int lWa; // [esp+20h] [ebp+10h]
  float *n; // [esp+24h] [ebp+14h]

  v7 = W != 0 ? lW : 0;
  v8 = W != 0 ? (unsigned int)nW : 0;
  n = vwin[winno[v8]];
  lWa = LODWORD(blocksizes[W]);
  winnoa = (int *)vwin[winno[v7]];
  v9 = LODWORD(blocksizes[v8]);
  v10 = LODWORD(blocksizes[v7]);
  v11 = lWa / 4 - v10 / 4;
  v12 = lWa / 4 + lWa / 2 - v9 / 4;
  v13 = v9 / 2;
  v14 = v11 + v10 / 2;
  v15 = v9 / 2 + v12;
  v16 = 0;
  if ( v11 > 0 )
  {
    memset(d, 0, 4 * v11);
    v16 = lWa / 4 - v10 / 4;
  }
  if ( v16 < v14 )
  {
    v17 = (float *)winnoa;
    do
    {
      v18 = *v17++ * d[v16++];
      d[v16 - 1] = v18;
    }
    while ( v16 < v14 );
  }
  v19 = v13 - 1;
  if ( v15 - v12 >= 4 )
  {
    v20 = &d[v12 + 2];
    v21 = &n[v19 - 2];
    v22 = ((unsigned int)(v15 - v12 - 4) >> 2) + 1;
    v12 += 4 * v22;
    v19 -= 4 * v22;
    do
    {
      v23 = v21[2];
      v21 -= 4;
      v24 = v23 * *(v20 - 2);
      v20 += 4;
      --v22;
      *(v20 - 6) = v24;
      *(v20 - 5) = v21[5] * *(v20 - 5);
      *(v20 - 4) = v21[4] * *(v20 - 4);
      *(v20 - 3) = v21[3] * *(v20 - 3);
    }
    while ( v22 );
  }
  if ( v12 < v15 )
  {
    v25 = &n[v19];
    do
    {
      v26 = *v25-- * d[v12++];
      d[v12 - 1] = v26;
    }
    while ( v12 < v15 );
  }
  if ( v12 < lWa )
    memset(&d[v12], 0, 4 * (lWa - v12));
}
