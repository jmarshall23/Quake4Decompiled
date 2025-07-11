
// FUNC: public: void __thiscall idSoundFade::Clear(void)
void __thiscall idSoundFade::Clear(idSoundFade *this)
{
  this->fadeStart44kHz = 0;
  this->fadeEnd44kHz = 0;
  this->fadeStartVolume = 1.0;
  this->fadeEndVolume = 1.0;
}

// FUNC: public: float __thiscall idSoundFade::FadeDbAt44kHz(int)
double __thiscall idSoundFade::FadeDbAt44kHz(idSoundFade *this, int current44kHz)
{
  int fadeEnd44kHz; // edx

  fadeEnd44kHz = this->fadeEnd44kHz;
  if ( current44kHz >= fadeEnd44kHz )
    return this->fadeEndVolume;
  if ( current44kHz <= this->fadeStart44kHz )
    return this->fadeStartVolume;
  return (double)(current44kHz - this->fadeStart44kHz)
       / (double)(fadeEnd44kHz - this->fadeStart44kHz)
       * (this->fadeEndVolume - this->fadeStartVolume)
       + this->fadeStartVolume;
}

// FUNC: public: void __thiscall idSoundChannel::Stop(void)
void __thiscall idSoundChannel::Stop(idSoundChannel *this)
{
  idSampleDecoder *decoder; // eax

  decoder = this->decoder;
  this->triggerState = 0;
  if ( decoder )
  {
    idSampleDecoder::Free(decoder);
    this->decoder = 0;
  }
}

// FUNC: public: void __thiscall idSoundChannel::ALStop(void)
void __thiscall idSoundChannel::ALStop(idSoundChannel *this)
{
  if ( idSoundSystemLocal::useOpenAL )
  {
    if ( this->openalSource != -1 && qalIsSource(this->openalSource) )
    {
      qalSourceStop(this->openalSource);
      qalSourcei(this->openalSource, 4105, 0);
      idSoundSystemLocal::FreeOpenALSource(&soundSystemLocal, this->openalSource);
    }
    if ( this->openalStreamingBuffer[0] )
    {
      if ( this->openalStreamingBuffer[1] )
      {
        if ( this->openalStreamingBuffer[2] )
        {
          qalGetError();
          qalDeleteBuffers(3u, this->openalStreamingBuffer);
          if ( !qalGetError() )
          {
            this->openalStreamingBuffer[2] = 0;
            this->openalStreamingBuffer[1] = 0;
            this->openalStreamingBuffer[0] = 0;
          }
        }
      }
    }
    if ( this->lastopenalStreamingBuffer[0] && this->lastopenalStreamingBuffer[1] && this->lastopenalStreamingBuffer[2] )
    {
      qalGetError();
      qalDeleteBuffers(3u, this->lastopenalStreamingBuffer);
      if ( !qalGetError() )
      {
        this->lastopenalStreamingBuffer[2] = 0;
        this->lastopenalStreamingBuffer[1] = 0;
        this->lastopenalStreamingBuffer[0] = 0;
      }
    }
  }
}

// FUNC: public: void __thiscall idSoundEmitterLocal::ClearPortalArea(void)
void __thiscall idSoundEmitterLocal::ClearPortalArea(idSoundEmitterLocal *this)
{
  this->lastValidPortalArea = -1;
}

// FUNC: public: void __thiscall idSoundEmitterLocal::OverrideParms(struct soundShaderParms_t const *,struct soundShaderParms_t const *,struct soundShaderParms_t *)
void __thiscall idSoundEmitterLocal::OverrideParms(
        idSoundEmitterLocal *this,
        const soundShaderParms_t *base,
        const soundShaderParms_t *over,
        soundShaderParms_t *out)
{
  float minDistance; // eax
  float maxDistance; // eax
  float shakes; // eax
  float volume; // eax
  float frequencyShift; // eax
  int soundClass; // eax

  if ( over )
  {
    if ( over->minDistance == 0.0 )
      minDistance = base->minDistance;
    else
      minDistance = over->minDistance;
    out->minDistance = minDistance;
    if ( over->maxDistance == 0.0 )
      maxDistance = base->maxDistance;
    else
      maxDistance = over->maxDistance;
    out->maxDistance = maxDistance;
    if ( over->shakes == 0.0 )
      shakes = base->shakes;
    else
      shakes = over->shakes;
    out->shakes = shakes;
    if ( over->volume == 0.0 )
      volume = base->volume;
    else
      volume = over->volume;
    out->volume = volume;
    if ( over->frequencyShift == 0.0 )
      frequencyShift = base->frequencyShift;
    else
      frequencyShift = over->frequencyShift;
    out->frequencyShift = frequencyShift;
    soundClass = over->soundClass;
    if ( !soundClass )
      soundClass = base->soundClass;
    out->soundClass = soundClass;
    out->soundShaderFlags = over->soundShaderFlags | base->soundShaderFlags;
  }
  else
  {
    qmemcpy(out, base, sizeof(soundShaderParms_t));
  }
}

