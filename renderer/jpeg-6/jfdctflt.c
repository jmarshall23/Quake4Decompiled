
// FUNC: _jpeg_fdct_float
void __cdecl jpeg_fdct_float(float *data)
{
  double v2; // st6
  double v3; // st5
  double v4; // st4
  double v5; // st3
  double v6; // st2
  double v7; // st7
  double v8; // rt0
  double v9; // st7
  double v10; // st4
  double v11; // st5
  double v12; // rt2
  double v13; // st6
  double v14; // st6
  double v15; // st5
  double v16; // st4
  double v17; // st3
  double v18; // st2
  double v19; // st7
  double v20; // rtt
  double v21; // st7
  double v22; // st4
  double v23; // st5
  double v24; // rt1
  double v25; // st6
  double v26; // st6
  double v27; // st5
  double v28; // st4
  double v29; // st3
  double v30; // st2
  double v31; // st7
  double v32; // rt2
  double v33; // st7
  double v34; // st4
  double v35; // st5
  double v36; // rt0
  double v37; // st6
  double v38; // st6
  double v39; // st5
  double v40; // st4
  double v41; // st3
  double v42; // st2
  double v43; // st7
  double v44; // rt1
  double v45; // st7
  double v46; // st4
  double v47; // st5
  double v48; // rtt
  double v49; // st6
  double v50; // st6
  double v51; // st5
  double v52; // st4
  double v53; // st3
  double v54; // st2
  double v55; // st7
  double v56; // rt0
  double v57; // st7
  double v58; // st4
  double v59; // st5
  double v60; // rt2
  double v61; // st6
  double v62; // st6
  double v63; // st5
  double v64; // st4
  double v65; // st3
  double v66; // st2
  double v67; // st7
  double v68; // rtt
  double v69; // st7
  double v70; // st4
  double v71; // st5
  double v72; // rt1
  double v73; // st6
  double v74; // st6
  double v75; // st5
  double v76; // st4
  double v77; // st3
  double v78; // st2
  double v79; // st7
  double v80; // rt2
  double v81; // st7
  double v82; // st4
  double v83; // st5
  double v84; // rt0
  double v85; // st6
  double v86; // st6
  double v87; // st5
  double v88; // st4
  double v89; // st3
  double v90; // st2
  double v91; // st7
  double v92; // rt1
  double v93; // st7
  double v94; // st4
  double v95; // st5
  double v96; // rtt
  double v97; // st6
  double v98; // st6
  double v99; // st5
  double v100; // st4
  double v101; // st3
  double v102; // st2
  double v103; // st7
  double v104; // rt0
  double v105; // st7
  double v106; // st4
  double v107; // st5
  double v108; // rt2
  double v109; // st6
  double v110; // st6
  double v111; // st5
  double v112; // st4
  double v113; // st3
  double v114; // st2
  double v115; // st7
  double v116; // rtt
  double v117; // st7
  double v118; // st4
  double v119; // st5
  double v120; // rt1
  double v121; // st6
  double v122; // st6
  double v123; // st5
  double v124; // st4
  double v125; // st3
  double v126; // st2
  double v127; // st7
  double v128; // rt2
  double v129; // st7
  double v130; // st4
  double v131; // st5
  double v132; // rt0
  double v133; // st6
  double v134; // st6
  double v135; // st5
  double v136; // st4
  double v137; // st3
  double v138; // st2
  double v139; // st7
  double v140; // rt1
  double v141; // st7
  double v142; // st4
  double v143; // st5
  double v144; // rtt
  double v145; // st6
  double v146; // st6
  double v147; // st5
  double v148; // st4
  double v149; // st3
  double v150; // st2
  double v151; // st7
  double v152; // rt0
  double v153; // st7
  double v154; // st4
  double v155; // st5
  double v156; // rt2
  double v157; // st6
  double v158; // st6
  double v159; // st5
  double v160; // st4
  double v161; // st3
  double v162; // st2
  double v163; // st7
  double v164; // rtt
  double v165; // st7
  double v166; // st4
  double v167; // st5
  double v168; // rt1
  double v169; // st6
  double v170; // st6
  double v171; // st5
  double v172; // st4
  double v173; // st3
  double v174; // st2
  double v175; // st7
  double v176; // rt2
  double v177; // st7
  double v178; // st4
  double v179; // st5
  double v180; // rt0
  double v181; // st6
  double v182; // st6
  double v183; // st5
  double v184; // st4
  double v185; // st3
  double v186; // st2
  double v187; // st7
  double v188; // rt1
  double v189; // st7
  double v190; // st4
  double v191; // st5
  double v192; // rtt
  double v193; // st6
  float tmp11; // [esp+0h] [ebp-Ch]
  float tmp11a; // [esp+0h] [ebp-Ch]
  float tmp11b; // [esp+0h] [ebp-Ch]
  float tmp11c; // [esp+0h] [ebp-Ch]
  float tmp11d; // [esp+0h] [ebp-Ch]
  float tmp11e; // [esp+0h] [ebp-Ch]
  float tmp11f; // [esp+0h] [ebp-Ch]
  float tmp11g; // [esp+0h] [ebp-Ch]
  float tmp11h; // [esp+0h] [ebp-Ch]
  float tmp11i; // [esp+0h] [ebp-Ch]
  float tmp11j; // [esp+0h] [ebp-Ch]
  float tmp11k; // [esp+0h] [ebp-Ch]
  float tmp11l; // [esp+0h] [ebp-Ch]
  float tmp11m; // [esp+0h] [ebp-Ch]
  float tmp11n; // [esp+0h] [ebp-Ch]
  float tmp11o; // [esp+0h] [ebp-Ch]
  float tmp11p; // [esp+0h] [ebp-Ch]
  float tmp11q; // [esp+0h] [ebp-Ch]
  float tmp11r; // [esp+0h] [ebp-Ch]
  float tmp11s; // [esp+0h] [ebp-Ch]
  float tmp11t; // [esp+0h] [ebp-Ch]
  float tmp11u; // [esp+0h] [ebp-Ch]
  float tmp11v; // [esp+0h] [ebp-Ch]
  float tmp11w; // [esp+0h] [ebp-Ch]
  float tmp11x; // [esp+0h] [ebp-Ch]
  float tmp11y; // [esp+0h] [ebp-Ch]
  float tmp11z; // [esp+0h] [ebp-Ch]
  float tmp11ba; // [esp+0h] [ebp-Ch]
  float tmp11bb; // [esp+0h] [ebp-Ch]
  float tmp11bc; // [esp+0h] [ebp-Ch]
  float tmp11bd; // [esp+0h] [ebp-Ch]
  float tmp11be; // [esp+0h] [ebp-Ch]
  float z11; // [esp+4h] [ebp-8h]
  float z11a; // [esp+4h] [ebp-8h]
  float z11b; // [esp+4h] [ebp-8h]
  float z11c; // [esp+4h] [ebp-8h]
  float z11d; // [esp+4h] [ebp-8h]
  float z11e; // [esp+4h] [ebp-8h]
  float z11f; // [esp+4h] [ebp-8h]
  float z11g; // [esp+4h] [ebp-8h]
  float z11h; // [esp+4h] [ebp-8h]
  float z11i; // [esp+4h] [ebp-8h]
  float z11j; // [esp+4h] [ebp-8h]
  float z11k; // [esp+4h] [ebp-8h]
  float z11l; // [esp+4h] [ebp-8h]
  float z11m; // [esp+4h] [ebp-8h]
  float z11n; // [esp+4h] [ebp-8h]
  float z11o; // [esp+4h] [ebp-8h]
  float z11p; // [esp+4h] [ebp-8h]
  float z11q; // [esp+4h] [ebp-8h]
  float z11r; // [esp+4h] [ebp-8h]
  float z11s; // [esp+4h] [ebp-8h]
  float z11t; // [esp+4h] [ebp-8h]
  float z11u; // [esp+4h] [ebp-8h]
  float z11v; // [esp+4h] [ebp-8h]
  float z11w; // [esp+4h] [ebp-8h]
  float z11x; // [esp+4h] [ebp-8h]
  float z11y; // [esp+4h] [ebp-8h]
  float z11z; // [esp+4h] [ebp-8h]
  float z11ba; // [esp+4h] [ebp-8h]
  float z11bb; // [esp+4h] [ebp-8h]
  float z11bc; // [esp+4h] [ebp-8h]
  float z11bd; // [esp+4h] [ebp-8h]
  float z11be; // [esp+4h] [ebp-8h]
  float tmp4; // [esp+8h] [ebp-4h]
  float tmp4a; // [esp+8h] [ebp-4h]
  float tmp4b; // [esp+8h] [ebp-4h]
  float tmp4c; // [esp+8h] [ebp-4h]
  float tmp4d; // [esp+8h] [ebp-4h]
  float tmp4e; // [esp+8h] [ebp-4h]
  float tmp4f; // [esp+8h] [ebp-4h]
  float tmp4g; // [esp+8h] [ebp-4h]
  float tmp4h; // [esp+8h] [ebp-4h]
  float tmp4i; // [esp+8h] [ebp-4h]
  float tmp4j; // [esp+8h] [ebp-4h]
  float tmp4k; // [esp+8h] [ebp-4h]
  float tmp4l; // [esp+8h] [ebp-4h]
  float tmp4m; // [esp+8h] [ebp-4h]
  float tmp4n; // [esp+8h] [ebp-4h]
  float tmp4o; // [esp+8h] [ebp-4h]
  float dataa; // [esp+10h] [ebp+4h]
  float datab; // [esp+10h] [ebp+4h]
  float datac; // [esp+10h] [ebp+4h]
  float datad; // [esp+10h] [ebp+4h]
  float datae; // [esp+10h] [ebp+4h]
  float dataf; // [esp+10h] [ebp+4h]
  float datag; // [esp+10h] [ebp+4h]
  float datah; // [esp+10h] [ebp+4h]
  float datai; // [esp+10h] [ebp+4h]
  float dataj; // [esp+10h] [ebp+4h]
  float datak; // [esp+10h] [ebp+4h]
  float datal; // [esp+10h] [ebp+4h]
  float datam; // [esp+10h] [ebp+4h]
  float datan; // [esp+10h] [ebp+4h]
  float datao; // [esp+10h] [ebp+4h]
  float datap; // [esp+10h] [ebp+4h]
  float dataq; // [esp+10h] [ebp+4h]
  float datar; // [esp+10h] [ebp+4h]
  float datas; // [esp+10h] [ebp+4h]
  float datat; // [esp+10h] [ebp+4h]
  float datau; // [esp+10h] [ebp+4h]
  float datav; // [esp+10h] [ebp+4h]
  float dataw; // [esp+10h] [ebp+4h]
  float datax; // [esp+10h] [ebp+4h]
  float datay; // [esp+10h] [ebp+4h]
  float dataz; // [esp+10h] [ebp+4h]
  float databa; // [esp+10h] [ebp+4h]
  float databb; // [esp+10h] [ebp+4h]
  float databc; // [esp+10h] [ebp+4h]
  float databd; // [esp+10h] [ebp+4h]
  float databe; // [esp+10h] [ebp+4h]
  float databf; // [esp+10h] [ebp+4h]

  v2 = *data - data[7];
  v3 = data[1] + data[6];
  v4 = data[1] - data[6];
  v5 = data[2] + data[5];
  z11 = data[2] - data[5];
  v6 = data[3] + data[4];
  tmp4 = data[3] - data[4];
  v7 = v6 + *data + data[7];
  dataa = *data + data[7] - v6;
  tmp11 = v5 + v3;
  *data = v5 + v3 + v7;
  data[4] = v7 - tmp11;
  v8 = (v3 - v5 + dataa) * 0.70710677;
  data[2] = dataa + v8;
  data[6] = dataa - v8;
  v9 = v4;
  v10 = v4 + v2;
  v11 = (tmp4 + z11 - v10) * 0.38268343;
  datab = (tmp4 + z11) * 0.54119611 + v11;
  tmp11a = v10 * 1.306563 + v11;
  v12 = v2;
  v13 = (z11 + v9) * 0.70710677;
  z11a = v13 + v12;
  data[5] = datab + v12 - v13;
  data[3] = v12 - v13 - datab;
  data[1] = z11a + tmp11a;
  data[7] = z11a - tmp11a;
  v14 = data[8] - data[15];
  v15 = data[9] + data[14];
  v16 = data[9] - data[14];
  v17 = data[10] + data[13];
  z11b = data[10] - data[13];
  v18 = data[11] + data[12];
  tmp4a = data[11] - data[12];
  v19 = v18 + data[8] + data[15];
  datac = data[8] + data[15] - v18;
  tmp11b = v17 + v15;
  data[8] = v17 + v15 + v19;
  data[12] = v19 - tmp11b;
  v20 = (v15 - v17 + datac) * 0.70710677;
  data[10] = datac + v20;
  data[14] = datac - v20;
  v21 = v16;
  v22 = v16 + v14;
  v23 = (tmp4a + z11b - v22) * 0.38268343;
  datad = (tmp4a + z11b) * 0.54119611 + v23;
  tmp11c = v22 * 1.306563 + v23;
  v24 = v14;
  v25 = (z11b + v21) * 0.70710677;
  z11c = v25 + v24;
  data[13] = datad + v24 - v25;
  data[11] = v24 - v25 - datad;
  data[9] = z11c + tmp11c;
  data[15] = z11c - tmp11c;
  v26 = data[16] - data[23];
  v27 = data[17] + data[22];
  v28 = data[17] - data[22];
  v29 = data[18] + data[21];
  z11d = data[18] - data[21];
  v30 = data[19] + data[20];
  tmp4b = data[19] - data[20];
  v31 = v30 + data[16] + data[23];
  datae = data[16] + data[23] - v30;
  tmp11d = v29 + v27;
  data[16] = v29 + v27 + v31;
  data[20] = v31 - tmp11d;
  v32 = (v27 - v29 + datae) * 0.70710677;
  data[18] = datae + v32;
  data[22] = datae - v32;
  v33 = v28;
  v34 = v28 + v26;
  v35 = (tmp4b + z11d - v34) * 0.38268343;
  dataf = (tmp4b + z11d) * 0.54119611 + v35;
  tmp11e = v34 * 1.306563 + v35;
  v36 = v26;
  v37 = (z11d + v33) * 0.70710677;
  z11e = v37 + v36;
  data[21] = dataf + v36 - v37;
  data[19] = v36 - v37 - dataf;
  data[17] = z11e + tmp11e;
  data[23] = z11e - tmp11e;
  v38 = data[24] - data[31];
  v39 = data[25] + data[30];
  v40 = data[25] - data[30];
  v41 = data[26] + data[29];
  z11f = data[26] - data[29];
  v42 = data[27] + data[28];
  tmp4c = data[27] - data[28];
  v43 = v42 + data[24] + data[31];
  datag = data[24] + data[31] - v42;
  tmp11f = v41 + v39;
  data[24] = v41 + v39 + v43;
  data[28] = v43 - tmp11f;
  v44 = (v39 - v41 + datag) * 0.70710677;
  data[26] = datag + v44;
  data[30] = datag - v44;
  v45 = v40;
  v46 = v40 + v38;
  v47 = (tmp4c + z11f - v46) * 0.38268343;
  datah = (tmp4c + z11f) * 0.54119611 + v47;
  tmp11g = v46 * 1.306563 + v47;
  v48 = v38;
  v49 = (z11f + v45) * 0.70710677;
  z11g = v49 + v48;
  data[29] = datah + v48 - v49;
  data[27] = v48 - v49 - datah;
  data[25] = z11g + tmp11g;
  data[31] = z11g - tmp11g;
  v50 = data[32] - data[39];
  v51 = data[33] + data[38];
  v52 = data[33] - data[38];
  v53 = data[34] + data[37];
  z11h = data[34] - data[37];
  v54 = data[35] + data[36];
  tmp4d = data[35] - data[36];
  v55 = v54 + data[32] + data[39];
  datai = data[32] + data[39] - v54;
  tmp11h = v53 + v51;
  data[32] = v53 + v51 + v55;
  data[36] = v55 - tmp11h;
  v56 = (v51 - v53 + datai) * 0.70710677;
  data[34] = datai + v56;
  data[38] = datai - v56;
  v57 = v52;
  v58 = v52 + v50;
  v59 = (tmp4d + z11h - v58) * 0.38268343;
  dataj = (tmp4d + z11h) * 0.54119611 + v59;
  tmp11i = v58 * 1.306563 + v59;
  v60 = v50;
  v61 = (z11h + v57) * 0.70710677;
  z11i = v61 + v60;
  data[37] = dataj + v60 - v61;
  data[35] = v60 - v61 - dataj;
  data[33] = z11i + tmp11i;
  data[39] = z11i - tmp11i;
  v62 = data[40] - data[47];
  v63 = data[41] + data[46];
  v64 = data[41] - data[46];
  v65 = data[42] + data[45];
  z11j = data[42] - data[45];
  v66 = data[43] + data[44];
  tmp4e = data[43] - data[44];
  v67 = v66 + data[40] + data[47];
  datak = data[40] + data[47] - v66;
  tmp11j = v65 + v63;
  data[40] = v65 + v63 + v67;
  data[44] = v67 - tmp11j;
  v68 = (v63 - v65 + datak) * 0.70710677;
  data[42] = datak + v68;
  data[46] = datak - v68;
  v69 = v64;
  v70 = v64 + v62;
  v71 = (tmp4e + z11j - v70) * 0.38268343;
  datal = (tmp4e + z11j) * 0.54119611 + v71;
  tmp11k = v70 * 1.306563 + v71;
  v72 = v62;
  v73 = (z11j + v69) * 0.70710677;
  z11k = v73 + v72;
  data[45] = datal + v72 - v73;
  data[43] = v72 - v73 - datal;
  data[41] = z11k + tmp11k;
  data[47] = z11k - tmp11k;
  v74 = data[48] - data[55];
  v75 = data[49] + data[54];
  v76 = data[49] - data[54];
  v77 = data[50] + data[53];
  z11l = data[50] - data[53];
  v78 = data[51] + data[52];
  tmp4f = data[51] - data[52];
  v79 = v78 + data[48] + data[55];
  datam = data[48] + data[55] - v78;
  tmp11l = v77 + v75;
  data[48] = v77 + v75 + v79;
  data[52] = v79 - tmp11l;
  v80 = (v75 - v77 + datam) * 0.70710677;
  data[50] = datam + v80;
  data[54] = datam - v80;
  v81 = v76;
  v82 = v76 + v74;
  v83 = (tmp4f + z11l - v82) * 0.38268343;
  datan = (tmp4f + z11l) * 0.54119611 + v83;
  tmp11m = v82 * 1.306563 + v83;
  v84 = v74;
  v85 = (z11l + v81) * 0.70710677;
  z11m = v85 + v84;
  data[53] = datan + v84 - v85;
  data[51] = v84 - v85 - datan;
  data[49] = z11m + tmp11m;
  data[55] = z11m - tmp11m;
  v86 = data[56] - data[63];
  v87 = data[57] + data[62];
  v88 = data[57] - data[62];
  v89 = data[58] + data[61];
  z11n = data[58] - data[61];
  v90 = data[59] + data[60];
  tmp4g = data[59] - data[60];
  v91 = v90 + data[56] + data[63];
  datao = data[56] + data[63] - v90;
  tmp11n = v89 + v87;
  data[56] = v89 + v87 + v91;
  data[60] = v91 - tmp11n;
  v92 = (v87 - v89 + datao) * 0.70710677;
  data[58] = datao + v92;
  data[62] = datao - v92;
  v93 = v88;
  v94 = v88 + v86;
  v95 = (tmp4g + z11n - v94) * 0.38268343;
  datap = (tmp4g + z11n) * 0.54119611 + v95;
  tmp11o = v94 * 1.306563 + v95;
  v96 = v86;
  v97 = (z11n + v93) * 0.70710677;
  z11o = v97 + v96;
  data[61] = datap + v96 - v97;
  data[59] = v96 - v97 - datap;
  data[57] = z11o + tmp11o;
  data[63] = z11o - tmp11o;
  v98 = *data - data[56];
  v99 = data[48] + data[8];
  v100 = data[8] - data[48];
  v101 = data[40] + data[16];
  z11p = data[16] - data[40];
  v102 = data[32] + data[24];
  tmp4h = data[24] - data[32];
  v103 = v102 + data[56] + *data;
  dataq = data[56] + *data - v102;
  tmp11p = v101 + v99;
  *data = v101 + v99 + v103;
  data[32] = v103 - tmp11p;
  v104 = (v99 - v101 + dataq) * 0.70710677;
  data[16] = dataq + v104;
  data[48] = dataq - v104;
  v105 = v100;
  v106 = v100 + v98;
  v107 = (tmp4h + z11p - v106) * 0.38268343;
  datar = (tmp4h + z11p) * 0.54119611 + v107;
  tmp11q = v106 * 1.306563 + v107;
  v108 = v98;
  v109 = (z11p + v105) * 0.70710677;
  z11q = v109 + v108;
  data[40] = datar + v108 - v109;
  data[24] = v108 - v109 - datar;
  data[8] = z11q + tmp11q;
  data[56] = z11q - tmp11q;
  v110 = data[1] - data[57];
  v111 = data[49] + data[9];
  v112 = data[9] - data[49];
  v113 = data[41] + data[17];
  z11r = data[17] - data[41];
  v114 = data[33] + data[25];
  tmp4i = data[25] - data[33];
  v115 = v114 + data[57] + data[1];
  datas = data[57] + data[1] - v114;
  tmp11r = v113 + v111;
  data[1] = v113 + v111 + v115;
  data[33] = v115 - tmp11r;
  v116 = (v111 - v113 + datas) * 0.70710677;
  data[17] = datas + v116;
  data[49] = datas - v116;
  v117 = v112;
  v118 = v112 + v110;
  v119 = (tmp4i + z11r - v118) * 0.38268343;
  datat = (tmp4i + z11r) * 0.54119611 + v119;
  tmp11s = v118 * 1.306563 + v119;
  v120 = v110;
  v121 = (z11r + v117) * 0.70710677;
  z11s = v121 + v120;
  data[41] = datat + v120 - v121;
  data[25] = v120 - v121 - datat;
  data[9] = z11s + tmp11s;
  data[57] = z11s - tmp11s;
  v122 = data[2] - data[58];
  v123 = data[50] + data[10];
  v124 = data[10] - data[50];
  v125 = data[42] + data[18];
  z11t = data[18] - data[42];
  v126 = data[34] + data[26];
  tmp4j = data[26] - data[34];
  v127 = v126 + data[58] + data[2];
  datau = data[58] + data[2] - v126;
  tmp11t = v125 + v123;
  data[2] = v125 + v123 + v127;
  data[34] = v127 - tmp11t;
  v128 = (v123 - v125 + datau) * 0.70710677;
  data[18] = datau + v128;
  data[50] = datau - v128;
  v129 = v124;
  v130 = v124 + v122;
  v131 = (tmp4j + z11t - v130) * 0.38268343;
  datav = (tmp4j + z11t) * 0.54119611 + v131;
  tmp11u = v130 * 1.306563 + v131;
  v132 = v122;
  v133 = (z11t + v129) * 0.70710677;
  z11u = v133 + v132;
  data[42] = datav + v132 - v133;
  data[26] = v132 - v133 - datav;
  data[10] = z11u + tmp11u;
  data[58] = z11u - tmp11u;
  v134 = data[3] - data[59];
  v135 = data[51] + data[11];
  v136 = data[11] - data[51];
  v137 = data[43] + data[19];
  z11v = data[19] - data[43];
  v138 = data[35] + data[27];
  tmp4k = data[27] - data[35];
  v139 = v138 + data[59] + data[3];
  dataw = data[59] + data[3] - v138;
  tmp11v = v137 + v135;
  data[3] = v137 + v135 + v139;
  data[35] = v139 - tmp11v;
  v140 = (v135 - v137 + dataw) * 0.70710677;
  data[19] = dataw + v140;
  data[51] = dataw - v140;
  v141 = v136;
  v142 = v136 + v134;
  v143 = (tmp4k + z11v - v142) * 0.38268343;
  datax = (tmp4k + z11v) * 0.54119611 + v143;
  tmp11w = v142 * 1.306563 + v143;
  v144 = v134;
  v145 = (z11v + v141) * 0.70710677;
  z11w = v145 + v144;
  data[43] = datax + v144 - v145;
  data[27] = v144 - v145 - datax;
  data[11] = z11w + tmp11w;
  data[59] = z11w - tmp11w;
  v146 = data[4] - data[60];
  v147 = data[52] + data[12];
  v148 = data[12] - data[52];
  v149 = data[44] + data[20];
  z11x = data[20] - data[44];
  v150 = data[36] + data[28];
  tmp4l = data[28] - data[36];
  v151 = v150 + data[60] + data[4];
  datay = data[60] + data[4] - v150;
  tmp11x = v149 + v147;
  data[4] = v149 + v147 + v151;
  data[36] = v151 - tmp11x;
  v152 = (v147 - v149 + datay) * 0.70710677;
  data[20] = datay + v152;
  data[52] = datay - v152;
  v153 = v148;
  v154 = v148 + v146;
  v155 = (tmp4l + z11x - v154) * 0.38268343;
  dataz = (tmp4l + z11x) * 0.54119611 + v155;
  tmp11y = v154 * 1.306563 + v155;
  v156 = v146;
  v157 = (z11x + v153) * 0.70710677;
  z11y = v157 + v156;
  data[44] = dataz + v156 - v157;
  data[28] = v156 - v157 - dataz;
  data[12] = z11y + tmp11y;
  data[60] = z11y - tmp11y;
  v158 = data[5] - data[61];
  v159 = data[53] + data[13];
  v160 = data[13] - data[53];
  v161 = data[45] + data[21];
  z11z = data[21] - data[45];
  v162 = data[37] + data[29];
  tmp4m = data[29] - data[37];
  v163 = v162 + data[61] + data[5];
  databa = data[61] + data[5] - v162;
  tmp11z = v161 + v159;
  data[5] = v161 + v159 + v163;
  data[37] = v163 - tmp11z;
  v164 = (v159 - v161 + databa) * 0.70710677;
  data[21] = databa + v164;
  data[53] = databa - v164;
  v165 = v160;
  v166 = v160 + v158;
  v167 = (tmp4m + z11z - v166) * 0.38268343;
  databb = (tmp4m + z11z) * 0.54119611 + v167;
  tmp11ba = v166 * 1.306563 + v167;
  v168 = v158;
  v169 = (z11z + v165) * 0.70710677;
  z11ba = v169 + v168;
  data[45] = databb + v168 - v169;
  data[29] = v168 - v169 - databb;
  data[13] = z11ba + tmp11ba;
  data[61] = z11ba - tmp11ba;
  v170 = data[6] - data[62];
  v171 = data[54] + data[14];
  v172 = data[14] - data[54];
  v173 = data[46] + data[22];
  z11bb = data[22] - data[46];
  v174 = data[38] + data[30];
  tmp4n = data[30] - data[38];
  v175 = v174 + data[62] + data[6];
  databc = data[62] + data[6] - v174;
  tmp11bb = v173 + v171;
  data[6] = v173 + v171 + v175;
  data[38] = v175 - tmp11bb;
  v176 = (v171 - v173 + databc) * 0.70710677;
  data[22] = databc + v176;
  data[54] = databc - v176;
  v177 = v172;
  v178 = v172 + v170;
  v179 = (tmp4n + z11bb - v178) * 0.38268343;
  databd = (tmp4n + z11bb) * 0.54119611 + v179;
  tmp11bc = v178 * 1.306563 + v179;
  v180 = v170;
  v181 = (z11bb + v177) * 0.70710677;
  z11bc = v181 + v180;
  data[46] = databd + v180 - v181;
  data[30] = v180 - v181 - databd;
  data[14] = z11bc + tmp11bc;
  data[62] = z11bc - tmp11bc;
  v182 = data[7] - data[63];
  v183 = data[55] + data[15];
  v184 = data[15] - data[55];
  v185 = data[47] + data[23];
  z11bd = data[23] - data[47];
  v186 = data[39] + data[31];
  tmp4o = data[31] - data[39];
  v187 = v186 + data[63] + data[7];
  databe = data[63] + data[7] - v186;
  tmp11bd = v185 + v183;
  data[7] = v185 + v183 + v187;
  data[39] = v187 - tmp11bd;
  v188 = (v183 - v185 + databe) * 0.70710677;
  data[23] = databe + v188;
  data[55] = databe - v188;
  v189 = v184;
  v190 = v184 + v182;
  v191 = (tmp4o + z11bd - v190) * 0.38268343;
  databf = (tmp4o + z11bd) * 0.54119611 + v191;
  tmp11be = v190 * 1.306563 + v191;
  v192 = v182;
  v193 = (z11bd + v189) * 0.70710677;
  z11be = v193 + v192;
  data[47] = databf + v192 - v193;
  data[31] = v192 - v193 - databf;
  data[15] = z11be + tmp11be;
  data[63] = z11be - tmp11be;
}
