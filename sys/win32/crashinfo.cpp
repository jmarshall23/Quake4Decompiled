
// FUNC: int __stdcall CI_ModuleCallback(char *,unsigned __int64,void *)
int __stdcall CI_ModuleCallback(char *ModuleName, unsigned __int64 BaseOfDll, void *__formal)
{
  _IMAGEHLP_MODULE64 mi; // [esp+8h] [ebp-688h] BYREF

  mi.SizeOfStruct = 0;
  memset(&mi.BaseOfImage, 0, 0x680u);
  if ( BaseOfDll < 0x70000000 )
  {
    CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, "%14s 0x%08x", ModuleName, (_DWORD)BaseOfDll);
    mi.SizeOfStruct = 1672;
    if ( SymGetModuleInfo64(CICurrentProcess, (unsigned int)BaseOfDll, &mi) )
    {
      CITxtIdx += _snprintf(
                    &CICrashReport[CITxtIdx],
                    0xFFu,
                    " (0x%08x) (%d) %s",
                    mi.ImageSize,
                    mi.SymType,
                    mi.LoadedImageName);
      if ( mi.LoadedPdbName[0] )
        CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, " (%s)", mi.LoadedPdbName);
      CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, "\r\n");
    }
  }
  return 1;
}

// FUNC: bool __cdecl CI_Init(void)
char __cdecl CI_Init()
{
  int v1; // eax
  char *v2; // [esp-18h] [ebp-1Ch]

  SymSetOptions(0x12u);
  if ( !SymInitialize(CICurrentProcess, 0, 1) )
    return 0;
  SymSetOptions(0x12u);
  v1 = _snprintf(&CICrashReport[CITxtIdx], 0xFFu, "        Module       Base         Size Typ Image\r\n");
  v2 = &CICrashReport[v1 + CITxtIdx];
  CITxtIdx += v1;
  CITxtIdx += _snprintf(v2, 0xFFu, "    ================================================\r\n");
  SymEnumerateModules64(CICurrentProcess, (PSYM_ENUMMODULES_CALLBACK64)CI_ModuleCallback, 0);
  CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, "    ================================================\r\n\r\n");
  return 1;
}

// FUNC: bool __cdecl CI_GetFuncInfo(unsigned __int64,char *)
char __cdecl CI_GetFuncInfo(unsigned __int64 addr, char *funcName)
{
  DWORD LastError; // eax
  unsigned int lineDisplacement; // [esp+Ch] [ebp-854h] BYREF
  unsigned __int64 symDisplacement; // [esp+10h] [ebp-850h] BYREF
  _IMAGEHLP_LINE64 line; // [esp+18h] [ebp-848h] BYREF
  _SYMBOL_INFO_PACKAGE symbolInfo; // [esp+30h] [ebp-830h] BYREF

  memset(&symbolInfo.si.TypeIndex, 0, 0x82Cu);
  memset(&line.Key, 0, 20);
  symDisplacement = 0i64;
  lineDisplacement = 0;
  symbolInfo.si.SizeOfStruct = 88;
  symbolInfo.si.MaxNameLen = 2000;
  line.SizeOfStruct = 24;
  if ( SymFromAddr(CICurrentProcess, addr, &symDisplacement, &symbolInfo.si) )
  {
    if ( SymGetLineFromAddr64(CICurrentProcess, addr, &lineDisplacement, &line) )
      _snprintf(
        funcName,
        0xFFu,
        "%s Line %d (+%d bytes) in %s",
        symbolInfo.si.Name,
        line.LineNumber,
        lineDisplacement,
        line.FileName);
    else
      _snprintf(funcName, 0xFFu, "%s + %d bytes", symbolInfo.si.Name, (_DWORD)symDisplacement);
    return 1;
  }
  else
  {
    sprintf(funcName, "0x%08x    ", (_DWORD)addr);
    LastError = GetLastError();
    FormatMessageA(0x1000u, 0, LastError, 0x400u, funcName + 12, 0xF4u, 0);
    return 1;
  }
}

