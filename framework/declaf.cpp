
// FUNC: public: static enum declAFJointMod_t __cdecl idDeclAF::JointModFromString(char const *)
int __cdecl idDeclAF::JointModFromString(const char *str)
{
  int result; // eax
  int v2; // eax

  result = idStr::Icmp(str, "orientation");
  if ( result )
  {
    if ( idStr::Icmp(str, "position") )
    {
      v2 = -(idStr::Icmp(str, "both") != 0);
      LOBYTE(v2) = v2 & 0xFE;
      return v2 + 2;
    }
    else
    {
      return 1;
    }
  }
  return result;
}

// FUNC: public: virtual char const * __thiscall idDeclAF::DefaultDefinition(void)const
const char *__thiscall idDeclAF::DefaultDefinition(idDeclAF *this)
{
  return "{\n"
         "\tsettings {\n"
         "\t\tmodel \"\"\n"
         "\t\tskin \"\"\n"
         "\t\tfriction 0.01, 0.01, 0.8, 0.5\n"
         "\t\tsuspendSpeed 20, 30, 40, 60\n"
         "\t\tnoMoveTime 1\n"
         "\t\tnoMoveTranslation 10\n"
         "\t\tnoMoveRotation 10\n"
         "\t\tminMoveTime -1\n"
         "\t\tmaxMoveTime -1\n"
         "\t\ttotalMass -1\n"
         "\t\tcontents corpse\n"
         "\t\tclipMask solid, corpse\n"
         "\t\tselfCollision 1\n"
         "\t}\n"
         "\tbody \"body\" {\n"
         "\t\tjoint \"origin\"\n"
         "\t\tmod orientation\n"
         "\t\tmodel box( ( -10, -10, -10 ), ( 10, 10, 10 ) )\n"
         "\t\torigin ( 0, 0, 0 )\n"
         "\t\tdensity 0.2\n"
         "\t\tfriction 0.01, 0.01, 0.8\n"
         "\t\tcontents corpse\n"
         "\t\tclipMask solid, corpse\n"
         "\t\tselfCollision 1\n"
         "\t\tcontainedJoints \"*origin\"\n"
         "\t}\n"
         "}\n";
}

// FUNC: public: __thiscall idAFVector::idAFVector(void)
void __thiscall idAFVector::idAFVector(idAFVector *this)
{
  char *baseBuffer; // ecx

  this->joint1.len = 0;
  this->joint1.alloced = 20;
  baseBuffer = this->joint1.baseBuffer;
  this->joint1.data = baseBuffer;
  *baseBuffer = 0;
  this->joint2.len = 0;
  this->joint2.alloced = 20;
  this->joint2.data = this->joint2.baseBuffer;
  this->joint2.baseBuffer[0] = 0;
  this->type = VEC_COORDS;
  this->vec.z = 0.0;
  this->vec.y = 0.0;
  this->vec.x = 0.0;
  this->negate = 0;
}

// FUNC: public: bool __thiscall idAFVector::Write(class idFile *)const
bool __thiscall idAFVector::Write(idAFVector *this, idFile *f)
{
  bool result; // al

  if ( this->negate )
    f->WriteFloatString(f, "-");
  switch ( this->type )
  {
    case VEC_COORDS:
      f->WriteFloatString(f, "( %f, %f, %f )", this->vec.x, this->vec.y, this->vec.z);
      result = 1;
      break;
    case VEC_JOINT:
      f->WriteFloatString(f, "joint( \"%s\" )", this->joint1.data);
      result = 1;
      break;
    case VEC_BONECENTER:
      f->WriteFloatString(f, "bonecenter( \"%s\", \"%s\" )", this->joint1.data, this->joint2.data);
      result = 1;
      break;
    case VEC_BONEDIR:
      f->WriteFloatString(f, "bonedir( \"%s\", \"%s\" )", this->joint1.data, this->joint2.data);
      goto LABEL_8;
    default:
LABEL_8:
      result = 1;
      break;
  }
  return result;
}

