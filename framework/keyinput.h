
// FUNC: bool __cdecl IsEscapeKey(int)
bool __cdecl IsEscapeKey(int key)
{
  return key == 27 || key == 203;
}
