
// FUNC: void * __cdecl unzReOpen(char const *,void *)
IGSS_FileSystem **__cdecl unzReOpen(const char *path, void *file)
{
  IGSS_FileSystem *FileSystem; // edi
  IGSS_FileSystem **v4; // esi

  FileSystem = GSS_GetFileSystem();
  if ( FileSystem->fopen(FileSystem, path, "rb") )
  {
    v4 = (IGSS_FileSystem **)Mem_Alloc(136, 0xBu);
    SIMDProcessor->Memcpy(SIMDProcessor, v4, file, 136);
    *v4 = FileSystem;
    v4[33] = 0;
    return v4;
  }
  else
  {
    Memory::Free(FileSystem);
    return 0;
  }
}

// FUNC: void * __cdecl unzOpen(char const *)
unz_s *__usercall unzOpen@<eax>(int a1@<ebp>, int a2@<edi>, int a3@<esi>, const char *path)
{
  IGSS_FileSystem *FileSystem; // ebx
  IGSS_FileSystem_vtbl *v5; // eax
  unz_s *result; // eax
  void *v7; // eax
  unsigned int v8; // esi
  __int16 v9; // ax
  IGSS_FileSystem v10; // edx
  int v11; // ebp
  __int16 v12; // ax
  IGSS_FileSystem v13; // edx
  int v14; // edi
  unsigned int v15; // edi
  IGSS_FileSystem v16; // eax
  unsigned int v17; // ebp
  IGSS_FileSystem v18; // eax
  unsigned int number_disk; // [esp+70h] [ebp-90h] BYREF
  int err; // [esp+74h] [ebp-8Ch] BYREF
  unz_s us; // [esp+78h] [ebp-88h] BYREF

  FileSystem = GSS_GetFileSystem();
  v5 = FileSystem->__vftable;
  err = 0;
  if ( v5->fopen(FileSystem, path, "rb") )
  {
    v7 = unzlocal_SearchCentralDir(FileSystem);
    v8 = (unsigned int)v7;
    if ( !v7 )
      err = -1;
    if ( ((int (__thiscall *)(IGSS_FileSystem *, void *, _DWORD, int, int))FileSystem->fseek)(FileSystem, v7, 0, a2, a3) )
      us.gi.number_entry = -1;
    ((void (__thiscall *)(IGSS_FileSystem *, int *, int, int, int))FileSystem->fread)(FileSystem, &err, 4, 1, a1);
    LittleLong((int)us.file);
    FileSystem->fread(FileSystem, &us, 2u, 1u);
    v9 = LittleShort((__int16)us.file);
    v10.__vftable = FileSystem->__vftable;
    us.gi.number_entry = v9;
    v10.fread(FileSystem, &us, 2u, 1u);
    v11 = LittleShort((__int16)us.file);
    FileSystem->fread(FileSystem, &us, 2u, 1u);
    v12 = LittleShort((__int16)us.file);
    v13.__vftable = FileSystem->__vftable;
    v14 = v12;
    us.num_file = v12;
    v13.fread(FileSystem, &us, 2u, 1u);
    if ( LittleShort((__int16)us.file) != v14 || v11 || us.gi.number_entry )
      us.gi.size_comment = -103;
    FileSystem->fread(FileSystem, &us.gi, 4u, 1u);
    v15 = LittleLong(number_disk);
    v16.__vftable = FileSystem->__vftable;
    us.size_central_dir = v15;
    v16.fread(FileSystem, &number_disk, 4u, 1u);
    v17 = LittleLong(number_disk);
    v18.__vftable = FileSystem->__vftable;
    us.offset_central_dir = v17;
    v18.fread(FileSystem, &number_disk, 2u, 1u);
    us.gi.size_comment = LittleShort(number_disk);
    if ( v8 < v15 + v17 || err )
    {
      FileSystem->fclose(FileSystem);
      Memory::Free(FileSystem);
      return 0;
    }
    else
    {
      us.file = FileSystem;
      us.byte_before_the_zipfile = v8 - v15 - v17;
      us.central_pos = v8;
      us.pfile_in_zip_read = 0;
      result = (unz_s *)Mem_Alloc(136, 0xBu);
      qmemcpy(result, &us, sizeof(unz_s));
      result->cached_central_directory = 0;
      result->cached_central_directory_current = 0;
    }
  }
  else
  {
    Memory::Free(FileSystem);
    return 0;
  }
  return result;
}

