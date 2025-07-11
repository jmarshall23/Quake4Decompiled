
// FUNC: public: virtual bool __thiscall idListGUILocal::IsConfigured(void)const
BOOL __thiscall idListGUILocal::IsConfigured(idListGUILocal *this)
{
  return this->m_pGUI != 0;
}

// FUNC: private: void __thiscall idListGUILocal::StateChanged(void)
void __usercall idListGUILocal::StateChanged(idListGUILocal *this@<ecx>, int a2@<ebp>, int a3@<edi>)
{
  int v4; // ebp
  idUserInterface *m_pGUI; // edi
  idUserInterface_vtbl *v6; // ebx
  char *v7; // eax
  idUserInterface_vtbl *v8; // edi
  char *v9; // eax
  int v10; // edi
  int v11; // ebx
  idUserInterface_vtbl *v12; // ebp
  char *v13; // eax
  int i; // edi
  idUserInterface_vtbl *v15; // ebx
  char *v16; // eax
  int j; // edi
  char *v18; // eax
  idUserInterface_vtbl *v19; // ebx
  char *v20; // eax
  char *v21; // eax
  char *data; // [esp+Ch] [ebp-10h]
  int v23; // [esp+20h] [ebp+4h]

  if ( this->m_stateUpdates )
  {
    v4 = ((int (__thiscall *)(idListGUILocal *, int, int))this->Num)(this, a3, a2);
    v23 = v4;
    if ( v4 > 0 )
    {
      m_pGUI = this->m_pGUI;
      v6 = m_pGUI->__vftable;
      v7 = va("%s_sel_0", this->m_name.data);
      if ( v6->GetStateInt(m_pGUI, v7, "0") >= v4 )
      {
        v8 = this->m_pGUI->__vftable;
        v9 = va("%s_sel_0", this->m_name.data);
        v8->SetStateInt(this->m_pGUI, v9, v4 - 1);
      }
    }
    v10 = 0;
    if ( v4 > 0 )
    {
      v11 = 0;
      do
      {
        v12 = this->m_pGUI->__vftable;
        data = this->list[v11].data;
        v13 = va("%s_item_%i", this->m_name.data, v10);
        v12->SetStateString(this->m_pGUI, v13, data);
        v4 = v23;
        ++v10;
        ++v11;
      }
      while ( v10 < v23 );
    }
    for ( i = v4; i < this->m_water; ++i )
    {
      v15 = this->m_pGUI->__vftable;
      v16 = va("%s_item_%i", this->m_name.data, i);
      v15->SetStateString(this->m_pGUI, v16, &entityFilter);
    }
    for ( j = 0; j < v4; ++j )
    {
      v18 = this->m_name.data;
      v19 = this->m_pGUI->__vftable;
      if ( this->m_greyed.list[j] )
      {
        v21 = va("%s_item_%i_greyed", v18, j);
        v19->SetStateBool(this->m_pGUI, v21, 1);
      }
      else
      {
        v20 = va("%s_item_%i_greyed", v18, j);
        v19->DeleteStateVar(this->m_pGUI, v20);
      }
    }
    this->m_water = v4;
    this->m_pGUI->StateChanged(this->m_pGUI, com_frameTime, 0);
  }
}

// FUNC: public: virtual int __thiscall idListGUILocal::GetNumSelections(void)
int __thiscall idListGUILocal::GetNumSelections(idListGUILocal *this)
{
  const char *v2; // edi
  idDict *v3; // eax
  const idKeyValue *Key; // eax

  v2 = va("%s_numsel", this->m_name.data);
  v3 = (idDict *)this->m_pGUI->State(this->m_pGUI);
  Key = idDict::FindKey(v3, v2);
  if ( Key )
    return atoi(Key->value->data);
  else
    return atoi("0");
}

// FUNC: public: virtual void __thiscall idListGUILocal::SetSelection(int)
void __userpurge idListGUILocal::SetSelection(idListGUILocal *this@<ecx>, int a2@<ebp>, int sel)
{
  idUserInterface_vtbl *v4; // edi
  char *v5; // eax

  v4 = this->m_pGUI->__vftable;
  v5 = va("%s_sel_0", this->m_name.data);
  v4->SetStateInt(this->m_pGUI, v5, sel);
  idListGUILocal::StateChanged(this, a2, (int)v4);
}

