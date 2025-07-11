
// FUNC: void __cdecl R_ImageStats_f(class idCmdArgs const &)
void __cdecl R_ImageStats_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax
  idImageManager_vtbl *v3; // edx
  int v4; // esi
  int v5; // edi
  idImage *v6; // eax
  idImage *v7; // ebx
  unsigned __int8 *v8; // ecx
  double v9; // st7
  int v10; // esi
  const idCmdArgs *v11; // edi
  int v12; // eax
  unsigned __int8 v13; // al
  double v14; // st6
  unsigned __int8 v15; // dl
  char *v16; // ecx
  unsigned __int8 v17; // bl
  char v18; // bl
  unsigned __int8 *v19; // ecx
  double v20; // st6
  double v21; // st7
  unsigned __int8 v22; // al
  double v23; // st6
  unsigned __int8 v24; // dl
  char *v25; // ecx
  unsigned __int8 v26; // bl
  char v27; // bl
  unsigned __int8 *v28; // ecx
  double v29; // st6
  unsigned __int8 v30; // al
  double v31; // st7
  unsigned __int8 v32; // dl
  char *v33; // ecx
  unsigned __int8 v34; // bl
  char v35; // bl
  unsigned __int8 *v36; // ecx
  double v37; // st7
  unsigned __int8 v38; // al
  double v39; // st7
  unsigned __int8 v40; // dl
  _BYTE *v41; // ecx
  unsigned __int8 v42; // bl
  char v43; // bl
  double v44; // st7
  int v45; // esi
  unsigned __int8 v46; // al
  double v47; // st6
  unsigned __int8 v48; // dl
  _BYTE *v49; // ecx
  unsigned __int8 v50; // bl
  char v51; // bl
  double v52; // st5
  idImageManager_vtbl *v53; // edx
  int totalBrightPixels; // [esp+20h] [ebp-40h]
  float tint; // [esp+24h] [ebp-3Ch]
  float tinta; // [esp+24h] [ebp-3Ch]
  float tintb; // [esp+24h] [ebp-3Ch]
  float cutoffHi; // [esp+28h] [ebp-38h]
  int numImages; // [esp+2Ch] [ebp-34h]
  float totalLuma; // [esp+30h] [ebp-30h]
  int numImagesInRange; // [esp+34h] [ebp-2Ch]
  int totalPixels; // [esp+38h] [ebp-28h]
  unsigned int v63; // [esp+3Ch] [ebp-24h]
  idImage *image; // [esp+40h] [ebp-20h]
  unsigned __int8 *pixels; // [esp+44h] [ebp-1Ch] BYREF
  int i; // [esp+48h] [ebp-18h]
  float cutoffLo; // [esp+4Ch] [ebp-14h]
  int width; // [esp+50h] [ebp-10h] BYREF
  int height[3]; // [esp+54h] [ebp-Ch] BYREF
  const idCmdArgs *argsa; // [esp+64h] [ebp+4h]
  unsigned __int8 argsb; // [esp+64h] [ebp+4h]
  float argsg; // [esp+64h] [ebp+4h]
  unsigned __int8 argsc; // [esp+64h] [ebp+4h]
  unsigned __int8 argsd; // [esp+64h] [ebp+4h]
  unsigned __int8 argse; // [esp+64h] [ebp+4h]
  float argsh; // [esp+64h] [ebp+4h]
  unsigned __int8 argsf; // [esp+64h] [ebp+4h]

  if ( args->argc >= 3 )
  {
    if ( args->argc <= 1 )
      v1 = &entityFilter;
    else
      v1 = args->argv[1];
    cutoffLo = atof(v1);
    if ( args->argc <= 2 )
      v2 = &entityFilter;
    else
      v2 = args->argv[2];
    cutoffHi = atof(v2);
    v3 = globalImages->__vftable;
    v4 = 0;
    v5 = 0;
    totalLuma = 0.0;
    numImages = 0;
    numImagesInRange = 0;
    totalPixels = 0;
    totalBrightPixels = 0;
    i = 0;
    if ( v3->GetNumImages(globalImages) > 0 )
    {
      do
      {
        v6 = globalImages->GetImageByIndex(globalImages, v4);
        v7 = v6;
        image = v6;
        if ( v6 )
        {
          if ( v6->depth == TD_DIFFUSE )
          {
            R_LoadImage(v6->imgName.data, &pixels, &width, height, 0, 1);
            v8 = pixels;
            if ( pixels )
            {
              v9 = 0.0;
              v10 = height[0] * width;
              tint = 0.0;
              v11 = 0;
              v12 = 0;
              argsa = 0;
              if ( height[0] * width >= 4 )
              {
                v63 = ((unsigned int)(v10 - 4) >> 2) + 1;
                height[1] = 4 * v63;
                do
                {
                  v13 = *v8;
                  v14 = 0.0;
                  v15 = v8[1];
                  v16 = (char *)(v8 + 1);
                  v17 = v16[1];
                  v16 += 2;
                  argsb = v17;
                  v18 = *v16;
                  v19 = (unsigned __int8 *)(v16 + 1);
                  if ( v18 )
                  {
                    v11 = (const idCmdArgs *)((char *)v11 + 1);
                    if ( v13 <= v15 )
                    {
                      if ( v15 <= argsb )
                        v14 = (double)argsb;
                      else
                        v14 = (double)v15;
                    }
                    else if ( v13 <= argsb )
                    {
                      v14 = (double)argsb;
                    }
                    else
                    {
                      v14 = (double)v13;
                    }
                  }
                  v20 = v14 * 0.0039215689;
                  argsg = v20;
                  v21 = v9 + v20;
                  if ( argsg > (double)cutoffHi )
                    ++totalBrightPixels;
                  v22 = *v19;
                  v23 = 0.0;
                  v24 = v19[1];
                  v25 = (char *)(v19 + 1);
                  v26 = v25[1];
                  v25 += 2;
                  argsc = v26;
                  v27 = *v25;
                  v28 = (unsigned __int8 *)(v25 + 1);
                  if ( v27 )
                  {
                    v11 = (const idCmdArgs *)((char *)v11 + 1);
                    if ( v22 <= v24 )
                    {
                      if ( v24 <= argsc )
                        v23 = (double)argsc;
                      else
                        v23 = (double)v24;
                    }
                    else if ( v22 <= argsc )
                    {
                      v23 = (double)argsc;
                    }
                    else
                    {
                      v23 = (double)v22;
                    }
                  }
                  v29 = v23 * 0.0039215689;
                  tinta = v29 + v21;
                  if ( v29 > cutoffHi )
                    ++totalBrightPixels;
                  v30 = *v28;
                  v31 = 0.0;
                  v32 = v28[1];
                  v33 = (char *)(v28 + 1);
                  v34 = v33[1];
                  v33 += 2;
                  argsd = v34;
                  v35 = *v33;
                  v36 = (unsigned __int8 *)(v33 + 1);
                  if ( v35 )
                  {
                    v11 = (const idCmdArgs *)((char *)v11 + 1);
                    if ( v30 <= v32 )
                    {
                      if ( v32 <= argsd )
                        v31 = (double)argsd;
                      else
                        v31 = (double)v32;
                    }
                    else if ( v30 <= argsd )
                    {
                      v31 = (double)argsd;
                    }
                    else
                    {
                      v31 = (double)v30;
                    }
                  }
                  v37 = v31 * 0.0039215689;
                  tintb = tinta + v37;
                  if ( v37 > cutoffHi )
                    ++totalBrightPixels;
                  v38 = *v36;
                  v39 = 0.0;
                  v40 = v36[1];
                  v41 = v36 + 1;
                  v42 = v41[1];
                  v41 += 2;
                  argse = v42;
                  v43 = *v41;
                  v8 = v41 + 1;
                  if ( v43 )
                  {
                    v11 = (const idCmdArgs *)((char *)v11 + 1);
                    if ( v38 <= v40 )
                    {
                      if ( v40 <= argse )
                        v39 = (double)argse;
                      else
                        v39 = (double)v40;
                    }
                    else if ( v38 <= argse )
                    {
                      v39 = (double)argse;
                    }
                    else
                    {
                      v39 = (double)v38;
                    }
                  }
                  v44 = v39 * 0.0039215689;
                  argsh = v44;
                  v9 = v44 + tintb;
                  tint = v9;
                  if ( argsh > (double)cutoffHi )
                    ++totalBrightPixels;
                  --v63;
                }
                while ( v63 );
                v12 = height[1];
                v7 = image;
                argsa = v11;
              }
              if ( v12 < v10 )
              {
                v45 = v10 - v12;
                do
                {
                  v46 = *v8;
                  v47 = 0.0;
                  v48 = v8[1];
                  v49 = v8 + 1;
                  v50 = v49[1];
                  v49 += 2;
                  argsf = v50;
                  v51 = *v49;
                  v8 = v49 + 1;
                  if ( v51 )
                  {
                    v11 = (const idCmdArgs *)((char *)v11 + 1);
                    if ( v46 <= v48 )
                    {
                      if ( v48 <= argsf )
                        v47 = (double)argsf;
                      else
                        v47 = (double)v48;
                    }
                    else if ( v46 <= argsf )
                    {
                      v47 = (double)argsf;
                    }
                    else
                    {
                      v47 = (double)v46;
                    }
                  }
                  v52 = v47 * 0.0039215689;
                  v9 = v9 + v52;
                  if ( v52 > cutoffHi )
                    ++totalBrightPixels;
                  --v45;
                }
                while ( v45 );
                v7 = image;
                tint = v9;
                argsa = v11;
              }
              if ( v9 != 0.0 )
              {
                v9 = v9 / (double)(int)argsa;
                tint = v9;
              }
              totalPixels += (int)v11;
              if ( v9 < cutoffLo || v9 > cutoffHi )
              {
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "%0.4g: %s\n",
                  v9,
                  v7->imgName.data);
                ++numImagesInRange;
              }
              R_StaticFree(pixels);
              v4 = i;
              v5 = ++numImages;
              totalLuma = tint + totalLuma;
            }
          }
        }
        v53 = globalImages->__vftable;
        i = ++v4;
      }
      while ( v4 < v53->GetNumImages(globalImages) );
      if ( v5 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Average intensity of %g from %d diffuse images\n",
          totalLuma / (double)numImages,
          v5);
        *(double *)&height[1] = cutoffHi;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%d%% lie between %g and %g\n",
          100 * (v5 - numImagesInRange) / v5,
          cutoffLo,
          cutoffHi);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%g%% of pixels are brighter than %g\n",
          (double)totalBrightPixels * 100.0 / (double)totalPixels,
          *(_QWORD *)&height[1]);
      }
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Usage - imageStats <lo> <hi>\n");
  }
}
