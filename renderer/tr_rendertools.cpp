
// FUNC: void __cdecl RB_SimpleWorldSetup(void)
void __cdecl RB_SimpleWorldSetup()
{
  backEnd.currentSpace = &backEnd.viewDef->worldSpace;
  qglLoadMatrixf(backEnd.viewDef->worldSpace.modelViewMatrix);
  backEnd.currentScissor = backEnd.viewDef->scissor;
  qglScissor(
    backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
    (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
    backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
    (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
}

// FUNC: void __cdecl RB_PolygonClear(void)
void __cdecl RB_PolygonClear()
{
  unsigned __int8 IsEnabled; // bl
  unsigned __int8 bDT; // [esp+5h] [ebp-3h]
  unsigned __int8 bCF; // [esp+6h] [ebp-2h]
  unsigned __int8 bST; // [esp+7h] [ebp-1h]

  qglPushMatrix();
  IsEnabled = qglIsEnabled(0xDE1u);
  bDT = qglIsEnabled(0xB71u);
  bCF = qglIsEnabled(0xB44u);
  bST = qglIsEnabled(0xC11u);
  qglLoadIdentity();
  qglDisable(0xDE1u);
  qglDisable(0xB71u);
  qglDisable(0xB44u);
  qglDisable(0xC11u);
  qglBegin(9u);
  qglVertex3f(-20.0, -20.0, -10.0);
  qglVertex3f(20.0, -20.0, -10.0);
  qglVertex3f(20.0, 20.0, -10.0);
  qglVertex3f(-20.0, 20.0, -10.0);
  qglEnd();
  if ( IsEnabled )
    qglEnable(0xDE1u);
  if ( bDT )
    qglEnable(0xB71u);
  if ( bCF )
    qglEnable(0xB44u);
  if ( bST )
    qglEnable(0xC11u);
  qglPopMatrix();
}

// FUNC: void __cdecl RB_CountStencilBuffer(void)
void __cdecl RB_CountStencilBuffer()
{
  unsigned __int8 *v0; // esi
  int v1; // edx
  int v2; // eax
  int v3; // edi
  int count; // [esp+Ch] [ebp-4h]

  v0 = (unsigned __int8 *)R_StaticAlloc(glConfig.vidWidth * glConfig.vidHeight);
  qglReadPixels(0, 0, glConfig.vidWidth, glConfig.vidHeight, 0x1901u, 0x1401u, v0);
  v1 = 0;
  v2 = 0;
  count = 0;
  if ( glConfig.vidWidth * glConfig.vidHeight > 0 )
  {
    do
    {
      v3 = v0[v2++];
      v1 += v3;
    }
    while ( v2 < glConfig.vidWidth * glConfig.vidHeight );
    count = v1;
  }
  R_StaticFree(v0);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "overdraw: %5.1f\n",
    (double)count / (double)(glConfig.vidWidth * glConfig.vidHeight));
}

// FUNC: R_ColorByStencilBuffer
void R_ColorByStencilBuffer()
{
  int v0; // edi
  const float *v1; // esi

  qglClearColor(1.0, 1.0, 1.0, 1.0);
  qglDisable(0xC11u);
  qglClear(0x4000u);
  qglStencilOp(0x1E00u, 0x1E00u, 0x1E00u);
  v0 = 0;
  v1 = colors_0[0];
  do
  {
    qglColor3fv(v1);
    qglStencilFunc(0x202u, v0, 0xFFu);
    RB_PolygonClear();
    v1 += 3;
    ++v0;
  }
  while ( (int)v1 < (int)colors_0[6] );
  qglStencilFunc(0x207u, 0, 0xFFu);
}

// FUNC: float __cdecl RB_DrawTextLength(char const *,float,int)
double __cdecl RB_DrawTextLength(const char *text, float scale, int len)
{
  double result; // st7
  signed int v4; // edi
  signed int i; // esi
  unsigned int v6; // ecx
  unsigned int v7; // eax
  double v8; // st6
  int v9; // edx
  int v10; // ecx
  int *v11; // eax

  result = 0.0;
  if ( text && *text )
  {
    v4 = len;
    if ( !len )
      v4 = strlen(text);
    for ( i = 0; i < v4; ++i )
    {
      v6 = text[i] - 32;
      if ( v6 <= 0x5F )
      {
        v7 = v6;
        v8 = (double)(int)simplex[v6][1];
        v9 = 2 * simplex[v6][0];
        if ( v9 > 0 )
        {
          v10 = 0;
          v11 = (int *)&simplex[v7][2];
          do
          {
            if ( *v11 >= 0 )
            {
              v11 += 2;
              v10 += 2;
              if ( *v11 >= 0 )
                continue;
            }
            ++v11;
            ++v10;
          }
          while ( v10 < v9 );
        }
        result = result + v8 * scale;
      }
    }
  }
  return result;
}

// FUNC: void __cdecl RB_TestImage(void)
void __cdecl RB_TestImage()
{
  idImage *testImage; // edi
  int *v1; // eax
  const unsigned __int8 *v2; // ecx
  int v3; // edx
  int v4; // esi
  int uploadHeight; // edi
  double v6; // st7
  float v7; // esi
  float v8; // edi
  float w; // [esp+3Ch] [ebp-1Ch]
  int wa; // [esp+3Ch] [ebp-1Ch]
  float h; // [esp+40h] [ebp-18h]
  float v12; // [esp+44h] [ebp-14h]
  float v13; // [esp+44h] [ebp-14h]
  float v14; // [esp+44h] [ebp-14h]
  cinData_t cin; // [esp+48h] [ebp-10h] BYREF

  testImage = tr.testImage;
  if ( tr.testImage )
  {
    if ( tr.testVideo )
    {
      v1 = (int *)((int (__stdcall *)(cinData_t *, int))tr.testVideo->ImageForTime)(
                    &cin,
                    (int)((backEnd.viewDef->floatTime - tr.testVideoStartTime) * 1000.0));
      v2 = (const unsigned __int8 *)v1[2];
      v3 = *v1;
      v4 = v1[1];
      cin.status = v1[3];
      if ( !v2 )
      {
        tr.testImage = 0;
        return;
      }
      idImage::UploadScratch(testImage, v2, v3, v4);
      w = 0.25;
      h = 0.25;
    }
    else
    {
      uploadHeight = tr.testImage->uploadHeight;
      wa = tr.testImage->uploadWidth;
      if ( wa <= uploadHeight )
        wa = tr.testImage->uploadHeight;
      v6 = (double)wa;
      h = (double)uploadHeight * 0.25 / v6;
      w = (double)tr.testImage->uploadWidth * 0.25 / v6 * ((double)glConfig.vidHeight / (double)glConfig.vidWidth);
    }
    qglLoadIdentity();
    qglMatrixMode(0x1701u);
    GL_State(65637);
    qglColor3f(1.0, 1.0, 1.0);
    qglPushMatrix();
    qglLoadIdentity();
    qglOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    tr.testImage->Bind(tr.testImage);
    qglBegin(7u);
    qglTexCoord2f(0.0, 1.0);
    v12 = 0.5 - w;
    v7 = v12;
    qglVertex2f(v12, 0.0);
    qglTexCoord2f(0.0, 0.0);
    v13 = h + h;
    v8 = v13;
    qglVertex2f(v7, v13);
    qglTexCoord2f(1.0, 0.0);
    v14 = w + 0.5;
    qglVertex2f(v14, v8);
    qglTexCoord2f(1.0, 1.0);
    qglVertex2f(v14, 0.0);
    qglEnd();
    qglPopMatrix();
    qglMatrixMode(0x1700u);
  }
}

// FUNC: void __cdecl RB_DrawBounds(class idBounds const &)
void __cdecl RB_DrawBounds(const idBounds *bounds)
{
  if ( bounds->b[0].x <= (double)bounds->b[1].x )
  {
    qglBegin(2u);
    qglVertex3f(bounds->b[0].x, bounds->b[0].y, bounds->b[0].z);
    qglVertex3f(bounds->b[0].x, bounds->b[1].y, bounds->b[0].z);
    qglVertex3f(bounds->b[1].x, bounds->b[1].y, bounds->b[0].z);
    qglVertex3f(bounds->b[1].x, bounds->b[0].y, bounds->b[0].z);
    qglEnd();
    qglBegin(2u);
    qglVertex3f(bounds->b[0].x, bounds->b[0].y, bounds->b[1].z);
    qglVertex3f(bounds->b[0].x, bounds->b[1].y, bounds->b[1].z);
    qglVertex3f(bounds->b[1].x, bounds->b[1].y, bounds->b[1].z);
    qglVertex3f(bounds->b[1].x, bounds->b[0].y, bounds->b[1].z);
    qglEnd();
    qglBegin(1u);
    qglVertex3f(bounds->b[0].x, bounds->b[0].y, bounds->b[0].z);
    qglVertex3f(bounds->b[0].x, bounds->b[0].y, bounds->b[1].z);
    qglVertex3f(bounds->b[0].x, bounds->b[1].y, bounds->b[0].z);
    qglVertex3f(bounds->b[0].x, bounds->b[1].y, bounds->b[1].z);
    qglVertex3f(bounds->b[1].x, bounds->b[0].y, bounds->b[0].z);
    qglVertex3f(bounds->b[1].x, bounds->b[0].y, bounds->b[1].z);
    qglVertex3f(bounds->b[1].x, bounds->b[1].y, bounds->b[0].z);
    qglVertex3f(bounds->b[1].x, bounds->b[1].y, bounds->b[1].z);
    qglEnd();
  }
}

// FUNC: void __cdecl RB_SimpleSurfaceSetup(struct drawSurf_s const *)
void __cdecl RB_SimpleSurfaceSetup(const drawSurf_s *drawSurf)
{
  const viewEntity_s *space; // eax

  space = drawSurf->space;
  if ( space != backEnd.currentSpace )
  {
    qglLoadMatrixf(space->modelViewMatrix);
    backEnd.currentSpace = drawSurf->space;
  }
  if ( r_useScissor.internalVar->integerValue )
  {
    if ( !idScreenRect::Equals(&backEnd.currentScissor, &drawSurf->scissorRect) )
    {
      backEnd.currentScissor = drawSurf->scissorRect;
      qglScissor(
        backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
        (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
        backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
        (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
    }
  }
}

// FUNC: void __cdecl RB_T_RenderHitSurface(struct drawSurf_s const *)
void __cdecl RB_T_RenderHitSurface(const drawSurf_s *surf)
{
  const idMaterial *material; // eax
  idImage *v2; // eax
  unsigned __int8 *materialType; // eax
  idImage *v4; // eax
  float v5; // [esp+4h] [ebp-14h]
  float v6; // [esp+8h] [ebp-10h]
  float v7; // [esp+Ch] [ebp-Ch]

  if ( r_showHitImages.internalVar->integerValue == 1 )
    GL_State(32);
  else
    GL_State(0);
  material = surf->material;
  if ( material->materialTypeArray )
  {
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    v2 = globalImages->ImageFromFile(globalImages, surf->material->materialTypeArrayName.data, 2, 1, 0, 2, 0, 0);
    v2->Bind(v2);
    RB_RenderTriangleSurface(surf->geo);
  }
  else
  {
    materialType = (unsigned __int8 *)material->materialType;
    if ( materialType )
    {
      v7 = (double)materialType[42] * 0.0039215689;
      v6 = (double)materialType[41] * 0.0039215689;
      v5 = (double)materialType[40] * 0.0039215689;
      qglColor4f(v5, v6, v7, 1.0);
      v4 = globalImages->GetWhiteImage(globalImages);
      v4->Bind(v4);
      RB_RenderTriangleSurface(surf->geo);
    }
  }
}

// FUNC: void __cdecl RB_ShowHitImages(void)
void __cdecl RB_ShowHitImages()
{
  if ( r_showHitImages.internalVar->integerValue )
  {
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    RB_RenderDrawSurfListWithFunction(backEnd.viewDef->drawSurfs, backEnd.viewDef->numDrawSurfs, RB_T_RenderHitSurface);
    qglEnable(0xB71u);
    qglDisable(0x2A02u);
    GL_State(0x10000);
    GL_Cull(0);
  }
}

// FUNC: void __cdecl RB_ShowOverdraw(void)
void __cdecl RB_ShowOverdraw()
{
  const idMaterial *v0; // ebp
  viewLight_s *viewLights; // ecx
  int v2; // ebx
  int v3; // edx
  drawSurf_s **drawSurfs; // edi
  const drawSurf_s *i; // eax
  const drawSurf_s *j; // eax
  unsigned __int8 *v7; // eax
  int v8; // edx
  unsigned __int8 *v9; // ecx
  int v10; // edi
  int v11; // esi
  const viewDef_s *viewDef; // ecx
  viewLight_s *v13; // esi
  const drawSurf_s *k; // ecx
  const drawSurf_s *m; // ecx
  int interactions; // [esp+8h] [ebp-8h]
  int numDrawSurfs; // [esp+Ch] [ebp-4h]

  if ( r_showOverDraw.internalVar->integerValue )
  {
    v0 = declManager->FindMaterial(declManager, "textures/common/overdrawtest", 0);
    if ( v0 )
    {
      viewLights = backEnd.viewDef->viewLights;
      v2 = backEnd.viewDef->numDrawSurfs;
      v3 = 0;
      drawSurfs = backEnd.viewDef->drawSurfs;
      numDrawSurfs = v2;
      interactions = 0;
      if ( viewLights )
      {
        do
        {
          for ( i = viewLights->localInteractions; i; ++v3 )
            i = i->nextOnLight;
          for ( j = viewLights->globalInteractions; j; ++v3 )
            j = j->nextOnLight;
          viewLights = viewLights->next;
        }
        while ( viewLights );
        interactions = v3;
      }
      v7 = R_FrameAlloc(v2 + 4 * v3);
      v8 = 0;
      if ( v2 > 0 )
      {
        v9 = v7;
        v10 = (char *)drawSurfs - (char *)v7;
        v8 = v2;
        do
        {
          v11 = *(_DWORD *)&v9[v10];
          if ( *(_DWORD *)(v11 + 8) )
            *(_DWORD *)(v11 + 8) = v0;
          *(_DWORD *)v9 = v11;
          v9 += 4;
          --v2;
        }
        while ( v2 );
      }
      viewDef = backEnd.viewDef;
      v13 = backEnd.viewDef->viewLights;
      if ( v13 )
      {
        do
        {
          for ( k = v13->localInteractions; k; ++v8 )
          {
            k->material = v0;
            *(_DWORD *)&v7[4 * v8] = k;
            k = k->nextOnLight;
          }
          for ( m = v13->globalInteractions; m; ++v8 )
          {
            m->material = v0;
            *(_DWORD *)&v7[4 * v8] = m;
            m = m->nextOnLight;
          }
          v13->localInteractions = 0;
          v13->globalInteractions = 0;
          v13 = v13->next;
        }
        while ( v13 );
        viewDef = backEnd.viewDef;
      }
      switch ( r_showOverDraw.internalVar->integerValue )
      {
        case 1:
          viewDef->drawSurfs = (drawSurf_s **)v7;
          backEnd.viewDef->numDrawSurfs = numDrawSurfs;
          break;
        case 2:
          viewDef->drawSurfs = (drawSurf_s **)&v7[4 * numDrawSurfs];
          backEnd.viewDef->numDrawSurfs = interactions;
          break;
        case 3:
          viewDef->drawSurfs = (drawSurf_s **)v7;
          backEnd.viewDef->numDrawSurfs += interactions;
          break;
      }
    }
  }
}

// FUNC: void __cdecl RB_ShowIntensity(void)
void __cdecl RB_ShowIntensity()
{
  unsigned __int8 *v0; // edi
  int v1; // eax
  unsigned __int8 *v2; // ecx
  unsigned int v3; // esi
  int v4; // eax

  if ( r_showIntensity.internalVar->integerValue )
  {
    v0 = (unsigned __int8 *)R_StaticAlloc(4 * glConfig.vidWidth * glConfig.vidHeight);
    qglReadPixels(0, 0, glConfig.vidWidth, glConfig.vidHeight, 0x1908u, 0x1401u, v0);
    v1 = 4 * glConfig.vidWidth * glConfig.vidHeight;
    if ( v1 > 0 )
    {
      v2 = v0 + 1;
      v3 = ((unsigned int)(v1 - 1) >> 2) + 1;
      do
      {
        v4 = *(v2 - 1);
        if ( *v2 > v4 )
          v4 = *v2;
        if ( v2[1] > v4 )
          v4 = v2[1];
        if ( v4 >= 128 )
        {
          *(v2 - 1) = 0;
          *v2 = 2 * (-1 - v4);
          v2[1] = 2 * (v4 + 0x80);
        }
        else
        {
          *(v2 - 1) = 2 * (0x80 - v4);
          *v2 = 2 * v4;
          v2[1] = 0;
        }
        v2 += 4;
        --v3;
      }
      while ( v3 );
    }
    qglLoadIdentity();
    qglMatrixMode(0x1701u);
    GL_State(0x10000);
    qglPushMatrix();
    qglLoadIdentity();
    qglOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    qglRasterPos2f(0.0, 0.0);
    qglPopMatrix();
    qglColor3f(1.0, 1.0, 1.0);
    globalImages->BindNull(globalImages);
    qglMatrixMode(0x1700u);
    qglDrawPixels(glConfig.vidWidth, glConfig.vidHeight, 0x1908u, 0x1401u, v0);
    R_StaticFree(v0);
  }
}

// FUNC: void __cdecl RB_ShowDepthBuffer(void)
void __cdecl RB_ShowDepthBuffer()
{
  void *v0; // esi

  if ( r_showDepth.internalVar->integerValue )
  {
    qglPushMatrix();
    qglLoadIdentity();
    qglMatrixMode(0x1701u);
    qglPushMatrix();
    qglLoadIdentity();
    qglOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    qglRasterPos2f(0.0, 0.0);
    qglPopMatrix();
    qglMatrixMode(0x1700u);
    qglPopMatrix();
    GL_State(0x10000);
    qglColor3f(1.0, 1.0, 1.0);
    globalImages->BindNull(globalImages);
    v0 = R_StaticAlloc(4 * glConfig.vidWidth * glConfig.vidHeight);
    memset(v0, 0, 4 * glConfig.vidWidth * glConfig.vidHeight);
    qglReadPixels(0, 0, glConfig.vidWidth, glConfig.vidHeight, 0x1902u, 0x1406u, v0);
    qglDrawPixels(glConfig.vidWidth, glConfig.vidHeight, 0x1908u, 0x1401u, v0);
    R_StaticFree(v0);
  }
}

// FUNC: void __cdecl RB_ShowLightCount(void)
void __cdecl RB_ShowLightCount()
{
  idImage *v0; // eax
  viewLight_s *i; // ebx
  int j; // edi
  const drawSurf_s *localInteractions; // esi
  char *v4; // eax

  if ( r_showLightCount.internalVar->integerValue )
  {
    GL_State(0x20000);
    RB_SimpleWorldSetup();
    qglClearStencil(0);
    qglClear(0x400u);
    qglEnable(0xB90u);
    if ( r_showLightCount.internalVar->integerValue < 2 )
      qglStencilOp(0x1E00u, 0x1E00u, 0x1E02u);
    else
      qglStencilOp(0x1E00u, 0x1E02u, 0x1E02u);
    qglStencilFunc(0x207u, 1, 0xFFu);
    v0 = globalImages->GetDefaultImage(globalImages);
    v0->Bind(v0);
    for ( i = backEnd.viewDef->viewLights; i; i = i->next )
    {
      for ( j = 0; j < 2; ++j )
      {
        if ( j )
          localInteractions = i->localInteractions;
        else
          localInteractions = i->globalInteractions;
        for ( ; localInteractions; localInteractions = localInteractions->nextOnLight )
        {
          RB_SimpleSurfaceSetup(localInteractions);
          if ( localInteractions->geo->ambientCache )
          {
            v4 = idVertexCache::Position(&vertexCache, localInteractions->geo->ambientCache);
            qglVertexPointer(3, 0x1406u, 64, v4);
            RB_DrawElementsWithCounters(localInteractions->geo);
          }
        }
      }
    }
    R_ColorByStencilBuffer();
    if ( r_showLightCount.internalVar->integerValue > 2 )
      RB_CountStencilBuffer();
  }
}

// FUNC: void __cdecl RB_ShowSilhouette(void)
void __cdecl RB_ShowSilhouette()
{
  viewLight_s *viewLights; // ebp
  int v1; // eax
  const drawSurf_s *localShadows; // ebx
  const srfTriangles_s *geo; // edi
  char *v4; // eax
  int v5; // esi
  int *indexes; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  char v10; // dl
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  const drawSurf_s *surf; // [esp+0h] [ebp-14h]
  int i; // [esp+4h] [ebp-10h]
  const viewLight_s *vLight; // [esp+8h] [ebp-Ch]
  int i2; // [esp+Ch] [ebp-8h]
  int i3; // [esp+10h] [ebp-4h]

  if ( r_showSilhouette.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xDE1u);
    qglDisable(0xB90u);
    qglColor3f(0.0, 0.0, 0.0);
    GL_State(0x2000);
    GL_Cull(2);
    qglDisable(0xB71u);
    RB_RenderDrawSurfListWithFunction(
      backEnd.viewDef->drawSurfs,
      backEnd.viewDef->numDrawSurfs,
      RB_T_RenderTriangleSurface);
    RB_SimpleWorldSetup();
    qglColor3f(0.5, 0.0, 0.0);
    GL_State(32);
    viewLights = backEnd.viewDef->viewLights;
    for ( vLight = viewLights; viewLights; vLight = viewLights )
    {
      v1 = 0;
      i = 0;
      do
      {
        if ( v1 )
          localShadows = viewLights->localShadows;
        else
          localShadows = viewLights->globalShadows;
        surf = localShadows;
        if ( localShadows )
        {
          do
          {
            RB_SimpleSurfaceSetup(localShadows);
            geo = localShadows->geo;
            v4 = idVertexCache::Position(&vertexCache, localShadows->geo->shadowCache);
            qglVertexPointer(3, 0x1406u, 16, v4);
            qglBegin(1u);
            v5 = 0;
            if ( geo->numIndexes > 0 )
            {
              do
              {
                indexes = geo->indexes;
                v7 = indexes[v5 + 1];
                v8 = indexes[v5];
                v9 = indexes[v5 + 2];
                v10 = v9;
                i3 = v9;
                i2 = v7;
                v11 = v7 & 1;
                v12 = v8 & 1;
                v13 = v10 & 1;
                if ( v13 + v12 + v11 == 1 )
                {
                  if ( v12 + v11 )
                  {
                    if ( !(v13 + v12) )
                    {
                      qglArrayElement(v8);
                      qglArrayElement(i3);
                    }
                  }
                  else
                  {
                    qglArrayElement(v8);
                    qglArrayElement(i2);
                  }
                }
                v5 += 3;
              }
              while ( v5 < geo->numIndexes );
              localShadows = surf;
              viewLights = (viewLight_s *)vLight;
            }
            qglEnd();
            localShadows = localShadows->nextOnLight;
            surf = localShadows;
          }
          while ( localShadows );
          v1 = i;
        }
        i = ++v1;
      }
      while ( v1 < 2 );
      viewLights = viewLights->next;
    }
    qglEnable(0xB71u);
    GL_State(0x10000);
    qglColor3f(1.0, 1.0, 1.0);
    GL_Cull(0);
  }
}

// FUNC: RB_ShowShadowCount
void RB_ShowShadowCount()
{
  idImage *v0; // eax
  viewLight_s *i; // ebx
  int j; // ebp
  const drawSurf_s *localShadows; // edi
  const srfTriangles_s *geo; // esi
  int integerValue; // ecx
  const void *v6; // eax
  int v7; // eax

  if ( r_showShadowCount.internalVar->integerValue )
  {
    GL_State(0x10000);
    qglClearStencil(0);
    qglClear(0x400u);
    qglEnable(0xB90u);
    qglStencilOp(0x1E00u, 0x1E02u, 0x1E02u);
    qglStencilFunc(0x207u, 1, 0xFFu);
    v0 = globalImages->GetDefaultImage(globalImages);
    v0->Bind(v0);
    GL_Cull(2);
    for ( i = backEnd.viewDef->viewLights; i; i = i->next )
    {
      for ( j = 0; j < 2; ++j )
      {
        if ( j )
          localShadows = i->localShadows;
        else
          localShadows = i->globalShadows;
        for ( ; localShadows; localShadows = localShadows->nextOnLight )
        {
          RB_SimpleSurfaceSetup(localShadows);
          geo = localShadows->geo;
          if ( localShadows->geo->shadowCache )
          {
            integerValue = r_showShadowCount.internalVar->integerValue;
            if ( (integerValue != 3 || geo->numShadowIndexesNoCaps == geo->numIndexes)
              && (integerValue != 4 || geo->numShadowIndexesNoCaps != geo->numIndexes) )
            {
              v6 = idVertexCache::Position(&vertexCache, localShadows->geo->shadowCache);
              qglVertexPointer(4, 0x1406u, 16, v6);
              RB_DrawElementsWithCounters(geo);
            }
          }
        }
      }
    }
    R_ColorByStencilBuffer();
    v7 = r_showShadowCount.internalVar->integerValue;
    switch ( v7 )
    {
      case 2:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "all shadows ");
        break;
      case 3:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "turboShadows ");
        break;
      case 4:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "static shadows ");
        break;
    }
    if ( r_showShadowCount.internalVar->integerValue >= 2 )
      RB_CountStencilBuffer();
    GL_Cull(0);
  }
}

// FUNC: void __cdecl RB_ShowBatchSize(struct drawSurf_s * *,int)
void __cdecl RB_ShowBatchSize(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  if ( r_showBatchSize.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xDE1u);
    qglDisable(0xB90u);
    qglColor3f(1.0, 1.0, 1.0);
    GL_State(0x2000);
    if ( r_showBatchSize.internalVar->integerValue == 1 )
    {
      qglPolygonOffset(-1.0, -2.0);
      qglEnable(0x2A02u);
    }
    else
    {
      if ( r_showBatchSize.internalVar->integerValue == 3 )
        GL_Cull(2);
      else
        GL_Cull(0);
      qglDisable(0xB71u);
    }
    RB_RenderDrawSurfListWithFunction(drawSurfs, numDrawSurfs, RB_T_ShowBatchSizeRenderTriangleSurface);
    qglEnable(0xB71u);
    qglDisable(0x2A02u);
    qglDepthRange(0.0, 1.0);
    GL_State(0x10000);
    GL_Cull(0);
  }
}

