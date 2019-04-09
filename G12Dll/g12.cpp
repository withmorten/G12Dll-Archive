#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdint.h>
#include "MemoryMgr.h"

#define G12DLL_NAME "G12"

#include "G12.h"

void PatchGothic(void)
{
	if (G12GetPrivateProfileInt("BarrierIgnoreSkyEffectsSetting", FALSE))
	{
		// Ignore skyEffects setting for oCSkyControler_Barrier::RenderSkyPre
		Nop(0x00632152, 6);
	}

	if (G12GetPrivateProfileInt("ShowTime", FALSE))
	{
		// Enable Show Time
		Patch(0x006357B8 + 1, (BYTE)0x86);
	}
}

void PatchSpacer(void)
{
	if (G12GetPrivateProfileInt("SpacerDisableNumlock", FALSE))
	{
		// Disable NumLock
		Patch(0x0073A0DF, (BYTE)0xEB);
		Patch(0x0079E4E0, (BYTE)0xEB);
	}

	if (G12GetPrivateProfileInt("BarrierIgnoreSkyEffectsSetting", FALSE))
	{
		// Ignore skyEffects setting in oCSkyControler_Barrier::RenderSkyPre()
		Nop(0x0065B932, 6);
	}

	// Enable saving of (indoor) meshes ...
	Patch(0x007A5C8A, (BYTE)0xEB);

	// Don't save mesh for compiled ascii
	Patch(0x007A1FD2 + 1, (BYTE)FALSE);

	// Don't save mesh for uncompiled ascii
	Patch(0x007A2095 + 1, (BYTE)FALSE);

	// Don't show "memory leaks found" everytime quitting
	Patch(0x005354A2 + 1, (BYTE)2);

	// BSP vobs ...
	Patch(0x004C10FE + 1, (BYTE)2);

	// BSP lights ...
	Patch(0x004C11E1 + 1, (BYTE)2);
}

void PatchGothic2(void)
{
	if (G12GetPrivateProfileInt("ShowTime", FALSE))
	{
		// Enable Show Time
		Patch(0x006BF92E + 1, (BYTE)0x86);
	}

	if (G12GetPrivateProfileInt("GodMode", FALSE))
	{
		// oCNpc::godmode
		Patch(0x00AB2660, 1);
	}
}

void PatchSpacer2(void)
{
	if (G12GetPrivateProfileInt("SpacerDisableNumlock", FALSE))
	{
		// Disable NumLock
		Patch(0x0048A63F, (BYTE)0xEB);
		Patch(0x0041C426, (BYTE)0xEB);
	}

	// Fix crash when exiting Spacer2 with log level >= 7
	NopTo(0x0041BC9D, 0x0041BCBD);
	NopTo(0x0041BD6D, 0x0041BD92);

	// Enable saving of (indoor) meshes ...
	Patch(0x00423C8D, (BYTE)0xEB);
}

void Init(void)
{
	if (GOTHIC108)
	{
		G12AllocConsole();
		PatchGothic();
	}
	else if (SPACER15)
	{
		G12AllocConsole();
		PatchSpacer();
	}
	else if (GOTHIC26)
	{
		G12AllocConsole();
		PatchGothic2();
	}
	else if (SPACER26)
	{
		G12AllocConsole();
		PatchSpacer2();
	}
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}