// FUNC: int __cdecl unzGetGlobalInfo(void *,struct unz_global_info_s *)
int __cdecl unzGetGlobalInfo(char *file, unz_global_info_s *pglobal_info)
{
  if ( !file )
    return -102;
  *pglobal_info = *(unz_global_info_s *)(file + 4);
  return 0;
}

// FUNC: int __cdecl unzGetCurrentFileInfo(void *,struct unz_file_info_s *,char *,unsigned long,void *,unsigned long,char *,unsigned long)
int __cdecl unzGetCurrentFileInfo(
        unz_s *file,
        unz_file_info_s *pfile_info,
        char *szFileName,
        unsigned int fileNameBufferSize,
        void *extraField,
        unsigned int extraFieldBufferSize,
        char *szComment,
        unsigned int commentBufferSize)
{
  return unzlocal_GetCurrentFileInfoInternal(
           file,
           pfile_info,
           0,
           szFileName,
           fileNameBufferSize,
           extraField,
           extraFieldBufferSize,
           szComment,
           commentBufferSize);
}

// FUNC: int __cdecl unzGoToFirstFile(void *)
int __usercall unzGoToFirstFile@<eax>(int a1@<ebp>, int a2@<edi>, int a3@<esi>, unz_s *file, int a5, int a6, int l)
{
  unz_s *v7; // ebx
  int result; // eax
  unsigned int offset_central_dir; // eax
  int v10; // ebp
  bool v11; // zf
  __int16 v12; // ax
  IGSS_FileSystem *v13; // ecx
  int v14; // edx
  IGSS_FileSystem_vtbl *v15; // eax
  __int16 v16; // ax
  IGSS_FileSystem *v17; // ecx
  int v18; // edx
  IGSS_FileSystem_vtbl *v19; // eax
  unsigned int v20; // eax
  IGSS_FileSystem *v21; // ecx
  int v22; // eax
  IGSS_FileSystem *v23; // ecx
  IGSS_FileSystem_vtbl *v24; // edx
  int v25; // eax
  IGSS_FileSystem *v26; // ecx
  IGSS_FileSystem_vtbl *v27; // edx
  int v28; // eax
  IGSS_FileSystem *v29; // ecx
  IGSS_FileSystem_vtbl *v30; // edx
  __int16 v31; // ax
  IGSS_FileSystem *v32; // ecx
  int v33; // edx
  IGSS_FileSystem_vtbl *v34; // eax
  __int16 v35; // ax
  IGSS_FileSystem *v36; // ecx
  int v37; // edx
  IGSS_FileSystem_vtbl *v38; // eax
  __int16 v39; // ax
  IGSS_FileSystem *v40; // ecx
  int v41; // edx
  IGSS_FileSystem_vtbl *v42; // eax
  int v43; // eax
  IGSS_FileSystem *v44; // ecx
  IGSS_FileSystem_vtbl *v45; // edx
  int v46; // eax
  int v48[20]; // [esp+C8h] [ebp-50h] BYREF

  v7 = file;
  if ( !file )
    return -102;
  offset_central_dir = file->offset_central_dir;
  v10 = 0;
  v11 = file->cached_central_directory == 0;
  file->pos_in_central_dir = offset_central_dir;
  v7->num_file = 0;
  if ( v11 )
  {
    if ( ((int (__thiscall *)(IGSS_FileSystem *, unsigned int, _DWORD, int, int, int))v7->file->fseek)(
           v7->file,
           offset_central_dir + v7->byte_before_the_zipfile,
           0,
           a3,
           a2,
           a1) )
    {
      v10 = -1;
    }
    else
    {
      v7->file->fread(v7->file, &l, 4u, 1u);
      if ( LittleLong(l) != 33639248 )
        v10 = -103;
    }
    v7->file->fread(v7->file, &l, 2u, 1u);
    v12 = LittleShort((__int16)file);
    v13 = v7->file;
    v14 = v12;
    v15 = v7->file->__vftable;
    v48[0] = v14;
    v15->fread(v13, &file, 2u, 1u);
    v48[1] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v16 = LittleShort((__int16)file);
    v17 = v7->file;
    v18 = v16;
    v19 = v7->file->__vftable;
    v48[2] = v18;
    v19->fread(v17, &file, 2u, 1u);
    v48[3] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 4u, 1u);
    v20 = LittleLong((int)file);
    v48[17] = BYTE2(v20) & 0x1F;
    v48[19] = (v20 >> 25) + 1980;
    v48[4] = v20;
    v48[18] = ((v20 >> 21) & 0xF) - 1;
    v48[16] = (unsigned __int16)v20 >> 11;
    v21 = v7->file;
    v48[15] = (v20 >> 5) & 0x3F;
    v48[14] = 2 * (v20 & 0x1F);
    v21->fread(v21, &file, 4u, 1u);
    v22 = LittleLong((int)file);
    v23 = v7->file;
    v24 = v7->file->__vftable;
    v48[5] = v22;
    v24->fread(v23, &file, 4u, 1u);
    v25 = LittleLong((int)file);
    v26 = v7->file;
    v27 = v7->file->__vftable;
    v48[6] = v25;
    v27->fread(v26, &file, 4u, 1u);
    v28 = LittleLong((int)file);
    v29 = v7->file;
    v30 = v7->file->__vftable;
    v48[7] = v28;
    v30->fread(v29, &file, 2u, 1u);
    v31 = LittleShort((__int16)file);
    v32 = v7->file;
    v33 = v31;
    v34 = v7->file->__vftable;
    v48[8] = v33;
    v34->fread(v32, &file, 2u, 1u);
    v48[9] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v35 = LittleShort((__int16)file);
    v36 = v7->file;
    v37 = v35;
    v38 = v7->file->__vftable;
    v48[10] = v37;
    v38->fread(v36, &file, 2u, 1u);
    v48[11] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v39 = LittleShort((__int16)file);
    v40 = v7->file;
    v41 = v39;
    v42 = v7->file->__vftable;
    v48[12] = v41;
    v42->fread(v40, &file, 4u, 1u);
    v43 = LittleLong((int)file);
    v44 = v7->file;
    v45 = v7->file->__vftable;
    v48[13] = v43;
    v45->fread(v44, &file, 4u, 1u);
    v46 = LittleLong((int)file);
    if ( !v10 )
    {
      if ( v7 != (unz_s *)-48 )
        qmemcpy(&v7->cur_file_info, v48, sizeof(v7->cur_file_info));
      if ( v7 != (unz_s *)-128 )
        v7->cur_file_info_internal.offset_curfile = v46;
    }
    result = v10;
    v7->current_file_ok = v10 == 0;
  }
  else
  {
    result = unzlocal_GetCurrentFileInfoInternalCache(v7, &v7->cur_file_info, &v7->cur_file_info_internal, 0, 0);
    v7->current_file_ok = result == 0;
  }
  return result;
}