// FUNC: public: void __thiscall idSoundEmitterLocal::CheckForCompletion(int)
void __thiscall idSoundEmitterLocal::CheckForCompletion(idSoundEmitterLocal *this, int current44kHzTime)
{
  bool v3; // zf
  idSampleDecoder **p_decoder; // esi
  int v5; // eax
  idSampleDecoder *v6; // eax
  bool hasActive; // [esp+7h] [ebp-9h]
  int length; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]

  v3 = !this->playing;
  hasActive = 0;
  this->hasShakes = 0;
  if ( v3 )
  {
LABEL_17:
    v3 = this->removeStatus == REMOVE_STATUS_WAITSAMPLEFINISHED;
    this->playing = 0;
    if ( v3 )
      this->removeStatus = REMOVE_STATUS_SAMPLEFINISHED;
    return;
  }
  p_decoder = &this->channels[0].decoder;
  v9 = 8;
  do
  {
    if ( !*((_BYTE *)p_decoder - 64) || !*(p_decoder - 1) )
      goto LABEL_15;
    if ( (*(_BYTE *)(p_decoder - 9) & 0x20) != 0 )
    {
LABEL_10:
      if ( *p_decoder && (*p_decoder)->GetLastDecodeTime(*p_decoder) < current44kHzTime - 256000 )
        (*p_decoder)->ClearDecoder(*p_decoder);
      hasActive = 1;
      if ( *((float *)p_decoder - 10) > 0.0 )
        this->hasShakes = 1;
      goto LABEL_15;
    }
    v5 = idSoundSample::LengthIn44kHzSamples((idSoundSample *)*(p_decoder - 4));
    length = v5;
    if ( (*(p_decoder - 4))[11].__vftable == (idSampleDecoder_vtbl *)2 )
    {
      v5 /= 2;
      length = v5;
    }
    if ( p_decoder[22] )
    {
      if ( (double)length >= *((float *)p_decoder + 24) )
        goto LABEL_10;
    }
    else if ( (int)*(p_decoder - 15) + v5 >= current44kHzTime )
    {
      goto LABEL_10;
    }
    v6 = *p_decoder;
    v3 = *p_decoder == 0;
    *((_BYTE *)p_decoder - 64) = 0;
    if ( !v3 )
    {
      idSampleDecoder::Free(v6);
      *p_decoder = 0;
    }
    idSoundChannel::ALStop((idSoundChannel *)(p_decoder - 16));
LABEL_15:
    p_decoder += 41;
    --v9;
  }
  while ( v9 );
  if ( !hasActive )
    goto LABEL_17;
}

// FUNC: public: virtual void __thiscall idSoundEmitterLocal::ModifySound(int,struct soundShaderParms_t const *)
void __thiscall idSoundEmitterLocal::ModifySound(
        idSoundEmitterLocal *this,
        int channel,
        const soundShaderParms_t *parms)
{
  soundShaderParms_t *p_parms; // esi
  int parmsa; // [esp+18h] [ebp+8h]

  if ( !parms )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idSoundEmitterLocal::ModifySound: NULL parms");
  if ( this->worldId && soundSystemLocal.writeDemo )
  {
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 6);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, this->index);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, channel);
    soundSystemLocal.writeDemo->Write(soundSystemLocal.writeDemo, parms, 40);
  }
  p_parms = &this->channels[0].parms;
  parmsa = 8;
  do
  {
    if ( LOBYTE(p_parms[-1].wetLevel) && (!channel || LODWORD(p_parms[1].volume) == channel) )
      idSoundEmitterLocal::OverrideParms(this, p_parms, parms, p_parms);
    p_parms = (soundShaderParms_t *)((char *)p_parms + 164);
    --parmsa;
  }
  while ( parmsa );
}

// FUNC: public: virtual bool __thiscall idSoundEmitterLocal::CurrentlyPlaying(int)const
char __thiscall idSoundEmitterLocal::CurrentlyPlaying(idSoundEmitterLocal *this, int channel)
{
  idSoundChannel *channels; // eax
  int v3; // edx

  channels = this->channels;
  v3 = 0;
  while ( channel && channels->triggerChannel != channel || !channels->triggerState )
  {
    ++v3;
    ++channels;
    if ( v3 >= 8 )
      return 0;
  }
  return 1;
}

// FUNC: public: void __thiscall idSoundChannel::Clear(void)
void __thiscall idSoundChannel::Clear(idSoundChannel *this)
{
  idSampleDecoder *decoder; // eax

  decoder = this->decoder;
  this->triggerState = 0;
  if ( decoder )
  {
    idSampleDecoder::Free(decoder);
    this->decoder = 0;
  }
  this->soundShader = 0;
  this->lastVolume = 0.0;
  this->triggerChannel = 0;
  this->channelFade.fadeStart44kHz = 0;
  this->channelFade.fadeEnd44kHz = 0;
  this->channelFade.fadeStartVolume = 1.0;
  this->channelFade.fadeEndVolume = 1.0;
  this->diversity = 0.0;
  this->leadinSample = 0;
  this->choice = 0;
  this->trigger44kHzTime = 0;
  this->lastV[0] = 0.0;
  this->lastV[1] = 0.0;
  this->lastV[2] = 0.0;
  this->lastV[3] = 0.0;
  this->lastV[4] = 0.0;
  this->lastV[5] = 0.0;
  this->parms.minDistance = 0.0;
  this->parms.maxDistance = 0.0;
  this->parms.volume = 0.0;
  this->parms.attenuatedVolume = 0.0;
  this->parms.shakes = 0.0;
  this->parms.soundShaderFlags = 0;
  this->parms.soundClass = 0;
  this->parms.frequencyShift = 0.0;
  this->parms.wetLevel = 0.0;
  this->parms.dryLevel = 0.0;
  this->triggered = 0;
  this->openalStreamingOffset = 0;
  this->openalStreamingBuffer[0] = 0;
  this->openalStreamingBuffer[1] = 0;
  this->openalStreamingBuffer[2] = 0;
  this->lastopenalStreamingBuffer[0] = 0;
  this->lastopenalStreamingBuffer[1] = 0;
  this->lastopenalStreamingBuffer[2] = 0;
  this->elapsedShift44kHzTime = 0.0;
  this->lastShift44kHzTime = 0;
  this->openalSource = -1;
  this->lastFrequencyShift = 1.0;
  this->parms.frequencyShift = 1.0;
}

