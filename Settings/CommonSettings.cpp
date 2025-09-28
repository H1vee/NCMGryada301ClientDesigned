//==============================================================================

#include "CommonSettings.h"

//==============================================================================

StringList::StringList()
	: m_nItems(0), m_pFirstItem(NULL), m_pLastItem(NULL)
{
}

//------------------------------------------------------------------------------

StringList::~StringList()
{
	Clear();
}

//------------------------------------------------------------------------------

VOID WINAPI StringList::Clear()
{
	PSTRING_LIST_NODE	pNextItem;

	while (m_pFirstItem)
	{
		pNextItem = m_pFirstItem->pNextNode;

		delete [] m_pFirstItem->pszNodeData;
		delete m_pFirstItem;

		m_pFirstItem = pNextItem;
	}

	m_pLastItem = NULL;
	m_nItems = 0;
}

//------------------------------------------------------------------------------

INT WINAPI StringList::GetItemsCount()
{
	return m_nItems;
}

//------------------------------------------------------------------------------

PSTR WINAPI StringList::GetItem(
	INT	nItem)
{
	PSTRING_LIST_NODE	pItem;

	if (nItem >= m_nItems)
		return NULL;

	pItem = m_pFirstItem;

	while (nItem --)
		pItem = pItem->pNextNode;

	return pItem->pszNodeData;
}

//------------------------------------------------------------------------------

BOOL WINAPI StringList::AddItem(
	PSTR	pszItem)
{
	PSTRING_LIST_NODE	pNewItem;

	pNewItem = new STRING_LIST_NODE;
	if (pNewItem == NULL)
		return FALSE;

	pNewItem->pNextNode = NULL;

	pNewItem->pszNodeData = new CHAR [strlen(pszItem) + 1];
	if (pNewItem->pszNodeData == NULL)
	{
		delete pNewItem;

		return FALSE;
	}

	strcpy(pNewItem->pszNodeData, pszItem);

	if (m_pLastItem)
	{
		m_pLastItem->pNextNode = pNewItem;
		m_pLastItem = pNewItem;
	}
	else
	{
		m_pFirstItem = m_pLastItem = pNewItem;
	}

	m_nItems ++;

	return TRUE;
}

//==============================================================================

CommonSettings::CommonSettings(
	HKEY	hRootKey,
	PCSTR	szPath)
{
	SetBaseRegKey(hRootKey, szPath);

#ifndef OS_NIX
	m_hAdvApi32 = NULL;
	m_RegDeleteKeyEx = NULL;
    //CHANGED
    m_hAdvApi32 = LoadLibraryA("Advapi32.dll");
	if (m_hAdvApi32)
	{
		m_RegDeleteKeyEx = (pRegDeleteKeyEx)
			GetProcAddress(m_hAdvApi32, "RegDeleteKeyExA");
		if (m_RegDeleteKeyEx == NULL)
		{
			FreeLibrary(m_hAdvApi32);
			m_hAdvApi32 = NULL;
		}
	}
#endif // OS_NIX
}

//------------------------------------------------------------------------------

CommonSettings::~CommonSettings()
{
#ifndef OS_NIX
	FreeLibrary(m_hAdvApi32);
	m_hAdvApi32 = NULL;
	m_RegDeleteKeyEx = NULL;
#endif // OS_NIX
}

//==============================================================================

VOID CommonSettings::SetBaseRegKey(
	HKEY	hRootKey,
	PCSTR	szPath)
{
	m_hRootKey = hRootKey;
	strcpy(m_szRegKey, szPath);
}

//------------------------------------------------------------------------------

VOID CommonSettings::GetBaseRegKey(
	HKEY	*phRootKey,
	PSTR	pszPath)
{
	*phRootKey = m_hRootKey;
	strcpy(pszPath, m_szRegKey);
}

//==============================================================================

DWORD CommonSettings::RegGetKeyWOW64()
{
#ifndef OS_NIX
	OSVERSIONINFO 	Version;

	Version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&Version);

	if(Version.dwMajorVersion > 5)
		return KEY_WOW64_32KEY;

	if(Version.dwMajorVersion == 5 &&
		Version.dwMinorVersion != 0)
		return KEY_WOW64_32KEY;
#endif // OS_NIX

	return 0;
}

//==============================================================================

