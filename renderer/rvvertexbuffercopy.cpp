
// FUNC: ConvertFloat16PairToFloat
void __usercall ConvertFloat16PairToFloat(float *destFloats@<ebx>, unsigned int float16Pair@<eax>)
{
  unsigned int i; // esi
  unsigned int v4; // eax
  __int16 v5; // cx
  int v6; // ecx
  int v7; // edx
  BOOL v8; // eax
  float result; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    v4 = (unsigned __int16)float16Pair;
    v5 = float16Pair;
    float16Pair >>= 16;
    v6 = v5 & 0x3FF;
    if ( (v4 & 0x7C00) != 0 )
    {
      v7 = (v4 >> 10) & 0x1F;
    }
    else if ( v6 )
    {
      v7 = 1;
      do
      {
        LOWORD(v6) = 2 * v6;
        --v7;
      }
      while ( (v6 & 0x400) == 0 );
      v6 &= 0x3FFu;
    }
    else
    {
      v7 = -112;
    }
    LODWORD(result) = ((v7 + 112) << 23) | ((v6 | (8 * (v4 & 0xFFFF8000))) << 13);
    v8 = i == 0;
    destFloats[v8] = result;
  }
}

// FUNC: ConvertFloatToFloat16Pair
void __usercall ConvertFloatToFloat16Pair(unsigned int *float16Pair@<edx>, const float *srcFloats@<eax>)
{
  unsigned int v3; // eax
  unsigned int v4; // ecx
  unsigned int v5; // eax
  int v6; // ecx
  unsigned int v7; // eax
  int v8; // esi
  unsigned int v9; // eax
  int v10; // edi
  unsigned int v11; // eax
  unsigned int floatValue; // [esp+Ch] [ebp-4h]

  *float16Pair = 0;
  v3 = *(_DWORD *)srcFloats;
  v4 = HIWORD(v3);
  v5 = v3 & 0x7FFFFFFF;
  v6 = v4 & 0x8000;
  if ( v5 <= 0x47FFEFFF )
  {
    if ( v5 >= 0x38800000 )
      v7 = v5 - 939524096;
    else
      v7 = (v5 & 0x7FFFFF | 0x800000) >> (113 - (v5 >> 23));
    *float16Pair = v6 | ((((v7 >> 13) & 1) + v7 + 4095) >> 13);
  }
  else
  {
    *float16Pair = v6 | 0x7FFF;
  }
  *float16Pair <<= 16;
  v8 = *float16Pair;
  floatValue = *((_DWORD *)srcFloats + 1);
  v9 = floatValue & 0x7FFFFFFF;
  v10 = HIWORD(floatValue) & 0x8000;
  if ( (floatValue & 0x7FFFFFFF) <= 0x47FFEFFF )
  {
    if ( v9 >= 0x38800000 )
      v11 = v9 - 939524096;
    else
      v11 = (floatValue & 0x7FFFFF | 0x800000) >> (113 - (v9 >> 23));
    *float16Pair = v10 | v8 | ((((v11 >> 13) & 1) + v11 + 4095) >> 13);
  }
  else
  {
    *float16Pair = v10 | v8 | 0x7FFF;
  }
}

