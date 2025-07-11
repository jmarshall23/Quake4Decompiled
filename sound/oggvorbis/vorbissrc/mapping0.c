
// FUNC: mapping0_free_info
void __cdecl mapping0_free_info(void *i)
{
  if ( i )
  {
    memset(i, 0, 0xC88u);
    _decoder_free(i);
  }
}

// FUNC: mapping0_pack
void __cdecl mapping0_pack(vorbis_info *vi, _DWORD *vm, oggpack_buffer *opb)
{
  int v3; // ebx
  unsigned int *v4; // edi
  int channels; // ecx
  int v6; // eax
  unsigned int i; // ecx
  int v8; // eax
  int v9; // ecx
  unsigned int j; // eax
  int v11; // edi
  unsigned int *v12; // ebx
  int v13; // ebx
  unsigned int *v14; // edi

  if ( (int)*vm <= 1 )
  {
    oggpack_write(opb, 0, 1);
  }
  else
  {
    oggpack_write(opb, 1u, 1);
    oggpack_write(opb, *vm - 1, 4);
  }
  if ( (int)vm[289] <= 0 )
  {
    oggpack_write(opb, 0, 1);
  }
  else
  {
    oggpack_write(opb, 1u, 1);
    oggpack_write(opb, vm[289] - 1, 8);
    v3 = 0;
    if ( (int)vm[289] > 0 )
    {
      v4 = vm + 546;
      do
      {
        channels = vi->channels;
        v6 = 0;
        if ( channels )
        {
          for ( i = channels - 1; i; i >>= 1 )
            ++v6;
        }
        oggpack_write(opb, *(v4 - 256), v6);
        v8 = vi->channels;
        v9 = 0;
        if ( v8 )
        {
          for ( j = v8 - 1; j; j >>= 1 )
            ++v9;
        }
        oggpack_write(opb, *v4, v9);
        ++v3;
        ++v4;
      }
      while ( v3 < vm[289] );
    }
  }
  oggpack_write(opb, 0, 2);
  if ( (int)*vm > 1 )
  {
    v11 = 0;
    if ( vi->channels > 0 )
    {
      v12 = vm + 1;
      do
      {
        oggpack_write(opb, *v12, 4);
        ++v11;
        ++v12;
      }
      while ( v11 < vi->channels );
    }
  }
  v13 = 0;
  if ( (int)*vm > 0 )
  {
    v14 = vm + 273;
    do
    {
      oggpack_write(opb, 0, 8);
      oggpack_write(opb, *(v14 - 16), 8);
      oggpack_write(opb, *v14, 8);
      ++v13;
      ++v14;
    }
    while ( v13 < *vm );
  }
}