BOOL CommonSettings::OpenRegKey(
	HKEY	*pKey,
	BOOL	bWrite)
{
	if (RegOpenKeyExA(m_hRootKey, m_szRegKey, 0,
		RegGetKeyWOW64() | KEY_READ | ((bWrite) ? KEY_WRITE : 0),
		pKey) != ERROR_SUCCESS)
	{
		if (RegCreateKeyExA(m_hRootKey, m_szRegKey, 0,
			NULL, REG_OPTION_NON_VOLATILE,
			RegGetKeyWOW64() | KEY_READ | ((bWrite) ? KEY_WRITE : 0),
			NULL, pKey, NULL) != ERROR_SUCCESS)
		{
			*pKey = NULL;

			return FALSE;
		}
	}

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::GetDWORD(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	PDWORD	pdwValue)
{
	HKEY	hBaseKey, hKey;
	DWORD	dwType = REG_DWORD;
	DWORD	dwSize = sizeof(DWORD);

	if (!OpenRegKey(&hBaseKey))
		return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);

		return FALSE;
	}

	if (RegQueryValueExA(hKey, szValueName, NULL,
		&dwType, NULL, NULL) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);

		return FALSE;
	}

	if (dwType != REG_DWORD)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);

		return FALSE;
	}

	if (RegQueryValueExA(hKey, szValueName,
		NULL, &dwType, (PBYTE) pdwValue, &dwSize) !=
		ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);

		return FALSE;
	}

	RegCloseKey(hBaseKey);
	RegCloseKey(hKey);

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::GetUINT(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	PUINT	puiValue)
{
	DWORD	dwTemp;
	BOOL	bResult;

	bResult = GetDWORD(szSubKey, szValueName,
		&dwTemp);
	if (!bResult)
		return FALSE;

	if (puiValue != NULL)
		*puiValue = (UINT) dwTemp;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::GetBOOL(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	PBOOL	pblValue)
{
	DWORD	dwTemp;
	BOOL	bResult;

	bResult = GetDWORD(szSubKey, szValueName,
		&dwTemp);
	if (!bResult)
		return FALSE;

	if (pblValue != NULL)
		*pblValue = (BOOL) dwTemp;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::GetString(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	PSTR	pszValue,
	DWORD	dwMaxSize)
{
	HKEY	hBaseKey, hKey;
	DWORD	dwType = REG_SZ;
	DWORD	dwSize = dwMaxSize;

	if (!OpenRegKey(&hBaseKey))
		return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		return FALSE;
	}

	if (RegQueryValueExA(hKey, szValueName, NULL,
		&dwType, NULL, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);
		return FALSE;
	}

	if (dwType != REG_SZ || dwSize > (dwMaxSize + 1))
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);
		return FALSE;
	}

	if (RegQueryValueExA(hKey, szValueName, NULL,
		&dwType, (PBYTE) pszValue, &dwSize) !=
		ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);

		return FALSE;
	}

	RegCloseKey(hBaseKey);
	RegCloseKey(hKey);

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::SetDWORD(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	DWORD	dwValue)
{
	HKEY	hBaseKey, hKey;

	if (!OpenRegKey(&hBaseKey, TRUE))
		return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_WRITE,
		&hKey) != ERROR_SUCCESS)
	{
		if (RegCreateKeyExA(hBaseKey, szSubKey, 0,
			NULL, REG_OPTION_NON_VOLATILE,
			RegGetKeyWOW64() | KEY_WRITE, NULL, &hKey, NULL) !=
			ERROR_SUCCESS)
		{
			RegCloseKey(hBaseKey);

			return FALSE;
		}
	}

	if (RegSetValueExA(hKey, szValueName, 0, REG_DWORD,
		(PBYTE) &dwValue, sizeof(DWORD)) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);

		return FALSE;
	}

	RegCloseKey(hBaseKey);
	RegCloseKey(hKey);

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::SetUINT(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	UINT	uiValue)
{
	return SetDWORD(szSubKey, szValueName,
		(DWORD) uiValue);
}

//------------------------------------------------------------------------------

BOOL CommonSettings::SetBOOL(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	BOOL	bValue)
{
	return SetDWORD(szSubKey, szValueName,
		(bValue) ? 1 : 0);
}

//------------------------------------------------------------------------------