// FUNC: void __cdecl CI_GetBasicType(char *,enum BasicType,unsigned __int64)
void __cdecl CI_GetBasicType(char *type, BasicType basicType, unsigned __int64 length)
{
  switch ( basicType )
  {
    case btVoid:
      strcat(type, "void");
      break;
    case btChar:
      goto $L58837;
    case btWChar:
      strcat(type, "wchar");
      break;
    case btInt:
    case btLong:
      switch ( length )
      {
        case 1ui64:
$L58837:
          strcat(type, "char");
          break;
        case 2ui64:
          strcat(type, "short");
          break;
        case 8ui64:
          strcat(type, "__int64");
          break;
        default:
          strcat(type, "int");
          break;
      }
      break;
    case btUInt:
    case btULong:
      switch ( length )
      {
        case 1ui64:
          strcat(type, "byte");
          break;
        case 2ui64:
          strcat(type, "word");
          break;
        case 8ui64:
          strcat(type, "unsigned __int64");
          break;
        default:
          strcat(type, "uint");
          break;
      }
      break;
    case btFloat:
      if ( length == 8 )
        strcat(type, "double");
      else
        strcat(type, "float");
      break;
    case btBCD:
      strcat(type, "BCD");
      break;
    case btBool:
      strcat(type, "bool");
      break;
    case btCurrency:
      strcat(type, "currency");
      break;
    case btDate:
      strcat(type, "date");
      break;
    case btVariant:
      strcat(type, "variant");
      break;
    case btComplex:
      strcat(type, "complex");
      break;
    case btBit:
      strcat(type, "bit");
      break;
    case btBSTR:
      strcat(type, "BSTR");
      break;
    case btHresult:
      strcat(type, "HRESULT");
      break;
    default:
      strcat(type, "notype");
      break;
  }
}

// FUNC: void __cdecl CI_GetBasicValue(char *,enum BasicType,char const *,unsigned __int64)
void __cdecl CI_GetBasicValue(char *result, BasicType basicType, const char *var, unsigned __int64 length)
{
  switch ( basicType )
  {
    case btInt:
    case btLong:
      switch ( length )
      {
        case 1ui64:
          sprintf(result, "%i (0x%02x)", *var, *(unsigned __int8 *)var);
          break;
        case 2ui64:
          sprintf(result, "%hi (0x%04x)", *(__int16 *)var, *(__int16 *)var);
          break;
        case 8ui64:
          goto LABEL_7;
        default:
          sprintf(result, "%i (0x%08x)", *(_DWORD *)var, *(_DWORD *)var);
          break;
      }
      break;
    case btUInt:
    case btULong:
      switch ( length )
      {
        case 1ui64:
          sprintf(result, "%u (0x%02x)", *(unsigned __int8 *)var, *(unsigned __int8 *)var);
          break;
        case 2ui64:
          sprintf(result, "%hu (0x%04x)", *(unsigned __int16 *)var, *(unsigned __int16 *)var);
          break;
        case 8ui64:
LABEL_7:
          sprintf(result, "%i64x", *(_DWORD *)var);
          break;
        default:
          sprintf(result, "%u (0x%08x)", *(_DWORD *)var, *(_DWORD *)var);
          break;
      }
      break;
    case btFloat:
      if ( length == 8 )
        sprintf(result, "%f", *(double *)var);
      else
        sprintf(result, "%f", *(float *)var);
      break;
    case btBool:
      if ( *var )
        strcpy(result, "true");
      else
        strcpy(result, "false");
      break;
    default:
      sprintf(result, "'%c'", *var);
      break;
  }
}

// FUNC: bool __cdecl CI_GetExceptionalValue(char *,char const *,enum BasicType,unsigned __int64,int)
char __cdecl CI_GetExceptionalValue(
        char *result,
        const char *var,
        BasicType basicType,
        unsigned __int64 __formal,
        int level)
{
  if ( !var )
    return 0;
  if ( basicType == btChar && level == 1 )
  {
    if ( *(_DWORD *)var )
      _snprintf(result, 0xFFu, "( \"%s\" )", *(const char **)var);
    else
      strcpy(result, "( NULL )");
    return 1;
  }
  if ( level != 2 )
    return 0;
  if ( *(_DWORD *)var )
    _snprintf(result, 0xFFu, "0x%08x ( = 0x%08x )", var, *(_DWORD *)var);
  else
    _snprintf(result, 0xFFu, "0x%08x ( NULL )", var);
  return 1;
}