// FUNC: public: __thiscall idDeclAF_Constraint::idDeclAF_Constraint(void)
void __thiscall idDeclAF_Constraint::idDeclAF_Constraint(idDeclAF_Constraint *this)
{
  char *data; // edx
  const char *v3; // ecx
  char v4; // al
  char *v5; // edx
  const char *v6; // ecx
  char v7; // al
  char *v8; // edx
  const char *v9; // ecx
  char v10; // al

  this->name.alloced = 20;
  this->name.len = 0;
  this->name.data = this->name.baseBuffer;
  this->name.baseBuffer[0] = 0;
  if ( this->name.alloced < 1 )
    idStr::ReAllocate(&this->name, 1, 1);
  data = this->name.data;
  v3 = &entityFilter;
  do
  {
    v4 = *v3;
    *data++ = *v3++;
  }
  while ( v4 );
  this->name.len = 0;
  this->body1.alloced = 20;
  this->body1.len = 0;
  this->body1.data = this->body1.baseBuffer;
  this->body1.baseBuffer[0] = 0;
  if ( this->body1.alloced < 1 )
    idStr::ReAllocate(&this->body1, 1, 1);
  v5 = this->body1.data;
  v6 = &entityFilter;
  do
  {
    v7 = *v6;
    *v5++ = *v6++;
  }
  while ( v7 );
  this->body1.len = 0;
  this->body2.alloced = 20;
  this->body2.len = 0;
  this->body2.data = this->body2.baseBuffer;
  this->body2.baseBuffer[0] = 0;
  if ( this->body2.alloced < 1 )
    idStr::ReAllocate(&this->body2, 1, 1);
  v8 = this->body2.data;
  v9 = &entityFilter;
  do
  {
    v10 = *v9;
    *v8++ = *v9++;
  }
  while ( v10 );
  this->body2.len = 0;
  this->type = DECLAF_CONSTRAINT_INVALID;
  this->friction = 0.0;
  this->stretch = 0.0;
  this->compress = 0.0;
  this->damping = 0.0;
  this->restLength = 0.0;
  this->minLength = 0.0;
  this->maxLength = 0.0;
  this->anchor.joint1.len = 0;
  this->anchor.joint1.alloced = 20;
  this->anchor.joint1.data = this->anchor.joint1.baseBuffer;
  this->anchor.joint1.baseBuffer[0] = 0;
  this->anchor.joint2.len = 0;
  this->anchor.joint2.alloced = 20;
  this->anchor.joint2.data = this->anchor.joint2.baseBuffer;
  this->anchor.joint2.baseBuffer[0] = 0;
  this->anchor.type = VEC_COORDS;
  this->anchor.vec.z = 0.0;
  this->anchor.vec.y = 0.0;
  this->anchor.vec.x = 0.0;
  this->anchor.negate = 0;
  this->anchor2.joint1.len = 0;
  this->anchor2.joint1.alloced = 20;
  this->anchor2.joint1.data = this->anchor2.joint1.baseBuffer;
  this->anchor2.joint1.baseBuffer[0] = 0;
  this->anchor2.joint2.len = 0;
  this->anchor2.joint2.alloced = 20;
  this->anchor2.joint2.data = this->anchor2.joint2.baseBuffer;
  this->anchor2.joint2.baseBuffer[0] = 0;
  this->anchor2.type = VEC_COORDS;
  this->anchor2.vec.z = 0.0;
  this->anchor2.vec.y = 0.0;
  this->anchor2.vec.x = 0.0;
  this->anchor2.negate = 0;
  `eh vector constructor iterator'(
    this->shaft,
    0x54u,
    2,
    (void (__thiscall *)(void *))idAFVector::idAFVector,
    (void (__thiscall *)(void *))idAFVector::~idAFVector);
  this->axis.joint1.len = 0;
  this->axis.joint1.alloced = 20;
  this->axis.joint1.data = this->axis.joint1.baseBuffer;
  this->axis.joint1.baseBuffer[0] = 0;
  this->axis.joint2.len = 0;
  this->axis.joint2.alloced = 20;
  this->axis.joint2.data = this->axis.joint2.baseBuffer;
  this->axis.joint2.baseBuffer[0] = 0;
  this->axis.type = VEC_COORDS;
  this->axis.vec.z = 0.0;
  this->axis.vec.y = 0.0;
  this->axis.vec.x = 0.0;
  this->axis.negate = 0;
  this->limitAxis.joint1.len = 0;
  this->limitAxis.joint1.alloced = 20;
  this->limitAxis.joint1.data = this->limitAxis.joint1.baseBuffer;
  this->limitAxis.joint1.baseBuffer[0] = 0;
  this->limitAxis.joint2.len = 0;
  this->limitAxis.joint2.alloced = 20;
  this->limitAxis.joint2.data = this->limitAxis.joint2.baseBuffer;
  this->limitAxis.joint2.baseBuffer[0] = 0;
  this->limitAxis.type = VEC_COORDS;
  this->limitAxis.vec.z = 0.0;
  this->limitAxis.vec.y = 0.0;
  this->limitAxis.vec.x = 0.0;
  this->limitAxis.negate = 0;
}

// FUNC: public: static int __cdecl idDeclAF::ContentsFromString(char const *)
int __cdecl idDeclAF::ContentsFromString(const char *str)
{
  int v1; // eax
  bool v2; // zf
  int v3; // esi
  idToken token; // [esp+4h] [ebp-124h] BYREF
  idLexer src; // [esp+54h] [ebp-D4h] BYREF
  int v7; // [esp+124h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v1 = 0;
  v2 = *str == 0;
  v7 = 0;
  if ( !v2 )
  {
    do
      ++v1;
    while ( str[v1] );
  }
  idLexer::idLexer(&src, str, v1, "idDeclAF::ContentsFromString", 0);
  LOBYTE(v7) = 1;
LABEL_4:
  v3 = 0;
  while ( idLexer::ReadToken(&src, &token) )
  {
    if ( !idStr::Icmp(token.data, "none") )
      goto LABEL_4;
    if ( idStr::Icmp(token.data, "solid") )
    {
      if ( idStr::Icmp(token.data, "body") )
      {
        if ( idStr::Icmp(token.data, "corpse") )
        {
          if ( idStr::Icmp(token.data, "playerclip") )
          {
            if ( idStr::Icmp(token.data, "monsterclip") )
            {
              if ( idStr::Icmp(token.data, "vehicleclip") )
              {
                if ( idStr::Icmp(token.data, "flyclip") )
                {
                  if ( idStr::Icmp(token.data, "itemclip") )
                  {
                    if ( idStr::Cmp(token.data, ",") )
                      break;
                  }
                  else
                  {
                    v3 |= 0x800000u;
                  }
                }
                else
                {
                  v3 |= 0x400000u;
                }
              }
              else
              {
                v3 |= 0x80000u;
              }
            }
            else
            {
              v3 |= 0x10u;
            }
          }
          else
          {
            v3 |= 8u;
          }
        }
        else
        {
          v3 |= 0x400u;
        }
      }
      else
      {
        v3 |= 0x100u;
      }
    }
    else
    {
      v3 |= 1u;
    }
  }
  LOBYTE(v7) = 0;
  idLexer::~idLexer(&src);
  v7 = -1;
  idStr::FreeData(&token);
  return v3;
}

// FUNC: public: virtual unsigned int __thiscall idDeclAF::Size(void)const
int __thiscall idDeclAF::Size(idDeclAF *this)
{
  int alloced; // eax
  int v2; // edx
  int v3; // eax

  if ( this->model.data == this->model.baseBuffer )
    alloced = 0;
  else
    alloced = this->model.alloced;
  v2 = alloced + 176;
  if ( this->skin.data == this->skin.baseBuffer )
    v3 = 4 * (this->bodies.size + this->constraints.size);
  else
    v3 = this->skin.alloced + 4 * (this->bodies.size + this->constraints.size);
  return v2 + v3;
}

// FUNC: public: void __thiscall idDeclAF::RenameBody(char const *,char const *)
void __thiscall idDeclAF::RenameBody(idDeclAF *this, const char *oldName, char *newName)
{
  int v4; // edi
  int v5; // edi
  idStr *p_body2; // ecx

  v4 = 0;
  if ( this->bodies.num > 0 )
  {
    while ( idStr::Icmp(this->bodies.list[v4]->name.data, oldName) )
    {
      if ( ++v4 >= this->bodies.num )
        goto LABEL_6;
    }
    idStr::operator=(&this->bodies.list[v4]->name, newName);
  }
LABEL_6:
  v5 = 0;
  if ( this->constraints.num > 0 )
  {
    while ( idStr::Icmp(this->constraints.list[v5]->body1.data, oldName) )
    {
      if ( !idStr::Icmp(this->constraints.list[v5]->body2.data, oldName) )
      {
        p_body2 = &this->constraints.list[v5]->body2;
        goto LABEL_11;
      }
LABEL_12:
      if ( ++v5 >= this->constraints.num )
        return;
    }
    p_body2 = &this->constraints.list[v5]->body1;
LABEL_11:
    idStr::operator=(p_body2, newName);
    goto LABEL_12;
  }
}

// FUNC: public: void __thiscall idDeclAF::RenameConstraint(char const *,char const *)
void __thiscall idDeclAF::RenameConstraint(idDeclAF *this, const char *oldName, char *newName)
{
  int v4; // esi

  v4 = 0;
  if ( this->constraints.num > 0 )
  {
    while ( idStr::Icmp(this->constraints.list[v4]->name.data, oldName) )
    {
      if ( ++v4 >= this->constraints.num )
        return;
    }
    idStr::operator=(&this->constraints.list[v4]->name, newName);
  }
}

// FUNC: public: virtual bool __thiscall rvDeclAFEditLocal::Save(class idDeclAF *)
char __thiscall rvDeclAFEditLocal::Save(rvDeclAFEditLocal *this, idDeclAF *edit)
{
  edit->RebuildTextSource(edit);
  edit->base->ReplaceSourceFileText(edit->base);
  edit->modified = 0;
  return 1;
}

// FUNC: public: virtual void __thiscall rvDeclAFEditLocal::RenameBody(class idDeclAF *,char const *,char const *)
void __thiscall rvDeclAFEditLocal::RenameBody(
        rvDeclAFEditLocal *this,
        idDeclAF *edit,
        const char *oldName,
        char *newName)
{
  idDeclAF::RenameBody(edit, oldName, newName);
}

// FUNC: public: virtual void __thiscall rvDeclAFEditLocal::RenameConstraint(class idDeclAF *,char const *,char const *)
void __thiscall rvDeclAFEditLocal::RenameConstraint(
        rvDeclAFEditLocal *this,
        idDeclAF *edit,
        const char *oldName,
        char *newName)
{
  idDeclAF::RenameConstraint(edit, oldName, newName);
}

// FUNC: public: bool __thiscall idAFVector::Parse(class idLexer &)
char __thiscall idAFVector::Parse(idAFVector *this, idLexer *src)
{
  int len; // esi
  idStr *p_joint1; // ebx
  char *data; // edi
  unsigned int v8; // ecx
  char *v9; // esi
  char v10; // dl
  char *v11; // edi
  char *v12; // esi
  char v13; // cl
  int v14; // esi
  int v15; // esi
  char *v16; // edi
  unsigned int v17; // ecx
  char *v18; // esi
  char v19; // al
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v21; // [esp+60h] [ebp-4h]
  idLexer *srca; // [esp+68h] [ebp+4h]
  int srcb; // [esp+68h] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v21 = 0;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_4;
  if ( idStr::Cmp(token.data, "-") )
  {
    this->negate = 0;
  }
  else
  {
    this->negate = 1;
    if ( !idLexer::ReadToken(src, &token) )
    {
LABEL_4:
      v21 = -1;
      idStr::FreeData(&token);
      return 0;
    }
  }
  if ( !idStr::Cmp(token.data, "(") )
  {
    this->type = VEC_COORDS;
    this->vec.x = idLexer::ParseFloat(src, 0);
    idLexer::ExpectTokenString(src, ",");
    this->vec.y = idLexer::ParseFloat(src, 0);
    idLexer::ExpectTokenString(src, ",");
    this->vec.z = idLexer::ParseFloat(src, 0);
LABEL_22:
    idLexer::ExpectTokenString(src, ")");
    v21 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  if ( !idStr::Cmp(token.data, "joint") )
  {
    this->type = VEC_JOINT;
    idLexer::ExpectTokenString(src, "(");
    idLexer::ReadToken(src, &token);
    len = token.len;
    p_joint1 = &this->joint1;
    srca = (idLexer *)token.len;
    if ( token.len + 1 > p_joint1->alloced )
      idStr::ReAllocate(p_joint1, token.len + 1, 0);
    data = p_joint1->data;
    v8 = len;
    v9 = token.data;
    v10 = v8;
    v8 >>= 2;
    qmemcpy(data, token.data, 4 * v8);
    v12 = &v9[4 * v8];
    v11 = &data[4 * v8];
    v13 = v10;
LABEL_21:
    qmemcpy(v11, v12, v13 & 3);
    *((_BYTE *)&srca->loaded + (unsigned int)p_joint1->data) = 0;
    p_joint1->len = (int)srca;
    goto LABEL_22;
  }
  if ( !idStr::Cmp(token.data, "bonecenter") )
  {
    this->type = VEC_BONECENTER;
LABEL_16:
    idLexer::ExpectTokenString(src, "(");
    idLexer::ReadToken(src, &token);
    v14 = token.len;
    srcb = token.len;
    if ( token.len + 1 > this->joint1.alloced )
      idStr::ReAllocate(&this->joint1, token.len + 1, 0);
    qmemcpy(this->joint1.data, token.data, v14);
    this->joint1.data[srcb] = 0;
    this->joint1.len = srcb;
    idLexer::ExpectTokenString(src, ",");
    idLexer::ReadToken(src, &token);
    v15 = token.len;
    p_joint1 = &this->joint2;
    srca = (idLexer *)token.len;
    if ( token.len + 1 > p_joint1->alloced )
      idStr::ReAllocate(p_joint1, token.len + 1, 0);
    v16 = p_joint1->data;
    v17 = v15;
    v18 = token.data;
    v19 = v17;
    v17 >>= 2;
    qmemcpy(v16, token.data, 4 * v17);
    v12 = &v18[4 * v17];
    v11 = &v16[4 * v17];
    v13 = v19;
    goto LABEL_21;
  }
  if ( !idStr::Cmp(token.data, "bonedir") )
  {
    this->type = VEC_BONEDIR;
    goto LABEL_16;
  }
  idLexer::Error(src, "unknown token %s in vector", token.data);
  v21 = -1;
  idStr::FreeData(&token);
  return 0;
}

// FUNC: public: void __thiscall idDeclAF_Body::SetDefault(class idDeclAF const *)
void __thiscall idDeclAF_Body::SetDefault(idDeclAF_Body *this, const idDeclAF *file)
{
  idStr::operator=(&this->name, "noname");
  this->modelType = 1;
  this->numSides = 3;
  this->v1.type = VEC_COORDS;
  this->v2.type = VEC_COORDS;
  this->v1.vec.z = -10.0;
  this->v1.vec.y = -10.0;
  this->v1.vec.x = -10.0;
  this->v2.vec.z = 10.0;
  this->v2.vec.y = 10.0;
  this->v2.vec.x = 10.0;
  this->origin.vec.z = 0.0;
  this->origin.vec.y = 0.0;
  this->origin.vec.x = 0.0;
  this->angles.roll = 0.0;
  this->angles.yaw = 0.0;
  this->angles.pitch = 0.0;
  this->density = 0.2;
  this->inertiaScale = mat3_identity;
  this->linearFriction = file->defaultLinearFriction;
  this->angularFriction = file->defaultAngularFriction;
  this->contactFriction = file->defaultContactFriction;
  this->contents = file->contents;
  this->clipMask = file->clipMask;
  this->selfCollision = file->selfCollision;
  this->frictionDirection.vec.z = 0.0;
  this->frictionDirection.vec.y = 0.0;
  this->frictionDirection.vec.x = 0.0;
  this->contactMotorDirection.vec.z = 0.0;
  this->contactMotorDirection.vec.y = 0.0;
  this->contactMotorDirection.vec.x = 0.0;
  idStr::operator=(&this->jointName, "origin");
  this->jointMod = DECLAF_JOINTMOD_AXIS;
  idStr::operator=(&this->containedJoints, "*origin");
}

// FUNC: public: __thiscall idDeclAF_Body::idDeclAF_Body(void)
void __thiscall idDeclAF_Body::idDeclAF_Body(idDeclAF_Body *this)
{
  this->name.len = 0;
  this->name.alloced = 20;
  this->name.data = this->name.baseBuffer;
  this->name.baseBuffer[0] = 0;
  this->jointName.len = 0;
  this->jointName.alloced = 20;
  this->jointName.data = this->jointName.baseBuffer;
  this->jointName.baseBuffer[0] = 0;
  this->v1.joint1.len = 0;
  this->v1.joint1.alloced = 20;
  this->v1.joint1.data = this->v1.joint1.baseBuffer;
  this->v1.joint1.baseBuffer[0] = 0;
  this->v1.joint2.len = 0;
  this->v1.joint2.alloced = 20;
  this->v1.joint2.data = this->v1.joint2.baseBuffer;
  this->v1.joint2.baseBuffer[0] = 0;
  this->v1.type = VEC_COORDS;
  this->v1.vec.z = 0.0;
  this->v1.vec.y = 0.0;
  this->v1.vec.x = 0.0;
  this->v1.negate = 0;
  this->v2.joint1.len = 0;
  this->v2.joint1.alloced = 20;
  this->v2.joint1.data = this->v2.joint1.baseBuffer;
  this->v2.joint1.baseBuffer[0] = 0;
  this->v2.joint2.len = 0;
  this->v2.joint2.alloced = 20;
  this->v2.joint2.data = this->v2.joint2.baseBuffer;
  this->v2.joint2.baseBuffer[0] = 0;
  this->v2.type = VEC_COORDS;
  this->v2.vec.z = 0.0;
  this->v2.vec.y = 0.0;
  this->v2.vec.x = 0.0;
  this->v2.negate = 0;
  this->origin.joint1.len = 0;
  this->origin.joint1.alloced = 20;
  this->origin.joint1.data = this->origin.joint1.baseBuffer;
  this->origin.joint1.baseBuffer[0] = 0;
  this->origin.joint2.len = 0;
  this->origin.joint2.alloced = 20;
  this->origin.joint2.data = this->origin.joint2.baseBuffer;
  this->origin.joint2.baseBuffer[0] = 0;
  this->origin.type = VEC_COORDS;
  this->origin.vec.z = 0.0;
  this->origin.vec.y = 0.0;
  this->origin.vec.x = 0.0;
  this->origin.negate = 0;
  this->containedJoints.len = 0;
  this->containedJoints.alloced = 20;
  this->containedJoints.data = this->containedJoints.baseBuffer;
  this->containedJoints.baseBuffer[0] = 0;
  this->frictionDirection.joint1.len = 0;
  this->frictionDirection.joint1.alloced = 20;
  this->frictionDirection.joint1.data = this->frictionDirection.joint1.baseBuffer;
  this->frictionDirection.joint1.baseBuffer[0] = 0;
  this->frictionDirection.joint2.len = 0;
  this->frictionDirection.joint2.alloced = 20;
  this->frictionDirection.joint2.data = this->frictionDirection.joint2.baseBuffer;
  this->frictionDirection.joint2.baseBuffer[0] = 0;
  this->frictionDirection.type = VEC_COORDS;
  this->frictionDirection.vec.z = 0.0;
  this->frictionDirection.vec.y = 0.0;
  this->frictionDirection.vec.x = 0.0;
  this->frictionDirection.negate = 0;
  this->contactMotorDirection.joint1.len = 0;
  this->contactMotorDirection.joint1.alloced = 20;
  this->contactMotorDirection.joint1.data = this->contactMotorDirection.joint1.baseBuffer;
  this->contactMotorDirection.joint1.baseBuffer[0] = 0;
  this->contactMotorDirection.joint2.alloced = 20;
  this->contactMotorDirection.joint2.len = 0;
  this->contactMotorDirection.joint2.data = this->contactMotorDirection.joint2.baseBuffer;
  this->contactMotorDirection.joint2.baseBuffer[0] = 0;
  this->contactMotorDirection.type = VEC_COORDS;
  this->contactMotorDirection.vec.z = 0.0;
  this->contactMotorDirection.vec.y = 0.0;
  this->contactMotorDirection.vec.x = 0.0;
  this->contactMotorDirection.negate = 0;
}

// FUNC: public: void __thiscall idDeclAF_Constraint::SetDefault(class idDeclAF const *)
void __thiscall idDeclAF_Constraint::SetDefault(idDeclAF_Constraint *this, const idDeclAF *file)
{
  const idDeclAF *v3; // esi
  idDeclAF_Body *v4; // eax
  unsigned int len; // esi
  idDeclAF_Body *v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  idStr::operator=(&this->name, "noname");
  v3 = file;
  this->type = DECLAF_CONSTRAINT_UNIVERSALJOINT;
  if ( file->bodies.num )
  {
    v4 = *file->bodies.list;
    len = v4->name.len;
    v6 = v4;
    v7 = v4->name.len;
    if ( v4->name.len + 1 > this->body1.alloced )
    {
      idStr::ReAllocate(&this->body1, len + 1, 0);
      v4 = v6;
    }
    qmemcpy(this->body1.data, v4->name.data, len);
    v3 = file;
    this->body1.data[v7] = 0;
    this->body1.len = v7;
  }
  else
  {
    idStr::operator=(&this->body1, "world");
  }
  idStr::operator=(&this->body2, "world");
  this->friction = v3->defaultConstraintFriction;
  this->anchor.vec.z = 0.0;
  this->anchor.vec.y = 0.0;
  this->anchor.vec.x = 0.0;
  this->anchor2.vec.z = 0.0;
  this->anchor2.vec.y = 0.0;
  this->anchor2.vec.x = 0.0;
  this->axis.vec.y = 0.0;
  this->axis.vec.z = 0.0;
  this->axis.vec.x = 1.0;
  this->shaft[0].vec.x = 0.0;
  this->shaft[0].vec.y = 0.0;
  this->shaft[0].vec.z = -1.0;
  this->shaft[1].vec.x = 0.0;
  this->shaft[1].vec.y = 0.0;
  this->shaft[1].vec.z = 1.0;
  this->limitAngles[2] = 0.0;
  this->limitAngles[1] = 0.0;
  this->limitAngles[0] = 0.0;
  this->limit = LIMIT_NONE;
  this->limitAxis.vec.x = 0.0;
  this->limitAxis.vec.y = 0.0;
  this->limitAxis.vec.z = -1.0;
}

// FUNC: public: static char const * __cdecl idDeclAF::ContentsToString(int,class idStr &)
char *__cdecl idDeclAF::ContentsToString(int contents, idStr *str)
{
  int len; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  char v6; // cl
  char *data; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  char v11; // cl
  char *v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  char v17; // cl
  char *v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // eax
  char v22; // cl
  char *v23; // eax
  int v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // eax
  char v28; // cl
  char *v29; // eax
  int v30; // edi
  int v31; // eax
  int v32; // eax
  char v33; // cl
  char *v34; // eax
  int v35; // eax
  int v36; // edi
  int v37; // eax
  int v38; // eax
  char v39; // cl
  char *v40; // eax
  int v41; // edi
  int v42; // eax
  int v43; // eax
  char v44; // cl
  char *v45; // edx
  char *v46; // eax
  int v47; // eax
  int v48; // edi
  int v49; // eax
  int v50; // eax
  char v51; // cl
  char *v52; // edx
  char *v53; // eax
  int v54; // edi
  int v55; // eax
  int v56; // eax
  char v57; // cl
  char *v58; // edx
  char *v59; // eax
  int v60; // eax
  int v61; // edi
  int v62; // eax
  int v63; // eax
  char v64; // cl
  char *v65; // edx
  char *v66; // eax
  int v67; // edi
  int v68; // eax
  int v69; // eax
  char v70; // cl
  char *v71; // edx
  char *v72; // eax
  int v73; // eax
  int v74; // edi
  int v75; // eax
  int v76; // eax
  char v77; // cl
  char *v78; // edx
  char *v79; // eax
  int v80; // edi
  int v81; // eax
  int v82; // eax
  char v83; // cl
  char *v84; // edx
  char *v85; // eax
  int v86; // eax
  int v87; // edi
  int v88; // eax
  int v89; // eax
  char v90; // cl
  char *v91; // edx
  char *v92; // eax
  int v93; // edi
  int v94; // eax
  int v95; // eax
  char v96; // cl
  char *v97; // edx
  char *v98; // eax

  idStr::operator=(str, (char *)&entityFilter);
  if ( (contents & 1) != 0 )
  {
    len = str->len;
    if ( str->len )
    {
      v3 = len + 2;
      v4 = len + 3;
      if ( v4 > str->alloced )
        idStr::ReAllocate(str, v4, 1);
      v5 = 0;
      v6 = 44;
      do
      {
        ++v5;
        str->data[str->len - 1 + v5] = v6;
        v6 = asc_1029E55C[v5];
      }
      while ( v6 );
      data = str->data;
      str->len = v3;
      data[v3] = 0;
    }
    v8 = str->len + 5;
    v9 = str->len + 6;
    if ( v9 > str->alloced )
      idStr::ReAllocate(str, v9, 1);
    v10 = 0;
    v11 = 115;
    do
    {
      ++v10;
      str->data[str->len - 1 + v10] = v11;
      v11 = aSolid[v10];
    }
    while ( v11 );
    v12 = str->data;
    str->len = v8;
    v12[v8] = 0;
  }
  if ( (contents & 0x100) != 0 )
  {
    v13 = str->len;
    if ( str->len )
    {
      v14 = v13 + 2;
      v15 = v13 + 3;
      if ( v15 > str->alloced )
        idStr::ReAllocate(str, v15, 1);
      v16 = 0;
      v17 = 44;
      do
      {
        ++v16;
        str->data[str->len - 1 + v16] = v17;
        v17 = asc_1029E55C[v16];
      }
      while ( v17 );
      v18 = str->data;
      str->len = v14;
      v18[v14] = 0;
    }
    v19 = str->len + 4;
    v20 = str->len + 5;
    if ( v20 > str->alloced )
      idStr::ReAllocate(str, v20, 1);
    v21 = 0;
    v22 = 98;
    do
    {
      ++v21;
      str->data[str->len - 1 + v21] = v22;
      v22 = aBody[v21];
    }
    while ( v22 );
    v23 = str->data;
    str->len = v19;
    v23[v19] = 0;
  }
  if ( (contents & 0x400) != 0 )
  {
    v24 = str->len;
    if ( str->len )
    {
      v25 = v24 + 2;
      v26 = v24 + 3;
      if ( v26 > str->alloced )
        idStr::ReAllocate(str, v26, 1);
      v27 = 0;
      v28 = 44;
      do
      {
        ++v27;
        str->data[str->len - 1 + v27] = v28;
        v28 = asc_1029E55C[v27];
      }
      while ( v28 );
      v29 = str->data;
      str->len = v25;
      v29[v25] = 0;
    }
    v30 = str->len + 6;
    v31 = str->len + 7;
    if ( v31 > str->alloced )
      idStr::ReAllocate(str, v31, 1);
    v32 = 0;
    v33 = 99;
    do
    {
      ++v32;
      str->data[str->len - 1 + v32] = v33;
      v33 = aCorpse[v32];
    }
    while ( v33 );
    v34 = str->data;
    str->len = v30;
    v34[v30] = 0;
  }
  if ( (contents & 8) != 0 )
  {
    v35 = str->len;
    if ( str->len )
    {
      v36 = v35 + 2;
      v37 = v35 + 3;
      if ( v37 > str->alloced )
        idStr::ReAllocate(str, v37, 1);
      v38 = 0;
      v39 = 44;
      do
      {
        ++v38;
        str->data[str->len - 1 + v38] = v39;
        v39 = asc_1029E55C[v38];
      }
      while ( v39 );
      v40 = str->data;
      str->len = v36;
      v40[v36] = 0;
    }
    v41 = str->len + 10;
    v42 = str->len + 11;
    if ( v42 > str->alloced )
      idStr::ReAllocate(str, v42, 1);
    v43 = 0;
    v44 = 112;
    do
    {
      v45 = &str->data[v43++];
      v45[str->len] = v44;
      v44 = aPlayerclip[v43];
    }
    while ( v44 );
    v46 = str->data;
    str->len = v41;
    v46[v41] = 0;
  }
  if ( (contents & 0x10) != 0 )
  {
    v47 = str->len;
    if ( str->len )
    {
      v48 = v47 + 2;
      v49 = v47 + 3;
      if ( v49 > str->alloced )
        idStr::ReAllocate(str, v49, 1);
      v50 = 0;
      v51 = 44;
      do
      {
        v52 = &str->data[v50++];
        v52[str->len] = v51;
        v51 = asc_1029E55C[v50];
      }
      while ( v51 );
      v53 = str->data;
      str->len = v48;
      v53[v48] = 0;
    }
    v54 = str->len + 11;
    v55 = str->len + 12;
    if ( v55 > str->alloced )
      idStr::ReAllocate(str, v55, 1);
    v56 = 0;
    v57 = 109;
    do
    {
      v58 = &str->data[v56++];
      v58[str->len] = v57;
      v57 = aMonsterclip[v56];
    }
    while ( v57 );
    v59 = str->data;
    str->len = v54;
    v59[v54] = 0;
  }
  if ( (contents & 0x80000) != 0 )
  {
    v60 = str->len;
    if ( str->len )
    {
      v61 = v60 + 2;
      v62 = v60 + 3;
      if ( v62 > str->alloced )
        idStr::ReAllocate(str, v62, 1);
      v63 = 0;
      v64 = 44;
      do
      {
        v65 = &str->data[v63++];
        v65[str->len] = v64;
        v64 = asc_1029E55C[v63];
      }
      while ( v64 );
      v66 = str->data;
      str->len = v61;
      v66[v61] = 0;
    }
    v67 = str->len + 11;
    v68 = str->len + 12;
    if ( v68 > str->alloced )
      idStr::ReAllocate(str, v68, 1);
    v69 = 0;
    v70 = 118;
    do
    {
      v71 = &str->data[v69++];
      v71[str->len] = v70;
      v70 = aVehicleclip[v69];
    }
    while ( v70 );
    v72 = str->data;
    str->len = v67;
    v72[v67] = 0;
  }
  if ( (contents & 0x400000) != 0 )
  {
    v73 = str->len;
    if ( str->len )
    {
      v74 = v73 + 2;
      v75 = v73 + 3;
      if ( v75 > str->alloced )
        idStr::ReAllocate(str, v75, 1);
      v76 = 0;
      v77 = 44;
      do
      {
        v78 = &str->data[v76++];
        v78[str->len] = v77;
        v77 = asc_1029E55C[v76];
      }
      while ( v77 );
      v79 = str->data;
      str->len = v74;
      v79[v74] = 0;
    }
    v80 = str->len + 7;
    v81 = str->len + 8;
    if ( v81 > str->alloced )
      idStr::ReAllocate(str, v81, 1);
    v82 = 0;
    v83 = 102;
    do
    {
      v84 = &str->data[v82++];
      v84[str->len] = v83;
      v83 = aFlyclip[v82];
    }
    while ( v83 );
    v85 = str->data;
    str->len = v80;
    v85[v80] = 0;
  }
  if ( (contents & 0x800000) != 0 )
  {
    v86 = str->len;
    if ( str->len )
    {
      v87 = v86 + 2;
      v88 = v86 + 3;
      if ( v88 > str->alloced )
        idStr::ReAllocate(str, v88, 1);
      v89 = 0;
      v90 = 44;
      do
      {
        v91 = &str->data[v89++];
        v91[str->len] = v90;
        v90 = asc_1029E55C[v89];
      }
      while ( v90 );
      v92 = str->data;
      str->len = v87;
      v92[v87] = 0;
    }
    v93 = str->len + 8;
    v94 = str->len + 9;
    if ( v94 > str->alloced )
      idStr::ReAllocate(str, v94, 1);
    v95 = 0;
    v96 = 105;
    do
    {
      v97 = &str->data[v95++];
      v97[str->len] = v96;
      v96 = aItemclip[v95];
    }
    while ( v96 );
    v98 = str->data;
    str->len = v93;
    v98[v93] = 0;
  }
  if ( !*str->data )
    idStr::operator=(str, "none");
  return str->data;
}

// FUNC: private: bool __thiscall idDeclAF::ParseBody(class idLexer &)
char __thiscall idDeclAF::ParseBody(idDeclAF *this, idLexer *src)
{
  idDeclAF_Body *v3; // eax
  int v4; // eax
  int v5; // ebx
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Body **list; // ebp
  int j; // eax
  int v14; // eax
  idDeclAF_Body **v15; // ecx
  bool v16; // zf
  idAFVector *v17; // ecx
  double y; // st7
  double z; // st6
  const char *v21; // [esp-10h] [ebp-D4h]
  bool hasJoint; // [esp+Bh] [ebp-B9h]
  int len; // [esp+Ch] [ebp-B8h]
  int v24; // [esp+Ch] [ebp-B8h]
  int v25; // [esp+Ch] [ebp-B8h]
  idToken token; // [esp+10h] [ebp-B4h] BYREF
  idDeclAF *v27; // [esp+60h] [ebp-64h]
  idAFVector angles; // [esp+64h] [ebp-60h] BYREF
  int v29; // [esp+C0h] [ebp-4h]

  token.floatvalue = 0.0;
  v27 = this;
  hasJoint = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  angles.joint1.alloced = 20;
  angles.joint2.alloced = 20;
  v29 = 1;
  angles.joint1.len = 0;
  angles.joint1.data = angles.joint1.baseBuffer;
  angles.joint1.baseBuffer[0] = 0;
  angles.joint2.len = 0;
  angles.joint2.data = angles.joint2.baseBuffer;
  angles.joint2.baseBuffer[0] = 0;
  angles.type = VEC_COORDS;
  memset(&angles.vec, 0, 13);
  v3 = (idDeclAF_Body *)Memory::Allocate(0x260u);
  if ( v3 )
  {
    idDeclAF_Body::idDeclAF_Body(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  if ( !this->bodies.list )
  {
    granularity = this->bodies.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->bodies.size )
      {
        v7 = granularity < this->bodies.num;
        this->bodies.size = granularity;
        if ( v7 )
          this->bodies.num = granularity;
        this->bodies.list = (idDeclAF_Body **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->bodies.num; ++i )
          this->bodies.list[i] = *(idDeclAF_Body **)(4 * i);
      }
    }
    else
    {
      this->bodies.list = 0;
      this->bodies.num = 0;
      this->bodies.size = 0;
    }
  }
  num = this->bodies.num;
  size = this->bodies.size;
  if ( num == size )
  {
    v11 = size + this->bodies.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->bodies.size )
      {
        list = this->bodies.list;
        this->bodies.size = v11;
        if ( v11 < num )
          this->bodies.num = v11;
        this->bodies.list = (idDeclAF_Body **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->bodies.num; ++j )
          this->bodies.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->bodies.list )
        Memory::Free(this->bodies.list);
      this->bodies.list = 0;
      this->bodies.num = 0;
      this->bodies.size = 0;
    }
  }
  v14 = this->bodies.num;
  v15 = &this->bodies.list[v14];
  this->bodies.num = v14 + 1;
  *v15 = (idDeclAF_Body *)v5;
  idDeclAF_Body::SetDefault((idDeclAF_Body *)v5, this);
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
    goto LABEL_120;
  len = token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *(_BYTE *)(len + *(_DWORD *)(v5 + 4)) = 0;
  v21 = *(const char **)(v5 + 4);
  *(_DWORD *)v5 = len;
  if ( !idStr::Icmp(v21, "origin") || !idStr::Icmp(*(const char **)(v5 + 4), "world") )
  {
    idLexer::Error(src, "a body may not be named \"origin\" or \"world\"");
    goto LABEL_120;
  }
  if ( !idLexer::ReadToken(src, &token) )
  {
LABEL_109:
    if ( !*(_DWORD *)(v5 + 68) )
    {
      idLexer::Error(src, "no model set for body");
      goto LABEL_120;
    }
    if ( !hasJoint )
    {
      idLexer::Error(src, "no joint set for body");
      goto LABEL_120;
    }
    *(_DWORD *)(v5 + 352) |= 0x20u;
    LOBYTE(v29) = 0;
    idAFVector::~idAFVector(&angles);
    v29 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "model") )
    {
      if ( !idLexer::ExpectTokenType(src, 4, 0, &token) )
        goto LABEL_120;
      if ( idStr::Icmp(token.data, "box") )
      {
        if ( idStr::Icmp(token.data, "octahedron") )
        {
          if ( idStr::Icmp(token.data, "dodecahedron") )
          {
            if ( idStr::Icmp(token.data, "cylinder") )
            {
              if ( idStr::Icmp(token.data, "cone") )
              {
                if ( idStr::Icmp(token.data, "bone") )
                {
                  if ( idStr::Icmp(token.data, "custom") )
                    idLexer::Error(src, "unkown model type %s", token.data);
                  else
                    idLexer::Error(src, "custom models not yet implemented");
                  goto LABEL_120;
                }
                *(_DWORD *)(v5 + 68) = 6;
                if ( !idLexer::ExpectTokenString(src, "(")
                  || !idAFVector::Parse((idAFVector *)(v5 + 72), src)
                  || !idLexer::ExpectTokenString(src, ",")
                  || !idAFVector::Parse((idAFVector *)(v5 + 156), src)
                  || !idLexer::ExpectTokenString(src, ",") )
                {
                  goto LABEL_120;
                }
                *(float *)(v5 + 244) = idLexer::ParseFloat(src, 0);
                v16 = idLexer::ExpectTokenString(src, ")") == 0;
                goto LABEL_107;
              }
              *(_DWORD *)(v5 + 68) = 5;
              if ( !idLexer::ExpectTokenString(src, "(")
                || !idAFVector::Parse((idAFVector *)(v5 + 72), src)
                || !idLexer::ExpectTokenString(src, ",")
                || !idAFVector::Parse((idAFVector *)(v5 + 156), src)
                || !idLexer::ExpectTokenString(src, ",") )
              {
                goto LABEL_120;
              }
            }
            else
            {
              *(_DWORD *)(v5 + 68) = 4;
              if ( !idLexer::ExpectTokenString(src, "(")
                || !idAFVector::Parse((idAFVector *)(v5 + 72), src)
                || !idLexer::ExpectTokenString(src, ",")
                || !idAFVector::Parse((idAFVector *)(v5 + 156), src)
                || !idLexer::ExpectTokenString(src, ",") )
              {
                goto LABEL_120;
              }
            }
            *(_DWORD *)(v5 + 240) = idLexer::ParseInt(src);
            v16 = idLexer::ExpectTokenString(src, ")") == 0;
LABEL_107:
            if ( v16 )
              goto LABEL_120;
            goto LABEL_108;
          }
          *(_DWORD *)(v5 + 68) = 3;
          if ( !idLexer::ExpectTokenString(src, "(")
            || !idAFVector::Parse((idAFVector *)(v5 + 72), src)
            || !idLexer::ExpectTokenString(src, ",")
            || !idAFVector::Parse((idAFVector *)(v5 + 156), src) )
          {
            goto LABEL_120;
          }
        }
        else
        {
          *(_DWORD *)(v5 + 68) = 2;
          if ( !idLexer::ExpectTokenString(src, "(")
            || !idAFVector::Parse((idAFVector *)(v5 + 72), src)
            || !idLexer::ExpectTokenString(src, ",")
            || !idAFVector::Parse((idAFVector *)(v5 + 156), src) )
          {
            goto LABEL_120;
          }
        }
      }
      else
      {
        *(_DWORD *)(v5 + 68) = 1;
        if ( !idLexer::ExpectTokenString(src, "(")
          || !idAFVector::Parse((idAFVector *)(v5 + 72), src)
          || !idLexer::ExpectTokenString(src, ",")
          || !idAFVector::Parse((idAFVector *)(v5 + 156), src) )
        {
          goto LABEL_120;
        }
      }
      v16 = idLexer::ExpectTokenString(src, ")") == 0;
      goto LABEL_107;
    }
    if ( !idStr::Icmp(token.data, "origin") )
    {
      v17 = (idAFVector *)(v5 + 252);
      goto LABEL_106;
    }
    if ( !idStr::Icmp(token.data, "angles") )
    {
      if ( !idAFVector::Parse(&angles, src) )
        goto LABEL_120;
      y = angles.vec.y;
      z = angles.vec.z;
      *(float *)(v5 + 336) = angles.vec.x;
      *(float *)(v5 + 340) = y;
      *(float *)(v5 + 344) = z;
      goto LABEL_108;
    }
    if ( !idStr::Icmp(token.data, "joint") )
    {
      if ( !idLexer::ExpectTokenType(src, 1, 0, &token) )
        goto LABEL_120;
      v24 = token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 40) )
        idStr::ReAllocate((idStr *)(v5 + 32), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 36), token.data, v24);
      *(_BYTE *)(v24 + *(_DWORD *)(v5 + 36)) = 0;
      *(_DWORD *)(v5 + 32) = v24;
      hasJoint = 1;
      goto LABEL_108;
    }
    if ( !idStr::Icmp(token.data, "mod") )
    {
      if ( !idLexer::ExpectAnyToken(src, &token) )
        goto LABEL_120;
      *(_DWORD *)(v5 + 64) = idDeclAF::JointModFromString(token.data);
      goto LABEL_108;
    }
    if ( idStr::Icmp(token.data, "density") )
      break;
    *(float *)(v5 + 248) = idLexer::ParseFloat(src, 0);
LABEL_108:
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_109;
  }
  if ( !idStr::Icmp(token.data, "inertiaScale") )
  {
    idLexer::Parse1DMatrix(src, 9, (float *)(v5 + 360));
    goto LABEL_108;
  }
  if ( !idStr::Icmp(token.data, "friction") )
  {
    *(float *)(v5 + 396) = idLexer::ParseFloat(src, 0);
    idLexer::ExpectTokenString(src, ",");
    *(float *)(v5 + 400) = idLexer::ParseFloat(src, 0);
    idLexer::ExpectTokenString(src, ",");
    *(float *)(v5 + 404) = idLexer::ParseFloat(src, 0);
    goto LABEL_108;
  }
  if ( !idStr::Icmp(token.data, "contents") )
  {
    idDeclAF::ParseContents(v27, src, (int *)(v5 + 348));
    goto LABEL_108;
  }
  if ( !idStr::Icmp(token.data, "clipMask") )
  {
    idDeclAF::ParseContents(v27, src, (int *)(v5 + 352));
    goto LABEL_108;
  }
  if ( !idStr::Icmp(token.data, "selfCollision") )
  {
    *(_BYTE *)(v5 + 356) = idLexer::ParseBool(src);
    goto LABEL_108;
  }
  if ( !idStr::Icmp(token.data, "containedjoints") )
  {
    if ( !idLexer::ExpectTokenType(src, 1, 0, &token) )
      goto LABEL_120;
    v25 = token.len;
    if ( token.len + 1 > *(_DWORD *)(v5 + 416) )
      idStr::ReAllocate((idStr *)(v5 + 408), token.len + 1, 0);
    qmemcpy(*(void **)(v5 + 412), token.data, v25);
    *(_BYTE *)(v25 + *(_DWORD *)(v5 + 412)) = 0;
    *(_DWORD *)(v5 + 408) = v25;
    goto LABEL_108;
  }
  if ( !idStr::Icmp(token.data, "frictionDirection") )
  {
    v17 = (idAFVector *)(v5 + 440);
    goto LABEL_106;
  }
  if ( !idStr::Icmp(token.data, "contactMotorDirection") )
  {
    v17 = (idAFVector *)(v5 + 524);
LABEL_106:
    v16 = !idAFVector::Parse(v17, src);
    goto LABEL_107;
  }
  if ( !idStr::Cmp(token.data, "}") )
    goto LABEL_109;
  idLexer::Error(src, "unknown token %s in body", token.data);
LABEL_120:
  LOBYTE(v29) = 0;
  idAFVector::~idAFVector(&angles);
  v29 = -1;
  idStr::FreeData(&token);
  return 0;
}

// FUNC: private: bool __thiscall idDeclAF::ParseFixed(class idLexer &)
char __thiscall idDeclAF::ParseFixed(idDeclAF *this, idLexer *src)
{
  idDeclAF_Constraint *v3; // eax
  int v4; // eax
  int v5; // ebp
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Constraint **list; // ebx
  int j; // eax
  int v14; // eax
  idLexer *v15; // ebx
  idDeclAF_Constraint **v16; // ecx
  int len; // esi
  int v19; // ebx
  idStr *v20; // ebp
  int v21; // [esp+8h] [ebp-64h]
  int v22; // [esp+Ch] [ebp-60h]
  idToken token; // [esp+10h] [ebp-5Ch] BYREF
  int v24; // [esp+68h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v24 = 0;
  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  LOBYTE(v24) = 1;
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v5 = v4;
    v21 = v4;
  }
  else
  {
    v21 = 0;
    v5 = 0;
  }
  LOBYTE(v24) = 0;
  idDeclAF_Constraint::SetDefault((idDeclAF_Constraint *)v5, this);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v7 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v7 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    v11 = size + this->constraints.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v11;
        if ( v11 < num )
          this->constraints.num = v11;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  v14 = this->constraints.num;
  v15 = src;
  v16 = &this->constraints.list[v14];
  this->constraints.num = v14 + 1;
  *v16 = (idDeclAF_Constraint *)v5;
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_42:
    v24 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  *(_DWORD *)(v5 + 96) = 1;
  len = token.len;
  v22 = token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *(_BYTE *)(v22 + *(_DWORD *)(v5 + 4)) = 0;
  *(_DWORD *)v5 = v22;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_29;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "body1") )
    {
      idLexer::ExpectTokenType(v15, 1, 0, &token);
      v19 = token.len;
      v20 = (idStr *)(v5 + 32);
      if ( token.len + 1 > v20->alloced )
        idStr::ReAllocate(v20, token.len + 1, 0);
      goto LABEL_38;
    }
    if ( idStr::Icmp(token.data, "body2") )
      break;
    idLexer::ExpectTokenType(v15, 1, 0, &token);
    v19 = token.len;
    v20 = (idStr *)(v5 + 64);
    if ( token.len + 1 > v20->alloced )
      idStr::ReAllocate(v20, token.len + 1, 0);
LABEL_38:
    qmemcpy(v20->data, token.data, v19);
    v20->data[v19] = 0;
    v20->len = v19;
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_29;
    v15 = src;
    v5 = v21;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(v15, "unknown token %s in ball and socket joint", token.data);
    goto LABEL_42;
  }
LABEL_29:
  v24 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idDeclAF::ParseBallAndSocketJoint(class idLexer &)
char __thiscall idDeclAF::ParseBallAndSocketJoint(idDeclAF *this, idLexer *src)
{
  idDeclAF_Constraint *v3; // eax
  int v4; // eax
  int v5; // ebp
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Constraint **list; // ebx
  int j; // eax
  int v14; // eax
  idDeclAF_Constraint **v16; // ecx
  int len; // esi
  int v18; // esi
  int v19; // esi
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v22; // [esp+64h] [ebp-4h]
  idLexer *srca; // [esp+6Ch] [ebp+4h]
  idLexer *srcb; // [esp+6Ch] [ebp+4h]
  idLexer *srcc; // [esp+6Ch] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v22 = 0;
  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  LOBYTE(v22) = 1;
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v22) = 0;
  idDeclAF_Constraint::SetDefault((idDeclAF_Constraint *)v5, this);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v7 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v7 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    v11 = size + this->constraints.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v11;
        if ( v11 < num )
          this->constraints.num = v11;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  v14 = this->constraints.num;
  v16 = &this->constraints.list[v14];
  this->constraints.num = v14 + 1;
  *v16 = (idDeclAF_Constraint *)v5;
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_39:
    v22 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  *(_DWORD *)(v5 + 96) = 2;
  *(_DWORD *)(v5 + 548) = -1;
  len = token.len;
  srca = (idLexer *)token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *((_BYTE *)&srca->loaded + *(_DWORD *)(v5 + 4)) = 0;
  *(_DWORD *)v5 = srca;
  *(_DWORD *)(v5 + 100) = 1056964608;
  *(_DWORD *)(v5 + 204) = 0;
  *(_DWORD *)(v5 + 200) = 0;
  *(_DWORD *)(v5 + 196) = 0;
  *(_DWORD *)(v5 + 372) = 0;
  *(_DWORD *)(v5 + 368) = 0;
  *(_DWORD *)(v5 + 364) = 0;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_57;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "body1") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v18 = token.len;
      srcb = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 40) )
        idStr::ReAllocate((idStr *)(v5 + 32), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 36), token.data, v18);
      *((_BYTE *)&srcb->loaded + *(_DWORD *)(v5 + 36)) = 0;
      *(_DWORD *)(v5 + 32) = srcb;
      goto LABEL_56;
    }
    if ( !idStr::Icmp(token.data, "body2") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v19 = token.len;
      srcc = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 72) )
        idStr::ReAllocate((idStr *)(v5 + 64), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 68), token.data, v19);
      *((_BYTE *)&srcc->loaded + *(_DWORD *)(v5 + 68)) = 0;
      *(_DWORD *)(v5 + 64) = srcc;
      goto LABEL_56;
    }
    if ( !idStr::Icmp(token.data, "anchor") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 128), src) )
        goto LABEL_39;
      goto LABEL_56;
    }
    if ( !idStr::Icmp(token.data, "conelimit") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 552), src) )
        goto LABEL_39;
      if ( !idLexer::ExpectTokenString(src, ",") )
        goto LABEL_39;
      *(float *)(v5 + 636) = idLexer::ParseFloat(src, 0);
      if ( !idLexer::ExpectTokenString(src, ",") || !idAFVector::Parse((idAFVector *)(v5 + 296), src) )
        goto LABEL_39;
      *(_DWORD *)(v5 + 548) = 0;
      goto LABEL_56;
    }
    if ( idStr::Icmp(token.data, "pyramidlimit") )
      break;
    if ( !idAFVector::Parse((idAFVector *)(v5 + 552), src) )
      goto LABEL_39;
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 636) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 640) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 644) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") || !idAFVector::Parse((idAFVector *)(v5 + 296), src) )
      goto LABEL_39;
    *(_DWORD *)(v5 + 548) = 1;
LABEL_56:
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_57;
  }
  if ( !idStr::Icmp(token.data, "friction") )
  {
    *(float *)(v5 + 100) = idLexer::ParseFloat(src, 0);
    goto LABEL_56;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(src, "unknown token %s in ball and socket joint", token.data);
    goto LABEL_39;
  }
LABEL_57:
  v22 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idDeclAF::ParseUniversalJoint(class idLexer &)
char __thiscall idDeclAF::ParseUniversalJoint(idDeclAF *this, idLexer *src)
{
  idDeclAF_Constraint *v3; // eax
  int v4; // eax
  int v5; // ebp
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Constraint **list; // ebx
  int j; // eax
  int v14; // eax
  idDeclAF_Constraint **v16; // ecx
  int len; // esi
  int v18; // esi
  int v19; // esi
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v22; // [esp+64h] [ebp-4h]
  idLexer *srca; // [esp+6Ch] [ebp+4h]
  idLexer *srcb; // [esp+6Ch] [ebp+4h]
  idLexer *srcc; // [esp+6Ch] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v22 = 0;
  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  LOBYTE(v22) = 1;
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v22) = 0;
  idDeclAF_Constraint::SetDefault((idDeclAF_Constraint *)v5, this);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v7 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v7 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    v11 = size + this->constraints.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v11;
        if ( v11 < num )
          this->constraints.num = v11;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  v14 = this->constraints.num;
  v16 = &this->constraints.list[v14];
  this->constraints.num = v14 + 1;
  *v16 = (idDeclAF_Constraint *)v5;
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_39:
    v22 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  *(_DWORD *)(v5 + 96) = 3;
  *(_DWORD *)(v5 + 548) = -1;
  len = token.len;
  srca = (idLexer *)token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *((_BYTE *)&srca->loaded + *(_DWORD *)(v5 + 4)) = 0;
  *(_DWORD *)v5 = srca;
  *(_DWORD *)(v5 + 100) = 1056964608;
  *(_DWORD *)(v5 + 204) = 0;
  *(_DWORD *)(v5 + 200) = 0;
  *(_DWORD *)(v5 + 196) = 0;
  *(_DWORD *)(v5 + 372) = 0;
  *(_DWORD *)(v5 + 368) = 0;
  *(_DWORD *)(v5 + 364) = 0;
  *(_DWORD *)(v5 + 456) = 0;
  *(_DWORD *)(v5 + 452) = 0;
  *(_DWORD *)(v5 + 448) = 0;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_58;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "body1") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v18 = token.len;
      srcb = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 40) )
        idStr::ReAllocate((idStr *)(v5 + 32), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 36), token.data, v18);
      *((_BYTE *)&srcb->loaded + *(_DWORD *)(v5 + 36)) = 0;
      *(_DWORD *)(v5 + 32) = srcb;
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "body2") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v19 = token.len;
      srcc = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 72) )
        idStr::ReAllocate((idStr *)(v5 + 64), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 68), token.data, v19);
      *((_BYTE *)&srcc->loaded + *(_DWORD *)(v5 + 68)) = 0;
      *(_DWORD *)(v5 + 64) = srcc;
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "anchor") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 128), src) )
        goto LABEL_39;
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "shafts") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 296), src)
        || !idLexer::ExpectTokenString(src, ",")
        || !idAFVector::Parse((idAFVector *)(v5 + 380), src) )
      {
        goto LABEL_39;
      }
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "conelimit") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 552), src) || !idLexer::ExpectTokenString(src, ",") )
        goto LABEL_39;
      *(float *)(v5 + 636) = idLexer::ParseFloat(src, 0);
      *(_DWORD *)(v5 + 548) = 0;
      goto LABEL_57;
    }
    if ( idStr::Icmp(token.data, "pyramidlimit") )
      break;
    if ( !idAFVector::Parse((idAFVector *)(v5 + 552), src) )
      goto LABEL_39;
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 636) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 640) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 644) = idLexer::ParseFloat(src, 0);
    *(_DWORD *)(v5 + 548) = 1;
LABEL_57:
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_58;
  }
  if ( !idStr::Icmp(token.data, "friction") )
  {
    *(float *)(v5 + 100) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(src, "unknown token %s in universal joint", token.data);
    goto LABEL_39;
  }
LABEL_58:
  v22 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idDeclAF::ParseHinge(class idLexer &)
char __thiscall idDeclAF::ParseHinge(idDeclAF *this, idLexer *src)
{
  idDeclAF_Constraint *v3; // eax
  int v4; // eax
  int v5; // ebp
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Constraint **list; // ebx
  int j; // eax
  int v14; // eax
  idDeclAF_Constraint **v16; // ecx
  int len; // esi
  int v18; // esi
  int v19; // esi
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v22; // [esp+64h] [ebp-4h]
  idLexer *srca; // [esp+6Ch] [ebp+4h]
  idLexer *srcb; // [esp+6Ch] [ebp+4h]
  idLexer *srcc; // [esp+6Ch] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v22 = 0;
  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  LOBYTE(v22) = 1;
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v22) = 0;
  idDeclAF_Constraint::SetDefault((idDeclAF_Constraint *)v5, this);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v7 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v7 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    v11 = size + this->constraints.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v11;
        if ( v11 < num )
          this->constraints.num = v11;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  v14 = this->constraints.num;
  v16 = &this->constraints.list[v14];
  this->constraints.num = v14 + 1;
  *v16 = (idDeclAF_Constraint *)v5;
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_39:
    v22 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  *(_DWORD *)(v5 + 96) = 4;
  *(_DWORD *)(v5 + 548) = -1;
  len = token.len;
  srca = (idLexer *)token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *((_BYTE *)&srca->loaded + *(_DWORD *)(v5 + 4)) = 0;
  *(_DWORD *)v5 = srca;
  *(_DWORD *)(v5 + 100) = 1056964608;
  *(_DWORD *)(v5 + 204) = 0;
  *(_DWORD *)(v5 + 200) = 0;
  *(_DWORD *)(v5 + 196) = 0;
  *(_DWORD *)(v5 + 540) = 0;
  *(_DWORD *)(v5 + 536) = 0;
  *(_DWORD *)(v5 + 532) = 0;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_50;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "body1") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v18 = token.len;
      srcb = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 40) )
        idStr::ReAllocate((idStr *)(v5 + 32), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 36), token.data, v18);
      *((_BYTE *)&srcb->loaded + *(_DWORD *)(v5 + 36)) = 0;
      *(_DWORD *)(v5 + 32) = srcb;
      goto LABEL_49;
    }
    if ( !idStr::Icmp(token.data, "body2") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v19 = token.len;
      srcc = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 72) )
        idStr::ReAllocate((idStr *)(v5 + 64), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 68), token.data, v19);
      *((_BYTE *)&srcc->loaded + *(_DWORD *)(v5 + 68)) = 0;
      *(_DWORD *)(v5 + 64) = srcc;
      goto LABEL_49;
    }
    if ( !idStr::Icmp(token.data, "anchor") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 128), src) )
        goto LABEL_39;
      goto LABEL_49;
    }
    if ( !idStr::Icmp(token.data, "axis") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 464), src) )
        goto LABEL_39;
      goto LABEL_49;
    }
    if ( idStr::Icmp(token.data, "limit") )
      break;
    *(float *)(v5 + 636) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 640) = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_39;
    *(float *)(v5 + 644) = idLexer::ParseFloat(src, 0);
    *(_DWORD *)(v5 + 548) = 0;
LABEL_49:
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_50;
  }
  if ( !idStr::Icmp(token.data, "friction") )
  {
    *(float *)(v5 + 100) = idLexer::ParseFloat(src, 0);
    goto LABEL_49;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(src, "unknown token %s in hinge", token.data);
    goto LABEL_39;
  }
LABEL_50:
  v22 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idDeclAF::ParseSlider(class idLexer &)
char __thiscall idDeclAF::ParseSlider(idDeclAF *this, idLexer *src)
{
  idDeclAF_Constraint *v3; // eax
  int v4; // eax
  int v5; // ebx
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Constraint **list; // ebp
  int j; // eax
  int v14; // eax
  idLexer *v15; // ebp
  idDeclAF_Constraint **v16; // ecx
  int len; // esi
  int v18; // esi
  int v19; // ebp
  int v21; // [esp+8h] [ebp-60h]
  int v22; // [esp+8h] [ebp-60h]
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v24; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v24 = 0;
  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  LOBYTE(v24) = 1;
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v24) = 0;
  idDeclAF_Constraint::SetDefault((idDeclAF_Constraint *)v5, this);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v7 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v7 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    v11 = size + this->constraints.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v11;
        if ( v11 < num )
          this->constraints.num = v11;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  v14 = this->constraints.num;
  v15 = src;
  v16 = &this->constraints.list[v14];
  this->constraints.num = v14 + 1;
  *v16 = (idDeclAF_Constraint *)v5;
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_38:
    v24 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  *(_DWORD *)(v5 + 96) = 5;
  *(_DWORD *)(v5 + 548) = -1;
  len = token.len;
  v21 = token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *(_BYTE *)(v21 + *(_DWORD *)(v5 + 4)) = 0;
  *(_DWORD *)v5 = v21;
  *(_DWORD *)(v5 + 100) = 1056964608;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_42;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "body1") )
    {
      idLexer::ExpectTokenType(v15, 1, 0, &token);
      v18 = token.len;
      v19 = v5 + 32;
      v22 = token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 40) )
        idStr::ReAllocate((idStr *)(v5 + 32), token.len + 1, 0);
      goto LABEL_32;
    }
    if ( idStr::Icmp(token.data, "body2") )
      break;
    idLexer::ExpectTokenType(v15, 1, 0, &token);
    v18 = token.len;
    v19 = v5 + 64;
    v22 = token.len;
    if ( token.len + 1 > *(_DWORD *)(v5 + 72) )
    {
      idStr::ReAllocate((idStr *)(v5 + 64), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 68), token.data, v18);
      *(_BYTE *)(v18 + *(_DWORD *)(v5 + 68)) = 0;
      *(_DWORD *)v19 = v18;
      v15 = src;
      goto LABEL_41;
    }
LABEL_32:
    qmemcpy(*(void **)(v19 + 4), token.data, v18);
    *(_BYTE *)(v22 + *(_DWORD *)(v19 + 4)) = 0;
    *(_DWORD *)v19 = v22;
    v15 = src;
LABEL_41:
    if ( !idLexer::ReadToken(v15, &token) )
      goto LABEL_42;
  }
  if ( !idStr::Icmp(token.data, "axis") )
  {
    if ( !idAFVector::Parse((idAFVector *)(v5 + 464), v15) )
      goto LABEL_38;
    goto LABEL_41;
  }
  if ( !idStr::Icmp(token.data, "friction") )
  {
    *(float *)(v5 + 100) = idLexer::ParseFloat(v15, 0);
    goto LABEL_41;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(v15, "unknown token %s in slider", token.data);
    goto LABEL_38;
  }
LABEL_42:
  v24 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idDeclAF::ParseSpring(class idLexer &)
char __thiscall idDeclAF::ParseSpring(idDeclAF *this, idLexer *src)
{
  idDeclAF_Constraint *v3; // eax
  int v4; // eax
  int v5; // ebp
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int num; // edx
  int size; // ecx
  int v11; // eax
  idDeclAF_Constraint **list; // ebx
  int j; // eax
  int v14; // eax
  idDeclAF_Constraint **v16; // ecx
  int len; // esi
  int v18; // esi
  int v19; // esi
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v22; // [esp+64h] [ebp-4h]
  idLexer *srca; // [esp+6Ch] [ebp+4h]
  idLexer *srcb; // [esp+6Ch] [ebp+4h]
  idLexer *srcc; // [esp+6Ch] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v22 = 0;
  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  LOBYTE(v22) = 1;
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v22) = 0;
  idDeclAF_Constraint::SetDefault((idDeclAF_Constraint *)v5, this);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v7 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v7 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    v11 = size + this->constraints.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v11;
        if ( v11 < num )
          this->constraints.num = v11;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v11);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  v14 = this->constraints.num;
  v16 = &this->constraints.list[v14];
  this->constraints.num = v14 + 1;
  *v16 = (idDeclAF_Constraint *)v5;
  if ( !idLexer::ExpectTokenType(src, 1, 0, &token) || !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_39:
    v22 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  *(_DWORD *)(v5 + 96) = 6;
  *(_DWORD *)(v5 + 548) = -1;
  len = token.len;
  srca = (idLexer *)token.len;
  if ( token.len + 1 > *(_DWORD *)(v5 + 8) )
    idStr::ReAllocate((idStr *)v5, token.len + 1, 0);
  qmemcpy(*(void **)(v5 + 4), token.data, len);
  *((_BYTE *)&srca->loaded + *(_DWORD *)(v5 + 4)) = 0;
  *(_DWORD *)v5 = srca;
  *(_DWORD *)(v5 + 100) = 1056964608;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_58;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "body1") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v18 = token.len;
      srcb = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 40) )
        idStr::ReAllocate((idStr *)(v5 + 32), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 36), token.data, v18);
      *((_BYTE *)&srcb->loaded + *(_DWORD *)(v5 + 36)) = 0;
      *(_DWORD *)(v5 + 32) = srcb;
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "body2") )
    {
      idLexer::ExpectTokenType(src, 1, 0, &token);
      v19 = token.len;
      srcc = (idLexer *)token.len;
      if ( token.len + 1 > *(_DWORD *)(v5 + 72) )
        idStr::ReAllocate((idStr *)(v5 + 64), token.len + 1, 0);
      qmemcpy(*(void **)(v5 + 68), token.data, v19);
      *((_BYTE *)&srcc->loaded + *(_DWORD *)(v5 + 68)) = 0;
      *(_DWORD *)(v5 + 64) = srcc;
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "anchor1") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 128), src) )
        goto LABEL_39;
      goto LABEL_57;
    }
    if ( !idStr::Icmp(token.data, "anchor2") )
    {
      if ( !idAFVector::Parse((idAFVector *)(v5 + 212), src) )
        goto LABEL_39;
      goto LABEL_57;
    }
    if ( idStr::Icmp(token.data, "friction") )
      break;
    *(float *)(v5 + 100) = idLexer::ParseFloat(src, 0);
LABEL_57:
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_58;
  }
  if ( !idStr::Icmp(token.data, "stretch") )
  {
    *(float *)(v5 + 104) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( !idStr::Icmp(token.data, "compress") )
  {
    *(float *)(v5 + 108) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( !idStr::Icmp(token.data, "damping") )
  {
    *(float *)(v5 + 112) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( !idStr::Icmp(token.data, "restLength") )
  {
    *(float *)(v5 + 116) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( !idStr::Icmp(token.data, "minLength") )
  {
    *(float *)(v5 + 120) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( !idStr::Icmp(token.data, "maxLength") )
  {
    *(float *)(v5 + 124) = idLexer::ParseFloat(src, 0);
    goto LABEL_57;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(src, "unknown token %s in spring", token.data);
    goto LABEL_39;
  }
LABEL_58:
  v22 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idDeclAF::ParseSettings(class idLexer &)
char __thiscall idDeclAF::ParseSettings(idDeclAF *this, idLexer *src)
{
  int len; // esi
  int v5; // esi
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v8; // [esp+5Ch] [ebp-4h]
  int srca; // [esp+64h] [ebp+4h]
  int srcb; // [esp+64h] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 0;
  if ( !idLexer::ExpectTokenString(src, "{") )
  {
LABEL_51:
    v8 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  this->fastEval = 0;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_48;
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "mesh") || !idStr::Icmp(token.data, "anim") )
    {
      if ( !idLexer::ExpectTokenType(src, 1, 0, &token) )
        goto LABEL_51;
      goto LABEL_47;
    }
    if ( !idStr::Icmp(token.data, "model") )
    {
      if ( !idLexer::ExpectTokenType(src, 1, 0, &token) )
        goto LABEL_51;
      len = token.len;
      srca = token.len;
      if ( token.len + 1 > this->model.alloced )
        idStr::ReAllocate(&this->model, token.len + 1, 0);
      qmemcpy(this->model.data, token.data, len);
      this->model.data[srca] = 0;
      this->model.len = srca;
      goto LABEL_47;
    }
    if ( !idStr::Icmp(token.data, "skin") )
    {
      if ( !idLexer::ExpectTokenType(src, 1, 0, &token) )
        goto LABEL_51;
      v5 = token.len;
      srcb = token.len;
      if ( token.len + 1 > this->skin.alloced )
        idStr::ReAllocate(&this->skin, token.len + 1, 0);
      qmemcpy(this->skin.data, token.data, v5);
      this->skin.data[srcb] = 0;
      this->skin.len = srcb;
      goto LABEL_47;
    }
    if ( !idStr::Icmp(token.data, "friction") )
    {
      this->defaultLinearFriction = idLexer::ParseFloat(src, 0);
      if ( !idLexer::ExpectTokenString(src, ",") )
        goto LABEL_51;
      this->defaultAngularFriction = idLexer::ParseFloat(src, 0);
      if ( !idLexer::ExpectTokenString(src, ",") )
        goto LABEL_51;
      this->defaultContactFriction = idLexer::ParseFloat(src, 0);
      if ( idLexer::CheckTokenString(src, ",") )
        this->defaultConstraintFriction = idLexer::ParseFloat(src, 0);
      goto LABEL_47;
    }
    if ( !idStr::Icmp(token.data, "totalMass") )
    {
      this->totalMass = idLexer::ParseFloat(src, 0);
      goto LABEL_47;
    }
    if ( idStr::Icmp(token.data, "suspendSpeed") )
      break;
    this->suspendVelocity.x = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_51;
    this->suspendVelocity.y = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_51;
    this->suspendAcceleration.x = idLexer::ParseFloat(src, 0);
    if ( !idLexer::ExpectTokenString(src, ",") )
      goto LABEL_51;
    this->suspendAcceleration.y = idLexer::ParseFloat(src, 0);
LABEL_47:
    if ( !idLexer::ReadToken(src, &token) )
      goto LABEL_48;
  }
  if ( !idStr::Icmp(token.data, "noMoveTime") )
  {
    this->noMoveTime = idLexer::ParseFloat(src, 0);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "noMoveTranslation") )
  {
    this->noMoveTranslation = idLexer::ParseFloat(src, 0);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "noMoveRotation") )
  {
    this->noMoveRotation = idLexer::ParseFloat(src, 0);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "minMoveTime") )
  {
    this->minMoveTime = idLexer::ParseFloat(src, 0);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "maxMoveTime") )
  {
    this->maxMoveTime = idLexer::ParseFloat(src, 0);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "contents") )
  {
    idDeclAF::ParseContents(this, src, &this->contents);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "clipMask") )
  {
    idDeclAF::ParseContents(this, src, &this->clipMask);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "selfCollision") )
  {
    this->selfCollision = idLexer::ParseBool(src);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(token.data, "fastEval") )
  {
    this->fastEval = 1;
    goto LABEL_47;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    idLexer::Error(src, "unknown token %s in settings", token.data);
    goto LABEL_51;
  }
LABEL_48:
  v8 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual bool __thiscall idDeclAF::Parse(char const *,int,bool)
char __thiscall idDeclAF::Parse(idDeclAF *this, const char *text, int textLength, bool noCaching)
{
  int v5; // ebp
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v7; // edx
  const char *v8; // edi
  int v9; // eax
  char v10; // al
  int num; // eax
  int v12; // ebx
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // ebp
  int v18; // edi
  idDeclAF_Body **list; // eax
  idDeclAF_Body *v21; // ecx
  idToken token; // [esp+Ch] [ebp-124h] BYREF
  idLexer src; // [esp+5Ch] [ebp-D4h] BYREF
  int v24; // [esp+12Ch] [ebp-4h]

  idLexer::idLexer(&src);
  v5 = 0;
  token.floatvalue = 0.0;
  v24 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = this->base;
  v7 = base->__vftable;
  LOBYTE(v24) = 1;
  v8 = v7->GetFileName(base);
  v9 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v8, v9);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  if ( !idLexer::ReadToken(&src, &token) )
  {
LABEL_20:
    num = this->bodies.num;
    if ( num > 0 )
    {
      v12 = 1;
      do
      {
        v13 = v12;
        if ( v12 < num )
        {
          do
          {
            if ( !idStr::Cmp(this->bodies.list[v5]->name.data, this->bodies.list[v13]->name.data) )
              idLexer::Error(&src, "two bodies with the same name \"%s\"", this->bodies.list[v5]->name.data);
            ++v13;
          }
          while ( v13 < this->bodies.num );
        }
        num = this->bodies.num;
        ++v12;
        ++v5;
      }
      while ( v12 - 1 < num );
    }
    v14 = this->constraints.num;
    if ( v14 > 0 )
    {
      v15 = 0;
      v16 = 1;
      do
      {
        v17 = v16;
        if ( v16 < v14 )
        {
          do
          {
            if ( !idStr::Cmp(this->constraints.list[v15]->name.data, this->constraints.list[v17]->name.data) )
              idLexer::Error(&src, "two constraints with the same name \"%s\"", this->constraints.list[v15]->name.data);
            ++v17;
          }
          while ( v17 < this->constraints.num );
        }
        if ( !idStr::Cmp(this->constraints.list[v15]->body1.data, &entityFilter) )
          idLexer::Error(&src, "no valid body1 specified for constraint '%s'", this->constraints.list[v15]->name.data);
        if ( !idStr::Cmp(this->constraints.list[v15]->body2.data, &entityFilter) )
          idLexer::Error(&src, "no valid body2 specified for constraint '%s'", this->constraints.list[v15]->name.data);
        v14 = this->constraints.num;
        ++v16;
        ++v15;
      }
      while ( v16 - 1 < v14 );
    }
    v18 = 0;
    if ( this->bodies.num > 0 )
    {
      while ( idStr::Cmp(this->bodies.list[v18]->jointName.data, "origin") )
      {
        if ( ++v18 >= this->bodies.num )
          goto LABEL_47;
      }
      if ( v18 )
      {
        list = this->bodies.list;
        v21 = *list;
        *list = list[v18];
        this->bodies.list[v18] = v21;
      }
    }
LABEL_47:
    LOBYTE(v24) = 0;
    idStr::FreeData(&token);
    v24 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
  while ( 1 )
  {
    if ( !idStr::Icmp(token.data, "settings") )
    {
      v10 = idDeclAF::ParseSettings(this, &src);
      goto LABEL_18;
    }
    if ( !idStr::Icmp(token.data, "body") )
    {
      v10 = idDeclAF::ParseBody(this, &src);
      goto LABEL_18;
    }
    if ( !idStr::Icmp(token.data, "fixed") )
    {
      v10 = idDeclAF::ParseFixed(this, &src);
      goto LABEL_18;
    }
    if ( !idStr::Icmp(token.data, "ballAndSocketJoint") )
    {
      v10 = idDeclAF::ParseBallAndSocketJoint(this, &src);
      goto LABEL_18;
    }
    if ( !idStr::Icmp(token.data, "universalJoint") )
    {
      v10 = idDeclAF::ParseUniversalJoint(this, &src);
      goto LABEL_18;
    }
    if ( !idStr::Icmp(token.data, "hinge") )
    {
      v10 = idDeclAF::ParseHinge(this, &src);
      goto LABEL_18;
    }
    if ( !idStr::Icmp(token.data, "slider") )
    {
      v10 = idDeclAF::ParseSlider(this, &src);
      goto LABEL_18;
    }
    if ( idStr::Icmp(token.data, "spring") )
      break;
    v10 = idDeclAF::ParseSpring(this, &src);
LABEL_18:
    if ( !v10 )
      goto LABEL_44;
    if ( !idLexer::ReadToken(&src, &token) )
      goto LABEL_20;
  }
  if ( !idStr::Cmp(token.data, "}") )
    goto LABEL_20;
  idLexer::Error(&src, "unknown keyword %s", token.data);
LABEL_44:
  LOBYTE(v24) = 0;
  idStr::FreeData(&token);
  v24 = -1;
  idLexer::~idLexer(&src);
  return 0;
}

// FUNC: public: void __thiscall idDeclAF::NewBody(char const *)
void __thiscall idDeclAF::NewBody(idDeclAF *this, char *name)
{
  idDeclAF_Body *v3; // eax
  idDeclAF_Body *v4; // eax
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v10; // ecx
  idDeclAF_Body **list; // edi
  int j; // eax
  idDeclAF_Body *v13; // [esp+10h] [ebp-4h]

  v3 = (idDeclAF_Body *)Memory::Allocate(0x260u);
  if ( v3 )
  {
    idDeclAF_Body::idDeclAF_Body(v3);
    v13 = v4;
  }
  else
  {
    v13 = 0;
  }
  idDeclAF_Body::SetDefault(v13, this);
  idStr::operator=(&v13->name, name);
  if ( !this->bodies.list )
  {
    granularity = this->bodies.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->bodies.size )
      {
        v6 = granularity < this->bodies.num;
        this->bodies.size = granularity;
        if ( v6 )
          this->bodies.num = granularity;
        this->bodies.list = (idDeclAF_Body **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->bodies.num; ++i )
          this->bodies.list[i] = *(idDeclAF_Body **)(4 * i);
      }
    }
    else
    {
      this->bodies.list = 0;
      this->bodies.num = 0;
      this->bodies.size = 0;
    }
  }
  num = this->bodies.num;
  size = this->bodies.size;
  if ( num == size )
  {
    if ( !this->bodies.granularity )
      this->bodies.granularity = 16;
    v10 = size + this->bodies.granularity - (size + this->bodies.granularity) % this->bodies.granularity;
    if ( v10 > 0 )
    {
      if ( v10 != this->bodies.size )
      {
        list = this->bodies.list;
        this->bodies.size = v10;
        if ( v10 < num )
          this->bodies.num = v10;
        this->bodies.list = (idDeclAF_Body **)Memory::Allocate(4 * v10);
        for ( j = 0; j < this->bodies.num; ++j )
          this->bodies.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->bodies.list )
        Memory::Free(this->bodies.list);
      this->bodies.list = 0;
      this->bodies.num = 0;
      this->bodies.size = 0;
    }
  }
  this->bodies.list[this->bodies.num++] = v13;
}

// FUNC: public: void __thiscall idDeclAF::NewConstraint(char const *)
void __thiscall idDeclAF::NewConstraint(idDeclAF *this, char *name)
{
  idDeclAF_Constraint *v3; // eax
  idDeclAF_Constraint *v4; // eax
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v10; // ecx
  idDeclAF_Constraint **list; // edi
  int j; // eax
  idDeclAF_Constraint *v13; // [esp+10h] [ebp-10h]

  v3 = (idDeclAF_Constraint *)Memory::Allocate(0x288u);
  if ( v3 )
  {
    idDeclAF_Constraint::idDeclAF_Constraint(v3);
    v13 = v4;
  }
  else
  {
    v13 = 0;
  }
  idDeclAF_Constraint::SetDefault(v13, this);
  idStr::operator=(&v13->name, name);
  if ( !this->constraints.list )
  {
    granularity = this->constraints.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->constraints.size )
      {
        v6 = granularity < this->constraints.num;
        this->constraints.size = granularity;
        if ( v6 )
          this->constraints.num = granularity;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->constraints.num; ++i )
          this->constraints.list[i] = *(idDeclAF_Constraint **)(4 * i);
      }
    }
    else
    {
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  num = this->constraints.num;
  size = this->constraints.size;
  if ( num == size )
  {
    if ( !this->constraints.granularity )
      this->constraints.granularity = 16;
    v10 = size + this->constraints.granularity - (size + this->constraints.granularity) % this->constraints.granularity;
    if ( v10 > 0 )
    {
      if ( v10 != this->constraints.size )
      {
        list = this->constraints.list;
        this->constraints.size = v10;
        if ( v10 < num )
          this->constraints.num = v10;
        this->constraints.list = (idDeclAF_Constraint **)Memory::Allocate(4 * v10);
        for ( j = 0; j < this->constraints.num; ++j )
          this->constraints.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->constraints.list )
        Memory::Free(this->constraints.list);
      this->constraints.list = 0;
      this->constraints.num = 0;
      this->constraints.size = 0;
    }
  }
  this->constraints.list[this->constraints.num++] = v13;
}

// FUNC: public: void __thiscall idDeclAF::DeleteConstraint(char const *)
void __thiscall idDeclAF::DeleteConstraint(idDeclAF *this, const char *name)
{
  int v3; // edi
  idDeclAF_Constraint **list; // edx
  idDeclAF_Constraint *v5; // ebx
  int num; // eax
  bool v7; // cc
  int v8; // eax
  idDeclAF_Constraint **v9; // ecx
  idDeclAF_Constraint *v10; // edx
  idDeclAF_Constraint **v11; // ecx

  v3 = 0;
  if ( this->constraints.num > 0 )
  {
    while ( idStr::Icmp(this->constraints.list[v3]->name.data, name) )
    {
      if ( ++v3 >= this->constraints.num )
        return;
    }
    list = this->constraints.list;
    v5 = list[v3];
    if ( v5 )
    {
      idDeclAF_Constraint::~idDeclAF_Constraint(list[v3]);
      Memory::Free(v5);
    }
    if ( v3 >= 0 )
    {
      num = this->constraints.num;
      if ( v3 < num )
      {
        v7 = v3 < num - 1;
        this->constraints.num = num - 1;
        v8 = v3;
        if ( v7 )
        {
          do
          {
            v9 = this->constraints.list;
            v10 = v9[v8 + 1];
            v11 = &v9[v8++];
            *v11 = v10;
          }
          while ( v8 < this->constraints.num );
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall rvDeclAFEditLocal::NewBody(class idDeclAF *,char const *)
void __thiscall rvDeclAFEditLocal::NewBody(rvDeclAFEditLocal *this, idDeclAF *edit, char *name)
{
  idDeclAF::NewBody(edit, name);
}

// FUNC: public: virtual void __thiscall rvDeclAFEditLocal::NewConstraint(class idDeclAF *,char const *)
void __thiscall rvDeclAFEditLocal::NewConstraint(rvDeclAFEditLocal *this, idDeclAF *edit, char *name)
{
  idDeclAF::NewConstraint(edit, name);
}

// FUNC: public: virtual void __thiscall rvDeclAFEditLocal::DeleteConstraint(class idDeclAF *,char const *)
void __thiscall rvDeclAFEditLocal::DeleteConstraint(rvDeclAFEditLocal *this, idDeclAF *edit, const char *name)
{
  idDeclAF::DeleteConstraint(edit, name);
}

// FUNC: private: bool __thiscall idDeclAF::WriteSettings(class idFile *)const
char __thiscall idDeclAF::WriteSettings(idDeclAF *this, idFile *f)
{
  idFile_vtbl *v4; // edx
  idFile_vtbl *v5; // ebx
  char *v6; // eax
  idFile_vtbl *v7; // ebx
  char *v8; // eax
  idStr str; // [esp+38h] [ebp-30h] BYREF
  int v11; // [esp+64h] [ebp-4h]

  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  v4 = f->__vftable;
  v11 = 0;
  v4->WriteFloatString(f, "\nsettings {\n");
  f->WriteFloatString(f, "\tmodel \"%s\"\n", this->model.data);
  f->WriteFloatString(f, "\tskin \"%s\"\n", this->skin.data);
  f->WriteFloatString(
    f,
    "\tfriction %f, %f, %f, %f\n",
    this->defaultLinearFriction,
    this->defaultAngularFriction,
    this->defaultContactFriction,
    this->defaultConstraintFriction);
  f->WriteFloatString(
    f,
    "\tsuspendSpeed %f, %f, %f, %f\n",
    this->suspendVelocity.x,
    this->suspendVelocity.y,
    this->suspendAcceleration.x,
    this->suspendAcceleration.y);
  f->WriteFloatString(f, "\tnoMoveTime %f\n", this->noMoveTime);
  f->WriteFloatString(f, "\tnoMoveTranslation %f\n", this->noMoveTranslation);
  f->WriteFloatString(f, "\tnoMoveRotation %f\n", this->noMoveRotation);
  f->WriteFloatString(f, "\tminMoveTime %f\n", this->minMoveTime);
  f->WriteFloatString(f, "\tmaxMoveTime %f\n", this->maxMoveTime);
  f->WriteFloatString(f, "\ttotalMass %f\n", this->totalMass);
  v5 = f->__vftable;
  v6 = idDeclAF::ContentsToString(this->contents, &str);
  v5->WriteFloatString(f, "\tcontents %s\n", v6);
  v7 = f->__vftable;
  v8 = idDeclAF::ContentsToString(this->clipMask, &str);
  v7->WriteFloatString(f, "\tclipMask %s\n", v8);
  f->WriteFloatString(f, "\tselfCollision %d\n", this->selfCollision);
  if ( this->fastEval )
    f->WriteFloatString(f, "\tfastEval\n");
  f->WriteFloatString(f, "}\n");
  v11 = -1;
  idStr::FreeData(&str);
  return 1;
}

// FUNC: private: virtual bool __thiscall idDeclAF::RebuildTextSource(void)
char __thiscall idDeclAF::RebuildTextSource(idDeclAF *this)
{
  int v2; // ebx
  const char *v3; // eax
  int v5; // esi
  idDeclAF_Constraint **list; // edx
  idDeclAF_Constraint *v7; // esi
  bool v8; // al
  idFile_Memory f; // [esp+8h] [ebp-4Ch] BYREF
  int v10; // [esp+50h] [ebp-4h]

  idFile_Memory::idFile_Memory(&f);
  v2 = 0;
  v10 = 0;
  idFile_Common::WriteFloatString(
    &f,
    "\n"
    "\n"
    "/*\n"
    "\tGenerated by the Articulated Figure Editor.\n"
    "\tDo not edit directly but launch the game and type 'editAFs' on the console.\n"
    "*/\n");
  v3 = this->base->GetName(this->base);
  idFile_Common::WriteFloatString(&f, "\narticulatedFigure %s {\n", v3);
  if ( !idDeclAF::WriteSettings(this, &f) )
  {
LABEL_2:
    v10 = -1;
    idFile_Memory::~idFile_Memory(&f);
    return 0;
  }
  v5 = 0;
  if ( this->bodies.num > 0 )
  {
    while ( idDeclAF::WriteBody(this, &f, this->bodies.list[v5]) )
    {
      if ( ++v5 >= this->bodies.num )
        goto LABEL_6;
    }
    goto LABEL_2;
  }
LABEL_6:
  if ( this->constraints.num > 0 )
  {
    while ( 2 )
    {
      list = this->constraints.list;
      v7 = list[v2];
      switch ( v7->type )
      {
        case DECLAF_CONSTRAINT_FIXED:
          f.WriteFloatString(&f, "\nfixed \"%s\" {\n", v7->name.data);
          f.WriteFloatString(&f, "\tbody1 \"%s\"\n", v7->body1.data);
          f.WriteFloatString(&f, "\tbody2 \"%s\"\n", v7->body2.data);
          f.WriteFloatString(&f, "}\n");
          goto LABEL_16;
        case DECLAF_CONSTRAINT_BALLANDSOCKETJOINT:
          v8 = idDeclAF::WriteBallAndSocketJoint(this, &f, list[v2]);
          goto LABEL_15;
        case DECLAF_CONSTRAINT_UNIVERSALJOINT:
          v8 = idDeclAF::WriteUniversalJoint(this, &f, list[v2]);
          goto LABEL_15;
        case DECLAF_CONSTRAINT_HINGE:
          v8 = idDeclAF::WriteHinge(this, &f, list[v2]);
          goto LABEL_15;
        case DECLAF_CONSTRAINT_SLIDER:
          v8 = idDeclAF::WriteSlider(this, &f, list[v2]);
          goto LABEL_15;
        case DECLAF_CONSTRAINT_SPRING:
          v8 = idDeclAF::WriteSpring(this, &f, list[v2]);
LABEL_15:
          if ( !v8 )
            goto LABEL_2;
LABEL_16:
          if ( ++v2 >= this->constraints.num )
            break;
          continue;
        default:
          goto LABEL_2;
      }
      break;
    }
  }
  idFile_Common::WriteFloatString(&f, "\n}");
  this->base->SetText(this->base, f.filePtr);
  v10 = -1;
  idFile_Memory::~idFile_Memory(&f);
  return 1;
}

// FUNC: public: virtual void __thiscall idDeclAF::FreeData(void)
void __thiscall idDeclAF::FreeData(idDeclAF *this)
{
  int i; // edi
  idDeclAF_Body **list; // eax
  idDeclAF_Body *v4; // ebp
  int j; // edi
  idDeclAF_Constraint **v6; // edx
  idDeclAF_Constraint *v7; // ebp

  this->defaultLinearFriction = 0.0099999998;
  this->defaultAngularFriction = 0.0099999998;
  this->defaultContactFriction = 0.80000001;
  this->defaultConstraintFriction = 0.5;
  this->totalMass = -1.0;
  this->modified = 0;
  this->suspendVelocity.x = 20.0;
  this->suspendVelocity.y = 30.0;
  this->suspendAcceleration.x = 40.0;
  this->suspendAcceleration.y = 60.0;
  this->noMoveTime = 1.0;
  this->noMoveTranslation = 10.0;
  this->noMoveRotation = 10.0;
  this->minMoveTime = -1.0;
  this->maxMoveTime = -1.0;
  this->selfCollision = 1;
  this->contents = 1024;
  this->clipMask = 1025;
  for ( i = 0; i < this->bodies.num; ++i )
  {
    list = this->bodies.list;
    v4 = list[i];
    if ( v4 )
    {
      idDeclAF_Body::~idDeclAF_Body(list[i]);
      Memory::Free(v4);
    }
    this->bodies.list[i] = 0;
  }
  if ( this->bodies.list )
    Memory::Free(this->bodies.list);
  this->bodies.list = 0;
  this->bodies.num = 0;
  this->bodies.size = 0;
  for ( j = 0; j < this->constraints.num; ++j )
  {
    v6 = this->constraints.list;
    v7 = v6[j];
    if ( v7 )
    {
      idDeclAF_Constraint::~idDeclAF_Constraint(v6[j]);
      Memory::Free(v7);
    }
    this->constraints.list[j] = 0;
  }
  if ( this->constraints.list )
    Memory::Free(this->constraints.list);
  this->constraints.list = 0;
  this->constraints.num = 0;
  this->constraints.size = 0;
}

// FUNC: public: void __thiscall idDeclAF::DeleteBody(char const *)
void __thiscall idDeclAF::DeleteBody(idDeclAF *this, const char *name)
{
  int v3; // edi
  idDeclAF_Body **list; // edx
  idDeclAF_Body *v5; // ebx
  int num; // eax
  bool v7; // cc
  int v8; // eax
  idDeclAF_Body **v9; // ecx
  idDeclAF_Body *v10; // edx
  idDeclAF_Body **v11; // ecx
  int i; // edi
  idDeclAF_Constraint **v13; // ecx
  idDeclAF_Constraint *v14; // ebx
  int v15; // eax
  int v16; // eax
  idDeclAF_Constraint **v17; // ecx

  v3 = 0;
  if ( this->bodies.num > 0 )
  {
    while ( idStr::Icmp(this->bodies.list[v3]->name.data, name) )
    {
      if ( ++v3 >= this->bodies.num )
        goto LABEL_11;
    }
    list = this->bodies.list;
    v5 = list[v3];
    if ( v5 )
    {
      idDeclAF_Body::~idDeclAF_Body(list[v3]);
      Memory::Free(v5);
    }
    if ( v3 >= 0 )
    {
      num = this->bodies.num;
      if ( v3 < num )
      {
        v7 = v3 < num - 1;
        this->bodies.num = num - 1;
        v8 = v3;
        if ( v7 )
        {
          do
          {
            v9 = this->bodies.list;
            v10 = v9[v8 + 1];
            v11 = &v9[v8++];
            *v11 = v10;
          }
          while ( v8 < this->bodies.num );
        }
      }
    }
  }
LABEL_11:
  for ( i = 0; i < this->constraints.num; ++i )
  {
    if ( !idStr::Icmp(this->constraints.list[i]->body1.data, name)
      || !idStr::Icmp(this->constraints.list[i]->body2.data, name) )
    {
      v13 = this->constraints.list;
      v14 = v13[i];
      if ( v14 )
      {
        idDeclAF_Constraint::~idDeclAF_Constraint(v13[i]);
        Memory::Free(v14);
      }
      if ( i >= 0 )
      {
        v15 = this->constraints.num;
        if ( i < v15 )
        {
          v7 = i < v15 - 1;
          this->constraints.num = v15 - 1;
          v16 = i;
          if ( v7 )
          {
            do
            {
              v17 = &this->constraints.list[v16++];
              *v17 = v17[1];
            }
            while ( v16 < this->constraints.num );
          }
        }
      }
      --i;
    }
  }
}

// FUNC: public: __thiscall idDeclAF::idDeclAF(void)
void __thiscall idDeclAF::idDeclAF(idDeclAF *this)
{
  char *baseBuffer; // ecx

  this->base = 0;
  this->__vftable = (idDeclAF_vtbl *)&idDeclAF::`vftable';
  baseBuffer = this->model.baseBuffer;
  this->model.len = 0;
  this->model.alloced = 20;
  this->model.data = baseBuffer;
  *baseBuffer = 0;
  this->skin.len = 0;
  this->skin.alloced = 20;
  this->skin.data = this->skin.baseBuffer;
  this->skin.baseBuffer[0] = 0;
  this->bodies.granularity = 16;
  this->bodies.list = 0;
  this->bodies.num = 0;
  this->bodies.size = 0;
  this->constraints.granularity = 16;
  this->constraints.list = 0;
  this->constraints.num = 0;
  this->constraints.size = 0;
  idDeclAF::FreeData(this);
}