BOOL CommonSettings::SetString(
	PCSTR	szSubKey,
	PCSTR	szValueName,
	PCSTR	szValue)
{
	HKEY	hBaseKey, hKey;

	if (!OpenRegKey(&hBaseKey, TRUE))
		return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_WRITE,
		&hKey) != ERROR_SUCCESS)
	{
		if (RegCreateKeyExA(hBaseKey, szSubKey, 0,
			NULL, REG_OPTION_NON_VOLATILE,
			RegGetKeyWOW64() | KEY_WRITE, NULL, &hKey, NULL) !=
			ERROR_SUCCESS)
		{
			RegCloseKey(hBaseKey);

			return FALSE;
		}
	}

	if (RegSetValueExA(hKey, szValueName, 0, REG_SZ,
		(PBYTE) szValue, (DWORD) strlen(szValue) + 1) !=
		ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);
		RegCloseKey(hKey);

		return FALSE;
	}

	RegCloseKey(hBaseKey);
	RegCloseKey(hKey);

	return TRUE;
}

//==============================================================================

BOOL CommonSettings::CopyRegistryKey(
	HKEY	hSourceRootKey,
	PSTR	pszSourceKey,
	HKEY	hDestRegRoot,
	PSTR	pszDestRegPath)
{
	HKEY	hKey1, hKey2;
	CHAR	szRegKeyName[MAX_PATH * 4 + 1];
	CHAR	szRegValueName[MAX_PATH * 4 + 1];
	DWORD	cbRegKeyName, cbRegValueName, cbRegValue,
			dwRegValueType, dwIndex;
	PBYTE	pbRegValue;

	if (RegOpenKeyExA(hSourceRootKey, pszSourceKey, 0,
		RegGetKeyWOW64() | KEY_ALL_ACCESS, &hKey1) != ERROR_SUCCESS)
	{
		return FALSE;
	}

	if (RegCreateKeyExA(hDestRegRoot, pszDestRegPath, 0, NULL, 0,
		RegGetKeyWOW64() | KEY_ALL_ACCESS, NULL, &hKey2, NULL) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey1);

		return FALSE;
	}

	dwIndex = 0;
	cbRegKeyName = MAX_PATH;

	while (RegEnumKeyA(hKey1, dwIndex, szRegKeyName, cbRegKeyName) == ERROR_SUCCESS)
	{
		if (!CopyRegistryKey(hKey1, szRegKeyName,
			hKey2, szRegKeyName))
		{
			RegCloseKey(hKey1);
			RegCloseKey(hKey2);

			return FALSE;
		}

		dwIndex++;
	}

	RegCloseKey(hKey1);
	RegCloseKey(hKey2);

	if (RegOpenKeyExA(hSourceRootKey, pszSourceKey, 0,
		RegGetKeyWOW64() | KEY_ALL_ACCESS, &hKey1) != ERROR_SUCCESS)
	{
		return FALSE;
	}

	if (RegCreateKeyExA(hDestRegRoot, pszDestRegPath, 0, NULL, 0,
		RegGetKeyWOW64() | KEY_ALL_ACCESS, NULL, &hKey2, NULL) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey1);

		return FALSE;
	}

	dwIndex = 0;
	cbRegValueName = MAX_PATH;
	cbRegValue = 0;

	while (RegEnumValueA(hKey1, dwIndex, szRegValueName, &cbRegValueName, NULL,
		NULL, NULL, &cbRegValue) == ERROR_SUCCESS)
	{
		pbRegValue =(PBYTE) VirtualAlloc(NULL, cbRegValue,
			MEM_COMMIT, PAGE_READWRITE);
		if (!pbRegValue)
		{
			RegCloseKey(hKey1);
			RegCloseKey(hKey2);

			return FALSE;
		}

		if (RegQueryValueExA(hKey1, szRegValueName, NULL, &dwRegValueType,
			pbRegValue, &cbRegValue) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey1);
			RegCloseKey(hKey2);

			VirtualFree(pbRegValue, 0, MEM_RELEASE);

			return FALSE;
		}

		if (RegSetValueExA(hKey2, szRegValueName, NULL, dwRegValueType,
			pbRegValue, cbRegValue) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey1);
			RegCloseKey(hKey2);

			VirtualFree(pbRegValue, 0, MEM_RELEASE);

			return FALSE;
		}

		VirtualFree(pbRegValue, 0, MEM_RELEASE);

		cbRegValueName = MAX_PATH;
		cbRegValue = 0;
		dwIndex++;
	}

	RegCloseKey(hKey1);
	RegCloseKey(hKey2);

	return TRUE;
}

//==============================================================================

