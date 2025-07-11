
// FUNC: public: virtual char const * __thiscall rvDeclPlayback::DefaultDefinition(void)const
const char *__thiscall rvDeclPlayback::DefaultDefinition(rvDeclPlayback *this)
{
  return "{ sequence { } data { } }";
}

// FUNC: public: void __thiscall rvDeclPlayback::ParseSample(class idLexer *,class idVec3 &,class idAngles &)
void __thiscall rvDeclPlayback::ParseSample(rvDeclPlayback *this, idLexer *src, idVec3 *pos, idAngles *ang)
{
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v5; // [esp+5Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v5 = 0;
  idLexer::ReadToken(src, &token);
  while ( idStr::Icmp(token.data, "}") )
  {
    if ( idStr::Icmp(token.data, "pos") )
    {
      if ( idStr::Icmp(token.data, "ang") )
      {
        if ( idStr::Icmp(token.data, "rotate") )
        {
          if ( !idStr::Icmp(token.data, "down") || !idStr::Icmp(token.data, "up") || !idStr::Icmp(token.data, "impulse") )
            idLexer::ParseInt(src);
        }
        else
        {
          ang->pitch = idLexer::ParseFloat(src, 0);
          idLexer::ExpectTokenString(src, ",");
          ang->yaw = idLexer::ParseFloat(src, 0);
          idLexer::ExpectTokenString(src, ",");
          ang->roll = idLexer::ParseFloat(src, 0);
        }
      }
      else
      {
        ang->pitch = idLexer::ParseFloat(src, 0);
        idLexer::ExpectTokenString(src, ",");
        ang->yaw = idLexer::ParseFloat(src, 0);
        ang->roll = 0.0;
      }
    }
    else
    {
      pos->x = idLexer::ParseFloat(src, 0);
      idLexer::ExpectTokenString(src, ",");
      pos->y = idLexer::ParseFloat(src, 0);
      idLexer::ExpectTokenString(src, ",");
      pos->z = idLexer::ParseFloat(src, 0);
    }
    idLexer::ReadToken(src, &token);
  }
  v5 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: void __thiscall rvDeclPlayback::WriteButtons(class idFile_Memory &)
void __thiscall rvDeclPlayback::WriteButtons(rvDeclPlayback *this, idFile_Memory *f)
{
  int num; // ebx
  int v5; // edi
  rvButtonState *list; // ecx
  unsigned __int8 v7; // bl
  rvButtonState *v8; // eax
  unsigned __int8 state; // al
  unsigned __int8 impulse; // al
  int count; // [esp+18h] [ebp-4h]
  unsigned __int8 fa; // [esp+20h] [ebp+4h]

  num = this->buttons.num;
  count = num;
  if ( num && (this->flags & 4) != 0 )
  {
    f->WriteFloatString(f, "\tbuttons\n\t{\n");
    v5 = 0;
    fa = 0;
    if ( num > 0 )
    {
      do
      {
        list = this->buttons.list;
        v7 = fa ^ list[v5].state;
        v8 = &list[v5];
        if ( v7 || v8->impulse )
        {
          f->WriteFloatString(f, "\t\t{ %.3g ", v8->time);
          if ( v7 )
          {
            state = this->buttons.list[v5].state;
            if ( (state & v7) != 0 )
              f->WriteFloatString(f, "down %d ", v7 & state);
            if ( (v7 & fa) != 0 )
              f->WriteFloatString(f, "up %d ", fa & v7);
            fa = this->buttons.list[v5].state;
          }
          impulse = this->buttons.list[v5].impulse;
          if ( impulse )
            f->WriteFloatString(f, "impulse %d ", impulse);
          f->WriteFloatString(f, "}\n");
        }
        ++v5;
      }
      while ( v5 < count );
    }
    f->WriteFloatString(f, "\t}\n");
  }
}

// FUNC: public: void __thiscall rvDeclPlayback::WriteSequence(class idFile_Memory &)
void __thiscall rvDeclPlayback::WriteSequence(rvDeclPlayback *this, idFile_Memory *f)
{
  f->WriteFloatString(f, "\tsequence\n\t{\n");
  f->WriteFloatString(f, "\t\torigin\t\t%.1f,%.1f,%.1f\n", this->origin.x, this->origin.y, this->origin.z);
  f->WriteFloatString(f, "\t\tframeRate\t%.1f\n", this->frameRate);
  f->WriteFloatString(f, "\t}\n");
}

// FUNC: public: bool __thiscall rvDeclPlayback::ParseData(class idLexer *)
char __thiscall rvDeclPlayback::ParseData(rvDeclPlayback *this, idLexer *src)
{
  float time; // [esp+10h] [ebp-78h]
  idVec3 pos; // [esp+14h] [ebp-74h] BYREF
  idAngles ang; // [esp+20h] [ebp-68h] BYREF
  idToken token; // [esp+2Ch] [ebp-5Ch] BYREF
  int v8; // [esp+84h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 0;
  time = 0.0;
  memset(&pos, 0, sizeof(pos));
  memset(&ang, 0, sizeof(ang));
  idLexer::ExpectTokenString(src, "{");
  if ( idLexer::ReadToken(src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( !idStr::Icmp(token.data, "{") )
      {
        rvDeclPlayback::ParseSample(this, src, &pos, &ang);
        ((void (__thiscall *)(idCurve_UniformCubicBSpline<idVec3> *, _DWORD, idVec3 *))this->points.AddValue)(
          &this->points,
          LODWORD(time),
          &pos);
        ((void (__thiscall *)(idCurve_UniformCubicBSpline<idAngles> *, _DWORD, idAngles *))this->angles.AddValue)(
          &this->angles,
          LODWORD(time),
          &ang);
        time = 1.0 / this->frameRate + time;
      }
      if ( !idLexer::ReadToken(src, &token) )
        goto LABEL_6;
    }
    this->duration = time;
    v8 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_6:
    v8 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: void __thiscall rvDeclPlayback::ParseButton(class idLexer *,unsigned char &,class rvButtonState &)
void __thiscall rvDeclPlayback::ParseButton(
        rvDeclPlayback *this,
        idLexer *src,
        unsigned __int8 *button,
        rvButtonState *state)
{
  unsigned __int8 v4; // bl
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v7; // [esp+5Ch] [ebp-4h]
  float srca; // [esp+64h] [ebp+4h]

  v4 = 0;
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v7 = 0;
  srca = idLexer::ParseFloat(src, 0);
  idLexer::ReadToken(src, &token);
  while ( idStr::Icmp(token.data, "}") )
  {
    if ( idStr::Icmp(token.data, "down") )
    {
      if ( idStr::Icmp(token.data, "up") )
      {
        if ( !idStr::Icmp(token.data, "impulse") )
          v4 = idLexer::ParseInt(src);
      }
      else
      {
        *button &= ~(unsigned __int8)idLexer::ParseInt(src);
      }
    }
    else
    {
      *button |= idLexer::ParseInt(src);
    }
    idLexer::ReadToken(src, &token);
  }
  state->state = *button;
  state->time = srca;
  state->impulse = v4;
  v7 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: bool __thiscall rvDeclPlayback::ParseSequence(class idLexer *)
char __thiscall rvDeclPlayback::ParseSequence(rvDeclPlayback *this, idLexer *src)
{
  char *data; // ebp
  const char *v4; // eax
  idStr deprecated; // [esp+8h] [ebp-7Ch] BYREF
  idToken token; // [esp+28h] [ebp-5Ch] BYREF
  int v8; // [esp+80h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 0;
  idLexer::ExpectTokenString(src, "sequence");
  idLexer::ExpectTokenString(src, "{");
  if ( idLexer::ReadToken(src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "destination") )
      {
        if ( idStr::Icmp(token.data, "origin") )
        {
          if ( idStr::Icmp(token.data, "framerate") )
          {
            data = token.data;
            v4 = this->base->GetName(this->base);
            idLexer::Error(src, "Invalid token %s in file %s.\n", data, v4);
          }
          else
          {
            this->frameRate = idLexer::ParseFloat(src, 0);
          }
        }
        else
        {
          this->origin.x = idLexer::ParseFloat(src, 0);
          idLexer::ExpectTokenString(src, ",");
          this->origin.y = idLexer::ParseFloat(src, 0);
          idLexer::ExpectTokenString(src, ",");
          this->origin.z = idLexer::ParseFloat(src, 0);
        }
      }
      else
      {
        deprecated.len = 0;
        deprecated.alloced = 20;
        deprecated.data = deprecated.baseBuffer;
        deprecated.baseBuffer[0] = 0;
        LOBYTE(v8) = 1;
        idLexer::ParseRestOfLine(src, &deprecated);
        LOBYTE(v8) = 0;
        idStr::FreeData(&deprecated);
      }
      if ( !idLexer::ReadToken(src, &token) )
        goto LABEL_11;
    }
    v8 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_11:
    v8 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: virtual void __thiscall rvDeclPlayback::FreeData(void)
void __thiscall rvDeclPlayback::FreeData(rvDeclPlayback *this)
{
  this->points.Clear(&this->points);
  this->angles.Clear(&this->angles);
  if ( this->buttons.list )
    Memory::Free(this->buttons.list);
  this->buttons.list = 0;
  this->buttons.num = 0;
  this->buttons.size = 0;
}

// FUNC: public: virtual void __thiscall rvDeclPlaybackEditLocal::SetOrigin(class rvDeclPlayback *,class idVec3 &)
void __thiscall rvDeclPlaybackEditLocal::SetOrigin(rvDeclPlaybackEditLocal *this, rvDeclPlayback *edit, idVec3 *origin)
{
  edit->origin = *origin;
}

// FUNC: public: void __thiscall rvDeclPlayback::WriteData(class idFile_Memory &)
void __thiscall rvDeclPlayback::WriteData(rvDeclPlayback *this, idFile_Memory *f)
{
  int v3; // ebx
  idVec3 *v4; // edx
  idAngles *v5; // eax
  float v6; // [esp+24h] [ebp-4Ch]
  float v7; // [esp+28h] [ebp-48h]
  float v8; // [esp+2Ch] [ebp-44h]
  float v9; // [esp+30h] [ebp-40h]
  float v10; // [esp+34h] [ebp-3Ch]
  float v11; // [esp+38h] [ebp-38h]
  int num; // [esp+3Ch] [ebp-34h]
  float pitch; // [esp+40h] [ebp-30h]
  float yaw; // [esp+44h] [ebp-2Ch]
  float roll; // [esp+48h] [ebp-28h]
  float x; // [esp+4Ch] [ebp-24h]
  float y; // [esp+50h] [ebp-20h]
  float z; // [esp+54h] [ebp-1Ch]
  float oldPos; // [esp+58h] [ebp-18h]
  float oldPos_4; // [esp+5Ch] [ebp-14h]
  float oldPos_8; // [esp+60h] [ebp-10h]
  float oldAng; // [esp+64h] [ebp-Ch]
  float oldAng_4; // [esp+68h] [ebp-8h]
  float oldAng_8; // [esp+6Ch] [ebp-4h]

  if ( (this->points.values.num || this->angles.values.num) && (this->flags & 3) != 0 )
  {
    f->WriteFloatString(f, "\tdata\n\t{\n");
    if ( this->points.values.num > 0 )
    {
      v3 = 0;
      num = this->points.values.num;
      do
      {
        f->WriteFloatString(f, "\t\t{ ");
        if ( (this->flags & 1) != 0 )
        {
          v4 = &this->points.values.list[v3];
          x = v4->x;
          y = v4->y;
          z = v4->z;
          v6 = v4->x - oldPos;
          if ( COERCE_FLOAT(LODWORD(v6) & 0x7FFFFFFF) > 0.0625
            || (v7 = y - oldPos_4, COERCE_FLOAT(LODWORD(v7) & 0x7FFFFFFF) > 0.0625)
            || (v8 = z - oldPos_8, COERCE_FLOAT(LODWORD(v8) & 0x7FFFFFFF) > 0.0625) )
          {
            f->WriteFloatString(f, "pos %.1f,%.1f,%.1f ", x, y, z);
            oldPos = x;
            oldPos_4 = y;
            oldPos_8 = z;
          }
        }
        if ( (this->flags & 2) != 0 )
        {
          v5 = &this->angles.values.list[v3];
          pitch = v5->pitch;
          roll = v5->roll;
          v9 = v5->pitch - oldAng;
          yaw = v5->yaw;
          if ( COERCE_FLOAT(LODWORD(v9) & 0x7FFFFFFF) > 0.0625
            || (v10 = yaw - oldAng_4, COERCE_FLOAT(LODWORD(v10) & 0x7FFFFFFF) > 0.0625)
            || (v11 = roll - oldAng_8, COERCE_FLOAT(LODWORD(v11) & 0x7FFFFFFF) > 0.0625) )
          {
            if ( roll == 0.0 )
              f->WriteFloatString(f, "ang %.1f,%.1f ", pitch, yaw);
            else
              f->WriteFloatString(f, "rotate %.1f,%.1f,%.1f ", pitch, yaw, roll);
            oldAng = pitch;
            oldAng_4 = yaw;
            oldAng_8 = roll;
          }
        }
        f->WriteFloatString(f, "}\n");
        ++v3;
        --num;
      }
      while ( num );
    }
    f->WriteFloatString(f, "\t}\n");
  }
}

// FUNC: public: bool __thiscall rvDeclPlayback::ParseButtons(class idLexer *)
char __thiscall rvDeclPlayback::ParseButtons(rvDeclPlayback *this, idLexer *src)
{
  idLexer *v3; // edi
  int granularity; // eax
  bool v5; // cc
  int i; // eax
  rvButtonState *list; // ecx
  int num; // ebp
  int size; // eax
  int v10; // ecx
  rvButtonState *v11; // edi
  int j; // eax
  rvButtonState *v13; // ecx
  unsigned __int8 button; // [esp+Bh] [ebp-65h] BYREF
  rvButtonState state; // [esp+Ch] [ebp-64h] BYREF
  idToken token; // [esp+14h] [ebp-5Ch] BYREF
  int v18; // [esp+6Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = src;
  v18 = 0;
  button = 0;
  idLexer::ExpectTokenString(src, "{");
  if ( idLexer::ReadToken(src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( !idStr::Icmp(token.data, "{") )
      {
        rvDeclPlayback::ParseButton(this, v3, &button, &state);
        if ( !this->buttons.list )
        {
          granularity = this->buttons.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->buttons.size )
            {
              v5 = granularity < this->buttons.num;
              this->buttons.size = granularity;
              if ( v5 )
                this->buttons.num = granularity;
              this->buttons.list = (rvButtonState *)Memory::Allocate(8 * granularity);
              for ( i = 0; i < this->buttons.num; ++i )
              {
                list = this->buttons.list;
                list[i].time = *(float *)(8 * i);
                *(_DWORD *)&list[i].state = *(_DWORD *)(8 * i + 4);
              }
            }
          }
          else
          {
            this->buttons.list = 0;
            this->buttons.num = 0;
            this->buttons.size = 0;
          }
        }
        num = this->buttons.num;
        size = this->buttons.size;
        if ( num == size )
        {
          if ( !this->buttons.granularity )
            this->buttons.granularity = 16;
          v10 = size + this->buttons.granularity - (size + this->buttons.granularity) % this->buttons.granularity;
          if ( v10 > 0 )
          {
            if ( v10 != this->buttons.size )
            {
              v11 = this->buttons.list;
              this->buttons.size = v10;
              if ( v10 < num )
                this->buttons.num = v10;
              this->buttons.list = (rvButtonState *)Memory::Allocate(8 * v10);
              for ( j = 0; j < this->buttons.num; ++j )
              {
                v13 = this->buttons.list;
                v13[j].time = v11[j].time;
                *(_DWORD *)&v13[j].state = *(_DWORD *)&v11[j].state;
              }
              if ( v11 )
                Memory::Free(v11);
            }
          }
          else
          {
            if ( this->buttons.list )
              Memory::Free(this->buttons.list);
            this->buttons.list = 0;
            this->buttons.num = 0;
            this->buttons.size = 0;
          }
        }
        v3 = src;
        this->buttons.list[this->buttons.num++] = state;
      }
      if ( !idLexer::ReadToken(v3, &token) )
        goto LABEL_28;
    }
    v18 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_28:
    v18 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: void __thiscall rvDeclPlayback::SetOrigin(void)
void __thiscall rvDeclPlayback::SetOrigin(rvDeclPlayback *this)
{
  int num; // esi
  idVec3 *list; // eax
  double v3; // st7
  float y; // edx
  float z; // eax
  int v6; // eax
  int v7; // edi
  unsigned int v8; // ebp
  idVec3 *v9; // edx
  double v10; // st7
  double v11; // st6
  idVec3 *v12; // eax
  double v13; // st7
  double v14; // st6
  idVec3 *v15; // eax
  idVec3 *v16; // edx
  int v17; // esi
  idVec3 *v18; // eax
  double v19; // st7
  idVec3 *v20; // eax
  float *v21; // edx
  double v22; // st7
  double v23; // st6
  float *v24; // eax
  int v25; // edx
  int v26; // esi
  idVec3 *v27; // eax
  double v28; // st7
  idVec3 *v29; // eax
  int count; // [esp+4h] [ebp-38h]
  int i; // [esp+8h] [ebp-34h]
  float v32; // [esp+Ch] [ebp-30h]
  float v33; // [esp+Ch] [ebp-30h]
  float v34; // [esp+Ch] [ebp-30h]
  float v35; // [esp+Ch] [ebp-30h]
  float v36; // [esp+Ch] [ebp-30h]
  float v37; // [esp+10h] [ebp-2Ch]
  float v38; // [esp+10h] [ebp-2Ch]
  float v39; // [esp+10h] [ebp-2Ch]
  float v40; // [esp+10h] [ebp-2Ch]
  float v41; // [esp+10h] [ebp-2Ch]
  float v42; // [esp+14h] [ebp-28h]
  float v43; // [esp+14h] [ebp-28h]
  float v44; // [esp+14h] [ebp-28h]
  float v45; // [esp+14h] [ebp-28h]
  float v46; // [esp+14h] [ebp-28h]
  float v47; // [esp+1Ch] [ebp-20h]
  float v48; // [esp+1Ch] [ebp-20h]
  float x; // [esp+24h] [ebp-18h]
  float v50; // [esp+28h] [ebp-14h]
  float v51; // [esp+2Ch] [ebp-10h]
  float v52; // [esp+38h] [ebp-4h]
  float v53; // [esp+38h] [ebp-4h]
  float v54; // [esp+38h] [ebp-4h]
  float v55; // [esp+38h] [ebp-4h]
  float v56; // [esp+38h] [ebp-4h]

  num = this->points.values.num;
  count = num;
  if ( num )
  {
    list = this->points.values.list;
    x = list->x;
    v3 = list->x + this->origin.x;
    y = list->y;
    z = list->z;
    v50 = y;
    this->origin.x = v3;
    v51 = z;
    this->origin.y = y + this->origin.y;
    this->origin.z = z + this->origin.z;
    this->bounds.b[0].z = idMath::INFINITY;
    this->bounds.b[0].y = idMath::INFINITY;
    this->bounds.b[0].x = idMath::INFINITY;
    v6 = 0;
    this->bounds.b[1].z = -1.0e30;
    this->bounds.b[1].y = -1.0e30;
    this->bounds.b[1].x = -1.0e30;
    if ( num >= 4 )
    {
      v7 = 0;
      v8 = ((unsigned int)(num - 4) >> 2) + 1;
      i = 4 * v8;
      do
      {
        v9 = &this->points.values.list[v7];
        v10 = v9->x - x;
        v11 = v9->y - v50;
        v52 = v9->z - v51;
        v9->z = v52;
        v9->x = v10;
        v9->y = v11;
        this->points.changed = 1;
        v12 = &this->points.values.list[v7];
        v32 = v12->x;
        v42 = v12->z;
        v37 = v12->y;
        if ( v12->x < (double)this->bounds.b[0].x )
          this->bounds.b[0].x = v32;
        if ( v32 > (double)this->bounds.b[1].x )
          this->bounds.b[1].x = v32;
        if ( v37 < (double)this->bounds.b[0].y )
          this->bounds.b[0].y = v37;
        if ( v37 > (double)this->bounds.b[1].y )
          this->bounds.b[1].y = v37;
        if ( v42 < (double)this->bounds.b[0].z )
          this->bounds.b[0].z = v42;
        if ( v42 > (double)this->bounds.b[1].z )
          this->bounds.b[1].z = v42;
        v13 = this->points.values.list[v7 + 1].x - x;
        v14 = this->points.values.list[v7 + 1].y - v50;
        v15 = &this->points.values.list[v7 + 1];
        v53 = this->points.values.list[v7 + 1].z - v51;
        v15->z = v53;
        v15->x = v13;
        v15->y = v14;
        this->points.changed = 1;
        v16 = &this->points.values.list[v7 + 1];
        v33 = v16->x;
        v38 = this->points.values.list[v7 + 1].y;
        v43 = this->points.values.list[v7 + 1].z;
        if ( v16->x < (double)this->bounds.b[0].x )
          this->bounds.b[0].x = v33;
        if ( v33 > (double)this->bounds.b[1].x )
          this->bounds.b[1].x = v33;
        if ( v38 < (double)this->bounds.b[0].y )
          this->bounds.b[0].y = v38;
        if ( v38 > (double)this->bounds.b[1].y )
          this->bounds.b[1].y = v38;
        if ( v43 < (double)this->bounds.b[0].z )
          this->bounds.b[0].z = v43;
        if ( v43 > (double)this->bounds.b[1].z )
          this->bounds.b[1].z = v43;
        v17 = v7 * 12 + 36;
        v18 = &this->points.values.list[v7 + 2];
        v19 = v18->x - x;
        v47 = v18->y;
        v54 = v18->z - v51;
        v18->z = v54;
        v18->x = v19;
        v18->y = v47 - v50;
        this->points.changed = 1;
        v20 = &this->points.values.list[v7 + 2];
        v34 = v20->x;
        v44 = v20->z;
        v39 = v20->y;
        if ( v20->x < (double)this->bounds.b[0].x )
          this->bounds.b[0].x = v34;
        if ( v34 > (double)this->bounds.b[1].x )
          this->bounds.b[1].x = v34;
        if ( v39 < (double)this->bounds.b[0].y )
          this->bounds.b[0].y = v39;
        if ( v39 > (double)this->bounds.b[1].y )
          this->bounds.b[1].y = v39;
        if ( v44 < (double)this->bounds.b[0].z )
          this->bounds.b[0].z = v44;
        if ( v44 > (double)this->bounds.b[1].z )
          this->bounds.b[1].z = v44;
        v21 = (float *)((char *)&this->points.values.list->x + v17);
        v22 = *v21 - x;
        v23 = v21[1] - v50;
        v55 = v21[2] - v51;
        v21[2] = v55;
        *v21 = v22;
        v21[1] = v23;
        this->points.changed = 1;
        v24 = (float *)((char *)&this->points.values.list->x + v17);
        v35 = *v24;
        v45 = v24[2];
        v40 = v24[1];
        if ( *v24 < (double)this->bounds.b[0].x )
          this->bounds.b[0].x = v35;
        if ( v35 > (double)this->bounds.b[1].x )
          this->bounds.b[1].x = v35;
        if ( v40 < (double)this->bounds.b[0].y )
          this->bounds.b[0].y = v40;
        if ( v40 > (double)this->bounds.b[1].y )
          this->bounds.b[1].y = v40;
        if ( v45 < (double)this->bounds.b[0].z )
          this->bounds.b[0].z = v45;
        if ( v45 > (double)this->bounds.b[1].z )
          this->bounds.b[1].z = v45;
        v7 += 4;
        --v8;
      }
      while ( v8 );
      num = count;
      v6 = i;
    }
    if ( v6 < num )
    {
      v25 = v6;
      v26 = num - v6;
      do
      {
        v27 = &this->points.values.list[v25];
        v28 = v27->x - x;
        v48 = v27->y;
        v56 = v27->z - v51;
        v27->z = v56;
        v27->x = v28;
        v27->y = v48 - v50;
        this->points.changed = 1;
        v29 = &this->points.values.list[v25];
        v36 = v29->x;
        v46 = v29->z;
        v41 = v29->y;
        if ( v29->x < (double)this->bounds.b[0].x )
          this->bounds.b[0].x = v36;
        if ( v36 > (double)this->bounds.b[1].x )
          this->bounds.b[1].x = v36;
        if ( v41 < (double)this->bounds.b[0].y )
          this->bounds.b[0].y = v41;
        if ( v41 > (double)this->bounds.b[1].y )
          this->bounds.b[1].y = v41;
        if ( v46 < (double)this->bounds.b[0].z )
          this->bounds.b[0].z = v46;
        if ( v46 > (double)this->bounds.b[1].z )
          this->bounds.b[1].z = v46;
        ++v25;
        --v26;
      }
      while ( v26 );
    }
  }
}

// FUNC: public: virtual bool __thiscall rvDeclPlayback::RebuildTextSource(void)
char __thiscall rvDeclPlayback::RebuildTextSource(rvDeclPlayback *this)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v3; // eax
  const char *v4; // eax
  idFile_Memory f; // [esp+4h] [ebp-4Ch] BYREF
  int v7; // [esp+4Ch] [ebp-4h]

  idFile_Memory::idFile_Memory(&f);
  base = this->base;
  v3 = base->__vftable;
  v7 = 0;
  v4 = v3->GetName(base);
  idFile_Common::WriteFloatString(&f, "\nplayback %s\n{\n", v4);
  rvDeclPlayback::WriteSequence(this, &f);
  rvDeclPlayback::WriteData(this, &f);
  rvDeclPlayback::WriteButtons(this, &f);
  idFile_Common::WriteFloatString(&f, "}\n\n");
  this->base->SetText(this->base, f.filePtr);
  v7 = -1;
  idFile_Memory::~idFile_Memory(&f);
  return 1;
}

// FUNC: public: bool __thiscall rvDeclPlayback::SetCurrentData(float,int,class rvDeclPlaybackData *)
char __thiscall rvDeclPlayback::SetCurrentData(
        rvDeclPlayback *this,
        float localTime,
        char control,
        rvDeclPlaybackData *pbd)
{
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  rvButtonState *list; // ecx
  int num; // ebx
  int size; // eax
  int v11; // ecx
  rvButtonState *v12; // edi
  int j; // eax
  rvButtonState *v14; // ecx
  int v15; // eax
  rvButtonState *v16; // ecx
  int state_4; // [esp+14h] [ebp-4h]

  if ( (control & 1) != 0 )
    ((void (__thiscall *)(idCurve_UniformCubicBSpline<idVec3> *, _DWORD, idVec3 *))this->points.AddValue)(
      &this->points,
      LODWORD(localTime),
      &pbd->position);
  if ( (control & 2) != 0 )
    ((void (__thiscall *)(idCurve_UniformCubicBSpline<idAngles> *, _DWORD, idAngles *))this->angles.AddValue)(
      &this->angles,
      LODWORD(localTime),
      &pbd->angles);
  if ( (control & 4) != 0 )
  {
    LOWORD(state_4) = *(_WORD *)&pbd->button;
    if ( !this->buttons.list )
    {
      granularity = this->buttons.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->buttons.size )
        {
          v6 = granularity < this->buttons.num;
          this->buttons.size = granularity;
          if ( v6 )
            this->buttons.num = granularity;
          this->buttons.list = (rvButtonState *)Memory::Allocate(8 * granularity);
          for ( i = 0; i < this->buttons.num; ++i )
          {
            list = this->buttons.list;
            list[i].time = *(float *)(8 * i);
            *(_DWORD *)&list[i].state = *(_DWORD *)(8 * i + 4);
          }
        }
      }
      else
      {
        this->buttons.list = 0;
        this->buttons.num = 0;
        this->buttons.size = 0;
      }
    }
    num = this->buttons.num;
    size = this->buttons.size;
    if ( num == size )
    {
      if ( !this->buttons.granularity )
        this->buttons.granularity = 16;
      v11 = size + this->buttons.granularity - (size + this->buttons.granularity) % this->buttons.granularity;
      if ( v11 > 0 )
      {
        if ( v11 != this->buttons.size )
        {
          v12 = this->buttons.list;
          this->buttons.size = v11;
          if ( v11 < num )
            this->buttons.num = v11;
          this->buttons.list = (rvButtonState *)Memory::Allocate(8 * v11);
          for ( j = 0; j < this->buttons.num; ++j )
          {
            v14 = this->buttons.list;
            v14[j].time = v12[j].time;
            *(_DWORD *)&v14[j].state = *(_DWORD *)&v12[j].state;
          }
          if ( v12 )
            Memory::Free(v12);
        }
      }
      else
      {
        if ( this->buttons.list )
          Memory::Free(this->buttons.list);
        this->buttons.list = 0;
        this->buttons.num = 0;
        this->buttons.size = 0;
      }
    }
    v15 = this->buttons.num;
    v16 = this->buttons.list;
    v16[v15].time = localTime;
    *(_DWORD *)&v16[v15].state = state_4;
    ++this->buttons.num;
  }
  if ( localTime > (double)this->duration )
    this->duration = localTime;
  return 1;
}

// FUNC: public: virtual unsigned int __thiscall rvDeclPlayback::Size(void)const
int __thiscall rvDeclPlayback::Size(rvDeclPlayback *this)
{
  return 8 * this->buttons.size + 184 + 12 * (this->points.values.num + this->angles.values.num);
}

// FUNC: public: virtual void __thiscall rvDeclPlaybackEditLocal::SetOrigin(class rvDeclPlayback *)
void __thiscall rvDeclPlaybackEditLocal::SetOrigin(rvDeclPlaybackEditLocal *this, rvDeclPlayback *edit)
{
  rvDeclPlayback::SetOrigin(edit);
}

// FUNC: public: virtual bool __thiscall rvDeclPlayback::Parse(char const *,int,bool)
char __thiscall rvDeclPlayback::Parse(rvDeclPlayback *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // edi
  int v8; // eax
  idToken token; // [esp+Ch] [ebp-124h] BYREF
  idLexer src; // [esp+5Ch] [ebp-D4h] BYREF
  int v12; // [esp+12Ch] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v12 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = this->base;
  v6 = base->__vftable;
  LOBYTE(v12) = 1;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  if ( rvDeclPlayback::ParseSequence(this, &src) && idLexer::ReadToken(&src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "data") )
      {
        if ( !idStr::Icmp(token.data, "buttons") )
          rvDeclPlayback::ParseButtons(this, &src);
      }
      else
      {
        rvDeclPlayback::ParseData(this, &src);
      }
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_9;
    }
    rvDeclPlayback::SetOrigin(this);
    LOBYTE(v12) = 0;
    idStr::FreeData(&token);
    v12 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
  else
  {
LABEL_9:
    LOBYTE(v12) = 0;
    idStr::FreeData(&token);
    v12 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
}

// FUNC: public: virtual __thiscall rvDeclPlayback::~rvDeclPlayback(void)
void __thiscall rvDeclPlayback::~rvDeclPlayback(rvDeclPlayback *this)
{
  idCurve_UniformCubicBSpline<idVec3> *p_points; // edi

  this->__vftable = (rvDeclPlayback_vtbl *)&rvDeclPlayback::`vftable';
  p_points = &this->points;
  this->points.Clear(&this->points);
  this->angles.Clear(&this->angles);
  if ( this->buttons.list )
    Memory::Free(this->buttons.list);
  this->buttons.list = 0;
  this->buttons.num = 0;
  this->buttons.size = 0;
  this->buttons.list = 0;
  this->buttons.num = 0;
  this->buttons.size = 0;
  idCurve_Spline<idAngles>::~idCurve_Spline<idAngles>(&this->angles);
  idCurve<idVec3>::~idCurve<idVec3>(p_points);
  this->__vftable = (rvDeclPlayback_vtbl *)&idDecl::`vftable';
}

// FUNC: public: void __thiscall rvDeclPlayback::Start(void)
void __thiscall rvDeclPlayback::Start(rvDeclPlayback *this)
{
  idCurve_UniformCubicBSpline<idVec3> *p_points; // edi
  rvButtonState *list; // edi
  int v4; // ecx
  bool v5; // cc
  int i; // eax
  rvButtonState *v7; // ecx

  this->origin.z = 0.0;
  this->origin.y = 0.0;
  this->origin.x = 0.0;
  this->bounds.b[0].z = idMath::INFINITY;
  this->bounds.b[0].y = idMath::INFINITY;
  this->bounds.b[0].x = idMath::INFINITY;
  this->bounds.b[1].z = -1.0e30;
  p_points = &this->points;
  this->bounds.b[1].y = -1.0e30;
  this->bounds.b[1].x = -1.0e30;
  p_points->Clear(p_points);
  this->angles.Clear(&this->angles);
  if ( this->buttons.list )
    Memory::Free(this->buttons.list);
  this->buttons.list = 0;
  this->buttons.num = 0;
  this->buttons.size = 0;
  idCurve<idVec3>::SetGranularity((idCurve<idAngles> *)p_points, 60);
  idCurve<idVec3>::SetGranularity(&this->angles, 60);
  list = this->buttons.list;
  this->buttons.granularity = 60;
  if ( list )
  {
    v4 = this->buttons.num + 59 - (this->buttons.num + 59) % 60;
    if ( v4 != this->buttons.size )
    {
      if ( v4 > 0 )
      {
        v5 = v4 < this->buttons.num;
        this->buttons.size = v4;
        if ( v5 )
          this->buttons.num = v4;
        this->buttons.list = (rvButtonState *)Memory::Allocate(8 * v4);
        for ( i = 0; i < this->buttons.num; ++i )
        {
          v7 = this->buttons.list;
          v7[i].time = list[i].time;
          *(_DWORD *)&v7[i].state = *(_DWORD *)&list[i].state;
        }
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        this->buttons.list = 0;
        this->buttons.num = 0;
        this->buttons.size = 0;
      }
    }
  }
}

// FUNC: public: __thiscall rvDeclPlayback::rvDeclPlayback(void)
void __thiscall rvDeclPlayback::rvDeclPlayback(rvDeclPlayback *this)
{
  this->base = 0;
  this->__vftable = (rvDeclPlayback_vtbl *)&rvDeclPlayback::`vftable';
  this->points.times.granularity = 16;
  this->points.times.list = 0;
  this->points.times.num = 0;
  this->points.times.size = 0;
  this->points.values.granularity = 16;
  this->points.values.list = 0;
  this->points.values.num = 0;
  this->points.values.size = 0;
  this->points.currentIndex = -1;
  this->points.changed = 0;
  this->points.boundaryType = BT_FREE;
  this->points.closeTime = 0.0;
  this->points.__vftable = (idCurve_UniformCubicBSpline<idVec3>_vtbl *)&idCurve_UniformCubicBSpline<idVec3>::`vftable';
  this->points.order = 4;
  this->angles.times.granularity = 16;
  this->angles.times.list = 0;
  this->angles.times.num = 0;
  this->angles.times.size = 0;
  this->angles.values.granularity = 16;
  this->angles.values.list = 0;
  this->angles.values.num = 0;
  this->angles.values.size = 0;
  this->angles.currentIndex = -1;
  this->angles.changed = 0;
  this->angles.boundaryType = BT_FREE;
  this->angles.closeTime = 0.0;
  this->angles.__vftable = (idCurve_UniformCubicBSpline<idAngles>_vtbl *)&idCurve_UniformCubicBSpline<idAngles>::`vftable';
  this->angles.order = 4;
  this->buttons.list = 0;
  this->buttons.num = 0;
  this->buttons.size = 0;
  this->buttons.granularity = 16;
  this->flags = 0;
  this->duration = 0.0;
  this->frameRate = 15.0;
  this->origin.z = 0.0;
  this->origin.y = 0.0;
  this->origin.x = 0.0;
  this->bounds.b[0].z = idMath::INFINITY;
  this->bounds.b[0].y = idMath::INFINITY;
  this->bounds.b[0].x = idMath::INFINITY;
  this->bounds.b[1].z = -1.0e30;
  this->bounds.b[1].y = -1.0e30;
  this->bounds.b[1].x = -1.0e30;
}

// FUNC: public: void __thiscall rvDeclPlayback::Copy(class rvDeclPlayback *)
void __thiscall rvDeclPlayback::Copy(rvDeclPlayback *this, rvDeclPlayback *pb)
{
  float y; // edx
  float z; // eax
  idCurve_UniformCubicBSpline<idVec3> *p_points; // ebp
  int size; // edx
  int i; // eax

  this->flags = pb->flags & 0x1FFFFFFF;
  this->frameRate = pb->frameRate;
  this->duration = pb->duration;
  y = pb->origin.y;
  z = pb->origin.z;
  this->origin.x = pb->origin.x;
  p_points = &this->points;
  this->origin.y = y;
  this->origin.z = z;
  idCurve<idAngles>::operator=((int)&this->points, (int)&pb->points);
  p_points->boundaryType = pb->points.boundaryType;
  p_points->closeTime = pb->points.closeTime;
  p_points->order = pb->points.order;
  idCurve<idAngles>::operator=((int)&this->angles, (int)&pb->angles);
  this->angles.boundaryType = pb->angles.boundaryType;
  this->angles.closeTime = pb->angles.closeTime;
  this->angles.order = pb->angles.order;
  if ( this->buttons.list )
    Memory::Free(this->buttons.list);
  this->buttons.num = 0;
  this->buttons.size = 0;
  this->buttons.list = 0;
  this->buttons.num = pb->buttons.num;
  size = pb->buttons.size;
  this->buttons.size = size;
  this->buttons.granularity = pb->buttons.granularity;
  if ( size )
  {
    this->buttons.list = (rvButtonState *)Memory::Allocate(8 * size);
    for ( i = 0; i < this->buttons.num; ++i )
      this->buttons.list[i] = pb->buttons.list[i];
  }
}

// FUNC: public: bool __thiscall rvDeclPlayback::Finish(float)
char __thiscall rvDeclPlayback::Finish(rvDeclPlayback *this, float desiredDuration)
{
  float frameRate; // edx
  float x; // eax
  float y; // ecx
  float z; // edx
  double v7; // st7
  unsigned __int8 state; // dl
  int v9; // ebx
  rvButtonState *list; // eax
  int granularity; // eax
  bool v12; // cc
  int i; // eax
  rvButtonState *v14; // ecx
  int num; // ebp
  int size; // ecx
  int v17; // ecx
  rvButtonState *v18; // edi
  int j; // eax
  rvButtonState *v20; // ecx
  int v21; // eax
  rvButtonState *v22; // ecx
  double v23; // st7
  idCurve_UniformCubicBSpline<idVec3>_vtbl *v24; // edx
  double v25; // st6
  double v26; // st7
  double v27; // st6
  int count; // [esp+10h] [ebp-120h]
  float counta; // [esp+10h] [ebp-120h]
  float oldTime; // [esp+14h] [ebp-11Ch]
  float oldTimea; // [esp+14h] [ebp-11Ch]
  int v33; // [esp+18h] [ebp-118h]
  float speed; // [esp+20h] [ebp-110h]
  float v35[3]; // [esp+24h] [ebp-10Ch] BYREF
  rvDeclPlayback temp; // [esp+30h] [ebp-100h] BYREF
  rvDeclPlaybackData pbd; // [esp+E8h] [ebp-48h] BYREF
  int v38; // [esp+12Ch] [ebp-4h]

  rvDeclPlayback::rvDeclPlayback(&temp);
  v38 = 0;
  rvDeclPlayback::SetOrigin(this);
  rvDeclPlayback::operator=((int)&temp, this);
  this->base->MakeDefault(this->base);
  frameRate = temp.frameRate;
  x = temp.origin.x;
  this->flags = temp.flags;
  y = temp.origin.y;
  this->frameRate = frameRate;
  z = temp.origin.z;
  this->origin.x = x;
  HIWORD(v33) = HIWORD(y);
  this->origin.y = y;
  this->origin.z = z;
  if ( desiredDuration >= 0.0 )
  {
    v7 = temp.duration / desiredDuration;
    this->duration = desiredDuration;
    speed = v7;
  }
  else
  {
    this->duration = temp.duration;
    speed = 1.0;
  }
  state = 0;
  v9 = 0;
  count = temp.buttons.num;
  if ( temp.buttons.num > 0 )
  {
    list = temp.buttons.list;
    do
    {
      if ( list[v9].state != state || list[v9].impulse )
      {
        LOWORD(v33) = *(_WORD *)&list[v9].state;
        oldTime = list[v9].time / speed;
        if ( !this->buttons.list )
        {
          granularity = this->buttons.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->buttons.size )
            {
              v12 = granularity < this->buttons.num;
              this->buttons.size = granularity;
              if ( v12 )
                this->buttons.num = granularity;
              this->buttons.list = (rvButtonState *)Memory::Allocate(8 * granularity);
              for ( i = 0; i < this->buttons.num; ++i )
              {
                v14 = this->buttons.list;
                v14[i].time = *(float *)(8 * i);
                *(_DWORD *)&v14[i].state = *(_DWORD *)(8 * i + 4);
              }
            }
          }
          else
          {
            this->buttons.list = 0;
            this->buttons.num = 0;
            this->buttons.size = 0;
          }
        }
        num = this->buttons.num;
        size = this->buttons.size;
        if ( num == size )
        {
          if ( !this->buttons.granularity )
            this->buttons.granularity = 16;
          v17 = this->buttons.granularity + size - (this->buttons.granularity + size) % this->buttons.granularity;
          if ( v17 > 0 )
          {
            if ( v17 != this->buttons.size )
            {
              v18 = this->buttons.list;
              this->buttons.size = v17;
              if ( v17 < num )
                this->buttons.num = v17;
              this->buttons.list = (rvButtonState *)Memory::Allocate(8 * v17);
              for ( j = 0; j < this->buttons.num; ++j )
              {
                v20 = this->buttons.list;
                v20[j].time = v18[j].time;
                *(_DWORD *)&v20[j].state = *(_DWORD *)&v18[j].state;
              }
              if ( v18 )
                Memory::Free(v18);
            }
          }
          else
          {
            if ( this->buttons.list )
              Memory::Free(this->buttons.list);
            this->buttons.list = 0;
            this->buttons.num = 0;
            this->buttons.size = 0;
          }
        }
        v21 = this->buttons.num;
        v22 = this->buttons.list;
        v22[v21].time = oldTime;
        *(_DWORD *)&v22[v21].state = v33;
        ++this->buttons.num;
        list = temp.buttons.list;
        state = temp.buttons.list[v9].state;
      }
      ++v9;
    }
    while ( v9 < count );
  }
  oldTimea = 0.0;
  counta = 0.0;
  if ( temp.duration >= 0.0 )
  {
    do
    {
      rvDeclPlayback::GetCurrentData(&temp, 3, oldTimea, 0.0, &pbd);
      v23 = pbd.position.z - this->origin.z;
      v24 = this->points.__vftable;
      v25 = pbd.position.y - this->origin.y;
      v35[0] = pbd.position.x - this->origin.x;
      v35[1] = v25;
      v35[2] = v23;
      v24->AddValue(&this->points, COERCE_FLOAT(LODWORD(counta)), (const idVec3 *)v35);
      ((void (__thiscall *)(idCurve_UniformCubicBSpline<idAngles> *, _DWORD, idAngles *))this->angles.AddValue)(
        &this->angles,
        LODWORD(counta),
        &pbd.angles);
      v26 = 1.0 / this->frameRate;
      v27 = speed * v26 + oldTimea;
      oldTimea = v27;
      counta = v26 + counta;
    }
    while ( v27 <= temp.duration );
  }
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 76))(*(_DWORD *)common.ip);
  v38 = -1;
  rvDeclPlayback::~rvDeclPlayback(&temp);
  return 1;
}

// FUNC: public: virtual bool __thiscall rvDeclPlaybackEditLocal::Finish(class rvDeclPlayback *,float)
char __thiscall rvDeclPlaybackEditLocal::Finish(
        rvDeclPlaybackEditLocal *this,
        rvDeclPlayback *edit,
        float desiredDuration)
{
  return rvDeclPlayback::Finish(edit, desiredDuration);
}

// FUNC: public: virtual void __thiscall rvDeclPlaybackEditLocal::Copy(class rvDeclPlayback *,class rvDeclPlayback *)
void __thiscall rvDeclPlaybackEditLocal::Copy(
        rvDeclPlaybackEditLocal *this,
        rvDeclPlayback *edit,
        rvDeclPlayback *copy)
{
  rvDeclPlayback::Copy(edit, copy);
}
