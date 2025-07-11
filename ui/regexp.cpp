
// FUNC: public: void __thiscall idRegister::SetToRegs(float *)
void __thiscall idRegister::SetToRegs(idRegister *this, float *registers)
{
  idWinVar *var; // eax
  float *v4; // eax
  float v5; // edx
  float v6; // ecx
  float v7; // edx
  double v8; // st7
  int v9; // eax
  unsigned __int16 *regs; // ecx
  float v11; // ebx
  float v3_4; // [esp+8h] [ebp-18h]
  float v3_8; // [esp+Ch] [ebp-14h]
  idVec4 v; // [esp+10h] [ebp-10h]

  if ( this->enabled )
  {
    var = this->var;
    if ( var )
    {
      if ( !var->guiDict && var->eval )
      {
        switch ( this->type )
        {
          case 0:
          case 7:
            v4 = (float *)&var[1];
            v5 = v4[1];
            v.x = *v4;
            v6 = v4[2];
            v.y = v5;
            v7 = v4[3];
            v.z = v6;
            v.w = v7;
            break;
          case 1:
            LODWORD(v.x) = var[1].__vftable;
            break;
          case 2:
            v.x = (float)LOBYTE(var[1].__vftable);
            break;
          case 3:
            v.x = (float)(int)var[1].__vftable;
            break;
          case 5:
            v3_4 = *(float *)&var[1].guiDict;
            LODWORD(v.x) = var[1].__vftable;
            v.y = v3_4;
            break;
          case 6:
            v8 = *(float *)&var[1].guiDict;
            v3_8 = *(float *)&var[1].name;
            v.x = *(float *)&var[1].__vftable;
            v.z = v3_8;
            v.y = v8;
            break;
          default:
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
              common.type,
              "idRegister::SetToRegs: bad reg type");
            break;
        }
        v9 = 0;
        if ( this->regCount > 0 )
        {
          regs = this->regs;
          do
          {
            v11 = *(&v.x + v9++);
            registers[*regs++] = v11;
          }
          while ( v9 < this->regCount );
        }
      }
    }
  }
}

// FUNC: public: void __thiscall idRegister::GetFromRegs(float *)
void __thiscall idRegister::GetFromRegs(idRegister *this, float *registers)
{
  idRegister *v2; // edi
  bool v3; // zf
  idWinFloat *var; // ecx
  int regCount; // ebp
  int v6; // ebx
  float *v7; // esi
  unsigned __int16 *v8; // eax
  unsigned int v9; // edi
  float *p_z; // edx
  unsigned __int16 *v11; // eax
  idWinVec4 *v12; // eax
  idWinRectangle *v13; // [esp+4h] [ebp-28h]
  int other; // [esp+8h] [ebp-24h] BYREF
  idVec4 v; // [esp+Ch] [ebp-20h] BYREF
  idRectangle rect; // [esp+1Ch] [ebp-10h] BYREF

  v2 = this;
  v3 = !this->enabled;
  other = (int)this;
  memset(&rect, 0, sizeof(rect));
  if ( !v3 )
  {
    var = (idWinFloat *)this->var;
    v13 = (idWinRectangle *)v2->var;
    if ( var )
    {
      if ( !var->guiDict && var->eval )
      {
        regCount = v2->regCount;
        v6 = 0;
        v7 = registers;
        if ( regCount >= 4 )
        {
          v8 = &v2->regs[1];
          v9 = ((unsigned int)(regCount - 4) >> 2) + 1;
          p_z = &v.z;
          v6 = 4 * v9;
          do
          {
            *(p_z - 2) = v7[*(v8 - 1)];
            *(p_z - 1) = v7[*v8];
            *p_z = v7[v8[1]];
            p_z[1] = v7[v8[2]];
            v8 += 4;
            p_z += 4;
            --v9;
          }
          while ( v9 );
          var = (idWinFloat *)v13;
          v2 = (idRegister *)other;
        }
        if ( v6 < regCount )
        {
          v11 = &v2->regs[v6];
          do
            *(&v.x + v6++) = v7[*v11++];
          while ( v6 < regCount );
        }
        switch ( v2->type )
        {
          case 0:
            v12 = (idWinVec4 *)__RTDynamicCast(
                                 var,
                                 0,
                                 &idWinVar `RTTI Type Descriptor',
                                 &idWinVec4 `RTTI Type Descriptor',
                                 0);
            idWinVec4::operator=(v12, &v);
            break;
          case 1:
            idWinFloat::operator=(var, &v.x);
            break;
          case 2:
            LOBYTE(registers) = v.x != 0.0;
            idWinBool::operator=((idWinBool *)var, (bool *)&registers);
            break;
          case 3:
            other = (int)v.x;
            idWinInt::operator=((idWinInt *)var, &other);
            break;
          case 5:
            idWinVec2::operator=((idWinVec2 *)var, (const idVec2 *)&v);
            break;
          case 6:
            idWinVec3::operator=((idWinVec3 *)var, (const idVec3 *)&v);
            break;
          case 7:
            rect = (idRectangle)v;
            idWinRectangle::operator=((idWinRectangle *)var, &rect);
            break;
          default:
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
              common.type,
              "idRegister::GetFromRegs: bad reg type");
            break;
        }
      }
    }
  }
}

