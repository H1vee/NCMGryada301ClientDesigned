//==============================================================================

#include "NCMsList.h"

//==============================================================================

NCMsList::NCMsList() : CommonSettings(NULL, "")
{
	SetBaseRegKey(NCMS_LIST_ROOT_KEY,
		NCMS_LIST_REGISTRY_BASE NCMS_LIST_SUBKEY);

	m_dwLastOrderNumber = NCM_NO_ORDER_NUMBER;
}

//------------------------------------------------------------------------------

NCMsList::NCMsList(
	HKEY		hRootKey) : CommonSettings(NULL, "")
{
	SetBaseRegKey((hRootKey == NULL) ?
		NCMS_LIST_ROOT_KEY : hRootKey,
		NCMS_LIST_REGISTRY_BASE NCMS_LIST_SUBKEY);

	m_dwLastOrderNumber = NCM_NO_ORDER_NUMBER;
}

//------------------------------------------------------------------------------

NCMsList::NCMsList(
	HKEY		hRootKey,
	PCSTR		szPath) : CommonSettings(NULL, "")
{
	CHAR		szRegKey[MAX_PATH * 4 + 1];

	if (szPath == NULL || strlen(szPath) == 0)
		strcpy(szRegKey, NCMS_LIST_REGISTRY_BASE);
	else
		strcpy(szRegKey, szPath);

	strcat(szRegKey, NCMS_LIST_SUBKEY);

	SetBaseRegKey((hRootKey == NULL) ?
		NCMS_LIST_ROOT_KEY : hRootKey, szRegKey);

	m_dwLastOrderNumber = NCM_NO_ORDER_NUMBER;
}

//------------------------------------------------------------------------------

NCMsList::~NCMsList()
{
}

//------------------------------------------------------------------------------

INT WINAPI NCMsList::CountModules()
{
	StringList	*pList;
	INT			nCount;

	if (EnumModules(&pList) == FALSE)
		return 0;

	nCount = pList->GetItemsCount();

	delete pList;

	return nCount;
}

//------------------------------------------------------------------------------

#pragma pack(push, 1)
	typedef struct
	{
		DWORD	dwOrderNumber;
		INT		nIndex;
	} MODULE_INFO,
	*PMODULE_INFO;
#pragma pack(pop)

//------------------------------------------------------------------------------

