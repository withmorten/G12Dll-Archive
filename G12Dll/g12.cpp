#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdint.h>
#include "MemoryMgr.h"

#define G12INI_SECTION "G12"

#include "G12.h"

FILE *conin, *conout;

void
PatchGothic(void)
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

void
PatchSpacer(void)
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

const char *Gothic1AppName = "Gothic - 2.6 (fix)";
const char *Gothic1WorldZen = "WORLD.ZEN";
const char *NoSound = "NOSOUND";

void
PatchGothic2(void)
{
	if (G12GetPrivateProfileInt("Gothic1Mode", 0))
	{
		// Fix App Title
		Patch(0x0089D9AC, Gothic1AppName);

		// New game starts WORLD.ZEN
		Patch(0x00429A23 + 1, Gothic1WorldZen);
		Patch(0x00429A52 + 1, Gothic1WorldZen);

		// No GAMESTART menu music
		Patch(0x004DB7EE + 1, NoSound);
		Patch(0x004DB815 + 1, NoSound);
	}

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

	if (G12GetPrivateProfileInt("G12Barrier", 0)) {
		LoadLibrary("g12barrier.dll");
	}
}

void
PatchSpacer2(void)
{
	if (G12GetPrivateProfileInt("SpacerDisableNumlock", 0))
	{
		// Disable NumLock
		Patch(0x0048A63F, (BYTE)0xEB);
		Patch(0x0041C426, (BYTE)0xEB);
	}
}

void
Init(void)
{
	if (G12GetPrivateProfileInt("AllocConsole", 0))
	{
		AllocConsole();
		freopen_s(&conin, "conin$", "r", stdin);
		freopen_s(&conout, "conout$", "w", stdout);
		freopen_s(&conout, "conout$", "w", stderr);
	}

	if (*(int *)0x004F3E10 == 0x5618EC83) // GothicMod.exe
	{
		PatchGothic();
	}
	else if (*(int *)0x00836A52 == 0x102474FF) // spacer.exe
	{
		PatchSpacer();
	}
	else if (*(int *)0x00502D70 == 0x5614EC83) // Gothic2.exe
	{
		PatchGothic2();
	}
	else if (*(int *)0x008523A2 == 0x102474FF) // Spacer2.exe
	{
		PatchSpacer2();
	}
}

BOOL WINAPI
DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}