// FUNC: int __cdecl unzGoToNextFile(void *)
int __usercall unzGoToNextFile@<eax>(int a1@<ebp>, int a2@<edi>, int a3@<esi>, unz_s *file, int a5, int a6, int l)
{
  unz_s *v7; // ebx
  int result; // eax
  int v9; // ecx
  unsigned int pos_in_central_dir; // eax
  int v11; // ebp
  bool v12; // zf
  __int16 v13; // ax
  IGSS_FileSystem *v14; // ecx
  int v15; // edx
  IGSS_FileSystem_vtbl *v16; // eax
  __int16 v17; // ax
  IGSS_FileSystem *v18; // ecx
  int v19; // edx
  IGSS_FileSystem_vtbl *v20; // eax
  unsigned int v21; // eax
  IGSS_FileSystem *v22; // ecx
  int v23; // eax
  IGSS_FileSystem *v24; // ecx
  IGSS_FileSystem_vtbl *v25; // edx
  int v26; // eax
  IGSS_FileSystem *v27; // ecx
  IGSS_FileSystem_vtbl *v28; // edx
  int v29; // eax
  IGSS_FileSystem *v30; // ecx
  IGSS_FileSystem_vtbl *v31; // edx
  __int16 v32; // ax
  IGSS_FileSystem *v33; // ecx
  int v34; // edx
  IGSS_FileSystem_vtbl *v35; // eax
  __int16 v36; // ax
  IGSS_FileSystem *v37; // ecx
  int v38; // edx
  IGSS_FileSystem_vtbl *v39; // eax
  __int16 v40; // ax
  IGSS_FileSystem *v41; // ecx
  int v42; // edx
  IGSS_FileSystem_vtbl *v43; // eax
  int v44; // eax
  IGSS_FileSystem *v45; // ecx
  IGSS_FileSystem_vtbl *v46; // edx
  int v47; // eax
  int v49[20]; // [esp+C8h] [ebp-50h] BYREF

  v7 = file;
  if ( !file )
    return -102;
  if ( !file->current_file_ok )
    return -100;
  v9 = file->num_file + 1;
  if ( v9 == file->gi.number_entry )
    return -100;
  file->pos_in_central_dir += file->cur_file_info.size_file_extra
                            + file->cur_file_info.size_file_comment
                            + file->cur_file_info.size_filename
                            + 46;
  pos_in_central_dir = v7->pos_in_central_dir;
  v11 = 0;
  v12 = v7->cached_central_directory == 0;
  v7->num_file = v9;
  if ( v12 )
  {
    if ( ((int (__thiscall *)(IGSS_FileSystem *, unsigned int, _DWORD, int, int, int))v7->file->fseek)(
           v7->file,
           pos_in_central_dir + v7->byte_before_the_zipfile,
           0,
           a3,
           a2,
           a1) )
    {
      v11 = -1;
    }
    else
    {
      v7->file->fread(v7->file, &l, 4u, 1u);
      if ( LittleLong(l) != 33639248 )
        v11 = -103;
    }
    v7->file->fread(v7->file, &l, 2u, 1u);
    v13 = LittleShort((__int16)file);
    v14 = v7->file;
    v15 = v13;
    v16 = v7->file->__vftable;
    v49[0] = v15;
    v16->fread(v14, &file, 2u, 1u);
    v49[1] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v17 = LittleShort((__int16)file);
    v18 = v7->file;
    v19 = v17;
    v20 = v7->file->__vftable;
    v49[2] = v19;
    v20->fread(v18, &file, 2u, 1u);
    v49[3] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 4u, 1u);
    v21 = LittleLong((int)file);
    v49[17] = BYTE2(v21) & 0x1F;
    v49[19] = (v21 >> 25) + 1980;
    v49[4] = v21;
    v49[18] = ((v21 >> 21) & 0xF) - 1;
    v49[16] = (unsigned __int16)v21 >> 11;
    v22 = v7->file;
    v49[15] = (v21 >> 5) & 0x3F;
    v49[14] = 2 * (v21 & 0x1F);
    v22->fread(v22, &file, 4u, 1u);
    v23 = LittleLong((int)file);
    v24 = v7->file;
    v25 = v7->file->__vftable;
    v49[5] = v23;
    v25->fread(v24, &file, 4u, 1u);
    v26 = LittleLong((int)file);
    v27 = v7->file;
    v28 = v7->file->__vftable;
    v49[6] = v26;
    v28->fread(v27, &file, 4u, 1u);
    v29 = LittleLong((int)file);
    v30 = v7->file;
    v31 = v7->file->__vftable;
    v49[7] = v29;
    v31->fread(v30, &file, 2u, 1u);
    v32 = LittleShort((__int16)file);
    v33 = v7->file;
    v34 = v32;
    v35 = v7->file->__vftable;
    v49[8] = v34;
    v35->fread(v33, &file, 2u, 1u);
    v49[9] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v36 = LittleShort((__int16)file);
    v37 = v7->file;
    v38 = v36;
    v39 = v7->file->__vftable;
    v49[10] = v38;
    v39->fread(v37, &file, 2u, 1u);
    v49[11] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v40 = LittleShort((__int16)file);
    v41 = v7->file;
    v42 = v40;
    v43 = v7->file->__vftable;
    v49[12] = v42;
    v43->fread(v41, &file, 4u, 1u);
    v44 = LittleLong((int)file);
    v45 = v7->file;
    v46 = v7->file->__vftable;
    v49[13] = v44;
    v46->fread(v45, &file, 4u, 1u);
    v47 = LittleLong((int)file);
    if ( !v11 )
    {
      if ( v7 != (unz_s *)-48 )
        qmemcpy(&v7->cur_file_info, v49, sizeof(v7->cur_file_info));
      if ( v7 != (unz_s *)-128 )
        v7->cur_file_info_internal.offset_curfile = v47;
    }
    result = v11;
    v7->current_file_ok = v11 == 0;
  }
  else
  {
    result = unzlocal_GetCurrentFileInfoInternalCache(v7, &v7->cur_file_info, &v7->cur_file_info_internal, 0, 0);
    v7->current_file_ok = result == 0;
  }
  return result;
}

