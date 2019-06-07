// first 4 bytes of WinMain for each version
#define GOTHIC101E	(*(int *)0x00512D50 == 0x8A18EC83) // Gothic.exe  1.01e
#define GOTHIC104D	(*(int *)0x004F56E0 == 0x8A18EC83) // Gothic.exe  1.04d
#define GOTHIC107C	(*(int *)0x004FD330 == 0x8A18EC83) // Gothic.exe  1.07c
#define GOTHIC108J	(*(int *)0x004FFFA0 == 0x8A18EC83) // Gothic.exe  1.08j
#define GOTHIC108KM	(*(int *)0x004F3E10 == 0x5618EC83) // Gothic.exe  1.08k_mod
#define SPACER150	(*(int *)0x00836A52 == 0x102474FF) // Spacer.exe  1.50
#define GOTHIC26	(*(int *)0x00502D70 == 0x5614EC83) // Gothic2.exe 2.6
#define SPACER26	(*(int *)0x008523A2 == 0x102474FF) // Spacer2.exe 2.6

char G12IniPath[MAX_PATH];

UINT G12GetPrivateProfileInt(LPCTSTR lpKeyName, INT nDefault)
{
	return GetPrivateProfileInt(G12DLL_NAME, lpKeyName, nDefault, G12IniPath);
}

UINT G12GetPrivateProfileBool(LPCTSTR lpKeyName, INT nDefault)
{
	return G12GetPrivateProfileInt(lpKeyName, nDefault);
}

DWORD G12GetPrivateProfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize)
{
	return GetPrivateProfileString(G12DLL_NAME, lpKeyName, lpDefault, lpReturnedString, nSize, G12IniPath);
}

FLOAT G12GetPrivateProfileFloat(LPCTSTR lpKeyName, LPCTSTR lpDefault)
{
	CHAR lpReturnedString[MAX_PATH];

	G12GetPrivateProfileString(lpKeyName, lpDefault, lpReturnedString, sizeof(lpReturnedString));

	return (FLOAT)atof(lpReturnedString);
}

FILE *conin, *conout;

void G12AllocConsole(void)
{
	// does not belong here, but whatever
	_getcwd(G12IniPath, sizeof(G12IniPath));
	strncat(G12IniPath, "\\G12.ini", sizeof(G12IniPath));

	if (G12GetPrivateProfileBool("AllocConsole", FALSE))
	{
		AllocConsole();
		freopen_s(&conin, "conin$", "r", stdin);
		freopen_s(&conout, "conout$", "w", stdout);
		freopen_s(&conout, "conout$", "w", stderr);
	}
}
