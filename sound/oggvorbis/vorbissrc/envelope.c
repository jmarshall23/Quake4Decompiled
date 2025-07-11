
// FUNC: __ve_envelope_clear
void __cdecl _ve_envelope_clear(envelope_lookup *e)
{
  void **p_window; // esi
  int v2; // ebx

  mdct_clear(&e->mdct);
  p_window = (void **)&e->band[0].window;
  v2 = 7;
  do
  {
    _decoder_free(*p_window);
    p_window += 4;
    --v2;
  }
  while ( v2 );
  _decoder_free(e->mdct_win);
  _decoder_free(e->filter);
  _decoder_free(e->mark);
  memset(e, 0, sizeof(envelope_lookup));
}
