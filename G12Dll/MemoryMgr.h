typedef uintptr_t addr;

#define WRAPPER __declspec(naked)
#define DEPRECATED __declspec(deprecated)
#define EAXJMP(a) { _asm mov eax, a _asm jmp eax }
#define VARJMP(a) { _asm jmp a }
#define WRAPARG(a) UNREFERENCED_PARAMETER(a)

#define RET(n)	__asm push	n __asm retn
#define ASM(name) void __declspec(naked) name(void)

#define NOVMT __declspec(novtable)
#define SETVMT(a) *((DWORD_PTR*)this) = (DWORD_PTR)a

#pragma warning(disable:4731) // -- suppress C4731:"frame pointer register 'ebp' modified by inline assembly code"

#define XCALL(uAddr)			\
	__asm { mov esp, ebp	}	\
	__asm { pop ebp			}	\
	__asm { mov eax, uAddr	}	\
	__asm { jmp eax			}

#define FIELD(type, var, offset) *(type*)((unsigned char*)var + offset)

template<typename T, typename AT> inline void
Patch(AT address, T value)
{
	DWORD		dwProtect[2];
	VirtualProtect((void*)address, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	*(T*)address = value;
	VirtualProtect((void*)address, sizeof(T), dwProtect[0], &dwProtect[1]);
}

inline void
PatchBytes(DWORD address, void* value, size_t nCount)
{
	DWORD		dwProtect[2];
	VirtualProtect((void*)address, nCount, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	memcpy((void*)address, value, nCount);
	VirtualProtect((void*)address, nCount, dwProtect[0], &dwProtect[1]);
}

template<typename AT> inline void
Nop(AT address, unsigned int nCount)
{
	DWORD		dwProtect[2];
	VirtualProtect((void*)address, nCount, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	memset((void*)address, 0x90, nCount);
	VirtualProtect((void*)address, nCount, dwProtect[0], &dwProtect[1]);
}

enum
{
	PATCH_CALL,
	PATCH_JUMP,
	PATCH_NOTHING,
};

template<typename AT, typename HT> inline void
InjectHook(AT address, HT hook, unsigned int nType=PATCH_NOTHING)
{
	DWORD		dwProtect[2];
	switch ( nType )
	{
	case PATCH_JUMP:
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		*(BYTE*)address = 0xE9;
		break;
	case PATCH_CALL:
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		*(BYTE*)address = 0xE8;
		break;
	default:
		VirtualProtect((void*)((DWORD)address + 1), 4, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		break;
	}
	DWORD		dwHook;
	_asm
	{
		mov		eax, hook
		mov		dwHook, eax
	}

	*(ptrdiff_t*)((DWORD)address + 1) = (DWORD)dwHook - (DWORD)address - 5;

	if ( nType == PATCH_NOTHING )
		VirtualProtect((void*)((DWORD)address + 1), 4, dwProtect[0], &dwProtect[1]);
	else
		VirtualProtect((void*)address, 5, dwProtect[0], &dwProtect[1]);
}

inline void ExtractCall(void *dst, addr a)
{
	*(addr*)dst = (addr)(*(addr*)(a+1) + a + 5);
}
template<typename T>
inline void InterceptCall(void *dst, T func, addr a)
{
	ExtractCall(dst, a);
	InjectHook(a, func);
}
template<typename T>
inline void InterceptVmethod(void *dst, T func, addr a)
{
	*(addr*)dst = *(addr*)a;
	Patch(a, func);
}