INT CompareModuleInfo(
	const VOID	*pElem1,
	const VOID	*pElem2)
{
	return ((INT) (((PMODULE_INFO) pElem1)->dwOrderNumber) -
		(INT) (((PMODULE_INFO) pElem2)->dwOrderNumber));
};

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::EnumModules(
	StringList	**ppList)
{
	StringList	*pList;
	PMODULE_INFO
				pModulesInfo;
	INT			i;

	if (EnumSubKeys(&pList) == FALSE)
		return FALSE;

	pModulesInfo = new MODULE_INFO [
		pList->GetItemsCount()];
	if (pModulesInfo == NULL)
	{
		delete pList;
		return FALSE;
	}

	for (i = 0; i < pList->GetItemsCount(); i++)
	{
		pModulesInfo[i].nIndex = i;

		if (GetDWORD(pList->GetItem(i),
				NCM_ORDER_NUMBER_VALUE,
				&pModulesInfo[i].dwOrderNumber) == FALSE)
		{
			pModulesInfo[i].dwOrderNumber =
				NCM_NO_ORDER_NUMBER;
			continue;
		}
	}

	qsort(pModulesInfo, pList->GetItemsCount(),
		sizeof(MODULE_INFO), CompareModuleInfo);

	*ppList = new StringList;
	if ((*ppList) == NULL)
	{
		delete [] pModulesInfo;
		delete pList;
		return FALSE;
	}

	for (i = 0; i < pList->GetItemsCount(); i++)
	{
		if (pModulesInfo[i].dwOrderNumber ==
				NCM_NO_ORDER_NUMBER)
			break;

		if ((*ppList)->AddItem(
				pList->GetItem(
					pModulesInfo[i].nIndex)) == FALSE)
		{
			delete [] pModulesInfo;
			delete pList;
			return FALSE;
		}

		m_dwLastOrderNumber =
			pModulesInfo[i].dwOrderNumber;
	}

	delete [] pModulesInfo;
	delete pList;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::IsModulesExists()
{
	StringList	*pList;
	INT			nCount;

	if (EnumModules(&pList) == FALSE)
		return FALSE;

	nCount = pList->GetItemsCount();

	delete pList;

	if (nCount == 0)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::AddModule(
	PSTR		pszName)
{
	BOOL		bResult;

    if (IsSubKeyExist(pszName))
        return FALSE;

    if (CreateSubKey(pszName) == FALSE)
        return FALSE;

	bResult = SetDWORD(pszName,
		NCM_ORDER_NUMBER_VALUE, ++m_dwLastOrderNumber);

	if (!bResult)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::SetModule(
	PSTR		pszName,
	PSTR		pszSN,
	PSTR		pszAddress,
	PSTR		pszAddressMask)
{
	BOOL		bResult;

	if (IsSubKeyExist(pszName) == FALSE)
		return FALSE;

	bResult = SetString(pszName,
		NCM_SN_VALUE, pszSN);

	bResult &= SetString(pszName,
		NCM_ADDRESS_VALUE, pszAddress);

	bResult &= SetString(pszName,
		NCM_ADDRESS_MASK_VALUE, pszAddressMask);

	if (!bResult)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::GetModule(
	PSTR		pszName,
	PSTR		pszSN,
	PSTR		pszAddress,
	PSTR		pszAddressMask)
{
	BOOL		bResult;

	if (IsSubKeyExist(pszName) == FALSE)
		return FALSE;

	bResult = GetString(pszName,
		NCM_SN_VALUE, pszSN,
		NCM_SN_LENGTH);

	bResult &= GetString(pszName,
		NCM_ADDRESS_VALUE, pszAddress,
		NCM_ADDRESS_MAX_LENGTH);

	if (pszAddressMask != NULL)
	{
		bResult &= GetString(pszName,
			NCM_ADDRESS_MASK_VALUE, pszAddressMask,
			NCM_ADDRESS_MAX_LENGTH);
	}

	if (!bResult)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::SetModuleInitialPort(
	PSTR		pszName,
	INT			iPoint,
	PSTR		pszPort)
{
	BOOL		bResult;

	if (IsSubKeyExist(pszName) == FALSE)
		return FALSE;

	CHAR		szValueName[MAX_PATH + 1];

	sprintf(szValueName, NCM_INITIAL_PORT_VALUE, 
		iPoint);

	bResult = SetString(pszName,
		szValueName, pszPort);

	if (!bResult)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::GetModuleInitialPort(
	PSTR		pszName,
	INT			iPoint,
	PSTR		pszPort)
{
	BOOL		bResult;

	if (IsSubKeyExist(pszName) == FALSE)
		return FALSE;

	CHAR		szValueName[MAX_PATH + 1];

	sprintf(szValueName, NCM_INITIAL_PORT_VALUE, 
		iPoint);

	bResult = GetString(pszName,
		szValueName, pszPort,
		NCM_PORT_MAX_LENGTH);

	if (!bResult)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::DeleteModule(
	PSTR		pszName)
{
	BOOL		bResult;

	bResult = DeleteSubKey(pszName);

	if (!bResult)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI NCMsList::DeleteModules()
{
	StringList 	*pList;
	BOOL		bResult = TRUE;

	if (EnumModules(&pList) == FALSE)
		return TRUE;

	if (pList->GetItemsCount() == 0)
	{
		delete pList;

		return TRUE;
	}

	for (int i = 0; i < pList->GetItemsCount(); i++)
	{
		bResult &= DeleteSubKey(pList->GetItem(i));
		if (bResult == FALSE)
			break;
	}

	delete pList;

	return bResult;
}

//==============================================================================