// FUNC: int __cdecl unzGetCurrentFileInfoPosition(void *,unsigned long *)
int __cdecl unzGetCurrentFileInfoPosition(_DWORD *file, unsigned int *pos)
{
  if ( !file )
    return -102;
  *pos = file[5];
  return 0;
}

// FUNC: int __cdecl unzSetCurrentFileInfoPosition(void *,unsigned long)
int __usercall unzSetCurrentFileInfoPosition@<eax>(
        int a1@<ebp>,
        int a2@<edi>,
        int a3@<esi>,
        unz_s *file,
        unsigned int pos,
        int a6,
        int l)
{
  unz_s *v7; // ebx
  int result; // eax
  unsigned int v9; // eax
  int v10; // ebp
  bool v11; // zf
  BOOL v12; // edx
  __int16 v13; // ax
  IGSS_FileSystem *v14; // ecx
  int v15; // edx
  IGSS_FileSystem_vtbl *v16; // eax
  __int16 v17; // ax
  IGSS_FileSystem *v18; // ecx
  int v19; // edx
  IGSS_FileSystem_vtbl *v20; // eax
  unsigned int v21; // eax
  IGSS_FileSystem *v22; // ecx
  int v23; // eax
  IGSS_FileSystem *v24; // ecx
  IGSS_FileSystem_vtbl *v25; // edx
  int v26; // eax
  IGSS_FileSystem *v27; // ecx
  IGSS_FileSystem_vtbl *v28; // edx
  int v29; // eax
  IGSS_FileSystem *v30; // ecx
  IGSS_FileSystem_vtbl *v31; // edx
  __int16 v32; // ax
  IGSS_FileSystem *v33; // ecx
  int v34; // edx
  IGSS_FileSystem_vtbl *v35; // eax
  __int16 v36; // ax
  IGSS_FileSystem *v37; // ecx
  int v38; // edx
  IGSS_FileSystem_vtbl *v39; // eax
  __int16 v40; // ax
  IGSS_FileSystem *v41; // ecx
  int v42; // edx
  IGSS_FileSystem_vtbl *v43; // eax
  int v44; // eax
  IGSS_FileSystem *v45; // ecx
  IGSS_FileSystem_vtbl *v46; // edx
  int v47; // eax
  int v49[20]; // [esp+C8h] [ebp-50h] BYREF

  v7 = file;
  if ( !file )
    return -102;
  v9 = pos;
  v10 = 0;
  v11 = file->cached_central_directory == 0;
  file->pos_in_central_dir = pos;
  if ( v11 )
  {
    if ( ((int (__thiscall *)(IGSS_FileSystem *, unsigned int, _DWORD, int, int, int))v7->file->fseek)(
           v7->file,
           v9 + v7->byte_before_the_zipfile,
           0,
           a3,
           a2,
           a1) )
    {
      v10 = -1;
    }
    else
    {
      v7->file->fread(v7->file, &l, 4u, 1u);
      if ( LittleLong(l) != 33639248 )
        v10 = -103;
    }
    v7->file->fread(v7->file, &l, 2u, 1u);
    v13 = LittleShort((__int16)file);
    v14 = v7->file;
    v15 = v13;
    v16 = v7->file->__vftable;
    v49[0] = v15;
    v16->fread(v14, &file, 2u, 1u);
    v49[1] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v17 = LittleShort((__int16)file);
    v18 = v7->file;
    v19 = v17;
    v20 = v7->file->__vftable;
    v49[2] = v19;
    v20->fread(v18, &file, 2u, 1u);
    v49[3] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 4u, 1u);
    v21 = LittleLong((int)file);
    v49[17] = BYTE2(v21) & 0x1F;
    v49[19] = (v21 >> 25) + 1980;
    v49[4] = v21;
    v49[18] = ((v21 >> 21) & 0xF) - 1;
    v49[16] = (unsigned __int16)v21 >> 11;
    v22 = v7->file;
    v49[15] = (v21 >> 5) & 0x3F;
    v49[14] = 2 * (v21 & 0x1F);
    v22->fread(v22, &file, 4u, 1u);
    v23 = LittleLong((int)file);
    v24 = v7->file;
    v25 = v7->file->__vftable;
    v49[5] = v23;
    v25->fread(v24, &file, 4u, 1u);
    v26 = LittleLong((int)file);
    v27 = v7->file;
    v28 = v7->file->__vftable;
    v49[6] = v26;
    v28->fread(v27, &file, 4u, 1u);
    v29 = LittleLong((int)file);
    v30 = v7->file;
    v31 = v7->file->__vftable;
    v49[7] = v29;
    v31->fread(v30, &file, 2u, 1u);
    v32 = LittleShort((__int16)file);
    v33 = v7->file;
    v34 = v32;
    v35 = v7->file->__vftable;
    v49[8] = v34;
    v35->fread(v33, &file, 2u, 1u);
    v49[9] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v36 = LittleShort((__int16)file);
    v37 = v7->file;
    v38 = v36;
    v39 = v7->file->__vftable;
    v49[10] = v38;
    v39->fread(v37, &file, 2u, 1u);
    v49[11] = LittleShort((__int16)file);
    v7->file->fread(v7->file, &file, 2u, 1u);
    v40 = LittleShort((__int16)file);
    v41 = v7->file;
    v42 = v40;
    v43 = v7->file->__vftable;
    v49[12] = v42;
    v43->fread(v41, &file, 4u, 1u);
    v44 = LittleLong((int)file);
    v45 = v7->file;
    v46 = v7->file->__vftable;
    v49[13] = v44;
    v46->fread(v45, &file, 4u, 1u);
    v47 = LittleLong((int)file);
    if ( !v10 )
    {
      if ( v7 != (unz_s *)-48 )
        qmemcpy(&v7->cur_file_info, v49, sizeof(v7->cur_file_info));
      if ( v7 != (unz_s *)-128 )
        v7->cur_file_info_internal.offset_curfile = v47;
    }
    result = 0;
    v7->current_file_ok = v10 == 0;
  }
  else
  {
    v12 = unzlocal_GetCurrentFileInfoInternalCache(v7, &v7->cur_file_info, &v7->cur_file_info_internal, 0, 0) == 0;
    result = 0;
    v7->current_file_ok = v12;
  }
  return result;
}

