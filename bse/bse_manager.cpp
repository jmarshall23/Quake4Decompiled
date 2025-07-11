
// FUNC: public: virtual void __thiscall rvBSEManagerLocal::EndLevelLoad(void)
void __thiscall rvBSEManagerLocal::EndLevelLoad(rvBSEManagerLocal *this)
{
  rvBSEManagerLocal::mEffectRates[0] = 0.0;
  dword_1137DDA0 = 0;
  dword_1137DDA4 = 0;
}

// FUNC: public: virtual void __thiscall rvBSEManagerLocal::StartFrame(void)
void __thiscall rvBSEManagerLocal::StartFrame(rvBSEManagerLocal *this)
{
  if ( com_debugHudActive )
  {
    rvBSEManagerLocal::mPerfCounters[0] = 0;
    dword_1137DDAC = 0;
    dword_1137DDB0 = 0;
    dword_1137DDB4 = 0;
    dword_1137DDB8 = 0;
  }
}

// FUNC: public: virtual void __thiscall rvBSEManagerLocal::EndFrame(void)
void __thiscall rvBSEManagerLocal::EndFrame(rvBSEManagerLocal *this)
{
  float v1; // [esp+18h] [ebp-4h]

  if ( com_debugHudActive )
  {
    game->DebugSetInt(game, "fx_num_active", rvBSEManagerLocal::mPerfCounters[0]);
    game->DebugSetInt(game, "fx_num_particles", dword_1137DDB0);
    game->DebugSetInt(game, "fx_num_traces", dword_1137DDAC);
    v1 = (double)dword_1137DDB4 * 0.00000095367432;
    ((void (__stdcall *)(const char *, _DWORD))game->DebugSetFloat)("fx_num_texels", LODWORD(v1));
    game->DebugSetInt(game, "fx_num_segments", dword_1137DDB8);
  }
}

// FUNC: public: virtual void __thiscall rvBSEManagerLocal::UpdateRateTimes(void)
void __thiscall rvBSEManagerLocal::UpdateRateTimes(rvBSEManagerLocal *this)
{
  double v1; // st7
  double v2; // st7
  double v3; // st7

  v1 = rvBSEManagerLocal::mEffectRates[0] - 0.1;
  rvBSEManagerLocal::mEffectRates[0] = v1;
  if ( v1 < 0.0 )
    rvBSEManagerLocal::mEffectRates[0] = 0.0;
  v2 = *(float *)&dword_1137DDA0 - 0.1;
  *(float *)&dword_1137DDA0 = v2;
  if ( v2 < 0.0 )
    dword_1137DDA0 = 0;
  v3 = *(float *)&dword_1137DDA4 - 0.1;
  *(float *)&dword_1137DDA4 = v3;
  if ( v3 < 0.0 )
    dword_1137DDA4 = 0;
}

