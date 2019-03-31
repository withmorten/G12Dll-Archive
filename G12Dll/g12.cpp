#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdint.h>
#include "MemoryMgr.h"

#define G12DLL_NAME "G12"

#include "G12.h"

void PatchGothic(void)
{
	if (G12GetPrivateProfileInt("BarrierIgnoreSkyEffectsSetting", 0))
	{
		// Ignore skyEffects setting for oCSkyControler_Barrier::RenderSkyPre
		Nop(0x00632152, 6);
	}

	if (G12GetPrivateProfileInt("ShowTime", 0))
	{
		// Enable Show Time
		Patch(0x006357B8 + 1, (BYTE)0x86);
	}
}

void PatchSpacer(void)
{
	if (G12GetPrivateProfileInt("SpacerDisableNumlock", 0))
	{
		// Disable NumLock
		Patch(0x0073A0DF, (BYTE)0xEB);
		Patch(0x0079E4E0, (BYTE)0xEB);
	}

	if (G12GetPrivateProfileInt("BarrierIgnoreSkyEffectsSetting", 0))
	{
		// Ignore skyEffects setting in oCSkyControler_Barrier::RenderSkyPre()
		Nop(0x0065B932, 6);
	}
}

void PatchGothic2(void)
{
	if (G12GetPrivateProfileInt("ShowTime", 0))
	{
		// Enable Show Time
		Patch(0x006BF92E + 1, (BYTE)0x86);
	}

	if (G12GetPrivateProfileInt("GodMode", 0))
	{
		// oCNpc::godmode
		Patch(0x00AB2660, 1);
	}
}

void PatchSpacer2(void)
{
	if (G12GetPrivateProfileInt("SpacerDisableNumlock", 0))
	{
		// Disable NumLock
		Patch(0x0048A63F, (BYTE)0xEB);
		Patch(0x0041C426, (BYTE)0xEB);
	}
}

void Init(void)
{
	if (GOTHIC1)
	{
		G12AllocConsole();
		PatchGothic();
	}
	else if (SPACER1)
	{
		G12AllocConsole();
		PatchSpacer();
	}
	else if (GOTHIC2)
	{
		G12AllocConsole();
		PatchGothic2();
	}
	else if (SPACER2)
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