// FUNC: void __cdecl CI_GetPointerValue(char *,char const *)
void __cdecl CI_GetPointerValue(char *result, const char *var)
{
  if ( var )
    sprintf(result, "0x%08x", var);
  else
    strcpy(result, "NULL");
}

// FUNC: void __cdecl CI_HandleCustomTypes(char *,char const *,int)
void __cdecl CI_HandleCustomTypes(char *result, char *var, int level)
{
  const char *StringValue; // eax

  if ( level || !var )
    goto LABEL_9;
  if ( !strcmp(result, "idVec3") )
  {
    sprintf(result, "( %g, %g, %g )", *(float *)var, *((float *)var + 1), *((float *)var + 2));
    return;
  }
  if ( !strcmp(result, "idVec4") )
  {
    sprintf(result, "( %g, %g, %g, %g )", *(float *)var, *((float *)var + 1), *((float *)var + 2), *((float *)var + 3));
    return;
  }
  if ( !strcmp(result, "idStr") )
  {
    StringValue = Com_GetStringValue(var);
    sprintf(result, "( \"%s\" )", StringValue);
  }
  else
  {
LABEL_9:
    sprintf(result, "0x%08x", var);
  }
}

// FUNC: void __cdecl CI_AppendPointerDeclaration(char *,int)
void __cdecl CI_AppendPointerDeclaration(char *type, int level)
{
  char *v2; // edi

  v2 = type - 1;
  if ( level )
  {
    if ( level == 1 )
    {
      while ( *++v2 )
        ;
      strcpy(v2, " *)");
    }
    else if ( level == 2 )
    {
      while ( *++v2 )
        ;
      strcpy(v2, " **)");
    }
    else
    {
      while ( *++v2 )
        ;
      strcpy(v2, " ?)");
    }
  }
  else
  {
    while ( *++v2 )
      ;
    strcpy(v2, ")");
  }
}

// FUNC: bool __cdecl CI_VarToString(char *,char *,char const *,unsigned long,int)
char __cdecl CI_VarToString(char *result, char *type, char *var, unsigned int typeId, int level)
{
  BasicType basicType; // [esp+10h] [ebp-10h] BYREF
  unsigned __int16 *typeName; // [esp+14h] [ebp-Ch] BYREF
  unsigned __int64 length; // [esp+18h] [ebp-8h] BYREF

  if ( !SymGetTypeInfo(CICurrentProcess, CIModuleInfo.BaseOfImage, typeId, TI_GET_LENGTH, &length) )
    length = 4i64;
  if ( SymGetTypeInfo(CICurrentProcess, CIModuleInfo.BaseOfImage, typeId, TI_GET_BASETYPE, &basicType) )
  {
    CI_GetBasicType(type, basicType, length);
    if ( level )
    {
      if ( !CI_GetExceptionalValue(result, var, basicType, length, level) )
        CI_GetPointerValue(result, var);
      CI_AppendPointerDeclaration(type, level);
      return 1;
    }
    else
    {
      CI_GetBasicValue(result, basicType, var, length);
      CI_AppendPointerDeclaration(type, 0);
      return 1;
    }
  }
  else if ( SymGetTypeInfo(CICurrentProcess, CIModuleInfo.BaseOfImage, typeId, TI_GET_SYMNAME, &typeName) )
  {
    _snprintf(result, 0xFFu, "%ls", typeName);
    strcat(type, result);
    LocalFree(typeName);
    CI_HandleCustomTypes(result, var, level);
    CI_AppendPointerDeclaration(type, level);
    return 1;
  }
  else
  {
    return 0;
  }
}

