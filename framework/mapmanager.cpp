
// FUNC: public: static bool __cdecl MapManager::ValidIndex(int)
BOOL __cdecl MapManager::ValidIndex(int i)
{
  return i >= 0;
}

// FUNC: public: static char const * __cdecl MapManager::Thumbnail(int)
char *__cdecl MapManager::Thumbnail(int index)
{
  if ( index >= `anonymous namespace'::gDefaultMaps.num )
    return `anonymous namespace'::gAddonMaps.list[index - `anonymous namespace'::gDefaultMaps.num].mThumbnail.data;
  else
    return `anonymous namespace'::gDefaultMaps.list[index].mThumbnail.data;
}

// FUNC: public: static int __cdecl MapManager::FindByFileName(char const *)
int __cdecl MapManager::FindByFileName(const char *name)
{
  int v1; // ebx
  const char *v2; // eax
  int v3; // edi
  int v4; // eax
  char *data; // edx
  const char *v6; // ecx
  char v7; // al
  idStr *v8; // esi
  unsigned int len; // ebp
  int v10; // eax
  int num; // ecx
  int v12; // edi
  int v13; // esi
  MapInfo *v15; // eax
  idStr mn; // [esp+Ch] [ebp-2Ch] BYREF
  int v17; // [esp+34h] [ebp-4h]

  v1 = 0;
  mn.len = 0;
  mn.alloced = 20;
  mn.data = mn.baseBuffer;
  mn.baseBuffer[0] = 0;
  if ( name )
  {
    v2 = &name[strlen(name) + 1];
    v3 = v2 - (name + 1);
    v4 = v2 - name;
    if ( v4 > 20 )
      idStr::ReAllocate(&mn, v4, 1);
    data = mn.data;
    v6 = name;
    do
    {
      v7 = *v6;
      *data++ = *v6++;
    }
    while ( v7 );
    mn.len = v3;
  }
  v17 = 0;
  v8 = idStr::StripFileExtension(&mn);
  len = v8->len;
  v10 = v8->len + 1;
  if ( v10 > mn.alloced )
    idStr::ReAllocate(&mn, v10, 0);
  qmemcpy(mn.data, v8->data, len);
  mn.data[len] = 0;
  num = `anonymous namespace'::gDefaultMaps.num;
  v12 = `anonymous namespace'::gAddonMaps.num + `anonymous namespace'::gDefaultMaps.num;
  v13 = 0;
  mn.len = len;
  if ( `anonymous namespace'::gAddonMaps.num + `anonymous namespace'::gDefaultMaps.num > 0 )
  {
    while ( 1 )
    {
      v15 = v13 >= num
          ? &`anonymous namespace'::gAddonMaps.list[v13 - num]
          : &`anonymous namespace'::gDefaultMaps.list[v1];
      if ( !idStr::Icmp(v15->mFileName.data, mn.data) )
        break;
      ++v13;
      ++v1;
      if ( v13 >= v12 )
        goto LABEL_10;
      num = `anonymous namespace'::gDefaultMaps.num;
    }
    v17 = -1;
    idStr::FreeData(&mn);
    return v13;
  }
  else
  {
LABEL_10:
    v17 = -1;
    idStr::FreeData(&mn);
    return -1;
  }
}

// FUNC: public: static void __cdecl MapManager::CreateDefaultMapList(void)
void __cdecl MapManager::CreateDefaultMapList()
{
  int v0; // eax
  int v1; // esi
  int granularity; // edi
  int v3; // ebx
  const idDecl *v4; // edi
  idDict *v5; // esi
  MapInfo *v6; // ebp
  const idKeyValue *Key; // eax
  const idPoolStr *value; // edi
  unsigned int len; // esi
  int v10; // eax
  MapInfo *v11; // ebp
  char *v12; // eax
  idStr *p_mLoadImage; // ebp
  const idKeyValue *v14; // eax
  const idPoolStr *v15; // edi
  unsigned int v16; // esi
  int v17; // eax
  idStr *p_mThumbnail; // ebp
  const idKeyValue *v19; // eax
  const idPoolStr *v20; // edi
  unsigned int v21; // esi
  int v22; // eax
  idStr *v23; // ebp
  const idKeyValue *v24; // eax
  const idPoolStr *v25; // edi
  unsigned int v26; // esi
  int v27; // eax
  int v28; // edi
  const idKeyValue *v29; // eax
  const char *data; // eax
  idDict *v31; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]
  int v33; // [esp+18h] [ebp-Ch]
  const idDecl *mapDecl; // [esp+1Ch] [ebp-8h]
  const idDecl *mapDecla; // [esp+1Ch] [ebp-8h]
  const idDecl *mapDeclb; // [esp+1Ch] [ebp-8h]
  const idDecl *mapDeclc; // [esp+1Ch] [ebp-8h]
  int numMaps; // [esp+20h] [ebp-4h]

  v0 = declManager->GetNumDecls(declManager, DECL_MAPDEF);
  v1 = v0;
  numMaps = v0;
  if ( v0 > `anonymous namespace'::gDefaultMaps.size )
  {
    granularity = `anonymous namespace'::gDefaultMaps.granularity;
    if ( !`anonymous namespace'::gDefaultMaps.granularity )
    {
      granularity = 16;
      `anonymous namespace'::gDefaultMaps.granularity = 16;
    }
    idList<`anonymous namespace'::MapInfo>::Resize(
      &`anonymous namespace'::gDefaultMaps,
      granularity + v0 - 1 - (granularity + v0 - 1) % granularity);
  }
  v3 = 0;
  `anonymous namespace'::gDefaultMaps.num = v1;
  i = 0;
  if ( v1 > 0 )
  {
    do
    {
      v4 = declManager->DeclByIndex(declManager, 17, i, 1);
      v5 = (idDict *)&v4[1];
      v6 = &`anonymous namespace'::gDefaultMaps.list[v3];
      mapDecl = v4;
      v31 = (idDict *)&v4[1];
      Key = idDict::FindKey((idDict *)&v4[1], "name");
      if ( Key )
      {
        value = Key->value;
        len = value->len;
        v10 = value->len + 1;
        v33 = value->len;
        if ( v10 > v6->mLocalizedName.alloced )
          idStr::ReAllocate(&v6->mLocalizedName, v10, 0);
        qmemcpy(v6->mLocalizedName.data, value->data, len);
        v5 = v31;
        v4 = mapDecl;
        v6->mLocalizedName.data[v33] = 0;
        v6->mLocalizedName.len = v33;
      }
      else
      {
        idStr::operator=(&v6->mLocalizedName, "broken_map");
      }
      v11 = &`anonymous namespace'::gDefaultMaps.list[v3];
      v12 = (char *)v4->base->GetName(v4->base);
      idStr::operator=(&v11->mFileName, v12);
      p_mLoadImage = &`anonymous namespace'::gDefaultMaps.list[v3].mLoadImage;
      v14 = idDict::FindKey(v5, "loadimage");
      if ( v14 )
      {
        v15 = v14->value;
        v16 = v15->len;
        v17 = v15->len + 1;
        mapDecla = (const idDecl *)v15->len;
        if ( v17 > p_mLoadImage->alloced )
          idStr::ReAllocate(p_mLoadImage, v17, 0);
        qmemcpy(p_mLoadImage->data, v15->data, v16);
        v5 = v31;
        *((_BYTE *)&mapDecla->__vftable + (unsigned int)p_mLoadImage->data) = 0;
        p_mLoadImage->len = (int)mapDecla;
      }
      else
      {
        idStr::operator=(p_mLoadImage, "gfx/guis/loadscreens/generic");
      }
      p_mThumbnail = &`anonymous namespace'::gDefaultMaps.list[v3].mThumbnail;
      v19 = idDict::FindKey(v5, "savethumb");
      if ( v19 )
      {
        v20 = v19->value;
        v21 = v20->len;
        v22 = v20->len + 1;
        mapDeclb = (const idDecl *)v20->len;
        if ( v22 > p_mThumbnail->alloced )
          idStr::ReAllocate(p_mThumbnail, v22, 0);
        qmemcpy(p_mThumbnail->data, v20->data, v21);
        v5 = v31;
        *((_BYTE *)&mapDeclb->__vftable + (unsigned int)p_mThumbnail->data) = 0;
        p_mThumbnail->len = (int)mapDeclb;
      }
      else
      {
        idStr::operator=(p_mThumbnail, "null");
      }
      if ( !idStr::Cmp(`anonymous namespace'::gDefaultMaps.list[v3].mThumbnail.data, "null") )
      {
        v23 = &`anonymous namespace'::gDefaultMaps.list[v3].mThumbnail;
        v24 = idDict::FindKey(v5, "mp_thumb");
        if ( v24 )
        {
          v25 = v24->value;
          v26 = v25->len;
          v27 = v25->len + 1;
          mapDeclc = (const idDecl *)v25->len;
          if ( v27 > v23->alloced )
            idStr::ReAllocate(v23, v27, 0);
          qmemcpy(v23->data, v25->data, v26);
          v5 = v31;
          *((_BYTE *)&mapDeclc->__vftable + (unsigned int)v23->data) = 0;
          v23->len = (int)mapDeclc;
        }
        else
        {
          idStr::operator=(v23, "gfx/guis/loadscreens/generic");
        }
      }
      `anonymous namespace'::gDefaultMaps.list[v3].mMagicNumber = -202247937;
      v28 = 0;
      `anonymous namespace'::gDefaultMaps.list[v3].mGametypeMask = 0;
      do
      {
        v29 = idDict::FindKey(v5, `anonymous namespace'::GametypeStrings[v28]);
        if ( v29 )
          data = v29->value->data;
        else
          data = "0";
        if ( atoi(data) )
          `anonymous namespace'::gDefaultMaps.list[v3].mGametypeMask |= 1 << v28;
        ++v28;
      }
      while ( v28 < 11 );
      ++v3;
      ++i;
    }
    while ( i < numMaps );
  }
}