// FUNC: RB_ShowOverdraw
void __cdecl RB_ShowOverdraw(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  idImage *v2; // eax
  int integerValue; // edi
  int i; // esi
  float v5; // eax
  float v6; // ecx
  float vidWidth; // [esp+28h] [ebp-18h]
  float v8; // [esp+28h] [ebp-18h]
  float v9; // [esp+28h] [ebp-18h]
  float v10; // [esp+28h] [ebp-18h]
  unsigned int v11; // [esp+2Ch] [ebp-14h]
  float v12; // [esp+2Ch] [ebp-14h]
  float vidHeight; // [esp+2Ch] [ebp-14h]
  float v14; // [esp+2Ch] [ebp-14h]
  float v15; // [esp+2Ch] [ebp-14h]
  float v16; // [esp+2Ch] [ebp-14h]

  if ( r_showOverDraw.internalVar->integerValue
    && r_showOverdrawMax.internalVar->integerValue
    && r_showOverdrawDivisor.internalVar->integerValue )
  {
    if ( glConfig.stencilBits >= 4 )
    {
      GL_DisableTexCoordState();
      globalImages->BindNull(globalImages);
      qglDisable(0xDE1u);
      qglEnable(0xB90u);
      qglStencilMask(0xFFFFFFFF);
      qglClearStencil(0);
      qglStencilFunc(0x207u, 0, 0xFFFFFFFF);
      qglStencilOp(0x1E00u, 0x1E02u, 0x1E02u);
      qglDisable(0xBC0u);
      qglDisable(0xB71u);
      qglClear(0x400u);
      qglEnable(0xBE2u);
      qglBlendFunc(0x302u, 0x303u);
      qglColor4f(1.0, 1.0, 1.0, 0.0);
      qglPolygonMode(0x408u, 0x1B02u);
      RB_RenderDrawSurfListWithFunction(drawSurfs, numDrawSurfs, RB_T_RenderTriangleSurfacePasses);
      v2 = globalImages->GetWhiteImage(globalImages);
      v2->Bind(v2);
      qglViewport(0, 0, glConfig.vidWidth, glConfig.vidHeight);
      qglMatrixMode(0x1701u);
      qglLoadIdentity();
      qglOrtho(0.0, (double)glConfig.vidWidth, (double)glConfig.vidHeight, 0.0, 10000.0, -10000.0);
      qglMatrixMode(0x1700u);
      qglLoadIdentity();
      GL_State(101);
      qglDisable(0xB71u);
      qglDepthMask(1u);
      GL_TexEnv(8448);
      qglDisable(0xB44u);
      qglDisable(0xB60u);
      qglDisable(0x3000u);
      qglStencilMask(0);
      integerValue = r_showOverdrawMax.internalVar->integerValue;
      for ( i = 1; i < integerValue; ++i )
      {
        v11 = 12 * (i / r_showOverdrawDivisor.internalVar->integerValue);
        v5 = *(float *)&dword_102FD6CC[v11 / 4];
        v6 = colors_1[v11 / 0xC][0];
        v12 = (double)(i / integerValue) * 0.75 + 0.25;
        qglColor4f(v6, v5, dword_102FD6D0[3 * (i / r_showOverdrawDivisor.internalVar->integerValue)], v12);
        qglStencilFunc(0x201u, i, 0xFFu);
        qglBegin(7u);
        qglVertex2f(0.0, 0.0);
        vidWidth = (float)glConfig.vidWidth;
        qglVertex2f(vidWidth, 0.0);
        vidHeight = (float)glConfig.vidHeight;
        v8 = (float)glConfig.vidWidth;
        qglVertex2f(v8, vidHeight);
        v14 = (float)glConfig.vidHeight;
        qglVertex2f(0.0, v14);
        qglEnd();
        integerValue = r_showOverdrawMax.internalVar->integerValue;
      }
      qglColor4f(qword_102FD704, *(&qword_102FD704 + 1), dword_102FD70C, 1.0);
      qglStencilFunc(0x201u, 2 * r_showOverdrawMax.internalVar->integerValue, 0xFFu);
      qglBegin(7u);
      qglVertex2f(0.0, 0.0);
      v9 = (float)glConfig.vidWidth;
      qglVertex2f(v9, 0.0);
      v15 = (float)glConfig.vidHeight;
      v10 = (float)glConfig.vidWidth;
      qglVertex2f(v10, v15);
      v16 = (float)glConfig.vidHeight;
      qglVertex2f(0.0, v16);
      qglEnd();
      qglEnable(0xB71u);
      qglDepthMask(0);
      qglDisable(0x2A02u);
      qglDepthRange(0.0, 1.0);
      GL_State(0x10000);
      GL_Cull(0);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Warning: not enough stencil bits to measure overdraw: %d\n",
        glConfig.stencilBits);
      r_showOverDraw.internalVar->InternalSetBool(r_showOverDraw.internalVar, 0);
    }
  }
}

