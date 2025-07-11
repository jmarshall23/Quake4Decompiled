
// FUNC: class idRenderModelStatic * __cdecl NewRenderModel<class idRenderModelStatic>(class idRenderModel const *)
void __cdecl NewRenderModel<idRenderModelStatic>()
{
  idRenderModelStatic *v0; // eax

  v0 = (idRenderModelStatic *)Memory::Allocate(0x70u);
  if ( v0 )
    idRenderModelStatic::idRenderModelStatic(v0);
}

// FUNC: public: __thiscall idMD5Joint::idMD5Joint(void)
void __thiscall idMD5Joint::idMD5Joint(idMD5Joint *this)
{
  char *baseBuffer; // ecx

  baseBuffer = this->name.baseBuffer;
  this->name.len = 0;
  this->name.alloced = 20;
  this->name.data = baseBuffer;
  *baseBuffer = 0;
  this->parent = 0;
}

// FUNC: class idRenderModelStatic * __cdecl NewRenderModel<class idRenderModelStatic>(enum Rv_Sys_Heap_ID_t)
void __cdecl NewRenderModel<idRenderModelStatic>()
{
  idRenderModelStatic *v0; // eax

  v0 = (idRenderModelStatic *)Memory::Allocate(0x70u);
  if ( v0 )
    idRenderModelStatic::idRenderModelStatic(v0);
}

// FUNC: class rvRenderModelMD5R * __cdecl NewRenderModel<class rvRenderModelMD5R>(enum Rv_Sys_Heap_ID_t)
void __cdecl NewRenderModel<rvRenderModelMD5R>()
{
  rvRenderModelMD5R *v0; // eax

  v0 = (rvRenderModelMD5R *)Memory::Allocate(0xC4u);
  if ( v0 )
    rvRenderModelMD5R::rvRenderModelMD5R(v0);
}

// FUNC: class idRenderModelMD5 * __cdecl NewRenderModel<class idRenderModelMD5>(enum Rv_Sys_Heap_ID_t)
void __cdecl NewRenderModel<idRenderModelMD5>()
{
  idRenderModelMD5 *v0; // eax

  v0 = (idRenderModelMD5 *)Memory::Allocate(0x9Cu);
  if ( v0 )
    idRenderModelMD5::idRenderModelMD5(v0);
}

// FUNC: class idRenderModelLiquid * __cdecl NewRenderModel<class idRenderModelLiquid>(enum Rv_Sys_Heap_ID_t)
void __cdecl NewRenderModel<idRenderModelLiquid>()
{
  idRenderModelLiquid *v0; // eax

  v0 = (idRenderModelLiquid *)Memory::Allocate(0xD8u);
  if ( v0 )
    idRenderModelLiquid::idRenderModelLiquid(v0);
}

// FUNC: class idRenderModelBeam * __cdecl NewRenderModel<class idRenderModelBeam>(enum Rv_Sys_Heap_ID_t)
idRenderModelBeam *__cdecl NewRenderModel<idRenderModelBeam>()
{
  idRenderModelStatic *v0; // esi
  idRenderModelBeam *result; // eax

  v0 = (idRenderModelStatic *)Memory::Allocate(0x70u);
  result = 0;
  if ( v0 )
  {
    idRenderModelStatic::idRenderModelStatic(v0);
    v0->__vftable = (idRenderModelStatic_vtbl *)&idRenderModelBeam::`vftable';
    return (idRenderModelBeam *)v0;
  }
  return result;
}

// FUNC: class idRenderModelSprite * __cdecl NewRenderModel<class idRenderModelSprite>(enum Rv_Sys_Heap_ID_t)
idRenderModelSprite *__cdecl NewRenderModel<idRenderModelSprite>()
{
  idRenderModelStatic *v0; // esi
  idRenderModelSprite *result; // eax

  v0 = (idRenderModelStatic *)Memory::Allocate(0x70u);
  result = 0;
  if ( v0 )
  {
    idRenderModelStatic::idRenderModelStatic(v0);
    v0->__vftable = (idRenderModelStatic_vtbl *)&idRenderModelSprite::`vftable';
    return (idRenderModelSprite *)v0;
  }
  return result;
}

// FUNC: class rvRenderModelBSE * __cdecl NewRenderModel<class rvRenderModelBSE>(enum Rv_Sys_Heap_ID_t)
rvRenderModelBSE *__cdecl NewRenderModel<rvRenderModelBSE>()
{
  rvRenderModelBSE *v0; // esi
  rvRenderModelBSE *result; // eax

  v0 = (rvRenderModelBSE *)Memory::Allocate(0x70u);
  result = 0;
  if ( v0 )
  {
    idRenderModelStatic::idRenderModelStatic(v0);
    v0->__vftable = (rvRenderModelBSE_vtbl *)&rvRenderModelBSE::`vftable';
    v0->bounds.b[0].z = idMath::INFINITY;
    v0->bounds.b[0].y = idMath::INFINITY;
    v0->bounds.b[0].x = idMath::INFINITY;
    result = v0;
    v0->bounds.b[1].z = -1.0e30;
    v0->bounds.b[1].y = -1.0e30;
    v0->bounds.b[1].x = -1.0e30;
  }
  return result;
}

// FUNC: class idRenderModelMD3 * __cdecl NewRenderModel<class idRenderModelMD3>(enum Rv_Sys_Heap_ID_t)
idRenderModelMD3 *__cdecl NewRenderModel<idRenderModelMD3>()
{
  idRenderModelStatic *v0; // esi
  idRenderModelMD3 *result; // eax

  v0 = (idRenderModelStatic *)Memory::Allocate(0x80u);
  result = 0;
  if ( v0 )
  {
    idRenderModelStatic::idRenderModelStatic(v0);
    v0->__vftable = (idRenderModelStatic_vtbl *)&idRenderModelMD3::`vftable';
    return (idRenderModelMD3 *)v0;
  }
  return result;
}
