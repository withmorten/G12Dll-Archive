#define G12INI_PATH1 ".\\G12.ini"
#define G12INI_PATH2 ".\\System\\G12.ini"

UINT
G12GetPrivateProfileInt(LPCTSTR lpKeyName, INT nDefault)
{
	INT nReturn;

	nReturn = GetPrivateProfileInt(G12INI_SECTION, lpKeyName, nDefault, G12INI_PATH1);

	if (GetLastError() == ERROR_PATH_NOT_FOUND)
	{
		nReturn = GetPrivateProfileInt(G12INI_SECTION, lpKeyName, nDefault, G12INI_PATH2);
	}

	return nReturn;
}

DWORD
G12GetPrivateProfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize)
{
	DWORD dwReturn;

	dwReturn = GetPrivateProfileString(G12INI_SECTION, lpKeyName, lpDefault, lpReturnedString, nSize, G12INI_PATH1);

	if (GetLastError() == ERROR_PATH_NOT_FOUND)
	{
		dwReturn = GetPrivateProfileString(G12INI_SECTION, lpKeyName, lpDefault, lpReturnedString, nSize, G12INI_PATH2);
	}

	return dwReturn;
}