// FUNC: void __cdecl CI_GetVariableValue(char *,char *,struct _SYMBOL_INFO *,void *,int)
void __cdecl CI_GetVariableValue(char *result, char *type, _SYMBOL_INFO *symInfo, char *variable, int offset)
{
  char *v5; // ebx
  _SYMBOL_INFO *v6; // ebp
  char *v7; // edi
  char *v8; // esi

  v5 = result;
  v6 = symInfo;
  v7 = type;
  *result = 0;
  *v7 = 0;
  if ( (v6->Flags & 0x10) != 0 )
    v8 = &variable[LODWORD(v6->Address) + offset];
  else
    v8 = variable;
  *(_WORD *)v7 = 40;
  if ( !CI_VarToString(v5, v7, v8, v6->TypeIndex, 0) )
  {
    SymGetTypeInfo(CICurrentProcess, CIModuleInfo.BaseOfImage, v6->TypeIndex, TI_GET_TYPEID, &result);
    if ( !CI_VarToString(v5, v7, v8, (unsigned int)result, 1) )
    {
      SymGetTypeInfo(CICurrentProcess, CIModuleInfo.BaseOfImage, (ULONG)result, TI_GET_TYPEID, &result);
      CI_VarToString(v5, v7, v8, (unsigned int)result, 2);
    }
  }
}

// FUNC: int __stdcall EnumerateSymbolsParmsCallback(struct _SYMBOL_INFO *,unsigned long,void *)
BOOL __stdcall EnumerateSymbolsParmsCallback(_SYMBOL_INFO *symInfo, unsigned int __formal, char *UserContext)
{
  char value[256]; // [esp+4h] [ebp-200h] BYREF
  char type[256]; // [esp+104h] [ebp-100h] BYREF

  if ( (symInfo->Flags & 0x40) != 0 )
  {
    CI_GetVariableValue(value, type, symInfo, UserContext, 4);
    CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, " %s%s = %s\r\n", type, symInfo->Name, value);
  }
  return CITxtIdx < 12288;
}

// FUNC: int __stdcall EnumerateSymbolsLocalsCallback(struct _SYMBOL_INFO *,unsigned long,void *)
BOOL __stdcall EnumerateSymbolsLocalsCallback(_SYMBOL_INFO *symInfo, unsigned int __formal, char *UserContext)
{
  unsigned int Flags; // eax
  char value[256]; // [esp+4h] [ebp-200h] BYREF
  char type[256]; // [esp+104h] [ebp-100h] BYREF

  Flags = symInfo->Flags;
  if ( (Flags & 0x80u) != 0 && (Flags & 0x40) == 0 )
  {
    CI_GetVariableValue(value, type, symInfo, UserContext, 0);
    CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, " %s%s = %s\r\n", type, symInfo->Name, value);
  }
  return CITxtIdx < 12288;
}