// FUNC: public: virtual void __thiscall idListGUILocal::SetStateChanges(bool)
void __userpurge idListGUILocal::SetStateChanges(idListGUILocal *this@<ecx>, int a2@<ebp>, int a3@<edi>, bool enable)
{
  this->m_stateUpdates = enable;
  idListGUILocal::StateChanged(this, a2, a3);
}

// FUNC: public: virtual void __thiscall idListGUILocal::Shutdown(void)
void __thiscall idListGUILocal::Shutdown(idListGUILocal *this)
{
  idStr *p_m_name; // esi

  p_m_name = &this->m_name;
  this->m_pGUI = 0;
  idStr::FreeData(&this->m_name);
  p_m_name->len = 0;
  p_m_name->alloced = 20;
  p_m_name->data = p_m_name->baseBuffer;
  p_m_name->baseBuffer[0] = 0;
  this->Clear(this);
}

// FUNC: public: virtual bool __thiscall idListGUILocal::Del(int)
char __userpurge idListGUILocal::Del@<al>(idListGUILocal *this@<ecx>, int a2@<edi>, int id)
{
  int num; // edx
  int v5; // eax
  int *i; // ecx
  int v8; // ecx
  bool v9; // cc
  int v10; // ecx
  int *list; // edx
  int v12; // esi
  int *v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  idStr *v17; // ecx
  unsigned int v18; // esi
  idStr *v19; // ebx
  int v20; // ecx
  int v21; // ecx
  bool *v22; // ecx
  int v23; // [esp+8h] [ebp-Ch]
  int v24; // [esp+Ch] [ebp-8h]
  int ida; // [esp+18h] [ebp+4h]

  num = this->m_ids.num;
  v5 = 0;
  if ( num <= 0 )
    return 0;
  for ( i = this->m_ids.list; *i != id; ++i )
  {
    if ( ++v5 >= num )
      return 0;
  }
  v23 = v5;
  if ( v5 == -1 )
    return 0;
  if ( v5 >= 0 )
  {
    v8 = this->m_ids.num;
    if ( v5 < v8 )
    {
      v9 = v5 < v8 - 1;
      this->m_ids.num = v8 - 1;
      v10 = v5;
      if ( v9 )
      {
        do
        {
          list = this->m_ids.list;
          v12 = list[v10 + 1];
          v13 = &list[v10++];
          *v13 = v12;
        }
        while ( v10 < this->m_ids.num );
      }
    }
    v14 = this->num;
    if ( v5 < v14 )
    {
      v15 = v14 - 1;
      this->num = v15;
      v24 = v5;
      if ( v5 < v15 )
      {
        v16 = 32 * v5;
        for ( ida = v16; ; v16 = ida )
        {
          v17 = this->list;
          v18 = *(int *)((char *)&v17[1].len + v16);
          v19 = (idStr *)((char *)v17 + v16);
          if ( (signed int)(v18 + 1) > *(int *)((char *)&v17->alloced + v16) )
            idStr::ReAllocate(v19, v18 + 1, 0);
          ida += 32;
          qmemcpy(v19->data, v19[1].data, v18);
          v19->data[v18] = 0;
          v19->len = v18;
          if ( ++v24 >= this->num )
            break;
        }
        v5 = v23;
      }
    }
    if ( v5 >= 0 )
    {
      v20 = this->m_greyed.num;
      if ( v5 < v20 )
      {
        v21 = v20 - 1;
        for ( this->m_greyed.num = v21; v5 < this->m_greyed.num; *v22 = v22[1] )
          v22 = &this->m_greyed.list[v5++];
      }
    }
  }
  idListGUILocal::StateChanged(this, (int)this, a2);
  return 1;
}