// FUNC: RB_ShowUnweld
void __cdecl RB_ShowUnweld(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int numVerts; // esi
  int v3; // eax
  drawSurf_s **v4; // ebx
  int v5; // eax
  void *v6; // esp
  int v7; // edi
  const drawSurf_s *v8; // esi
  const srfTriangles_s *geo; // ebx
  int v10; // eax
  int v11; // edi
  int v12; // ecx
  float *v13; // esi
  idDrawVert *verts; // ecx
  double v15; // st7
  float *v16; // ecx
  int integerValue; // edx
  bool v18; // cc
  int v19; // [esp+0h] [ebp-44h] BYREF
  int i; // [esp+Ch] [ebp-38h]
  int v21; // [esp+10h] [ebp-34h]
  int v22; // [esp+14h] [ebp-30h]
  int v23; // [esp+18h] [ebp-2Ch]
  float v24; // [esp+1Ch] [ebp-28h]
  float v25; // [esp+20h] [ebp-24h]
  float v26; // [esp+24h] [ebp-20h]
  float v27; // [esp+28h] [ebp-1Ch]
  float v28; // [esp+2Ch] [ebp-18h]
  float v29; // [esp+30h] [ebp-14h]
  float v30; // [esp+34h] [ebp-10h]
  float v31; // [esp+38h] [ebp-Ch]
  bool *cache; // [esp+3Ch] [ebp-8h]
  int count; // [esp+40h] [ebp-4h]

  numVerts = 0;
  if ( r_showUnweld.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_State(0x10000);
    v3 = 0;
    if ( numDrawSurfs <= 0 )
    {
      v4 = drawSurfs;
    }
    else
    {
      do
      {
        v4 = drawSurfs;
        if ( drawSurfs[v3]->geo->numVerts > numVerts )
          numVerts = drawSurfs[v3]->geo->numVerts;
        ++v3;
      }
      while ( v3 < numDrawSurfs );
    }
    v5 = numVerts + 3;
    LOBYTE(v5) = (numVerts + 3) & 0xFC;
    v6 = alloca(v5);
    v7 = 0;
    cache = (bool *)&v19;
    i = 0;
    if ( numDrawSurfs > 0 )
    {
      while ( 1 )
      {
        v8 = v4[v7];
        RB_SimpleSurfaceSetup(v8);
        qglPointSize(4.0);
        qglBegin(0);
        geo = v8->geo;
        if ( v8->geo->verts )
        {
          memset(cache, 0, geo->numVerts);
          v10 = geo->numVerts;
          if ( v10 > 0 )
          {
            v11 = 1;
            v12 = 0;
            v21 = 1;
            v22 = 0;
            do
            {
              if ( !cache[v11 - 1] )
              {
                v13 = (float *)((char *)&geo->verts->xyz.x + v12);
                count = 0;
                if ( v11 < v10 )
                {
                  v23 = v12 + 64;
                  do
                  {
                    if ( !cache[v11] )
                    {
                      verts = geo->verts;
                      v15 = *v13 - *(float *)((char *)&verts->xyz.x + v23);
                      v16 = (float *)((char *)&verts->xyz.x + v23);
                      v31 = v15;
                      LODWORD(v31) &= ~0x80000000;
                      if ( v31 <= 0.001 )
                      {
                        v30 = v13[1] - v16[1];
                        LODWORD(v30) &= ~0x80000000;
                        if ( v30 <= 0.001 )
                        {
                          v29 = v13[2] - v16[2];
                          LODWORD(v29) &= ~0x80000000;
                          if ( v29 <= 0.001 )
                          {
                            integerValue = r_showUnweld.internalVar->integerValue;
                            if ( integerValue < 2
                              || (v28 = v13[14] - v16[14], HIBYTE(v28) &= ~0x80u, v28 <= 0.001)
                              && (v27 = v13[15] - v16[15], HIBYTE(v27) &= ~0x80u, v27 <= 0.001) )
                            {
                              if ( integerValue < 3
                                || (v26 = v13[4] - v16[4], HIBYTE(v26) &= ~0x80u, v26 <= 0.001)
                                && (v25 = v13[5] - v16[5], HIBYTE(v25) &= ~0x80u, v25 <= 0.001)
                                && (v24 = v13[6] - v16[6], HIBYTE(v24) &= ~0x80u, v24 <= 0.001) )
                              {
                                ++count;
                                cache[v11] = 1;
                              }
                            }
                          }
                        }
                      }
                    }
                    v23 += 64;
                    ++v11;
                  }
                  while ( v11 < geo->numVerts );
                  if ( count )
                  {
                    if ( --count >= 4 )
                      count = 3;
                    qglColor3ubv(UnweldColors[count]);
                    qglVertex3fv(v13);
                  }
                }
              }
              v10 = geo->numVerts;
              v11 = v21 + 1;
              v12 = v22 + 64;
              v18 = v21 < v10;
              v22 += 64;
              ++v21;
            }
            while ( v18 );
          }
          qglEnd();
          v7 = i;
        }
        i = ++v7;
        if ( v7 >= numDrawSurfs )
          break;
        v4 = drawSurfs;
      }
    }
    GL_State(0x10000);
  }
}

