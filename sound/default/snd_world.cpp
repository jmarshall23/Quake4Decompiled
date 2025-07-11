
// FUNC: public: virtual void __thiscall idSoundSystemLocal::StartWritingDemo(int,class idDemoFile *)
void __thiscall idSoundSystemLocal::StartWritingDemo(idSoundSystemLocal *this, int worldId, idDemoFile *demo)
{
  this->writeDemo = demo;
  soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
  soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 0);
  this->WriteToSaveGame(this, worldId, this->writeDemo);
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::StopWritingDemo(int)
void __thiscall idSoundSystemLocal::StopWritingDemo(idSoundSystemLocal *this, int worldId)
{
  this->writeDemo = 0;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::ResetListener(void)
void __thiscall idSoundSystemLocal::ResetListener(idSoundSystemLocal *this)
{
  Sys_EnterCriticalSection(0);
  this->listenerArea = 0;
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: void __thiscall idSoundSystemLocal::WriteToSaveGameSoundShaderParams(class idFile *,struct soundShaderParms_t *)
void __thiscall idSoundSystemLocal::WriteToSaveGameSoundShaderParams(
        idSoundSystemLocal *this,
        idFile *saveGame,
        soundShaderParms_t *params)
{
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->minDistance));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->maxDistance));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->volume));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->attenuatedVolume));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->shakes));
  saveGame->WriteInt(saveGame, params->soundShaderFlags);
  saveGame->WriteInt(saveGame, params->soundClass);
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->frequencyShift));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->wetLevel));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(params->dryLevel));
}

// FUNC: public: void __thiscall idSoundSystemLocal::WriteToSaveGameSoundChannel(class idFile *,class idSoundChannel *)
void __thiscall idSoundSystemLocal::WriteToSaveGameSoundChannel(
        idSoundSystemLocal *this,
        idFile *saveGame,
        idSoundChannel *ch)
{
  idSoundSystemLocal *v4; // ebx
  float *lastV; // ebx
  int v6; // ebp

  v4 = this;
  LOBYTE(this) = ch->triggerState;
  saveGame->WriteBool(saveGame, (const bool)this);
  saveGame->WriteInt(saveGame, ch->trigger44kHzTime);
  idSoundSystemLocal::WriteToSaveGameSoundShaderParams(v4, saveGame, &ch->parms);
  saveGame->WriteInt(saveGame, (const int)ch->leadinSample);
  saveGame->WriteInt(saveGame, ch->choice);
  saveGame->WriteInt(saveGame, ch->triggerChannel);
  saveGame->WriteInt(saveGame, (const int)ch->soundShader);
  saveGame->WriteInt(saveGame, (const int)ch->decoder);
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(ch->diversity));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(ch->lastVolume));
  lastV = ch->lastV;
  v6 = 6;
  do
  {
    ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, *(_DWORD *)lastV++);
    --v6;
  }
  while ( v6 );
  saveGame->WriteInt(saveGame, ch->channelFade.fadeStart44kHz);
  saveGame->WriteInt(saveGame, ch->channelFade.fadeEnd44kHz);
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(ch->channelFade.fadeStartVolume));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(ch->channelFade.fadeEndVolume));
  saveGame->WriteInt(saveGame, ch->lastShift44kHzTime);
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(ch->lastFrequencyShift));
  ((void (__thiscall *)(idFile *, _DWORD))saveGame->WriteFloat)(saveGame, LODWORD(ch->elapsedShift44kHzTime));
}

// FUNC: public: void __thiscall idSoundSystemLocal::ReadFromSaveGameSoundShaderParams(class idFile *,struct soundShaderParms_t *)
void __thiscall idSoundSystemLocal::ReadFromSaveGameSoundShaderParams(
        idSoundSystemLocal *this,
        idFile *saveGame,
        soundShaderParms_t *params)
{
  saveGame->ReadFloat(saveGame, (float *)params);
  saveGame->ReadFloat(saveGame, &params->maxDistance);
  saveGame->ReadFloat(saveGame, &params->volume);
  saveGame->ReadFloat(saveGame, &params->attenuatedVolume);
  saveGame->ReadFloat(saveGame, &params->shakes);
  saveGame->ReadInt(saveGame, &params->soundShaderFlags);
  saveGame->ReadInt(saveGame, &params->soundClass);
  saveGame->ReadFloat(saveGame, &params->frequencyShift);
  saveGame->ReadFloat(saveGame, &params->wetLevel);
  saveGame->ReadFloat(saveGame, &params->dryLevel);
}