// FUNC: void __cdecl CI_WriteLocals(struct _tagSTACKFRAME64 *)
void __cdecl CI_WriteLocals(_tagSTACKFRAME64 *stack)
{
  int Offset; // edx
  int Offset_high; // ecx
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  void *FuncTableEntry; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  unsigned int v14; // ecx
  unsigned int v15; // edx
  int v16; // eax
  int v17; // eax
  void *v18; // edx
  _IMAGEHLP_STACK_FRAME imagehlpStackFrame; // [esp+8h] [ebp-80h] BYREF

  Offset = stack->AddrReturn.Offset;
  memset(&imagehlpStackFrame.ReturnOffset, 0, 0x78u);
  Offset_high = HIDWORD(stack->AddrPC.Offset);
  LODWORD(imagehlpStackFrame.InstructionOffset) = stack->AddrPC.Offset;
  HIDWORD(imagehlpStackFrame.ReturnOffset) = HIDWORD(stack->AddrReturn.Offset);
  v3 = stack->AddrStack.Offset;
  LODWORD(imagehlpStackFrame.ReturnOffset) = Offset;
  v4 = HIDWORD(stack->AddrFrame.Offset);
  LODWORD(imagehlpStackFrame.StackOffset) = v3;
  v5 = HIDWORD(stack->AddrBStore.Offset);
  HIDWORD(imagehlpStackFrame.InstructionOffset) = Offset_high;
  v6 = stack->AddrFrame.Offset;
  HIDWORD(imagehlpStackFrame.FrameOffset) = v4;
  v7 = stack->AddrBStore.Offset;
  HIDWORD(imagehlpStackFrame.BackingStoreOffset) = v5;
  FuncTableEntry = stack->FuncTableEntry;
  LODWORD(imagehlpStackFrame.FrameOffset) = v6;
  v9 = HIDWORD(stack->AddrStack.Offset);
  LODWORD(imagehlpStackFrame.BackingStoreOffset) = v7;
  HIDWORD(imagehlpStackFrame.StackOffset) = v9;
  v10 = HIDWORD(stack->Params[0]);
  LODWORD(imagehlpStackFrame.Params[0]) = stack->Params[0];
  v11 = HIDWORD(stack->Params[1]);
  HIDWORD(imagehlpStackFrame.Params[0]) = v10;
  v12 = stack->Params[2];
  imagehlpStackFrame.FuncTableEntry = (int)FuncTableEntry;
  v13 = stack->Params[1];
  HIDWORD(imagehlpStackFrame.Params[1]) = v11;
  v14 = stack->Params[3];
  LODWORD(imagehlpStackFrame.Params[2]) = v12;
  v15 = HIDWORD(stack->Params[3]);
  LODWORD(imagehlpStackFrame.Params[1]) = v13;
  v16 = HIDWORD(stack->Params[2]);
  imagehlpStackFrame.Params[3] = __PAIR64__(v15, v14);
  HIDWORD(imagehlpStackFrame.Params[2]) = v16;
  imagehlpStackFrame.Virtual = stack->Virtual;
  if ( SymSetContext(CICurrentProcess, &imagehlpStackFrame, 0) )
  {
    v17 = sprintf(&CICrashReport[CITxtIdx], "\r\nParameters:\r\n");
    v18 = (void *)stack->AddrFrame.Offset;
    CITxtIdx += v17;
    SymEnumSymbols(
      CICurrentProcess,
      0i64,
      &entityFilter,
      (PSYM_ENUMERATESYMBOLS_CALLBACK)EnumerateSymbolsParmsCallback,
      v18);
    CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "\r\nLocal Variables:\r\n");
    SymEnumSymbols(
      CICurrentProcess,
      0i64,
      &entityFilter,
      (PSYM_ENUMERATESYMBOLS_CALLBACK)EnumerateSymbolsLocalsCallback,
      (PVOID)stack->AddrFrame.Offset);
  }
  else
  {
    CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "\r\nFailed to set stack frame context\r\n");
  }
  CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "\r\n");
}