// FUNC: int __cdecl unzReadCurrentFile(void *,void *,unsigned int)
int __cdecl unzReadCurrentFile(_DWORD *file, void *buf, unsigned int len)
{
  _DWORD *v3; // ebx
  int *v5; // esi
  unsigned int v6; // eax
  unsigned int v7; // eax
  int v8; // edi
  int v9; // ecx
  unsigned int v10; // edi
  unsigned int i; // eax
  unsigned int v12; // eax
  int v13; // ebx
  const unsigned __int8 *v14; // ebp
  EStatus v15; // eax
  unsigned int v16; // edi
  unsigned int v17; // eax
  unsigned int iRead; // [esp+14h] [ebp-8h]
  int err; // [esp+18h] [ebp-4h]

  v3 = file;
  iRead = 0;
  if ( !file )
    return -102;
  v5 = (int *)file[33];
  if ( !v5 )
    return -102;
  if ( !*v5 )
    return -100;
  if ( !len )
    return 0;
  v5[4] = (int)buf;
  v6 = v5[20];
  v5[5] = len;
  if ( len > v6 )
    v5[5] = v6;
  if ( !v5[5] )
    return iRead;
  while ( 1 )
  {
    if ( !v5[2] )
    {
      v7 = v5[19];
      if ( v7 )
      {
        v8 = 0x10000;
        if ( v7 < 0x10000 )
          v8 = v5[19];
        if ( v3[18] == v7
          && (*(int (__thiscall **)(int, int, _DWORD))(*(_DWORD *)v5[21] + 4))(v5[21], v5[12] + v5[23], 0)
          || (*(int (__thiscall **)(int, _DWORD, int, int))(*(_DWORD *)v5[21] + 12))(v5[21], *v5, v8, 1) != 1 )
        {
          return -1;
        }
        v9 = *v5;
        v5[12] += v8;
        v5[19] -= v8;
        v5[1] = v9;
        v5[2] = v8;
      }
    }
    if ( !v5[22] )
    {
      v10 = v5[2];
      if ( v5[5] < v10 )
        v10 = v5[5];
      for ( i = 0; i < v10; ++i )
        *(_BYTE *)(i + v5[4]) = *(_BYTE *)(i + v5[1]);
      v12 = crc32(v5[17], (const unsigned __int8 *)v5[4], v10);
      v5[20] -= v10;
      v5[2] -= v10;
      v5[5] -= v10;
      v5[4] += v10;
      v5[1] += v10;
      v5[6] += v10;
      iRead += v10;
      v5[17] = v12;
      goto LABEL_29;
    }
    v13 = v5[6];
    v14 = (const unsigned __int8 *)v5[4];
    v15 = inflate((z_stream_s *)(v5 + 1));
    v16 = v5[6] - v13;
    err = v15;
    v17 = crc32(v5[17], v14, v16);
    v5[20] -= v16;
    iRead += v16;
    v5[17] = v17;
    if ( err == 1 )
      return iRead;
    if ( err )
      return err;
    v3 = file;
LABEL_29:
    if ( !v5[5] )
      return iRead;
  }
}