// FUNC: public: void __thiscall idSoundSystemLocal::ReadFromSaveGameSoundChannel(class idFile *,class idSoundChannel *)
void __thiscall idSoundSystemLocal::ReadFromSaveGameSoundChannel(
        idSoundSystemLocal *this,
        idFile *saveGame,
        idSoundChannel *ch)
{
  float *lastV; // ebx
  int v6; // ebp

  saveGame->ReadBool(saveGame, (bool *)ch);
  saveGame->ReadInt(saveGame, &ch->trigger44kHzTime);
  idSoundSystemLocal::ReadFromSaveGameSoundShaderParams(this, saveGame, &ch->parms);
  saveGame->ReadInt(saveGame, (int *)&ch->leadinSample);
  saveGame->ReadInt(saveGame, &ch->choice);
  saveGame->ReadInt(saveGame, &ch->triggerChannel);
  saveGame->ReadInt(saveGame, (int *)&ch->soundShader);
  saveGame->ReadInt(saveGame, (int *)&ch->decoder);
  saveGame->ReadFloat(saveGame, &ch->diversity);
  saveGame->ReadFloat(saveGame, &ch->lastVolume);
  lastV = ch->lastV;
  v6 = 6;
  do
  {
    saveGame->ReadFloat(saveGame, lastV++);
    --v6;
  }
  while ( v6 );
  saveGame->ReadInt(saveGame, (int *)&ch->channelFade);
  saveGame->ReadInt(saveGame, &ch->channelFade.fadeEnd44kHz);
  saveGame->ReadFloat(saveGame, &ch->channelFade.fadeStartVolume);
  saveGame->ReadFloat(saveGame, &ch->channelFade.fadeEndVolume);
  saveGame->ReadInt(saveGame, &ch->lastShift44kHzTime);
  saveGame->ReadFloat(saveGame, &ch->lastFrequencyShift);
  saveGame->ReadFloat(saveGame, &ch->elapsedShift44kHzTime);
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::FadeSoundClasses(int,int,float,float)
void __thiscall idSoundSystemLocal::FadeSoundClasses(
        idSoundSystemLocal *this,
        int worldId,
        unsigned int soundClass,
        float to,
        float over)
{
  idSoundFade *v6; // esi
  int v7; // ebx
  int lastAVI44kHz; // edi
  int v9; // edi
  float toa; // [esp+18h] [ebp+Ch]

  if ( soundClass >= 4 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idSoundWorldLocal::FadeSoundClasses: bad soundClass %i",
      soundClass);
  toa = idMath::dBToScale(to);
  v6 = &this->soundClassFade[soundClass];
  v7 = idSoundSystemLocal::MillisecondsToSamples(this, (int)(over * 1000.0));
  if ( this->soundClassFade[soundClass].fadeEndVolume != toa
    || this->soundClassFade[soundClass].fadeEnd44kHz - this->soundClassFade[soundClass].fadeStart44kHz != v7 )
  {
    if ( this->fpa[0] )
      lastAVI44kHz = this->lastAVI44kHz;
    else
      lastAVI44kHz = idSoundSystemLocal::GetCurrent44kHzTime(this);
    v9 = lastAVI44kHz + 4096;
    v6->fadeStartVolume = idSoundFade::FadeDbAt44kHz(v6, v9);
    v6->fadeStart44kHz = v9;
    v6->fadeEnd44kHz = v7 + v9;
    v6->fadeEndVolume = toa;
  }
}

// FUNC: public: void __thiscall idSoundSystemLocal::ClearAllSoundEmitters(void)
void __thiscall idSoundSystemLocal::ClearAllSoundEmitters(idSoundSystemLocal *this)
{
  int i; // edi

  Sys_EnterCriticalSection(0);
  this->AVIClose(this, 1);
  this->StopAllSounds(this, -1);
  for ( i = 0; i < this->GetNumEmitters(this); ++i )
    idSoundEmitterLocal::Clear(this->emitters.list[i]);
  this->localSound[0] = 0;
  this->localSound[1] = 0;
  this->localSound[2] = 0;
  this->localSound[3] = 0;
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: void __thiscall idSoundSystemLocal::ResolveOrigin(int,struct soundPortalTrace_s const *,int,float,int,class idVec3 const &,class idSoundEmitterLocal *)
void __thiscall idSoundSystemLocal::ResolveOrigin(
        idSoundSystemLocal *this,
        int stackDepth,
        const soundPortalTrace_s *prevStack,
        int soundArea,
        float dist,
        int occlusionPortals,
        const idVec3 *soundOrigin,
        idSoundEmitterLocal *def)
{
  idSoundEmitterLocal *v8; // edi
  int v10; // ebp
  double v11; // st5
  double v12; // st3
  double v13; // st4
  double v14; // st3
  double v15; // st4
  double v16; // st7
  idRenderWorld *rw; // ecx
  int v18; // esi
  int v19; // ecx
  const soundPortalTrace_s *v20; // eax
  const idVec3 *v21; // esi
  double v22; // st7
  double v23; // st6
  double v24; // st5
  int v25; // ebp
  double v26; // st7
  double v27; // st7
  double v28; // st6
  int numPoints; // ecx
  int v30; // esi
  idVec5 *v31; // eax
  int v32; // ecx
  double v33; // st7
  double v34; // st6
  double v35; // st5
  double v36; // st7
  long double v37; // st6
  long double v38; // st6
  long double v39; // st5
  long double v40; // st7
  double v41; // st6
  double v42; // st5
  double v43; // st7
  double v44; // st5
  double v45; // st3
  double v46; // st4
  double v47; // st3
  double v48; // st7
  float v49; // [esp+10h] [ebp-D0h]
  int otherArea; // [esp+30h] [ebp-B0h]
  float edgeNormal; // [esp+38h] [ebp-A8h]
  float edgeNormal_4; // [esp+3Ch] [ebp-A4h]
  float edgeNormal_8; // [esp+40h] [ebp-A0h]
  idVec3 source; // [esp+44h] [ebp-9Ch] BYREF
  int p; // [esp+50h] [ebp-90h]
  int numPortals; // [esp+54h] [ebp-8Ch]
  idPlane pl; // [esp+58h] [ebp-88h] BYREF
  float occlusionDistance; // [esp+68h] [ebp-78h]
  idVec3 dir; // [esp+6Ch] [ebp-74h]
  idVec3 v60; // [esp+78h] [ebp-68h]
  float v61; // [esp+84h] [ebp-5Ch]
  float v62; // [esp+88h] [ebp-58h]
  float v63; // [esp+8Ch] [ebp-54h]
  float v64; // [esp+90h] [ebp-50h]
  soundPortalTrace_s newStack; // [esp+94h] [ebp-4Ch] BYREF
  exitPortal_t re; // [esp+9Ch] [ebp-44h] BYREF
  float v67; // [esp+B4h] [ebp-2Ch]
  float v68; // [esp+B8h] [ebp-28h]
  float v69; // [esp+C0h] [ebp-20h]
  float v70[3]; // [esp+C4h] [ebp-1Ch]
  float v71; // [esp+D0h] [ebp-10h]
  idVec3 result; // [esp+D4h] [ebp-Ch] BYREF

  v8 = def;
  if ( dist < (double)def->distance )
  {
    v10 = soundArea;
    if ( soundArea == this->listenerArea )
    {
      v11 = soundOrigin->z - this->listenerPos.z;
      v12 = soundOrigin->y - this->listenerPos.y;
      v13 = v11 * v11 + v12 * v12;
      v14 = soundOrigin->x - this->listenerPos.x;
      v15 = v13 + v14 * v14;
      *(float *)&p = v15;
      v16 = v15
          * ((1.5 - 0.5 * v15 * COERCE_FLOAT(1597463007 - (p >> 1)) * COERCE_FLOAT(1597463007 - (p >> 1)))
           * COERCE_FLOAT(1597463007 - (p >> 1)))
          + dist;
      if ( v16 < def->distance )
      {
        def->distance = v16;
        def->spatializedOrigin = *soundOrigin;
        def->numPortals = occlusionPortals;
      }
    }
    else if ( stackDepth != 10 )
    {
      if ( soundArea < 0 || soundArea >= this->rw->NumAreas(this->rw) )
      {
        v44 = soundOrigin->z - this->listenerPos.z;
        v45 = soundOrigin->y - this->listenerPos.y;
        v46 = v44 * v44 + v45 * v45;
        v47 = soundOrigin->x - this->listenerPos.x;
        v48 = v46 + v47 * v47;
        *(float *)&numPortals = v48;
        def->distance = (1.5
                       - 0.5
                       * v48
                       * COERCE_FLOAT(1597463007 - (numPortals >> 1))
                       * COERCE_FLOAT(1597463007 - (numPortals >> 1)))
                      * COERCE_FLOAT(1597463007 - (numPortals >> 1))
                      * v48
                      + dist;
        def->spatializedOrigin = *soundOrigin;
        def->numPortals = occlusionPortals;
      }
      else
      {
        rw = this->rw;
        newStack.portalArea = soundArea;
        newStack.prevStack = prevStack;
        *(float *)&v18 = 0.0;
        *(float *)&numPortals = COERCE_FLOAT(rw->NumPortalsInArea(rw, soundArea));
        *(float *)&p = 0.0;
        if ( numPortals > 0 )
        {
          do
          {
            (*(void (__thiscall **)(idRenderWorld *, exitPortal_t *, int, int))this->rw->gapA8)(this->rw, &re, v10, v18);
            ++this->soundStats.numPortalChecks;
            ++v8->numPortalChecks;
            occlusionDistance = 0.0;
            if ( (re.blockingBits & 5) != 0 )
            {
              ++occlusionPortals;
              occlusionDistance = s_doorDistanceAdd.internalVar->floatValue;
            }
            v19 = re.areas[0];
            otherArea = re.areas[0];
            if ( re.areas[0] == v10 )
            {
              otherArea = re.areas[1];
              v19 = re.areas[1];
            }
            v20 = prevStack;
            if ( prevStack )
            {
              while ( v20->portalArea != v19 )
              {
                v20 = v20->prevStack;
                if ( !v20 )
                  goto LABEL_16;
              }
            }
            else
            {
LABEL_16:
              idWinding::GetPlane((idWinding *)re.w, &pl);
              v21 = soundOrigin;
              dir.x = this->listenerPos.x - soundOrigin->x;
              dir.y = this->listenerPos.y - soundOrigin->y;
              dir.z = this->listenerPos.z - soundOrigin->z;
              v22 = pl.c * dir.z + pl.b * dir.y + pl.a * dir.x;
              if ( v22 == 0.0 )
              {
                source = *idWinding::GetCenter((idWinding *)re.w, &result);
              }
              else
              {
                v23 = pl.c * soundOrigin->z;
                v24 = pl.a * soundOrigin->x;
                v60 = dir;
                v25 = 0;
                v26 = -((v23 + v24 + pl.b * soundOrigin->y + pl.d) / v22);
                v69 = dir.y * v26;
                v70[0] = dir.z * v26;
                v27 = dir.x * v26 + soundOrigin->x;
                v28 = v69 + soundOrigin->y;
                v71 = v70[0] + soundOrigin->z;
                source.z = v71;
                source.x = v27;
                source.y = v28;
                numPoints = re.w->numPoints;
                if ( numPoints > 0 )
                {
                  v30 = 0;
                  do
                  {
                    ++v25;
                    v31 = re.w->p;
                    v32 = v25 % numPoints;
                    v33 = v31[v32].x - v31[v30].x;
                    v34 = v31[v32].y - v31[v30].y;
                    v35 = v31[v32].z - v31[v30].z;
                    edgeNormal = pl.b * v35 - v34 * pl.c;
                    edgeNormal_4 = pl.c * v33 - v35 * pl.a;
                    edgeNormal_8 = v34 * pl.a - pl.b * v33;
                    v36 = (source.z - v31[v32].z) * edgeNormal_8
                        + (source.y - v31[v32].y) * edgeNormal_4
                        + (source.x - v31[v32].x) * edgeNormal;
                    if ( v36 > 0.0 )
                    {
                      v37 = edgeNormal_8 * edgeNormal_8 + edgeNormal_4 * edgeNormal_4 + edgeNormal * edgeNormal;
                      if ( v37 == 0.0 )
                      {
                        v38 = 0.0;
                      }
                      else
                      {
                        v39 = 1.0 / sqrt(v37);
                        edgeNormal = edgeNormal * v39;
                        edgeNormal_4 = edgeNormal_4 * v39;
                        edgeNormal_8 = edgeNormal_8 * v39;
                        v38 = v37 * v39;
                      }
                      v40 = v36 / v38;
                      v61 = edgeNormal;
                      v62 = edgeNormal_4;
                      v63 = edgeNormal_8;
                      v67 = edgeNormal_4 * v40;
                      v68 = edgeNormal_8 * v40;
                      source.x = source.x - edgeNormal * v40;
                      source.y = source.y - v67;
                      source.z = source.z - v68;
                    }
                    numPoints = re.w->numPoints;
                    ++v30;
                  }
                  while ( v25 < numPoints );
                  v21 = soundOrigin;
                }
                v8 = def;
                v10 = soundArea;
              }
              v41 = source.y - v21->y;
              v42 = source.z - v21->z;
              v43 = v42 * v42 + v41 * v41 + (source.x - v21->x) * (source.x - v21->x);
              v64 = v43;
              v49 = (1.5
                   - 0.5
                   * v43
                   * COERCE_FLOAT(1597463007 - (SLODWORD(v64) >> 1))
                   * COERCE_FLOAT(1597463007 - (SLODWORD(v64) >> 1)))
                  * COERCE_FLOAT(1597463007 - (SLODWORD(v64) >> 1))
                  * v43
                  + occlusionDistance
                  + dist;
              idSoundSystemLocal::ResolveOrigin(
                this,
                stackDepth + 1,
                &newStack,
                otherArea,
                v49,
                occlusionPortals,
                &source,
                v8);
              v18 = p;
            }
            p = ++v18;
          }
          while ( v18 < numPortals );
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::ListActiveSounds(int)
void __thiscall idSoundSystemLocal::ListActiveSounds(idSoundSystemLocal *this, int worldId)
{
  idSoundSystemLocal *v2; // ebp
  int v3; // edi
  idSoundEmitterLocal *v4; // esi
  idSoundSample **p_leadinSample; // edi
  int v6; // ebx
  int v7; // eax
  unsigned int openalSourceCount; // ecx
  int v9; // esi
  int v10; // edx
  bool *p_stereo; // eax
  int j; // [esp+8h] [ebp-Ch]

  v2 = this;
  if ( this->isInitialized )
  {
    Sys_EnterCriticalSection(0);
    v3 = 1;
    for ( j = 1; v3 < v2->GetNumEmitters(v2); j = v3 )
    {
      v4 = v2->emitters.list[v3];
      if ( v4->removeStatus < REMOVE_STATUS_SAMPLEFINISHED && v4->playing )
      {
        p_leadinSample = &v4->channels[0].leadinSample;
        v6 = 8;
        do
        {
          if ( *((_BYTE *)p_leadinSample - 48) )
          {
            v7 = (*(int (__thiscall **)(int))(*(_DWORD *)p_leadinSample[3]->name.len + 4))(p_leadinSample[3]->name.len);
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "%s: (%d, %d, %d) %d/%d, portals = %d, looping = %d, channels = %d, occlusion = %d\n",
              v7,
              (int)v4->origin.x,
              (int)v4->origin.y,
              (int)v4->origin.z,
              (int)v4->distance,
              (int)v4->maxDistance,
              v4->numPortalChecks,
              (unsigned int)*(p_leadinSample - 5) & 0x20,
              (*p_leadinSample)->nChannels,
              v4->numPortals);
            v2 = this;
          }
          p_leadinSample += 41;
          --v6;
        }
        while ( v6 );
        v3 = j;
      }
      ++v3;
    }
    openalSourceCount = v2->openalSourceCount;
    v9 = 0;
    v10 = 0;
    if ( openalSourceCount )
    {
      p_stereo = &v2->openalSources[0].stereo;
      do
      {
        if ( *(p_stereo - 2) )
        {
          if ( *p_stereo )
            ++v9;
          else
            ++v10;
        }
        p_stereo += 16;
        --openalSourceCount;
      }
      while ( openalSourceCount );
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Using %d mono OpenAL source(s)\n",
      v10);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Using %d stereo OpenAL source(s)\n",
      v9);
    Sys_LeaveCriticalSection(0);
  }
}

// FUNC: public: void __thiscall idSoundSystemLocal::OffsetSoundTime(int)
void __thiscall idSoundSystemLocal::OffsetSoundTime(idSoundSystemLocal *this, int offset44kHz)
{
  int i; // edi
  int j; // eax
  idSoundEmitterLocal *v5; // ecx
  bool v6; // zf
  int v7; // ecx
  idSoundEmitterLocal *v8; // ecx
  int v9; // ecx
  idSoundEmitterLocal *v10; // ecx
  int v11; // ecx
  idSoundEmitterLocal *v12; // ecx
  int v13; // ecx

  Sys_EnterCriticalSection(0);
  for ( i = 0; i < this->GetNumEmitters(this); ++i )
  {
    if ( this->emitters.list[i] )
    {
      for ( j = 0; j < 8; j += 4 )
      {
        v5 = this->emitters.list[i];
        v6 = !v5->channels[j].triggerState;
        v7 = (int)&v5->channels[j];
        if ( !v6 && (*(_BYTE *)(v7 + 28) & 0x20) == 0 )
          *(_DWORD *)(v7 + 4) += offset44kHz;
        v8 = this->emitters.list[i];
        v6 = !v8->channels[j + 1].triggerState;
        v9 = (int)&v8->channels[j + 1];
        if ( !v6 && (*(_BYTE *)(v9 + 28) & 0x20) == 0 )
          *(_DWORD *)(v9 + 4) += offset44kHz;
        v10 = this->emitters.list[i];
        v6 = !v10->channels[j + 2].triggerState;
        v11 = (int)&v10->channels[j + 2];
        if ( !v6 && (*(_BYTE *)(v11 + 28) & 0x20) == 0 )
          *(_DWORD *)(v11 + 4) += offset44kHz;
        v12 = this->emitters.list[i];
        v6 = !v12->channels[j + 3].triggerState;
        v13 = (int)&v12->channels[j + 3];
        if ( !v6 && (*(_BYTE *)(v13 + 28) & 0x20) == 0 )
          *(_DWORD *)(v13 + 4) += offset44kHz;
      }
    }
  }
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::WriteToSaveGame(int,class idFile *)
void __thiscall idSoundSystemLocal::WriteToSaveGame(idSoundSystemLocal *this, int worldId, int savefile)
{
  int pause44kHz; // edi
  idFile *v5; // esi
  int v6; // eax
  int v7; // ebp
  idSoundEmitterLocal *v8; // edi
  idFile_vtbl *v9; // edx
  idFile v10; // eax
  idSoundChannel *channels; // ebp
  int v12; // eax
  int v13; // eax
  int v14; // ebp
  idSoundSample **p_leadinSample; // edi
  int v16; // eax
  int i; // [esp+64h] [ebp-4h]

  Sys_EnterCriticalSection(0);
  pause44kHz = this->pause44kHz;
  if ( pause44kHz <= 0 )
    pause44kHz = idSoundSystemLocal::GetCurrent44kHzTime(this);
  v5 = (idFile *)savefile;
  (*(void (__thiscall **)(int, idVec3 *))(*(_DWORD *)savefile + 160))(savefile, &this->listenerPos);
  v5->WriteMat3(v5, &this->listenerAxis);
  v5->WriteInt(v5, this->listenerPrivateId);
  v5->WriteInt(v5, this->gameMsec);
  v5->WriteInt(v5, this->game44kHz);
  v5->WriteInt(v5, pause44kHz);
  v6 = this->GetNumEmitters(this);
  v5->WriteInt(v5, v6);
  v7 = 1;
  for ( i = 1; v7 < this->GetNumEmitters(this); i = v7 )
  {
    v8 = this->emitters.list[v7];
    if ( v8->removeStatus )
    {
      v9 = v5->__vftable;
      savefile = -1;
      v9->Write(v5, &savefile, 4);
    }
    else if ( v8->AttachedToWorld(v8, 1) )
    {
      v5->WriteInt(v5, v7);
      v5->WriteVec3(v5, &v8->origin);
      v5->WriteInt(v5, v8->listenerId);
      idSoundSystemLocal::WriteToSaveGameSoundShaderParams(this, v5, &v8->parms);
      ((void (__thiscall *)(idFile *, _DWORD))v5->WriteFloat)(v5, LODWORD(v8->amplitude));
      v5->WriteInt(v5, v8->ampTime);
      channels = v8->channels;
      savefile = 8;
      do
      {
        idSoundSystemLocal::WriteToSaveGameSoundChannel(this, v5, channels++);
        --savefile;
      }
      while ( savefile );
      v12 = ((int (__thiscall *)(idFile *, _DWORD))v5->WriteFloat)(v5, LODWORD(v8->distance));
      LOBYTE(v12) = v8->hasShakes;
      v5->WriteBool(v5, v12);
      v5->WriteInt(v5, v8->lastValidPortalArea);
      v13 = ((int (__thiscall *)(idFile *, _DWORD))v5->WriteFloat)(v5, LODWORD(v8->maxDistance));
      LOBYTE(v13) = v8->playing;
      v5->WriteBool(v5, v13);
      ((void (__thiscall *)(idFile *, _DWORD))v5->WriteFloat)(v5, LODWORD(v8->realDistance));
      v5->WriteInt(v5, v8->removeStatus);
      v5->WriteVec3(v5, &v8->spatializedOrigin);
      v14 = 0;
      p_leadinSample = &v8->channels[0].leadinSample;
      do
      {
        if ( *((_BYTE *)p_leadinSample - 48) && p_leadinSample[3] && *p_leadinSample )
        {
          v5->WriteInt(v5, v14);
          v16 = (*(int (__thiscall **)(int))(*(_DWORD *)p_leadinSample[3]->name.len + 4))(p_leadinSample[3]->name.len);
          v5->WriteString(v5, (const char *)v16);
          v5->WriteString(v5, (*p_leadinSample)->name.data);
        }
        ++v14;
        p_leadinSample += 41;
      }
      while ( v14 < 8 );
      v5->WriteInt(v5, -1);
      v7 = i;
    }
    else
    {
      v10.__vftable = v5->__vftable;
      savefile = -1;
      v10.Write(v5, &savefile, 4);
    }
    ++v7;
  }
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: virtual class idSoundEmitter * __thiscall idSoundSystemLocal::EmitterForIndex(int,int)
idSoundEmitterLocal *__thiscall idSoundSystemLocal::EmitterForIndex(idSoundSystemLocal *this, int worldId, int index)
{
  int v5; // ebx
  int v6; // eax

  if ( index <= 0 )
    return 0;
  if ( index >= this->GetNumEmitters(this) )
  {
    v5 = *(_DWORD *)common.type;
    v6 = this->GetNumEmitters(this);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 152))(
      common.type,
      "idSoundWorldLocal::EmitterForIndex: %i > %i",
      index,
      v6);
  }
  return this->emitters.list[index];
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::StopAllSounds(int)
void __thiscall idSoundSystemLocal::StopAllSounds(idSoundSystemLocal *this, int worldId)
{
  int i; // ebx
  idSoundEmitterLocal *v4; // esi

  Sys_EnterCriticalSection(0);
  for ( i = 0; i < this->GetNumEmitters(this); ++i )
  {
    v4 = this->emitters.list[i];
    if ( v4 && v4->AttachedToWorld(v4, worldId) )
    {
      v4->StopSound(v4, 0);
      idSoundEmitterLocal::ClearPortalArea(v4);
    }
  }
  Sys_LeaveCriticalSection(0);
}

// FUNC: public: void __thiscall idSoundSystemLocal::CalcEars(int,class idVec3,class idVec3,class idMat3,float * const,float)
void __thiscall idSoundSystemLocal::CalcEars(
        idSoundSystemLocal *this,
        int numSpeakers,
        idVec3 spatializedOrigin,
        idVec3 listenerPos,
        idMat3 listenerAxis,
        float *ears,
        float spatialize)
{
  double v7; // st7
  double v8; // st6
  long double v9; // st5
  long double v10; // st5
  double v11; // st4
  double v12; // st5
  double v13; // st5
  double v14; // st5
  double v15; // st7
  double v16; // st6
  idCVar *internalVar; // edx
  float svec; // [esp+0h] [ebp-Ch]
  float svec_4; // [esp+4h] [ebp-8h]
  float svec_8; // [esp+8h] [ebp-4h]
  float ovec; // [esp+14h] [ebp+8h]

  svec = spatializedOrigin.x - listenerPos.x;
  svec_4 = spatializedOrigin.y - listenerPos.y;
  svec_8 = spatializedOrigin.z - listenerPos.z;
  ovec = listenerAxis.mat[0].y * svec_4 + listenerAxis.mat[0].x * svec + listenerAxis.mat[0].z * svec_8;
  v7 = listenerAxis.mat[1].z * svec_8 + listenerAxis.mat[1].y * svec_4 + listenerAxis.mat[1].x * svec;
  v8 = listenerAxis.mat[2].z * svec_8 + listenerAxis.mat[2].y * svec_4 + listenerAxis.mat[2].x * svec;
  v9 = v8 * v8 + ovec * ovec + v7 * v7;
  if ( v9 != 0.0 )
  {
    v10 = 1.0 / sqrt(v9);
    ovec = ovec * v10;
    v7 = v7 * v10;
    v8 = v8 * v10;
  }
  if ( numSpeakers == 6 )
  {
    if ( (_S19_1 & 1) == 0 )
    {
      _S19_1 |= 1u;
      speakerVector[0].x = 0.70700002;
      dword_112F0F0C = 1060437492;
      dword_112F0F10 = 0;
      dword_112F0F14 = 1060437492;
      dword_112F0F18 = -1087046156;
      dword_112F0F1C = 0;
      dword_112F0F20 = 1060437492;
      dword_112F0F24 = 0;
      dword_112F0F28 = 0;
      dword_112F0F2C = 0;
      dword_112F0F30 = 0;
      dword_112F0F34 = 0;
      dword_112F0F38 = -1087046156;
      dword_112F0F3C = 1060437492;
      dword_112F0F40 = 0;
      dword_112F0F44 = -1087046156;
      dword_112F0F48 = -1087046156;
      dword_112F0F4C = 0;
    }
    v11 = (*(float *)&dword_112F0F10 * v8
         + ovec * speakerVector[0].x
         + *(float *)&dword_112F0F0C * v7
         + idSoundSystemLocal::s_dotbias6.internalVar->floatValue)
        / (idSoundSystemLocal::s_dotbias6.internalVar->floatValue + 1.0);
    *ears = v11;
    if ( v11 < idSoundSystemLocal::s_minVolume6.internalVar->floatValue )
      *ears = idSoundSystemLocal::s_minVolume6.internalVar->floatValue;
    v12 = (*(float *)&dword_112F0F1C * v8
         + ovec * *(float *)&dword_112F0F14
         + *(float *)&dword_112F0F18 * v7
         + idSoundSystemLocal::s_dotbias6.internalVar->floatValue)
        / (idSoundSystemLocal::s_dotbias6.internalVar->floatValue + 1.0);
    ears[1] = v12;
    if ( v12 < idSoundSystemLocal::s_minVolume6.internalVar->floatValue )
      ears[1] = idSoundSystemLocal::s_minVolume6.internalVar->floatValue;
    v13 = (*(float *)&dword_112F0F28 * v8
         + ovec * *(float *)&dword_112F0F20
         + *(float *)&dword_112F0F24 * v7
         + idSoundSystemLocal::s_dotbias6.internalVar->floatValue)
        / (idSoundSystemLocal::s_dotbias6.internalVar->floatValue + 1.0);
    ears[2] = v13;
    if ( v13 < idSoundSystemLocal::s_minVolume6.internalVar->floatValue )
      ears[2] = idSoundSystemLocal::s_minVolume6.internalVar->floatValue;
    ears[3] = idSoundSystemLocal::s_subFraction.internalVar->floatValue;
    v14 = (*(float *)&dword_112F0F40 * v8
         + ovec * *(float *)&dword_112F0F38
         + *(float *)&dword_112F0F3C * v7
         + idSoundSystemLocal::s_dotbias6.internalVar->floatValue)
        / (idSoundSystemLocal::s_dotbias6.internalVar->floatValue + 1.0);
    ears[4] = v14;
    if ( v14 < idSoundSystemLocal::s_minVolume6.internalVar->floatValue )
      ears[4] = idSoundSystemLocal::s_minVolume6.internalVar->floatValue;
    v15 = (*(float *)&dword_112F0F4C * v8
         + ovec * *(float *)&dword_112F0F44
         + *(float *)&dword_112F0F48 * v7
         + idSoundSystemLocal::s_dotbias6.internalVar->floatValue)
        / (idSoundSystemLocal::s_dotbias6.internalVar->floatValue + 1.0);
    ears[5] = v15;
    if ( v15 < idSoundSystemLocal::s_minVolume6.internalVar->floatValue )
      ears[5] = idSoundSystemLocal::s_minVolume6.internalVar->floatValue;
  }
  else
  {
    v16 = idSoundSystemLocal::s_dotbias2.internalVar->floatValue
        + (idSoundSystemLocal::s_spatializationDecay.internalVar->floatValue
         - idSoundSystemLocal::s_dotbias2.internalVar->floatValue)
        * (1.0 - spatialize)
        + 1.0;
    *ears = (v7 + idSoundSystemLocal::s_dotbias2.internalVar->floatValue) / v16;
    ears[1] = (idSoundSystemLocal::s_dotbias2.internalVar->floatValue - v7) / v16;
    internalVar = idSoundSystemLocal::s_minVolume2.internalVar;
    if ( *ears < (double)idSoundSystemLocal::s_minVolume2.internalVar->floatValue )
    {
      *ears = idSoundSystemLocal::s_minVolume2.internalVar->floatValue;
      internalVar = idSoundSystemLocal::s_minVolume2.internalVar;
    }
    if ( ears[1] < (double)internalVar->floatValue )
      ears[1] = internalVar->floatValue;
    ears[4] = 0.0;
    ears[3] = 0.0;
    ears[2] = 0.0;
    ears[5] = 0.0;
  }
}

// FUNC: public: void __thiscall idSoundSystemLocal::DetermineChannelContribution(class idSoundEmitterLocal *,class idSoundChannel *,int)
void __thiscall idSoundSystemLocal::DetermineChannelContribution(
        idSoundSystemLocal *this,
        idSoundEmitterLocal *sound,
        idSoundChannel *chan,
        int current44kHz)
{
  idSoundSample *leadinSample; // ecx
  const idSoundShader *soundShader; // ebp
  bool v8; // bl
  double v10; // st7
  double realDistance; // st6
  double v12; // st6
  int triggerChannel; // eax
  int soundShaderFlags; // eax
  float mind; // [esp+8h] [ebp-10h]
  float maxd; // [esp+Ch] [ebp-Ch]
  float floatValue; // [esp+10h] [ebp-8h]
  idSoundSystemLocal *v18; // [esp+14h] [ebp-4h]
  char chana; // [esp+20h] [ebp+8h]
  float noOcclusion; // [esp+24h] [ebp+Ch]
  float noOcclusiona; // [esp+24h] [ebp+Ch]

  leadinSample = chan->leadinSample;
  v18 = this;
  if ( !leadinSample || leadinSample->defaultSound && !s_playDefaultSound.internalVar->integerValue )
  {
    chan->lastVolume = 0.0;
    return;
  }
  soundShader = chan->soundShader;
  if ( !soundShader )
  {
    chan->lastVolume = 0.0;
    return;
  }
  maxd = chan->parms.maxDistance;
  mind = chan->parms.minDistance;
  v8 = (chan->parms.soundShaderFlags & 8) != 0;
  if ( (chan->parms.soundShaderFlags & 4) != 0 || (chana = 0, !s_useOcclusion.internalVar->integerValue) )
    chana = 1;
  if ( sound->listenerId == this->listenerPrivateId )
    v8 = 1;
  if ( LODWORD(soundShader->leadinVolume) == 1065353216
    || current44kHz - chan->trigger44kHzTime >= idSoundSample::LengthIn44kHzSamples(leadinSample) )
  {
    noOcclusion = chan->parms.volume;
  }
  else
  {
    noOcclusion = soundShader->leadinVolume;
  }
  floatValue = s_volume.internalVar->floatValue;
  noOcclusiona = idSoundFade::FadeDbAt44kHz(&chan->channelFade, current44kHz) * (floatValue * noOcclusion);
  v10 = idSoundFade::FadeDbAt44kHz(&v18->soundClassFade[chan->parms.soundClass], current44kHz) * noOcclusiona;
  if ( !v8 )
  {
    if ( chana )
      realDistance = sound->realDistance;
    else
      realDistance = sound->distance;
    if ( realDistance < maxd )
    {
      if ( realDistance > mind )
      {
        v12 = 1.0 - (realDistance - mind) / (maxd - mind);
        if ( v12 >= 0.0 )
        {
          if ( v12 > 1.0 )
            v12 = 1.0;
        }
        else
        {
          v12 = 0.0;
        }
        if ( s_quadraticFalloff.internalVar->integerValue )
          v12 = v12 * v12;
        v10 = v10 * v12;
      }
    }
    else
    {
      v10 = 0.0;
    }
    if ( (chan->parms.soundShaderFlags & 0x2000) == 0 )
    {
      triggerChannel = chan->triggerChannel;
      if ( triggerChannel != 6 && triggerChannel != 7 && chan->parms.soundClass != 3 )
      {
        if ( triggerChannel == 10 )
          v10 = v10 * idSoundSystemLocal::s_radioChatterFraction.internalVar->floatValue;
        else
          v10 = v10 * idSoundSystemLocal::s_speakerFraction.internalVar->floatValue;
      }
    }
  }
  soundShaderFlags = chan->parms.soundShaderFlags;
  if ( (soundShaderFlags & 1) != 0 && sound->listenerId != v18->listenerPrivateId )
    v10 = 0.0;
  if ( (soundShaderFlags & 2) != 0 && sound->listenerId == v18->listenerPrivateId )
  {
    v10 = 0.0;
  }
  else if ( v10 >= 0.0009765625 )
  {
    goto LABEL_46;
  }
  if ( chan->lastVolume < 0.0009765625 )
  {
    chan->lastVolume = 0.0;
    return;
  }
LABEL_46:
  chan->lastVolume = v10;
}

// FUNC: public: void __thiscall idSoundSystemLocal::AddChannelContribution(class idSoundEmitterLocal *,class idSoundChannel *,int,int,float *)
void __thiscall idSoundSystemLocal::AddChannelContribution(
        idSoundSystemLocal *this,
        idSoundEmitterLocal *sound,
        idSoundChannel *chan,
        int current44kHz,
        int numSpeakers,
        float *finalMixBuffer)
{
  double lastVolume; // st7
  int maxDistance_low; // eax
  int soundShaderFlags; // eax
  bool v10; // dl
  bool v11; // cl
  bool v12; // al
  bool v13; // zf
  double realDistance; // st7
  float y; // eax
  float z; // ecx
  float v17; // ecx
  float v18; // eax
  int lastShift44kHzTime; // ecx
  int v20; // edi
  int v21; // ecx
  double v22; // st7
  double elapsedShift44kHzTime; // st7
  unsigned int v24; // ebx
  idSoundSample *leadinSample; // ecx
  bool v26; // al
  unsigned int openalSource; // edx
  int v28; // eax
  unsigned int v29; // ecx
  unsigned int v30; // edx
  unsigned int v31; // eax
  unsigned int v32; // ecx
  int EnumValue; // eax
  float v34; // edx
  float v35; // eax
  int openalBuffer; // eax
  unsigned int v37; // edx
  int v38; // eax
  int v39; // esi
  _EAXOCCLUSIONPROPERTIES *p_SourceOcclusion; // edi
  int v41; // edx
  int i; // ecx
  int lastValidPortalArea; // eax
  idSoundSystemLocal *v44; // edi
  _GUID *efxSlotId; // edi
  int v46; // eax
  int (__cdecl *alEAXSet)(const _GUID *, unsigned int, unsigned int, void *, unsigned int); // eax
  float v48; // eax
  float v49; // ecx
  int numPortals; // eax
  int (__cdecl *v51)(const _GUID *, unsigned int, unsigned int, void *, unsigned int); // eax
  float v52; // ecx
  float v53; // ecx
  unsigned int openalStreamingOffset; // eax
  unsigned int v55; // eax
  double v56; // st7
  int v57; // ecx
  double v58; // st7
  int v59; // edx
  unsigned int v60; // ecx
  double v61; // st7
  float v62; // eax
  float v63; // ecx
  float v64; // edx
  float v65; // eax
  float v66; // ecx
  idSIMDProcessor_vtbl *v67; // eax
  idSIMDProcessor_vtbl *v68; // eax
  float v69; // ecx
  float v70; // edx
  float v71; // eax
  float v72; // ecx
  float v73; // edx
  idVec3 v74; // [esp-38h] [ebp-E8h]
  idMat3 v75; // [esp-20h] [ebp-D0h] BYREF
  idSoundChannel *lastV; // [esp+4h] [ebp-ACh]
  float v77; // [esp+8h] [ebp-A8h]
  int samples; // [esp+1Ch] [ebp-94h]
  float v79; // [esp+20h] [ebp-90h]
  bool looping; // [esp+27h] [ebp-89h]
  float frequencyshift; // [esp+28h] [ebp-88h]
  bool omni; // [esp+2Eh] [ebp-82h]
  bool global; // [esp+2Fh] [ebp-81h]
  int finishedbuffers; // [esp+30h] [ebp-80h] BYREF
  int jj; // [esp+34h] [ebp-7Ch]
  idSoundSystemLocal *v86; // [esp+38h] [ebp-78h]
  bool noOcclusion; // [esp+3Fh] [ebp-71h]
  int SourceRoom; // [esp+40h] [ebp-70h] BYREF
  float ears[6]; // [esp+44h] [ebp-6Ch] BYREF
  _EAXOCCLUSIONPROPERTIES SourceOcclusion; // [esp+5Ch] [ebp-54h] BYREF
  float spatialize; // [esp+6Ch] [ebp-44h]
  _EAXACTIVEFXSLOTS SourceActiveSlot; // [esp+70h] [ebp-40h] BYREF

  lastVolume = chan->lastVolume;
  v86 = this;
  if ( lastVolume >= 0.0009765625 )
  {
    maxDistance_low = SLODWORD(chan->parms.maxDistance);
    finishedbuffers = SLODWORD(chan->parms.minDistance);
    jj = maxDistance_low;
    soundShaderFlags = chan->parms.soundShaderFlags;
    omni = (soundShaderFlags & 0x10) != 0;
    v10 = (soundShaderFlags & 0x20) != 0;
    v11 = (soundShaderFlags & 8) != 0;
    looping = v10;
    global = v11;
    v12 = (soundShaderFlags & 4) != 0 || !s_useOcclusion.internalVar->integerValue;
    v13 = sound->listenerId == this->listenerPrivateId;
    noOcclusion = v12;
    if ( v13 )
    {
      v11 = 1;
      global = 1;
    }
    v13 = chan->leadinSample->nChannels == 2;
    SourceRoom = (int)chan->leadinSample;
    if ( v13 )
      omni = 1;
    spatialize = 1.0;
    if ( !v11 )
    {
      if ( v12 )
      {
        realDistance = sound->realDistance;
        y = sound->origin.y;
        SourceOcclusion.lOcclusion = LODWORD(sound->origin.x);
        z = sound->origin.z;
        SourceOcclusion.flOcclusionLFRatio = y;
        SourceOcclusion.flOcclusionRoomRatio = z;
      }
      else
      {
        realDistance = sound->distance;
        v17 = sound->spatializedOrigin.y;
        SourceOcclusion.lOcclusion = LODWORD(sound->spatializedOrigin.x);
        v18 = sound->spatializedOrigin.z;
        SourceOcclusion.flOcclusionLFRatio = v17;
        SourceOcclusion.flOcclusionRoomRatio = v18;
      }
      if ( realDistance < *(float *)&jj
        && realDistance <= *(float *)&finishedbuffers
        && *(float *)&finishedbuffers > 0.0 )
      {
        spatialize = realDistance / *(float *)&finishedbuffers;
      }
    }
    if ( idSoundSystemLocal::s_frequencyShift.internalVar->integerValue )
      frequencyshift = chan->parms.frequencyShift;
    else
      frequencyshift = 1.0;
    lastShift44kHzTime = chan->lastShift44kHzTime;
    if ( lastShift44kHzTime || frequencyshift != 1.0 )
    {
      if ( frequencyshift >= 0.25 )
      {
        if ( frequencyshift > 4.0 )
          frequencyshift = 4.0;
      }
      else
      {
        frequencyshift = 0.25;
      }
      v20 = current44kHz;
      if ( lastShift44kHzTime )
      {
        LODWORD(v79) = current44kHz - lastShift44kHzTime;
        v22 = (double)(current44kHz - lastShift44kHzTime) * chan->lastFrequencyShift + chan->elapsedShift44kHzTime;
      }
      else
      {
        LODWORD(v79) = current44kHz - chan->trigger44kHzTime;
        v22 = (double)SLODWORD(v79) * frequencyshift;
      }
      chan->lastFrequencyShift = frequencyshift;
      chan->elapsedShift44kHzTime = v22;
      elapsedShift44kHzTime = chan->elapsedShift44kHzTime;
      chan->lastShift44kHzTime = current44kHz;
      samples = (int)elapsedShift44kHzTime;
      v21 = (int)elapsedShift44kHzTime;
    }
    else
    {
      v20 = current44kHz;
      v21 = current44kHz - chan->trigger44kHzTime;
    }
    v24 = ((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0;
    if ( !idSoundSystemLocal::useOpenAL )
    {
      if ( *(_DWORD *)(SourceRoom + 44) == 2 )
      {
        idSoundChannel::GatherChannelSamples(
          chan,
          2 * v21,
          0x2000,
          (float *)(((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0));
      }
      else
      {
        if ( frequencyshift <= 1.0 )
          v56 = 1.0;
        else
          v56 = frequencyshift;
        idSoundChannel::GatherChannelSamples(
          chan,
          v21,
          (int)(4096.0 * v56),
          (float *)(((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0));
        samples = (int)(frequencyshift * 4096.0);
        if ( samples != 4096 )
        {
          if ( frequencyshift <= 1.0 )
          {
            if ( frequencyshift < 1.0 )
            {
              v59 = 4095;
              jj = 4095;
              v60 = v24 + 16380;
              do
              {
                --v59;
                v60 -= 4;
                v61 = (double)jj * frequencyshift;
                jj = v59;
                samples = (int)v61;
                *(_DWORD *)(v60 + 4) = *(_DWORD *)(v24 + 4 * (int)v61);
              }
              while ( v59 > -1 );
            }
          }
          else
          {
            *(float *)&v57 = 0.0;
            *(float *)&jj = 0.0;
            do
            {
              v58 = (double)jj;
              jj = ++v57;
              samples = (int)(v58 * frequencyshift);
              *(_DWORD *)(v24 + 4 * v57 - 4) = *(_DWORD *)(v24 + 4 * samples);
            }
            while ( v57 < 4096 );
          }
        }
      }
      if ( global || omni )
      {
        ears[0] = s_globalFraction.internalVar->floatValue * chan->lastVolume;
        ears[1] = s_globalFraction.internalVar->floatValue * chan->lastVolume;
        ears[2] = s_globalFraction.internalVar->floatValue * chan->lastVolume;
        ears[3] = s_globalFraction.internalVar->floatValue * chan->lastVolume;
        ears[4] = s_globalFraction.internalVar->floatValue * chan->lastVolume;
        ears[5] = s_globalFraction.internalVar->floatValue * chan->lastVolume;
        ears[3] = idSoundSystemLocal::s_subFraction.internalVar->floatValue * chan->lastVolume;
      }
      else
      {
        v77 = spatialize;
        lastV = (idSoundChannel *)ears;
        qmemcpy(&v75, &v86->listenerAxis, sizeof(v75));
        LODWORD(v74.x) = SourceOcclusion.lOcclusion;
        *(_QWORD *)&v74.y = *(_QWORD *)&SourceOcclusion.flOcclusionLFRatio;
        idSoundSystemLocal::CalcEars(v86, numSpeakers, v74, v86->listenerPos, v75, ears, spatialize);
        v20 = current44kHz;
        ears[0] = ears[0] * chan->lastVolume;
        ears[1] = ears[1] * chan->lastVolume;
        ears[2] = ears[2] * chan->lastVolume;
        ears[3] = ears[3] * chan->lastVolume;
        ears[4] = ears[4] * chan->lastVolume;
        ears[5] = ears[5] * chan->lastVolume;
      }
      if ( idSoundSystemLocal::s_clipVolumes.internalVar->integerValue && SLOBYTE(chan->parms.soundShaderFlags) >= 0 )
      {
        if ( ears[0] > 1.0 )
          ears[0] = 1.0;
        if ( ears[1] > 1.0 )
          ears[1] = 1.0;
        if ( ears[2] > 1.0 )
          ears[2] = 1.0;
        if ( ears[3] > 1.0 )
          ears[3] = 1.0;
        if ( ears[4] > 1.0 )
          ears[4] = 1.0;
        if ( ears[5] > 1.0 )
          ears[5] = 1.0;
      }
      if ( v20 == chan->trigger44kHzTime )
      {
        v62 = ears[1];
        v63 = ears[2];
        chan->lastV[0] = ears[0];
        v64 = ears[3];
        chan->lastV[1] = v62;
        v65 = ears[4];
        chan->lastV[2] = v63;
        v66 = ears[5];
        chan->lastV[3] = v64;
        chan->lastV[4] = v65;
        chan->lastV[5] = v66;
      }
      if ( numSpeakers == 6 )
      {
        v13 = *(_DWORD *)(SourceRoom + 44) == 1;
        v67 = SIMDProcessor->__vftable;
        v77 = COERCE_FLOAT(ears);
        lastV = (idSoundChannel *)chan->lastV;
        LODWORD(v75.mat[2].z) = 4096;
        LODWORD(v75.mat[2].y) = ((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0;
        if ( v13 )
          ((void (__stdcall *)(_DWORD, _DWORD, idSoundChannel *, _DWORD))v67->MixSoundSixSpeakerMono)(
            LODWORD(v75.mat[2].y),
            LODWORD(v75.mat[2].z),
            lastV,
            LODWORD(v77));
        else
          ((void (__stdcall *)(_DWORD, _DWORD, idSoundChannel *, _DWORD))v67->MixSoundSixSpeakerStereo)(
            LODWORD(v75.mat[2].y),
            LODWORD(v75.mat[2].z),
            lastV,
            LODWORD(v77));
      }
      else
      {
        v13 = *(_DWORD *)(SourceRoom + 44) == 1;
        v68 = SIMDProcessor->__vftable;
        v77 = COERCE_FLOAT(ears);
        lastV = (idSoundChannel *)chan->lastV;
        LODWORD(v75.mat[2].z) = 4096;
        LODWORD(v75.mat[2].y) = ((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0;
        if ( v13 )
          ((void (__stdcall *)(_DWORD, _DWORD, idSoundChannel *, _DWORD))v68->MixSoundTwoSpeakerMono)(
            LODWORD(v75.mat[2].y),
            LODWORD(v75.mat[2].z),
            lastV,
            LODWORD(v77));
        else
          ((void (__stdcall *)(_DWORD, _DWORD, idSoundChannel *, _DWORD))v68->MixSoundTwoSpeakerStereo)(
            LODWORD(v75.mat[2].y),
            LODWORD(v75.mat[2].z),
            lastV,
            LODWORD(v77));
      }
      v69 = ears[1];
      v70 = ears[2];
      chan->lastV[0] = ears[0];
      v71 = ears[3];
      chan->lastV[1] = v69;
      v72 = ears[4];
      chan->lastV[2] = v70;
      v73 = ears[5];
      chan->lastV[3] = v71;
      chan->lastV[4] = v72;
      chan->lastV[5] = v73;
      goto LABEL_173;
    }
    if ( sound->removeStatus >= REMOVE_STATUS_SAMPLEFINISHED )
      goto LABEL_173;
    if ( chan->openalSource != -1 )
    {
      if ( qalIsSource(chan->openalSource) )
        goto LABEL_43;
      v10 = looping;
    }
    leadinSample = chan->leadinSample;
    v26 = !leadinSample->hardwareBuffer || !chan->soundShader->entries[0][1].name.baseBuffer[8] || v10;
    chan->openalSource = idSoundSystemLocal::AllocOpenALSource(v86, chan, v26, leadinSample->nChannels == 2);
LABEL_43:
    if ( chan->openalSource == -1 || !qalIsSource(chan->openalSource) )
      goto LABEL_173;
    if ( chan->triggered )
      qalSourceStop(chan->openalSource);
    if ( global || omni )
    {
      qalSourcei(chan->openalSource, 514, 1);
      qalSource3f(chan->openalSource, 4100, 0.0, 0.0, 0.0);
    }
    else
    {
      qalSourcei(chan->openalSource, 514, 0);
      openalSource = chan->openalSource;
      v77 = -*(float *)&SourceOcclusion.lOcclusion;
      v75.mat[2].z = -SourceOcclusion.flOcclusionLFRatio;
      qalSource3f(openalSource, 4100, v75.mat[2].z, SourceOcclusion.flOcclusionRoomRatio, v77);
    }
    if ( chan->lastVolume >= 1.0 )
      v79 = 1.0;
    else
      v79 = chan->lastVolume;
    qalSourcef(chan->openalSource, 4106, v79);
    v28 = looping && chan->soundShader->entries[0][1].name.baseBuffer[8];
    qalSourcei(chan->openalSource, 4103, v28);
    qalSourcef(chan->openalSource, 4128, *(float *)&finishedbuffers);
    qalSourcef(chan->openalSource, 4131, *(float *)&jj);
    if ( frequencyshift <= 0.25 )
      *(float *)&jj = 0.25;
    else
      *(float *)&jj = frequencyshift;
    qalSourcef(chan->openalSource, 4099, *(float *)&jj);
    if ( looping )
    {
      if ( !chan->soundShader->entries[0][1].name.baseBuffer[8] )
        goto LABEL_63;
    }
    else if ( !chan->leadinSample->hardwareBuffer )
    {
LABEL_63:
      if ( chan->triggered )
      {
        v29 = chan->openalSource;
        finishedbuffers = 3;
        qalSourcei(v29, 4105, 0);
        qalDeleteBuffers(3u, chan->lastopenalStreamingBuffer);
        v30 = chan->openalStreamingBuffer[0];
        v31 = chan->openalStreamingBuffer[1];
        v32 = chan->openalStreamingBuffer[2];
        LODWORD(v75.mat[1].z) = chan->openalStreamingBuffer;
        LODWORD(v75.mat[1].y) = 3;
        chan->lastopenalStreamingBuffer[0] = v30;
        chan->lastopenalStreamingBuffer[1] = v31;
        chan->lastopenalStreamingBuffer[2] = v32;
        qalGenBuffers(LODWORD(v75.mat[1].y), (unsigned int *)LODWORD(v75.mat[1].z));
        if ( v86->alEAXSetBufferMode )
        {
          EnumValue = qalGetEnumValue("AL_STORAGE_ACCESSIBLE");
          v86->alEAXSetBufferMode(3u, chan->openalStreamingBuffer, EnumValue);
        }
        v34 = *(float *)&chan->openalStreamingBuffer[1];
        v35 = *(float *)&chan->openalStreamingBuffer[2];
        SourceOcclusion.lOcclusion = chan->openalStreamingBuffer[0];
        SourceOcclusion.flOcclusionLFRatio = v34;
        SourceOcclusion.flOcclusionRoomRatio = v35;
      }
      else
      {
        v37 = chan->openalSource;
        *(float *)&finishedbuffers = 0.0;
        qalGetSourcei(v37, 4118, &finishedbuffers);
        v38 = finishedbuffers;
        if ( finishedbuffers >= 3 )
        {
          v38 = 3;
          finishedbuffers = 3;
        }
        qalSourceUnqueueBuffers(chan->openalSource, v38, (unsigned int *)&SourceOcclusion);
        if ( finishedbuffers == 3 )
          chan->triggered = 1;
      }
      *(float *)&jj = 0.0;
      samples = (int)(frequencyshift * 4096.0);
      if ( finishedbuffers > 0 )
      {
        v39 = samples;
        p_SourceOcclusion = &SourceOcclusion;
        do
        {
          if ( idSoundChannel::GatherChannelSamples(
                 chan,
                 *(_DWORD *)(SourceRoom + 44) * chan->openalStreamingOffset,
                 v39 * *(_DWORD *)(SourceRoom + 44),
                 (float *)(((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0)) )
          {
            v41 = SourceRoom;
            for ( i = 0; i < v39 * *(_DWORD *)(v41 + 44); ++i )
            {
              if ( *(float *)(v24 + 4 * i) >= -32768.0 )
              {
                if ( *(float *)(v24 + 4 * i) <= 32767.0 )
                {
                  samples = *(int *)(v24 + 4 * i);
                  LODWORD(spatialize) = (int)*(float *)&samples;
                  *(_WORD *)(v24 + 2 * i) = LOWORD(spatialize);
                }
                else
                {
                  *(_WORD *)(v24 + 2 * i) = 0x7FFF;
                }
              }
              else
              {
                *(_WORD *)(v24 + 2 * i) = 0x8000;
              }
            }
            qalBufferData(
              p_SourceOcclusion->lOcclusion,
              2 * (chan->leadinSample->nChannels != 1) + 4353,
              (void *)(((unsigned int)&inputSamples[3] + 3) & 0xFFFFFFF0),
              2 * v39 * *(_DWORD *)(SourceRoom + 44),
              0xAC44u);
            qalSourceQueueBuffers(chan->openalSource, 1u, (unsigned int *)p_SourceOcclusion);
            chan->openalStreamingOffset += v39;
          }
          p_SourceOcclusion = (_EAXOCCLUSIONPROPERTIES *)((char *)p_SourceOcclusion + 4);
          ++jj;
        }
        while ( jj < finishedbuffers );
      }
      goto LABEL_89;
    }
    if ( chan->triggered )
    {
      if ( looping )
        openalBuffer = *(_DWORD *)&chan->soundShader->entries[0][1].name.baseBuffer[4];
      else
        openalBuffer = chan->leadinSample->openalBuffer;
      qalSourcei(chan->openalSource, 4105, openalBuffer);
    }
LABEL_89:
    if ( !idSoundSystemLocal::useEAXReverb || chan->leadinSample->nChannels != 1 || !v86->efxloaded )
      goto LABEL_111;
    lastValidPortalArea = sound->lastValidPortalArea;
    v44 = v86;
    if ( lastValidPortalArea == v86->efxSlotToArea[0] )
    {
      efxSlotId = v86->efxSlotId;
    }
    else if ( lastValidPortalArea == v86->efxSlotToArea[1] )
    {
      efxSlotId = &v86->efxSlotId[1];
    }
    else if ( lastValidPortalArea == v86->efxSlotToArea[2] )
    {
      efxSlotId = &v86->efxSlotId[2];
    }
    else
    {
      if ( lastValidPortalArea != v86->efxSlotToArea[3] )
      {
        SourceActiveSlot.guidActiveFXSlots[0] = EAX_NULL_GUID;
LABEL_102:
        v13 = chan->triggerChannel == 10;
        SourceActiveSlot.guidActiveFXSlots[1] = EAX_PrimaryFXSlotID;
        SourceActiveSlot.guidActiveFXSlots[2] = EAX_NULL_GUID;
        SourceActiveSlot.guidActiveFXSlots[3] = EAX_NULL_GUID;
        if ( v13 )
          SourceRoom = -10000;
        else
          SourceRoom = (chan->parms.soundShaderFlags & 0x2000) != 0 ? 0xFFFFFE0C : 0;
        alEAXSet = v44->alEAXSet;
        if ( !alEAXSet )
          goto LABEL_111;
        if ( v44->eaxVersion == 6 )
        {
          alEAXSet(&EAXPROPERTYID_EAX50_Source, 27u, chan->openalSource, &SourceActiveSlot, 64u);
          v48 = *(float *)&chan->openalSource;
          LODWORD(v75.mat[1].z) = 4;
          LODWORD(v75.mat[1].y) = &SourceRoom;
          v75.mat[1].x = v48;
          LODWORD(v75.mat[0].z) = 7;
          LODWORD(v75.mat[0].y) = &EAXPROPERTYID_EAX50_Source;
        }
        else
        {
          if ( v44->eaxVersion != 5 )
            goto LABEL_111;
          alEAXSet(&EAXPROPERTYID_EAX40_Source, 27u, chan->openalSource, &SourceActiveSlot, 64u);
          v49 = *(float *)&chan->openalSource;
          LODWORD(v75.mat[1].z) = 4;
          LODWORD(v75.mat[1].y) = &SourceRoom;
          v75.mat[1].x = v49;
          LODWORD(v75.mat[0].z) = 7;
          LODWORD(v75.mat[0].y) = &EAXPROPERTYID_EAX40_Source;
        }
        v44->alEAXSet(
          (const _GUID *)LODWORD(v75.mat[0].y),
          LODWORD(v75.mat[0].z),
          LODWORD(v75.mat[1].x),
          (void *)LODWORD(v75.mat[1].y),
          LODWORD(v75.mat[1].z));
LABEL_111:
        if ( idSoundSystemLocal::useEAXOcclusion && chan->leadinSample->nChannels == 1 )
        {
          numPortals = sound->numPortals;
          SourceOcclusion.lOcclusion = 0;
          if ( numPortals && !noOcclusion )
            SourceOcclusion.lOcclusion = -1500 * numPortals;
          v51 = v86->alEAXSet;
          SourceOcclusion.flOcclusionLFRatio = 0.0;
          SourceOcclusion.flOcclusionRoomRatio = 1.5;
          SourceOcclusion.flOcclusionDirectRatio = 1.0;
          if ( v51 )
          {
            if ( v86->eaxVersion == 6 )
            {
              v52 = *(float *)&chan->openalSource;
              LODWORD(v77) = 16;
              lastV = (idSoundChannel *)&SourceOcclusion;
              v75.mat[2].z = v52;
              LODWORD(v75.mat[2].y) = 3;
              LODWORD(v75.mat[2].x) = &EAXPROPERTYID_EAX50_Source;
            }
            else
            {
              if ( v86->eaxVersion != 5 )
                goto LABEL_122;
              v53 = *(float *)&chan->openalSource;
              LODWORD(v77) = 16;
              lastV = (idSoundChannel *)&SourceOcclusion;
              v75.mat[2].z = v53;
              LODWORD(v75.mat[2].y) = 3;
              LODWORD(v75.mat[2].x) = &EAXPROPERTYID_EAX40_Source;
            }
            v51((const _GUID *)LODWORD(v75.mat[2].x), LODWORD(v75.mat[2].y), LODWORD(v75.mat[2].z), lastV, LODWORD(v77));
          }
        }
LABEL_122:
        if ( chan->triggered )
        {
          if ( looping )
          {
            if ( !chan->soundShader->entries[0][1].name.baseBuffer[8] )
              goto LABEL_131;
          }
          else if ( !chan->leadinSample->hardwareBuffer )
          {
LABEL_131:
            qalSourcePlay(chan->openalSource);
            chan->triggered = 0;
            goto LABEL_173;
          }
          openalStreamingOffset = chan->openalStreamingOffset;
          if ( openalStreamingOffset >= 0x1000 )
            v55 = openalStreamingOffset - 4096;
          else
            v55 = 0;
          chan->openalStreamingOffset = v55;
          if ( v55 )
            goto LABEL_173;
          goto LABEL_131;
        }
LABEL_173:
        ++v86->soundStats.activeSounds;
        return;
      }
      efxSlotId = &v86->efxSlotId[3];
    }
    SourceActiveSlot.guidActiveFXSlots[0].Data1 = efxSlotId->Data1;
    *(_DWORD *)&SourceActiveSlot.guidActiveFXSlots[0].Data2 = *(_DWORD *)&efxSlotId->Data2;
    *(_DWORD *)SourceActiveSlot.guidActiveFXSlots[0].Data4 = *(_DWORD *)efxSlotId->Data4;
    v46 = *(_DWORD *)&efxSlotId->Data4[4];
    v44 = v86;
    *(_DWORD *)&SourceActiveSlot.guidActiveFXSlots[0].Data4[4] = v46;
    goto LABEL_102;
  }
}

// FUNC: public: float __thiscall idSoundSystemLocal::FindAmplitude(class idSoundEmitterLocal *,int,class idVec3 const *,int,bool)
long double __thiscall idSoundSystemLocal::FindAmplitude(
        idSoundSystemLocal *this,
        idSoundEmitterLocal *sound,
        const int localTime,
        const idVec3 *listenerPosition,
        int channel,
        bool shakesOnly)
{
  const idVec3 *v6; // edi
  double v7; // st6
  double v8; // st5
  int *p_soundShaderFlags; // esi
  int v10; // ecx
  bool v11; // bl
  double v12; // st7
  double v13; // st7
  int v14; // edi
  const char *ShakeData; // eax
  unsigned int v16; // ebp
  unsigned int v17; // edx
  double v18; // st7
  float dlen; // [esp+4h] [ebp-24h]
  float mind; // [esp+8h] [ebp-20h]
  int activeChannelCount; // [esp+Ch] [ebp-1Ch]
  float high; // [esp+10h] [ebp-18h]
  float shakes; // [esp+14h] [ebp-14h]
  float maxd; // [esp+18h] [ebp-10h]
  float preprocessedScale; // [esp+1Ch] [ebp-Ch]
  int v27; // [esp+20h] [ebp-8h]
  float sounda; // [esp+2Ch] [ebp+4h]

  if ( !sound->playing )
    return 0.0;
  v6 = listenerPosition;
  if ( listenerPosition )
  {
    preprocessedScale = 600.0;
    v7 = sound->origin.y - listenerPosition->y;
    v8 = sound->origin.z - listenerPosition->z;
    dlen = sqrt(v8 * v8 + v7 * v7 + (sound->origin.x - listenerPosition->x) * (sound->origin.x - listenerPosition->x));
  }
  else
  {
    dlen = 1.0;
    preprocessedScale = 2800.0;
  }
  activeChannelCount = 0;
  high = 0.0;
  p_soundShaderFlags = &sound->channels[0].parms.soundShaderFlags;
  v27 = 8;
  do
  {
    if ( *((_BYTE *)p_soundShaderFlags - 28) && (!channel || p_soundShaderFlags[7] == channel) )
    {
      v10 = *p_soundShaderFlags;
      v11 = (*p_soundShaderFlags & 0x20) != 0;
      shakes = *((float *)p_soundShaderFlags - 1);
      if ( !shakesOnly || shakes > 0.0 )
      {
        if ( !v6 )
        {
          sounda = 1.0;
          if ( (v10 & 0x100) != 0 )
          {
            v12 = 32767.0;
          }
          else
          {
LABEL_27:
            v14 = localTime - *(p_soundShaderFlags - 6);
            ShakeData = idSoundShader::GetShakeData((idSoundShader *)p_soundShaderFlags[8], p_soundShaderFlags[6]);
            if ( !ShakeData || !*ShakeData )
              goto LABEL_37;
            v16 = 0;
            do
              ++v16;
            while ( ShakeData[v16] );
            v17 = 30 * v14 / 0xAC44u;
            if ( v11 )
              v17 %= v16;
            if ( v17 >= v16 )
            {
LABEL_37:
              v6 = listenerPosition;
              goto LABEL_38;
            }
            v6 = listenerPosition;
            v12 = (double)(ShakeData[v17] - 97) * preprocessedScale;
          }
          v18 = v12 * sounda;
          ++activeChannelCount;
          if ( v18 > high )
            high = v18;
          goto LABEL_38;
        }
        sounda = *((float *)p_soundShaderFlags - 3);
        if ( shakesOnly )
          sounda = sounda * shakes;
        if ( (v10 & 8) == 0 )
        {
          maxd = *((float *)p_soundShaderFlags - 4);
          mind = *((float *)p_soundShaderFlags - 5);
          if ( dlen >= (double)maxd )
            goto LABEL_38;
          if ( dlen > (double)mind )
          {
            v13 = 1.0 - (dlen - mind) / (maxd - mind);
            if ( v13 >= 0.0 )
            {
              if ( v13 > 1.0 )
                v13 = 1.0;
            }
            else
            {
              v13 = 0.0;
            }
            if ( s_quadraticFalloff.internalVar->integerValue )
              v13 = v13 * v13;
            sounda = v13 * sounda;
          }
        }
        if ( sounda > 0.0 )
          goto LABEL_27;
      }
    }
LABEL_38:
    p_soundShaderFlags += 41;
    --v27;
  }
  while ( v27 );
  if ( !activeChannelCount )
    return 0.0;
  return atan2(high * 0.000030518509, 1.0) / (idMath::M_DEG2RAD * 45.0);
}

// FUNC: public: virtual float __thiscall idSoundSystemLocal::CurrentShakeAmplitudeForPosition(int,int,class idVec3 const &)
double __thiscall idSoundSystemLocal::CurrentShakeAmplitudeForPosition(
        idSoundSystemLocal *this,
        int worldId,
        int time,
        const idVec3 *listererPosition)
{
  int Current44kHzTime; // ebx
  int i; // edi
  idSoundEmitterLocal *v8; // eax
  float amp; // [esp+4h] [ebp-4h]

  amp = 0.0;
  if ( s_constantAmplitude.internalVar->floatValue >= 0.0 )
    return 0.0;
  Current44kHzTime = idSoundSystemLocal::GetCurrent44kHzTime(this);
  for ( i = 1; i < this->GetNumEmitters(this); ++i )
  {
    v8 = this->emitters.list[i];
    if ( v8->hasShakes )
      amp = idSoundSystemLocal::FindAmplitude(this, v8, Current44kHzTime, listererPosition, 0, 1) + amp;
  }
  return amp;
}

// FUNC: public: void __thiscall idSoundSystemLocal::MixLoop(int,int,int,float *)
void __thiscall idSoundSystemLocal::MixLoop(
        idSoundSystemLocal *this,
        int worldId,
        int current44kHz,
        int numSpeakers,
        float *finalMixBuffer)
{
  bool v6; // zf
  float z; // edx
  float v8; // eax
  float v9; // ecx
  double y; // st7
  int v11; // eax
  int v12; // ebx
  double v13; // st7
  int v14; // esi
  int j; // ecx
  int v16; // edi
  idVec3 *Center; // eax
  double v18; // st6
  double v19; // st5
  double v20; // st3
  double v21; // st4
  int v22; // ecx
  exitPortal_t *v23; // eax
  int v24; // edx
  const idWinding *w; // ecx
  int blockingBits; // edx
  int portalHandle; // ecx
  float v28; // edi
  int v29; // eax
  double v30; // st7
  int v31; // edx
  int k; // ecx
  idWinding *v33; // esi
  double v34; // st7
  double v35; // st6
  long double v36; // st6
  long double v37; // st6
  double v38; // st7
  double v39; // st6
  long double v40; // st6
  long double v41; // st6
  idVec3 *v42; // eax
  double v43; // st7
  double v44; // st6
  double v45; // st5
  long double v46; // st7
  double v47; // st7
  double v48; // st7
  double v49; // st6
  double v50; // st5
  idWinding *v51; // esi
  double v52; // st7
  long double v53; // st6
  long double v54; // st6
  double v55; // st7
  long double v56; // st6
  long double v57; // st6
  idVec3 *v58; // eax
  double v59; // st7
  double v60; // st6
  double v61; // st5
  long double v62; // st7
  int v63; // eax
  idSoundSystemLocal_vtbl *v64; // esi
  int v65; // eax
  const char *v66; // eax
  const char *v67; // esi
  int v68; // edi
  char *data; // edx
  char *v70; // ecx
  char v71; // al
  idSoundEffect *v72; // eax
  int v73; // eax
  char v74; // cl
  void *v75; // esi
  float v76; // esi
  int v77; // eax
  int v78; // edx
  int (__cdecl *alEAXSet)(const _GUID *, unsigned int, unsigned int, void *, unsigned int); // eax
  int v80; // ecx
  float v81; // eax
  double v82; // st7
  int v83; // edx
  int m; // ecx
  idWinding *v85; // esi
  double v86; // st7
  double v87; // st6
  long double v88; // st6
  long double v89; // st6
  double v90; // st7
  double v91; // st6
  long double v92; // st6
  long double v93; // st6
  idVec3 *v94; // eax
  double v95; // st7
  double v96; // st6
  double v97; // st5
  long double v98; // st7
  double v99; // st7
  double v100; // st7
  double v101; // st6
  double v102; // st5
  idWinding *v103; // esi
  double v104; // st7
  double v105; // st6
  long double v106; // st6
  long double v107; // st6
  double v108; // st7
  double v109; // st6
  long double v110; // st6
  long double v111; // st6
  idVec3 *v112; // eax
  double v113; // st7
  double v114; // st6
  double v115; // st5
  long double v116; // st7
  int v117; // eax
  idSoundSystemLocal_vtbl *v118; // esi
  int v119; // eax
  const char *v120; // esi
  unsigned int v121; // eax
  int v122; // edi
  int v123; // eax
  char *v124; // edx
  const char *v125; // ecx
  char v126; // al
  idSoundEffect *v127; // eax
  char v128; // cl
  void *v129; // esi
  int v130; // edi
  float v131; // esi
  int v132; // eax
  int (__cdecl *v133)(const _GUID *, unsigned int, unsigned int, void *, unsigned int); // eax
  int v134; // eax
  int *v135; // ecx
  int (__cdecl *v136)(const _GUID *, unsigned int, unsigned int, void *, unsigned int); // ecx
  int integerValue; // esi
  idSoundEmitterLocal *v138; // edi
  idSoundChannel *v139; // esi
  int v140; // eax
  idSoundSystemLocal_vtbl *v141; // eax
  int v142; // esi
  idSoundEmitterLocal *v143; // edi
  idSoundChannel *channels; // esi
  int v145; // ebx
  bool v146; // c0
  bool v147; // c3
  float v148; // ecx
  float *n; // edx
  idSoundSystemLocal_vtbl *v150; // edx
  float v151; // edi
  int v152; // ebx
  idSoundChannel *v153; // esi
  int *efxSlotToArea; // [esp+1Ch] [ebp-24Ch]
  float v155; // [esp+1Ch] [ebp-24Ch]
  float v156; // [esp+1Ch] [ebp-24Ch]
  float v157; // [esp+1Ch] [ebp-24Ch]
  float v158; // [esp+1Ch] [ebp-24Ch]
  float v159; // [esp+1Ch] [ebp-24Ch]
  float v160; // [esp+1Ch] [ebp-24Ch]
  float numEmitters; // [esp+20h] [ebp-248h]
  float numEmittersa; // [esp+20h] [ebp-248h]
  int numEmittersb; // [esp+20h] [ebp-248h]
  int numEmittersc; // [esp+20h] [ebp-248h]
  int numEmittersd; // [esp+20h] [ebp-248h]
  int numPortals; // [esp+24h] [ebp-244h]
  _GUID *numPortalsa; // [esp+24h] [ebp-244h]
  float numPortalsc; // [esp+24h] [ebp-244h]
  float numPortalsd; // [esp+24h] [ebp-244h]
  float numPortalse; // [esp+24h] [ebp-244h]
  int numPortalsb; // [esp+24h] [ebp-244h]
  int index; // [esp+28h] [ebp-240h] BYREF
  idSoundEffect *v173; // [esp+2Ch] [ebp-23Ch] BYREF
  int i; // [esp+30h] [ebp-238h]
  int EnvironmentID; // [esp+34h] [ebp-234h] BYREF
  idSoundEffect *effect; // [esp+38h] [ebp-230h] BYREF
  float maxVolume; // [esp+3Ch] [ebp-22Ch]
  idVec3 left; // [esp+40h] [ebp-228h]
  idVec3 right; // [esp+4Ch] [ebp-21Ch]
  float farthestDistance; // [esp+58h] [ebp-210h] BYREF
  idVec3 direction; // [esp+5Ch] [ebp-20Ch]
  const idWinding **p_w; // [esp+68h] [ebp-200h]
  idBounds boundary; // [esp+6Ch] [ebp-1FCh] BYREF
  _EAXVECTOR EnvironmentDirection; // [esp+84h] [ebp-1E4h]
  float closestDistance[4]; // [esp+90h] [ebp-1D8h]
  int closestArea[4]; // [esp+A0h] [ebp-1C8h] BYREF
  float v187; // [esp+B0h] [ebp-1B8h]
  float v188; // [esp+BCh] [ebp-1ACh]
  float v189; // [esp+C8h] [ebp-1A0h]
  float v190; // [esp+D4h] [ebp-194h]
  idVec3 result; // [esp+E0h] [ebp-188h] BYREF
  float v192; // [esp+ECh] [ebp-17Ch]
  idStr name; // [esp+F8h] [ebp-170h] BYREF
  exitPortal_t portal; // [esp+118h] [ebp-150h] BYREF
  idStr v195; // [esp+12Ch] [ebp-13Ch] BYREF
  float listenerPosition[3]; // [esp+14Ch] [ebp-11Ch] BYREF
  float listenerOrientation[6]; // [esp+158h] [ebp-110h] BYREF
  idStr temp; // [esp+170h] [ebp-F8h] BYREF
  idVec3 v199; // [esp+190h] [ebp-D8h] BYREF
  _EAXREVERBPROPERTIES EnvironmentParameters; // [esp+19Ch] [ebp-CCh] BYREF
  exitPortal_t closestPortal[4]; // [esp+20Ch] [ebp-5Ch] BYREF
  int v202; // [esp+264h] [ebp-4h]

  temp.len = 0;
  temp.alloced = 20;
  temp.data = temp.baseBuffer;
  temp.baseBuffer[0] = 0;
  v6 = this->activeSoundWorld == 1;
  v202 = 0;
  if ( v6 && this->listenerArea == -1 )
  {
    if ( idSoundSystemLocal::useOpenAL )
      qalListenerf(4106, 0.0);
    v202 = -1;
    idStr::FreeData(&temp);
    return;
  }
  if ( !idSoundSystemLocal::useOpenAL )
    goto LABEL_126;
  z = this->listenerPos.z;
  v8 = this->listenerAxis.mat[0].z;
  listenerPosition[0] = -this->listenerPos.y;
  v9 = this->listenerAxis.mat[2].z;
  listenerPosition[2] = -this->listenerPos.x;
  listenerPosition[1] = z;
  y = this->listenerAxis.mat[0].y;
  listenerOrientation[1] = v8;
  listenerOrientation[4] = v9;
  listenerOrientation[0] = -y;
  listenerOrientation[2] = -this->listenerAxis.mat[0].x;
  listenerOrientation[3] = -this->listenerAxis.mat[2].y;
  listenerOrientation[5] = -this->listenerAxis.mat[2].x;
  qalListenerf(4106, 1.0);
  qalListenerfv(4100, listenerPosition);
  qalListenerfv(4111, listenerOrientation);
  if ( !idSoundSystemLocal::useEAXReverb || !this->efxloaded )
    goto LABEL_126;
  closestArea[0] = this->listenerArea;
  memset(&closestArea[1], 255, 12);
  closestDistance[0] = 0.0;
  closestDistance[1] = 3.4028235e38;
  closestDistance[2] = 3.4028235e38;
  closestDistance[3] = 3.4028235e38;
  if ( closestArea[0] < 0 || closestArea[0] >= this->rw->NumAreas(this->rw) )
    v11 = 0;
  else
    v11 = this->rw->NumPortalsInArea(this->rw, closestArea[0]);
  v12 = 0;
  for ( numPortals = v11; v12 < numPortals; ++v12 )
  {
    (*(void (__thiscall **)(idRenderWorld *, exitPortal_t *, int, int))this->rw->gapA8)(
      this->rw,
      &portal,
      this->listenerArea,
      v12);
    v13 = closestDistance[0];
    farthestDistance = closestDistance[0];
    v14 = 0;
    for ( j = 1; j < 4; ++j )
    {
      if ( v13 < closestDistance[j] )
      {
        v14 = j;
        v13 = closestDistance[j];
      }
    }
    farthestDistance = v13;
    v16 = portal.areas[0];
    if ( portal.areas[0] == this->listenerArea )
      v16 = portal.areas[1];
    Center = idWinding::GetCenter((idWinding *)portal.w, &result);
    v18 = Center->y - this->listenerPos.y;
    v19 = Center->x - this->listenerPos.x;
    v20 = Center->z - this->listenerPos.z;
    v21 = v19 * v19 + v18 * v18 + v20 * v20;
    if ( v21 > 0.0 && v21 < farthestDistance )
    {
      v22 = portal.areas[0];
      closestDistance[v14] = v21;
      v23 = &closestPortal[v14];
      v24 = portal.areas[1];
      v23->areas[0] = v22;
      w = portal.w;
      v23->areas[1] = v24;
      blockingBits = portal.blockingBits;
      v23->w = w;
      portalHandle = portal.portalHandle;
      v23->blockingBits = blockingBits;
      closestArea[v14] = v16;
      v23->portalHandle = portalHandle;
    }
  }
  numPortalsa = this->efxSlotId;
  farthestDistance = *(float *)this->efxSlotAvailable;
  i = 0;
  efxSlotToArea = this->efxSlotToArea;
  do
  {
    v28 = 0.0;
    maxVolume = 0.0;
    p_w = &closestPortal[0].w;
    do
    {
      v29 = closestArea[LODWORD(v28)];
      if ( v29 == -1 || *efxSlotToArea != v29 )
        goto LABEL_68;
      v6 = v29 == this->listenerArea;
      *(float *)&effect = 0.0;
      *(float *)&EnvironmentID = NAN;
      if ( !v6 )
      {
        v51 = (idWinding *)*p_w;
        idWinding::GetBounds((idWinding *)*p_w, &boundary);
        v52 = boundary.b[0].z - this->listenerPos.z;
        *(float *)&v173 = boundary.b[0].y - this->listenerPos.y;
        LODWORD(left.y) = v173;
        v188 = boundary.b[0].x - this->listenerPos.x;
        left.x = v188;
        left.z = v52;
        v53 = v188 * v188 + *(float *)&v173 * *(float *)&v173 + v52 * v52;
        if ( v53 != 0.0 )
        {
          v54 = 1.0 / sqrt(v53);
          left.x = v188 * v54;
          left.y = *(float *)&v173 * v54;
          left.z = v54 * v52;
        }
        v55 = boundary.b[1].z - this->listenerPos.z;
        *(float *)&v173 = boundary.b[1].y - this->listenerPos.y;
        LODWORD(right.y) = v173;
        v189 = boundary.b[1].x - this->listenerPos.x;
        right.x = v189;
        right.z = v55;
        v56 = v189 * v189 + *(float *)&v173 * *(float *)&v173 + v55 * v55;
        if ( v56 != 0.0 )
        {
          v57 = 1.0 / sqrt(v56);
          right.x = v189 * v57;
          right.y = *(float *)&v173 * v57;
          right.z = v57 * v55;
        }
        v58 = idWinding::GetCenter(v51, (idVec3 *)&portal);
        *(float *)&numEmittersc = v58->z - this->listenerPos.z;
        *(float *)&v173 = v58->y - this->listenerPos.y;
        v59 = v58->x - this->listenerPos.x;
        result.x = v59;
        v60 = *(float *)&v173;
        v61 = *(float *)&numEmittersc;
        *(float *)&index = result.x * result.x
                         + *(float *)&v173 * *(float *)&v173
                         + *(float *)&numEmittersc * *(float *)&numEmittersc;
        if ( *(float *)&index != 0.0 )
        {
          v62 = 1.0 / sqrt(*(float *)&index);
          *(float *)&index = v62;
          v59 = v62 * result.x;
          v60 = *(float *)&index * *(float *)&v173;
          v61 = *(float *)&index * *(float *)&numEmittersc;
        }
        direction.x = v61 * this->listenerAxis.mat[0].z
                    + v60 * this->listenerAxis.mat[0].y
                    + v59 * this->listenerAxis.mat[0].x;
        direction.y = v61 * this->listenerAxis.mat[1].z
                    + v60 * this->listenerAxis.mat[1].y
                    + v59 * this->listenerAxis.mat[1].x;
        direction.z = v61 * this->listenerAxis.mat[2].z
                    + v60 * this->listenerAxis.mat[2].y
                    + v59 * this->listenerAxis.mat[2].x;
        v47 = (right.z * left.z + right.y * left.y + right.x * left.x + 1.0) * 0.18099999 + 0.63700002;
        goto LABEL_49;
      }
      v30 = 3.4028235e38;
      v31 = 4;
      for ( k = 1; k < 4; ++k )
      {
        if ( v30 > closestDistance[k] )
        {
          v31 = k;
          v30 = closestDistance[k];
        }
      }
      if ( v31 < 4 )
      {
        v33 = (idWinding *)closestPortal[v31].w;
        idWinding::GetBounds(v33, &boundary);
        v34 = boundary.b[0].z - this->listenerPos.z;
        numEmitters = boundary.b[0].y - this->listenerPos.y;
        v35 = boundary.b[0].x - this->listenerPos.x;
        left.y = numEmitters;
        v190 = v35;
        left.x = v190;
        left.z = v34;
        v36 = v190 * v190 + numEmitters * numEmitters + v34 * v34;
        if ( v36 != 0.0 )
        {
          v37 = 1.0 / sqrt(v36);
          left.x = v190 * v37;
          left.y = numEmitters * v37;
          left.z = v37 * v34;
        }
        v38 = boundary.b[1].z - this->listenerPos.z;
        numEmittersa = boundary.b[1].y - this->listenerPos.y;
        v39 = boundary.b[1].x - this->listenerPos.x;
        right.y = numEmittersa;
        v187 = v39;
        right.x = v187;
        right.z = v38;
        v40 = v187 * v187 + numEmittersa * numEmittersa + v38 * v38;
        if ( v40 != 0.0 )
        {
          v41 = 1.0 / sqrt(v40);
          right.x = v187 * v41;
          right.y = numEmittersa * v41;
          right.z = v41 * v38;
        }
        v42 = idWinding::GetCenter(v33, &v199);
        *(float *)&v173 = v42->z - this->listenerPos.z;
        *(float *)&numEmittersb = v42->y - this->listenerPos.y;
        v43 = v42->x - this->listenerPos.x;
        v192 = v43;
        v44 = *(float *)&numEmittersb;
        v45 = *(float *)&v173;
        *(float *)&index = v192 * v192
                         + *(float *)&numEmittersb * *(float *)&numEmittersb
                         + *(float *)&v173 * *(float *)&v173;
        if ( *(float *)&index != 0.0 )
        {
          v46 = 1.0 / sqrt(*(float *)&index);
          *(float *)&index = v46;
          v43 = v46 * v192;
          v44 = *(float *)&index * *(float *)&numEmittersb;
          v45 = *(float *)&index * *(float *)&v173;
        }
        direction.x = v45 * this->listenerAxis.mat[0].z
                    + v44 * this->listenerAxis.mat[0].y
                    + v43 * this->listenerAxis.mat[0].x;
        direction.y = v45 * this->listenerAxis.mat[1].z
                    + v44 * this->listenerAxis.mat[1].y
                    + v43 * this->listenerAxis.mat[1].x;
        direction.z = v45 * this->listenerAxis.mat[2].z
                    + v44 * this->listenerAxis.mat[2].y
                    + v43 * this->listenerAxis.mat[2].x;
        v47 = (right.z * left.z + right.y * left.y + right.x * left.x + 1.0) * 0.31850001 - 0.63700002;
LABEL_49:
        *(float *)&index = v47;
        v48 = v47 * direction.x;
        v49 = *(float *)&index * direction.y;
        v50 = *(float *)&index * direction.z;
        goto LABEL_50;
      }
      v48 = 0.0;
      v49 = 0.0;
      v50 = 0.0;
LABEL_50:
      v63 = closestArea[LODWORD(v28)];
      v64 = this->__vftable;
      EnvironmentDirection.x = -v49;
      EnvironmentDirection.y = v50;
      EnvironmentDirection.z = v48;
      v65 = v64->GetReverb(this, v63);
      v66 = v64->GetReverbName(this, v65);
      v67 = v66;
      name.len = 0;
      name.alloced = 20;
      name.data = name.baseBuffer;
      name.baseBuffer[0] = 0;
      if ( v66 )
      {
        v68 = strlen(v66);
        if ( v68 + 1 > 20 )
          idStr::ReAllocate(&name, v68 + 1, 1);
        data = name.data;
        v70 = (char *)v67;
        do
        {
          v71 = *v70;
          *data++ = *v70++;
        }
        while ( v71 );
        name.len = v68;
      }
      LOBYTE(v202) = 1;
      idEFXFile::FindEffect(&this->EFXDatabase, &name, &effect, &EnvironmentID);
      v72 = effect;
      if ( *(float *)&effect != 0.0 )
        goto LABEL_165;
      v195.data = v195.baseBuffer;
      v195.alloced = 20;
      v195.baseBuffer[0] = 0;
      v73 = 0;
      do
      {
        v74 = aDefault_2[v73];
        v195.baseBuffer[v73++] = v74;
      }
      while ( v74 );
      v195.len = 7;
      LOBYTE(v202) = 2;
      idEFXFile::FindEffect(&this->EFXDatabase, &v195, &effect, &EnvironmentID);
      LOBYTE(v202) = 1;
      idStr::FreeData(&v195);
      v72 = effect;
      if ( *(float *)&effect != 0.0 )
      {
LABEL_165:
        v75 = v72->data;
        if ( v75 )
        {
          qmemcpy(&EnvironmentParameters, v75, v72->datasize);
          if ( &EnvironmentParameters )
          {
            v76 = maxVolume;
            v77 = closestArea[LODWORD(maxVolume)];
            v78 = i;
            *efxSlotToArea = v77;
            v6 = idSoundSystemLocal::s_muteEAXReverb.internalVar->integerValue == 0;
            *((_BYTE *)&farthestDistance + v78) = 0;
            if ( !v6 && v77 == this->listenerArea )
              EnvironmentParameters.lRoom = -10000;
            EnvironmentParameters.vReflectionsPan.x = EnvironmentDirection.x;
            EnvironmentParameters.vReverbPan.x = EnvironmentDirection.x;
            alEAXSet = this->alEAXSet;
            EnvironmentParameters.vReflectionsPan.y = EnvironmentDirection.y;
            EnvironmentParameters.vReflectionsPan.z = EnvironmentDirection.z;
            EnvironmentParameters.vReverbPan.y = EnvironmentDirection.y;
            EnvironmentParameters.vReverbPan.z = EnvironmentDirection.z;
            closestArea[LODWORD(v76)] = -1;
            if ( alEAXSet )
              alEAXSet(numPortalsa, 1u, 0, &EnvironmentParameters, 112u);
          }
        }
      }
      LOBYTE(v202) = 0;
      idStr::FreeData(&name);
      v28 = maxVolume;
LABEL_68:
      p_w += 5;
      ++LODWORD(v28);
      maxVolume = v28;
    }
    while ( SLODWORD(v28) < 4 );
    ++efxSlotToArea;
    ++numPortalsa;
    ++i;
  }
  while ( i < 4 );
  v80 = 0;
  i = 0;
  p_w = &closestPortal[0].w;
  while ( 2 )
  {
    if ( closestArea[v80] == -1 )
      goto LABEL_116;
    v81 = 0.0;
    maxVolume = 0.0;
    while ( !*((_BYTE *)&farthestDistance + LODWORD(v81)) )
    {
      ++LODWORD(v81);
      if ( SLODWORD(v81) >= 4 )
      {
        maxVolume = v81;
        goto LABEL_116;
      }
    }
    maxVolume = v81;
    v6 = closestArea[v80] == this->listenerArea;
    *(float *)&v173 = 0.0;
    *(float *)&index = NAN;
    if ( v6 )
    {
      v82 = 3.4028235e38;
      v83 = 4;
      for ( m = 1; m < 4; ++m )
      {
        if ( v82 > closestDistance[m] )
        {
          v83 = m;
          v82 = closestDistance[m];
        }
      }
      if ( v83 < 4 )
      {
        v85 = (idWinding *)closestPortal[v83].w;
        idWinding::GetBounds(v85, &boundary);
        v86 = boundary.b[0].z - this->listenerPos.z;
        v155 = boundary.b[0].y - this->listenerPos.y;
        v87 = boundary.b[0].x - this->listenerPos.x;
        right.y = v155;
        v189 = v87;
        right.x = v189;
        right.z = v86;
        v88 = v189 * v189 + v155 * v155 + v86 * v86;
        if ( v88 != 0.0 )
        {
          v89 = 1.0 / sqrt(v88);
          right.x = v189 * v89;
          right.y = v155 * v89;
          right.z = v89 * v86;
        }
        v90 = boundary.b[1].z - this->listenerPos.z;
        v156 = boundary.b[1].y - this->listenerPos.y;
        v91 = boundary.b[1].x - this->listenerPos.x;
        left.y = v156;
        v188 = v91;
        left.x = v188;
        left.z = v90;
        v92 = v188 * v188 + v156 * v156 + v90 * v90;
        if ( v92 != 0.0 )
        {
          v93 = 1.0 / sqrt(v92);
          left.x = v188 * v93;
          left.y = v156 * v93;
          left.z = v93 * v90;
        }
        v94 = idWinding::GetCenter(v85, (idVec3 *)&portal);
        *(float *)&effect = v94->z - this->listenerPos.z;
        v157 = v94->y - this->listenerPos.y;
        v95 = v94->x - this->listenerPos.x;
        result.x = v95;
        v96 = v157;
        v97 = *(float *)&effect;
        *(float *)&EnvironmentID = result.x * result.x + v157 * v157 + *(float *)&effect * *(float *)&effect;
        if ( *(float *)&EnvironmentID != 0.0 )
        {
          v98 = 1.0 / sqrt(*(float *)&EnvironmentID);
          numPortalsc = v98;
          v95 = v98 * result.x;
          v96 = numPortalsc * v157;
          v97 = numPortalsc * *(float *)&effect;
        }
        direction.x = v97 * this->listenerAxis.mat[0].z
                    + v96 * this->listenerAxis.mat[0].y
                    + v95 * this->listenerAxis.mat[0].x;
        direction.y = v97 * this->listenerAxis.mat[1].z
                    + v96 * this->listenerAxis.mat[1].y
                    + v95 * this->listenerAxis.mat[1].x;
        direction.z = v97 * this->listenerAxis.mat[2].z
                    + v96 * this->listenerAxis.mat[2].y
                    + v95 * this->listenerAxis.mat[2].x;
        v99 = (left.z * right.z + left.y * right.y + left.x * right.x + 1.0) * 0.31850001 - 0.63700002;
        goto LABEL_97;
      }
      v100 = 0.0;
      v101 = 0.0;
      v102 = 0.0;
    }
    else
    {
      v103 = (idWinding *)*p_w;
      idWinding::GetBounds((idWinding *)*p_w, &boundary);
      v104 = boundary.b[0].z - this->listenerPos.z;
      v158 = boundary.b[0].y - this->listenerPos.y;
      v105 = boundary.b[0].x - this->listenerPos.x;
      right.y = v158;
      v187 = v105;
      right.x = v187;
      right.z = v104;
      v106 = v187 * v187 + v158 * v158 + v104 * v104;
      if ( v106 != 0.0 )
      {
        v107 = 1.0 / sqrt(v106);
        right.x = v187 * v107;
        right.y = v158 * v107;
        right.z = v107 * v104;
      }
      v108 = boundary.b[1].z - this->listenerPos.z;
      v159 = boundary.b[1].y - this->listenerPos.y;
      v109 = boundary.b[1].x - this->listenerPos.x;
      left.y = v159;
      v190 = v109;
      left.x = v190;
      left.z = v108;
      v110 = v190 * v190 + v159 * v159 + v108 * v108;
      if ( v110 != 0.0 )
      {
        v111 = 1.0 / sqrt(v110);
        left.x = v190 * v111;
        left.y = v159 * v111;
        left.z = v111 * v108;
      }
      v112 = idWinding::GetCenter(v103, &v199);
      *(float *)&effect = v112->z - this->listenerPos.z;
      v160 = v112->y - this->listenerPos.y;
      v113 = v112->x - this->listenerPos.x;
      v192 = v113;
      v114 = v160;
      v115 = *(float *)&effect;
      *(float *)&EnvironmentID = v192 * v192 + v160 * v160 + *(float *)&effect * *(float *)&effect;
      if ( *(float *)&EnvironmentID != 0.0 )
      {
        v116 = 1.0 / sqrt(*(float *)&EnvironmentID);
        numPortalsd = v116;
        v113 = v116 * v192;
        v114 = numPortalsd * v160;
        v115 = numPortalsd * *(float *)&effect;
      }
      direction.x = v115 * this->listenerAxis.mat[0].z
                  + v114 * this->listenerAxis.mat[0].y
                  + v113 * this->listenerAxis.mat[0].x;
      direction.y = v115 * this->listenerAxis.mat[1].z
                  + v114 * this->listenerAxis.mat[1].y
                  + v113 * this->listenerAxis.mat[1].x;
      direction.z = v115 * this->listenerAxis.mat[2].z
                  + v114 * this->listenerAxis.mat[2].y
                  + v113 * this->listenerAxis.mat[2].x;
      v99 = (left.z * right.z + left.y * right.y + left.x * right.x + 1.0) * 0.18099999 + 0.63700002;
LABEL_97:
      numPortalse = v99;
      v100 = v99 * direction.x;
      v101 = numPortalse * direction.y;
      v102 = numPortalse * direction.z;
    }
    v117 = closestArea[i];
    v118 = this->__vftable;
    EnvironmentDirection.x = -v101;
    EnvironmentDirection.y = v102;
    EnvironmentDirection.z = v100;
    v119 = v118->GetReverb(this, v117);
    v120 = v118->GetReverbName(this, v119);
    name.len = 0;
    name.alloced = 20;
    name.data = name.baseBuffer;
    name.baseBuffer[0] = 0;
    if ( v120 )
    {
      v121 = (unsigned int)&v120[strlen(v120) + 1];
      v122 = v121 - (_DWORD)(v120 + 1);
      v123 = v121 - (_DWORD)v120;
      if ( v123 > 20 )
        idStr::ReAllocate(&name, v123, 1);
      v124 = name.data;
      v125 = v120;
      do
      {
        v126 = *v125;
        *v124++ = *v125++;
      }
      while ( v126 );
      name.len = v122;
    }
    LOBYTE(v202) = 3;
    idEFXFile::FindEffect(&this->EFXDatabase, &name, &v173, &index);
    v127 = v173;
    if ( *(float *)&v173 != 0.0 )
      goto LABEL_166;
    v195.alloced = 20;
    v195.data = v195.baseBuffer;
    v195.baseBuffer[0] = 0;
    do
    {
      v128 = aDefault_2[(_DWORD)v127];
      v195.baseBuffer[(_DWORD)v127] = v128;
      v127 = (idSoundEffect *)((char *)v127 + 1);
    }
    while ( v128 );
    v195.len = 7;
    LOBYTE(v202) = 4;
    idEFXFile::FindEffect(&this->EFXDatabase, &v195, &v173, &index);
    LOBYTE(v202) = 3;
    idStr::FreeData(&v195);
    v127 = v173;
    if ( *(float *)&v173 != 0.0 )
    {
LABEL_166:
      v129 = v127->data;
      if ( v129 )
      {
        qmemcpy(&EnvironmentParameters, v129, v127->datasize);
        if ( &EnvironmentParameters )
        {
          v130 = i;
          v131 = maxVolume;
          v132 = closestArea[i];
          this->efxSlotToArea[LODWORD(maxVolume)] = v132;
          v6 = idSoundSystemLocal::s_muteEAXReverb.internalVar->integerValue == 0;
          *((_BYTE *)&farthestDistance + LODWORD(v131)) = 0;
          if ( !v6 && v132 == this->listenerArea )
            EnvironmentParameters.lRoom = -10000;
          EnvironmentParameters.vReflectionsPan.x = EnvironmentDirection.x;
          EnvironmentParameters.vReverbPan.x = EnvironmentDirection.x;
          v133 = this->alEAXSet;
          EnvironmentParameters.vReflectionsPan.y = EnvironmentDirection.y;
          EnvironmentParameters.vReflectionsPan.z = EnvironmentDirection.z;
          EnvironmentParameters.vReverbPan.y = EnvironmentDirection.y;
          EnvironmentParameters.vReverbPan.z = EnvironmentDirection.z;
          closestArea[v130] = -1;
          if ( v133 )
            v133(&this->efxSlotId[LODWORD(v131)], 1u, 0, &EnvironmentParameters, 112u);
        }
      }
    }
    LOBYTE(v202) = 0;
    idStr::FreeData(&name);
    v80 = i;
LABEL_116:
    p_w += 5;
    i = ++v80;
    if ( v80 < 4 )
      continue;
    break;
  }
  v134 = 0;
  v135 = this->efxSlotToArea;
  while ( *v135 != this->listenerArea )
  {
    ++v134;
    ++v135;
    if ( v134 >= 4 )
      goto LABEL_126;
  }
  v136 = this->alEAXSet;
  if ( v136 )
  {
    if ( this->eaxVersion == 6 )
    {
      v136(&EAXPROPERTYID_EAX50_Context, 2u, 0, &this->efxSlotId[v134], 16u);
    }
    else if ( this->eaxVersion == 5 )
    {
      v136(&EAXPROPERTYID_EAX40_Context, 2u, 0, &this->efxSlotId[v134], 16u);
    }
  }
LABEL_126:
  integerValue = s_singleEmitter.internalVar->integerValue;
  if ( integerValue <= 0 || integerValue >= this->GetNumEmitters(this) )
  {
    v6 = idSoundSystemLocal::s_useOpenAL.internalVar->integerValue == 0;
    v140 = s_maxChannelsMixed.internalVar->integerValue;
    EnvironmentID = v140;
    if ( !v6 || v140 <= 0 )
      *(float *)&EnvironmentID = 1.4012983e-38;
    v141 = this->__vftable;
    v142 = 1;
    farthestDistance = 0.0;
    numEmittersd = 0;
    i = 1;
    if ( v141->GetNumEmitters(this) > 1 )
    {
      do
      {
        v143 = this->emitters.list[v142];
        if ( v143 && v143->playing && v143->AttachedToWorld(v143, worldId) )
        {
          maxVolume = 0.0;
          channels = v143->channels;
          v145 = 8;
          do
          {
            if ( channels->triggerState )
            {
              idSoundSystemLocal::DetermineChannelContribution(this, v143, channels, current44kHz);
              if ( channels->lastVolume > (double)maxVolume )
                maxVolume = channels->lastVolume;
            }
            else
            {
              idSoundChannel::ALStop(channels);
              channels->lastVolume = 0.0;
            }
            ++channels;
            --v145;
          }
          while ( v145 );
          v146 = maxVolume < 0.0;
          v147 = maxVolume == 0.0;
          v143->maxChannelVolume = maxVolume;
          if ( !v146 && !v147 )
          {
            v148 = farthestDistance;
            for ( n = &farthestDistance; v148 != 0.0; v148 = *(float *)(LODWORD(v148) + 1428) )
            {
              if ( maxVolume > (double)*(float *)(LODWORD(v148) + 1424) )
                break;
              n = (float *)(LODWORD(v148) + 1428);
            }
            ++numEmittersd;
            *(_DWORD *)n = v143;
            *(float *)&v143->next = v148;
          }
        }
        v150 = this->__vftable;
        v142 = ++i;
      }
      while ( v142 < v150->GetNumEmitters(this) );
    }
    v151 = farthestDistance;
    numPortalsb = this->soundStats.activeSounds;
    for ( i = 0; i < numEmittersd; ++i )
    {
      v152 = 0;
      v153 = (idSoundChannel *)(LODWORD(v151) + 108);
      while ( 1 )
      {
        idSoundSystemLocal::AddChannelContribution(
          this,
          (idSoundEmitterLocal *)LODWORD(v151),
          v153,
          current44kHz,
          numSpeakers,
          finalMixBuffer);
        if ( this->soundStats.activeSounds - numPortalsb >= EnvironmentID )
          break;
        ++v152;
        ++v153;
        if ( v152 >= 8 )
          goto LABEL_161;
      }
      i = numEmittersd;
LABEL_161:
      v151 = *(float *)(LODWORD(v151) + 1428);
    }
  }
  else
  {
    v138 = this->emitters.list[s_singleEmitter.internalVar->integerValue];
    if ( v138 && v138->playing )
    {
      v139 = v138->channels;
      EnvironmentID = 8;
      do
      {
        if ( v139->triggerState )
          idSoundSystemLocal::AddChannelContribution(this, v138, v139, current44kHz, numSpeakers, finalMixBuffer);
        else
          idSoundChannel::ALStop(v139);
        ++v139;
        --EnvironmentID;
      }
      while ( *(float *)&EnvironmentID != 0.0 );
    }
  }
  v202 = -1;
  idStr::FreeData(&temp);
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::AVIOpen(int,char const *,char const *)
void __thiscall idSoundSystemLocal::AVIOpen(idSoundSystemLocal *this, int worldId, char *path, char *name)
{
  idStr *p_aviDemoPath; // edi
  idAudioHardware *snd_audio_hw; // ecx
  idStr *v7; // eax
  idFileSystem_vtbl *v8; // edx
  idStr *v9; // eax
  idFileSystem_vtbl *v10; // edx
  idStr *v11; // eax
  idFileSystem_vtbl *v12; // edx
  idStr *v13; // eax
  idFileSystem_vtbl *v14; // edx
  idStr *v15; // eax
  idFileSystem_vtbl *v16; // edx
  idStr *v17; // eax
  idFileSystem_vtbl *v18; // edx
  idStr *p_result; // ecx
  idStr *v20; // eax
  idFileSystem_vtbl *v21; // edx
  idStr *v22; // eax
  idFileSystem_vtbl *v23; // edx
  char *data; // [esp+30h] [ebp-64h]
  char *v25; // [esp+30h] [ebp-64h]
  char *v26; // [esp+30h] [ebp-64h]
  char *v27; // [esp+30h] [ebp-64h]
  char *v28; // [esp+30h] [ebp-64h]
  char *v29; // [esp+30h] [ebp-64h]
  char *v30; // [esp+30h] [ebp-64h]
  char *v31; // [esp+30h] [ebp-64h]
  idStr result; // [esp+48h] [ebp-4Ch] BYREF
  idStr v33; // [esp+68h] [ebp-2Ch] BYREF
  int v34; // [esp+90h] [ebp-4h]

  p_aviDemoPath = &this->aviDemoPath;
  idStr::operator=(&this->aviDemoPath, path);
  idStr::operator=(&this->aviDemoName, name);
  snd_audio_hw = this->snd_audio_hw;
  this->lastAVI44kHz = this->game44kHz - this->game44kHz % 4096;
  if ( snd_audio_hw->GetNumberOfSpeakers(snd_audio_hw) == 6 )
  {
    v7 = operator+(&result, p_aviDemoPath, "channel_51_left.raw");
    v8 = fileSystem->__vftable;
    data = v7->data;
    v34 = 0;
    this->fpa[0] = v8->OpenFileWrite(fileSystem, data, "fs_savepath", 0);
    v34 = -1;
    idStr::FreeData(&result);
    v9 = operator+(&result, p_aviDemoPath, "channel_51_right.raw");
    v10 = fileSystem->__vftable;
    v25 = v9->data;
    v34 = 1;
    this->fpa[1] = v10->OpenFileWrite(fileSystem, v25, "fs_savepath", 0);
    v34 = -1;
    idStr::FreeData(&result);
    v11 = operator+(&result, p_aviDemoPath, "channel_51_center.raw");
    v12 = fileSystem->__vftable;
    v26 = v11->data;
    v34 = 2;
    this->fpa[2] = v12->OpenFileWrite(fileSystem, v26, "fs_savepath", 0);
    v34 = -1;
    idStr::FreeData(&result);
    v13 = operator+(&result, p_aviDemoPath, "channel_51_lfe.raw");
    v14 = fileSystem->__vftable;
    v27 = v13->data;
    v34 = 3;
    this->fpa[3] = v14->OpenFileWrite(fileSystem, v27, "fs_savepath", 0);
    v34 = -1;
    idStr::FreeData(&result);
    v15 = operator+(&result, p_aviDemoPath, "channel_51_backleft.raw");
    v16 = fileSystem->__vftable;
    v28 = v15->data;
    v34 = 4;
    this->fpa[4] = v16->OpenFileWrite(fileSystem, v28, "fs_savepath", 0);
    v34 = -1;
    idStr::FreeData(&result);
    v17 = operator+(&result, p_aviDemoPath, "channel_51_backright.raw");
    v18 = fileSystem->__vftable;
    v29 = v17->data;
    v34 = 5;
    this->fpa[5] = v18->OpenFileWrite(fileSystem, v29, "fs_savepath", 0);
    p_result = &result;
  }
  else
  {
    v20 = operator+(&result, p_aviDemoPath, "channel_left.raw");
    v21 = fileSystem->__vftable;
    v30 = v20->data;
    v34 = 6;
    this->fpa[0] = v21->OpenFileWrite(fileSystem, v30, "fs_savepath", 0);
    v34 = -1;
    idStr::FreeData(&result);
    v22 = operator+(&v33, p_aviDemoPath, "channel_right.raw");
    v23 = fileSystem->__vftable;
    v31 = v22->data;
    v34 = 7;
    this->fpa[1] = v23->OpenFileWrite(fileSystem, v31, "fs_savepath", 0);
    p_result = &v33;
  }
  v34 = -1;
  idStr::FreeData(p_result);
  this->SetMute(this, 1);
}

// FUNC: public: void __thiscall idSoundSystemLocal::AVIUpdate(void)
void __thiscall idSoundSystemLocal::AVIUpdate(idSoundSystemLocal *this)
{
  idSoundSystemLocal *v1; // ebx
  idAudioHardware *snd_audio_hw; // ecx
  int v3; // edi
  float *v4; // esi
  int v5; // ebp
  idFile **fpa; // ebx
  int v7; // ecx
  float *v8; // edx
  float v9; // [esp+Ch] [ebp-1A04Ch]
  __int16 v11[4100]; // [esp+18h] [ebp-1A040h] BYREF
  float v12; // [esp+2020h] [ebp-18038h] BYREF

  v1 = this;
  if ( this->game44kHz - this->lastAVI44kHz >= 4096 )
  {
    snd_audio_hw = this->snd_audio_hw;
    if ( snd_audio_hw )
      v3 = snd_audio_hw->GetNumberOfSpeakers(snd_audio_hw);
    else
      v3 = 2;
    v4 = &v12;
    SIMDProcessor->Memset(SIMDProcessor, &v12, 0, v3 << 14);
    idSoundSystemLocal::MixLoop(v1, v1->activeSoundWorld, v1->lastAVI44kHz, v3, &v12);
    if ( v3 > 0 )
    {
      v5 = 4 * v3;
      fpa = v1->fpa;
      do
      {
        v7 = 0;
        v8 = v4;
        do
        {
          v9 = *v8;
          if ( *v8 >= -32768.0 )
          {
            if ( v9 <= 32767.0 )
              v11[v7] = (int)v9;
            else
              v11[v7] = 0x7FFF;
          }
          else
          {
            v11[v7] = 0x8000;
          }
          ++v7;
          v8 = (float *)((char *)v8 + v5);
        }
        while ( v7 < 4096 );
        (*fpa)->Write(*fpa, v11, 0x2000);
        ++v4;
        ++fpa;
        --v3;
      }
      while ( v3 );
      v1 = this;
    }
    v1->lastAVI44kHz += 4096;
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::AVIClose(int)
void __userpurge idSoundSystemLocal::AVIClose(idSoundSystemLocal *this@<ecx>, int a2@<ebx>, int worldId)
{
  idSoundSystemLocal *v3; // esi
  idFile **fpa; // edi
  bool v5; // zf
  int v6; // ebx
  const idStr *p_aviDemoPath; // ebx
  const idStr *v8; // eax
  idStr *v9; // esi
  char *len; // ebp
  int v11; // eax
  idFile *v12; // ebp
  idStr *v13; // esi
  char *v14; // ebx
  int v15; // eax
  idFile *v16; // ebx
  idStr *v17; // esi
  unsigned int v18; // edi
  int v19; // eax
  char *v20; // eax
  idFile *v21; // esi
  int v22; // eax
  int v23; // edi
  const idStr *v24; // esi
  idStr *v25; // eax
  idStr *v26; // eax
  idSoundSystemLocal *v28; // [esp+84h] [ebp-98h] BYREF
  const idStr *s0; // [esp+88h] [ebp-94h]
  idStr name; // [esp+8Ch] [ebp-90h] BYREF
  mminfo_s info; // [esp+ACh] [ebp-70h] BYREF
  int v32; // [esp+BCh] [ebp-60h]
  pcmwaveformat_s format; // [esp+C0h] [ebp-5Ch] BYREF
  __int16 v34; // [esp+D0h] [ebp-4Ch]
  __int16 v35; // [esp+D2h] [ebp-4Ah]
  idStr result; // [esp+D4h] [ebp-48h] BYREF
  idStr v37; // [esp+F4h] [ebp-28h] BYREF
  int retaddr; // [esp+11Ch] [ebp+0h]

  v3 = this;
  fpa = this->fpa;
  v5 = this->fpa[0] == 0;
  v28 = this;
  if ( !v5 )
  {
    this->game44kHz += 4096;
    idSoundSystemLocal::AVIUpdate(this);
    v3->game44kHz -= 4096;
    v6 = 6;
    do
    {
      if ( *fpa )
      {
        fileSystem->CloseFile(fileSystem, *fpa);
        *fpa = 0;
      }
      ++fpa;
      --v6;
    }
    while ( v6 );
    if ( ((int (__thiscall *)(idAudioHardware *, int))v3->snd_audio_hw->GetNumberOfSpeakers)(v3->snd_audio_hw, a2) == 2 )
    {
      name.data = 0;
      *(_DWORD *)name.baseBuffer = 20;
      name.alloced = (int)&name.baseBuffer[4];
      name.baseBuffer[4] = 0;
      p_aviDemoPath = &v3->aviDemoPath;
      retaddr = 2;
      v8 = operator+(&result, &v3->aviDemoPath, &v3->aviDemoName);
      v9 = operator+(&v37, v8, ".wav");
      len = (char *)v9->len;
      v11 = v9->len + 1;
      if ( v11 > 20 )
        idStr::ReAllocate((idStr *)&name.data, v11, 0);
      qmemcpy((void *)name.alloced, v9->data, (unsigned int)len);
      len[name.alloced] = 0;
      name.data = len;
      idStr::FreeData(&v37);
      LOBYTE(retaddr) = 0;
      idStr::FreeData(&result);
      v12 = fileSystem->OpenFileWrite(fileSystem, name.alloced, "fs_savepath", 0);
      if ( !v12 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "Couldn't write %s",
          name.alloced);
      v13 = operator+(&result, p_aviDemoPath, "channel_right.raw");
      v14 = (char *)v13->len;
      v15 = v13->len + 1;
      LOBYTE(retaddr) = 3;
      if ( v15 > *(int *)name.baseBuffer )
        idStr::ReAllocate((idStr *)&name.data, v15, 0);
      qmemcpy((void *)name.alloced, v13->data, (unsigned int)v14);
      v14[name.alloced] = 0;
      name.data = v14;
      LOBYTE(retaddr) = 0;
      idStr::FreeData(&result);
      v16 = fileSystem->OpenFileRead(fileSystem, name.alloced, 1, 0);
      if ( !v16 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "Couldn't open %s",
          name.alloced);
      v17 = operator+(&result, s0 + 6, "channel_left.raw");
      v18 = v17->len;
      v19 = v17->len + 1;
      LOBYTE(retaddr) = 4;
      *(_DWORD *)&format.wf.wFormatTag = v17->len;
      if ( v19 > *(int *)name.baseBuffer )
        idStr::ReAllocate((idStr *)&name.data, v19, 0);
      v20 = *(char **)&format.wf.wFormatTag;
      qmemcpy((void *)name.alloced, v17->data, v18);
      v20[name.alloced] = 0;
      name.data = v20;
      LOBYTE(retaddr) = 0;
      idStr::FreeData(&result);
      v21 = fileSystem->OpenFileRead(fileSystem, name.alloced, 1, 0);
      if ( !v21 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "Couldn't open %s",
          name.alloced);
      v22 = v16->Length(v16);
      info.cksize = 1179011410;
      info.dwDataOffset = 1163280727;
      v23 = v22 / 2;
      info.fccType = 2 * v16->Length(v16) + 28;
      v32 = 12;
      v12->Write(v12, &info.cksize, 12);
      info.cksize = 544501094;
      info.fccType = 16;
      v12->Write(v12, &info.cksize, 8);
      v35 = 16;
      *(_DWORD *)&format.wf.nBlockAlign = 176400;
      format.wf.nAvgBytesPerSec = 44100;
      format.wf.nSamplesPerSec = 131073;
      v34 = 4;
      v12->Write(v12, &format.wf.nSamplesPerSec, 16);
      info.cksize = 1635017060;
      info.fccType = 2 * v16->Length(v16);
      v12->Write(v12, &info.cksize, 8);
      if ( v23 > 0 )
      {
        do
        {
          v21->Read(v21, &name, 2);
          v16->Read(v16, &v28, 2);
          v12->Write(v12, &name, 2);
          v12->Write(v12, &v28, 2);
          --v23;
        }
        while ( v23 );
      }
      fileSystem->CloseFile(fileSystem, v12);
      fileSystem->CloseFile(fileSystem, v21);
      fileSystem->CloseFile(fileSystem, v16);
      v24 = s0 + 6;
      v25 = operator+(&result, s0 + 6, "channel_right.raw");
      fileSystem->RemoveFile(fileSystem, v25->data, "fs_savepath");
      idStr::FreeData(&result);
      v26 = operator+(&result, v24, "channel_left.raw");
      fileSystem->RemoveFile(fileSystem, v26->data, "fs_savepath");
      idStr::FreeData(&result);
      retaddr = -1;
      idStr::FreeData((idStr *)&name.data);
      v3 = (idSoundSystemLocal *)s0;
    }
    v3->SetMute(v3, 0);
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::PlaceListener(class idVec3 const &,class idMat3 const &,int,int,class idStr const &)
void __thiscall idSoundSystemLocal::PlaceListener(
        idSoundSystemLocal *this,
        const idVec3 *origin,
        const idMat3 *axis,
        int listenerId,
        int gameTime,
        const idStr *areaName)
{
  int gameMsec; // eax
  bool v8; // zf
  double v9; // st7
  idRenderWorld *rw; // ecx
  float gameTimea; // [esp+24h] [ebp+10h]

  if ( this->isInitialized && this->pause44kHz < 0 )
  {
    if ( this->writeDemo )
    {
      soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
      soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 1);
      this->writeDemo->WriteVec3(this->writeDemo, origin);
      this->writeDemo->WriteMat3(this->writeDemo, axis);
      this->writeDemo->WriteInt(this->writeDemo, listenerId);
      this->writeDemo->WriteInt(this->writeDemo, gameTime);
    }
    idSoundSystemLocal::GetCurrent44kHzTime(this);
    gameMsec = this->gameMsec;
    if ( gameTime > gameMsec + 500 )
      idSoundSystemLocal::OffsetSoundTime(this, (int)((double)(gameMsec - gameTime) * 44.100002));
    v8 = this->fpa[0] == 0;
    v9 = (double)gameTime;
    this->gameMsec = gameTime;
    if ( v8 )
      gameTimea = v9 * 44.100002;
    else
      gameTimea = v9 * 45.9375;
    this->game44kHz = (int)gameTimea;
    this->listenerPrivateId = listenerId;
    this->listenerPos = *origin;
    this->listenerAxis = *axis;
    rw = this->rw;
    if ( rw )
      this->listenerArea = rw->PointInArea(rw, &this->listenerPos);
    else
      this->listenerArea = 0;
    (*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 172))(*(_DWORD *)common.ip, this->listenerArea);
    if ( this->listenerArea >= 0 )
      this->ForegroundUpdate(this);
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::ForegroundUpdate(void)
void __usercall idSoundSystemLocal::ForegroundUpdate(
        idSoundSystemLocal *this@<ecx>,
        int *a2@<ebx>,
        int a3@<ebp>,
        const idCmdArgs *a4@<edi>,
        int *a5@<esi>)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  int v7; // ebp
  bool v8; // cc
  idSoundEmitterLocal *v9; // esi
  idRenderWorld *rw; // ecx
  double v11; // st7
  float z; // eax
  int x_low; // ecx
  int y_low; // edx
  double v15; // st7
  idRenderWorld *v16; // eax
  idRenderWorld_vtbl *v17; // ebp
  float *p_maxDistance; // ebp
  bool v19; // zf
  float v20; // edx
  const char *v21; // eax
  idRenderWorld *v22; // ecx
  const idMaterial *v23; // eax
  shaderStage_t *stages; // ebp
  idCinematic *v25; // eax
  idCinematic *v26; // esi
  idSoundCache *soundCache; // eax
  idGame_vtbl *v28; // esi
  int CacheMemoryUsage; // eax
  idMat3 *p_listenerAxis; // [esp+50h] [ebp-47Ch]
  const char *defaulted; // [esp+54h] [ebp-478h]
  idBounds ref; // [esp+58h] [ebp-474h] BYREF
  int v37; // [esp+70h] [ebp-45Ch]
  idVec3 textPos; // [esp+74h] [ebp-458h] BYREF
  float min; // [esp+80h] [ebp-44Ch]
  int j; // [esp+84h] [ebp-448h]
  int current44kHzTime; // [esp+88h] [ebp-444h]
  float max; // [esp+8Ch] [ebp-440h]
  idRenderWorld *v43; // [esp+90h] [ebp-43Ch]
  int v44[2]; // [esp+94h] [ebp-438h] BYREF
  float v45; // [esp+9Ch] [ebp-430h]
  float v46[4]; // [esp+A0h] [ebp-42Ch] BYREF
  int v47; // [esp+B0h] [ebp-41Ch] BYREF
  int v48; // [esp+B4h] [ebp-418h]
  int v49; // [esp+B8h] [ebp-414h]
  int v50; // [esp+BCh] [ebp-410h]
  char text[1024]; // [esp+C0h] [ebp-40Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v52; // [esp+4C0h] [ebp-Ch]
  void *v53; // [esp+4C4h] [ebp-8h]
  int v54; // [esp+4C8h] [ebp-4h]

  v54 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v53 = &_ehhandler__ForegroundUpdate_idSoundSystemLocal__UAEXXZ;
  v52 = ExceptionList;
  if ( this->isInitialized )
  {
    current44kHzTime = idSoundSystemLocal::GetCurrent44kHzTime(this);
    this->soundStats.numPortalChecks = 0;
    Sys_EnterCriticalSection(0);
    if ( this->fpa[0] )
      current44kHzTime = this->lastAVI44kHz;
    v7 = 1;
    v8 = this->emitters.num <= 1;
    j = 1;
    if ( !v8 )
    {
      do
      {
        v9 = this->emitters.list[v7];
        if ( v9 )
        {
          if ( v9->AttachedToWorld(v9, this->activeSoundWorld) )
          {
            v8 = v9->removeStatus < REMOVE_STATUS_SAMPLEFINISHED;
            v9->numPortalChecks = 0;
            if ( v8 )
            {
              idSoundEmitterLocal::CheckForCompletion(v9, current44kHzTime);
              if ( v9->playing )
              {
                if ( this->activeSoundWorld == 3 )
                  v9->distance = idVec3::Dist(&this->listenerPos, &v9->origin);
                else
                  idSoundEmitterLocal::Spatialize(v9, this->listenerPos, this->listenerArea, this->rw);
                if ( s_drawSounds.internalVar->integerValue && this->rw )
                {
                  if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 64) )
                  {
                    if ( (v9->parms.soundShaderFlags & 0x200000) != 0 )
                      goto LABEL_16;
                  }
                  else if ( v9->distance < (double)v9->maxDistance || s_drawSounds.internalVar->integerValue > 1 )
                  {
LABEL_16:
                    ref.b[1].z = -1.0e30;
                    ref.b[0].x = idMath::INFINITY;
                    ref.b[0].z = idMath::INFINITY;
                    ref.b[0].y = idMath::INFINITY;
                    ref.b[1].y = ref.b[1].z;
                    ref.b[1].x = ref.b[1].z;
                    if ( 1.0e30 > -10.0 )
                      ref.b[0].x = -10.0;
                    if ( ref.b[1].z < -10.0 )
                      ref.b[1].x = -10.0;
                    if ( ref.b[0].y > -10.0 )
                      ref.b[0].y = -10.0;
                    if ( ref.b[1].z < -10.0 )
                      ref.b[1].y = -10.0;
                    if ( ref.b[0].z > -10.0 )
                      ref.b[0].z = -10.0;
                    if ( ref.b[1].z < -10.0 )
                      ref.b[1].z = -10.0;
                    if ( ref.b[0].x > 10.0 )
                      ref.b[0].x = 10.0;
                    if ( ref.b[1].x < 10.0 )
                      ref.b[1].x = 10.0;
                    if ( ref.b[0].y > 10.0 )
                      ref.b[0].y = 10.0;
                    if ( ref.b[1].y < 10.0 )
                      ref.b[1].y = 10.0;
                    if ( ref.b[0].z > 10.0 )
                      ref.b[0].z = 10.0;
                    if ( ref.b[1].z < 10.0 )
                      ref.b[1].z = 10.0;
                    rw = this->rw;
                    v11 = v9->distance / v9->maxDistance;
                    v46[1] = 0.25;
                    v46[0] = 1.0 - v11;
                    v46[2] = v46[0];
                    v46[3] = v46[0];
                    ((void (__thiscall *)(idRenderWorld *, float *, idBounds *, idVec3 *, _DWORD, _DWORD, const idCmdArgs *, int *, int, int *, idMat3 *, const char *))rw->DebugBounds)(
                      rw,
                      v46,
                      &ref,
                      &v9->origin,
                      0,
                      0,
                      a4,
                      a5,
                      a3,
                      a2,
                      p_listenerAxis,
                      defaulted);
                    if ( v9->origin.x != v9->spatializedOrigin.x
                      || v9->origin.y != v9->spatializedOrigin.y
                      || v9->origin.z != v9->spatializedOrigin.z )
                    {
                      this->rw->DebugArrow(this->rw, &colorRed, &v9->origin, &v9->spatializedOrigin, 4, 0);
                    }
                    z = v9->origin.z;
                    x_low = LODWORD(v9->origin.x);
                    y_low = LODWORD(v9->origin.y);
                    ref.b[0].y = 0.0;
                    ref.b[0].x = 0.0;
                    v45 = z;
                    v15 = z - 8.0;
                    v16 = this->rw;
                    defaulted = (const char *)1;
                    v44[0] = x_low;
                    v45 = v15;
                    p_listenerAxis = &this->listenerAxis;
                    a2 = &v47;
                    v44[1] = y_low;
                    a3 = 1036831949;
                    v47 = 1065353216;
                    v48 = 0;
                    v49 = 0;
                    v50 = 1065353216;
                    v17 = v16->__vftable;
                    v43 = v16;
                    a5 = v44;
                    a4 = (const idCmdArgs *)va("%i", v9->index);
                    ((void (__thiscall *)(idRenderWorld *))v17->DrawTextA)(v43);
                    p_maxDistance = &v9->channels[0].parms.maxDistance;
                    v37 = 8;
                    textPos.z = textPos.z + 8.0;
                    do
                    {
                      if ( *((_BYTE *)p_maxDistance - 12) )
                      {
                        v19 = *(_BYTE *)(*((_DWORD *)p_maxDistance + 9) + 40) == 0;
                        v20 = *p_maxDistance;
                        min = *(p_maxDistance - 1);
                        max = v20;
                        defaulted = "(DEFAULTED)";
                        if ( v19 )
                          defaulted = &entityFilter;
                        v21 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(*((_DWORD *)p_maxDistance + 12)
                                                                                        + 4)
                                                                          + 4))(*(_DWORD *)(*((_DWORD *)p_maxDistance
                                                                                            + 12)
                                                                                          + 4));
                        p_listenerAxis = (idMat3 *)(int)v9->distance;
                        sprintf(
                          text,
                          "%s (%i/%i %i/%i)%s",
                          v21,
                          p_listenerAxis,
                          (int)v9->realDistance,
                          (int)min,
                          (int)max,
                          defaulted);
                        v22 = this->rw;
                        v47 = 1065353216;
                        v48 = 0;
                        v49 = 0;
                        v50 = 1065353216;
                        ((void (__thiscall *)(idRenderWorld *, char *, idVec3 *, int, int *, idMat3 *, int, _DWORD, _DWORD))v22->DrawTextA)(
                          v22,
                          text,
                          &textPos,
                          1036831949,
                          &v47,
                          &this->listenerAxis,
                          1,
                          0,
                          0);
                        textPos.z = textPos.z + 8.0;
                      }
                      p_maxDistance += 41;
                      --v37;
                    }
                    while ( v37 );
                    v7 = j;
                  }
                }
              }
            }
          }
        }
        v8 = ++v7 < this->emitters.num;
        j = v7;
      }
      while ( v8 );
    }
    if ( this->voiceCommInit )
      SpawnStub(a4);
    Sys_LeaveCriticalSection(0);
    if ( s_showLevelMeter.internalVar->integerValue )
    {
      v23 = declManager->FindMaterial(declManager, "gfx/guis/soundmeter/audiobg", 0);
      if ( v23 )
      {
        stages = v23->stages;
        if ( !stages->texture.cinematic )
        {
          if ( Memory::mAllocator )
            *(float *)&v25 = COERCE_FLOAT(Memory::mAllocator(0x10u));
          else
            *(float *)&v25 = COERCE_FLOAT(malloc(0x10u));
          v26 = v25;
          min = *(float *)&v25;
          v54 = 0;
          if ( *(float *)&v25 == 0.0 )
          {
            v26 = 0;
          }
          else
          {
            idCinematic::idCinematic(v25);
            v26->__vftable = (idCinematic_vtbl *)&idSndWindow::`vftable';
            LOBYTE(v26[1].__vftable) = 0;
          }
          v54 = -1;
          stages->texture.cinematic = v26;
        }
      }
    }
    if ( this->fpa[0] )
      idSoundSystemLocal::AVIUpdate(this);
    if ( com_debugHudActive && this->rw )
    {
      soundCache = this->soundCache;
      if ( soundCache )
      {
        game->DebugSetInt(game, "snd_num_loaded_sounds", soundCache->listCache.num);
        v28 = game->__vftable;
        CacheMemoryUsage = idSoundSystemLocal::GetCacheMemoryUsage(this);
        v28->DebugSetInt(game, "snd_sound_memory", CacheMemoryUsage / 1024);
        game->DebugSetInt(game, "snd_active_sounds", this->soundStats.activeSounds);
        game->DebugSetInt(game, "snd_num_portal_checks", this->soundStats.numPortalChecks);
      }
    }
  }
}

// FUNC: public: class idSoundEmitterLocal * __thiscall idSoundSystemLocal::AllocLocalSoundEmitter(int,int)
idSoundEmitterLocal *__thiscall idSoundSystemLocal::AllocLocalSoundEmitter(
        idSoundSystemLocal *this,
        int worldId,
        int index)
{
  int v4; // edi
  idSoundEmitterLocal *v5; // ebp
  idSoundEmitterLocal *v6; // eax
  idSoundEmitterLocal *v7; // eax
  int granularity; // eax
  bool v9; // cc
  idSoundEmitterLocal **v10; // eax
  int i; // eax
  int num; // ebx
  int size; // eax
  int v14; // ecx
  idSoundEmitterLocal **list; // edi
  idSoundEmitterLocal **v16; // eax
  int j; // eax
  int v18; // esi
  unsigned int v20; // [esp-4h] [ebp-24h]
  idSoundEmitterLocal **v21; // [esp-4h] [ebp-24h]
  unsigned int v22; // [esp-4h] [ebp-24h]
  idSoundEmitterLocal *v23; // [esp+10h] [ebp-10h]

  Sys_EnterCriticalSection(0);
  v4 = 1;
  if ( this->GetNumEmitters(this) <= 1 )
    goto LABEL_8;
  while ( 1 )
  {
    v5 = this->emitters.list[v4];
    if ( v5->removeStatus >= REMOVE_STATUS_SAMPLEFINISHED )
      break;
    if ( ++v4 >= this->GetNumEmitters(this) )
      goto LABEL_8;
  }
  if ( s_showStartSound.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "sound: recycling sound def %d\n",
      v4);
  if ( v4 == -1 )
  {
LABEL_8:
    if ( Memory::mAllocator )
      v6 = (idSoundEmitterLocal *)Memory::mAllocator(0x5A0u);
    else
      v6 = (idSoundEmitterLocal *)malloc(0x5A0u);
    if ( v6 )
      idSoundEmitterLocal::idSoundEmitterLocal(v6);
    else
      v7 = 0;
    v23 = v7;
    v5 = v7;
    if ( !this->emitters.list )
    {
      granularity = this->emitters.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->emitters.size )
        {
          v9 = granularity < this->emitters.num;
          this->emitters.size = granularity;
          if ( v9 )
            this->emitters.num = granularity;
          v20 = 4 * granularity;
          if ( Memory::mAllocator )
            v10 = (idSoundEmitterLocal **)Memory::mAllocator(v20);
          else
            v10 = (idSoundEmitterLocal **)malloc(v20);
          this->emitters.list = v10;
          for ( i = 0; i < this->emitters.num; ++i )
            this->emitters.list[i] = *(idSoundEmitterLocal **)(4 * i);
        }
      }
      else
      {
        this->emitters.list = 0;
        this->emitters.num = 0;
        this->emitters.size = 0;
      }
    }
    num = this->emitters.num;
    size = this->emitters.size;
    if ( num != size )
      goto LABEL_46;
    if ( !this->emitters.granularity )
      this->emitters.granularity = 16;
    v14 = size + this->emitters.granularity - (size + this->emitters.granularity) % this->emitters.granularity;
    if ( v14 > 0 )
    {
      if ( v14 != this->emitters.size )
      {
        list = this->emitters.list;
        this->emitters.size = v14;
        if ( v14 < num )
          this->emitters.num = v14;
        v22 = 4 * v14;
        if ( Memory::mAllocator )
          v16 = (idSoundEmitterLocal **)Memory::mAllocator(v22);
        else
          v16 = (idSoundEmitterLocal **)malloc(v22);
        this->emitters.list = v16;
        for ( j = 0; j < this->emitters.num; ++j )
          this->emitters.list[j] = list[j];
        if ( list )
        {
          if ( Memory::mDeallocator )
            Memory::mDeallocator(list);
          else
            free(list);
        }
      }
      goto LABEL_46;
    }
    if ( this->emitters.list )
    {
      v21 = this->emitters.list;
      if ( Memory::mDeallocator )
      {
        Memory::mDeallocator(v21);
        this->emitters.list = 0;
        this->emitters.num = 0;
        this->emitters.size = 0;
        goto LABEL_46;
      }
      free(v21);
    }
    this->emitters.list = 0;
    this->emitters.num = 0;
    this->emitters.size = 0;
LABEL_46:
    this->emitters.list[this->emitters.num++] = v23;
    v18 = this->emitters.num;
    v4 = v18 - 1;
    if ( s_showStartSound.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "sound: appended new sound def %d\n",
        v18 - 1);
  }
  idSoundEmitterLocal::Clear(v5);
  v5->index = v4;
  v5->removeStatus = REMOVE_STATUS_ALIVE;
  v5->worldId = worldId;
  Sys_LeaveCriticalSection(0);
  return v5;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::AllocSoundEmitter(int)
int __thiscall idSoundSystemLocal::AllocSoundEmitter(idSoundSystemLocal *this, int worldId)
{
  idSoundEmitterLocal *v4; // esi

  if ( !this->isInitialized )
    return -1;
  v4 = idSoundSystemLocal::AllocLocalSoundEmitter(this, worldId, -1);
  if ( s_showStartSound.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "AllocSoundEmitter = %i\n",
      v4->index);
  if ( this->writeDemo )
  {
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
    soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
    soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, v4->index);
  }
  return v4->index;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::ProcessDemoCommand(int,class idDemoFile *)
void __thiscall idSoundSystemLocal::ProcessDemoCommand(idSoundSystemLocal *this, int worldId, idDemoFile *readDemo)
{
  int v4; // eax
  char v5; // cl
  idSoundSystemLocal_vtbl *v6; // edx
  int v7; // eax
  int v8; // eax
  idSoundEmitterLocal *v9; // eax
  float v10; // eax
  bool v11; // zf
  int granularity; // eax
  bool v13; // cc
  idSoundEmitterLocal **v14; // eax
  int i; // eax
  int size; // eax
  int num; // ebp
  int v18; // ecx
  idSoundEmitterLocal **list; // esi
  idSoundEmitterLocal **v20; // eax
  int j; // eax
  _DWORD *v22; // esi
  idSoundEmitter *v23; // eax
  idDeclManager_vtbl *v24; // ebx
  char *HashString; // eax
  int v26; // ebx
  idSoundEmitter *v27; // eax
  idSoundEmitter *v28; // eax
  idSoundEmitter *v29; // eax
  idSoundEmitter *v30; // eax
  idSoundEmitterLocal **v31; // [esp+8h] [ebp-A0h]
  unsigned int v32; // [esp+8h] [ebp-A0h]
  unsigned int v33; // [esp+Ch] [ebp-9Ch]
  int v34; // [esp+1Ch] [ebp-8Ch] BYREF
  int index; // [esp+20h] [ebp-88h] BYREF
  float diversity; // [esp+24h] [ebp-84h] BYREF
  int shaderFlags; // [esp+28h] [ebp-80h] BYREF
  int channel; // [esp+2Ch] [ebp-7Ch] BYREF
  float over; // [esp+30h] [ebp-78h] BYREF
  float to; // [esp+34h] [ebp-74h] BYREF
  idSoundEmitterLocal *v41; // [esp+38h] [ebp-70h] BYREF
  idVec3 velocity; // [esp+3Ch] [ebp-6Ch] BYREF
  idVec3 origin; // [esp+48h] [ebp-60h] BYREF
  idStr v44; // [esp+54h] [ebp-54h] BYREF
  soundShaderParms_t parms; // [esp+74h] [ebp-34h] BYREF
  int v46; // [esp+A4h] [ebp-4h]

  if ( readDemo && readDemo->ReadChar(readDemo, (char *)&v34 + 3) )
  {
    switch ( HIBYTE(v34) )
    {
      case 0:
        this->ReadFromSaveGame(this, worldId, readDemo);
        this->SetActiveSoundWorld(this, 1);
        return;
      case 1:
        readDemo->ReadVec3(readDemo, &velocity);
        readDemo->ReadMat3(readDemo, (idMat3 *)&parms);
        readDemo->ReadInt(readDemo, (int *)&diversity);
        readDemo->ReadInt(readDemo, &shaderFlags);
        v44.alloced = 20;
        v44.data = v44.baseBuffer;
        v44.baseBuffer[0] = 0;
        v4 = 0;
        do
        {
          v5 = aUndefined_0[v4];
          v44.baseBuffer[v4++] = v5;
        }
        while ( v5 );
        v44.len = 9;
        v6 = this->__vftable;
        v46 = 0;
        v6->PlaceListener(this, &velocity, (const idMat3 *)&parms, LODWORD(diversity), shaderFlags, &v44);
        v46 = -1;
        idStr::FreeData(&v44);
        return;
      case 2:
        readDemo->Read(readDemo, &index, 4);
        if ( index < 1 || (v7 = this->GetNumEmitters(this), index > v7) )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "idSoundWorldLocal::ProcessDemoCommand: bad emitter number");
        Sys_EnterCriticalSection(0);
        v8 = this->GetNumEmitters(this);
        if ( index == v8 )
        {
          if ( Memory::mAllocator )
            v9 = (idSoundEmitterLocal *)Memory::mAllocator(0x5A0u);
          else
            v9 = (idSoundEmitterLocal *)malloc(0x5A0u);
          v41 = v9;
          v46 = 1;
          if ( v9 )
          {
            idSoundEmitterLocal::idSoundEmitterLocal(v9);
            diversity = v10;
          }
          else
          {
            diversity = 0.0;
          }
          v11 = this->emitters.list == 0;
          v46 = -1;
          shaderFlags = LODWORD(diversity);
          if ( v11 )
          {
            granularity = this->emitters.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->emitters.size )
              {
                v13 = granularity < this->emitters.num;
                this->emitters.size = granularity;
                if ( v13 )
                  this->emitters.num = granularity;
                v33 = 4 * granularity;
                if ( Memory::mAllocator )
                  v14 = (idSoundEmitterLocal **)Memory::mAllocator(v33);
                else
                  v14 = (idSoundEmitterLocal **)malloc(v33);
                this->emitters.list = v14;
                for ( i = 0; i < this->emitters.num; ++i )
                  this->emitters.list[i] = *(idSoundEmitterLocal **)(4 * i);
              }
            }
            else
            {
              this->emitters.list = 0;
              this->emitters.num = 0;
              this->emitters.size = 0;
            }
          }
          size = this->emitters.size;
          num = this->emitters.num;
          if ( num != size )
            goto LABEL_50;
          if ( !this->emitters.granularity )
            this->emitters.granularity = 16;
          v18 = size + this->emitters.granularity - (size + this->emitters.granularity) % this->emitters.granularity;
          if ( v18 > 0 )
          {
            if ( v18 != this->emitters.size )
            {
              list = this->emitters.list;
              this->emitters.size = v18;
              if ( v18 < num )
                this->emitters.num = v18;
              v32 = 4 * v18;
              if ( Memory::mAllocator )
                v20 = (idSoundEmitterLocal **)Memory::mAllocator(v32);
              else
                v20 = (idSoundEmitterLocal **)malloc(v32);
              this->emitters.list = v20;
              for ( j = 0; j < this->emitters.num; ++j )
                this->emitters.list[j] = list[j];
              if ( list )
              {
                if ( Memory::mDeallocator )
                  Memory::mDeallocator(list);
                else
                  free(list);
              }
            }
            goto LABEL_50;
          }
          if ( this->emitters.list )
          {
            v31 = this->emitters.list;
            if ( Memory::mDeallocator )
            {
              Memory::mDeallocator(v31);
              this->emitters.list = 0;
              this->emitters.num = 0;
              this->emitters.size = 0;
LABEL_50:
              *(float *)&this->emitters.list[this->emitters.num++] = diversity;
              goto LABEL_52;
            }
            free(v31);
          }
          this->emitters.list = 0;
          this->emitters.num = 0;
          this->emitters.size = 0;
          goto LABEL_50;
        }
        shaderFlags = (int)this->emitters.list[index];
LABEL_52:
        v22 = (_DWORD *)shaderFlags;
        idSoundEmitterLocal::Clear((idSoundEmitterLocal *)shaderFlags);
        v22[2] = index;
        v22[3] = 0;
        v22[1] = worldId;
        Sys_LeaveCriticalSection(0);
        break;
      case 3:
        readDemo->ReadInt(readDemo, &index);
        readDemo->ReadBool(readDemo, (bool *)&shaderFlags);
        soundSystem->FreeSoundEmitter(soundSystem, worldId, index, shaderFlags);
        return;
      case 4:
        readDemo->ReadInt(readDemo, &index);
        readDemo->ReadVec3(readDemo, &origin);
        readDemo->ReadVec3(readDemo, &velocity);
        readDemo->ReadInt(readDemo, &shaderFlags);
        readDemo->Read(readDemo, &parms, 40);
        v23 = this->EmitterForIndex(this, worldId, index);
        v23->UpdateEmitter(v23, &origin, &velocity, shaderFlags, &parms);
        return;
      case 5:
        readDemo->ReadInt(readDemo, &index);
        v24 = declManager->__vftable;
        HashString = idDemoFile::ReadHashString(readDemo);
        v26 = (int)v24->FindSound(declManager, HashString, 1);
        readDemo->ReadInt(readDemo, &channel);
        readDemo->ReadFloat(readDemo, &diversity);
        readDemo->ReadInt(readDemo, &shaderFlags);
        v27 = this->EmitterForIndex(this, worldId, index);
        ((void (__thiscall *)(idSoundEmitter *, int, int, _DWORD, int))v27->StartSound)(
          v27,
          v26,
          channel,
          LODWORD(diversity),
          shaderFlags);
        return;
      case 6:
        readDemo->ReadInt(readDemo, &index);
        readDemo->ReadInt(readDemo, &channel);
        readDemo->Read(readDemo, &parms, 40);
        v28 = this->EmitterForIndex(this, worldId, index);
        v28->ModifySound(v28, channel, &parms);
        return;
      case 7:
        readDemo->ReadInt(readDemo, &index);
        readDemo->ReadInt(readDemo, &channel);
        v29 = this->EmitterForIndex(this, worldId, index);
        v29->StopSound(v29, channel);
        return;
      case 8:
        readDemo->ReadInt(readDemo, &index);
        readDemo->ReadInt(readDemo, (int *)&v41);
        readDemo->ReadFloat(readDemo, &to);
        readDemo->ReadFloat(readDemo, &over);
        v30 = this->EmitterForIndex(this, worldId, index);
        ((void (__thiscall *)(idSoundEmitter *, idSoundEmitterLocal *, _DWORD, _DWORD))v30->FadeSound)(
          v30,
          v41,
          LODWORD(to),
          LODWORD(over));
        return;
      default:
        return;
    }
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::ReadFromSaveGame(int,class idFile *)
void __thiscall idSoundSystemLocal::ReadFromSaveGame(idSoundSystemLocal *this, int worldId, idFile *savefile)
{
  int v5; // eax
  char v6; // cl
  idSoundSystemLocal_vtbl *v7; // edx
  int v8; // eax
  int v9; // ecx
  idSoundEmitterLocal *v10; // eax
  idSoundEmitterLocal *v11; // eax
  bool v12; // zf
  int granularity; // eax
  bool v14; // cc
  idSoundEmitterLocal **v15; // eax
  int j; // eax
  int v17; // ebp
  int size; // eax
  int v19; // ecx
  idSoundEmitterLocal **list; // ebx
  idSoundEmitterLocal **v21; // eax
  int k; // eax
  int v23; // eax
  int v24; // ebx
  idSoundEmitterLocal *v25; // ebx
  idSoundChannel *channels; // ebp
  int m; // eax
  int v28; // eax
  int v29; // ebp
  idSoundCache *soundCache; // ecx
  char v31; // dl
  int v32; // ecx
  int v33; // eax
  int v34; // edx
  int v35; // eax
  unsigned int v36; // [esp+68h] [ebp-B8h]
  idSoundEmitterLocal **v37; // [esp+68h] [ebp-B8h]
  unsigned int v38; // [esp+68h] [ebp-B8h]
  idSoundEmitterLocal *i; // [esp+7Ch] [ebp-A4h]
  int ia; // [esp+7Ch] [ebp-A4h]
  int channel; // [esp+80h] [ebp-A0h] BYREF
  int num; // [esp+84h] [ebp-9Ch] BYREF
  int v43; // [esp+88h] [ebp-98h]
  int listenerId; // [esp+8Ch] [ebp-94h] BYREF
  int currentSoundTime; // [esp+90h] [ebp-90h]
  int gameTime; // [esp+94h] [ebp-8Ch] BYREF
  int savedSoundTime; // [esp+98h] [ebp-88h] BYREF
  int soundTimeOffset; // [esp+9Ch] [ebp-84h]
  int handle; // [esp+A0h] [ebp-80h] BYREF
  idStr soundShader; // [esp+A4h] [ebp-7Ch] BYREF
  idStr v51; // [esp+C4h] [ebp-5Ch] BYREF
  idVec3 origin; // [esp+E4h] [ebp-3Ch] BYREF
  idMat3 axis; // [esp+F0h] [ebp-30h] BYREF
  int v54; // [esp+11Ch] [ebp-4h]

  soundShader.len = 0;
  soundShader.alloced = 20;
  soundShader.data = soundShader.baseBuffer;
  soundShader.baseBuffer[0] = 0;
  v54 = 0;
  Sys_EnterCriticalSection(0);
  idSoundSystemLocal::ClearAllSoundEmitters(this);
  savefile->ReadVec3(savefile, &origin);
  savefile->ReadMat3(savefile, &axis);
  savefile->ReadInt(savefile, &listenerId);
  savefile->ReadInt(savefile, &gameTime);
  savefile->ReadInt(savefile, &this->game44kHz);
  savefile->ReadInt(savefile, &savedSoundTime);
  currentSoundTime = idSoundSystemLocal::GetCurrent44kHzTime(this);
  soundTimeOffset = currentSoundTime - savedSoundTime;
  this->pause44kHz = currentSoundTime;
  v51.alloced = 20;
  v51.data = v51.baseBuffer;
  v51.baseBuffer[0] = 0;
  v5 = 0;
  do
  {
    v6 = aUndefined_0[v5];
    v51.baseBuffer[v5++] = v6;
  }
  while ( v6 );
  v51.len = 9;
  v7 = this->__vftable;
  LOBYTE(v54) = 1;
  v7->PlaceListener(this, &origin, &axis, listenerId, gameTime, &v51);
  LOBYTE(v54) = 0;
  idStr::FreeData(&v51);
  savefile->ReadInt(savefile, &num);
  v8 = this->GetNumEmitters(this);
  v9 = num;
  if ( v8 < num )
  {
    while ( 1 )
    {
      if ( Memory::mAllocator )
        v10 = (idSoundEmitterLocal *)Memory::mAllocator(0x5A0u);
      else
        v10 = (idSoundEmitterLocal *)malloc(0x5A0u);
      v43 = (int)v10;
      LOBYTE(v54) = 2;
      if ( v10 )
      {
        idSoundEmitterLocal::idSoundEmitterLocal(v10);
        i = v11;
      }
      else
      {
        i = 0;
      }
      v12 = this->emitters.list == 0;
      LOBYTE(v54) = 0;
      if ( v12 )
      {
        granularity = this->emitters.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->emitters.size )
          {
            v14 = granularity < this->emitters.num;
            this->emitters.size = granularity;
            if ( v14 )
              this->emitters.num = granularity;
            v36 = 4 * granularity;
            if ( Memory::mAllocator )
              v15 = (idSoundEmitterLocal **)Memory::mAllocator(v36);
            else
              v15 = (idSoundEmitterLocal **)malloc(v36);
            this->emitters.list = v15;
            for ( j = 0; j < this->emitters.num; ++j )
              this->emitters.list[j] = *(idSoundEmitterLocal **)(4 * j);
          }
        }
        else
        {
          this->emitters.list = 0;
          this->emitters.num = 0;
          this->emitters.size = 0;
        }
      }
      v17 = this->emitters.num;
      size = this->emitters.size;
      if ( v17 != size )
        goto LABEL_42;
      if ( !this->emitters.granularity )
        this->emitters.granularity = 16;
      v19 = size + this->emitters.granularity - (size + this->emitters.granularity) % this->emitters.granularity;
      if ( v19 > 0 )
      {
        if ( v19 != this->emitters.size )
        {
          list = this->emitters.list;
          this->emitters.size = v19;
          if ( v19 < v17 )
            this->emitters.num = v19;
          v38 = 4 * v19;
          if ( Memory::mAllocator )
            v21 = (idSoundEmitterLocal **)Memory::mAllocator(v38);
          else
            v21 = (idSoundEmitterLocal **)malloc(v38);
          this->emitters.list = v21;
          for ( k = 0; k < this->emitters.num; ++k )
            this->emitters.list[k] = list[k];
          if ( list )
          {
            if ( Memory::mDeallocator )
              Memory::mDeallocator(list);
            else
              free(list);
          }
        }
        goto LABEL_42;
      }
      if ( !this->emitters.list )
        goto LABEL_29;
      v37 = this->emitters.list;
      if ( !Memory::mDeallocator )
        break;
      Memory::mDeallocator(v37);
      this->emitters.list = 0;
      this->emitters.num = 0;
      this->emitters.size = 0;
LABEL_42:
      this->emitters.list[this->emitters.num++] = i;
      i->index = this->emitters.num - 1;
      i->worldId = worldId;
      v23 = this->GetNumEmitters(this);
      v9 = num;
      if ( v23 >= num )
        goto LABEL_43;
    }
    free(v37);
LABEL_29:
    this->emitters.list = 0;
    this->emitters.num = 0;
    this->emitters.size = 0;
    goto LABEL_42;
  }
LABEL_43:
  v24 = 1;
  ia = 1;
  if ( v9 > 1 )
  {
    do
    {
      savefile->ReadInt(savefile, &handle);
      if ( handle >= 0 )
      {
        if ( handle != v24 )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "idSoundWorldLocal::ReadFromSaveGame: index mismatch");
        v25 = this->emitters.list[v24];
        v25->worldId = 1;
        v25->removeStatus = REMOVE_STATUS_ALIVE;
        v25->playing = 1;
        savefile->ReadVec3(savefile, &v25->origin);
        savefile->ReadInt(savefile, &v25->listenerId);
        idSoundSystemLocal::ReadFromSaveGameSoundShaderParams(this, savefile, &v25->parms);
        savefile->ReadFloat(savefile, &v25->amplitude);
        savefile->ReadInt(savefile, &v25->ampTime);
        channels = v25->channels;
        v43 = 8;
        do
        {
          idSoundSystemLocal::ReadFromSaveGameSoundChannel(this, savefile, channels++);
          --v43;
        }
        while ( v43 );
        savefile->ReadFloat(savefile, &v25->distance);
        savefile->ReadBool(savefile, &v25->hasShakes);
        savefile->ReadInt(savefile, &v25->lastValidPortalArea);
        savefile->ReadFloat(savefile, &v25->maxDistance);
        savefile->ReadBool(savefile, &v25->playing);
        savefile->ReadFloat(savefile, &v25->realDistance);
        savefile->ReadInt(savefile, (int *)&v25->removeStatus);
        savefile->ReadVec3(savefile, &v25->spatializedOrigin);
        savefile->ReadInt(savefile, &channel);
        for ( m = channel; channel >= 0; m = channel )
        {
          if ( m > 8 )
          {
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
              common.type,
              "idSoundWorldLocal::ReadFromSaveGame: channel > SOUND_MAX_CHANNELS");
            m = channel;
          }
          v28 = m;
          v29 = (int)&v25->channels[v28];
          if ( v25->channels[v28].decoder )
            v25->channels[v28].decoder = idSampleDecoder::Alloc();
          savefile->ReadString(savefile, &soundShader);
          *(_DWORD *)(v29 + 60) = declManager->FindSound(declManager, soundShader.data, 1);
          savefile->ReadString(savefile, &soundShader);
          soundCache = this->soundCache;
          if ( soundCache )
            *(_DWORD *)(v29 + 48) = idSoundCache::FindSample(soundCache, &soundShader);
          else
            *(_DWORD *)(v29 + 48) = 0;
          v31 = *(_BYTE *)v29;
          v32 = soundTimeOffset;
          *(_DWORD *)(v29 + 4) += soundTimeOffset;
          v33 = *(_DWORD *)(v29 + 4);
          *(_BYTE *)(v29 + 116) = v31;
          v34 = currentSoundTime - v33;
          v35 = *(_DWORD *)(v29 + 100);
          *(_DWORD *)(v29 + 124) = v34;
          if ( v35 )
          {
            *(_DWORD *)(v29 + 104) += v32;
            *(_DWORD *)(v29 + 100) = v32 + v35;
          }
          savefile->ReadInt(savefile, &channel);
        }
        v24 = ia;
      }
      ia = ++v24;
    }
    while ( v24 < num );
  }
  Sys_LeaveCriticalSection(0);
  v54 = -1;
  idStr::FreeData(&soundShader);
}