// FUNC: void __cdecl CI_GetCallStack(struct _CONTEXT *)
void __cdecl CI_GetCallStack(_CONTEXT *context)
{
  unsigned int Ebp; // edx
  unsigned int Esp; // edx
  int v3; // esi
  int v4; // eax
  DWORD LastError; // eax
  DWORD v6; // eax
  char *v7; // [esp-10h] [ebp-238h]
  char *v8; // [esp-Ch] [ebp-234h]
  char *v9; // [esp-Ch] [ebp-234h]
  unsigned int Eip; // [esp-4h] [ebp-22Ch]
  _tagSTACKFRAME64 stack; // [esp+20h] [ebp-208h] BYREF
  char funcName[256]; // [esp+128h] [ebp-100h] BYREF

  memset(&stack, 0, sizeof(stack));
  memset(funcName, 0, sizeof(funcName));
  if ( context )
  {
    CI_Init();
    Eip = context->Eip;
    Ebp = context->Ebp;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrFrame.Mode = AddrModeFlat;
    stack.AddrStack.Mode = AddrModeFlat;
    stack.AddrPC.Offset = Eip;
    LODWORD(stack.AddrFrame.Offset) = Ebp;
    Esp = context->Esp;
    v7 = &CICrashReportBasic[CITxtBasIdx];
    context->ContextFlags = 65543;
    *(_DWORD *)&stack.AddrPC.Segment = 0;
    HIDWORD(stack.AddrFrame.Offset) = 0;
    *(_DWORD *)&stack.AddrFrame.Segment = 0;
    stack.AddrStack.Offset = Esp;
    *(_DWORD *)&stack.AddrStack.Segment = 0;
    CITxtBasIdx += _snprintf(v7, 0xFFu, "Crash address: 0x%08x\r\n", Eip);
    v3 = 0;
    while ( CITxtIdx <= 12288 )
    {
      CIModuleInfo.SizeOfStruct = 1672;
      if ( !SymGetModuleInfo64(CICurrentProcess, stack.AddrPC.Offset, &CIModuleInfo) )
      {
        v4 = sprintf(&CICrashReport[CITxtIdx], "Failed to GetModuleInfo64: ");
        v8 = &CICrashReport[v4 + CITxtIdx];
        CITxtIdx += v4;
        LastError = GetLastError();
        FormatMessageA(0x1000u, 0, LastError, 0x400u, v8, 0xF4u, 0);
        CITxtIdx = strlen(CICrashReport);
        CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "\r\n\r\n");
        return;
      }
      if ( !StackWalk64(
              0x14Cu,
              CICurrentProcess,
              CICurrentThread,
              &stack,
              context,
              0,
              SymFunctionTableAccess64,
              SymGetModuleBase64,
              0) )
      {
        CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "StackWalk64 failed: ");
        v9 = &CICrashReport[CITxtIdx];
        v6 = GetLastError();
        FormatMessageA(0x1000u, 0, v6, 0x400u, v9, 0xF4u, 0);
        CITxtIdx = strlen(CICrashReport);
        CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "\r\n\r\n");
        break;
      }
      if ( CI_GetFuncInfo(stack.AddrPC.Offset, funcName) )
      {
        CITxtBasIdx += _snprintf(
                         &CICrashReportBasic[CITxtBasIdx],
                         0xFFu,
                         "%s:%s\r\n",
                         CIModuleInfo.ModuleName,
                         funcName);
        CITxtIdx += _snprintf(&CICrashReport[CITxtIdx], 0xFFu, "******** %s:%s\r\n", CIModuleInfo.ModuleName, funcName);
        CI_WriteLocals(&stack);
      }
      else
      {
        CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "PDB interrogate failed\r\n");
      }
      if ( ++v3 >= 9 )
        break;
    }
    CITxtIdx += sprintf(&CICrashReport[CITxtIdx], "<End of stack>\r\n\r\n");
    CITxtBasIdx += sprintf(&CICrashReportBasic[CITxtBasIdx], "<End of stack>\r\n\r\n");
  }
  else
  {
    CITxtBasIdx += _snprintf(&CICrashReportBasic[CITxtBasIdx], 0xFFu, "NULL context\r\n\r\n");
  }
}

// FUNC: void __cdecl CI_GetMemoryState(void)
void __cdecl CI_GetMemoryState()
{
  _MEMORYSTATUSEX statex; // [esp+4h] [ebp-40h] BYREF

  statex.dwLength = 64;
  GlobalMemoryStatusEx(&statex);
  CITxtBasIdx += sprintf(
                   &CICrashReportBasic[CITxtBasIdx],
                   "Memory: %d MB used out of %d MB\r\n\r\n",
                   (unsigned int)((statex.ullTotalPhys - statex.ullAvailPhys) >> 20),
                   (unsigned int)(statex.ullTotalPhys >> 20));
}