// FUNC: long __cdecl unztell(void *)
int __cdecl unztell(_DWORD *file)
{
  int v1; // eax

  if ( file && (v1 = file[33]) != 0 )
    return *(_DWORD *)(v1 + 24);
  else
    return -102;
}

// FUNC: int __cdecl unzCloseCurrentFile(void *)
int __cdecl unzCloseCurrentFile(_DWORD *file)
{
  int v1; // ebp
  int v3; // esi
  bool v4; // zf

  v1 = 0;
  if ( !file )
    return -102;
  v3 = file[33];
  if ( !v3 )
    return -102;
  if ( !*(_DWORD *)(v3 + 80) && *(_DWORD *)(v3 + 68) != *(_DWORD *)(v3 + 72) )
    v1 = -105;
  if ( *(_DWORD *)v3 )
    Mem_Free(*(void **)v3);
  v4 = *(_DWORD *)(v3 + 52) == 0;
  *(_DWORD *)v3 = 0;
  if ( !v4 )
    inflateEnd((z_stream_s *)(v3 + 4));
  *(_DWORD *)(v3 + 52) = 0;
  Mem_Free((void *)v3);
  file[33] = 0;
  return v1;
}

// FUNC: int __cdecl unzClose(void *)
int __cdecl unzClose(void **file)
{
  bool v2; // zf

  if ( !file )
    return -102;
  if ( file[10] )
  {
    Mem_Free(file[10]);
    file[10] = 0;
  }
  v2 = file[33] == 0;
  file[11] = 0;
  if ( !v2 )
    unzCloseCurrentFile(file);
  (*(void (__thiscall **)(void *))(*(_DWORD *)*file + 16))(*file);
  Memory::Free(*file);
  Mem_Free(file);
  return 0;
}

