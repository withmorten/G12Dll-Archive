#define GOTHIC1 (*(int *)0x004F3E10 == 0x5618EC83) // GothicMod.exe
#define SPACER1 (*(int *)0x00836A52 == 0x102474FF) // spacer.exe
#define GOTHIC2 (*(int *)0x00502D70 == 0x5614EC83) // Gothic2.exe
#define SPACER2 (*(int *)0x008523A2 == 0x102474FF) // Spacer2.exe

#define G12INI_PATH1 ".\\G12.ini"
#define G12INI_PATH2 ".\\System\\G12.ini"

UINT G12GetPrivateProfileInt(LPCTSTR lpKeyName, INT nDefault)
{
	FILE *f = fopen(G12INI_PATH1, "r");

	if (f)
	{
		fclose(f);

		return GetPrivateProfileInt(G12DLL_NAME, lpKeyName, nDefault, G12INI_PATH1);
	}

	fclose(f);

	return GetPrivateProfileInt(G12DLL_NAME, lpKeyName, nDefault, G12INI_PATH2);
}

DWORD G12GetPrivateProfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize)
{
	FILE *f = fopen(G12INI_PATH1, "r");

	if (f)
	{
		fclose(f);

		return GetPrivateProfileString(G12DLL_NAME, lpKeyName, lpDefault, lpReturnedString, nSize, G12INI_PATH1);
	}

	fclose(f);

	return GetPrivateProfileString(G12DLL_NAME, lpKeyName, lpDefault, lpReturnedString, nSize, G12INI_PATH2);
}

FILE *conin, *conout;

void G12AllocConsole(void)
{
	if (G12GetPrivateProfileInt("AllocConsole", FALSE))
	{
		AllocConsole();
		freopen_s(&conin, "conin$", "r", stdin);
		freopen_s(&conout, "conout$", "w", stdout);
		freopen_s(&conout, "conout$", "w", stderr);
	}
}