// FUNC: char const * __cdecl CI_GetExceptionString(unsigned long)
const char *__cdecl CI_GetExceptionString(unsigned int dwCode)
{
  const char *result; // eax

  if ( dwCode > 0xC000008D )
  {
    switch ( dwCode )
    {
      case 0xC000008E:
        result = "FLT_DIVIDE_BY_ZERO";
        break;
      case 0xC000008F:
        result = "FLT_INEXACT_RESULT";
        break;
      case 0xC0000090:
        result = "FLT_INVALID_OPERATION";
        break;
      case 0xC0000091:
        result = "FLT_OVERFLOW";
        break;
      case 0xC0000092:
        result = "FLT_STACK_CHECK";
        break;
      case 0xC0000093:
        result = "FLT_UNDERFLOW";
        break;
      case 0xC0000094:
        result = "INT_DIVIDE_BY_ZERO";
        break;
      case 0xC0000095:
        result = "INT_OVERFLOW";
        break;
      case 0xC0000096:
        result = "PRIV_INSTRUCTION";
        break;
      case 0xC00000FD:
        result = "STACK_OVERFLOW";
        break;
      default:
        return "UNKNOWN EXCEPTION";
    }
  }
  else if ( dwCode == -1073741683 )
  {
    return "FLT_DENORMAL_OPERAND";
  }
  else if ( dwCode > 0xC0000006 )
  {
    switch ( dwCode )
    {
      case 0xC0000008:
        result = "INVALID_HANDLE";
        break;
      case 0xC000001D:
        result = "ILLEGAL_INSTRUCTION";
        break;
      case 0xC0000025:
        result = "NONCONTINUABLE_EXCEPTION";
        break;
      case 0xC0000026:
        result = "INVALID_DISPOSITION";
        break;
      case 0xC000008C:
        result = "ARRAY_BOUNDS_EXCEEDED";
        break;
      default:
        return "UNKNOWN EXCEPTION";
    }
  }
  else if ( dwCode == -1073741818 )
  {
    return "IN_PAGE_ERROR";
  }
  else
  {
    if ( dwCode > 0x80000003 )
    {
      if ( dwCode == -2147483644 )
        return "SINGLE_STEP";
      if ( dwCode == -1073741819 )
        return "ACCESS_VIOLATION";
    }
    else
    {
      switch ( dwCode )
      {
        case 0x80000003:
          return "BREAKPOINT";
        case 0x80000001:
          return "GUARD_PAGE";
        case 0x80000002:
          return "DATATYPE_MISALIGNMENT";
      }
    }
    return "UNKNOWN EXCEPTION";
  }
  return result;
}

// FUNC: void __cdecl CI_SetCrashReportAutoSendString(char const *)
void __cdecl CI_SetCrashReportAutoSendString(const char *psString)
{
  if ( psString )
  {
    strncpy(g_sAutoReport, psString, 0x7FFu);
    byte_1131886F = 0;
  }
  else
  {
    g_sAutoReport[0] = 0;
  }
}

// FUNC: void __cdecl CI_AppendAutoSendString(struct _iobuf *)
void __cdecl CI_AppendAutoSendString(_iobuf *file)
{
  if ( g_sAutoReport[0] )
  {
    fwrite("###--- CUT HERE ---###", 1u, 0x16u, file);
    fwrite(g_sAutoReport, 1u, strlen(g_sAutoReport), file);
  }
}

// FUNC: void __cdecl CI_DumpMiniDump(void *,struct _EXCEPTION_POINTERS *)
// positive sp value has been detected, the output may be wrong!
void __cdecl CI_DumpMiniDump(void *hFile, _EXCEPTION_POINTERS *excpInfo)
{
  _MINIDUMP_EXCEPTION_INFORMATION eInfo; // [esp+Ch] [ebp-24h] BYREF
  CPPEH_RECORD ms_exc; // [esp+18h] [ebp-18h]

  if ( excpInfo )
  {
    OutputDebugStringA("writing minidump\r\n");
    eInfo.ThreadId = CICurrentThreadId;
    eInfo.ExceptionPointers = excpInfo;
    eInfo.ClientPointers = 1;
    MiniDumpWriteDump(CICurrentProcess, CICurrentProcessId, hFile, MiniDumpWithDataSegs, &eInfo, 0, 0);
  }
  else
  {
    OutputDebugStringA("raising exception\r\n");
    RaiseException(0x80000003, 0, 0, 0);
    ms_exc.registration.TryLevel = -1;
  }
}

