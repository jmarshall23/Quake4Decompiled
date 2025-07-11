
// FUNC: public: virtual void __thiscall idSysLocal::FPU_SetPrecision(int)
void __thiscall idSysLocal::FPU_SetPrecision(idSysLocal *this, int flags)
{
  Sys_FPU_SetPrecision(flags);
}

// FUNC: public: virtual struct _iobuf * __thiscall idSysLocal::FOpen(char const *,char const *)
_iobuf *__thiscall idSysLocal::FOpen(idSysLocal *this, const char *name, const char *mode)
{
  return Sys_FOpen(name, mode);
}

// FUNC: public: virtual void __thiscall idSysLocal::FPrintf(struct _iobuf *,char const *)
void __thiscall idSysLocal::FPrintf(idSysLocal *this, _iobuf *file, const char *fmt)
{
  Sys_FPrintf(file, fmt);
}

// FUNC: public: virtual int __thiscall idSysLocal::FTell(struct _iobuf *)
int __thiscall idSysLocal::FTell(idSysLocal *this, _iobuf *file)
{
  return Sys_FTell(file);
}

// FUNC: public: virtual int __thiscall idSysLocal::FSeek(struct _iobuf *,long,int)
int __thiscall idSysLocal::FSeek(idSysLocal *this, _iobuf *file, int offset, int mode)
{
  return Sys_FSeek(file, offset, mode);
}

// FUNC: public: virtual void __thiscall idSysLocal::FClose(struct _iobuf *)
void __thiscall idSysLocal::FClose(idSysLocal *this, _iobuf *file)
{
  Sys_FClose(file);
}

// FUNC: public: virtual int __thiscall idSysLocal::FRead(void *,int,int,struct _iobuf *)
int __thiscall idSysLocal::FRead(idSysLocal *this, void *buffer, int size, int count, _iobuf *file)
{
  return Sys_FRead(buffer, size, count, file);
}

// FUNC: public: virtual int __thiscall idSysLocal::FWrite(void *,int,int,struct _iobuf *)
int __thiscall idSysLocal::FWrite(idSysLocal *this, void *buffer, int size, int count, _iobuf *file)
{
  return Sys_FWrite(buffer, size, count, file);
}

// FUNC: public: virtual long __thiscall idSysLocal::FileTimeStamp(struct _iobuf *)
int __thiscall idSysLocal::FileTimeStamp(idSysLocal *this, _iobuf *file)
{
  return Sys_FileTimeStamp(file);
}

// FUNC: public: virtual int __thiscall idSysLocal::FEof(struct _iobuf *)
int __thiscall idSysLocal::FEof(idSysLocal *this, _iobuf *stream)
{
  return Sys_FEof(stream);
}

// FUNC: public: virtual char * __thiscall idSysLocal::FGets(char *,int,struct _iobuf *)
char *__thiscall idSysLocal::FGets(idSysLocal *this, char *string, int n, _iobuf *stream)
{
  return Sys_FGets(string, n, stream);
}

// FUNC: public: virtual void __thiscall idSysLocal::FFlush(struct _iobuf *)
void __thiscall idSysLocal::FFlush(idSysLocal *this, _iobuf *f)
{
  Sys_FFlush(f);
}

// FUNC: public: virtual int __thiscall idSysLocal::SetVBuf(struct _iobuf *,char *,int,unsigned int)
int __thiscall idSysLocal::SetVBuf(idSysLocal *this, _iobuf *stream, char *buffer, int mode, unsigned int size)
{
  return Sys_SetVBuf(stream, buffer, mode, size);
}