// FUNC: public: virtual void __thiscall idListGUILocal::Clear(void)
void __thiscall idListGUILocal::Clear(idListGUILocal *this)
{
  idStr *list; // eax
  char *v3; // ebx

  if ( this->m_ids.list )
    Memory::Free(this->m_ids.list);
  this->m_ids.list = 0;
  this->m_ids.num = 0;
  this->m_ids.size = 0;
  list = this->list;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->list = 0;
  this->num = 0;
  this->size = 0;
  if ( this->m_greyed.list )
    Memory::Free(this->m_greyed.list);
  this->m_greyed.list = 0;
  this->m_greyed.num = 0;
  this->m_greyed.size = 0;
  if ( this->m_pGUI )
    idListGUILocal::StateChanged(this);
}

// FUNC: public: virtual void __thiscall idListGUILocal::Add(int,class idStr const &,bool)
void __thiscall idListGUILocal::Add(idListGUILocal *this, int id, const idStr *s, bool greyed)
{
  int num; // ecx
  int v6; // eax
  int *list; // edx
  int size; // ecx
  idStr *v10; // ebx
  int len; // esi
  int v12; // eax
  int granularity; // eax
  bool v14; // cc
  int i; // eax
  int v16; // edi
  int v17; // eax
  int v18; // ecx
  int *v19; // esi
  int j; // eax
  int v21; // eax
  int k; // eax
  int v23; // edi
  int v24; // eax
  int v25; // ecx
  bool *v26; // esi
  int m; // eax
  int v28; // esi
  idStr *v29; // ebx
  unsigned int v30; // ecx
  char *data; // esi
  char *v32; // edi
  char v33; // al
  char *v34; // edi
  char *v35; // esi
  int v36; // ecx
  const idStr *sa; // [esp+18h] [ebp+8h]
  int greyeda; // [esp+1Ch] [ebp+Ch]

  num = this->m_ids.num;
  v6 = 0;
  if ( num <= 0 )
    goto LABEL_7;
  list = this->m_ids.list;
  while ( *list != id )
  {
    ++v6;
    ++list;
    if ( v6 >= num )
      goto LABEL_7;
  }
  if ( v6 == -1 )
  {
LABEL_7:
    if ( !this->list )
      idList<idStr>::Resize(&this->idList<idStr>, this->granularity);
    size = this->size;
    if ( this->num == size )
    {
      if ( !this->granularity )
        this->granularity = 16;
      idList<idStr>::Resize(
        &this->idList<idStr>,
        this->granularity + size - (this->granularity + size) % this->granularity);
    }
    v10 = &this->list[this->num];
    len = s->len;
    v12 = s->len + 1;
    sa = (const idStr *)s->len;
    if ( v12 > v10->alloced )
      idStr::ReAllocate(v10, v12, 0);
    qmemcpy(v10->data, s->data, len);
    *((_BYTE *)&sa->len + (unsigned int)v10->data) = 0;
    v10->len = (int)sa;
    ++this->num;
    if ( !this->m_ids.list )
    {
      granularity = this->m_ids.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->m_ids.size )
        {
          v14 = granularity < this->m_ids.num;
          this->m_ids.size = granularity;
          if ( v14 )
            this->m_ids.num = granularity;
          this->m_ids.list = (int *)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->m_ids.num; ++i )
            this->m_ids.list[i] = *(_DWORD *)(4 * i);
        }
      }
      else
      {
        this->m_ids.list = 0;
        this->m_ids.num = 0;
        this->m_ids.size = 0;
      }
    }
    v16 = this->m_ids.num;
    v17 = this->m_ids.size;
    if ( v16 == v17 )
    {
      if ( !this->m_ids.granularity )
        this->m_ids.granularity = 16;
      v18 = v17 + this->m_ids.granularity - (v17 + this->m_ids.granularity) % this->m_ids.granularity;
      if ( v18 > 0 )
      {
        if ( v18 != this->m_ids.size )
        {
          v19 = this->m_ids.list;
          this->m_ids.size = v18;
          if ( v18 < v16 )
            this->m_ids.num = v18;
          this->m_ids.list = (int *)Memory::Allocate(4 * v18);
          for ( j = 0; j < this->m_ids.num; ++j )
            this->m_ids.list[j] = v19[j];
          if ( v19 )
            Memory::Free(v19);
        }
      }
      else
      {
        if ( this->m_ids.list )
          Memory::Free(this->m_ids.list);
        this->m_ids.list = 0;
        this->m_ids.num = 0;
        this->m_ids.size = 0;
      }
    }
    this->m_ids.list[this->m_ids.num++] = id;
    if ( !this->m_greyed.list )
    {
      v21 = this->m_greyed.granularity;
      if ( v21 > 0 )
      {
        if ( v21 != this->m_greyed.size )
        {
          v14 = v21 < this->m_greyed.num;
          this->m_greyed.size = v21;
          if ( v14 )
            this->m_greyed.num = v21;
          this->m_greyed.list = (bool *)Memory::Allocate(v21);
          for ( k = 0; k < this->m_greyed.num; ++k )
            this->m_greyed.list[k] = *(_BYTE *)k;
        }
      }
      else
      {
        this->m_greyed.list = 0;
        this->m_greyed.num = 0;
        this->m_greyed.size = 0;
      }
    }
    v23 = this->m_greyed.num;
    v24 = this->m_greyed.size;
    if ( v23 == v24 )
    {
      if ( !this->m_greyed.granularity )
        this->m_greyed.granularity = 16;
      v25 = v24 + this->m_greyed.granularity - (v24 + this->m_greyed.granularity) % this->m_greyed.granularity;
      if ( v25 > 0 )
      {
        if ( v25 != this->m_greyed.size )
        {
          v26 = this->m_greyed.list;
          this->m_greyed.size = v25;
          if ( v25 < v23 )
            this->m_greyed.num = v25;
          this->m_greyed.list = (bool *)Memory::Allocate(v25);
          for ( m = 0; m < this->m_greyed.num; ++m )
            this->m_greyed.list[m] = v26[m];
          if ( v26 )
            Memory::Free(v26);
        }
      }
      else
      {
        if ( this->m_greyed.list )
          Memory::Free(this->m_greyed.list);
        this->m_greyed.list = 0;
        this->m_greyed.num = 0;
        this->m_greyed.size = 0;
      }
    }
    this->m_greyed.list[this->m_greyed.num++] = greyed;
    idListGUILocal::StateChanged(this, (int)this, v23);
  }
  else
  {
    v28 = s->len;
    greyeda = s->len;
    v29 = &this->list[v6];
    if ( s->len + 1 > v29->alloced )
      idStr::ReAllocate(v29, v28 + 1, 0);
    v30 = v28;
    data = s->data;
    v32 = v29->data;
    v33 = v30;
    v30 >>= 2;
    qmemcpy(v32, data, 4 * v30);
    v35 = &data[4 * v30];
    v34 = &v32[4 * v30];
    v36 = v33 & 3;
    qmemcpy(v34, v35, v36);
    v29->data[greyeda] = 0;
    v29->len = greyeda;
    idListGUILocal::StateChanged(this, (int)this, (int)&v34[v36]);
  }
}

