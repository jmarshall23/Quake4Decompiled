
// FUNC: public: bool __thiscall rvParticleParms::operator!=(class rvParticleParms const &)const
BOOL __thiscall rvParticleParms::operator!=(rvParticleParms *this, const rvParticleParms *comp)
{
  return !rvParticleParms::Compare(this, comp);
}