// FUNC: public: void __thiscall idRegister::WriteToSaveGame(class idFile *)
void __thiscall idRegister::WriteToSaveGame(idRegister *this, idFile *savefile)
{
  idFile *v2; // esi
  idFile_vtbl *v4; // edx

  v2 = savefile;
  savefile->Write(savefile, this, 1);
  v2->Write(v2, &this->type, 2);
  v2->Write(v2, &this->regCount, 4);
  v2->Write(v2, this->regs, 8);
  v4 = v2->__vftable;
  savefile = (idFile *)this->name.len;
  v4->Write(v2, &savefile, 4);
  v2->Write(v2, this->name.data, (int)savefile);
  this->var->WriteToSaveGame(this->var, v2);
}

// FUNC: public: void __thiscall idRegister::ReadFromSaveGame(class idFile *)
void __thiscall idRegister::ReadFromSaveGame(idRegister *this, idFile *savefile)
{
  idFile *v2; // esi
  idFile *v4; // edi

  v2 = savefile;
  savefile->Read(savefile, this, 1);
  v2->Read(v2, &this->type, 2);
  v2->Read(v2, &this->regCount, 4);
  v2->Read(v2, this->regs, 8);
  v2->Read(v2, &savefile, 4);
  v4 = savefile;
  if ( (int)&savefile->__vftable + 1 > this->name.alloced )
    idStr::ReAllocate(&this->name, (int)&savefile->__vftable + 1, 1);
  this->name.len = (int)v4;
  memset(this->name.data, 0x20u, (unsigned int)v4);
  this->name.data[this->name.len] = 0;
  v2->Read(v2, this->name.data, (int)savefile);
  this->var->ReadFromSaveGame(this->var, v2);
}

// FUNC: public: void __thiscall idRegisterList::GetFromRegs(float *)
void __thiscall idRegisterList::GetFromRegs(idRegisterList *this, float *registers)
{
  int i; // esi

  for ( i = 0; i < this->regs.num; ++i )
    idRegister::GetFromRegs(this->regs.list[i], registers);
}

// FUNC: public: void __thiscall idRegisterList::SetToRegs(float *)
void __thiscall idRegisterList::SetToRegs(idRegisterList *this, float *registers)
{
  int i; // esi

  for ( i = 0; i < this->regs.num; ++i )
    idRegister::SetToRegs(this->regs.list[i], registers);
}

// FUNC: public: void __thiscall idRegisterList::WriteToSaveGame(class idFile *)
void __thiscall idRegisterList::WriteToSaveGame(idRegisterList *this, idFile *savefile)
{
  idFile_vtbl *v2; // edx
  int i; // esi
  int num; // [esp+Ch] [ebp-4h] BYREF

  v2 = savefile->__vftable;
  num = this->regs.num;
  v2->Write(savefile, &num, 4);
  for ( i = 0; i < num; ++i )
    idRegister::WriteToSaveGame(this->regs.list[i], savefile);
}

// FUNC: public: void __thiscall idRegisterList::ReadFromSaveGame(class idFile *)
void __thiscall idRegisterList::ReadFromSaveGame(idRegisterList *this, idFile *savefile)
{
  idFile *v2; // edi
  int i; // esi

  v2 = savefile;
  savefile->Read(savefile, &savefile, 4);
  for ( i = 0; i < (int)savefile; ++i )
    idRegister::ReadFromSaveGame(this->regs.list[i], v2);
}