// FUNC: void __cdecl CI_SaveCrashReport(struct _EXCEPTION_POINTERS *)
void __cdecl CI_SaveCrashReport(_EXCEPTION_POINTERS *origExceptionInfo)
{
  int v1; // eax
  char v2; // cl
  char *v3; // eax
  char *v4; // edx
  char v5; // cl
  HANDLE FileA; // eax
  void *v7; // esi
  _iobuf *v8; // esi
  _PROCESS_INFORMATION ProcessInformation; // [esp+0h] [ebp-6154h] BYREF
  _STARTUPINFOA StartupInfo; // [esp+10h] [ebp-6144h] BYREF
  char TempFileName[256]; // [esp+54h] [ebp-6100h] BYREF
  char buffer[24576]; // [esp+154h] [ebp-6000h] BYREF

  v1 = 0;
  do
  {
    v2 = CICrashReportBasic[v1];
    buffer[v1++] = v2;
  }
  while ( v2 );
  v3 = CICrashReport;
  v4 = &buffer[CITxtBasIdx - (_DWORD)CICrashReport];
  do
  {
    v5 = *v3;
    v3[(_DWORD)v4] = *v3;
    ++v3;
  }
  while ( v5 );
  if ( GetTempFileNameA(".", "QIV", 0, TempFileName) )
  {
    FileA = CreateFileA("minidump.dmp", 0x40000000u, 0, 0, 2u, 0x80000080, 0);
    v7 = FileA;
    if ( FileA != (HANDLE)-1 )
    {
      CI_DumpMiniDump(FileA, origExceptionInfo);
      CloseHandle(v7);
    }
    v8 = fopen(TempFileName, "wb");
    if ( v8 )
    {
      fwrite(buffer, 1u, strlen(buffer), v8);
      CI_AppendAutoSendString(v8);
      fclose(v8);
      memset(&StartupInfo.lpReserved, 0, 0x40u);
      memset(&ProcessInformation, 0, sizeof(ProcessInformation));
      StartupInfo.cb = 68;
      sprintf(
        buffer,
        "",
        TempFileName,
        "");
      CreateProcessA(0, buffer, 0, 0, 0, 0, 0, 0, &StartupInfo, &ProcessInformation);
    }
  }
}

// FUNC: long __stdcall CI_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *)
void __stdcall __noreturn CI_UnhandledExceptionFilter(_EXCEPTION_POINTERS *origExceptionInfo)
{
  _CONTEXT *v1; // esi
  const char *Version; // eax
  const char *ErrorMessage; // eax
  const char *ExceptionString; // eax
  _EXCEPTION_RECORD exceptionRecord; // [esp+10h] [ebp-320h] BYREF
  _CONTEXT contextRecord; // [esp+60h] [ebp-2D0h] BYREF

  if ( !CIEntered )
  {
    qmemcpy(&exceptionRecord, origExceptionInfo->ExceptionRecord, sizeof(exceptionRecord));
    v1 = origExceptionInfo->ContextRecord;
    CIEntered = 1;
    qmemcpy(&contextRecord, v1, sizeof(contextRecord));
    CICurrentProcess = GetCurrentProcess();
    CICurrentProcessId = GetCurrentProcessId();
    CICurrentThread = GetCurrentThread();
    CICurrentThreadId = GetCurrentThreadId();
    Version = Com_GetVersion();
    CITxtBasIdx += sprintf(CICrashReportBasic, "%s\r\n\r\n", Version);
    if ( strlen(Com_GetErrorMessage()) )
    {
      ErrorMessage = Com_GetErrorMessage();
      CITxtBasIdx += sprintf(&CICrashReportBasic[CITxtBasIdx], "ERROR: %s\r\n\r\n", ErrorMessage);
    }
    ExceptionString = CI_GetExceptionString(exceptionRecord.ExceptionCode);
    CITxtBasIdx += sprintf(&CICrashReportBasic[CITxtBasIdx], "Exception: %s\r\n", ExceptionString);
    CI_GetCallStack(&contextRecord);
    CI_GetMemoryState();
    CI_SaveCrashReport(origExceptionInfo);
    SymCleanup(CICurrentProcess);
  }
  exit(0);
}

// FUNC: void __cdecl CI_InitCrashReporting(void)
void __cdecl CI_InitCrashReporting()
{
  CIPreviousExceptionFilter = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CI_UnhandledExceptionFilter);
}

// FUNC: void __cdecl CI_ShutdownCrashReporting(void)
void __cdecl CI_ShutdownCrashReporting()
{
  if ( CIPreviousExceptionFilter )
    SetUnhandledExceptionFilter(CIPreviousExceptionFilter);
}