// FUNC: public: void __thiscall idSoundEmitterLocal::Clear(void)
void __thiscall idSoundEmitterLocal::Clear(idSoundEmitterLocal *this)
{
  idSoundChannel *channels; // edi
  int v3; // ebx

  channels = this->channels;
  v3 = 8;
  do
  {
    idSoundChannel::ALStop(channels);
    idSoundChannel::Clear(channels++);
    --v3;
  }
  while ( v3 );
  this->removeStatus = REMOVE_STATUS_SAMPLEFINISHED;
  this->origin.z = 0.0;
  this->origin.y = 0.0;
  this->origin.x = 0.0;
  this->listenerId = -1;
  this->lastValidPortalArea = -1;
  this->realDistance = 0.0;
  this->distance = 0.0;
  this->numPortals = 0;
  this->playing = 0;
  this->hasShakes = 0;
  this->ampTime = 0;
  this->amplitude = 0.0;
  this->maxDistance = 10.0;
  this->spatializedOrigin.z = 0.0;
  this->spatializedOrigin.y = 0.0;
  this->spatializedOrigin.x = 0.0;
  this->parms.minDistance = 0.0;
  this->parms.maxDistance = 0.0;
  this->parms.volume = 0.0;
  this->parms.attenuatedVolume = 0.0;
  this->parms.shakes = 0.0;
  this->parms.soundShaderFlags = 0;
  this->parms.soundClass = 0;
  this->parms.frequencyShift = 0.0;
  this->parms.wetLevel = 0.0;
  this->parms.dryLevel = 0.0;
  this->numPortalChecks = 0;
  this->maxChannelVolume = 1.0;
  this->next = 0;
}

