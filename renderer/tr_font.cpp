
// FUNC: public: virtual bool __thiscall idRenderSystemLocal::RegisterFont(char const *,struct fontInfoEx_t &)
bool __userpurge idRenderSystemLocal::RegisterFont@<al>(
        idRenderSystemLocal *this@<ecx>,
        float *p_pointSize@<ebp>,
        const char *fontName,
        fontInfoEx_t *font)
{
  int v4; // esi
  fontInfoEx_t *v5; // ebx
  int v6; // eax
  fontInfoEx_t *p_fontInfoMedium; // ebp
  char *v8; // eax
  idFile *v9; // esi
  float *p_horiBearingY; // edi
  const idMaterial *v11; // eax
  float mw; // [esp+58h] [ebp-40h]
  float mh; // [esp+5Ch] [ebp-3Ch]
  float fontCount; // [esp+60h] [ebp-38h]
  int found; // [esp+64h] [ebp-34h]
  idStr name; // [esp+6Ch] [ebp-2Ch] BYREF
  int v19; // [esp+94h] [ebp-4h]

  v4 = 0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v5 = font;
  v19 = 0;
  memset(font, 0, sizeof(fontInfoEx_t));
  found = 0;
  do
  {
    if ( v4 )
    {
      if ( v4 == 1 )
      {
        v6 = 24;
        p_fontInfoMedium = (fontInfoEx_t *)&v5->fontInfoMedium;
      }
      else
      {
        v6 = 48;
        p_fontInfoMedium = (fontInfoEx_t *)&v5->fontInfoLarge;
      }
    }
    else
    {
      v6 = 12;
      p_fontInfoMedium = v5;
    }
    v8 = va("%s_%i.fontdat", fontName, v6);
    idStr::operator=(&name, v8);
    if ( fileSystem->ReadFile(fileSystem, name.data, 0, 0) == 9236 )
    {
      found |= 1 << v4;
      v9 = (idFile *)((int (__thiscall *)(idFileSystem *, char *, int, _DWORD, float *))fileSystem->OpenFileRead)(
                       fileSystem,
                       name.data,
                       1,
                       0,
                       p_pointSize);
      mh = 0.0;
      fontCount = 0.0;
      p_horiBearingY = &p_fontInfoMedium->fontInfoSmall.glyphs[0].horiBearingY;
      name.len = 256;
      do
      {
        v9->ReadFloat(v9, p_horiBearingY - 4);
        v9->ReadFloat(v9, p_horiBearingY - 3);
        v9->ReadFloat(v9, p_horiBearingY - 2);
        v9->ReadFloat(v9, p_horiBearingY - 1);
        v9->ReadFloat(v9, p_horiBearingY);
        v9->ReadFloat(v9, p_horiBearingY + 1);
        v9->ReadFloat(v9, p_horiBearingY + 2);
        v9->ReadFloat(v9, p_horiBearingY + 3);
        v9->ReadFloat(v9, p_horiBearingY + 4);
        if ( mh < (double)*(p_horiBearingY - 2) )
          mh = *(p_horiBearingY - 2);
        if ( fontCount < (double)*(p_horiBearingY - 3) )
          fontCount = *(p_horiBearingY - 3);
        p_horiBearingY += 9;
        --name.len;
      }
      while ( name.len );
      p_pointSize = &p_fontInfoMedium->fontInfoSmall.pointSize;
      ((void (__thiscall *)(idFile *))v9->ReadFloat)(v9);
      v9->ReadFloat(v9, &p_fontInfoMedium->fontInfoSmall.fontHeight);
      v9->ReadFloat(v9, &p_fontInfoMedium->fontInfoSmall.ascender);
      v9->ReadFloat(v9, &p_fontInfoMedium->fontInfoSmall.descender);
      fileSystem->CloseFile(fileSystem, v9);
      v11 = declManager->FindMaterial(declManager, name.data, 1);
      p_fontInfoMedium->fontInfoSmall.material = (idMaterial *)v11;
      v11->sort = -2.0;
      if ( fontCount == 0.0 )
      {
        font->maxWidthSmall = mw;
        font->maxHeightSmall = mh;
      }
      else if ( LODWORD(fontCount) == 1 )
      {
        font->maxWidthMedium = mw;
        font->maxHeightMedium = mh;
      }
      else
      {
        font->maxWidthLarge = mw;
        font->maxHeightLarge = mh;
      }
      v5 = font;
      v4 = LODWORD(fontCount);
    }
    ++v4;
  }
  while ( v4 < 3 );
  switch ( found )
  {
    case 1:
      qmemcpy(&v5->fontInfoMedium, v5, sizeof(v5->fontInfoMedium));
      v5->maxHeightMedium = v5->maxHeightSmall;
      qmemcpy(&v5->fontInfoLarge, v5, sizeof(v5->fontInfoLarge));
      v5->maxHeightLarge = v5->maxHeightSmall;
      break;
    case 2:
      qmemcpy(v5, &v5->fontInfoMedium, 0x2414u);
      v5->maxHeightSmall = v5->maxHeightMedium;
      qmemcpy(&v5->fontInfoLarge, &v5->fontInfoMedium, sizeof(v5->fontInfoLarge));
      v5->maxHeightLarge = v5->maxHeightMedium;
      break;
    case 3:
      qmemcpy(&v5->fontInfoLarge, &v5->fontInfoMedium, sizeof(v5->fontInfoLarge));
      v5->maxHeightLarge = v5->maxHeightMedium;
      break;
    case 4:
      qmemcpy(v5, &v5->fontInfoLarge, 0x2414u);
      v5->maxHeightSmall = v5->maxHeightLarge;
      qmemcpy(&v5->fontInfoMedium, &v5->fontInfoLarge, sizeof(v5->fontInfoMedium));
      v5->maxHeightMedium = v5->maxHeightLarge;
      break;
    case 5:
      qmemcpy(&v5->fontInfoMedium, &v5->fontInfoLarge, sizeof(v5->fontInfoMedium));
      v5->maxHeightMedium = v5->maxHeightLarge;
      break;
    case 6:
      qmemcpy(v5, &v5->fontInfoMedium, 0x2414u);
      v5->maxHeightSmall = v5->maxHeightMedium;
      break;
    default:
      break;
  }
  v19 = -1;
  idStr::FreeData(&name);
  return found != 0;
}