// FUNC: public: virtual float __thiscall rvBSEManagerLocal::EffectDuration(class rvRenderEffectLocal const *)
double __thiscall rvBSEManagerLocal::EffectDuration(rvBSEManagerLocal *this, const rvRenderEffectLocal *def)
{
  rvBSE *effect; // eax

  if ( def && def->index >= 0 && (effect = def->effect) != 0 )
    return effect->mDuration;
  else
    return 0.0;
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::CheckDefForSound(struct renderEffect_s const *)
int __thiscall rvBSEManagerLocal::CheckDefForSound(rvBSEManagerLocal *this, const renderEffect_s *def)
{
  return (int)def->declEffect[1].__vftable & 1;
}

// FUNC: public: void __thiscall rvBSEManagerLocal::SetDoubleVisionParms(float,float)
void __thiscall rvBSEManagerLocal::SetDoubleVisionParms(rvBSEManagerLocal *this, float time, float scale)
{
  ((void (__thiscall *)(idGame *, _DWORD, _DWORD, _DWORD))game->StartViewEffect)(game, 0, LODWORD(time), LODWORD(scale));
}

// FUNC: public: void __thiscall rvBSEManagerLocal::SetShakeParms(float,float)
void __thiscall rvBSEManagerLocal::SetShakeParms(rvBSEManagerLocal *this, float time, float scale)
{
  ((void (__thiscall *)(idGame *, int, _DWORD, _DWORD))game->StartViewEffect)(game, 1, LODWORD(time), LODWORD(scale));
}

// FUNC: public: void __thiscall rvBSEManagerLocal::SetTunnelParms(float,float)
void __thiscall rvBSEManagerLocal::SetTunnelParms(rvBSEManagerLocal *this, float time, float scale)
{
  ((void (__thiscall *)(idGame *, int, _DWORD, _DWORD))game->StartViewEffect)(game, 2, LODWORD(time), LODWORD(scale));
}

// FUNC: public: void __thiscall rvBSEManagerLocal::Stats(class idCmdArgs const &)
void __userpurge rvBSEManagerLocal::Stats(rvBSEManagerLocal *this@<ecx>, int a2@<edi>, const idCmdArgs *args)
{
  const char *v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // ebp
  int v8; // esi
  rvDeclEffect *v9; // edi
  int num; // ebx
  int j; // esi
  rvSegmentTemplate *SegmentTemplate; // eax
  int loaded; // [esp+2Ch] [ebp-18h]
  int never; // [esp+30h] [ebp-14h]
  int haveParts; // [esp+34h] [ebp-10h]
  int i; // [esp+38h] [ebp-Ch]
  float ia; // [esp+38h] [ebp-Ch]
  int partTotal; // [esp+3Ch] [ebp-8h]
  int loadall; // [esp+40h] [ebp-4h]
  float argsa; // [esp+48h] [ebp+4h]

  if ( args->argc <= 1 )
    v3 = &entityFilter;
  else
    v3 = args->argv[1];
  v4 = idStr::Icmp(v3, "all");
  v5 = *(_DWORD *)common.type;
  LOBYTE(loadall) = v4 == 0;
  v6 = declManager->GetNumDecls(declManager, DECL_EFFECT);
  (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(common.type, "... processing %d registered effects\n", v6);
  v7 = 1;
  v8 = 1;
  loaded = 1;
  never = 0;
  partTotal = 1;
  haveParts = 1;
  i = 1;
  if ( declManager->GetNumDecls(declManager, DECL_EFFECT) > 1 )
  {
    do
    {
      v9 = (rvDeclEffect *)((int (__thiscall *)(idDeclManager *, int, int, int))declManager->EffectByIndex)(
                             declManager,
                             v8,
                             loadall,
                             a2);
      if ( v9->base->GetState(v9->base) == DS_PARSED )
      {
        ++never;
        num = v9->mSegmentTemplates.num;
        for ( j = 0; j < num; ++j )
        {
          SegmentTemplate = rvDeclEffect::GetSegmentTemplate(v9, j);
          if ( (SegmentTemplate->mFlags & 4) != 0 )
          {
            loadall = (int)SegmentTemplate->mCount.y;
            v7 += loadall;
            ++i;
          }
        }
        loaded += num;
        v8 = partTotal;
      }
      else if ( !v9->base->EverReferenced(v9->base) )
      {
        ++haveParts;
      }
      ++v8;
      a2 = 9;
      partTotal = v8;
    }
    while ( v8 < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
    partTotal = v7;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%d segments in %d loaded effects (%d never referenced)\n",
    1,
    loaded,
    never);
  argsa = (float)1;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%.2f segments per effect\n",
    argsa / (double)loaded);
  ia = (float)haveParts;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%.2f of segments have particles\n",
    ia / argsa);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%.2f particles per segment with particles\n",
    (double)partTotal / ia);
}

// FUNC: void __cdecl BSE_Stats_f(class idCmdArgs const &)
void __usercall BSE_Stats_f(int a1@<edi>, const idCmdArgs *args)
{
  rvBSEManagerLocal::Stats(&bseLocal, a1, args);
}