// FUNC: public: void __thiscall idSoundEmitterLocal::Spatialize(class idVec3,int,class idRenderWorld *)
void __thiscall idSoundEmitterLocal::Spatialize(
        idSoundEmitterLocal *this,
        idVec3 listenerPos,
        int listenerArea,
        idRenderWorld *rw)
{
  idVec3 *p_origin; // edi
  double v6; // st4
  double v7; // st7
  char v9; // c0
  int v11; // ebp
  int lastValidPortalArea; // eax
  int listenerPosa; // [esp+18h] [ebp+4h]
  idRenderWorld *rwa; // [esp+28h] [ebp+14h]

  this->maxDistance = 0.0;
  if ( this->channels[0].triggerState && this->channels[0].parms.maxDistance > 0.0 )
    this->maxDistance = this->channels[0].parms.maxDistance;
  if ( this->channels[1].triggerState && this->channels[1].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[1].parms.maxDistance;
  if ( this->channels[2].triggerState && this->channels[2].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[2].parms.maxDistance;
  if ( this->channels[3].triggerState && this->channels[3].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[3].parms.maxDistance;
  if ( this->channels[4].triggerState && this->channels[4].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[4].parms.maxDistance;
  if ( this->channels[5].triggerState && this->channels[5].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[5].parms.maxDistance;
  if ( this->channels[6].triggerState && this->channels[6].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[6].parms.maxDistance;
  if ( this->channels[7].triggerState && this->channels[7].parms.maxDistance > (double)this->maxDistance )
    this->maxDistance = this->channels[7].parms.maxDistance;
  p_origin = &this->origin;
  v6 = (listenerPos.z - this->origin.z) * (listenerPos.z - this->origin.z)
     + (listenerPos.y - this->origin.y) * (listenerPos.y - this->origin.y)
     + (listenerPos.x - this->origin.x) * (listenerPos.x - this->origin.x);
  *(float *)&listenerPosa = v6;
  v7 = v6
     * ((1.5 - 0.5
             * v6
             * COERCE_FLOAT(1597463007 - (listenerPosa >> 1))
             * COERCE_FLOAT(1597463007 - (listenerPosa >> 1)))
      * COERCE_FLOAT(1597463007 - (listenerPosa >> 1)));
  this->realDistance = v7;
  if ( !v9 )
  {
    this->distance = v7;
    return;
  }
  this->distance = this->maxDistance;
  if ( listenerArea != -1 )
  {
    if ( rw )
    {
      v11 = rw->PointInArea(rw, &this->origin);
      if ( v11 == -1 )
      {
        lastValidPortalArea = this->lastValidPortalArea;
        if ( lastValidPortalArea == -1 )
        {
LABEL_31:
          this->distance = this->realDistance;
          this->spatializedOrigin.x = p_origin->x;
          this->spatializedOrigin.y = this->origin.y;
          this->spatializedOrigin.z = this->origin.z;
          this->numPortals = 0;
          return;
        }
        if ( lastValidPortalArea >= 0 )
        {
          rwa = (idRenderWorld *)this->lastValidPortalArea;
          if ( (int)rwa < rw->NumAreas(rw) )
            v11 = (int)rwa;
        }
      }
      this->lastValidPortalArea = v11;
      if ( v11 == listenerArea )
        goto LABEL_31;
      idSoundSystemLocal::ResolveOrigin(&soundSystemLocal, 0, 0, v11, 0.0, 0, &this->origin, this);
    }
    else
    {
      this->distance = v7;
      this->spatializedOrigin.x = p_origin->x;
      this->spatializedOrigin.y = this->origin.y;
      this->spatializedOrigin.z = this->origin.z;
      this->numPortals = 0;
    }
  }
}

// FUNC: public: virtual void __thiscall idSoundEmitterLocal::UpdateEmitter(class idVec3 const &,class idVec3 const &,int,struct soundShaderParms_t const *)
void __thiscall idSoundEmitterLocal::UpdateEmitter(
        idSoundEmitterLocal *this,
        const idVec3 *origin,
        const idVec3 *velocity,
        int listenerId,
        const soundShaderParms_t *parms)
{
  if ( !parms )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idSoundEmitterLocal::UpdateEmitter: NULL parms");
  if ( this->worldId && soundSystemLocal.writeDemo )
  {
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 4);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, this->index);
    soundSystemLocal.writeDemo->WriteVec3(soundSystemLocal.writeDemo, origin);
    soundSystemLocal.writeDemo->WriteVec3(soundSystemLocal.writeDemo, velocity);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, listenerId);
    soundSystemLocal.writeDemo->Write(soundSystemLocal.writeDemo, parms, 40);
  }
  Sys_EnterCriticalSection(0);
  this->origin = *origin;
  this->listenerId = listenerId;
  qmemcpy(&this->parms, parms, sizeof(this->parms));
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: virtual int __thiscall idSoundEmitterLocal::StartSound(class idSoundShader const *,int,float,int)
const idSoundShader *__thiscall idSoundEmitterLocal::StartSound(
        idSoundEmitterLocal *this,
        const idSoundShader *shader,
        int channel,
        float diversity,
        int soundShaderFlags)
{
  int v7; // edi
  const char *v8; // eax
  const char *v9; // eax
  int v10; // ebp
  rvCommonSample *v11; // edx
  int v12; // eax
  idSoundSample **p_leadinSample; // ecx
  int v14; // ecx
  idSoundChannel *channels; // eax
  int v16; // ecx
  int *p_trigger44kHzTime; // eax
  int v18; // eax
  idSoundChannel *v19; // esi
  int v20; // ebp
  int v21; // eax
  idSampleDecoder *decoder; // eax
  int v23; // ecx
  idSoundChannel *v24; // eax
  idSoundChannel *v25; // ebp
  rvCommonSample *v27; // eax
  idSoundSample *leadinSample; // eax
  int v29; // esi
  int v30; // eax
  int v31; // esi
  idSoundSample *v32; // eax
  int integerValue; // ecx
  bool v34; // zf
  int v35; // eax
  int v36; // eax
  double v37; // st7
  int v38; // eax
  int start44kHz; // [esp+18h] [ebp-30h]
  soundShaderParms_t chanParms; // [esp+20h] [ebp-28h] BYREF
  int shadera; // [esp+4Ch] [ebp+4h]
  int shaderb; // [esp+4Ch] [ebp+4h]
  const idSoundShader *shaderc; // [esp+4Ch] [ebp+4h]
  int soundShaderFlagsa; // [esp+58h] [ebp+10h]

  if ( !shader || s_skipStartSound.internalVar->integerValue )
    return 0;
  if ( s_showStartSound.internalVar->integerValue )
  {
    v7 = *(_DWORD *)common.type;
    v8 = shader->base->GetName(shader->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(
      common.type,
      "StartSound %ims (%i,%i,%s) = ",
      soundSystemLocal.gameMsec,
      this->index,
      channel,
      v8);
  }
  if ( this->worldId && soundSystemLocal.writeDemo )
  {
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 5);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, this->index);
    v9 = shader->base->GetName(shader->base);
    idDemoFile::WriteHashString(soundSystemLocal.writeDemo, v9);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, channel);
    ((void (__thiscall *)(idDemoFile *, _DWORD))soundSystemLocal.writeDemo->WriteFloat)(
      soundSystemLocal.writeDemo,
      LODWORD(diversity));
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, soundShaderFlags);
  }
  Sys_EnterCriticalSection(0);
  ++shader->playCount;
  qmemcpy(&chanParms, &shader->parms, sizeof(chanParms));
  idSoundEmitterLocal::OverrideParms(this, &chanParms, &this->parms, &chanParms);
  chanParms.soundShaderFlags |= soundShaderFlags;
  if ( soundSystemLocal.fpa[0] )
    start44kHz = soundSystemLocal.lastAVI44kHz + 4096;
  else
    start44kHz = idSoundSystemLocal::GetCurrent44kHzTime(&soundSystemLocal) + 4096;
  shadera = shader->numEntries;
  if ( !shadera )
  {
    if ( s_showStartSound.internalVar->integerValue )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "no samples in sound shader\n");
LABEL_56:
    Sys_LeaveCriticalSection(0);
    return 0;
  }
  soundShaderFlagsa = (int)((double)shadera * diversity);
  v10 = soundShaderFlagsa;
  if ( soundShaderFlagsa < 0 || soundShaderFlagsa >= shadera )
  {
    soundShaderFlagsa = 0;
    v10 = 0;
  }
  if ( (chanParms.soundShaderFlags & 0x200) != 0 )
  {
    v11 = shader->leadins[v10];
    if ( !v11 )
      v11 = shader->entries[v10];
    v12 = 0;
    p_leadinSample = &this->channels[0].leadinSample;
    while ( *p_leadinSample != v11 )
    {
      ++v12;
      p_leadinSample += 41;
      if ( v12 >= 8 )
        goto LABEL_25;
    }
    soundShaderFlagsa = (v10 + 1) % shadera;
  }
LABEL_25:
  if ( (chanParms.soundShaderFlags & 0x40) != 0 )
  {
    v14 = 0;
    channels = this->channels;
    while ( !channels->triggerState || channels->soundShader != shader )
    {
      ++v14;
      ++channels;
      if ( v14 >= 8 )
        goto LABEL_30;
    }
    if ( s_showStartSound.internalVar->integerValue )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "PLAY_ONCE not restarting\n");
    goto LABEL_56;
  }
