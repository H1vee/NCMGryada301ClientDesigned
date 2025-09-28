//=============================================================================

#include "NCRemoteControlCP.h"

//=============================================================================

NCRemoteControlCP::NCRemoteControlCP()
{
	hDLL = NULL;
}

//-----------------------------------------------------------------------------

NCRemoteControlCP::~NCRemoteControlCP()
{
	if(hDLL != NULL)
		FreeLibrary(hDLL);
}

//-----------------------------------------------------------------------------

BOOL NCRemoteControlCP::Load()
{
	if(hDLL != NULL)
		return TRUE;

	hDLL = LoadLibraryA(NC_REMOTE_CONTROL_CP_DLL_NAME);
	if(!hDLL)
		return FALSE;

	pGetInterface = (PNC_REMOTE_CONTROL_CP_GET_INTERFACE) 
		GetProcAddress(hDLL, "NCRemoteControlGetInterface");
	pFreeInterface = (PNC_REMOTE_CONTROL_CP_FREE_INTERFACE) 
		GetProcAddress(hDLL, "NCRemoteControlFreeInterface");
	pGetInterfaceEx = (PNC_REMOTE_CONTROL_CP_GET_INTERFACE_EX) 
		GetProcAddress(hDLL, "NCRemoteControlGetInterfaceEx");
	pFreeInterfaceEx = (PNC_REMOTE_CONTROL_CP_FREE_INTERFACE_EX) 
		GetProcAddress(hDLL, "NCRemoteControlFreeInterfaceEx");

	if (pGetInterface == NULL ||
		pFreeInterface == NULL ||
		pGetInterfaceEx == NULL ||
		pFreeInterfaceEx == NULL)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;

		return FALSE;
	}

	pGetVersion = (PNC_REMOTE_CONTROL_CP_GET_VERSION)
		GetProcAddress(hDLL, "NCRemoteControlGetVersion");

	return TRUE;
}

//-----------------------------------------------------------------------------

VOID NCRemoteControlCP::Unload()
{
	if (hDLL != NULL)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
	}
}

//-----------------------------------------------------------------------------

PNC_REMOTE_CONTROL_CP_INTERFACE NCRemoteControlCP::GetInterface()
{
	if (hDLL == NULL)
		return NULL;

	return pGetInterface();
}

//-----------------------------------------------------------------------------

VOID NCRemoteControlCP::FreeInterface(
	PNC_REMOTE_CONTROL_CP_INTERFACE	pInterface)
{
	if (hDLL == NULL)
		return;

	pFreeInterface(pInterface);
}

//-----------------------------------------------------------------------------

PNC_REMOTE_CONTROL_CP_INTERFACE_EX NCRemoteControlCP::GetInterfaceEx()
{
	if (hDLL == NULL)
		return NULL;

	return pGetInterfaceEx();
}

//-----------------------------------------------------------------------------

VOID NCRemoteControlCP::FreeInterfaceEx(
	PNC_REMOTE_CONTROL_CP_INTERFACE_EX	pInterface)
{
	if (hDLL == NULL)
		return;

	pFreeInterfaceEx(pInterface);
}

//-----------------------------------------------------------------------------

UINT NCRemoteControlCP::GetVersion()
{
	if(hDLL == NULL)
		return NC_HOST_CP_NONE_VERSION;

	if(pGetVersion == NULL)
		return NC_HOST_CP_NONE_VERSION;

	return pGetVersion();
}

//-----------------------------------------------------------------------------

VOID NCRemoteControlCP::ReportError(
	PSTR								pszCaption,
	PNC_REMOTE_CONTROL_CP_INTERFACE		pInterface,
	DWORD								dwError,
	PSTR								pszError,
	BOOL								bShow,
	HWND								hParentWindow)
{
	CHAR	szError[NC_REMOTE_CONTROL_CP_MAX_ERROR_DESCR_LENGTH + 1];
	CHAR	szErrorShow[NC_REMOTE_CONTROL_CP_MAX_ERROR_DESCR_LENGTH + 1];

	pInterface->GetErrorDescr(dwError, szError);

	if (pszCaption)
	{
		if (pszError)
		{
			sprintf(pszError,
				"%s. Опис помилки: %s", pszCaption, szError);
		}

		if (bShow)
		{
			sprintf(szErrorShow,
				"%s.\nОпис помилки: %s", pszCaption, szError);
		}
	}
	else
	{
		if (pszError)
			sprintf(pszError, "%s", szError);

		if (bShow)
			sprintf(szErrorShow, "%s", szError);
	}

	if (bShow)
	{
		MessageBoxA(hParentWindow,
			szErrorShow,
			"Повідомлення оператору",
			MB_TASKMODAL | MB_OK | MB_ICONERROR);
	}
}

//==============================================================================