// FUNC: void __cdecl BSE_Log_f(class idCmdArgs const &)
void __usercall BSE_Log_f(int a1@<ecx>, int a2@<edi>, int a3@<esi>, const idCmdArgs *args)
{
  int v4; // esi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // esi
  int v9; // edi
  int v10; // ebp
  int v11; // eax
  int v12; // esi
  int v13; // eax
  void *retaddr; // [esp+1Ch] [ebp+0h]

  v4 = *(_DWORD *)common.type;
  v5 = ((int (__thiscall *)(idDeclManager *, int, int))declManager->GetNumDecls)(declManager, 9, a3);
  (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "Processing %d effect decls....\n", v5);
  retaddr = 0;
  v6 = 1;
  if ( declManager->GetNumDecls(declManager, DECL_EFFECT) > 1 )
  {
    do
    {
      v7 = ((int (__thiscall *)(idDeclManager *, int, _DWORD, int))declManager->EffectByIndex)(declManager, v6, 0, a2);
      v8 = *(_DWORD *)(v7 + 44);
      if ( v8 || *(_DWORD *)(v7 + 48) )
      {
        v9 = *(_DWORD *)(v7 + 48);
        v10 = *(_DWORD *)common.type;
        v11 = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v7 + 4) + 4))(*(_DWORD *)(v7 + 4));
        (*(void (**)(netadrtype_t, const char *, ...))(v10 + 124))(
          common.type,
          "%d plays (%d loops): '%s'\n",
          v8,
          v9,
          v11);
        args = (const idCmdArgs *)((char *)args + 1);
      }
      a2 = 9;
      ++v6;
    }
    while ( v6 < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
  }
  v12 = *(_DWORD *)common.type;
  v13 = declManager->GetNumDecls(declManager, DECL_EFFECT);
  (*(void (**)(netadrtype_t, const char *, ...))(v12 + 124))(
    common.type,
    "%d effects played or looped out of %d\n",
    a1,
    v13);
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::Filtered(char const *,enum effectCategory_t)
bool __thiscall rvBSEManagerLocal::Filtered(rvBSEManagerLocal *this, const char *name, effectCategory_t category)
{
  const char *value; // ecx
  int v5; // eax

  value = bse_singleEffect.internalVar->value;
  v5 = 0;
  if ( !*value )
    return !this->CanPlayRateLimited(this, category);
  do
    ++v5;
  while ( value[v5] );
  return v5 && !strstr(name, bse_singleEffect.internalVar->value) || !this->CanPlayRateLimited(this, category);
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::CanPlayRateLimited(enum effectCategory_t)
bool __thiscall rvBSEManagerLocal::CanPlayRateLimited(rvBSEManagerLocal *this, effectCategory_t category)
{
  float *v2; // esi
  bool result; // al
  float categorya; // [esp+8h] [ebp+4h]

  if ( category == EC_IGNORE || bse_rateLimit.internalVar->floatValue <= 0.1 )
    return 1;
  v2 = &rvBSEManagerLocal::mEffectRates[category];
  categorya = effectCosts[category] * bse_rateCost.internalVar->floatValue;
  if ( bse_rateLimit.internalVar->floatValue * 0.5 < *v2
    && categorya + *v2 > rvRandom::flrand(0.0, bse_rateLimit.internalVar->floatValue) )
  {
    return 0;
  }
  result = 1;
  *v2 = categorya + *v2;
  return result;
}

// FUNC: public: virtual void __thiscall rvBSEManagerLocal::StopEffect(class rvRenderEffectLocal *)
void __thiscall rvBSEManagerLocal::StopEffect(rvBSEManagerLocal *this, rvRenderEffectLocal *def)
{
  int v2; // edi
  const char *v3; // eax

  if ( def && def->index >= 0 && def->effect )
  {
    if ( bse_debug.internalVar->integerValue )
    {
      v2 = *(_DWORD *)common.type;
      v3 = def->parms.declEffect->base->GetName(def->parms.declEffect->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v2 + 124))(common.type, "BSE: Stop: %s\n", v3);
    }
    def->effect->mFlags |= 8u;
  }
}