LABEL_30:
  v16 = 0;
  p_trigger44kHzTime = &this->channels[0].trigger44kHzTime;
  do
  {
    if ( *((_BYTE *)p_trigger44kHzTime - 4)
      && (const idSoundShader *)p_trigger44kHzTime[14] == shader
      && *p_trigger44kHzTime == start44kHz )
    {
      if ( s_showStartSound.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "already started this frame\n");
      goto LABEL_56;
    }
    ++v16;
    p_trigger44kHzTime += 41;
  }
  while ( v16 < 8 );
  if ( channel )
  {
    v18 = 0;
    v19 = this->channels;
    while ( !v19->triggerState || !v19->soundShader || v19->triggerChannel != channel )
    {
      ++v18;
      ++v19;
      if ( v18 >= 8 )
        goto LABEL_50;
    }
    if ( s_showStartSound.internalVar->integerValue )
    {
      v20 = *(_DWORD *)common.type;
      v21 = (int)v19->soundShader->base->GetName(v19->soundShader->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v20 + 124))(common.type, "(override %s)", v21);
    }
    decoder = v19->decoder;
    v19->triggerState = 0;
    if ( decoder )
    {
      idSampleDecoder::Free(decoder);
      v19->decoder = 0;
    }
  }
LABEL_50:
  v23 = 0;
  v24 = this->channels;
  do
  {
    v25 = v24;
    if ( !v24->triggerState )
      break;
    ++v23;
    ++v24;
  }
  while ( v23 < 8 );
  if ( v23 == 8 )
  {
    if ( s_showStartSound.internalVar->integerValue )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "no channels available\n");
    goto LABEL_56;
  }
  v27 = shader->leadins[soundShaderFlagsa];
  if ( v27 )
    v25->leadinSample = (idSoundSample *)v27;
  else
    v25->leadinSample = (idSoundSample *)shader->entries[soundShaderFlagsa];
  leadinSample = v25->leadinSample;
  v25->choice = soundShaderFlagsa;
  if ( !leadinSample->purged
    || (v29 = Sys_Milliseconds(),
        v25->leadinSample->Load(v25->leadinSample, -1),
        v30 = Sys_Milliseconds(),
        session->TimeHitch(session, v30 - v29),
        soundSystemLocal.fpa[0]) )
  {
    v31 = start44kHz;
  }
  else
  {
    v31 = idSoundSystemLocal::GetCurrent44kHzTime(&soundSystemLocal) + 4096;
  }
  if ( s_showStartSound.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "'%s'\n",
      v25->leadinSample->name.data);
  v32 = v25->leadinSample;
  if ( v32->defaultSound )
  {
    integerValue = com_QuickLoad.internalVar->integerValue;
    if ( integerValue != 1 && integerValue != 3 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Playing default sound %s",
        v32->name.data);
  }
  v25->trigger44kHzTime = v31;
  qmemcpy(&v25->parms, &chanParms, sizeof(v25->parms));
  v34 = v25->decoder == 0;
  v25->triggered = 1;
  v25->openalStreamingOffset = 0;
  v25->soundShader = shader;
  v25->triggerChannel = channel;
  v25->lastShift44kHzTime = 0;
  v25->elapsedShift44kHzTime = 0.0;
  v25->lastFrequencyShift = 1.0;
  v25->triggerState = 1;
  if ( v34 )
    v25->decoder = idSampleDecoder::Alloc();
  this->playing = 1;
  idSoundEmitterLocal::Spatialize(
    this,
    soundSystemLocal.listenerPos,
    soundSystemLocal.listenerArea,
    soundSystemLocal.rw);
  v35 = idSoundSample::LengthIn44kHzSamples(v25->leadinSample);
  shaderb = v35;
  if ( v25->leadinSample->nChannels == 2 )
    shaderb = v35 / 2;
  v36 = v25->parms.soundShaderFlags;
  if ( (v36 & 0x20) != 0 && (v36 & 0x800) == 0 )
  {
    v37 = (double)shaderb * diversity;
    v25->trigger44kHzTime = (int)((double)v25->trigger44kHzTime - v37) & 0xFFFFFFF8;
    v38 = (int)v37;
    LOBYTE(v38) = (int)v37 & 0xF8;
    v25->openalStreamingOffset = v38;
  }
  shaderc = (const idSoundShader *)(int)((double)shaderb * 0.022675738);
  Sys_LeaveCriticalSection(0);
  if ( this->worldId && s_drawSounds.internalVar->integerValue > 1 )
  {
    chanParms.minDistance = -8.0;
    chanParms.maxDistance = -8.0;
    chanParms.volume = -8.0;
    chanParms.attenuatedVolume = 8.0;
    chanParms.shakes = 8.0;
    chanParms.soundShaderFlags = 1090519040;
    soundSystemLocal.rw->DebugBounds(
      soundSystemLocal.rw,
      &colorGreen,
      (const idBounds *)&chanParms,
      &this->origin,
      5000,
      0);
  }
  return shaderc;
}