// FUNC: rvVtxCopyFloatToFloat
void __fastcall rvVtxCopyFloatToFloat(
        unsigned __int8 *srcPtr,
        int destStride,
        float *destPtr,
        int destNumValuesPerComponent,
        int srcStride,
        int srcNumValuesPerComponent,
        int numComponents,
        const unsigned int *copyMapping,
        const float *srcTailPtr,
        bool absFlag)
{
  const float *v10; // ebx
  int v11; // edi
  float *v13; // ecx
  int v14; // eax
  const unsigned __int8 *v15; // edi
  float *v16; // ecx
  const unsigned __int8 *v17; // edi
  float *v18; // ecx
  const unsigned __int8 *v19; // edi
  float *v20; // ecx
  const unsigned __int8 *v21; // edi
  const unsigned __int8 *v22; // edi
  int v23; // eax
  const unsigned __int8 *v24; // edi
  float *v25; // ecx
  const unsigned __int8 *v26; // edi
  float *v27; // ecx
  const unsigned __int8 *v28; // edi
  float *v29; // ecx
  const unsigned __int8 *v30; // edi
  const unsigned __int8 *v31; // edi
  int v32; // eax
  float *v33; // edi
  float *v34; // ecx
  float *v35; // edi
  float *v36; // ecx
  float *v37; // edi
  float *v38; // ecx
  float *v39; // edi
  float *v40; // edi
  int v41; // eax
  const unsigned int *v42; // eax
  float *v43; // edi
  float *v44; // ecx
  float *v45; // edi
  float *v46; // ecx
  float *v47; // edi
  float *v48; // ecx
  float *v49; // edi
  float *v50; // edi
  int v51; // ecx
  unsigned __int8 *v52; // eax
  int v53; // esi
  int v54; // edi
  unsigned int v55; // esi
  unsigned __int8 *v56; // eax
  unsigned __int8 *v57; // eax
  unsigned __int8 *v58; // eax
  int v59; // esi
  int v60; // esi
  int v61; // edi
  unsigned int v62; // esi
  unsigned __int8 *v63; // eax
  unsigned __int8 *v64; // eax
  unsigned __int8 *v65; // eax
  int v66; // esi
  int v67; // esi
  int v68; // edi
  unsigned int v69; // esi
  unsigned __int8 *v70; // eax
  unsigned __int8 *v71; // eax
  unsigned __int8 *v72; // eax
  int v73; // esi
  int v74; // esi
  int v75; // edi
  unsigned int v76; // esi
  unsigned __int8 *v77; // eax
  unsigned __int8 *v78; // eax
  unsigned __int8 *v79; // eax
  int v80; // esi
  float *v81; // eax
  int v82; // esi
  unsigned int v83; // ecx
  float *v84; // eax
  float *v85; // eax
  float *v86; // eax
  int v87; // ecx
  int v88; // esi
  unsigned int v89; // ecx
  float *v90; // eax
  float *v91; // eax
  float *v92; // eax
  int v93; // ecx
  int v94; // esi
  unsigned int v95; // ecx
  float *v96; // eax
  float *v97; // eax
  float *v98; // eax
  int v99; // ecx
  int curComponent; // [esp+10h] [ebp-Ch]
  int curComponenta; // [esp+10h] [ebp-Ch]
  int curComponentb; // [esp+10h] [ebp-Ch]
  int curComponentc; // [esp+10h] [ebp-Ch]
  const unsigned int *v104; // [esp+14h] [ebp-8h]
  const unsigned int *v105; // [esp+14h] [ebp-8h]
  const unsigned int *v106; // [esp+14h] [ebp-8h]
  unsigned int v107; // [esp+18h] [ebp-4h]
  unsigned int v108; // [esp+18h] [ebp-4h]
  unsigned int v109; // [esp+18h] [ebp-4h]
  unsigned int v110; // [esp+18h] [ebp-4h]

  v10 = srcTailPtr;
  v11 = destNumValuesPerComponent;
  v13 = destPtr;
  if ( destNumValuesPerComponent > srcNumValuesPerComponent )
    v11 = srcNumValuesPerComponent;
  switch ( v11 )
  {
    case 1:
      v14 = 0;
      curComponent = 0;
      if ( numComponents >= 4 )
      {
        v104 = copyMapping + 2;
        v107 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        curComponent = 4 * v107;
        do
        {
          if ( copyMapping )
          {
            v15 = &srcPtr[srcStride * *(v104 - 2)];
          }
          else
          {
            v15 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
            *v13 = fabs(*(float *)v15);
          else
            *v13 = *(float *)v15;
          v16 = (float *)((char *)v13 + destStride);
          if ( copyMapping )
          {
            v17 = &srcPtr[srcStride * *(v104 - 1)];
          }
          else
          {
            v17 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
            *v16 = fabs(*(float *)v17);
          else
            *v16 = *(float *)v17;
          v18 = (float *)((char *)v16 + destStride);
          if ( copyMapping )
          {
            v19 = &srcPtr[srcStride * *v104];
          }
          else
          {
            v19 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
            *v18 = fabs(*(float *)v19);
          else
            *v18 = *(float *)v19;
          v20 = (float *)((char *)v18 + destStride);
          if ( copyMapping )
          {
            v21 = &srcPtr[srcStride * v104[1]];
          }
          else
          {
            v21 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
            *v20 = fabs(*(float *)v21);
          else
            *v20 = *(float *)v21;
          v104 += 4;
          v13 = (float *)((char *)v20 + destStride);
          --v107;
        }
        while ( v107 );
        v14 = curComponent;
      }
      if ( v14 < numComponents )
      {
        do
        {
          if ( copyMapping )
          {
            v22 = &srcPtr[srcStride * copyMapping[v14]];
          }
          else
          {
            v22 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
            *v13 = fabs(*(float *)v22);
          else
            *v13 = *(float *)v22;
          v14 = curComponent + 1;
          v13 = (float *)((char *)v13 + destStride);
          ++curComponent;
        }
        while ( curComponent < numComponents );
      }
      break;
    case 2:
      v23 = 0;
      curComponenta = 0;
      if ( numComponents >= 4 )
      {
        v105 = copyMapping + 2;
        v108 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        curComponenta = 4 * v108;
        do
        {
          if ( copyMapping )
          {
            v24 = &srcPtr[srcStride * *(v105 - 2)];
          }
          else
          {
            v24 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v13 = fabs(*(float *)v24);
            v13[1] = fabs(*((float *)v24 + 1));
          }
          else
          {
            *v13 = *(float *)v24;
            v13[1] = *((float *)v24 + 1);
          }
          v25 = (float *)((char *)v13 + destStride);
          if ( copyMapping )
          {
            v26 = &srcPtr[srcStride * *(v105 - 1)];
          }
          else
          {
            v26 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v25 = fabs(*(float *)v26);
            v25[1] = fabs(*((float *)v26 + 1));
          }
          else
          {
            *v25 = *(float *)v26;
            v25[1] = *((float *)v26 + 1);
          }
          v27 = (float *)((char *)v25 + destStride);
          if ( copyMapping )
          {
            v28 = &srcPtr[srcStride * *v105];
          }
          else
          {
            v28 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v27 = fabs(*(float *)v28);
            v27[1] = fabs(*((float *)v28 + 1));
          }
          else
          {
            *v27 = *(float *)v28;
            v27[1] = *((float *)v28 + 1);
          }
          v29 = (float *)((char *)v27 + destStride);
          if ( copyMapping )
          {
            v30 = &srcPtr[srcStride * v105[1]];
          }
          else
          {
            v30 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v29 = fabs(*(float *)v30);
            v29[1] = fabs(*((float *)v30 + 1));
          }
          else
          {
            *v29 = *(float *)v30;
            v29[1] = *((float *)v30 + 1);
          }
          v105 += 4;
          v13 = (float *)((char *)v29 + destStride);
          --v108;
        }
        while ( v108 );
        v23 = curComponenta;
      }
      if ( v23 < numComponents )
      {
        do
        {
          if ( copyMapping )
          {
            v31 = &srcPtr[srcStride * copyMapping[v23]];
          }
          else
          {
            v31 = srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v13 = fabs(*(float *)v31);
            v13[1] = fabs(*((float *)v31 + 1));
          }
          else
          {
            *v13 = *(float *)v31;
            v13[1] = *((float *)v31 + 1);
          }
          v23 = curComponenta + 1;
          v13 = (float *)((char *)v13 + destStride);
          ++curComponenta;
        }
        while ( curComponenta < numComponents );
      }
      break;
    case 3:
      v32 = 0;
      curComponentb = 0;
      if ( numComponents >= 4 )
      {
        v106 = copyMapping + 2;
        v109 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        curComponentb = 4 * v109;
        do
        {
          if ( copyMapping )
          {
            v33 = (float *)&srcPtr[srcStride * *(v106 - 2)];
          }
          else
          {
            v33 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v13 = fabs(*v33);
            v13[1] = fabs(v33[1]);
            v13[2] = fabs(v33[2]);
          }
          else
          {
            *v13 = *v33;
            v13[1] = v33[1];
            v13[2] = v33[2];
          }
          v34 = (float *)((char *)v13 + destStride);
          if ( copyMapping )
          {
            v35 = (float *)&srcPtr[srcStride * *(v106 - 1)];
          }
          else
          {
            v35 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v34 = fabs(*v35);
            v34[1] = fabs(v35[1]);
            v34[2] = fabs(v35[2]);
          }
          else
          {
            *v34 = *v35;
            v34[1] = v35[1];
            v34[2] = v35[2];
          }
          v36 = (float *)((char *)v34 + destStride);
          if ( copyMapping )
          {
            v37 = (float *)&srcPtr[srcStride * *v106];
          }
          else
          {
            v37 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v36 = fabs(*v37);
            v36[1] = fabs(v37[1]);
            v36[2] = fabs(v37[2]);
          }
          else
          {
            *v36 = *v37;
            v36[1] = v37[1];
            v36[2] = v37[2];
          }
          v38 = (float *)((char *)v36 + destStride);
          if ( copyMapping )
          {
            v39 = (float *)&srcPtr[srcStride * v106[1]];
          }
          else
          {
            v39 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v38 = fabs(*v39);
            v38[1] = fabs(v39[1]);
            v38[2] = fabs(v39[2]);
          }
          else
          {
            *v38 = *v39;
            v38[1] = v39[1];
            v38[2] = v39[2];
          }
          v106 += 4;
          v13 = (float *)((char *)v38 + destStride);
          --v109;
        }
        while ( v109 );
        v32 = curComponentb;
      }
      if ( v32 < numComponents )
      {
        do
        {
          if ( copyMapping )
          {
            v40 = (float *)&srcPtr[srcStride * copyMapping[v32]];
          }
          else
          {
            v40 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v13 = fabs(*v40);
            v13[1] = fabs(v40[1]);
            v13[2] = fabs(v40[2]);
          }
          else
          {
            *v13 = *v40;
            v13[1] = v40[1];
            v13[2] = v40[2];
          }
          v32 = curComponentb + 1;
          v13 = (float *)((char *)v13 + destStride);
          ++curComponentb;
        }
        while ( curComponentb < numComponents );
      }
      break;
    case 4:
      v41 = 0;
      curComponentc = 0;
      if ( numComponents >= 4 )
      {
        v110 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        v42 = copyMapping + 2;
        curComponentc = 4 * v110;
        do
        {
          if ( copyMapping )
          {
            v43 = (float *)&srcPtr[srcStride * *(v42 - 2)];
          }
          else
          {
            v43 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v13 = fabs(*v43);
            v13[1] = fabs(v43[1]);
            v13[2] = fabs(v43[2]);
            v13[3] = fabs(v43[3]);
          }
          else
          {
            *v13 = *v43;
            v13[1] = v43[1];
            v13[2] = v43[2];
            v13[3] = v43[3];
          }
          v44 = (float *)((char *)v13 + destStride);
          if ( copyMapping )
          {
            v45 = (float *)&srcPtr[srcStride * *(v42 - 1)];
          }
          else
          {
            v45 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v44 = fabs(*v45);
            v44[1] = fabs(v45[1]);
            v44[2] = fabs(v45[2]);
            v44[3] = fabs(v45[3]);
          }
          else
          {
            *v44 = *v45;
            v44[1] = v45[1];
            v44[2] = v45[2];
            v44[3] = v45[3];
          }
          v46 = (float *)((char *)v44 + destStride);
          if ( copyMapping )
          {
            v47 = (float *)&srcPtr[srcStride * *v42];
          }
          else
          {
            v47 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v46 = fabs(*v47);
            v46[1] = fabs(v47[1]);
            v46[2] = fabs(v47[2]);
            v46[3] = fabs(v47[3]);
          }
          else
          {
            *v46 = *v47;
            v46[1] = v47[1];
            v46[2] = v47[2];
            v46[3] = v47[3];
          }
          v48 = (float *)((char *)v46 + destStride);
          if ( copyMapping )
          {
            v49 = (float *)&srcPtr[srcStride * v42[1]];
          }
          else
          {
            v49 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v48 = fabs(*v49);
            v48[1] = fabs(v49[1]);
            v48[2] = fabs(v49[2]);
            v48[3] = fabs(v49[3]);
          }
          else
          {
            *v48 = *v49;
            v48[1] = v49[1];
            v48[2] = v49[2];
            v48[3] = v49[3];
          }
          v13 = (float *)((char *)v48 + destStride);
          v42 += 4;
          --v110;
        }
        while ( v110 );
        v41 = curComponentc;
        v10 = srcTailPtr;
      }
      if ( v41 < numComponents )
      {
        do
        {
          if ( copyMapping )
          {
            v50 = (float *)&srcPtr[srcStride * copyMapping[v41]];
          }
          else
          {
            v50 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          if ( absFlag )
          {
            *v13 = fabs(*v50);
            v13[1] = fabs(v50[1]);
            v13[2] = fabs(v50[2]);
            v13[3] = fabs(v50[3]);
          }
          else
          {
            *v13 = *v50;
            v13[1] = v50[1];
            v13[2] = v50[2];
            v13[3] = v50[3];
          }
          v41 = curComponentc + 1;
          v13 = (float *)((char *)v13 + destStride);
          ++curComponentc;
        }
        while ( curComponentc < numComponents );
      }
      break;
    default:
      break;
  }
  if ( destNumValuesPerComponent > srcNumValuesPerComponent )
  {
    if ( v10 )
    {
      v51 = srcNumValuesPerComponent;
      v52 = (unsigned __int8 *)&destPtr[srcNumValuesPerComponent];
      switch ( destNumValuesPerComponent - srcNumValuesPerComponent )
      {
        case 1:
          v53 = numComponents;
          v54 = 0;
          if ( numComponents >= 4 )
          {
            v55 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v54 = 4 * v55;
            do
            {
              *(float *)v52 = v10[v51];
              v56 = &v52[destStride];
              *(float *)v56 = v10[v51];
              v57 = &v56[destStride];
              *(float *)v57 = v10[v51];
              v58 = &v57[destStride];
              *(float *)v58 = v10[v51];
              v52 = &v58[destStride];
              --v55;
            }
            while ( v55 );
            v53 = numComponents;
          }
          if ( v54 < v53 )
          {
            v59 = v53 - v54;
            do
            {
              *(float *)v52 = v10[v51];
              v52 += destStride;
              --v59;
            }
            while ( v59 );
          }
          break;
        case 2:
          v60 = numComponents;
          v61 = 0;
          if ( numComponents >= 4 )
          {
            v62 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v61 = 4 * v62;
            do
            {
              *(float *)v52 = v10[v51];
              *((float *)v52 + 1) = v10[v51 + 1];
              *(float *)&v52[destStride] = v10[v51];
              v63 = &v52[destStride];
              *((float *)v63 + 1) = v10[v51 + 1];
              v64 = &v63[destStride];
              *(float *)v64 = v10[v51];
              *((float *)v64 + 1) = v10[v51 + 1];
              v65 = &v64[destStride];
              *(float *)v65 = v10[v51];
              *((float *)v65 + 1) = v10[v51 + 1];
              v52 = &v65[destStride];
              --v62;
            }
            while ( v62 );
            v60 = numComponents;
          }
          if ( v61 < v60 )
          {
            v66 = v60 - v61;
            do
            {
              *(float *)v52 = v10[v51];
              *((float *)v52 + 1) = v10[v51 + 1];
              v52 += destStride;
              --v66;
            }
            while ( v66 );
          }
          break;
        case 3:
          v67 = numComponents;
          v68 = 0;
          if ( numComponents >= 4 )
          {
            v69 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v68 = 4 * v69;
            do
            {
              *(float *)v52 = v10[v51];
              *((float *)v52 + 1) = v10[v51 + 1];
              *((float *)v52 + 2) = v10[v51 + 2];
              *(float *)&v52[destStride] = v10[v51];
              v70 = &v52[destStride];
              *((float *)v70 + 1) = v10[v51 + 1];
              *((float *)v70 + 2) = v10[v51 + 2];
              v71 = &v70[destStride];
              *(float *)v71 = v10[v51];
              *((float *)v71 + 1) = v10[v51 + 1];
              *((float *)v71 + 2) = v10[v51 + 2];
              v72 = &v71[destStride];
              *(float *)v72 = v10[v51];
              *((float *)v72 + 1) = v10[v51 + 1];
              *((float *)v72 + 2) = v10[v51 + 2];
              v52 = &v72[destStride];
              --v69;
            }
            while ( v69 );
            v67 = numComponents;
          }
          if ( v68 < v67 )
          {
            v73 = v67 - v68;
            do
            {
              *(float *)v52 = v10[v51];
              *((float *)v52 + 1) = v10[v51 + 1];
              *((float *)v52 + 2) = v10[v51 + 2];
              v52 += destStride;
              --v73;
            }
            while ( v73 );
          }
          break;
        case 4:
          v74 = numComponents;
          v75 = 0;
          if ( numComponents >= 4 )
          {
            v76 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v75 = 4 * v76;
            do
            {
              *(float *)v52 = v10[v51];
              *((float *)v52 + 1) = v10[v51 + 1];
              *((float *)v52 + 2) = v10[v51 + 2];
              *((float *)v52 + 3) = v10[v51 + 3];
              *(float *)&v52[destStride] = v10[v51];
              *(float *)&v52[destStride + 4] = v10[v51 + 1];
              v77 = &v52[destStride];
              *((float *)v77 + 2) = v10[v51 + 2];
              *((float *)v77 + 3) = v10[v51 + 3];
              *(float *)&v77[destStride] = v10[v51];
              v78 = &v77[destStride];
              *((float *)v78 + 1) = v10[v51 + 1];
              *((float *)v78 + 2) = v10[v51 + 2];
              *((float *)v78 + 3) = v10[v51 + 3];
              v79 = &v78[destStride];
              *(float *)v79 = v10[v51];
              *((float *)v79 + 1) = v10[v51 + 1];
              *((float *)v79 + 2) = v10[v51 + 2];
              *((float *)v79 + 3) = v10[v51 + 3];
              v52 = &v79[destStride];
              --v76;
            }
            while ( v76 );
            v74 = numComponents;
          }
          if ( v75 < v74 )
          {
            v80 = v74 - v75;
            do
            {
              *(float *)v52 = v10[v51];
              *((float *)v52 + 1) = v10[v51 + 1];
              *((float *)v52 + 2) = v10[v51 + 2];
              *((float *)v52 + 3) = v10[v51 + 3];
              v52 += destStride;
              --v80;
            }
            while ( v80 );
          }
          break;
        default:
          return;
      }
    }
    else if ( destNumValuesPerComponent == srcNumValuesPerComponent + 1 )
    {
      v81 = destPtr;
      switch ( srcNumValuesPerComponent )
      {
        case 1:
          v94 = 0;
          if ( numComponents >= 4 )
          {
            v95 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v94 = 4 * v95;
            do
            {
              v81[1] = 1.0 - *v81;
              v96 = (float *)((char *)v81 + destStride);
              v96[1] = 1.0 - *v96;
              v97 = (float *)((char *)v96 + destStride);
              v97[1] = 1.0 - *v97;
              v98 = (float *)((char *)v97 + destStride);
              v98[1] = 1.0 - *v98;
              v81 = (float *)((char *)v98 + destStride);
              --v95;
            }
            while ( v95 );
          }
          if ( v94 < numComponents )
          {
            v99 = numComponents - v94;
            do
            {
              v81[1] = 1.0 - *v81;
              v81 = (float *)((char *)v81 + destStride);
              --v99;
            }
            while ( v99 );
          }
          break;
        case 2:
          v88 = 0;
          if ( numComponents >= 4 )
          {
            v89 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v88 = 4 * v89;
            do
            {
              v81[2] = 1.0 - (v81[1] + *v81);
              v90 = (float *)((char *)v81 + destStride);
              v90[2] = 1.0 - (v90[1] + *v90);
              v91 = (float *)((char *)v90 + destStride);
              v91[2] = 1.0 - (v91[1] + *v91);
              v92 = (float *)((char *)v91 + destStride);
              v92[2] = 1.0 - (v92[1] + *v92);
              v81 = (float *)((char *)v92 + destStride);
              --v89;
            }
            while ( v89 );
          }
          if ( v88 < numComponents )
          {
            v93 = numComponents - v88;
            do
            {
              v81[2] = 1.0 - (v81[1] + *v81);
              v81 = (float *)((char *)v81 + destStride);
              --v93;
            }
            while ( v93 );
          }
          break;
        case 3:
          v82 = 0;
          if ( numComponents >= 4 )
          {
            v83 = ((unsigned int)(numComponents - 4) >> 2) + 1;
            v82 = 4 * v83;
            do
            {
              v81[3] = 1.0 - (v81[2] + v81[1] + *v81);
              v84 = (float *)((char *)v81 + destStride);
              v84[3] = 1.0 - (v84[2] + v84[1] + *v84);
              v85 = (float *)((char *)v84 + destStride);
              v85[3] = 1.0 - (v85[2] + v85[1] + *v85);
              v86 = (float *)((char *)v85 + destStride);
              v86[3] = 1.0 - (v86[2] + v86[1] + *v86);
              v81 = (float *)((char *)v86 + destStride);
              --v83;
            }
            while ( v83 );
          }
          if ( v82 < numComponents )
          {
            v87 = numComponents - v82;
            do
            {
              v81[3] = 1.0 - (v81[2] + v81[1] + *v81);
              v81 = (float *)((char *)v81 + destStride);
              --v87;
            }
            while ( v87 );
          }
          break;
      }
    }
  }
}

// FUNC: rvVtxCopyFloatToInt
void __usercall rvVtxCopyFloatToInt(
        int destNumValuesPerComponent@<ecx>,
        int srcNumValuesPerComponent@<eax>,
        int numComponents@<ebx>,
        unsigned __int8 *destPtr,
        int destStride,
        unsigned __int8 *srcPtr,
        int srcStride,
        const unsigned int *copyMapping)
{
  unsigned __int8 *v8; // edx
  int i; // ecx
  const unsigned __int8 *v11; // eax
  int j; // edi
  const unsigned __int8 *v13; // ecx
  int v14; // edi
  unsigned __int8 *v15; // edx
  float *v16; // ecx
  int v17; // edi
  unsigned __int8 *v18; // edx
  float *v19; // ecx

  v8 = destPtr;
  if ( destNumValuesPerComponent <= srcNumValuesPerComponent )
    srcNumValuesPerComponent = destNumValuesPerComponent;
  switch ( srcNumValuesPerComponent )
  {
    case 1:
      for ( i = 0; i < numComponents; v8 += destStride )
      {
        if ( copyMapping )
        {
          v11 = &srcPtr[srcStride * copyMapping[i]];
        }
        else
        {
          v11 = srcPtr;
          srcPtr += srcStride;
        }
        ++i;
        *(_DWORD *)v8 = (int)*(float *)v11;
      }
      break;
    case 2:
      for ( j = 0; j < numComponents; v8 += destStride )
      {
        if ( copyMapping )
        {
          v13 = &srcPtr[srcStride * copyMapping[j]];
        }
        else
        {
          v13 = srcPtr;
          srcPtr += srcStride;
        }
        ++j;
        *(_DWORD *)v8 = (int)*(float *)v13;
        *((_DWORD *)v8 + 1) = (int)*((float *)v13 + 1);
      }
      break;
    case 3:
      v14 = 0;
      if ( numComponents > 0 )
      {
        v15 = destPtr + 8;
        do
        {
          if ( copyMapping )
          {
            v16 = (float *)&srcPtr[srcStride * copyMapping[v14]];
          }
          else
          {
            v16 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          ++v14;
          *((_DWORD *)v15 - 2) = (int)*v16;
          *((_DWORD *)v15 - 1) = (int)v16[1];
          *(_DWORD *)v15 = (int)v16[2];
          v15 += destStride;
        }
        while ( v14 < numComponents );
      }
      break;
    case 4:
      v17 = 0;
      if ( numComponents > 0 )
      {
        v18 = destPtr + 8;
        do
        {
          if ( copyMapping )
          {
            v19 = (float *)&srcPtr[srcStride * copyMapping[v17]];
          }
          else
          {
            v19 = (float *)srcPtr;
            srcPtr += srcStride;
          }
          ++v17;
          *((_DWORD *)v18 - 2) = (int)*v19;
          *((_DWORD *)v18 - 1) = (int)v19[1];
          *(_DWORD *)v18 = (int)v19[2];
          *((_DWORD *)v18 + 1) = (int)v19[3];
          v18 += destStride;
        }
        while ( v17 < numComponents );
      }
      break;
    default:
      return;
  }
}

// FUNC: rvVtxCopyIntToFloat
void __usercall rvVtxCopyIntToFloat(
        int destStride@<edx>,
        unsigned __int8 *srcPtr@<ecx>,
        const float *srcTailPtr@<ebx>,
        float *destPtr,
        int destNumValuesPerComponent,
        int srcStride,
        int srcNumValuesPerComponent,
        int numComponents,
        const unsigned int *copyMapping)
{
  float *v9; // eax
  int v10; // edi
  const unsigned int *v11; // ebp
  const unsigned __int8 *v12; // edi
  float *v13; // eax
  const unsigned __int8 *v14; // edi
  float *v15; // eax
  const unsigned __int8 *v16; // edi
  float *v17; // eax
  const unsigned __int8 *v18; // edi
  int i; // ebp
  unsigned int v20; // edi
  const unsigned __int8 *v21; // edi
  const unsigned int *v22; // ebp
  const unsigned __int8 *v23; // edi
  float *v24; // eax
  const unsigned __int8 *v25; // edi
  float *v26; // eax
  const unsigned __int8 *v27; // edi
  float *v28; // eax
  const unsigned __int8 *v29; // edi
  int j; // ebp
  unsigned int v31; // edi
  const unsigned __int8 *v32; // edi
  const unsigned int *v33; // ebp
  int *v34; // edi
  float *v35; // eax
  int *v36; // edi
  float *v37; // eax
  int *v38; // edi
  float *v39; // eax
  int *v40; // edi
  int v41; // ebp
  int *v42; // edi
  const unsigned int *v43; // ebp
  int *v44; // edi
  float *v45; // eax
  int *v46; // edi
  float *v47; // eax
  int *v48; // edi
  float *v49; // eax
  int *v50; // edi
  int v51; // ebp
  unsigned int v52; // edi
  int *v53; // edi
  int v54; // ecx
  float *v55; // eax
  int v56; // esi
  unsigned int v57; // esi
  float *v58; // eax
  float *v59; // eax
  float *v60; // eax
  int v61; // ebp
  int v62; // esi
  unsigned int v63; // esi
  float *v64; // eax
  float *v65; // eax
  float *v66; // eax
  int v67; // ebp
  int v68; // esi
  unsigned int v69; // esi
  float *v70; // eax
  float *v71; // eax
  float *v72; // eax
  int v73; // esi
  int v74; // esi
  unsigned int v75; // esi
  float *v76; // eax
  float *v77; // eax
  float *v78; // eax
  int v79; // esi
  int curComponent; // [esp+Ch] [ebp-8h]
  int curComponenta; // [esp+Ch] [ebp-8h]
  int curComponentb; // [esp+Ch] [ebp-8h]
  int curComponentc; // [esp+Ch] [ebp-8h]
  int curComponentd; // [esp+Ch] [ebp-8h]
  int curComponente; // [esp+Ch] [ebp-8h]
  int curComponentf; // [esp+Ch] [ebp-8h]
  int curComponentg; // [esp+Ch] [ebp-8h]
  unsigned int v88; // [esp+10h] [ebp-4h]
  unsigned int v89; // [esp+10h] [ebp-4h]
  unsigned int v90; // [esp+10h] [ebp-4h]
  unsigned int v91; // [esp+10h] [ebp-4h]

  v9 = destPtr;
  v10 = srcNumValuesPerComponent;
  if ( destNumValuesPerComponent <= srcNumValuesPerComponent )
    v10 = destNumValuesPerComponent;
  switch ( v10 )
  {
    case 1:
      curComponent = 0;
      if ( numComponents >= 4 )
      {
        v88 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        v11 = copyMapping + 2;
        curComponent = 4 * v88;
        do
        {
          if ( copyMapping )
          {
            v12 = &srcPtr[srcStride * *(v11 - 2)];
          }
          else
          {
            v12 = srcPtr;
            srcPtr += srcStride;
          }
          *v9 = (float)*(int *)v12;
          v13 = (float *)((char *)v9 + destStride);
          if ( copyMapping )
          {
            v14 = &srcPtr[srcStride * *(v11 - 1)];
          }
          else
          {
            v14 = srcPtr;
            srcPtr += srcStride;
          }
          *v13 = (float)*(int *)v14;
          v15 = (float *)((char *)v13 + destStride);
          if ( copyMapping )
          {
            v16 = &srcPtr[srcStride * *v11];
          }
          else
          {
            v16 = srcPtr;
            srcPtr += srcStride;
          }
          *v15 = (float)*(int *)v16;
          v17 = (float *)((char *)v15 + destStride);
          if ( copyMapping )
          {
            v18 = &srcPtr[srcStride * v11[1]];
          }
          else
          {
            v18 = srcPtr;
            srcPtr += srcStride;
          }
          v11 += 4;
          *v17 = (float)*(int *)v18;
          v9 = (float *)((char *)v17 + destStride);
          --v88;
        }
        while ( v88 );
      }
      for ( i = curComponent; i < numComponents; v9 = (float *)((char *)v9 + destStride) )
      {
        if ( copyMapping )
        {
          v20 = copyMapping[i];
          i = curComponent;
          v21 = &srcPtr[srcStride * v20];
        }
        else
        {
          v21 = srcPtr;
          srcPtr += srcStride;
        }
        curComponent = ++i;
        *v9 = (float)*(int *)v21;
      }
      goto LABEL_88;
    case 2:
      curComponenta = 0;
      if ( numComponents >= 4 )
      {
        v89 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        v22 = copyMapping + 2;
        curComponenta = 4 * v89;
        do
        {
          if ( copyMapping )
          {
            v23 = &srcPtr[srcStride * *(v22 - 2)];
          }
          else
          {
            v23 = srcPtr;
            srcPtr += srcStride;
          }
          *v9 = (float)*(int *)v23;
          v9[1] = (float)*((int *)v23 + 1);
          v24 = (float *)((char *)v9 + destStride);
          if ( copyMapping )
          {
            v25 = &srcPtr[srcStride * *(v22 - 1)];
          }
          else
          {
            v25 = srcPtr;
            srcPtr += srcStride;
          }
          *v24 = (float)*(int *)v25;
          v24[1] = (float)*((int *)v25 + 1);
          v26 = (float *)((char *)v24 + destStride);
          if ( copyMapping )
          {
            v27 = &srcPtr[srcStride * *v22];
          }
          else
          {
            v27 = srcPtr;
            srcPtr += srcStride;
          }
          *v26 = (float)*(int *)v27;
          v26[1] = (float)*((int *)v27 + 1);
          v28 = (float *)((char *)v26 + destStride);
          if ( copyMapping )
          {
            v29 = &srcPtr[srcStride * v22[1]];
          }
          else
          {
            v29 = srcPtr;
            srcPtr += srcStride;
          }
          v22 += 4;
          *v28 = (float)*(int *)v29;
          v28[1] = (float)*((int *)v29 + 1);
          v9 = (float *)((char *)v28 + destStride);
          --v89;
        }
        while ( v89 );
      }
      for ( j = curComponenta; j < numComponents; v9 = (float *)((char *)v9 + destStride) )
      {
        if ( copyMapping )
        {
          v31 = copyMapping[j];
          j = curComponenta;
          v32 = &srcPtr[srcStride * v31];
        }
        else
        {
          v32 = srcPtr;
          srcPtr += srcStride;
        }
        curComponenta = ++j;
        *v9 = (float)*(int *)v32;
        v9[1] = (float)*((int *)v32 + 1);
      }
      goto LABEL_88;
    case 3:
      curComponentb = 0;
      if ( numComponents >= 4 )
      {
        v90 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        v33 = copyMapping + 2;
        curComponentb = 4 * v90;
        do
        {
          if ( copyMapping )
          {
            v34 = (int *)&srcPtr[srcStride * *(v33 - 2)];
          }
          else
          {
            v34 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          *v9 = (float)*v34;
          v9[1] = (float)v34[1];
          v9[2] = (float)v34[2];
          v35 = (float *)((char *)v9 + destStride);
          if ( copyMapping )
          {
            v36 = (int *)&srcPtr[srcStride * *(v33 - 1)];
          }
          else
          {
            v36 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          *v35 = (float)*v36;
          v35[1] = (float)v36[1];
          v35[2] = (float)v36[2];
          v37 = (float *)((char *)v35 + destStride);
          if ( copyMapping )
          {
            v38 = (int *)&srcPtr[srcStride * *v33];
          }
          else
          {
            v38 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          *v37 = (float)*v38;
          v37[1] = (float)v38[1];
          v37[2] = (float)v38[2];
          v39 = (float *)((char *)v37 + destStride);
          if ( copyMapping )
          {
            v40 = (int *)&srcPtr[srcStride * v33[1]];
          }
          else
          {
            v40 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          v33 += 4;
          *v39 = (float)*v40;
          v39[1] = (float)v40[1];
          v39[2] = (float)v40[2];
          v9 = (float *)((char *)v39 + destStride);
          --v90;
        }
        while ( v90 );
      }
      v41 = numComponents;
      if ( curComponentb >= numComponents )
        goto LABEL_88;
      do
      {
        if ( copyMapping )
        {
          v41 = numComponents;
          v42 = (int *)&srcPtr[srcStride * copyMapping[curComponentb]];
        }
        else
        {
          v42 = (int *)srcPtr;
          srcPtr += srcStride;
        }
        *v9 = (float)*v42;
        v9[1] = (float)v42[1];
        ++curComponentb;
        v9[2] = (float)v42[2];
        v9 = (float *)((char *)v9 + destStride);
      }
      while ( curComponentb < v41 );
      break;
    case 4:
      curComponentc = 0;
      if ( numComponents >= 4 )
      {
        v91 = ((unsigned int)(numComponents - 4) >> 2) + 1;
        v43 = copyMapping + 2;
        curComponentc = 4 * v91;
        do
        {
          if ( copyMapping )
          {
            v44 = (int *)&srcPtr[srcStride * *(v43 - 2)];
          }
          else
          {
            v44 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          *v9 = (float)*v44;
          v9[1] = (float)v44[1];
          v9[2] = (float)v44[2];
          v9[3] = (float)v44[3];
          v45 = (float *)((char *)v9 + destStride);
          if ( copyMapping )
          {
            v46 = (int *)&srcPtr[srcStride * *(v43 - 1)];
          }
          else
          {
            v46 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          *v45 = (float)*v46;
          v45[1] = (float)v46[1];
          v45[2] = (float)v46[2];
          v45[3] = (float)v46[3];
          v47 = (float *)((char *)v45 + destStride);
          if ( copyMapping )
          {
            v48 = (int *)&srcPtr[srcStride * *v43];
          }
          else
          {
            v48 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          *v47 = (float)*v48;
          v47[1] = (float)v48[1];
          v47[2] = (float)v48[2];
          v47[3] = (float)v48[3];
          v49 = (float *)((char *)v47 + destStride);
          if ( copyMapping )
          {
            v50 = (int *)&srcPtr[srcStride * v43[1]];
          }
          else
          {
            v50 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          v43 += 4;
          *v49 = (float)*v50;
          v49[1] = (float)v50[1];
          v49[2] = (float)v50[2];
          v49[3] = (float)v50[3];
          v9 = (float *)((char *)v49 + destStride);
          --v91;
        }
        while ( v91 );
      }
      if ( curComponentc < numComponents )
      {
        v51 = curComponentc;
        do
        {
          if ( copyMapping )
          {
            v52 = copyMapping[v51];
            v51 = curComponentc;
            v53 = (int *)&srcPtr[srcStride * v52];
          }
          else
          {
            v53 = (int *)srcPtr;
            srcPtr += srcStride;
          }
          curComponentc = ++v51;
          *v9 = (float)*v53;
          v9[1] = (float)v53[1];
          v9[2] = (float)v53[2];
          v9[3] = (float)v53[3];
          v9 = (float *)((char *)v9 + destStride);
        }
        while ( v51 < numComponents );
      }
      goto LABEL_88;
    default:
LABEL_88:
      v41 = numComponents;
      break;
  }
  if ( destNumValuesPerComponent > srcNumValuesPerComponent && srcTailPtr )
  {
    v54 = srcNumValuesPerComponent;
    v55 = &destPtr[srcNumValuesPerComponent];
    switch ( destNumValuesPerComponent - srcNumValuesPerComponent )
    {
      case 1:
        v56 = 0;
        if ( v41 >= 4 )
        {
          v57 = ((unsigned int)(v41 - 4) >> 2) + 1;
          curComponentd = 4 * v57;
          do
          {
            *v55 = srcTailPtr[v54];
            v58 = (float *)((char *)v55 + destStride);
            *v58 = srcTailPtr[v54];
            v59 = (float *)((char *)v58 + destStride);
            *v59 = srcTailPtr[v54];
            v60 = (float *)((char *)v59 + destStride);
            *v60 = srcTailPtr[v54];
            v55 = (float *)((char *)v60 + destStride);
            --v57;
          }
          while ( v57 );
          v56 = curComponentd;
        }
        if ( v56 < v41 )
        {
          v61 = v41 - v56;
          do
          {
            *v55 = srcTailPtr[v54];
            v55 = (float *)((char *)v55 + destStride);
            --v61;
          }
          while ( v61 );
        }
        break;
      case 2:
        v62 = 0;
        if ( v41 >= 4 )
        {
          v63 = ((unsigned int)(v41 - 4) >> 2) + 1;
          curComponente = 4 * v63;
          do
          {
            *v55 = srcTailPtr[v54];
            v55[1] = srcTailPtr[v54 + 1];
            *(float *)((char *)v55 + destStride) = srcTailPtr[v54];
            v64 = (float *)((char *)v55 + destStride);
            v64[1] = srcTailPtr[v54 + 1];
            v65 = (float *)((char *)v64 + destStride);
            *v65 = srcTailPtr[v54];
            v65[1] = srcTailPtr[v54 + 1];
            v66 = (float *)((char *)v65 + destStride);
            *v66 = srcTailPtr[v54];
            v66[1] = srcTailPtr[v54 + 1];
            v55 = (float *)((char *)v66 + destStride);
            --v63;
          }
          while ( v63 );
          v62 = curComponente;
        }
        if ( v62 < v41 )
        {
          v67 = v41 - v62;
          do
          {
            *v55 = srcTailPtr[v54];
            v55[1] = srcTailPtr[v54 + 1];
            v55 = (float *)((char *)v55 + destStride);
            --v67;
          }
          while ( v67 );
        }
        break;
      case 3:
        v68 = 0;
        if ( v41 >= 4 )
        {
          v69 = ((unsigned int)(v41 - 4) >> 2) + 1;
          curComponentf = 4 * v69;
          do
          {
            *v55 = srcTailPtr[v54];
            v55[1] = srcTailPtr[v54 + 1];
            v55[2] = srcTailPtr[v54 + 2];
            *(float *)((char *)v55 + destStride) = srcTailPtr[v54];
            v70 = (float *)((char *)v55 + destStride);
            v70[1] = srcTailPtr[v54 + 1];
            v70[2] = srcTailPtr[v54 + 2];
            v71 = (float *)((char *)v70 + destStride);
            *v71 = srcTailPtr[v54];
            v71[1] = srcTailPtr[v54 + 1];
            v71[2] = srcTailPtr[v54 + 2];
            v72 = (float *)((char *)v71 + destStride);
            *v72 = srcTailPtr[v54];
            v72[1] = srcTailPtr[v54 + 1];
            v72[2] = srcTailPtr[v54 + 2];
            v55 = (float *)((char *)v72 + destStride);
            --v69;
          }
          while ( v69 );
          v68 = curComponentf;
        }
        if ( v68 < v41 )
        {
          v73 = v41 - v68;
          do
          {
            *v55 = srcTailPtr[v54];
            v55[1] = srcTailPtr[v54 + 1];
            v55[2] = srcTailPtr[v54 + 2];
            v55 = (float *)((char *)v55 + destStride);
            --v73;
          }
          while ( v73 );
        }
        break;
      case 4:
        v74 = 0;
        if ( v41 >= 4 )
        {
          v75 = ((unsigned int)(v41 - 4) >> 2) + 1;
          curComponentg = 4 * v75;
          do
          {
            *v55 = srcTailPtr[v54];
            v55[1] = srcTailPtr[v54 + 1];
            v55[2] = srcTailPtr[v54 + 2];
            v55[3] = srcTailPtr[v54 + 3];
            *(float *)((char *)v55 + destStride) = srcTailPtr[v54];
            *(float *)((char *)v55 + destStride + 4) = srcTailPtr[v54 + 1];
            v76 = (float *)((char *)v55 + destStride);
            v76[2] = srcTailPtr[v54 + 2];
            v76[3] = srcTailPtr[v54 + 3];
            *(float *)((char *)v76 + destStride) = srcTailPtr[v54];
            v77 = (float *)((char *)v76 + destStride);
            v77[1] = srcTailPtr[v54 + 1];
            v77[2] = srcTailPtr[v54 + 2];
            v77[3] = srcTailPtr[v54 + 3];
            v78 = (float *)((char *)v77 + destStride);
            *v78 = srcTailPtr[v54];
            v78[1] = srcTailPtr[v54 + 1];
            v78[2] = srcTailPtr[v54 + 2];
            v78[3] = srcTailPtr[v54 + 3];
            v55 = (float *)((char *)v78 + destStride);
            --v75;
          }
          while ( v75 );
          v74 = curComponentg;
        }
        if ( v74 < v41 )
        {
          v79 = v41 - v74;
          do
          {
            *v55 = srcTailPtr[v54];
            v55[1] = srcTailPtr[v54 + 1];
            v55[2] = srcTailPtr[v54 + 2];
            v55[3] = srcTailPtr[v54 + 3];
            v55 = (float *)((char *)v55 + destStride);
            --v79;
          }
          while ( v79 );
        }
        break;
      default:
        return;
    }
  }
}

// FUNC: rvVtxCopyIntToInt
void __usercall rvVtxCopyIntToInt(
        const unsigned __int8 *srcPtr@<edx>,
        int srcStride@<edi>,
        int srcNumValuesPerComponent@<eax>,
        int numComponents@<ebx>,
        unsigned __int8 *destPtr,
        int destStride,
        int destNumValuesPerComponent,
        const unsigned int *copyMapping)
{
  unsigned __int8 *v8; // ecx
  const unsigned int *v9; // ebp
  int i; // esi
  const unsigned __int8 *v11; // eax
  int v12; // esi
  const unsigned __int8 *v13; // eax
  int v14; // esi
  unsigned __int8 *v15; // ecx
  const unsigned __int8 *v16; // eax
  int v17; // esi
  unsigned __int8 *v18; // ecx
  const unsigned __int8 *v19; // eax

  v8 = destPtr;
  v9 = copyMapping;
  if ( destNumValuesPerComponent <= srcNumValuesPerComponent )
    srcNumValuesPerComponent = destNumValuesPerComponent;
  switch ( srcNumValuesPerComponent )
  {
    case 1:
      for ( i = 0; i < numComponents; ++i )
      {
        if ( copyMapping )
        {
          v11 = &srcPtr[srcStride * copyMapping[i]];
        }
        else
        {
          v11 = srcPtr;
          srcPtr += srcStride;
        }
        *(_DWORD *)v8 = *(_DWORD *)v11;
        v8 += destStride;
      }
      break;
    case 2:
      v12 = 0;
      if ( numComponents > 0 )
      {
        while ( 1 )
        {
          if ( v9 )
          {
            v13 = &srcPtr[srcStride * v9[v12]];
          }
          else
          {
            v13 = srcPtr;
            srcPtr += srcStride;
          }
          *(_DWORD *)v8 = *(_DWORD *)v13;
          *((_DWORD *)v8 + 1) = *((_DWORD *)v13 + 1);
          v8 += destStride;
          if ( ++v12 >= numComponents )
            break;
          v9 = copyMapping;
        }
      }
      break;
    case 3:
      v14 = 0;
      if ( numComponents > 0 )
      {
        v15 = destPtr + 8;
        while ( 1 )
        {
          if ( v9 )
          {
            v16 = &srcPtr[srcStride * v9[v14]];
          }
          else
          {
            v16 = srcPtr;
            srcPtr += srcStride;
          }
          *((_DWORD *)v15 - 2) = *(_DWORD *)v16;
          *((_DWORD *)v15 - 1) = *((_DWORD *)v16 + 1);
          *(_DWORD *)v15 = *((_DWORD *)v16 + 2);
          v15 += destStride;
          if ( ++v14 >= numComponents )
            break;
          v9 = copyMapping;
        }
      }
      break;
    case 4:
      v17 = 0;
      if ( numComponents > 0 )
      {
        v18 = destPtr + 8;
        while ( 1 )
        {
          if ( v9 )
          {
            v19 = &srcPtr[srcStride * v9[v17]];
          }
          else
          {
            v19 = srcPtr;
            srcPtr += srcStride;
          }
          *((_DWORD *)v18 - 2) = *(_DWORD *)v19;
          *((_DWORD *)v18 - 1) = *((_DWORD *)v19 + 1);
          *(_DWORD *)v18 = *((_DWORD *)v19 + 2);
          *((_DWORD *)v18 + 1) = *((_DWORD *)v19 + 3);
          v18 += destStride;
          if ( ++v17 >= numComponents )
            break;
          v9 = copyMapping;
        }
      }
      break;
    default:
      return;
  }
}

// FUNC: rvVtxCopyDWordToDWord
void __usercall rvVtxCopyDWordToDWord(
        unsigned __int8 *destPtr@<edx>,
        const unsigned __int8 *srcPtr@<eax>,
        int srcStride@<ebx>,
        int numComponents@<edi>,
        int destStride,
        const unsigned int *copyMapping)
{
  int i; // ecx
  const unsigned __int8 *v8; // eax

  for ( i = 0; i < numComponents; ++i )
  {
    if ( copyMapping )
    {
      v8 = &srcPtr[srcStride * copyMapping[i]];
    }
    else
    {
      v8 = srcPtr;
      srcPtr += srcStride;
    }
    *(_DWORD *)destPtr = *(_DWORD *)v8;
    destPtr += destStride;
  }
}

// FUNC: rvVtxCopyFloatToDec16Pair
void __usercall rvVtxCopyFloatToDec16Pair(
        unsigned __int8 *destPtr@<eax>,
        const int *destShifts@<ebx>,
        int destStride,
        const unsigned __int8 *srcPtr,
        int srcStride,
        const float *destScales,
        const unsigned int *destMasks,
        int numComponents,
        const unsigned int *copyMapping)
{
  int i; // esi
  const unsigned __int8 *v11; // edx

  for ( i = 0; i < numComponents; destPtr += destStride )
  {
    if ( copyMapping )
    {
      v11 = &srcPtr[srcStride * copyMapping[i]];
    }
    else
    {
      v11 = srcPtr;
      srcPtr += srcStride;
    }
    ++i;
    *(_DWORD *)destPtr = ((*destMasks & (int)(*(float *)v11 * *destScales)) << *destShifts) | ((destMasks[1] & (int)(*((float *)v11 + 1) * destScales[1])) << destShifts[1]);
  }
}

// FUNC: rvVtxCopyDec16PairToFloat
void __usercall rvVtxCopyDec16PairToFloat(
        float *destPtr@<eax>,
        const float *srcScales@<edi>,
        const unsigned int *srcMasks@<esi>,
        const int *srcShifts@<edx>,
        int destStride,
        const unsigned __int8 *srcPtr,
        int srcStride,
        int numComponents,
        const unsigned int *copyMapping)
{
  int v9; // ebx
  int v10; // ecx
  const unsigned __int8 *v11; // ebp
  const unsigned __int8 *v12; // ebx
  float *v13; // eax
  const unsigned __int8 *v14; // ebx
  float *v15; // eax
  const unsigned __int8 *v16; // ebx
  float *v17; // eax
  const unsigned __int8 *v18; // ebx
  const unsigned __int8 *v19; // ebx
  const unsigned int *v20; // [esp+8h] [ebp-10h]
  int curComponent; // [esp+Ch] [ebp-Ch]
  unsigned int v22; // [esp+10h] [ebp-8h]

  v9 = numComponents;
  v10 = 0;
  v11 = srcPtr;
  curComponent = 0;
  if ( numComponents >= 4 )
  {
    v20 = copyMapping + 2;
    v22 = ((unsigned int)(numComponents - 4) >> 2) + 1;
    curComponent = 4 * v22;
    do
    {
      if ( copyMapping )
      {
        v12 = &v11[srcStride * *(v20 - 2)];
      }
      else
      {
        v12 = v11;
        srcPtr = &v11[srcStride];
      }
      *destPtr = (double)(*srcMasks & (*(_DWORD *)v12 >> *srcShifts)) * *srcScales;
      destPtr[1] = (double)(srcMasks[1] & (*(_DWORD *)v12 >> srcShifts[1])) * srcScales[1];
      v13 = (float *)((char *)destPtr + destStride);
      if ( copyMapping )
      {
        v14 = &srcPtr[srcStride * *(v20 - 1)];
      }
      else
      {
        v14 = srcPtr;
        srcPtr += srcStride;
      }
      *v13 = (double)(*srcMasks & (*(_DWORD *)v14 >> *srcShifts)) * *srcScales;
      v13[1] = (double)(srcMasks[1] & (*(_DWORD *)v14 >> srcShifts[1])) * srcScales[1];
      v15 = (float *)((char *)v13 + destStride);
      if ( copyMapping )
      {
        v16 = &srcPtr[srcStride * *v20];
      }
      else
      {
        v16 = srcPtr;
        srcPtr += srcStride;
      }
      *v15 = (double)(*srcMasks & (*(_DWORD *)v16 >> *srcShifts)) * *srcScales;
      v15[1] = (double)(srcMasks[1] & (*(_DWORD *)v16 >> srcShifts[1])) * srcScales[1];
      v17 = (float *)((char *)v15 + destStride);
      if ( copyMapping )
      {
        v18 = &srcPtr[srcStride * v20[1]];
      }
      else
      {
        v18 = srcPtr;
        srcPtr += srcStride;
      }
      *v17 = (double)(*srcMasks & (*(_DWORD *)v18 >> *srcShifts)) * *srcScales;
      v20 += 4;
      v11 = srcPtr;
      v17[1] = (double)(srcMasks[1] & (*(_DWORD *)v18 >> srcShifts[1])) * srcScales[1];
      destPtr = (float *)((char *)v17 + destStride);
      --v22;
    }
    while ( v22 );
    v9 = numComponents;
    v10 = curComponent;
  }
  if ( v10 < v9 )
  {
    while ( 1 )
    {
      if ( copyMapping )
      {
        v19 = &v11[srcStride * copyMapping[v10]];
      }
      else
      {
        v19 = v11;
        srcPtr = &v11[srcStride];
      }
      *destPtr = (double)(*srcMasks & (*(_DWORD *)v19 >> *srcShifts)) * *srcScales;
      v10 = ++curComponent;
      destPtr[1] = (double)(srcMasks[1] & (*(_DWORD *)v19 >> srcShifts[1])) * srcScales[1];
      destPtr = (float *)((char *)destPtr + destStride);
      if ( curComponent >= numComponents )
        break;
      v11 = srcPtr;
    }
  }
}

// FUNC: rvVtxCopySignedDec16PairToFloat
void __usercall rvVtxCopySignedDec16PairToFloat(
        float *destPtr@<eax>,
        const float *srcScales@<edi>,
        const unsigned int *srcMasks@<esi>,
        const int *srcShifts@<edx>,
        int destStride,
        const unsigned __int8 *srcPtr,
        int srcStride,
        int numComponents,
        const unsigned int *copyMapping)
{
  int v9; // ebx
  int v10; // ecx
  const unsigned __int8 *v11; // ebp
  const unsigned __int8 *v12; // ebx
  float *v13; // eax
  const unsigned __int8 *v14; // ebx
  float *v15; // eax
  const unsigned __int8 *v16; // ebx
  float *v17; // eax
  const unsigned __int8 *v18; // ebx
  const unsigned __int8 *v19; // ebx
  const unsigned int *v20; // [esp+8h] [ebp-10h]
  int curComponent; // [esp+Ch] [ebp-Ch]
  unsigned int v22; // [esp+10h] [ebp-8h]

  v9 = numComponents;
  v10 = 0;
  v11 = srcPtr;
  curComponent = 0;
  if ( numComponents >= 4 )
  {
    v20 = copyMapping + 2;
    v22 = ((unsigned int)(numComponents - 4) >> 2) + 1;
    curComponent = 4 * v22;
    do
    {
      if ( copyMapping )
      {
        v12 = &v11[srcStride * *(v20 - 2)];
      }
      else
      {
        v12 = v11;
        srcPtr = &v11[srcStride];
      }
      *destPtr = (double)(__int16)(*(_WORD *)srcMasks & (*(_DWORD *)v12 >> *srcShifts)) * *srcScales;
      destPtr[1] = (double)(__int16)(srcMasks[1] & (*(_DWORD *)v12 >> srcShifts[1])) * srcScales[1];
      v13 = (float *)((char *)destPtr + destStride);
      if ( copyMapping )
      {
        v14 = &srcPtr[srcStride * *(v20 - 1)];
      }
      else
      {
        v14 = srcPtr;
        srcPtr += srcStride;
      }
      *v13 = (double)(__int16)(*(_WORD *)srcMasks & (*(_DWORD *)v14 >> *srcShifts)) * *srcScales;
      v13[1] = (double)(__int16)(srcMasks[1] & (*(_DWORD *)v14 >> srcShifts[1])) * srcScales[1];
      v15 = (float *)((char *)v13 + destStride);
      if ( copyMapping )
      {
        v16 = &srcPtr[srcStride * *v20];
      }
      else
      {
        v16 = srcPtr;
        srcPtr += srcStride;
      }
      *v15 = (double)(__int16)(*(_WORD *)srcMasks & (*(_DWORD *)v16 >> *srcShifts)) * *srcScales;
      v15[1] = (double)(__int16)(srcMasks[1] & (*(_DWORD *)v16 >> srcShifts[1])) * srcScales[1];
      v17 = (float *)((char *)v15 + destStride);
      if ( copyMapping )
      {
        v18 = &srcPtr[srcStride * v20[1]];
      }
      else
      {
        v18 = srcPtr;
        srcPtr += srcStride;
      }
      v20 += 4;
      v11 = srcPtr;
      *v17 = (double)(__int16)(*(_WORD *)srcMasks & (*(_DWORD *)v18 >> *srcShifts)) * *srcScales;
      v17[1] = (double)(__int16)(srcMasks[1] & (*(_DWORD *)v18 >> srcShifts[1])) * srcScales[1];
      destPtr = (float *)((char *)v17 + destStride);
      --v22;
    }
    while ( v22 );
    v9 = numComponents;
    v10 = curComponent;
  }
  if ( v10 < v9 )
  {
    while ( 1 )
    {
      if ( copyMapping )
      {
        v19 = &v11[srcStride * copyMapping[v10]];
      }
      else
      {
        v19 = v11;
        srcPtr = &v11[srcStride];
      }
      *destPtr = (double)(__int16)(*(_WORD *)srcMasks & (*(_DWORD *)v19 >> *srcShifts)) * *srcScales;
      v10 = ++curComponent;
      destPtr[1] = (double)(__int16)(srcMasks[1] & (*(_DWORD *)v19 >> srcShifts[1])) * srcScales[1];
      destPtr = (float *)((char *)destPtr + destStride);
      if ( curComponent >= numComponents )
        break;
      v11 = srcPtr;
    }
  }
}

// FUNC: rvVtxCopyFloatToFloat16Pair
void __usercall rvVtxCopyFloatToFloat16Pair(
        unsigned __int8 *destPtr@<edx>,
        const unsigned __int8 *srcPtr@<eax>,
        int numComponents@<ebx>,
        int destStride,
        int srcStride,
        const unsigned int *copyMapping)
{
  int i; // esi
  const unsigned __int8 *v8; // eax
  int v9; // edx

  for ( i = 0; i < numComponents; ++i )
  {
    if ( copyMapping )
    {
      v8 = &srcPtr[srcStride * copyMapping[i]];
    }
    else
    {
      v8 = srcPtr;
      srcPtr += srcStride;
    }
    ConvertFloatToFloat16Pair((unsigned int *)destPtr, (const float *)v8);
    destPtr = (unsigned __int8 *)(destStride + v9);
  }
}

// FUNC: rvVtxCopyFloat16PairToFloat
void __usercall rvVtxCopyFloat16PairToFloat(
        float *destPtr@<ecx>,
        const unsigned __int8 *srcPtr@<eax>,
        int destStride,
        int srcStride,
        int numComponents,
        const unsigned int *copyMapping)
{
  int i; // esi
  const unsigned __int8 *v9; // eax

  for ( i = 0; i < numComponents; ++i )
  {
    if ( copyMapping )
    {
      v9 = &srcPtr[srcStride * copyMapping[i]];
    }
    else
    {
      v9 = srcPtr;
      srcPtr += srcStride;
    }
    ConvertFloat16PairToFloat(destPtr, *(_DWORD *)v9);
    destPtr = (float *)((char *)destPtr + destStride);
  }
}

// FUNC: rvVtxCopyFloatToDecTriple
void __usercall rvVtxCopyFloatToDecTriple(
        const unsigned int *destMasks@<ebx>,
        const int *destShifts@<edi>,
        unsigned __int8 *destPtr,
        int destStride,
        const unsigned __int8 *srcPtr,
        int srcStride,
        const float *destScales,
        int numComponents,
        const unsigned int *copyMapping)
{
  const unsigned int *v9; // edx
  int v10; // ecx
  const unsigned __int8 *v11; // eax
  const float *v12; // ebp
  int v13; // esi
  float *v14; // edx
  unsigned int v15; // eax
  double v16; // st7

  v9 = copyMapping;
  v10 = srcStride;
  v11 = srcPtr;
  v12 = destScales;
  v13 = 0;
  if ( numComponents > 0 )
  {
    while ( 1 )
    {
      if ( v9 )
      {
        v14 = (float *)&v11[v10 * v9[v13]];
      }
      else
      {
        v14 = (float *)v11;
        srcPtr = &v11[v10];
      }
      ++v13;
      v15 = (destMasks[2] & (int)(v14[2] * v12[2])) << destShifts[2];
      v16 = v14[1] * v12[1];
      v12 = destScales;
      *(_DWORD *)destPtr = ((*destMasks & (int)(*v14 * *destScales)) << *destShifts) | ((destMasks[1] & (int)v16) << destShifts[1]) | v15;
      destPtr += destStride;
      if ( v13 >= numComponents )
        break;
      v11 = srcPtr;
      v10 = srcStride;
      v9 = copyMapping;
    }
  }
}

// FUNC: rvVtxCopyDecTripleToFloat
void __usercall rvVtxCopyDecTripleToFloat(
        float *destPtr@<eax>,
        const float *srcScales@<edi>,
        const unsigned int *srcMasks@<esi>,
        const int *srcShifts@<edx>,
        int destStride,
        const unsigned __int8 *srcPtr,
        int srcStride,
        int numComponents,
        const unsigned int *copyMapping)
{
  int v9; // ebx
  int v10; // ecx
  const unsigned __int8 *v11; // ebp
  const unsigned __int8 *v12; // ebx
  float *v13; // eax
  const unsigned __int8 *v14; // ebx
  float *v15; // eax
  const unsigned __int8 *v16; // ebx
  float *v17; // eax
  const unsigned __int8 *v18; // ebx
  const unsigned __int8 *v19; // ebx
  const unsigned int *v20; // [esp+8h] [ebp-10h]
  int curComponent; // [esp+Ch] [ebp-Ch]
  unsigned int v22; // [esp+10h] [ebp-8h]

  v9 = numComponents;
  v10 = 0;
  v11 = srcPtr;
  curComponent = 0;
  if ( numComponents >= 4 )
  {
    v20 = copyMapping + 2;
    v22 = ((unsigned int)(numComponents - 4) >> 2) + 1;
    curComponent = 4 * v22;
    do
    {
      if ( copyMapping )
      {
        v12 = &v11[srcStride * *(v20 - 2)];
      }
      else
      {
        v12 = v11;
        srcPtr = &v11[srcStride];
      }
      *destPtr = (double)(*srcMasks & (*(_DWORD *)v12 >> *srcShifts)) * *srcScales;
      destPtr[1] = (double)(srcMasks[1] & (*(_DWORD *)v12 >> srcShifts[1])) * srcScales[1];
      destPtr[2] = (double)(srcMasks[2] & (*(_DWORD *)v12 >> srcShifts[2])) * srcScales[2];
      v13 = (float *)((char *)destPtr + destStride);
      if ( copyMapping )
      {
        v14 = &srcPtr[srcStride * *(v20 - 1)];
      }
      else
      {
        v14 = srcPtr;
        srcPtr += srcStride;
      }
      *v13 = (double)(*srcMasks & (*(_DWORD *)v14 >> *srcShifts)) * *srcScales;
      v13[1] = (double)(srcMasks[1] & (*(_DWORD *)v14 >> srcShifts[1])) * srcScales[1];
      v13[2] = (double)(srcMasks[2] & (*(_DWORD *)v14 >> srcShifts[2])) * srcScales[2];
      v15 = (float *)((char *)v13 + destStride);
      if ( copyMapping )
      {
        v16 = &srcPtr[srcStride * *v20];
      }
      else
      {
        v16 = srcPtr;
        srcPtr += srcStride;
      }
      *v15 = (double)(*srcMasks & (*(_DWORD *)v16 >> *srcShifts)) * *srcScales;
      v15[1] = (double)(srcMasks[1] & (*(_DWORD *)v16 >> srcShifts[1])) * srcScales[1];
      v15[2] = (double)(srcMasks[2] & (*(_DWORD *)v16 >> srcShifts[2])) * srcScales[2];
      v17 = (float *)((char *)v15 + destStride);
      if ( copyMapping )
      {
        v18 = &srcPtr[srcStride * v20[1]];
      }
      else
      {
        v18 = srcPtr;
        srcPtr += srcStride;
      }
      *v17 = (double)(*srcMasks & (*(_DWORD *)v18 >> *srcShifts)) * *srcScales;
      v17[1] = (double)(srcMasks[1] & (*(_DWORD *)v18 >> srcShifts[1])) * srcScales[1];
      v20 += 4;
      v11 = srcPtr;
      v17[2] = (double)(srcMasks[2] & (*(_DWORD *)v18 >> srcShifts[2])) * srcScales[2];
      destPtr = (float *)((char *)v17 + destStride);
      --v22;
    }
    while ( v22 );
    v9 = numComponents;
    v10 = curComponent;
  }
  if ( v10 < v9 )
  {
    while ( 1 )
    {
      if ( copyMapping )
      {
        v19 = &v11[srcStride * copyMapping[v10]];
      }
      else
      {
        v19 = v11;
        srcPtr = &v11[srcStride];
      }
      *destPtr = (double)(*srcMasks & (*(_DWORD *)v19 >> *srcShifts)) * *srcScales;
      destPtr[1] = (double)(srcMasks[1] & (*(_DWORD *)v19 >> srcShifts[1])) * srcScales[1];
      v10 = ++curComponent;
      destPtr[2] = (double)(srcMasks[2] & (*(_DWORD *)v19 >> srcShifts[2])) * srcScales[2];
      destPtr = (float *)((char *)destPtr + destStride);
      if ( curComponent >= numComponents )
        break;
      v11 = srcPtr;
    }
  }
}

// FUNC: rvVtxCopySignedDecTripleToFloat
void __usercall rvVtxCopySignedDecTripleToFloat(
        float *destPtr@<eax>,
        const float *srcScales@<edi>,
        const int *srcLeftShifts@<esi>,
        const int *srcshifts@<edx>,
        int destStride,
        const unsigned __int8 *srcPtr,
        int srcStride,
        int srcMasks,
        const unsigned int *numComponents)
{
  const unsigned __int8 *v9; // ebx
  int v10; // ebp
  int v11; // ecx
  const unsigned __int8 *v12; // ecx
  float *v13; // eax
  const unsigned __int8 *v14; // ecx
  float *v15; // eax
  const unsigned __int8 *v16; // ecx
  float *v17; // eax
  const unsigned __int8 *v18; // ecx
  const unsigned __int8 *v19; // ecx
  int v20; // ebp
  _DWORD *v21; // [esp+Ch] [ebp-10h]
  int curComponent; // [esp+10h] [ebp-Ch]
  unsigned int v23; // [esp+14h] [ebp-8h]

  v9 = srcPtr;
  v10 = srcMasks;
  v11 = 0;
  curComponent = 0;
  if ( srcMasks >= 4 )
  {
    v21 = numComponents + 2;
    v23 = ((unsigned int)(srcMasks - 4) >> 2) + 1;
    curComponent = 4 * v23;
    do
    {
      if ( numComponents )
      {
        v12 = &v9[srcStride * *(v21 - 2)];
      }
      else
      {
        v12 = v9;
        srcPtr = &v9[srcStride];
      }
      *destPtr = (double)((int)(*(_DWORD *)v12 << *srcLeftShifts) >> (*srcLeftShifts + *srcshifts)) * *srcScales;
      destPtr[1] = (double)((int)(*(_DWORD *)v12 << srcLeftShifts[1]) >> (srcLeftShifts[1] + srcshifts[1]))
                 * srcScales[1];
      destPtr[2] = (double)((int)(*(_DWORD *)v12 << srcLeftShifts[2]) >> (*((_BYTE *)srcLeftShifts + 8)
                                                                        + *((_BYTE *)srcshifts + 8)))
                 * srcScales[2];
      v13 = (float *)((char *)destPtr + destStride);
      if ( numComponents )
      {
        v14 = &srcPtr[srcStride * *(v21 - 1)];
      }
      else
      {
        v14 = srcPtr;
        srcPtr += srcStride;
      }
      *v13 = (double)((int)(*(_DWORD *)v14 << *srcLeftShifts) >> (*srcLeftShifts + *srcshifts)) * *srcScales;
      v13[1] = (double)((int)(*(_DWORD *)v14 << srcLeftShifts[1]) >> (srcLeftShifts[1] + srcshifts[1])) * srcScales[1];
      v13[2] = (double)((int)(*(_DWORD *)v14 << srcLeftShifts[2]) >> (*((_BYTE *)srcLeftShifts + 8)
                                                                    + *((_BYTE *)srcshifts + 8)))
             * srcScales[2];
      v15 = (float *)((char *)v13 + destStride);
      if ( numComponents )
      {
        v16 = &srcPtr[srcStride * *v21];
      }
      else
      {
        v16 = srcPtr;
        srcPtr += srcStride;
      }
      *v15 = (double)((int)(*(_DWORD *)v16 << *srcLeftShifts) >> (*srcLeftShifts + *srcshifts)) * *srcScales;
      v15[1] = (double)((int)(*(_DWORD *)v16 << srcLeftShifts[1]) >> (srcLeftShifts[1] + srcshifts[1])) * srcScales[1];
      v15[2] = (double)((int)(*(_DWORD *)v16 << srcLeftShifts[2]) >> (*((_BYTE *)srcLeftShifts + 8)
                                                                    + *((_BYTE *)srcshifts + 8)))
             * srcScales[2];
      v17 = (float *)((char *)v15 + destStride);
      if ( numComponents )
      {
        v18 = &srcPtr[srcStride * v21[1]];
      }
      else
      {
        v18 = srcPtr;
        srcPtr += srcStride;
      }
      v21 += 4;
      *v17 = (double)((int)(*(_DWORD *)v18 << *srcLeftShifts) >> (*srcLeftShifts + *srcshifts)) * *srcScales;
      v17[1] = (double)((int)(*(_DWORD *)v18 << srcLeftShifts[1]) >> (srcLeftShifts[1] + srcshifts[1])) * srcScales[1];
      v9 = srcPtr;
      v17[2] = (double)((int)(*(_DWORD *)v18 << srcLeftShifts[2]) >> (*((_BYTE *)srcLeftShifts + 8)
                                                                    + *((_BYTE *)srcshifts + 8)))
             * srcScales[2];
      destPtr = (float *)((char *)v17 + destStride);
      --v23;
    }
    while ( v23 );
    v11 = curComponent;
    v10 = srcMasks;
  }
  if ( v11 < v10 )
  {
    while ( 1 )
    {
      if ( numComponents )
      {
        v19 = &v9[srcStride * numComponents[v11]];
      }
      else
      {
        v19 = v9;
        srcPtr = &v9[srcStride];
      }
      *destPtr = (double)((int)(*(_DWORD *)v19 << *srcLeftShifts) >> (*srcLeftShifts + *srcshifts)) * *srcScales;
      destPtr[1] = (double)((int)(*(_DWORD *)v19 << srcLeftShifts[1]) >> (srcLeftShifts[1] + srcshifts[1]))
                 * srcScales[1];
      v20 = (int)(*(_DWORD *)v19 << srcLeftShifts[2]) >> (srcLeftShifts[2] + srcshifts[2]);
      v11 = ++curComponent;
      destPtr[2] = (double)v20 * srcScales[2];
      destPtr = (float *)((char *)destPtr + destStride);
      if ( curComponent >= srcMasks )
        break;
      v9 = srcPtr;
    }
  }
}

// FUNC: public: static void __cdecl rvVertexBuffer::ComponentCopy(unsigned char *,int,enum Rv_Vertex_Data_Type_t,int,unsigned char const *,int,enum Rv_Vertex_Data_Type_t,int,int,unsigned int const *,float *,bool)
void __cdecl rvVertexBuffer::ComponentCopy(
        unsigned __int8 *destPtr,
        int destStride,
        Rv_Vertex_Data_Type_t destDataType,
        int destNumValuesPerComponent,
        unsigned __int8 *srcPtr,
        int srcStride,
        Rv_Vertex_Data_Type_t srcDataType,
        int srcNumValuesPerComponent,
        int numComponents,
        const unsigned int *copyMapping,
        float *srcTailPtr,
        bool absFlag)
{
  const unsigned int *v12; // esi
  unsigned __int8 *v13; // edx
  const unsigned __int8 *v14; // eax
  int v15; // ebp
  int v16; // edi
  const unsigned __int8 *v17; // eax
  int v18; // [esp-18h] [ebp-18h]
  const unsigned int *v19; // [esp-14h] [ebp-14h]
  const unsigned int *v20; // [esp-14h] [ebp-14h]
  const unsigned int *v21; // [esp-14h] [ebp-14h]

  switch ( destDataType )
  {
    case RV_VERTEX_DATA_TYPE_FLOAT:
      switch ( srcDataType )
      {
        case RV_VERTEX_DATA_TYPE_FLOAT:
          rvVtxCopyFloatToFloat(
            srcPtr,
            destStride,
            (float *)destPtr,
            destNumValuesPerComponent,
            srcStride,
            srcNumValuesPerComponent,
            numComponents,
            copyMapping,
            srcTailPtr,
            absFlag);
          break;
        case RV_VERTEX_DATA_TYPE_FLOAT16:
          rvVtxCopyFloat16PairToFloat((float *)destPtr, srcPtr, destStride, srcStride, numComponents, copyMapping);
          if ( srcNumValuesPerComponent == 4 )
            rvVtxCopyFloat16PairToFloat(
              (float *)destPtr + 2,
              srcPtr + 4,
              destStride,
              srcStride,
              numComponents,
              copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_INT:
          rvVtxCopyIntToFloat(
            destStride,
            srcPtr,
            srcTailPtr,
            (float *)destPtr,
            destNumValuesPerComponent,
            srcStride,
            srcNumValuesPerComponent,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_SHORT:
          rvVtxCopySignedDec16PairToFloat(
            (float *)destPtr,
            scaleOne,
            mask16bit,
            shift16Bit,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          if ( srcNumValuesPerComponent == 4 )
            rvVtxCopySignedDec16PairToFloat(
              (float *)destPtr + 2,
              scaleOne,
              mask16bit,
              shift16Bit,
              destStride,
              srcPtr + 4,
              srcStride,
              numComponents,
              copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_USHORT:
          rvVtxCopyDec16PairToFloat(
            (float *)destPtr,
            scaleOne,
            mask16bit,
            shift16Bit,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          if ( srcNumValuesPerComponent == 4 )
            rvVtxCopyDec16PairToFloat(
              (float *)destPtr + 2,
              scaleOne,
              mask16bit,
              shift16Bit,
              destStride,
              srcPtr + 4,
              srcStride,
              numComponents,
              copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_SHORTN:
          rvVtxCopySignedDec16PairToFloat(
            (float *)destPtr,
            scaleInv32767,
            mask16bit,
            shift16Bit,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          if ( srcNumValuesPerComponent == 4 )
            rvVtxCopySignedDec16PairToFloat(
              (float *)destPtr + 2,
              scaleInv32767,
              mask16bit,
              shift16Bit,
              destStride,
              srcPtr + 4,
              srcStride,
              numComponents,
              copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_USHORTN:
          rvVtxCopyDec16PairToFloat(
            (float *)destPtr,
            scaleInv65535,
            mask16bit,
            shift16Bit,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          if ( srcNumValuesPerComponent == 4 )
            rvVtxCopyDec16PairToFloat(
              (float *)destPtr + 2,
              scaleInv65535,
              mask16bit,
              shift16Bit,
              destStride,
              srcPtr + 4,
              srcStride,
              numComponents,
              copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_UDEC_10_10_10:
          rvVtxCopyDecTripleToFloat(
            (float *)destPtr,
            scaleOne,
            mask10_10_10,
            shift10_10_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_DEC_10_10_10:
          rvVtxCopySignedDecTripleToFloat(
            (float *)destPtr,
            scaleOne,
            leftShift10_10_10,
            shift10_10_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_UDEC_10_10_10N:
          rvVtxCopyDecTripleToFloat(
            (float *)destPtr,
            scaleInv1023,
            mask10_10_10,
            shift10_10_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_DEC_10_10_10N:
          rvVtxCopySignedDecTripleToFloat(
            (float *)destPtr,
            scaleInv511,
            leftShift10_10_10,
            shift10_10_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_UDEC_10_11_11:
          rvVtxCopyDecTripleToFloat(
            (float *)destPtr,
            scaleOne,
            mask10_11_11,
            shift10_11_11,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_DEC_10_11_11:
          rvVtxCopySignedDecTripleToFloat(
            (float *)destPtr,
            scaleOne,
            leftShift10_11_11,
            shift10_11_11,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_UDEC_10_11_11N:
          rvVtxCopyDecTripleToFloat(
            (float *)destPtr,
            scaleInv1023_2047_2047,
            mask10_11_11,
            shift10_11_11,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_DEC_10_11_11N:
          rvVtxCopySignedDecTripleToFloat(
            (float *)destPtr,
            scaleInv511_1023_1023,
            leftShift10_11_11,
            shift10_11_11,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_UDEC_11_11_10:
          rvVtxCopyDecTripleToFloat(
            (float *)destPtr,
            scaleOne,
            mask11_11_10,
            shift11_11_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_DEC_11_11_10:
          rvVtxCopySignedDecTripleToFloat(
            (float *)destPtr,
            scaleOne,
            leftShift11_11_10,
            shift11_11_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_UDEC_11_11_10N:
          rvVtxCopyDecTripleToFloat(
            (float *)destPtr,
            scaleInv2047_2047_1023,
            mask11_11_10,
            shift11_11_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        case RV_VERTEX_DATA_TYPE_DEC_11_11_10N:
          rvVtxCopySignedDecTripleToFloat(
            (float *)destPtr,
            scaleInv1023_1023_511,
            leftShift11_11_10,
            shift11_11_10,
            destStride,
            srcPtr,
            srcStride,
            numComponents,
            copyMapping);
          break;
        default:
          return;
      }
      return;
    case RV_VERTEX_DATA_TYPE_FLOAT16:
      v12 = copyMapping;
      v13 = destPtr;
      v14 = srcPtr;
      v15 = destStride;
      v19 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
      {
        v16 = numComponents;
        goto LABEL_47;
      }
      rvVtxCopyFloatToFloat16Pair(destPtr, srcPtr, numComponents, destStride, srcStride, copyMapping);
      if ( srcNumValuesPerComponent == 4 )
        rvVtxCopyFloatToFloat16Pair(destPtr + 4, srcPtr + 8, numComponents, destStride, srcStride, copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_INT:
      if ( srcDataType == RV_VERTEX_DATA_TYPE_FLOAT )
        rvVtxCopyFloatToInt(
          destNumValuesPerComponent,
          srcNumValuesPerComponent,
          numComponents,
          destPtr,
          destStride,
          srcPtr,
          srcStride,
          copyMapping);
      else
        rvVtxCopyIntToInt(
          srcPtr,
          srcStride,
          srcNumValuesPerComponent,
          numComponents,
          destPtr,
          destStride,
          destNumValuesPerComponent,
          copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_COLOR:
    case RV_VERTEX_DATA_TYPE_UBYTE:
    case RV_VERTEX_DATA_TYPE_BYTE:
    case RV_VERTEX_DATA_TYPE_UBYTEN:
    case RV_VERTEX_DATA_TYPE_BYTEN:
      goto $L114434;
    case RV_VERTEX_DATA_TYPE_SHORT:
    case RV_VERTEX_DATA_TYPE_USHORT:
      v12 = copyMapping;
      v16 = numComponents;
      v19 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_45;
      rvVtxCopyFloatToDec16Pair(
        destPtr,
        shift16Bit,
        destStride,
        srcPtr,
        srcStride,
        scaleOne,
        mask16bit,
        numComponents,
        copyMapping);
      if ( srcNumValuesPerComponent == 4 )
        rvVtxCopyFloatToDec16Pair(
          destPtr + 4,
          shift16Bit,
          destStride,
          srcPtr + 8,
          srcStride,
          scaleOne,
          mask16bit,
          numComponents,
          copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_SHORTN:
      v12 = copyMapping;
      v14 = srcPtr;
      v16 = numComponents;
      v19 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_46;
      rvVtxCopyFloatToDec16Pair(
        destPtr,
        shift16Bit,
        destStride,
        srcPtr,
        srcStride,
        scale32767,
        mask16bit,
        numComponents,
        copyMapping);
      if ( srcNumValuesPerComponent == 4 )
        rvVtxCopyFloatToDec16Pair(
          destPtr + 4,
          shift16Bit,
          destStride,
          srcPtr + 8,
          srcStride,
          scale32767,
          mask16bit,
          numComponents,
          copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_USHORTN:
      v12 = copyMapping;
      v16 = numComponents;
      v19 = copyMapping;
      if ( srcDataType == RV_VERTEX_DATA_TYPE_FLOAT )
      {
        rvVtxCopyFloatToDec16Pair(
          destPtr,
          shift16Bit,
          destStride,
          srcPtr,
          srcStride,
          scale65535,
          mask16bit,
          numComponents,
          copyMapping);
        if ( srcNumValuesPerComponent == 4 )
          rvVtxCopyFloatToDec16Pair(
            destPtr + 4,
            shift16Bit,
            destStride,
            srcPtr + 8,
            srcStride,
            scale65535,
            mask16bit,
            numComponents,
            copyMapping);
      }
      else
      {
LABEL_45:
        v14 = srcPtr;
LABEL_46:
        v15 = destStride;
        v13 = destPtr;
LABEL_47:
        rvVtxCopyDWordToDWord(v13, v14, srcStride, v16, v15, v19);
        if ( srcNumValuesPerComponent == 4 )
          rvVtxCopyDWordToDWord(destPtr + 4, srcPtr + 4, srcStride, v16, v15, v12);
      }
      return;
    case RV_VERTEX_DATA_TYPE_UDEC_10_10_10:
    case RV_VERTEX_DATA_TYPE_DEC_10_10_10:
      v20 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_64;
      rvVtxCopyFloatToDecTriple(
        mask10_10_10,
        shift10_10_10,
        destPtr,
        destStride,
        srcPtr,
        srcStride,
        scaleOne,
        numComponents,
        copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_UDEC_10_10_10N:
      v20 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_67;
      rvVtxCopyFloatToDecTriple(
        mask10_10_10,
        shift10_10_10,
        destPtr,
        destStride,
        srcPtr,
        srcStride,
        scale1023,
        numComponents,
        copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_DEC_10_10_10N:
      v21 = copyMapping;
      v17 = srcPtr;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_61;
      rvVtxCopyFloatToDecTriple(
        mask10_10_10,
        shift10_10_10,
        destPtr,
        destStride,
        srcPtr,
        srcStride,
        scale511,
        numComponents,
        copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_UDEC_10_11_11:
    case RV_VERTEX_DATA_TYPE_DEC_10_11_11:
      v20 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_64;
      rvVtxCopyFloatToDecTriple(
        mask10_11_11,
        shift10_11_11,
        destPtr,
        destStride,
        srcPtr,
        srcStride,
        scaleOne,
        numComponents,
        copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_UDEC_10_11_11N:
      v20 = copyMapping;
      if ( srcDataType != RV_VERTEX_DATA_TYPE_FLOAT )
        goto LABEL_67;
      rvVtxCopyFloatToDecTriple(
        mask10_11_11,
        shift10_11_11,
        destPtr,
        destStride,
        srcPtr,
        srcStride,
        scale1023_2047_2047,
        numComponents,
        copyMapping);
      return;
    case RV_VERTEX_DATA_TYPE_DEC_10_11_11N:
      v21 = copyMapping;
      v17 = srcPtr;
      if ( srcDataType == RV_VERTEX_DATA_TYPE_FLOAT )
        rvVtxCopyFloatToDecTriple(
          mask10_11_11,
          shift10_11_11,
          destPtr,
          destStride,
          srcPtr,
          srcStride,
          scale511_1023_1023,
          numComponents,
          copyMapping);
      else
LABEL_61:
        rvVtxCopyDWordToDWord(destPtr, v17, srcStride, numComponents, destStride, v21);
      return;
    case RV_VERTEX_DATA_TYPE_UDEC_11_11_10:
    case RV_VERTEX_DATA_TYPE_DEC_11_11_10:
      v20 = copyMapping;
      if ( srcDataType == RV_VERTEX_DATA_TYPE_FLOAT )
      {
        rvVtxCopyFloatToDecTriple(
          mask11_11_10,
          shift11_11_10,
          destPtr,
          destStride,
          srcPtr,
          srcStride,
          scaleOne,
          numComponents,
          copyMapping);
        return;
      }
LABEL_64:
      v18 = destStride;
      goto LABEL_72;
    case RV_VERTEX_DATA_TYPE_UDEC_11_11_10N:
      v20 = copyMapping;
      if ( srcDataType == RV_VERTEX_DATA_TYPE_FLOAT )
      {
        rvVtxCopyFloatToDecTriple(
          mask11_11_10,
          shift11_11_10,
          destPtr,
          destStride,
          srcPtr,
          srcStride,
          scale2047_2047_1023,
          numComponents,
          copyMapping);
        return;
      }
LABEL_67:
      v18 = destStride;
      goto LABEL_72;
    case RV_VERTEX_DATA_TYPE_DEC_11_11_10N:
      if ( srcDataType == RV_VERTEX_DATA_TYPE_FLOAT )
      {
        rvVtxCopyFloatToDecTriple(
          mask11_11_10,
          shift11_11_10,
          destPtr,
          destStride,
          srcPtr,
          srcStride,
          scale1023_1023_511,
          numComponents,
          copyMapping);
      }
      else
      {
$L114434:
        v20 = copyMapping;
        v18 = destStride;
LABEL_72:
        rvVtxCopyDWordToDWord(destPtr, srcPtr, srcStride, numComponents, v18, v20);
      }
      return;
    default:
      return;
  }
}