// FUNC: public: virtual void __thiscall rvBSEManagerLocal::FreeEffect(class rvRenderEffectLocal *)
void __thiscall rvBSEManagerLocal::FreeEffect(rvBSEManagerLocal *this, rvRenderEffectLocal *def)
{
  int v2; // edi
  const char *v3; // eax
  idBlockAlloc<rvBSE,256,26>::element_s *p_list; // eax

  if ( def && def->index >= 0 && def->effect )
  {
    if ( bse_debug.internalVar->integerValue )
    {
      v2 = *(_DWORD *)common.type;
      v3 = def->parms.declEffect->base->GetName(def->parms.declEffect->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v2 + 124))(common.type, "BSE: Free: %s\n", v3);
    }
    rvBSE::Destroy(def->effect);
    p_list = (idBlockAlloc<rvBSE,256,26>::element_s *)&def->effect[-1].mSegments.list;
    p_list->next = rvBSEManagerLocal::effects.free;
    --rvBSEManagerLocal::effects.active;
    rvBSEManagerLocal::effects.free = p_list;
    def->effect = 0;
  }
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::ServiceEffect(class rvRenderEffectLocal *,float)
char __thiscall rvBSEManagerLocal::ServiceEffect(rvBSEManagerLocal *this, rvRenderEffectLocal *def, float time)
{
  rvBSE *effect; // edi
  rvBSEManagerLocal_vtbl *v5; // ebp
  int v6; // eax

  effect = def->effect;
  if ( !effect )
    return 1;
  v5 = this->__vftable;
  v6 = ((int (__thiscall *)(idDeclBase *, _DWORD))def->parms.declEffect->base->GetName)(def->parms.declEffect->base, 0);
  if ( ((unsigned __int8 (__thiscall *)(rvBSEManagerLocal *, int))v5->Filtered)(this, v6)
    || rvBSE::Service(effect, &def->parms, time) )
  {
    return 1;
  }
  def->referenceBounds = effect->mCurrentLocalBounds;
  if ( com_debugHudActive )
    ++rvBSEManagerLocal::mPerfCounters[0];
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 104))(*(_DWORD *)common.ip)
    || bse_debug.internalVar->integerValue )
  {
    rvBSE::EvaluateCost(effect, -1);
  }
  return 0;
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::Finish(class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::Finish(rvDeclEffectEditLocal *this, rvDeclEffect *edit)
{
  rvDeclEffect::Finish(edit);
}

// FUNC: public: virtual class rvSegmentTemplate * __thiscall rvDeclEffectEditLocal::GetSegmentTemplate(class rvDeclEffect *,char const *)
rvSegmentTemplate *__thiscall rvDeclEffectEditLocal::GetSegmentTemplate(
        rvDeclEffectEditLocal *this,
        rvDeclEffect *edit,
        const char *name)
{
  return rvDeclEffect::GetSegmentTemplate(edit, name);
}

// FUNC: public: virtual class rvSegmentTemplate * __thiscall rvDeclEffectEditLocal::GetSegmentTemplate(class rvDeclEffect *,int)
rvSegmentTemplate *__thiscall rvDeclEffectEditLocal::GetSegmentTemplate(
        rvDeclEffectEditLocal *this,
        rvDeclEffect *edit,
        int i)
{
  return rvDeclEffect::GetSegmentTemplate(edit, i);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::CopyData(class rvDeclEffect *,class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::CopyData(rvDeclEffectEditLocal *this, rvDeclEffect *edit, rvDeclEffect *copy)
{
  rvDeclEffect::CopyData(edit, copy);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::CreateEditorOriginal(class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::CreateEditorOriginal(rvDeclEffectEditLocal *this, rvDeclEffect *edit)
{
  rvDeclEffect::CreateEditorOriginal(edit);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::DeleteEditorOriginal(class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::DeleteEditorOriginal(rvDeclEffectEditLocal *this, rvDeclEffect *edit)
{
  if ( edit )
    rvDeclEffect::DeleteEditorOriginal(edit);
}

// FUNC: public: virtual bool __thiscall rvDeclEffectEditLocal::CompareToEditorOriginal(class rvDeclEffect *)
bool __thiscall rvDeclEffectEditLocal::CompareToEditorOriginal(rvDeclEffectEditLocal *this, rvDeclEffect *edit)
{
  return rvDeclEffect::CompareToEditorOriginal(edit);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::RevertToEditorOriginal(class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::RevertToEditorOriginal(rvDeclEffectEditLocal *this, rvDeclEffect *edit)
{
  rvDeclEffect::Revert(edit);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::Init(class rvSegmentTemplate *,class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::Init(rvDeclEffectEditLocal *this, rvSegmentTemplate *edit, rvDeclEffect *decl)
{
  rvSegmentTemplate::Init(edit, decl);
}

// FUNC: public: virtual bool __thiscall rvDeclEffectEditLocal::Parse(class rvSegmentTemplate *,class rvDeclEffect *,int,class idLexer *)
bool __thiscall rvDeclEffectEditLocal::Parse(
        rvDeclEffectEditLocal *this,
        rvSegmentTemplate *edit,
        rvDeclEffect *effect,
        int type,
        idLexer *lexer)
{
  return rvSegmentTemplate::Parse(edit, effect, type, lexer);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::Finish(class rvSegmentTemplate *,class rvDeclEffect *)
void __thiscall rvDeclEffectEditLocal::Finish(
        rvDeclEffectEditLocal *this,
        rvSegmentTemplate *edit,
        rvDeclEffect *effect)
{
  rvSegmentTemplate::Finish(edit, effect);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SetName(class rvSegmentTemplate *,char const *)
void __thiscall rvDeclEffectEditLocal::SetName(rvDeclEffectEditLocal *this, rvSegmentTemplate *edit, char *name)
{
  idStr::operator=(&edit->mSegmentName, name);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::Finish(class rvParticleTemplate *)
void __thiscall rvDeclEffectEditLocal::Finish(rvDeclEffectEditLocal *this, rvParticleTemplate *edit)
{
  rvParticleTemplate::Finish(edit);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::Init(class rvParticleTemplate *)
void __thiscall rvDeclEffectEditLocal::Init(rvDeclEffectEditLocal *this, rvParticleTemplate *edit)
{
  rvParticleTemplate::Init(edit);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::FixupParms(class rvParticleTemplate *,class rvParticleParms *)
void __thiscall rvDeclEffectEditLocal::FixupParms(
        rvDeclEffectEditLocal *this,
        rvParticleTemplate *edit,
        rvParticleParms *parms)
{
  rvParticleTemplate::FixupParms(edit, parms);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SetMaterialName(class rvParticleTemplate *,char const *)
void __thiscall rvDeclEffectEditLocal::SetMaterialName(
        rvDeclEffectEditLocal *this,
        rvParticleTemplate *edit,
        char *name)
{
  idStr::operator=(&edit->mMaterialName, name);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SetModelName(class rvParticleTemplate *,char const *)
void __thiscall rvDeclEffectEditLocal::SetModelName(rvDeclEffectEditLocal *this, rvParticleTemplate *edit, char *name)
{
  idStr::operator=(&edit->mModelName, name);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SetEntityDefName(class rvParticleTemplate *,char const *)
void __thiscall rvDeclEffectEditLocal::SetEntityDefName(
        rvDeclEffectEditLocal *this,
        rvParticleTemplate *edit,
        char *name)
{
  idStr::operator=(&edit->mEntityDefName, name);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SetTrailTypeName(class rvParticleTemplate *,char const *)
void __thiscall rvDeclEffectEditLocal::SetTrailTypeName(
        rvDeclEffectEditLocal *this,
        rvParticleTemplate *edit,
        char *name)
{
  idStr::operator=(&edit->mTrailTypeName, name);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SetTrailMaterialName(class rvParticleTemplate *,char const *)
void __thiscall rvDeclEffectEditLocal::SetTrailMaterialName(
        rvDeclEffectEditLocal *this,
        rvParticleTemplate *edit,
        char *name)
{
  idStr::operator=(&edit->mTrailMaterialName, name);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::CalcRate(class rvEnvParms *,float *,float,int)
void __thiscall rvDeclEffectEditLocal::CalcRate(
        rvDeclEffectEditLocal *this,
        rvEnvParms *edit,
        float *rate,
        float duration,
        int count)
{
  rvEnvParms::CalcRate(edit, rate, duration, count);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::Evaluate3(class rvEnvParms *,float,float const *,float const *,float const *,float *)
void __thiscall rvDeclEffectEditLocal::Evaluate3(
        rvDeclEffectEditLocal *this,
        rvEnvParms *edit,
        float time,
        const float *start,
        const float *rate,
        const float *end,
        float *dest)
{
  rvEnvParms::Evaluate3(edit, time, start, rate, end, dest);
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::SwapSegments(class rvSegmentTemplate *,class rvSegmentTemplate *)
void __thiscall rvDeclEffectEditLocal::SwapSegments(
        rvDeclEffectEditLocal *this,
        rvSegmentTemplate *seg1,
        rvSegmentTemplate *seg2)
{
  rvSegmentTemplate temp; // [esp+8h] [ebp-5D8h] BYREF
  int v4; // [esp+5DCh] [ebp-4h]

  rvSegmentTemplate::rvSegmentTemplate(&temp);
  v4 = 0;
  rvSegmentTemplate::operator=((char *)&temp, (int)seg1);
  rvSegmentTemplate::operator=((char *)seg1, (int)seg2);
  rvSegmentTemplate::operator=((char *)seg2, (int)&temp);
  v4 = 1;
  rvParticleTemplate::~rvParticleTemplate(&temp.mParticleTemplate);
  v4 = -1;
  idStr::FreeData(&temp.mSegmentName);
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::Init(void)
char __thiscall rvBSEManagerLocal::Init(rvBSEManagerLocal *this)
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "----------------- BSE Init ------------------\n");
  declManager->FindEffect(declManager, "_default", 1);
  declManager->FindMaterial(declManager, "_default", 1);
  declManager->FindMaterial(declManager, "gfx/effects/particles_shapes/motionblur", 1);
  declManager->FindType(declManager, DECL_TABLE, "halfsintable", 1, 0);
  renderModelManager->FindModel(renderModelManager, "_default");
  rvBSEManagerLocal::g_decals = cvarSystem->Find(cvarSystem, "g_decals");
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 108))(*(_DWORD *)common.ip);
  rvBSEManagerLocal::mEffectRates[0] = 0.0;
  dword_1137DDA0 = 0;
  dword_1137DDA4 = 0;
  cmdSystem->AddCommand(
    cmdSystem,
    "bseStats",
    BSE_Stats_f,
    0,
    "Dumps the stats of every registered effect - use all to force parse every effect",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "bseLog",
    BSE_Log_f,
    0,
    "Dumps the number of times an effect has been played since game start",
    0);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "--------- BSE Created Successfully ----------\n");
  return 1;
}

// FUNC: public: virtual void __thiscall rvDeclEffectEditLocal::DeleteSegment(class rvDeclEffect *,int)
void __thiscall rvDeclEffectEditLocal::DeleteSegment(rvDeclEffectEditLocal *this, rvDeclEffect *edit, int index)
{
  rvDeclEffect::DeleteSegment(edit, index);
}

// FUNC: public: virtual int __thiscall rvDeclEffectEditLocal::AddSegment(class rvDeclEffect *,class rvSegmentTemplate *)
int __thiscall rvDeclEffectEditLocal::AddSegment(
        rvDeclEffectEditLocal *this,
        rvDeclEffect *edit,
        rvSegmentTemplate *add)
{
  return rvDeclEffect::AddSegment(edit, add);
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::PlayEffect(class rvRenderEffectLocal *,float)
char __thiscall rvBSEManagerLocal::PlayEffect(rvBSEManagerLocal *this, rvRenderEffectLocal *def, float time)
{
  rvDeclEffect *declEffect; // esi
  rvBSEManagerLocal_vtbl *v5; // ebp
  int v6; // eax
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v9; // eax
  int v10; // edi
  int v11; // eax
  rvBSE *v12; // eax

  declEffect = (rvDeclEffect *)def->parms.declEffect;
  v5 = this->__vftable;
  v6 = ((int (__thiscall *)(idDeclBase *, _DWORD))declEffect->base->GetName)(declEffect->base, 0);
  if ( ((unsigned __int8 (__thiscall *)(rvBSEManagerLocal *, int))v5->Filtered)(this, v6) )
    return 0;
  if ( bse_debug.internalVar->integerValue )
  {
    base = declEffect->base;
    v9 = base->__vftable;
    ++count;
    v10 = *(_DWORD *)common.type;
    v11 = ((int (__thiscall *)(idDeclBase *, _DWORD, _DWORD))v9->GetName)(
            base,
            COERCE_UNSIGNED_INT64(time),
            HIDWORD(COERCE_UNSIGNED_INT64(time)));
    (*(void (**)(netadrtype_t, const char *, ...))(v10 + 124))(common.type, "BSE: Play %d: %s at %g\n", count, v11);
  }
  ++declEffect->mPlayCount;
  v12 = idBlockAlloc<rvBSE,256,26>::Alloc(&rvBSEManagerLocal::effects);
  def->effect = v12;
  rvBSE::Init(v12, declEffect, &def->parms, time);
  return 1;
}

// FUNC: public: virtual bool __thiscall rvBSEManagerLocal::Shutdown(void)
char __thiscall rvBSEManagerLocal::Shutdown(rvBSEManagerLocal *this)
{
  int i; // esi

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "--------------- BSE Shutdown ----------------\n");
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 108))(*(_DWORD *)common.ip);
  for ( i = 0; i < rvBSEManagerLocal::mTraceModels.num; ++i )
    Memory::Free(rvBSEManagerLocal::mTraceModels.list[i]);
  if ( rvBSEManagerLocal::mTraceModels.list )
    Memory::Free(rvBSEManagerLocal::mTraceModels.list);
  rvBSEManagerLocal::mTraceModels.list = 0;
  rvBSEManagerLocal::mTraceModels.num = 0;
  rvBSEManagerLocal::mTraceModels.size = 0;
  idBlockAlloc<rvBSE,256,26>::Shutdown(&rvBSEManagerLocal::effects);
  rvBSEManagerLocal::mEffectRates[0] = 0.0;
  dword_1137DDA0 = 0;
  dword_1137DDA4 = 0;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
  return 1;
}