// FUNC: public: virtual void __thiscall idSoundEmitterLocal::StopSound(int)
void __thiscall idSoundEmitterLocal::StopSound(idSoundEmitterLocal *this, int channel)
{
  idSampleDecoder **p_decoder; // esi
  idSampleDecoder *v5; // eax
  bool v6; // zf
  int channela; // [esp+14h] [ebp+4h]

  if ( s_showStartSound.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "StopSound(%i,%i)\n",
      this->index,
      channel);
  if ( this->worldId && soundSystemLocal.writeDemo )
  {
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 7);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, this->index);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, channel);
  }
  Sys_EnterCriticalSection(0);
  p_decoder = &this->channels[0].decoder;
  channela = 8;
  do
  {
    if ( *((_BYTE *)p_decoder - 64) && (!channel || *(p_decoder - 2) == (idSampleDecoder *)channel) )
    {
      v5 = *p_decoder;
      v6 = *p_decoder == 0;
      *((_BYTE *)p_decoder - 64) = 0;
      if ( !v6 )
      {
        idSampleDecoder::Free(v5);
        *p_decoder = 0;
      }
      idSoundChannel::ALStop((idSoundChannel *)(p_decoder - 16));
      *(p_decoder - 4) = 0;
      *(p_decoder - 1) = 0;
    }
    p_decoder += 41;
    --channela;
  }
  while ( channela );
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: virtual void __thiscall idSoundEmitterLocal::FadeSound(int,float,float)
void __thiscall idSoundEmitterLocal::FadeSound(idSoundEmitterLocal *this, int channel, float to, float over)
{
  int lastAVI44kHz; // edi
  int v6; // edi
  int v7; // edx
  int fadeEnd44kHz; // eax
  double fadeStartVolume; // st7
  int fadeStart44kHz; // ecx
  int v11; // eax
  double fadeEndVolume; // st7
  int v13; // ecx
  int v14; // eax
  double v15; // st7
  int v16; // ecx
  int v17; // eax
  double v18; // st7
  int v19; // ecx
  int v20; // eax
  double v21; // st7
  int v22; // ecx
  int v23; // eax
  double v24; // st7
  int v25; // ecx
  int v26; // eax
  double v27; // st7
  int v28; // ecx
  int v29; // eax
  double v30; // st7
  int v31; // ecx
  float toa; // [esp+20h] [ebp+8h]

  if ( s_showStartSound.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "FadeSound(%i,%i,%f,%f )\n",
      this->index,
      channel,
      to,
      over);
  if ( this->worldId )
  {
    if ( soundSystemLocal.writeDemo )
    {
      soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
      soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 8);
      soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, this->index);
      soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, channel);
      ((void (__thiscall *)(idDemoFile *, _DWORD))soundSystemLocal.writeDemo->WriteFloat)(
        soundSystemLocal.writeDemo,
        LODWORD(to));
      ((void (__thiscall *)(idDemoFile *, _DWORD))soundSystemLocal.writeDemo->WriteFloat)(
        soundSystemLocal.writeDemo,
        LODWORD(over));
    }
    toa = idMath::dBToScale(to);
    if ( soundSystemLocal.fpa[0] )
      lastAVI44kHz = soundSystemLocal.lastAVI44kHz;
    else
      lastAVI44kHz = idSoundSystemLocal::GetCurrent44kHzTime(&soundSystemLocal);
    v6 = lastAVI44kHz + 4096;
    v7 = idSoundSystemLocal::MillisecondsToSamples(&soundSystemLocal, (int)(over * 1000.0));
    if ( this->channels[0].triggerState
      && (!channel || this->channels[0].triggerChannel == channel)
      && (this->channels[0].channelFade.fadeEndVolume != toa
       || this->channels[0].channelFade.fadeEnd44kHz - this->channels[0].channelFade.fadeStart44kHz != v7) )
    {
      fadeEnd44kHz = this->channels[0].channelFade.fadeEnd44kHz;
      if ( v6 < fadeEnd44kHz )
      {
        fadeStart44kHz = this->channels[0].channelFade.fadeStart44kHz;
        if ( v6 <= fadeStart44kHz )
          fadeStartVolume = this->channels[0].channelFade.fadeStartVolume;
        else
          fadeStartVolume = (double)(v6 - fadeStart44kHz)
                          / (double)(fadeEnd44kHz - fadeStart44kHz)
                          * (this->channels[0].channelFade.fadeEndVolume - this->channels[0].channelFade.fadeStartVolume)
                          + this->channels[0].channelFade.fadeStartVolume;
      }
      else
      {
        fadeStartVolume = this->channels[0].channelFade.fadeEndVolume;
      }
      this->channels[0].channelFade.fadeStartVolume = fadeStartVolume;
      this->channels[0].channelFade.fadeStart44kHz = v6;
      this->channels[0].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[0].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[1].triggerState
      && (!channel || this->channels[1].triggerChannel == channel)
      && (this->channels[1].channelFade.fadeEndVolume != toa
       || this->channels[1].channelFade.fadeEnd44kHz - this->channels[1].channelFade.fadeStart44kHz != v7) )
    {
      v11 = this->channels[1].channelFade.fadeEnd44kHz;
      if ( v6 < v11 )
      {
        v13 = this->channels[1].channelFade.fadeStart44kHz;
        if ( v6 <= v13 )
          fadeEndVolume = this->channels[1].channelFade.fadeStartVolume;
        else
          fadeEndVolume = (double)(v6 - v13)
                        / (double)(v11 - v13)
                        * (this->channels[1].channelFade.fadeEndVolume - this->channels[1].channelFade.fadeStartVolume)
                        + this->channels[1].channelFade.fadeStartVolume;
      }
      else
      {
        fadeEndVolume = this->channels[1].channelFade.fadeEndVolume;
      }
      this->channels[1].channelFade.fadeStartVolume = fadeEndVolume;
      this->channels[1].channelFade.fadeStart44kHz = v6;
      this->channels[1].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[1].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[2].triggerState
      && (!channel || this->channels[2].triggerChannel == channel)
      && (this->channels[2].channelFade.fadeEndVolume != toa
       || this->channels[2].channelFade.fadeEnd44kHz - this->channels[2].channelFade.fadeStart44kHz != v7) )
    {
      v14 = this->channels[2].channelFade.fadeEnd44kHz;
      if ( v6 < v14 )
      {
        v16 = this->channels[2].channelFade.fadeStart44kHz;
        if ( v6 <= v16 )
          v15 = this->channels[2].channelFade.fadeStartVolume;
        else
          v15 = (double)(v6 - v16)
              / (double)(v14 - v16)
              * (this->channels[2].channelFade.fadeEndVolume - this->channels[2].channelFade.fadeStartVolume)
              + this->channels[2].channelFade.fadeStartVolume;
      }
      else
      {
        v15 = this->channels[2].channelFade.fadeEndVolume;
      }
      this->channels[2].channelFade.fadeStartVolume = v15;
      this->channels[2].channelFade.fadeStart44kHz = v6;
      this->channels[2].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[2].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[3].triggerState
      && (!channel || this->channels[3].triggerChannel == channel)
      && (this->channels[3].channelFade.fadeEndVolume != toa
       || this->channels[3].channelFade.fadeEnd44kHz - this->channels[3].channelFade.fadeStart44kHz != v7) )
    {
      v17 = this->channels[3].channelFade.fadeEnd44kHz;
      if ( v6 < v17 )
      {
        v19 = this->channels[3].channelFade.fadeStart44kHz;
        if ( v6 <= v19 )
          v18 = this->channels[3].channelFade.fadeStartVolume;
        else
          v18 = (double)(v6 - v19)
              / (double)(v17 - v19)
              * (this->channels[3].channelFade.fadeEndVolume - this->channels[3].channelFade.fadeStartVolume)
              + this->channels[3].channelFade.fadeStartVolume;
      }
      else
      {
        v18 = this->channels[3].channelFade.fadeEndVolume;
      }
      this->channels[3].channelFade.fadeStartVolume = v18;
      this->channels[3].channelFade.fadeStart44kHz = v6;
      this->channels[3].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[3].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[4].triggerState
      && (!channel || this->channels[4].triggerChannel == channel)
      && (this->channels[4].channelFade.fadeEndVolume != toa
       || this->channels[4].channelFade.fadeEnd44kHz - this->channels[4].channelFade.fadeStart44kHz != v7) )
    {
      v20 = this->channels[4].channelFade.fadeEnd44kHz;
      if ( v6 < v20 )
      {
        v22 = this->channels[4].channelFade.fadeStart44kHz;
        if ( v6 <= v22 )
          v21 = this->channels[4].channelFade.fadeStartVolume;
        else
          v21 = (double)(v6 - v22)
              / (double)(v20 - v22)
              * (this->channels[4].channelFade.fadeEndVolume - this->channels[4].channelFade.fadeStartVolume)
              + this->channels[4].channelFade.fadeStartVolume;
      }
      else
      {
        v21 = this->channels[4].channelFade.fadeEndVolume;
      }
      this->channels[4].channelFade.fadeStartVolume = v21;
      this->channels[4].channelFade.fadeStart44kHz = v6;
      this->channels[4].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[4].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[5].triggerState
      && (!channel || this->channels[5].triggerChannel == channel)
      && (this->channels[5].channelFade.fadeEndVolume != toa
       || this->channels[5].channelFade.fadeEnd44kHz - this->channels[5].channelFade.fadeStart44kHz != v7) )
    {
      v23 = this->channels[5].channelFade.fadeEnd44kHz;
      if ( v6 < v23 )
      {
        v25 = this->channels[5].channelFade.fadeStart44kHz;
        if ( v6 <= v25 )
          v24 = this->channels[5].channelFade.fadeStartVolume;
        else
          v24 = (double)(v6 - v25)
              / (double)(v23 - v25)
              * (this->channels[5].channelFade.fadeEndVolume - this->channels[5].channelFade.fadeStartVolume)
              + this->channels[5].channelFade.fadeStartVolume;
      }
      else
      {
        v24 = this->channels[5].channelFade.fadeEndVolume;
      }
      this->channels[5].channelFade.fadeStartVolume = v24;
      this->channels[5].channelFade.fadeStart44kHz = v6;
      this->channels[5].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[5].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[6].triggerState
      && (!channel || this->channels[6].triggerChannel == channel)
      && (this->channels[6].channelFade.fadeEndVolume != toa
       || this->channels[6].channelFade.fadeEnd44kHz - this->channels[6].channelFade.fadeStart44kHz != v7) )
    {
      v26 = this->channels[6].channelFade.fadeEnd44kHz;
      if ( v6 < v26 )
      {
        v28 = this->channels[6].channelFade.fadeStart44kHz;
        if ( v6 <= v28 )
          v27 = this->channels[6].channelFade.fadeStartVolume;
        else
          v27 = (double)(v6 - v28)
              / (double)(v26 - v28)
              * (this->channels[6].channelFade.fadeEndVolume - this->channels[6].channelFade.fadeStartVolume)
              + this->channels[6].channelFade.fadeStartVolume;
      }
      else
      {
        v27 = this->channels[6].channelFade.fadeEndVolume;
      }
      this->channels[6].channelFade.fadeStartVolume = v27;
      this->channels[6].channelFade.fadeStart44kHz = v6;
      this->channels[6].channelFade.fadeEnd44kHz = v7 + v6;
      this->channels[6].channelFade.fadeEndVolume = toa;
    }
    if ( this->channels[7].triggerState
      && (!channel || this->channels[7].triggerChannel == channel)
      && (this->channels[7].channelFade.fadeEndVolume != toa
       || this->channels[7].channelFade.fadeEnd44kHz - this->channels[7].channelFade.fadeStart44kHz != v7) )
    {
      v29 = this->channels[7].channelFade.fadeEnd44kHz;
      if ( v6 < v29 )
      {
        v31 = this->channels[7].channelFade.fadeStart44kHz;
        if ( v6 <= v31 )
          v30 = this->channels[7].channelFade.fadeStartVolume;
        else
          v30 = (double)(v6 - v31)
              / (double)(v29 - v31)
              * (this->channels[7].channelFade.fadeEndVolume - this->channels[7].channelFade.fadeStartVolume)
              + this->channels[7].channelFade.fadeStartVolume;
      }
      else
      {
        v30 = this->channels[7].channelFade.fadeEndVolume;
      }
      this->channels[7].channelFade.fadeStartVolume = v30;
      this->channels[7].channelFade.fadeStart44kHz = v6;
      this->channels[7].channelFade.fadeEnd44kHz = v6 + v7;
      this->channels[7].channelFade.fadeEndVolume = toa;
    }
  }
}