// FUNC: public: class idRegister * __thiscall idRegisterList::FindReg(char const *)
idRegister *__thiscall idRegisterList::FindReg(idRegisterList *this, const char *name)
{
  unsigned __int8 v2; // al
  int v3; // esi
  const char *i; // ecx
  int v6; // edx
  int v7; // esi

  v2 = *name;
  v3 = 0;
  for ( i = name; v2; v3 += v6 )
  {
    if ( idStr::lowerCaseCharacter[v2] )
      v2 = idStr::lowerCaseCharacter[v2];
    v6 = (char)v2 * (_DWORD)&i[119 - (_DWORD)name];
    v2 = *++i;
  }
  v7 = this->regHash.hash[v3 & this->regHash.hashMask & this->regHash.lookupMask];
  if ( v7 == -1 )
    return 0;
  while ( idStr::Icmp(this->regs.list[v7]->name.data, name) )
  {
    v7 = this->regHash.indexChain[v7 & this->regHash.lookupMask];
    if ( v7 == -1 )
      return 0;
  }
  return this->regs.list[v7];
}

// FUNC: public: void __thiscall idRegisterList::AddReg(char const *,int,class idParser *,class idWindow *,class idWinVar *)
void __thiscall idRegisterList::AddReg(
        idRegisterList *this,
        char *name,
        int type,
        idParser *src,
        idWindow *win,
        idWinVar *var)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  char *v7; // ebx
  idRegister *Reg; // eax
  idRegister *v10; // eax
  idRegister *v11; // edi
  int v12; // ecx
  idRegister *v13; // eax
  char *v14; // eax
  int v15; // ebp
  unsigned __int16 *regs; // edi
  unsigned __int8 v17; // al
  idHashIndex *p_regHash; // edx
  int v19; // edi
  char *v20; // ecx
  int v21; // edx
  int granularity; // eax
  bool v23; // cc
  int i; // eax
  int num; // ebx
  int size; // ecx
  int v27; // ecx
  idRegister **list; // edi
  int j; // eax
  int v30; // esi
  int indexSize; // eax
  int v32; // eax
  int v33; // ebx
  int v34; // esi
  unsigned __int16 *v35; // edi
  int numRegs; // [esp+4h] [ebp-B8h]
  idHashIndex *numRegsa; // [esp+4h] [ebp-B8h]
  idRegister *v38; // [esp+8h] [ebp-B4h]
  int hash; // [esp+Ch] [ebp-B0h]
  idToken tok; // [esp+10h] [ebp-ACh] BYREF
  idToken token; // [esp+60h] [ebp-5Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v42; // [esp+B0h] [ebp-Ch]
  void *v43; // [esp+B4h] [ebp-8h]
  int v44; // [esp+B8h] [ebp-4h]

  v44 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v43 = &_ehhandler__AddReg_idRegisterList__QAEXPBDHPAVidParser__PAVidWindow__PAVidWinVar___Z;
  v42 = ExceptionList;
  v7 = name;
  Reg = idRegisterList::FindReg(this, name);
  if ( !Reg )
  {
    numRegs = idRegister::REGCOUNT[type];
    v10 = (idRegister *)Memory::Allocate(0x34u);
    v11 = v10;
    v44 = 0;
    if ( v10 )
    {
      v10->name.len = 0;
      v10->name.alloced = 20;
      v10->name.data = v10->name.baseBuffer;
      v10->name.baseBuffer[0] = 0;
      LOBYTE(v44) = 1;
      idStr::operator=(&v10->name, name);
      v11->type = type;
      v12 = idRegister::REGCOUNT[type];
      v13 = v11;
      v11->enabled = (_WORD)type != 4;
      v11->regCount = v12;
      v11->var = 0;
      v38 = v11;
    }
    else
    {
      v38 = 0;
      v13 = 0;
    }
    v44 = -1;
    v13->var = var;
    if ( type == 4 )
    {
      tok.floatvalue = 0.0;
      tok.len = 0;
      tok.alloced = 20;
      tok.data = tok.baseBuffer;
      tok.baseBuffer[0] = 0;
      v44 = 2;
      if ( idParser::ReadToken(src, &tok) )
      {
        v14 = (char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                        common.type,
                        tok.data,
                        -1);
        idStr::operator=(&tok, v14);
        var->Init(var, tok.data, win);
      }
      v44 = -1;
      idStr::FreeData(&tok);
    }
    else
    {
      v15 = 0;
      if ( numRegs > 0 )
      {
        regs = v13->regs;
        do
        {
          *regs = idWindow::ParseExpression(win, src, 0, 0);
          if ( v15 < numRegs - 1 )
            idParser::ExpectTokenString(src, ",");
          ++v15;
          ++regs;
        }
        while ( v15 < numRegs );
        v7 = name;
      }
    }
    v17 = *v7;
    p_regHash = &this->regHash;
    v19 = 0;
    numRegsa = &this->regHash;
    v20 = v7;
    if ( *v7 )
    {
      do
      {
        if ( idStr::lowerCaseCharacter[v17] )
          v17 = idStr::lowerCaseCharacter[v17];
        v21 = (char)v17 * (_DWORD)&v20[119 - (_DWORD)v7];
        v17 = *++v20;
        v19 += v21;
      }
      while ( v17 );
      p_regHash = &this->regHash;
    }
    hash = v19 & p_regHash->hashMask;
    if ( !this->regs.list )
    {
      granularity = this->regs.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->regs.size )
        {
          v23 = granularity < this->regs.num;
          this->regs.size = granularity;
          if ( v23 )
            this->regs.num = granularity;
          this->regs.list = (idRegister **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->regs.num; ++i )
            this->regs.list[i] = *(idRegister **)(4 * i);
          p_regHash = &this->regHash;
        }
      }
      else
      {
        this->regs.list = 0;
        this->regs.num = 0;
        this->regs.size = 0;
      }
    }
    num = this->regs.num;
    size = this->regs.size;
    if ( this->regs.num == size )
    {
      if ( !this->regs.granularity )
        this->regs.granularity = 16;
      v27 = this->regs.granularity + size - (this->regs.granularity + size) % this->regs.granularity;
      if ( v27 > 0 )
      {
        if ( v27 != this->regs.size )
        {
          list = this->regs.list;
          this->regs.size = v27;
          if ( v27 < num )
            this->regs.num = v27;
          this->regs.list = (idRegister **)Memory::Allocate(4 * v27);
          for ( j = 0; j < this->regs.num; ++j )
            this->regs.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->regs.list )
          Memory::Free(this->regs.list);
        this->regs.list = 0;
        this->regs.num = 0;
        this->regs.size = 0;
      }
      p_regHash = &this->regHash;
    }
    this->regs.list[this->regs.num++] = v38;
    v30 = this->regs.num - 1;
    if ( p_regHash->hash == idHashIndex::INVALID_INDEX )
    {
      indexSize = p_regHash->indexSize;
      if ( v30 >= indexSize )
        indexSize = v30 + 1;
      idHashIndex::Allocate(p_regHash, p_regHash->hashSize, indexSize);
    }
    else
    {
      if ( v30 < p_regHash->indexSize )
      {
LABEL_51:
        v32 = hash & p_regHash->hashMask;
        p_regHash->indexChain[v30] = p_regHash->hash[v32];
        p_regHash->hash[v32] = v30;
        return;
      }
      idHashIndex::ResizeIndex(p_regHash, v30 + 1);
    }
    p_regHash = numRegsa;
    goto LABEL_51;
  }
  v33 = idRegister::REGCOUNT[type];
  Reg->var = var;
  if ( type == 4 )
  {
    token.floatvalue = 0.0;
    token.len = 0;
    token.alloced = 20;
    token.data = token.baseBuffer;
    token.baseBuffer[0] = 0;
    v44 = 3;
    if ( idParser::ReadToken(src, &token) )
      var->Init(var, token.data, win);
    v44 = -1;
    idStr::FreeData(&token);
  }
  else
  {
    v34 = 0;
    if ( v33 > 0 )
    {
      v35 = Reg->regs;
      do
      {
        *v35 = idWindow::ParseExpression(win, src, 0, 0);
        if ( v34 < v33 - 1 )
          idParser::ExpectTokenString(src, ",");
        ++v34;
        ++v35;
      }
      while ( v34 < v33 );
    }
  }
}

// FUNC: public: void __thiscall idRegisterList::Reset(void)
void __thiscall idRegisterList::Reset(idRegisterList *this)
{
  int i; // edi
  idRegister **list; // eax
  idRegister *v4; // ebx
  int *hash; // edi

  for ( i = 0; i < this->regs.num; ++i )
  {
    list = this->regs.list;
    v4 = list[i];
    if ( v4 )
    {
      idRegister::~idRegister(list[i]);
      Memory::Free(v4);
    }
    this->regs.list[i] = 0;
  }
  if ( this->regs.list )
    Memory::Free(this->regs.list);
  this->regs.list = 0;
  this->regs.num = 0;
  this->regs.size = 0;
  hash = this->regHash.hash;
  if ( hash != idHashIndex::INVALID_INDEX )
    memset(hash, 0xFFu, 4 * this->regHash.hashSize);
}
