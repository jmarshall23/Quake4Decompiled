
// FUNC: public: virtual int __thiscall idCollisionModelManagerLocal::Contacts(struct contactInfo_t *,int,class idVec3 const &,class idVec6 const &,float,class idTraceModel const *,class idMat3 const &,int,class idCollisionModel *,class idVec3 const &,class idMat3 const &)
int __thiscall idCollisionModelManagerLocal::Contacts(
        idCollisionModelManagerLocal *this,
        contactInfo_t *contacts,
        int maxContacts,
        const idVec3 *start,
        const idVec6 *dir,
        float depth,
        const idTraceModel *trm,
        const idMat3 *trmAxis,
        int contentMask,
        idCollisionModel *model,
        const idVec3 *origin,
        const idMat3 *modelAxis)
{
  double v13; // st7
  double v14; // st7
  double v15; // st6
  idCollisionModelManagerLocal_vtbl *v16; // edx
  int result; // eax
  idVec3 end; // [esp+0h] [ebp-8Ch] BYREF
  float v19; // [esp+14h] [ebp-78h]
  trace_t results; // [esp+18h] [ebp-74h] BYREF

  this->maxContacts = maxContacts;
  this->contacts = contacts;
  this->getContacts = 1;
  this->numContacts = 0;
  v13 = depth * dir->p[0];
  end.y = depth * dir->p[1];
  end.z = depth * dir->p[2];
  v14 = v13 + start->x;
  v15 = end.y + start->y;
  v19 = end.z + start->z;
  end.z = v19;
  v16 = this->__vftable;
  end.x = v14;
  end.y = v15;
  v16->Translation(this, &results, start, &end, trm, trmAxis, contentMask, model, origin, modelAxis);
  result = this->numContacts;
  this->getContacts = 0;
  this->maxContacts = 0;
  return result;
}
