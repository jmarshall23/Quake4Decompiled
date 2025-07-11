
// FUNC: public: __thiscall rvDeclLipSync::rvDeclLipSync(void)
void __thiscall rvDeclLipSync::rvDeclLipSync(rvDeclLipSync *this)
{
  idDict *p_mLipSyncData; // edi
  idKeyValue *list; // ebp
  int num; // ecx
  int v4; // eax
  int i; // eax
  idKeyValue *v6; // ecx
  idHashIndex *p_argHash; // [esp+10h] [ebp-18h]

  this->base = 0;
  this->__vftable = (rvDeclLipSync_vtbl *)&rvDeclLipSync::`vftable';
  this->mDescription.len = 0;
  this->mDescription.alloced = 20;
  this->mDescription.data = this->mDescription.baseBuffer;
  this->mDescription.baseBuffer[0] = 0;
  this->mTranscribeText.len = 0;
  this->mTranscribeText.alloced = 20;
  this->mTranscribeText.data = this->mTranscribeText.baseBuffer;
  this->mTranscribeText.baseBuffer[0] = 0;
  this->mHMM.len = 0;
  this->mHMM.alloced = 20;
  this->mHMM.data = this->mHMM.baseBuffer;
  this->mHMM.baseBuffer[0] = 0;
  p_mLipSyncData = &this->mLipSyncData;
  this->mLipSyncData.args.granularity = 16;
  this->mLipSyncData.args.list = 0;
  this->mLipSyncData.args.num = 0;
  this->mLipSyncData.args.size = 0;
  p_argHash = &this->mLipSyncData.argHash;
  idHashIndex::Init(&this->mLipSyncData.argHash, 1024, 1024);
  p_mLipSyncData->args.granularity = 16;
  list = p_mLipSyncData->args.list;
  if ( list )
  {
    num = p_mLipSyncData->args.num;
    v4 = p_mLipSyncData->args.num + 15 - (p_mLipSyncData->args.num + 15) % 16;
    if ( v4 != p_mLipSyncData->args.size )
    {
      if ( v4 > 0 )
      {
        p_mLipSyncData->args.size = v4;
        if ( v4 < num )
          p_mLipSyncData->args.num = v4;
        p_mLipSyncData->args.list = (idKeyValue *)Memory::Allocate(8 * v4);
        for ( i = 0; i < p_mLipSyncData->args.num; ++i )
        {
          v6 = p_mLipSyncData->args.list;
          v6[i].key = list[i].key;
          v6[i].value = list[i].value;
        }
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        p_mLipSyncData->args.list = 0;
        p_mLipSyncData->args.num = 0;
        p_mLipSyncData->args.size = 0;
      }
    }
  }
  p_mLipSyncData->argHash.granularity = 16;
  idHashIndex::Free(p_argHash);
  p_argHash->indexSize = 16;
  p_argHash->hashSize = 128;
}

// FUNC: public: virtual __thiscall rvDeclLipSync::~rvDeclLipSync(void)
void __thiscall rvDeclLipSync::~rvDeclLipSync(rvDeclLipSync *this)
{
  idDict *p_mLipSyncData; // esi
  idKeyValue *list; // eax

  this->__vftable = (rvDeclLipSync_vtbl *)&rvDeclLipSync::`vftable';
  p_mLipSyncData = &this->mLipSyncData;
  idDict::Clear(&this->mLipSyncData);
  idHashIndex::Free(&p_mLipSyncData->argHash);
  list = p_mLipSyncData->args.list;
  if ( list )
    Memory::Free(list);
  p_mLipSyncData->args.list = 0;
  p_mLipSyncData->args.num = 0;
  p_mLipSyncData->args.size = 0;
  idStr::FreeData(&this->mHMM);
  idStr::FreeData(&this->mTranscribeText);
  idStr::FreeData(&this->mDescription);
  this->__vftable = (rvDeclLipSync_vtbl *)&idDecl::`vftable';
}