BOOL CommonSettings::EnumSubKeys(
	StringList	**ppList)
{
	HKEY		hKey;
	CHAR		szName[MAX_PATH * 4 + 1];
	DWORD		dwIndex = 0;
	LONG		nResult;

	if (!OpenRegKey(&hKey))
		return FALSE;

	*ppList = new StringList();
	if ((*ppList) == NULL)
	{
		RegCloseKey(hKey);

		return FALSE;
	}

	do
    {
        //CHANGED
        nResult = RegEnumKeyA(hKey, dwIndex,
            szName, sizeof(szName));
		if (nResult == ERROR_SUCCESS)
		{
			if ((*ppList)->AddItem(szName) == FALSE)
			{
				delete (*ppList);
				RegCloseKey(hKey);

				return FALSE;
			}
		}

		dwIndex ++;
	} while (nResult == ERROR_SUCCESS);

	RegCloseKey(hKey);

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::CreateSubKey(
	PCSTR	szSubKey)
{
	HKEY	hBaseKey, hKey;

    if (!OpenRegKey(&hBaseKey, TRUE))
        return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_READ | KEY_WRITE,
		&hKey) != ERROR_SUCCESS)
	{
		if (RegCreateKeyExA(hBaseKey, szSubKey, 0,
			NULL, REG_OPTION_NON_VOLATILE,
			RegGetKeyWOW64() | KEY_READ | KEY_WRITE,
			NULL, &hKey, NULL) != ERROR_SUCCESS)
		{
			RegCloseKey(hBaseKey);

			return FALSE;
		}
	}

	RegCloseKey(hBaseKey);
	RegCloseKey(hKey);

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL CommonSettings::IsSubKeyExist(
	PCSTR	szSubKey)
{
	HKEY	hBaseKey, hKey;

	if (!OpenRegKey(&hBaseKey))
		return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_READ,
		&hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);

		return FALSE;
	}

	RegCloseKey(hBaseKey);
	RegCloseKey(hKey);

	return TRUE;
}

//==============================================================================

BOOL CommonSettings::DeleteSubKey(
	PCSTR	szSubKey)
{
#ifndef OS_NIX
	HKEY	hBaseKey;

	if (!OpenRegKey(&hBaseKey, TRUE))
		return FALSE;

	if (m_RegDeleteKeyEx != NULL)
	{
		if (m_RegDeleteKeyEx(hBaseKey, szSubKey,
			RegGetKeyWOW64(), 0) != ERROR_SUCCESS)
		{
			RegCloseKey(hBaseKey);

			return FALSE;
		}
	}
	else
	{
		if (RegDeleteKeyA(hBaseKey, szSubKey) !=
			ERROR_SUCCESS)
		{
			RegCloseKey(hBaseKey);

			return FALSE;
		}
	}

	RegCloseKey(hBaseKey);

	return TRUE;
#else // OS_NIX
	HKEY	hBaseKey;

	if (!OpenRegKey(&hBaseKey, TRUE))
		return FALSE;

	if (RegDeleteKeyA(hBaseKey, szSubKey) !=
		ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);

		return FALSE;
	}

	RegCloseKey(hBaseKey);

	return TRUE;
#endif
}

//==============================================================================

BOOL CommonSettings::EnumValues(
	PCSTR		szSubKey,
	StringList	**ppList)
{
	HKEY		hBaseKey, hKey;
	CHAR		szName[MAX_PATH * 4 + 1];
	CHAR		szValueName[MAX_PATH * 4 + 1];
	DWORD		dwNameSize;
	DWORD		dwValueNameSize;
	DWORD		dwIndex = 0;
	DWORD		dwType = REG_SZ;
	LONG		nResult;

	if (!OpenRegKey(&hBaseKey))
		return FALSE;

	if (RegOpenKeyExA(hBaseKey, szSubKey, 0,
		RegGetKeyWOW64() | KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hBaseKey);

		return FALSE;
	}

	*ppList = new StringList();
	if ((*ppList) == NULL)
	{
		RegCloseKey(hKey);
		RegCloseKey(hBaseKey);

		return FALSE;
	}

	do
	{
		dwNameSize = sizeof(szName);
		dwValueNameSize = sizeof(szValueName);
        //CHANGED
        nResult = RegEnumValueA(hKey, dwIndex,
			szName, &dwNameSize, NULL, &dwType,
			(PBYTE) szValueName, &dwValueNameSize);
		if (nResult == ERROR_SUCCESS)
		{
			if ((*ppList)->AddItem(szValueName) == FALSE)
			{
				delete (*ppList);
				RegCloseKey(hKey);
				RegCloseKey(hBaseKey);

				return FALSE;
			}
		}

		dwIndex ++;
	} while (nResult == ERROR_SUCCESS);

	RegCloseKey(hKey);
	RegCloseKey(hBaseKey);

	return TRUE;
}

//==============================================================================
