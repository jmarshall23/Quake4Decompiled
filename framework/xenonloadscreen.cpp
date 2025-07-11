
// FUNC: void __cdecl GenerateXenonLoadScreenData(void)
void __cdecl GenerateXenonLoadScreenData()
{
  idFileList *v0; // ebp
  int v1; // ebx
  int v2; // eax
  char v3; // cl
  const char *v4; // esi
  unsigned int v5; // kr00_4
  char v6; // cl
  int v7; // eax
  char *v8; // edx
  const char *v9; // esi
  unsigned int v10; // eax
  int v11; // edi
  int v12; // eax
  char *data; // edx
  const char *v14; // ecx
  char v15; // al
  int v16; // esi
  int v17; // eax
  char v18; // cl
  char *v19; // edx
  idMaterial *v20; // eax
  idMaterial *v21; // eax
  bool v22; // cc
  idMaterial *v23; // eax
  idMaterial *v24; // eax
  idMaterial *v25; // eax
  idMaterial *v26; // eax
  idMaterial *v27; // eax
  idMaterial *v28; // eax
  const idDecl *v29; // eax
  const char *v30; // esi
  unsigned int v31; // eax
  int v32; // edi
  int v33; // eax
  char *v34; // edx
  const char *v35; // ecx
  char v36; // al
  int j; // ebp
  char *v38; // edx
  const char *v39; // ecx
  char v40; // al
  int v41; // esi
  int k; // eax
  char v43; // cl
  char *v44; // edx
  const char *v45; // eax
  const char *v46; // esi
  int v47; // edi
  char v48; // cl
  int m; // eax
  char *v50; // edx
  idMaterial *v51; // esi
  int len; // esi
  char *v53; // ecx
  char *v54; // edx
  char v55; // al
  int v56; // esi
  int v57; // eax
  char v58; // cl
  char *v59; // edx
  int i; // [esp+80h] [ebp-1CCh]
  int ia; // [esp+80h] [ebp-1CCh]
  int numMaps; // [esp+84h] [ebp-1C8h]
  int numMapsa; // [esp+84h] [ebp-1C8h]
  idStr matName; // [esp+88h] [ebp-1C4h] BYREF
  idStr xprName; // [esp+A8h] [ebp-1A4h] BYREF
  idStr rdfName; // [esp+C8h] [ebp-184h] BYREF
  idStr fileName; // [esp+E8h] [ebp-164h] BYREF
  idStr fullName; // [esp+108h] [ebp-144h] BYREF
  idToken token; // [esp+128h] [ebp-124h] BYREF
  idLexer lex; // [esp+178h] [ebp-D4h] BYREF
  int v71; // [esp+248h] [ebp-4h]

  globalImages->GenerateRDF(globalImages, "_ignore_me");
  com_Bundler.internalVar->InternalSetInteger(com_Bundler.internalVar, 1);
  v0 = fileSystem->ListFiles(fileSystem, "loadscreens", ".gui", 0, 0, 0);
  i = 0;
  if ( v0->list.num > 0 )
  {
    v1 = 0;
    numMaps = 0;
    do
    {
      fullName.alloced = 20;
      fullName.data = fullName.baseBuffer;
      fullName.baseBuffer[0] = 0;
      v2 = 0;
      do
      {
        v3 = aLoadscreens_0[v2];
        fullName.baseBuffer[v2++] = v3;
      }
      while ( v3 );
      fullName.len = 12;
      v4 = *(char **)((char *)&v0->list.list->data + v1);
      v71 = 0;
      if ( v4 )
      {
        v5 = strlen(v4);
        if ( (int)(v5 + 13) > fullName.alloced )
          idStr::ReAllocate(&fullName, v5 + 13, 1);
        v6 = *v4;
        v7 = 0;
        if ( *v4 )
        {
          do
          {
            v8 = &fullName.data[v7++];
            v8[fullName.len] = v6;
            v6 = v4[v7];
          }
          while ( v6 );
          v1 = numMaps;
        }
        fullName.len = v5 + 12;
        fullName.data[v5 + 12] = 0;
      }
      idLexer::idLexer(&lex, fullName.data, 6300, 0);
      v9 = *(char **)((char *)&v0->list.list->data + v1);
      LOBYTE(v71) = 1;
      xprName.len = 0;
      xprName.alloced = 20;
      xprName.data = xprName.baseBuffer;
      xprName.baseBuffer[0] = 0;
      if ( v9 )
      {
        v10 = (unsigned int)&v9[strlen(v9) + 1];
        v11 = v10 - (_DWORD)(v9 + 1);
        v12 = v10 - (_DWORD)v9;
        if ( v12 > 20 )
          idStr::ReAllocate(&xprName, v12, 1);
        data = xprName.data;
        v14 = v9;
        do
        {
          v15 = *v14;
          *data++ = *v14++;
        }
        while ( v15 );
        xprName.len = v11;
      }
      LOBYTE(v71) = 2;
      idStr::StripFileExtension(&xprName);
      v16 = xprName.len + 4;
      if ( xprName.len + 5 > xprName.alloced )
        idStr::ReAllocate(&xprName, xprName.len + 5, 1);
      v17 = 0;
      v18 = 95;
      do
      {
        v19 = &xprName.data[v17++];
        v19[xprName.len] = v18;
        v18 = aGui_3[v17];
      }
      while ( v18 );
      xprName.len = v16;
      xprName.data[v16] = 0;
      token.floatvalue = 0.0;
      token.len = 0;
      token.alloced = 20;
      token.data = token.baseBuffer;
      token.baseBuffer[0] = 0;
      LOBYTE(v71) = 3;
      while ( idLexer::ReadToken(&lex, &token) )
      {
        if ( !idStr::Icmp(token.data, "background") )
        {
          idLexer::ReadToken(&lex, &token);
          v20 = (idMaterial *)declManager->FindMaterial(declManager, token.data, 1);
          idMaterial::ReloadImages(v20, 1);
        }
        if ( !idStr::Icmp(token.data, "font") )
        {
          idLexer::ReadToken(&lex, &token);
          v21 = (idMaterial *)declManager->FindMaterial(declManager, token.data, 1);
          idMaterial::ReloadImages(v21, 1);
        }
      }
      globalImages->GenerateRDF(globalImages, xprName.data);
      LOBYTE(v71) = 2;
      idStr::FreeData(&token);
      LOBYTE(v71) = 1;
      idStr::FreeData(&xprName);
      LOBYTE(v71) = 0;
      idLexer::~idLexer(&lex);
      v71 = -1;
      idStr::FreeData(&fullName);
      v1 += 32;
      v22 = ++i < v0->list.num;
      numMaps = v1;
    }
    while ( v22 );
  }
  v23 = (idMaterial *)declManager->FindMaterial(declManager, "fonts/english/marine_12.tga", 1);
  idMaterial::ReloadImages(v23, 1);
  v24 = (idMaterial *)declManager->FindMaterial(declManager, "fonts/english/marine_24.tga", 1);
  idMaterial::ReloadImages(v24, 1);
  v25 = (idMaterial *)declManager->FindMaterial(declManager, "fonts/english/marine_48.tga", 1);
  idMaterial::ReloadImages(v25, 1);
  v26 = (idMaterial *)declManager->FindMaterial(declManager, "fonts/english/lowpixel_12.tga", 1);
  idMaterial::ReloadImages(v26, 1);
  v27 = (idMaterial *)declManager->FindMaterial(declManager, "fonts/english/lowpixel_24.tga", 1);
  idMaterial::ReloadImages(v27, 1);
  v28 = (idMaterial *)declManager->FindMaterial(declManager, "fonts/english/lowpixel_48.tga", 1);
  idMaterial::ReloadImages(v28, 1);
  globalImages->GenerateRDF(globalImages, "fonts_gui");
  numMapsa = declManager->GetNumDecls(declManager, DECL_MAPDEF);
  for ( ia = 0; ia < numMapsa; ++ia )
  {
    v29 = declManager->DeclByIndex(declManager, 17, ia, 1);
    v30 = v29->base->GetName(v29->base);
    fileName.len = 0;
    fileName.alloced = 20;
    fileName.data = fileName.baseBuffer;
    fileName.baseBuffer[0] = 0;
    if ( v30 )
    {
      v31 = (unsigned int)&v30[strlen(v30) + 1];
      v32 = v31 - (_DWORD)(v30 + 1);
      v33 = v31 - (_DWORD)v30;
      if ( v33 > 20 )
        idStr::ReAllocate(&fileName, v33, 1);
      v34 = fileName.data;
      v35 = v30;
      do
      {
        v36 = *v35;
        *v34++ = *v35++;
      }
      while ( v36 );
      fileName.len = v32;
    }
    v71 = 4;
    idStr::StripPath(&fileName);
    for ( j = 1; j < 4; ++j )
    {
      matName.data = matName.baseBuffer;
      matName.len = 0;
      matName.alloced = 20;
      matName.baseBuffer[0] = 0;
      idStr::ReAllocate(&matName, 22, 1);
      v38 = matName.data;
      v39 = "gfx/guis/loadscreens/";
      do
      {
        v40 = *v39;
        *v38++ = *v39++;
      }
      while ( v40 );
      matName.len = 21;
      v41 = fileName.len + 21;
      LOBYTE(v71) = 5;
      if ( fileName.len + 22 > matName.alloced )
        idStr::ReAllocate(&matName, fileName.len + 22, 1);
      for ( k = 0; k < fileName.len; v44[matName.len] = v43 )
      {
        v43 = fileName.data[k];
        v44 = &matName.data[k++];
      }
      matName.len = v41;
      matName.data[v41] = 0;
      v45 = va("_%d", j);
      v46 = v45;
      if ( v45 )
      {
        v47 = strlen(v45) + matName.len;
        if ( v47 + 1 > matName.alloced )
          idStr::ReAllocate(&matName, v47 + 1, 1);
        v48 = *v46;
        for ( m = 0; v48; v48 = v46[m] )
        {
          v50 = &matName.data[m++];
          v50[matName.len] = v48;
        }
        matName.len = v47;
        matName.data[v47] = 0;
      }
      v51 = (idMaterial *)declManager->FindMaterial(declManager, matName.data, 1);
      LOBYTE(v71) = 4;
      idStr::FreeData(&matName);
    }
    idMaterial::ReloadImages(v51, 1);
    len = fileName.len;
    rdfName.len = 0;
    rdfName.alloced = 20;
    rdfName.data = rdfName.baseBuffer;
    rdfName.baseBuffer[0] = 0;
    if ( fileName.len + 1 > 20 )
      idStr::ReAllocate(&rdfName, fileName.len + 1, 1);
    v53 = fileName.data;
    v54 = rdfName.data;
    do
    {
      v55 = *v53;
      *v54++ = *v53++;
    }
    while ( v55 );
    rdfName.len = len;
    v56 = len + 4;
    LOBYTE(v71) = 6;
    if ( v56 + 1 > rdfName.alloced )
      idStr::ReAllocate(&rdfName, v56 + 1, 1);
    v57 = 0;
    v58 = 95;
    do
    {
      v59 = &rdfName.data[v57++];
      v59[rdfName.len] = v58;
      v58 = aGui_3[v57];
    }
    while ( v58 );
    rdfName.len = v56;
    rdfName.data[v56] = 0;
    globalImages->GenerateRDF(globalImages, rdfName.data);
    LOBYTE(v71) = 4;
    idStr::FreeData(&rdfName);
    v71 = -1;
    idStr::FreeData(&fileName);
  }
  com_Bundler.internalVar->InternalSetInteger(com_Bundler.internalVar, 0);
}