// FUNC: RB_ShowSurfaceInfo
void __cdecl RB_ShowSurfaceInfo()
{
  double z; // st7
  double y; // st6
  double v2; // st6
  double v3; // st7
  double v4; // st7
  idRenderWorldLocal_vtbl *v5; // esi
  int v6; // eax
  const char *v7; // eax
  double v8; // st7
  const char *v9; // eax
  int numStages; // ebp
  int v11; // edi
  shaderStage_t *v12; // eax
  idImage *image; // esi
  char *data; // ebp
  const char *NameForInternalFormat; // eax
  const char *v16; // eax
  double v17; // st7
  const char *v18; // eax
  double v19; // st7
  int v20; // [esp+9Ch] [ebp-14Ch]
  float counta; // [esp+B0h] [ebp-138h]
  float countb; // [esp+B0h] [ebp-138h]
  float countc; // [esp+B0h] [ebp-138h]
  int count; // [esp+B0h] [ebp-138h]
  float v25; // [esp+B4h] [ebp-134h]
  int v26; // [esp+B4h] [ebp-134h]
  float v27; // [esp+B8h] [ebp-130h]
  int v28; // [esp+B8h] [ebp-130h]
  float v29; // [esp+BCh] [ebp-12Ch] BYREF
  float v30; // [esp+C0h] [ebp-128h]
  float v31; // [esp+C4h] [ebp-124h]
  float v32; // [esp+C8h] [ebp-120h]
  float v33; // [esp+CCh] [ebp-11Ch]
  idVec3 end; // [esp+D0h] [ebp-118h] BYREF
  modelTrace_s mt; // [esp+DCh] [ebp-10Ch] BYREF
  idStr work; // [esp+108h] [ebp-E0h] BYREF
  float v37[3]; // [esp+128h] [ebp-C0h] BYREF
  idVec3 start; // [esp+134h] [ebp-B4h] BYREF
  idStr name; // [esp+140h] [ebp-A8h] BYREF
  float v40[3]; // [esp+160h] [ebp-88h]
  float v41; // [esp+16Ch] [ebp-7Ch]
  idVec3 trans[3]; // [esp+178h] [ebp-70h] BYREF
  float matrix[16]; // [esp+19Ch] [ebp-4Ch] BYREF
  int numDrawSurfsa; // [esp+1E4h] [ebp-4h]

  if ( r_showSurfaceInfo.internalVar->integerValue )
  {
    z = tr.primaryView->renderView.viewaxis.mat[0].z;
    y = tr.primaryView->renderView.viewaxis.mat[0].y;
    v29 = tr.primaryView->renderView.viewaxis.mat[0].x * 16.0;
    v25 = z * 16.0 + tr.primaryView->renderView.vieworg.z;
    counta = y * 16.0 + tr.primaryView->renderView.vieworg.y;
    v2 = v29 + tr.primaryView->renderView.vieworg.x;
    start.z = v25;
    end.x = v2;
    start.x = v2;
    start.y = counta;
    v3 = tr.primaryView->renderView.viewaxis.mat[0].z * 1000.0;
    v27 = tr.primaryView->renderView.viewaxis.mat[0].y * 1000.0;
    v29 = tr.primaryView->renderView.viewaxis.mat[0].x * 1000.0;
    end.x = v29 + end.x;
    end.y = v27 + counta;
    end.z = v3 + v25;
    if ( ((unsigned __int8 (__thiscall *)(idRenderWorldLocal *, modelTrace_s *, idVec3 *, idVec3 *, _DWORD, _DWORD, _DWORD))tr.primaryWorld->Trace)(
           tr.primaryWorld,
           &mt,
           &start,
           &end,
           0,
           0,
           0) )
    {
      GL_DisableTexCoordState();
      globalImages->BindNull(globalImages);
      qglDisable(0xDE1u);
      qglDisable(0xB90u);
      qglColor3f(1.0, 1.0, 1.0);
      GL_State(0x2000);
      qglPolygonOffset(-1.0, -2.0);
      qglEnable(0x2A02u);
      `vector constructor iterator'(trans, 0xCu, 3, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
      R_AxisToModelMatrix(&mt.entity->axis, &mt.entity->origin, matrix);
      v4 = tr.primaryView->renderView.viewaxis.mat[2].z * 12.0;
      countb = tr.primaryView->renderView.viewaxis.mat[2].y * 12.0;
      v29 = tr.primaryView->renderView.viewaxis.mat[2].x * 12.0;
      v29 = mt.point.x + v29;
      v30 = mt.point.y + countb;
      v31 = v4 + mt.point.z;
      v5 = tr.primaryWorld->__vftable;
      v6 = ((int (__thiscall *)(idRenderModel *, float *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))mt.entity->hModel->Name)(
             mt.entity->hModel,
             &v29,
             1051931443,
             &colorRed,
             &tr.primaryView->renderView.viewaxis,
             1,
             0,
             0);
      ((void (__thiscall *)(idRenderWorldLocal *, int))v5->DrawTextA)(tr.primaryWorld, v6);
      v7 = mt.material->base->GetName(mt.material->base);
      ((void (__thiscall *)(idRenderWorldLocal *, const char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))tr.primaryWorld->DrawTextA)(
        tr.primaryWorld,
        v7,
        &mt.point,
        1051931443,
        &colorBlue,
        &tr.primaryView->renderView.viewaxis,
        1,
        0,
        0);
      if ( mt.materialType )
      {
        v8 = tr.primaryView->renderView.viewaxis.mat[2].z * -12.0;
        countc = tr.primaryView->renderView.viewaxis.mat[2].y * -12.0;
        v29 = tr.primaryView->renderView.viewaxis.mat[2].x * -12.0;
        v29 = v29 + mt.point.x;
        v30 = mt.point.y + countc;
        v31 = v8 + mt.point.z;
        v9 = mt.materialType->base->GetName(mt.materialType->base);
        ((void (__thiscall *)(idRenderWorldLocal *, const char *, float *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))tr.primaryWorld->DrawTextA)(
          tr.primaryWorld,
          v9,
          &v29,
          1051931443,
          &colorGreen,
          &tr.primaryView->renderView.viewaxis,
          1,
          0,
          0);
      }
      if ( r_showSurfaceInfo.internalVar->integerValue > 1 )
      {
        work.len = 0;
        work.alloced = 20;
        work.data = work.baseBuffer;
        work.baseBuffer[0] = 0;
        numDrawSurfsa = 0;
        name.len = 0;
        name.alloced = 20;
        name.data = name.baseBuffer;
        name.baseBuffer[0] = 0;
        numStages = mt.material->numStages;
        v11 = 0;
        LOBYTE(numDrawSurfsa) = 1;
        count = numStages;
        if ( numStages > 0 )
        {
          v26 = 0;
          v28 = -24;
          do
          {
            v12 = &mt.material->stages[v26];
            if ( v12->newStage || v12->newShaderStage )
            {
              v18 = va("%d: newStage/newShaderStage", v11);
              idStr::operator=(&work, v18);
              v19 = (double)v28;
              v33 = v19 * tr.primaryView->renderView.viewaxis.mat[2].z;
              v32 = v19 * tr.primaryView->renderView.viewaxis.mat[2].y;
              v41 = v19 * tr.primaryView->renderView.viewaxis.mat[2].x;
              v29 = v41 + mt.point.x;
              v30 = mt.point.y + v32;
              v31 = mt.point.z + v33;
              ((void (__thiscall *)(idRenderWorldLocal *, char *, float *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))tr.primaryWorld->DrawTextA)(
                tr.primaryWorld,
                work.data,
                &v29,
                1050253722,
                &colorGreen,
                &tr.primaryView->renderView.viewaxis,
                1,
                0,
                0);
            }
            else
            {
              image = v12->texture.image;
              if ( image )
              {
                idStr::ExtractFileBase(&image->imgName, &name);
                data = name.data;
                v20 = idImage::StorageSize(image);
                NameForInternalFormat = idImage::GetNameForInternalFormat(image);
                v16 = va(
                        "%d: %s (%dx%dx%s - %d)",
                        v11,
                        data,
                        image->uploadWidth,
                        image->uploadHeight,
                        NameForInternalFormat,
                        v20);
                idStr::operator=(&work, v16);
                numStages = count;
              }
              else
              {
                idStr::operator=(&work, "<null image>");
              }
              v17 = (double)v28;
              v32 = v17 * tr.primaryView->renderView.viewaxis.mat[2].z;
              v33 = v17 * tr.primaryView->renderView.viewaxis.mat[2].y;
              v40[0] = v17 * tr.primaryView->renderView.viewaxis.mat[2].x;
              v37[0] = v40[0] + mt.point.x;
              v37[1] = mt.point.y + v33;
              v37[2] = mt.point.z + v32;
              ((void (__thiscall *)(idRenderWorldLocal *, char *, float *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))tr.primaryWorld->DrawTextA)(
                tr.primaryWorld,
                work.data,
                v37,
                1050253722,
                &colorGreen,
                &tr.primaryView->renderView.viewaxis,
                1,
                0,
                0);
            }
            ++v26;
            v28 -= 12;
            ++v11;
          }
          while ( v11 < numStages );
        }
        LOBYTE(numDrawSurfsa) = 0;
        idStr::FreeData(&name);
        numDrawSurfsa = -1;
        idStr::FreeData(&work);
      }
      qglEnable(0xB71u);
      qglDisable(0x2A02u);
      qglDepthRange(0.0, 1.0);
      GL_State(0x10000);
      GL_Cull(0);
    }
  }
}

// FUNC: RB_ShowViewEntitys
void __usercall RB_ShowViewEntitys(viewEntity_s *vModels@<eax>)
{
  int integerValue; // eax
  idRenderModel *v3; // eax
  int v4; // eax
  float v5; // ecx
  float v6; // edx
  float v7; // ecx
  float v8; // edx
  float v9; // eax
  idBounds b; // [esp+1Ch] [ebp-30h] BYREF
  idBounds v11; // [esp+34h] [ebp-18h] BYREF

  integerValue = r_showViewEntitys.internalVar->integerValue;
  if ( integerValue )
  {
    if ( integerValue == 2 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "view entities: ");
      for ( ; vModels; vModels = vModels->next )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%i ",
          vModels->entityDef->index);
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
    }
    else
    {
      GL_DisableTexCoordState();
      globalImages->BindNull(globalImages);
      qglDisable(0xDE1u);
      qglDisable(0xB90u);
      qglColor3f(1.0, 1.0, 1.0);
      GL_State(0x2000);
      GL_Cull(2);
      qglDisable(0xB71u);
      qglDisable(0xC11u);
      for ( ; vModels; vModels = vModels->next )
      {
        qglLoadMatrixf(vModels->modelViewMatrix);
        if ( vModels->entityDef )
        {
          qglColor3f(1.0, 1.0, 0.0);
          RB_DrawBounds(&vModels->entityDef->referenceBounds);
          qglColor3f(1.0, 1.0, 1.0);
          v3 = R_EntityDefDynamicModel(vModels->entityDef, 0);
          if ( v3 )
          {
            v4 = (int)v3->Bounds(v3, &v11, &vModels->entityDef->parms);
            v5 = *(float *)(v4 + 4);
            b.b[0].x = *(float *)v4;
            v6 = *(float *)(v4 + 8);
            b.b[0].y = v5;
            v7 = *(float *)(v4 + 12);
            b.b[0].z = v6;
            v8 = *(float *)(v4 + 16);
            v9 = *(float *)(v4 + 20);
            b.b[1].x = v7;
            b.b[1].y = v8;
            b.b[1].z = v9;
            RB_DrawBounds(&b);
          }
        }
      }
      qglEnable(0xB71u);
      qglDisable(0x2A02u);
      qglDepthRange(0.0, 1.0);
      GL_State(0x10000);
      GL_Cull(0);
    }
  }
}

// FUNC: RB_ShowTexturePolarity
void __cdecl RB_ShowTexturePolarity(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int v2; // edi
  const drawSurf_s *v3; // eax
  const srfTriangles_s *geo; // esi
  int v5; // ebp
  int *indexes; // eax
  idDrawVert *verts; // ecx
  int v8; // edi
  double v9; // st7
  int v10; // edi
  int v11; // esi
  double v12; // st7
  int v13; // esi
  idDrawVert *v14; // ebx
  double v15; // st7
  float v16; // [esp-1Ch] [ebp-28h]
  float v17; // [esp-18h] [ebp-24h]
  float v18; // [esp+0h] [ebp-Ch]
  const srfTriangles_s *tri; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( r_showTexturePolarity.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_State(101);
    qglColor3f(1.0, 1.0, 1.0);
    v2 = 0;
    i = 0;
    if ( numDrawSurfs <= 0 )
      goto LABEL_17;
    while ( 1 )
    {
      v3 = drawSurfs[v2];
      geo = v3->geo;
      tri = v3->geo;
      if ( !v3->geo->verts )
        goto LABEL_16;
      RB_SimpleSurfaceSetup(v3);
      qglBegin(4u);
      v5 = 0;
      if ( geo->numIndexes <= 0 )
        goto LABEL_15;
      while ( 1 )
      {
        indexes = geo->indexes;
        verts = geo->verts;
        v8 = indexes[v5 + 1] << 6;
        v9 = *(float *)((char *)&verts->st.x + v8);
        v10 = (int)verts + v8;
        v11 = indexes[v5] << 6;
        v12 = v9 - *(float *)((char *)&verts->st.x + v11);
        v13 = (int)verts + v11;
        v14 = &verts[indexes[v5 + 2]];
        v15 = v12 * (v14->st.y - *(float *)(v13 + 60))
            - (v14->st.x - *(float *)(v13 + 56)) * (*(float *)(v10 + 60) - *(float *)(v13 + 60));
        v18 = v15;
        HIBYTE(v18) &= ~0x80u;
        if ( v18 >= 0.0001 )
        {
          v17 = 0.0;
          if ( v15 < 0.0 )
          {
            qglColor4f(1.0, 0.0, 0.0, 0.5);
            goto LABEL_13;
          }
          v16 = 1.0;
        }
        else
        {
          v17 = 1.0;
          v16 = 0.0;
        }
        qglColor4f(0.0, v16, v17, 0.5);
LABEL_13:
        qglVertex3fv((const float *)v13);
        qglVertex3fv((const float *)v10);
        qglVertex3fv(&v14->xyz.x);
        v5 += 3;
        if ( v5 >= tri->numIndexes )
          break;
        geo = tri;
      }
      v2 = i;
LABEL_15:
      qglEnd();
LABEL_16:
      i = ++v2;
      if ( v2 >= numDrawSurfs )
      {
LABEL_17:
        GL_State(0x10000);
        return;
      }
    }
  }
}

// FUNC: RB_ShowUnsmoothedTangents
void __cdecl RB_ShowUnsmoothedTangents(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int v2; // edi
  drawSurf_s *v3; // esi
  const srfTriangles_s *geo; // ebp
  int v5; // esi
  int *indexes; // eax
  idDrawVert *verts; // ecx
  const float *p_x; // edi
  const float *v9; // ebx
  int i; // [esp+0h] [ebp-4h]

  if ( r_showUnsmoothedTangents.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_State(101);
    qglColor4f(0.0, 1.0, 0.0, 0.5);
    v2 = 0;
    for ( i = 0; v2 < numDrawSurfs; i = v2 )
    {
      v3 = drawSurfs[v2];
      if ( v3->material->unsmoothedTangents )
      {
        RB_SimpleSurfaceSetup(drawSurfs[v2]);
        geo = v3->geo;
        qglBegin(4u);
        v5 = 0;
        if ( geo->numIndexes > 0 )
        {
          do
          {
            indexes = geo->indexes;
            verts = geo->verts;
            p_x = &verts[indexes[v5 + 1]].xyz.x;
            v9 = &verts[indexes[v5 + 2]].xyz.x;
            qglVertex3fv(&verts[indexes[v5]].xyz.x);
            qglVertex3fv(p_x);
            qglVertex3fv(v9);
            v5 += 3;
          }
          while ( v5 < geo->numIndexes );
          v2 = i;
        }
        qglEnd();
      }
      ++v2;
    }
    GL_State(0x10000);
  }
}

// FUNC: RB_ShowTangentSpace
void __cdecl RB_ShowTangentSpace(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int i; // ebp
  const drawSurf_s *v3; // esi
  const srfTriangles_s *geo; // edi
  int j; // ebx
  int integerValue; // eax
  int v7; // esi
  double v8; // st7
  float v9; // [esp+0h] [ebp-20h]
  float v10; // [esp+4h] [ebp-1Ch]
  float v11; // [esp+8h] [ebp-18h]

  if ( r_showTangentSpace.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_State(101);
    for ( i = 0; i < numDrawSurfs; ++i )
    {
      v3 = drawSurfs[i];
      RB_SimpleSurfaceSetup(v3);
      geo = v3->geo;
      if ( v3->geo->verts )
      {
        qglBegin(4u);
        for ( j = 0; j < geo->numIndexes; ++j )
        {
          integerValue = r_showTangentSpace.internalVar->integerValue;
          v7 = (int)&geo->verts[geo->indexes[j]];
          if ( integerValue == 1 )
          {
            v11 = (*(float *)(v7 + 40) + 1.0) * 0.5;
            v10 = (*(float *)(v7 + 36) + 1.0) * 0.5;
            v8 = *(float *)(v7 + 32);
          }
          else if ( integerValue == 2 )
          {
            v11 = (*(float *)(v7 + 52) + 1.0) * 0.5;
            v10 = (*(float *)(v7 + 48) + 1.0) * 0.5;
            v8 = *(float *)(v7 + 44);
          }
          else
          {
            v11 = (*(float *)(v7 + 24) + 1.0) * 0.5;
            v10 = (*(float *)(v7 + 20) + 1.0) * 0.5;
            v8 = *(float *)(v7 + 16);
          }
          v9 = (v8 + 1.0) * 0.5;
          qglColor4f(v9, v10, v11, 0.5);
          qglVertex3fv((const float *)v7);
        }
        qglEnd();
      }
    }
    GL_State(0x10000);
  }
}

// FUNC: RB_ShowVertexColor
void __cdecl RB_ShowVertexColor(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int i; // ebp
  const drawSurf_s *v3; // esi
  const srfTriangles_s *geo; // edi
  int j; // ebx
  int v6; // esi

  if ( r_showVertexColor.internalVar->integerValue )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_State(0);
    for ( i = 0; i < numDrawSurfs; ++i )
    {
      v3 = drawSurfs[i];
      RB_SimpleSurfaceSetup(v3);
      geo = v3->geo;
      if ( v3->geo->verts )
      {
        qglBegin(4u);
        for ( j = 0; j < geo->numIndexes; ++j )
        {
          v6 = (int)&geo->verts[geo->indexes[j]];
          qglColor4ubv((const unsigned __int8 *)(v6 + 12));
          qglVertex3fv((const float *)v6);
        }
        qglEnd();
      }
    }
    GL_State(0x10000);
  }
}

// FUNC: RB_ShowTextureVectors
void __cdecl RB_ShowTextureVectors(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int v2; // esi
  const srfTriangles_s *geo; // ebp
  int v4; // ebx
  int *indexes; // eax
  idDrawVert *verts; // edx
  int v7; // esi
  double v8; // st7
  float *v9; // esi
  int v10; // ecx
  double v11; // st7
  float *v12; // ecx
  double v13; // st6
  float *p_x; // edi
  double v15; // st7
  double v16; // st6
  int v17; // eax
  float v18; // edx
  float v19; // eax
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st5
  double v24; // st5
  double v25; // st4
  double v26; // st3
  long double v27; // st3
  long double v28; // rtt
  double v29; // st7
  double v30; // st6
  double v31; // st5
  long double v32; // st4
  long double v33; // st3
  double floatValue; // st5
  float inva; // [esp+0h] [ebp-D0h]
  idVec3 mid; // [esp+4h] [ebp-CCh] BYREF
  float v37; // [esp+10h] [ebp-C0h]
  float d0[5]; // [esp+14h] [ebp-BCh]
  float d1[5]; // [esp+28h] [ebp-A8h]
  idVec3 temp; // [esp+3Ch] [ebp-94h]
  int i; // [esp+48h] [ebp-88h]
  idVec3 tangents[2]; // [esp+4Ch] [ebp-84h] BYREF
  float v43; // [esp+64h] [ebp-6Ch]
  float v44; // [esp+68h] [ebp-68h]
  float v45; // [esp+70h] [ebp-60h]
  float v46; // [esp+74h] [ebp-5Ch]
  float v47; // [esp+78h] [ebp-58h]
  float v48; // [esp+7Ch] [ebp-54h]
  float v49; // [esp+80h] [ebp-50h]
  float v50; // [esp+88h] [ebp-48h]
  float v51; // [esp+8Ch] [ebp-44h]
  float v52; // [esp+9Ch] [ebp-34h]
  float v53; // [esp+A8h] [ebp-28h]
  float v54; // [esp+B4h] [ebp-1Ch]
  float v55; // [esp+C0h] [ebp-10h]
  float v56; // [esp+C4h] [ebp-Ch]

  if ( r_showTextureVectors.internalVar->floatValue != 0.0 )
  {
    GL_State(0);
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    v2 = 0;
    for ( i = 0; v2 < numDrawSurfs; i = v2 )
    {
      geo = drawSurfs[v2]->geo;
      if ( geo->verts && geo->facePlanes )
      {
        RB_SimpleSurfaceSetup(drawSurfs[v2]);
        qglBegin(1u);
        v4 = 0;
        if ( geo->numIndexes > 0 )
        {
          do
          {
            indexes = geo->indexes;
            verts = geo->verts;
            v7 = indexes[v4 + 1] << 6;
            v8 = *(float *)((char *)&verts->xyz.x + v7);
            v9 = (float *)((char *)&verts->xyz.x + v7);
            v10 = indexes[v4] << 6;
            v11 = v8 + *(float *)((char *)&verts->xyz.x + v10);
            v12 = (float *)((char *)&verts->xyz.x + v10);
            v13 = v12[1] + v9[1];
            p_x = &verts[indexes[v4 + 2]].xyz.x;
            v54 = v9[2] + v12[2];
            v56 = v11 + *p_x;
            v15 = v13 + p_x[1];
            v16 = v54 + p_x[2];
            v43 = v56 * 0.33333334;
            mid.x = v43;
            v44 = v15 * 0.33333334;
            mid.y = v44;
            mid.z = v16 * 0.33333334;
            v17 = (int)&geo->facePlanes[v4 / 3];
            v45 = *(float *)v17;
            v18 = *(float *)(v17 + 4);
            v19 = *(float *)(v17 + 8);
            v46 = v18;
            v47 = v19;
            v55 = v19 * 0.1;
            mid.x = v45 * 0.1 + v43;
            mid.y = v18 * 0.1 + v44;
            mid.z = v55 + v16 * 0.33333334;
            v20 = *v9 - *v12;
            d0[1] = v9[1] - v12[1];
            d0[2] = v9[2] - v12[2];
            d0[3] = v9[14] - v12[14];
            d0[4] = v9[15] - v12[15];
            v21 = *p_x - *v12;
            d1[1] = p_x[1] - v12[1];
            d1[2] = p_x[2] - v12[2];
            d1[3] = p_x[14] - v12[14];
            v22 = p_x[15] - v12[15];
            d1[4] = v22;
            v23 = v22 * d0[3] - d1[3] * d0[4];
            if ( v23 != 0.0 )
            {
              inva = 1.0 / v23;
              v24 = (d1[4] * v20 - v21 * d0[4]) * inva;
              v25 = (d1[4] * d0[1] - d1[1] * d0[4]) * inva;
              v26 = (d1[4] * d0[2] - d1[2] * d0[4]) * inva;
              temp.z = v26;
              v27 = v26 * temp.z + v25 * v25 + v24 * v24;
              if ( v27 != 0.0 )
              {
                v28 = 1.0 / sqrt(v27);
                v24 = v24 * v28;
                v25 = v25 * v28;
                temp.z = temp.z * v28;
              }
              tangents[0].z = temp.z;
              tangents[0].x = v24;
              tangents[0].y = v25;
              v29 = (v21 * d0[3] - d1[3] * v20) * inva;
              v30 = (d1[1] * d0[3] - d1[3] * d0[1]) * inva;
              v31 = (d1[2] * d0[3] - d1[3] * d0[2]) * inva;
              temp.z = v31;
              v32 = v31 * v31 + v30 * v30 + v29 * v29;
              if ( v32 != 0.0 )
              {
                v33 = 1.0 / sqrt(v32);
                v29 = v29 * v33;
                v30 = v30 * v33;
                temp.z = v31 * v33;
                v31 = v31 * v33;
              }
              tangents[1].x = v29;
              tangents[1].y = v30;
              tangents[1].z = v31;
              floatValue = r_showTextureVectors.internalVar->floatValue;
              v50 = tangents[0].x * floatValue;
              v51 = tangents[0].y * floatValue;
              v53 = floatValue * tangents[0].z + mid.z;
              tangents[0].z = v53;
              tangents[0].x = v50 + mid.x;
              tangents[0].y = v51 + mid.y;
              v37 = r_showTextureVectors.internalVar->floatValue;
              v48 = v37 * v29;
              v49 = v30 * v37;
              v52 = temp.z * v37 + mid.z;
              tangents[1].z = v52;
              tangents[1].x = v48 + mid.x;
              tangents[1].y = v49 + mid.y;
              qglColor3f(1.0, 0.0, 0.0);
              qglVertex3fv(&mid.x);
              qglVertex3fv(&tangents[0].x);
              qglColor3f(0.0, 1.0, 0.0);
              qglVertex3fv(&mid.x);
              qglVertex3fv(&tangents[1].x);
            }
            v4 += 3;
          }
          while ( v4 < geo->numIndexes );
          v2 = i;
        }
        qglEnd();
      }
      ++v2;
    }
  }
}

// FUNC: RB_ShowDominantTris
void __cdecl RB_ShowDominantTris(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int v2; // esi
  drawSurf_s *v3; // eax
  const srfTriangles_s *geo; // edi
  int v5; // ebp
  int v6; // ebx
  idDrawVert *verts; // edx
  dominantTri_s *v8; // ecx
  int v9; // eax
  double v10; // st7
  int v11; // eax
  double v12; // st7
  const float *p_x; // esi
  double v14; // st6
  float *v15; // ecx
  int v16; // [esp+0h] [ebp-38h]
  int i; // [esp+4h] [ebp-34h]
  float v18; // [esp+8h] [ebp-30h]
  float v19; // [esp+Ch] [ebp-2Ch]
  idVec3 mid; // [esp+14h] [ebp-24h] BYREF
  float v21; // [esp+28h] [ebp-10h]
  float v22; // [esp+34h] [ebp-4h]

  if ( r_showDominantTri.internalVar->integerValue )
  {
    GL_State(0);
    GL_DisableTexCoordState();
    qglPolygonOffset(-1.0, -2.0);
    qglEnable(0x2A02u);
    globalImages->BindNull(globalImages);
    v2 = 0;
    for ( i = 0; v2 < numDrawSurfs; i = v2 )
    {
      v3 = drawSurfs[v2];
      geo = v3->geo;
      v5 = 0;
      if ( v3->geo->verts && geo->dominantTris )
      {
        RB_SimpleSurfaceSetup(drawSurfs[v2]);
        qglColor3f(1.0, 1.0, 0.0);
        qglBegin(1u);
        v6 = 0;
        if ( geo->numVerts > 0 )
        {
          v16 = 0;
          do
          {
            verts = geo->verts;
            v8 = &geo->dominantTris[v16];
            v9 = v8->v2 << 6;
            v10 = *(float *)((char *)&verts->xyz.x + v9);
            v11 = (int)verts + v9;
            v12 = v10 + verts[v5].xyz.x;
            p_x = &verts[v5].xyz.x;
            v14 = *(float *)(v11 + 4) + verts[v5].xyz.y;
            v15 = &verts[v8->v3].xyz.x;
            v21 = *(float *)(v11 + 8) + verts[v5].xyz.z;
            v18 = v12 + *v15;
            v19 = v14 + v15[1];
            v22 = (v21 + v15[2]) * 0.33333334;
            mid.z = v22;
            mid.x = v18 * 0.33333334;
            mid.y = v19 * 0.33333334;
            qglVertex3fv(&mid.x);
            qglVertex3fv(p_x);
            ++v16;
            ++v6;
            ++v5;
          }
          while ( v6 < geo->numVerts );
          v2 = i;
        }
        qglEnd();
      }
      ++v2;
    }
    qglDisable(0x2A02u);
  }
}

// FUNC: RB_ShowEdges
void __cdecl RB_ShowEdges(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int v2; // eax
  const drawSurf_s *v3; // eax
  const srfTriangles_s *geo; // esi
  int v5; // ebp
  int v6; // ebx
  int v7; // ecx
  int *indexes; // eax
  int v9; // edi
  int numIndexes; // eax
  int v11; // ecx
  int *v12; // esi
  int m; // eax
  int v14; // edx
  bool v15; // zf
  int v16; // edi
  int v17; // ebx
  int v18; // ebp
  silEdge_t *v19; // esi
  idDrawVert *ac; // [esp+0h] [ebp-1Ch]
  const srfTriangles_s *tri; // [esp+4h] [ebp-18h]
  int k; // [esp+8h] [ebp-14h]
  int j; // [esp+Ch] [ebp-10h]
  int v24; // [esp+10h] [ebp-Ch]
  int i2; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  if ( r_showEdges.internalVar->integerValue )
  {
    GL_State(0x10000);
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB71u);
    v2 = 0;
    for ( i = 0; i < numDrawSurfs; ++i )
    {
      v3 = drawSurfs[v2];
      geo = v3->geo;
      tri = v3->geo;
      ac = v3->geo->verts;
      if ( ac )
      {
        RB_SimpleSurfaceSetup(v3);
        qglColor3f(1.0, 1.0, 0.0);
        qglBegin(1u);
        v5 = 0;
        for ( j = 0; v5 < geo->numIndexes; j = v5 )
        {
          v6 = 0;
          k = 0;
          do
          {
            if ( v6 == 2 )
              v7 = 0;
            else
              v7 = v6 + 1;
            indexes = geo->indexes;
            v9 = indexes[v6 + v5];
            i2 = indexes[v5 + v7];
            numIndexes = geo->numIndexes;
            v11 = 0;
            v24 = numIndexes;
            if ( numIndexes > 0 )
            {
              v12 = geo->indexes;
              do
              {
                for ( m = 0; m < 3; ++m )
                {
                  if ( m == 2 )
                    v14 = 0;
                  else
                    v14 = m + 1;
                  if ( v12[m + v11] == i2 && v12[v11 + v14] == v9 )
                    break;
                }
                v15 = m == 3;
                numIndexes = v24;
                if ( !v15 )
                  break;
                v11 += 3;
              }
              while ( v11 < v24 );
              geo = tri;
              v6 = k;
              v5 = j;
            }
            if ( v11 == numIndexes )
            {
              qglVertex3fv(&ac[v9].xyz.x);
              qglVertex3fv(&ac[i2].xyz.x);
            }
            k = ++v6;
          }
          while ( v6 < 3 );
          v5 += 3;
        }
        qglEnd();
        if ( geo->silEdges )
        {
          v16 = geo->numIndexes / 3;
          qglColor3f(1.0, 0.0, 0.0);
          qglBegin(1u);
          v17 = 0;
          if ( geo->numSilEdges > 0 )
          {
            v18 = 0;
            while ( 1 )
            {
              v19 = &geo->silEdges[v18];
              if ( v19->p1 == v16 || v19->p2 == v16 )
              {
                qglVertex3fv(&ac[v19->v1].xyz.x);
                qglVertex3fv(&ac[v19->v2].xyz.x);
              }
              ++v17;
              ++v18;
              if ( v17 >= tri->numSilEdges )
                break;
              geo = tri;
            }
          }
          qglEnd();
        }
      }
      v2 = i + 1;
    }
    qglEnable(0xB71u);
  }
}

// FUNC: void __cdecl RB_ShowLights(void)
void __cdecl RB_ShowLights()
{
  viewLight_s *viewLights; // ebx
  int i; // ebp
  idRenderLightLocal *lightDef; // esi
  const srfTriangles_s *frustumTris; // edi
  idRenderWorldLocal *renderWorld; // eax
  int num; // edx
  idList<idRenderLightLocal *> *p_lightDefs; // eax
  int v7; // ecx
  idRenderLightLocal **list; // eax
  int v9; // edx

  if ( r_showLights.internalVar->integerValue )
  {
    RB_SimpleWorldSetup();
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_Cull(2);
    qglDisable(0xB71u);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "volumes: ");
    viewLights = backEnd.viewDef->viewLights;
    for ( i = 0; viewLights; viewLights = viewLights->next )
    {
      lightDef = viewLights->lightDef;
      frustumTris = lightDef->frustumTris;
      ++i;
      if ( r_showLights.internalVar->integerValue >= 2 )
      {
        GL_State(357);
        if ( lightDef->parms.noShadows )
          qglColor4f(1.0, 0.0, 0.0, 0.25);
        else
          qglColor4f(0.0, 0.0, 1.0, 0.25);
        qglEnable(0xB71u);
        RB_RenderTriangleSurface(frustumTris);
      }
      if ( r_showLights.internalVar->integerValue >= 3 )
      {
        GL_State(8448);
        qglDisable(0xB71u);
        qglColor3f(1.0, 1.0, 1.0);
        RB_RenderTriangleSurface(frustumTris);
      }
      renderWorld = backEnd.viewDef->renderWorld;
      num = renderWorld->lightDefs.num;
      p_lightDefs = &renderWorld->lightDefs;
      v7 = 0;
      if ( num <= 0 )
      {
LABEL_14:
        v7 = -1;
      }
      else
      {
        list = p_lightDefs->list;
        while ( *list != viewLights->lightDef )
        {
          ++v7;
          ++list;
          if ( v7 >= num )
            goto LABEL_14;
        }
      }
      v9 = *(_DWORD *)common.type;
      if ( viewLights->viewInsideLight )
        (*(void (__cdecl **)(netadrtype_t, const char *, int))(v9 + 124))(common.type, "[%i] ", v7);
      else
        (*(void (__cdecl **)(netadrtype_t, const char *, int))(v9 + 124))(common.type, "%i ", v7);
    }
    qglEnable(0xB71u);
    qglDisable(0x2A02u);
    qglDepthRange(0.0, 1.0);
    GL_State(0x10000);
    GL_Cull(0);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, " = %i total\n", i);
  }
}

// FUNC: void __cdecl RB_ShowLightPortals(void)
void __cdecl RB_ShowLightPortals()
{
  viewLight_s *i; // edi
  idRenderLightLocal *lightDef; // eax
  const srfTriangles_s *frustumTris; // esi

  if ( r_showLightPortals.internalVar->integerValue )
  {
    RB_SimpleWorldSetup();
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    GL_Cull(2);
    qglDisable(0xB71u);
    for ( i = backEnd.viewDef->viewLights; i; i = i->next )
    {
      lightDef = i->lightDef;
      if ( lightDef->numPortalsCrossed > 1 )
      {
        frustumTris = lightDef->frustumTris;
        GL_State(8448);
        qglDisable(0xB71u);
        qglColor3f(1.0, 1.0, 1.0);
        RB_RenderTriangleSurface(frustumTris);
      }
    }
    qglEnable(0xB71u);
    qglDisable(0x2A02u);
    qglDepthRange(0.0, 1.0);
    GL_State(0x10000);
    GL_Cull(0);
  }
}

// FUNC: void __cdecl RB_ShowPortals(void)
void __cdecl RB_ShowPortals()
{
  if ( r_showPortals.internalVar->integerValue )
  {
    if ( backEnd.viewDef->renderView.viewID >= 0 )
    {
      RB_SimpleWorldSetup();
      globalImages->BindNull(globalImages);
      qglDisable(0xB71u);
      GL_State(0x10000);
      idRenderWorldLocal::ShowPortals(backEnd.viewDef->renderWorld);
      qglEnable(0xB71u);
    }
  }
}

// FUNC: RB_DrawText
void __usercall RB_DrawText(
        const char *text@<eax>,
        const idMat3 *viewAxis@<ebx>,
        const idVec3 *origin,
        float scale,
        const idVec4 *color,
        int align)
{
  int v7; // eax
  int v8; // ecx
  const char *v9; // edi
  int v10; // edx
  double v11; // st7
  double v12; // st6
  const char *v13; // edx
  bool v14; // zf
  int v15; // ecx
  double v16; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st7
  unsigned int v21; // ecx
  unsigned int v22; // esi
  int v23; // edx
  const int *v24; // edi
  int v25; // ebp
  int *v26; // esi
  double v27; // st7
  double v28; // st6
  int v29; // ecx
  double v30; // st7
  double v31; // st6
  double v32; // st7
  double v33; // st6
  bool v34; // cc
  float org; // [esp+4h] [ebp-12Ch]
  float org_4; // [esp+8h] [ebp-128h]
  float org_8; // [esp+Ch] [ebp-124h]
  float textLen; // [esp+10h] [ebp-120h]
  const char *v39; // [esp+14h] [ebp-11Ch]
  int line; // [esp+18h] [ebp-118h]
  int len; // [esp+1Ch] [ebp-114h]
  float v42; // [esp+20h] [ebp-110h]
  float v43; // [esp+24h] [ebp-10Ch]
  float v44; // [esp+28h] [ebp-108h]
  int v45; // [esp+2Ch] [ebp-104h]
  int num; // [esp+30h] [ebp-100h]
  int i; // [esp+34h] [ebp-FCh]
  float v48; // [esp+38h] [ebp-F8h]
  float v49; // [esp+3Ch] [ebp-F4h]
  float v50; // [esp+40h] [ebp-F0h]
  float spacing; // [esp+50h] [ebp-E0h]
  float y; // [esp+58h] [ebp-D8h]
  float v53; // [esp+5Ch] [ebp-D4h]
  float v54; // [esp+60h] [ebp-D0h]
  float v55; // [esp+64h] [ebp-CCh]
  float v56; // [esp+68h] [ebp-C8h]
  int j; // [esp+6Ch] [ebp-C4h]
  float z; // [esp+78h] [ebp-B8h]
  float v59; // [esp+88h] [ebp-A8h]
  float v60; // [esp+8Ch] [ebp-A4h]
  float v61; // [esp+98h] [ebp-98h]
  float v62; // [esp+9Ch] [ebp-94h]
  float v63; // [esp+A4h] [ebp-8Ch]
  float v64; // [esp+A8h] [ebp-88h]
  idVec3 p1; // [esp+ACh] [ebp-84h] BYREF
  float v66; // [esp+BCh] [ebp-74h]
  float v67; // [esp+C0h] [ebp-70h]
  idVec3 p2; // [esp+C4h] [ebp-6Ch] BYREF
  float v69; // [esp+D4h] [ebp-5Ch]
  float v70; // [esp+D8h] [ebp-58h]
  float v71; // [esp+E0h] [ebp-50h]
  float v72; // [esp+E4h] [ebp-4Ch]
  float v73; // [esp+ECh] [ebp-44h]
  float v74; // [esp+F0h] [ebp-40h]
  float v75; // [esp+F4h] [ebp-3Ch]
  float v76; // [esp+F8h] [ebp-38h]
  float v77; // [esp+104h] [ebp-2Ch]
  float v78; // [esp+108h] [ebp-28h]
  float v79; // [esp+114h] [ebp-1Ch]
  float v80; // [esp+120h] [ebp-10h]
  float v81; // [esp+12Ch] [ebp-4h]

  if ( text && *text )
  {
    qglBegin(1u);
    qglColor3fv(&color->x);
    line = *text == 10;
    v7 = strlen(text);
    v8 = 0;
    len = v7;
    i = 0;
    if ( v7 > 0 )
    {
      v9 = text;
      v10 = 1 - (_DWORD)text;
      v39 = text;
      for ( j = 1 - (_DWORD)text; ; v10 = j )
      {
        if ( !v8 || *v9 == 10 )
        {
          v11 = (double)line * scale * 36.0;
          v12 = v11 * viewAxis->mat[2].x;
          v66 = v11 * viewAxis->mat[2].y;
          v67 = v11 * viewAxis->mat[2].z;
          v42 = origin->x - v12;
          v43 = origin->y - v66;
          org = v42;
          org_4 = v43;
          v44 = origin->z - v67;
          org_8 = v44;
          if ( align )
          {
            v13 = &v9[v10];
            v14 = v13 == (const char *)v7;
            textLen = 0.0;
            v15 = 1;
            if ( (int)v13 <= v7 )
            {
              while ( !v14 && v9[v15] != 10 )
              {
                ++v13;
                ++v15;
                v14 = v13 == (const char *)v7;
                if ( (int)v13 > v7 )
                  goto LABEL_15;
              }
              textLen = RB_DrawTextLength(v9, scale, v15);
              v9 = v39;
              v7 = len;
            }
LABEL_15:
            v16 = textLen;
            if ( align == 2 )
            {
              v17 = v16 * viewAxis->mat[1].x;
              v18 = textLen * viewAxis->mat[1].y;
              v79 = textLen * viewAxis->mat[1].z;
              org = v17 + v42;
              org_4 = v18 + v43;
              v19 = v79;
            }
            else
            {
              v20 = v16 * 0.5;
              v63 = v20 * viewAxis->mat[1].y;
              v64 = v20 * viewAxis->mat[1].z;
              org = v20 * viewAxis->mat[1].x + v42;
              org_4 = v63 + v43;
              v19 = v64;
            }
            org_8 = v19 + v44;
          }
          ++line;
        }
        v21 = *v9 - 32;
        if ( v21 <= 0x5F )
        {
          v22 = v21;
          v23 = 2 * simplex[v21][0];
          spacing = (float)simplex[v21][1];
          num = v23;
          if ( v23 > 0 )
          {
            v24 = &simplex[v22][2];
            v25 = 0;
            v26 = (int *)&simplex[v22][3];
            do
            {
              v45 = *v24;
              if ( *v24 >= 0 )
              {
                v27 = (double)*v26 * scale;
                z = viewAxis->mat[2].z;
                v24 += 2;
                v59 = viewAxis->mat[2].x * v27;
                v26 += 2;
                v25 += 2;
                v60 = viewAxis->mat[2].y * v27;
                v54 = -viewAxis->mat[1].x;
                v55 = -viewAxis->mat[1].y;
                v56 = -viewAxis->mat[1].z;
                v28 = (double)v45 * scale;
                v73 = v55 * v28;
                v74 = v56 * v28;
                v77 = v73 + org_4;
                v78 = v74 + org_8;
                v80 = v78 + v27 * z;
                p1.z = v80;
                v29 = *v24;
                p1.x = v54 * v28 + org + v59;
                p1.y = v77 + v60;
                if ( v29 >= 0 )
                {
                  v30 = (double)*v26 * scale;
                  y = viewAxis->mat[2].y;
                  v53 = viewAxis->mat[2].z;
                  v75 = viewAxis->mat[2].x * v30;
                  v76 = y * v30;
                  v48 = -viewAxis->mat[1].x;
                  v49 = -viewAxis->mat[1].y;
                  v50 = -viewAxis->mat[1].z;
                  v31 = (double)v29 * scale;
                  v69 = v49 * v31;
                  v70 = v50 * v31;
                  v61 = v69 + org_4;
                  v62 = v70 + org_8;
                  v81 = v62 + v30 * v53;
                  p2.z = v81;
                  p2.x = v48 * v31 + org + v75;
                  p2.y = v61 + v76;
                  qglVertex3fv(&p1.x);
                  qglVertex3fv(&p2.x);
                }
                else
                {
                  ++v26;
                  ++v24;
                  ++v25;
                }
                v23 = num;
                v7 = len;
              }
              else
              {
                ++v26;
                ++v24;
                ++v25;
              }
            }
            while ( v25 < v23 );
            v9 = v39;
          }
          v32 = spacing * scale;
          v33 = v32 * viewAxis->mat[1].x;
          v71 = v32 * viewAxis->mat[1].y;
          v72 = v32 * viewAxis->mat[1].z;
          org = org - v33;
          org_4 = org_4 - v71;
          org_8 = org_8 - v72;
        }
        v8 = i + 1;
        ++v9;
        v34 = ++i < v7;
        v39 = v9;
        if ( !v34 )
          break;
      }
    }
    qglEnd();
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ShowDebugText(void)
void __thiscall idRenderWorldLocal::ShowDebugText(idRenderWorldLocal *this)
{
  int integerValue; // eax
  int v3; // ebp
  int v4; // edi
  debugText_s *v5; // eax
  int v6; // ebp
  int v7; // edi
  debugText_s *v8; // eax
  float v9; // [esp+0h] [ebp-Ch]
  int width; // [esp+8h] [ebp-4h]

  if ( this->debugText.num )
  {
    RB_SimpleWorldSetup();
    globalImages->BindNull(globalImages);
    integerValue = r_debugLineWidth.internalVar->integerValue;
    width = integerValue;
    if ( integerValue >= 1 )
    {
      if ( integerValue > 10 )
        width = 10;
    }
    else
    {
      width = 1;
    }
    GL_State(0x2000);
    v9 = (float)width;
    qglLineWidth(v9);
    if ( !r_debugLineDepthTest.internalVar->integerValue )
      qglDisable(0xB71u);
    v3 = 0;
    if ( this->debugText.num > 0 )
    {
      v4 = 0;
      do
      {
        v5 = &this->debugText.list[v4];
        if ( !v5->depthTest )
          RB_DrawText(v5->text.data, &v5->viewAxis, &v5->origin, v5->scale, &v5->color, v5->align);
        ++v3;
        ++v4;
      }
      while ( v3 < this->debugText.num );
    }
    if ( !r_debugLineDepthTest.internalVar->integerValue )
      qglEnable(0xB71u);
    v6 = 0;
    if ( this->debugText.num > 0 )
    {
      v7 = 0;
      do
      {
        v8 = &this->debugText.list[v7];
        if ( v8->depthTest )
          RB_DrawText(v8->text.data, &v8->viewAxis, &v8->origin, v8->scale, &v8->color, v8->align);
        ++v6;
        ++v7;
      }
      while ( v6 < this->debugText.num );
    }
    qglLineWidth(1.0);
    GL_State(0x10000);
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ShowDebugPolygons(void)
void __thiscall idRenderWorldLocal::ShowDebugPolygons(idRenderWorldLocal *this)
{
  idRenderWorldLocal *v1; // ebx
  int v2; // ebp
  debugPolygon_s *v3; // esi
  int v4; // edi
  int v5; // ebx
  int i; // [esp+18h] [ebp-8h]

  v1 = this;
  v2 = 0;
  if ( this->debugPolys.num )
  {
    RB_SimpleWorldSetup();
    globalImages->BindNull(globalImages);
    qglDisable(0xDE1u);
    qglDisable(0xB90u);
    qglEnable(0xB71u);
    if ( r_debugPolygonFilled.internalVar->integerValue )
    {
      GL_State(357);
      GL_PolygonOffsetState(1, -1.0, -2.0);
    }
    else
    {
      GL_State(0x2000);
      GL_PolygonOffsetState(0, 0.0, 0.0);
      qglPolygonOffset(-1.0, -2.0);
      qglEnable(0x2A02u);
    }
    GL_Cull(2);
    for ( i = 0; i < v1->debugPolys.num; ++i )
    {
      v3 = &v1->debugPolys.list[v2];
      qglColor4fv(&v3->rgb.x);
      if ( v3->depthTest )
        qglEnable(0xB71u);
      else
        qglDisable(0xB71u);
      qglBegin(9u);
      v4 = 0;
      if ( v3->winding.numPoints > 0 )
      {
        v5 = 0;
        do
        {
          qglVertex3fv(&v3->winding.p[v5].x);
          ++v4;
          ++v5;
        }
        while ( v4 < v3->winding.numPoints );
        v1 = this;
      }
      qglEnd();
      ++v2;
    }
    GL_State(0x10000);
    qglEnable(0xB71u);
    GL_Cull(2884);
    if ( r_debugPolygonFilled.internalVar->integerValue )
      GL_PolygonOffsetState(0, 0.0, 0.0);
    else
      qglDisable(0x2A02u);
    qglDepthRange(0.0, 1.0);
    GL_State(0x10000);
  }
}

// FUNC: void __cdecl RB_TestGamma(void)
None

// FUNC: RB_TestGammaBias
None

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ShowDebugLines(void)
void __thiscall idRenderWorldLocal::ShowDebugLines(idRenderWorldLocal *this)
{
  int v2; // ebx
  int v3; // ebp
  debugLine_s *v4; // esi
  int v5; // ebx
  int v6; // ebp
  debugLine_s *v7; // esi

  if ( this->debugLines.num )
  {
    RB_SimpleWorldSetup();
    globalImages->BindNull(globalImages);
    GL_State(0x2000);
    qglLineWidth(4.0);
    if ( !r_debugLineDepthTest.internalVar->integerValue )
      qglDisable(0xB71u);
    qglLineWidth(1.0);
    qglBegin(1u);
    v2 = 0;
    if ( this->debugLines.num > 0 )
    {
      v3 = 0;
      do
      {
        v4 = &this->debugLines.list[v3];
        if ( !v4->depthTest )
        {
          qglColor3fv(&this->debugLines.list[v3].rgb.x);
          qglVertex3fv(&v4->start.x);
          qglVertex3fv(&v4->end.x);
        }
        ++v2;
        ++v3;
      }
      while ( v2 < this->debugLines.num );
    }
    qglEnd();
    qglLineWidth(4.0);
    if ( !r_debugLineDepthTest.internalVar->integerValue )
      qglEnable(0xB71u);
    qglBegin(1u);
    v5 = 0;
    if ( this->debugLines.num > 0 )
    {
      v6 = 0;
      do
      {
        v7 = &this->debugLines.list[v6];
        qglColor4fv(&v7->rgb.x);
        qglVertex3fv(&v7->start.x);
        qglVertex3fv(&v7->end.x);
        ++v5;
        ++v6;
      }
      while ( v5 < this->debugLines.num );
    }
    qglEnd();
    qglLineWidth(1.0);
    GL_State(0x10000);
  }
}

// FUNC: void __cdecl RB_UpdateDebugCvars(void)
void __cdecl RB_UpdateDebugCvars()
{
  idList<triangle_s> *p_spherePolys; // esi

  if ( (r_debugSphereSubdivision.internalVar->flags & 0x40000) != 0 )
  {
    p_spherePolys = &tr.primaryWorld->spherePolys;
    if ( tr.primaryWorld->spherePolys.list )
      Memory::Free(tr.primaryWorld->spherePolys.list);
    p_spherePolys->list = 0;
    p_spherePolys->num = 0;
    p_spherePolys->size = 0;
    BYTE2(r_debugSphereSubdivision.internalVar->flags) &= ~4u;
  }
}

// FUNC: RB_ShowTris
void __cdecl RB_ShowTris(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  if ( r_showTris.internalVar->integerValue
    || (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x2000) )
  {
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xDE1u);
    qglDisable(0xB90u);
    qglColor3f(1.0, 1.0, 1.0);
    GL_State(0x2000);
    if ( r_showTris.internalVar->integerValue == 1 )
    {
      qglPolygonOffset(-1.0, -2.0);
      qglEnable(0x2A02u);
    }
    else
    {
      if ( r_showTris.internalVar->integerValue == 3 || r_showTris.internalVar->integerValue == 5 )
        GL_Cull(2);
      else
        GL_Cull(0);
      qglDisable(0xB71u);
    }
    RB_RenderDrawSurfListWithFunction(drawSurfs, numDrawSurfs, RB_T_ShowTriRenderTriangleSurface);
    qglEnable(0xB71u);
    qglDisable(0x2A02u);
    qglDepthRange(0.0, 1.0);
    GL_State(0x10000);
    GL_Cull(0);
  }
}

// FUNC: RB_ShowNormals
void __cdecl RB_ShowNormals(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int v2; // edi
  int j; // ebp
  const drawSurf_s *v4; // esi
  const srfTriangles_s *geo; // esi
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  drawSurf_s *v9; // ebp
  const srfTriangles_s *v10; // edi
  int v11; // esi
  float *p_x; // eax
  double v13; // st7
  double v14; // st6
  double v15; // st5
  idMat3 *p_viewaxis; // ebx
  const char *v17; // eax
  int k; // esi
  int *indexes; // edx
  idDrawVert *verts; // ebx
  int v21; // eax
  double v22; // st7
  float *v23; // eax
  float *v24; // ecx
  double v25; // st6
  double v26; // st5
  double v27; // st4
  double v28; // st3
  float *v29; // eax
  double v30; // st5
  double v31; // st4
  idMat3 *v32; // ebx
  const char *v33; // eax
  const float *modelMatrix; // [esp-1Ch] [ebp-A0h]
  const float *v35; // [esp-1Ch] [ebp-A0h]
  float size; // [esp+0h] [ebp-84h]
  int sizea; // [esp+0h] [ebp-84h]
  bool showNumbers; // [esp+7h] [ebp-7Dh]
  idVec3 end; // [esp+8h] [ebp-7Ch] BYREF
  int i; // [esp+14h] [ebp-70h]
  float v41; // [esp+18h] [ebp-6Ch]
  float v42; // [esp+1Ch] [ebp-68h]
  float v43; // [esp+20h] [ebp-64h]
  idVec3 in; // [esp+24h] [ebp-60h] BYREF
  idVec3 v45; // [esp+30h] [ebp-54h] BYREF
  float v46; // [esp+40h] [ebp-44h]
  float v47; // [esp+44h] [ebp-40h]
  idVec3 pos; // [esp+48h] [ebp-3Ch] BYREF
  float v49; // [esp+5Ch] [ebp-28h]
  float v50; // [esp+60h] [ebp-24h]
  float v51; // [esp+74h] [ebp-10h]
  float v52; // [esp+80h] [ebp-4h]

  if ( r_showNormals.internalVar->floatValue != 0.0 )
  {
    GL_State(0x2000);
    GL_DisableTexCoordState();
    globalImages->BindNull(globalImages);
    qglDisable(0xB90u);
    if ( r_debugLineDepthTest.internalVar->integerValue )
      qglEnable(0xB71u);
    else
      qglDisable(0xB71u);
    size = r_showNormals.internalVar->floatValue;
    if ( size >= 0.0 )
    {
      showNumbers = 0;
    }
    else
    {
      showNumbers = 1;
      size = -size;
    }
    v2 = numDrawSurfs;
    for ( j = 0; j < v2; ++j )
    {
      v4 = drawSurfs[j];
      RB_SimpleSurfaceSetup(v4);
      geo = v4->geo;
      if ( geo->verts )
      {
        qglBegin(1u);
        v6 = 0;
        if ( geo->numVerts > 0 )
        {
          v7 = 0;
          do
          {
            qglColor3f(0.0, 0.0, 1.0);
            qglVertex3fv(&geo->verts[v7].xyz.x);
            end.x = size * geo->verts[v7].normal.x + geo->verts[v7].xyz.x;
            end.y = size * geo->verts[v7].normal.y + geo->verts[v7].xyz.y;
            end.z = size * geo->verts[v7].normal.z + geo->verts[v7].xyz.z;
            qglVertex3fv(&end.x);
            qglColor3f(1.0, 0.0, 0.0);
            qglVertex3fv(&geo->verts[v7].xyz.x);
            end.x = size * geo->verts[v7].tangents[0].x + geo->verts[v7].xyz.x;
            end.y = size * geo->verts[v7].tangents[0].y + geo->verts[v7].xyz.y;
            end.z = size * geo->verts[v7].tangents[0].z + geo->verts[v7].xyz.z;
            qglVertex3fv(&end.x);
            qglColor3f(0.0, 1.0, 0.0);
            qglVertex3fv(&geo->verts[v7].xyz.x);
            end.x = size * geo->verts[v7].tangents[1].x + geo->verts[v7].xyz.x;
            end.y = size * geo->verts[v7].tangents[1].y + geo->verts[v7].xyz.y;
            end.z = size * geo->verts[v7].tangents[1].z + geo->verts[v7].xyz.z;
            qglVertex3fv(&end.x);
            ++v6;
            ++v7;
          }
          while ( v6 < geo->numVerts );
          v2 = numDrawSurfs;
        }
        qglEnd();
      }
    }
    if ( showNumbers )
    {
      RB_SimpleWorldSetup();
      v8 = 0;
      i = 0;
      if ( v2 > 0 )
      {
        do
        {
          v9 = drawSurfs[v8];
          v10 = v9->geo;
          v11 = 0;
          if ( v9->geo->verts )
          {
            if ( v10->numVerts > 0 )
            {
              sizea = 0;
              do
              {
                p_x = &v10->verts[sizea].xyz.x;
                v13 = p_x[4] * 0.2;
                v14 = p_x[5] * 0.2;
                v49 = p_x[6] * 0.2;
                v15 = p_x[8] + *p_x;
                v46 = p_x[1] + p_x[9];
                modelMatrix = v9->space->modelMatrix;
                v47 = p_x[2] + p_x[10];
                in.x = v15 + v13;
                in.y = v46 + v14;
                in.z = v47 + v49;
                R_LocalPointToGlobal(modelMatrix, &in, &pos);
                p_viewaxis = &backEnd.viewDef->renderView.viewaxis;
                v17 = va("%d", v11);
                RB_DrawText(v17, p_viewaxis, &pos, 0.0099999998, &colorWhite, 1);
                ++sizea;
                ++v11;
              }
              while ( v11 < v10->numVerts );
            }
            for ( k = 0; k < v10->numIndexes; k += 3 )
            {
              indexes = v10->indexes;
              verts = v10->verts;
              v21 = indexes[k] << 6;
              v22 = *(float *)((char *)&verts->normal.x + v21);
              v23 = (float *)((char *)&verts->xyz.x + v21);
              v24 = &verts[indexes[k + 1]].xyz.x;
              v25 = v23[5] * 0.2;
              v52 = v23[6] * 0.2;
              v26 = *v23 + *v24;
              v27 = v24[1] + v23[1];
              v28 = v24[2] + v23[2];
              v29 = &verts[indexes[k + 2]].xyz.x;
              v51 = v28;
              v50 = v26 + *v29;
              v30 = v27 + v29[1];
              v31 = v51 + v29[2];
              v35 = v9->space->modelMatrix;
              v41 = v50 * 0.33333334;
              v42 = v30 * 0.33333334;
              v43 = v31 * 0.33333334;
              v45.x = v41 + v22 * 0.2;
              v45.y = v42 + v25;
              v45.z = v43 + v52;
              R_LocalPointToGlobal(v35, &v45, &pos);
              v32 = &backEnd.viewDef->renderView.viewaxis;
              v33 = va("%d", k / 3);
              RB_DrawText(v33, v32, &pos, 0.0099999998, &colorCyan, 1);
            }
          }
          v8 = ++i;
        }
        while ( i < numDrawSurfs );
      }
    }
    qglEnable(0xB90u);
  }
}

// FUNC: void __cdecl RB_ShowTriangleTangents(struct drawSurf_s * *,int)
void __cdecl RB_ShowTriangleTangents(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  const drawSurf_s *v2; // esi
  int v3; // ebx
  drawSurf_s *v4; // esi
  srfTriangles_s *geo; // edi
  localTrace_s *v6; // eax
  const srfTriangles_s *v7; // edi
  int i; // ebp
  int v9; // ebx
  idDrawVert *verts; // eax
  float y; // ecx
  double v12; // st7
  float z; // edx
  idDrawVert *v14; // eax
  double v15; // st6
  idDrawVert *v16; // eax
  float v17; // ecx
  double v18; // st7
  float v19; // edx
  idDrawVert *v20; // eax
  double v21; // st6
  idDrawVert *v22; // eax
  float v23; // ecx
  double v24; // st7
  float v25; // edx
  idDrawVert *v26; // eax
  double v27; // st6
  idRenderWorldLocal_vtbl *v28; // esi
  char *v29; // eax
  int j; // esi
  idMat3 *p_viewaxis; // [esp-1Ch] [ebp-1BCh]
  idVec3 end; // [esp+4h] [ebp-19Ch] BYREF
  const drawSurf_s *bestDrawSurf; // [esp+10h] [ebp-190h]
  float v34; // [esp+18h] [ebp-188h]
  float v35; // [esp+1Ch] [ebp-184h]
  idVec3 start; // [esp+20h] [ebp-180h] BYREF
  idVec3 localStart; // [esp+2Ch] [ebp-174h] BYREF
  float v38; // [esp+3Ch] [ebp-164h]
  float v39; // [esp+40h] [ebp-160h]
  float v40; // [esp+48h] [ebp-158h]
  float v41; // [esp+4Ch] [ebp-154h]
  idVec3 localEnd; // [esp+50h] [ebp-150h] BYREF
  float v43; // [esp+64h] [ebp-13Ch]
  idVec3 globalXYZ; // [esp+68h] [ebp-138h] BYREF
  float v45; // [esp+7Ch] [ebp-124h]
  float v46; // [esp+88h] [ebp-118h]
  localTrace_s best; // [esp+8Ch] [ebp-114h] BYREF
  localTrace_s hit; // [esp+E8h] [ebp-B8h] BYREF
  localTrace_s result; // [esp+144h] [ebp-5Ch] BYREF

  if ( r_showTriangleTangents.internalVar->integerValue )
  {
    start = backEnd.viewDef->renderView.vieworg;
    end = backEnd.viewDef->renderView.viewaxis.mat[0];
    v34 = end.y * 4000.0;
    v2 = 0;
    v3 = 0;
    v35 = end.z * 4000.0;
    best.fraction = 1.0;
    bestDrawSurf = 0;
    localStart.z = v35 + start.z;
    end.z = localStart.z;
    end.x = end.x * 4000.0 + start.x;
    end.y = v34 + start.y;
    if ( numDrawSurfs > 0 )
    {
      do
      {
        v4 = drawSurfs[v3];
        geo = (srfTriangles_s *)v4->geo;
        if ( v4->geo )
        {
          if ( geo->verts )
          {
            R_GlobalPointToLocal(v4->space->modelMatrix, &start, &localStart);
            R_GlobalPointToLocal(v4->space->modelMatrix, &end, &localEnd);
            if ( idBounds::LineIntersection(&geo->bounds, &localStart, &localEnd) )
            {
              v6 = R_LocalTrace(&result, &localStart, &localEnd, 0.0, geo, v4->material);
              localTrace_s::operator=(&hit, v6);
              if ( hit.fraction < (double)best.fraction )
              {
                localTrace_s::operator=(&best, &hit);
                bestDrawSurf = v4;
              }
            }
          }
        }
        ++v3;
      }
      while ( v3 < numDrawSurfs );
      v2 = bestDrawSurf;
    }
    (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, 1);
    if ( best.fraction < 1.0 )
    {
      GL_State(0x2000);
      qglDisableClientState(0x8078u);
      globalImages->BindNull(globalImages);
      qglDisable(0xB90u);
      if ( r_debugLineDepthTest.internalVar->integerValue )
        qglEnable(0xB71u);
      else
        qglDisable(0xB71u);
      qglLoadMatrixf(v2->space->modelViewMatrix);
      v7 = v2->geo;
      qglBegin(1u);
      for ( i = 0; i < 3; ++i )
      {
        v9 = best.indexes[i];
        qglColor3f(0.0, 0.0, 1.0);
        qglVertex3fv(&v7->verts[v9].xyz.x);
        verts = v7->verts;
        y = verts[v9].normal.y;
        v12 = verts[v9].normal.x + verts[v9].xyz.x;
        z = verts[v9].normal.z;
        v14 = &verts[v9];
        v34 = y;
        v15 = y + v14->xyz.y;
        v35 = z;
        v46 = z + v14->xyz.z;
        end.z = v46;
        end.x = v12;
        end.y = v15;
        qglVertex3fv(&end.x);
        qglColor3f(1.0, 0.0, 0.0);
        qglVertex3fv(&v7->verts[v9].xyz.x);
        v16 = v7->verts;
        v17 = v16[v9].tangents[0].y;
        v18 = v16[v9].tangents[0].x + v16[v9].xyz.x;
        v19 = v16[v9].tangents[0].z;
        v20 = &v16[v9];
        v38 = v17;
        v21 = v17 + v20->xyz.y;
        v39 = v19;
        v43 = v19 + v20->xyz.z;
        end.z = v43;
        end.x = v18;
        end.y = v21;
        qglVertex3fv(&end.x);
        qglColor3f(0.0, 1.0, 0.0);
        qglVertex3fv(&v7->verts[v9].xyz.x);
        v22 = v7->verts;
        v23 = v22[v9].tangents[1].y;
        v24 = v22[v9].tangents[1].x + v22[v9].xyz.x;
        v25 = v22[v9].tangents[1].z;
        v26 = &v22[v9];
        v40 = v23;
        v27 = v23 + v26->xyz.y;
        v41 = v25;
        v45 = v25 + v26->xyz.z;
        end.x = v24;
        end.z = v45;
        end.y = v27;
        qglVertex3fv(&end.x);
        if ( tr.primaryWorld )
        {
          R_LocalPointToGlobal(bestDrawSurf->space->modelMatrix, &v7->verts[v9].xyz, &globalXYZ);
          v28 = tr.primaryWorld->__vftable;
          p_viewaxis = &backEnd.viewDef->renderView.viewaxis;
          v29 = va("%d", v9);
          ((void (__thiscall *)(idRenderWorldLocal *, char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))v28->DrawTextA)(
            tr.primaryWorld,
            v29,
            &globalXYZ,
            1017370378,
            &colorGreen,
            p_viewaxis,
            1,
            0,
            0);
        }
      }
      qglEnd();
      if ( r_showTriangleTangents.internalVar->integerValue == 2 )
      {
        qglColor3f(1.0, 1.0, 1.0);
        qglBegin(2u);
        for ( j = 0; j < 3; ++j )
          qglVertex3fv(&v7->verts[best.indexes[j]].xyz.x);
        qglEnd();
      }
      qglEnable(0xB90u);
    }
  }
}

// FUNC: void __cdecl RB_RenderDebugTools(struct drawSurf_s * *,int)
void __cdecl RB_RenderDebugTools(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  idRenderWorldLocal *primaryWorld; // esi

  if ( tr.testStandaloneVideo )
    tr.testStandaloneVideo->Draw(tr.testStandaloneVideo);
  if ( backEnd.viewDef->viewEntitys )
  {
    GL_State(0x10000);
    backEnd.currentScissor = backEnd.viewDef->scissor;
    qglScissor(
      backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
      (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
      backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
      (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
    RB_UpdateDebugCvars();
    RB_ShowLightCount();
    RB_ShowShadowCount();
    RB_ShowTexturePolarity(drawSurfs, numDrawSurfs);
    RB_ShowTangentSpace(drawSurfs, numDrawSurfs);
    RB_ShowVertexColor(drawSurfs, numDrawSurfs);
    RB_ShowHitImages();
    RB_ShowBatchSize(drawSurfs, numDrawSurfs);
    RB_ShowTris(drawSurfs, numDrawSurfs);
    RB_ShowUnsmoothedTangents(drawSurfs, numDrawSurfs);
    RB_ShowOverdraw(drawSurfs, numDrawSurfs);
    RB_ShowUnweld(drawSurfs, numDrawSurfs);
    RB_ShowSurfaceInfo();
    RB_ShowEdges(drawSurfs, numDrawSurfs);
    RB_ShowNormals(drawSurfs, numDrawSurfs);
    RB_ShowViewEntitys(backEnd.viewDef->viewEntitys);
    RB_ShowLights();
    RB_ShowLightPortals();
    RB_ShowTextureVectors(drawSurfs, numDrawSurfs);
    RB_ShowDominantTris(drawSurfs, numDrawSurfs);
    if ( r_testGamma.internalVar->integerValue > 0 )
      RB_TestGamma();
    if ( r_testGammaBias.internalVar->integerValue > 0 )
      RB_TestGammaBias();
    RB_TestImage();
    RB_ShowPortals();
    RB_ShowSilhouette();
    RB_ShowDepthBuffer();
    RB_ShowIntensity();
    RB_ShowTrace(drawSurfs, numDrawSurfs);
    RB_ShowTriangleTangents(drawSurfs, numDrawSurfs);
    primaryWorld = tr.primaryWorld;
    if ( tr.primaryWorld )
    {
      tr.primaryWorld->ShowDebugLines(tr.primaryWorld);
      primaryWorld->ShowDebugPolygons(primaryWorld);
      primaryWorld->ShowDebugText(primaryWorld);
    }
  }
}