// FUNC: public: virtual void __thiscall idListGUILocal::Push(class idStr const &,bool)
void __thiscall idListGUILocal::Push(idListGUILocal *this, const idStr *s, bool greyed)
{
  idList<idStr> *v4; // esi
  int size; // ecx
  idStr *v7; // ebx
  int len; // esi
  int v9; // eax
  int num; // ebx
  int granularity; // eax
  bool v12; // cc
  int i; // eax
  int v14; // edi
  int v15; // eax
  int v16; // ecx
  int *list; // esi
  int j; // eax
  int v19; // eax
  int k; // eax
  int v21; // edi
  int v22; // eax
  int v23; // ecx
  bool *v24; // esi
  int m; // eax
  const idStr *sa; // [esp+14h] [ebp+4h]

  v4 = &this->idList<idStr>;
  if ( !this->list )
    idList<idStr>::Resize(&this->idList<idStr>, this->granularity);
  size = v4->size;
  if ( v4->num == size )
  {
    if ( !v4->granularity )
      v4->granularity = 16;
    idList<idStr>::Resize(v4, v4->granularity + size - (v4->granularity + size) % v4->granularity);
  }
  v7 = &v4->list[v4->num];
  len = s->len;
  v9 = s->len + 1;
  sa = (const idStr *)s->len;
  if ( v9 > v7->alloced )
    idStr::ReAllocate(v7, v9, 0);
  qmemcpy(v7->data, s->data, len);
  *((_BYTE *)&sa->len + (unsigned int)v7->data) = 0;
  v7->len = (int)sa;
  ++this->num;
  num = this->m_ids.num;
  if ( !this->m_ids.list )
  {
    granularity = this->m_ids.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->m_ids.size )
      {
        v12 = granularity < this->m_ids.num;
        this->m_ids.size = granularity;
        if ( v12 )
          this->m_ids.num = granularity;
        this->m_ids.list = (int *)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->m_ids.num; ++i )
          this->m_ids.list[i] = *(_DWORD *)(4 * i);
      }
    }
    else
    {
      this->m_ids.list = 0;
      this->m_ids.num = 0;
      this->m_ids.size = 0;
    }
  }
  v14 = this->m_ids.num;
  v15 = this->m_ids.size;
  if ( v14 == v15 )
  {
    if ( !this->m_ids.granularity )
      this->m_ids.granularity = 16;
    v16 = v15 + this->m_ids.granularity - (v15 + this->m_ids.granularity) % this->m_ids.granularity;
    if ( v16 > 0 )
    {
      if ( v16 != this->m_ids.size )
      {
        list = this->m_ids.list;
        this->m_ids.size = v16;
        if ( v16 < v14 )
          this->m_ids.num = v16;
        this->m_ids.list = (int *)Memory::Allocate(4 * v16);
        for ( j = 0; j < this->m_ids.num; ++j )
          this->m_ids.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->m_ids.list )
        Memory::Free(this->m_ids.list);
      this->m_ids.list = 0;
      this->m_ids.num = 0;
      this->m_ids.size = 0;
    }
  }
  this->m_ids.list[this->m_ids.num++] = num;
  if ( !this->m_greyed.list )
  {
    v19 = this->m_greyed.granularity;
    if ( v19 > 0 )
    {
      if ( v19 != this->m_greyed.size )
      {
        v12 = v19 < this->m_greyed.num;
        this->m_greyed.size = v19;
        if ( v12 )
          this->m_greyed.num = v19;
        this->m_greyed.list = (bool *)Memory::Allocate(v19);
        for ( k = 0; k < this->m_greyed.num; ++k )
          this->m_greyed.list[k] = *(_BYTE *)k;
      }
    }
    else
    {
      this->m_greyed.list = 0;
      this->m_greyed.num = 0;
      this->m_greyed.size = 0;
    }
  }
  v21 = this->m_greyed.num;
  v22 = this->m_greyed.size;
  if ( v21 == v22 )
  {
    if ( !this->m_greyed.granularity )
      this->m_greyed.granularity = 16;
    v23 = v22 + this->m_greyed.granularity - (v22 + this->m_greyed.granularity) % this->m_greyed.granularity;
    if ( v23 > 0 )
    {
      if ( v23 != this->m_greyed.size )
      {
        v24 = this->m_greyed.list;
        this->m_greyed.size = v23;
        if ( v23 < v21 )
          this->m_greyed.num = v23;
        this->m_greyed.list = (bool *)Memory::Allocate(v23);
        for ( m = 0; m < this->m_greyed.num; ++m )
          this->m_greyed.list[m] = v24[m];
        if ( v24 )
          Memory::Free(v24);
      }
    }
    else
    {
      if ( this->m_greyed.list )
        Memory::Free(this->m_greyed.list);
      this->m_greyed.list = 0;
      this->m_greyed.num = 0;
      this->m_greyed.size = 0;
    }
  }
  this->m_greyed.list[this->m_greyed.num++] = greyed;
  idListGUILocal::StateChanged(this, (int)this, v21);
}