// FUNC: public: virtual float __thiscall idSoundEmitterLocal::CurrentAmplitude(void)
double __thiscall idSoundEmitterLocal::CurrentAmplitude(idSoundEmitterLocal *this)
{
  double result; // st7
  int Current44kHzTime; // eax

  if ( s_constantAmplitude.internalVar->floatValue >= 0.0 )
    return s_constantAmplitude.internalVar->floatValue;
  if ( this->removeStatus > REMOVE_STATUS_WAITSAMPLEFINISHED )
    return 0.0;
  Current44kHzTime = idSoundSystemLocal::GetCurrent44kHzTime(&soundSystemLocal);
  if ( this->ampTime == Current44kHzTime )
    return this->amplitude;
  this->ampTime = Current44kHzTime;
  result = idSoundSystemLocal::FindAmplitude(&soundSystemLocal, this, Current44kHzTime, 0, 0, 0);
  this->amplitude = result;
  return result;
}

// FUNC: public: __thiscall idSoundChannel::idSoundChannel(void)
void __thiscall idSoundChannel::idSoundChannel(idSoundChannel *this)
{
  this->decoder = 0;
  idSoundChannel::Clear(this);
}

// FUNC: public: __thiscall idSoundChannel::~idSoundChannel(void)
// attributes: thunk
void __thiscall idSoundChannel::~idSoundChannel(idSoundChannel *this)
{
  idSoundChannel::Clear(this);
}

