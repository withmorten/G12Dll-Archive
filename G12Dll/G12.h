#define G12INI_PATH1 ".\\G12.ini"
#define G12INI_PATH2 ".\\System\\G12.ini"

UINT G12GetPrivateProfileInt(LPCTSTR lpKeyName, INT nDefault)
{
	FILE *f = fopen(G12INI_PATH1, "r");

	if (f)
	{
		fclose(f);

		return GetPrivateProfileInt(G12INI_SECTION, lpKeyName, nDefault, G12INI_PATH1);
	}

	return GetPrivateProfileInt(G12INI_SECTION, lpKeyName, nDefault, G12INI_PATH2);
}

DWORD G12GetPrivateProfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize)
{
	FILE *f = fopen(G12INI_PATH1, "r");

	if (f)
	{
		fclose(f);

		return GetPrivateProfileString(G12INI_SECTION, lpKeyName, lpDefault, lpReturnedString, nSize, G12INI_PATH1);
	}

	return GetPrivateProfileString(G12INI_SECTION, lpKeyName, lpDefault, lpReturnedString, nSize, G12INI_PATH2);
}
