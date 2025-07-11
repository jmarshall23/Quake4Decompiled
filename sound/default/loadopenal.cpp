
// FUNC: bool __cdecl LoadOpenAL(void)
char __cdecl LoadOpenAL()
{
  if ( hOpenAL )
    return 1;
  if ( bOpenALFailedLoad )
    return 0;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "...initializing QAL\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "...calling LoadLibrary( '%s' ): ",
    "OpenAL32.dll");
  hOpenAL = LoadLibraryA("OpenAL32.dll");
  if ( !hOpenAL )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
    bOpenALFailedLoad = 1;
    return 0;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
  qalGetError = GetProcAddress(hOpenAL, "alGetError");
  qalIsSource = (char (__cdecl *)(unsigned int))GetProcAddress(hOpenAL, "alIsSource");
  qalGenBuffers = (void (__cdecl *)(unsigned int, unsigned int *))GetProcAddress(hOpenAL, "alGenBuffers");
  qalSourceStop = (void (__cdecl *)(unsigned int))GetProcAddress(hOpenAL, "alSourceStop");
  qalGetSourcei = (void (__cdecl *)(unsigned int, int, int *))GetProcAddress(hOpenAL, "alGetSourcei");
  qalGetInteger = (int (__cdecl *)(int))GetProcAddress(hOpenAL, "alGetInteger");
  qalBufferData = (void (__cdecl *)(unsigned int, int, void *, unsigned int, unsigned int))GetProcAddress(
                                                                                             hOpenAL,
                                                                                             "alBufferData");
  qalDeleteBuffers = (void (__cdecl *)(unsigned int, unsigned int *))GetProcAddress(hOpenAL, "alDeleteBuffers");
  qalIsExtensionPresent = (char (__cdecl *)(unsigned __int8 *))GetProcAddress(hOpenAL, "alIsExtensionPresent");
  qalDeleteSources = (void (__cdecl *)(unsigned int, unsigned int *))GetProcAddress(hOpenAL, "alDeleteSources");
  qalGetEnumValue = (int (__cdecl *)(unsigned __int8 *))GetProcAddress(hOpenAL, "alGetEnumValue");
  qalGetProcAddress = (void *(__cdecl *)(unsigned __int8 *))GetProcAddress(hOpenAL, "alGetProcAddress");
  qalListenerfv = (void (__cdecl *)(int, float *))GetProcAddress(hOpenAL, "alListenerfv");
  qalSourceQueueBuffers = (void (__cdecl *)(unsigned int, unsigned int, unsigned int *))GetProcAddress(
                                                                                          hOpenAL,
                                                                                          "alSourceQueueBuffers");
  qalSourcei = (void (__cdecl *)(unsigned int, int, int))GetProcAddress(hOpenAL, "alSourcei");
  qalListenerf = (void (__cdecl *)(int, float))GetProcAddress(hOpenAL, "alListenerf");
  qalcCloseDevice = (void (__cdecl *)(struct ALCdevice_struct *))GetProcAddress(hOpenAL, "alcCloseDevice");
  qalIsBuffer = (char (__cdecl *)(unsigned int))GetProcAddress(hOpenAL, "alIsBuffer");
  qalSource3f = (void (__cdecl *)(unsigned int, int, float, float, float))GetProcAddress(hOpenAL, "alSource3f");
  qalGenSources = (void (__cdecl *)(unsigned int, unsigned int *))GetProcAddress(hOpenAL, "alGenSources");
  qalSourcef = (void (__cdecl *)(unsigned int, int, float))GetProcAddress(hOpenAL, "alSourcef");
  qalSourceUnqueueBuffers = (void (__cdecl *)(unsigned int, unsigned int, unsigned int *))GetProcAddress(
                                                                                            hOpenAL,
                                                                                            "alSourceUnqueueBuffers");
  qalSourcePlay = (void (__cdecl *)(unsigned int))GetProcAddress(hOpenAL, "alSourcePlay");
  qalSourcePause = (void (__cdecl *)(unsigned int))GetProcAddress(hOpenAL, "alSourcePause");
  qalcOpenDevice = (struct ALCdevice_struct *(__cdecl *)(unsigned __int8 *))GetProcAddress(hOpenAL, "alcOpenDevice");
  qalcCreateContext = (struct ALCcontext_struct *(__cdecl *)(struct ALCdevice_struct *, int *))GetProcAddress(
                                                                                                 hOpenAL,
                                                                                                 "alcCreateContext");
  qalcMakeContextCurrent = (char (__cdecl *)(struct ALCcontext_struct *))GetProcAddress(
                                                                           hOpenAL,
                                                                           "alcMakeContextCurrent");
  qalcSuspendContext = (void (__cdecl *)(struct ALCcontext_struct *))GetProcAddress(hOpenAL, "alcSuspendContext");
  qalcProcessContext = (void (__cdecl *)(struct ALCcontext_struct *))GetProcAddress(hOpenAL, "alcProcessContext");
  qalcDestroyContext = (void (__cdecl *)(struct ALCcontext_struct *))GetProcAddress(hOpenAL, "alcDestroyContext");
  qalcGetString = (unsigned __int8 *(__cdecl *)(struct ALCdevice_struct *, int))GetProcAddress(hOpenAL, "alcGetString");
  qalcIsExtensionPresent = (char (__cdecl *)(struct ALCdevice_struct *, unsigned __int8 *))GetProcAddress(
                                                                                             hOpenAL,
                                                                                             "alcIsExtensionPresent");
  qalcGetProcAddress = (void *(__cdecl *)(struct ALCdevice_struct *, unsigned __int8 *))GetProcAddress(
                                                                                          hOpenAL,
                                                                                          "alcGetProcAddress");
  qalcGetEnumValue = (int (__cdecl *)(struct ALCdevice_struct *, unsigned __int8 *))GetProcAddress(
                                                                                      hOpenAL,
                                                                                      "alcGetEnumValue");
  return 1;
}

// FUNC: void __cdecl FreeOpenAL(void)
void __cdecl FreeOpenAL()
{
  if ( !bOpenALFailedLoad )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...shutting down QAL\n");
    if ( hOpenAL )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "...unloading OpenAL DLL\n");
      FreeLibrary(hOpenAL);
    }
    hOpenAL = 0;
    qalGetError = 0;
    qalIsSource = 0;
    qalGenBuffers = 0;
    qalSourceStop = 0;
    qalGetSourcei = 0;
    qalGetInteger = 0;
    qalBufferData = 0;
    qalDeleteBuffers = 0;
    qalIsExtensionPresent = 0;
    qalDeleteSources = 0;
    qalGetEnumValue = 0;
    qalGetProcAddress = 0;
    qalListenerfv = 0;
    qalSourceQueueBuffers = 0;
    qalSourcei = 0;
    qalListenerf = 0;
    qalcCloseDevice = 0;
    qalIsBuffer = 0;
    qalSource3f = 0;
    qalGenSources = 0;
    qalSourcef = 0;
    qalSourceUnqueueBuffers = 0;
    qalSourcePlay = 0;
    qalSourcePause = 0;
    qalcOpenDevice = 0;
    qalcCreateContext = 0;
    qalcMakeContextCurrent = 0;
    qalcSuspendContext = 0;
    qalcProcessContext = 0;
    qalcDestroyContext = 0;
    qalcGetString = 0;
    qalcIsExtensionPresent = 0;
    qalcGetProcAddress = 0;
    qalcGetEnumValue = 0;
  }
}
