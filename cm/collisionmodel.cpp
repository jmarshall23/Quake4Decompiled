
// FUNC: public: virtual bool __thiscall idCollisionModelLocal::GetContents(int &)const
char __thiscall idCollisionModelLocal::GetContents(idCollisionModelLocal *this, int *contents)
{
  *contents = this->contents;
  return 1;
}

// FUNC: public: virtual bool __thiscall idCollisionModelLocal::GetBounds(class idBounds &)const
char __thiscall idCollisionModelLocal::GetBounds(idCollisionModelLocal *this, idBounds *bounds)
{
  *bounds = this->bounds;
  return 1;
}
