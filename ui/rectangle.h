
// FUNC: public: __thiscall idRectangle::idRectangle(void)
void __thiscall idRectangle::idRectangle(idRectangle *this)
{
  this->h = 0.0;
  this->w = 0.0;
  this->y = 0.0;
  this->x = 0.0;
}

// FUNC: public: bool __thiscall idRectangle::Contains(float,float)
bool __thiscall idRectangle::Contains(idRectangle *this, float xt, float yt)
{
  return (0.0 != this->w || 0.0 != this->h)
      && xt >= (double)this->x
      && this->x + this->w >= xt
      && yt >= (double)this->y
      && this->h + this->y >= yt;
}