// FUNC: int __cdecl unzOpenCurrentFile(void *)
int __cdecl unzOpenCurrentFile(unz_s *file)
{
  unz_s *v1; // edi
  file_in_zip_read_info_s *v3; // esi
  char *v4; // eax
  unz_s *v5; // ecx
  unsigned int v6; // edx
  bool v7; // zf
  unsigned int v8; // ecx
  int v9; // edx
  unsigned int size_local_extrafield; // [esp+8h] [ebp-8h] BYREF
  unsigned int iSizeVar; // [esp+Ch] [ebp-4h] BYREF

  v1 = file;
  if ( !file || !file->current_file_ok )
    return -102;
  if ( file->pfile_in_zip_read )
    unzCloseCurrentFile(file);
  if ( unzlocal_CheckCurrentFileCoherencyHeader(v1, 0, &iSizeVar, (unsigned int *)&file, &size_local_extrafield) )
    return -103;
  v3 = (file_in_zip_read_info_s *)Mem_Alloc(96, 0xBu);
  if ( !v3 )
    return -104;
  v4 = (char *)Mem_Alloc(0x10000, 0xBu);
  v5 = file;
  v6 = size_local_extrafield;
  v3->read_buffer = v4;
  v3->offset_local_extrafield = (unsigned int)v5;
  v3->size_local_extrafield = v6;
  v3->pos_local_extrafield = 0;
  if ( !v4 )
  {
    Mem_Free(v3);
    return -104;
  }
  v3->stream_initialised = 0;
  v7 = v1->cur_file_info.compression_method == 0;
  v3->crc32_wait = v1->cur_file_info.crc;
  v3->crc32 = 0;
  v3->compression_method = v1->cur_file_info.compression_method;
  v3->file = v1->file;
  v3->byte_before_the_zipfile = v1->byte_before_the_zipfile;
  v3->stream.total_out = 0;
  if ( !v7 && inflateInit(&v3->stream, Z_SYNC_FLUSH, 1) == Z_OK )
    v3->stream_initialised = 1;
  v3->rest_read_compressed = v1->cur_file_info.compressed_size;
  v8 = iSizeVar;
  v3->rest_read_uncompressed = v1->cur_file_info.uncompressed_size;
  v9 = v1->cur_file_info_internal.offset_curfile + v8 + 30;
  v3->stream.avail_in = 0;
  v3->pos_in_zipfile = v9;
  v1->pfile_in_zip_read = v3;
  return 0;
}