// FUNC: public: virtual __thiscall idDeclAF::~idDeclAF(void)
void __thiscall idDeclAF::~idDeclAF(idDeclAF *this)
{
  int i; // edi
  idDeclAF_Body **list; // eax
  idDeclAF_Body *v4; // ebp
  int j; // edi
  idDeclAF_Constraint **v6; // edx
  idDeclAF_Constraint *v7; // ebp
  idDeclAF_Body **v8; // eax

  this->__vftable = (idDeclAF_vtbl *)&idDeclAF::`vftable';
  for ( i = 0; i < this->bodies.num; ++i )
  {
    list = this->bodies.list;
    v4 = list[i];
    if ( v4 )
    {
      idDeclAF_Body::~idDeclAF_Body(list[i]);
      Memory::Free(v4);
    }
    this->bodies.list[i] = 0;
  }
  if ( this->bodies.list )
    Memory::Free(this->bodies.list);
  this->bodies.list = 0;
  this->bodies.num = 0;
  this->bodies.size = 0;
  for ( j = 0; j < this->constraints.num; ++j )
  {
    v6 = this->constraints.list;
    v7 = v6[j];
    if ( v7 )
    {
      idDeclAF_Constraint::~idDeclAF_Constraint(v6[j]);
      Memory::Free(v7);
    }
    this->constraints.list[j] = 0;
  }
  if ( this->constraints.list )
    Memory::Free(this->constraints.list);
  this->constraints.list = 0;
  this->constraints.num = 0;
  this->constraints.size = 0;
  this->constraints.list = 0;
  this->constraints.num = 0;
  this->constraints.size = 0;
  v8 = this->bodies.list;
  if ( v8 )
    Memory::Free(v8);
  this->bodies.list = 0;
  this->bodies.num = 0;
  this->bodies.size = 0;
  idStr::FreeData(&this->skin);
  idStr::FreeData(&this->model);
  this->__vftable = (idDeclAF_vtbl *)&idDecl::`vftable';
}

// FUNC: public: virtual void __thiscall rvDeclAFEditLocal::DeleteBody(class idDeclAF *,char const *)
void __thiscall rvDeclAFEditLocal::DeleteBody(rvDeclAFEditLocal *this, idDeclAF *edit, const char *name)
{
  idDeclAF::DeleteBody(edit, name);
}
