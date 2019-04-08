#define GOTHIC101 (*(int *)0x00512D50 == 0x8A18EC83) // Gothic.exe  1.01e
#define GOTHIC108 (*(int *)0x004F3E10 == 0x5618EC83) // Gothic.exe  1.08k_mod
#define SPACER15  (*(int *)0x00836A52 == 0x102474FF) // Spacer.exe  1.5
#define GOTHIC26  (*(int *)0x00502D70 == 0x5614EC83) // Gothic2.exe 2.6
#define SPACER26  (*(int *)0x008523A2 == 0x102474FF) // Spacer2.exe 2.6

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