// FUNC: public: __thiscall idSoundEmitterLocal::idSoundEmitterLocal(void)
void __thiscall idSoundEmitterLocal::idSoundEmitterLocal(idSoundEmitterLocal *this)
{
  this->__vftable = (idSoundEmitterLocal_vtbl *)&idSoundEmitterLocal::`vftable';
  `eh vector constructor iterator'(
    this->channels,
    0xA4u,
    8,
    (void (__thiscall *)(void *))idSoundChannel::idSoundChannel,
    (void (__thiscall *)(void *))idSoundChannel::~idSoundChannel);
  this->worldId = 0;
  idSoundEmitterLocal::Clear(this);
}

// FUNC: public: virtual __thiscall idSoundEmitterLocal::~idSoundEmitterLocal(void)
void __thiscall idSoundEmitterLocal::~idSoundEmitterLocal(idSoundEmitterLocal *this)
{
  this->__vftable = (idSoundEmitterLocal_vtbl *)&idSoundEmitterLocal::`vftable';
  idSoundEmitterLocal::Clear(this);
  `eh vector destructor iterator'(
    this->channels,
    0xA4u,
    8,
    (void (__thiscall *)(void *))idSoundChannel::~idSoundChannel);
  this->__vftable = (idSoundEmitterLocal_vtbl *)&idSoundEmitter::`vftable';
}
