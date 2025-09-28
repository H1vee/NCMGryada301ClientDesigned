//=============================================================================

#include "NCHostCP.h"

//=============================================================================

#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#if defined(_MSC_VER) && _MSC_VER < 1900
#ifndef snprintf

#define snprintf c99_snprintf

__inline int c99_snprintf(
	char *Dest, size_t DestSize, const char *Format, ...)
{
	int nCount;
	va_list ArgList;

	va_start(ArgList, Format);

	nCount = -1;

	if (DestSize != 0)
	{
		nCount = _vsnprintf_s(
			Dest, DestSize, _TRUNCATE, Format, ArgList);
	}

	if (nCount == -1)
		nCount = _vscprintf(Format, ArgList);

	va_end(ArgList);

	return nCount;
}

#endif // snprintf
#endif // _MSC_VER && _MSC_VER < 1900

//=============================================================================

static DWORD		s_dwRefCount = 0;
static NCHostCP		*s_pNCHostICP;

//=============================================================================

NCHostCP::NCHostCP()
{
	hLibrary = NULL;
}

//-----------------------------------------------------------------------------

NCHostCP::~NCHostCP()
{
	Unload();
}

//-----------------------------------------------------------------------------

BOOL NCHostCP::Load(
	PCSTR					pszLocation)
{
	if(hLibrary != NULL)
		return TRUE;

#ifndef NC_HOST_INTERNAL
	if (pszLocation == NULL || pszLocation[0] == 0)
	{
		hLibrary = LoadLibraryA(NC_HOST_CP_LIB_NAME);
	}
	else
	{
		CHAR				szLibraryName[MAX_PATH * 4 + 1];
		DWORD				dwLocationLength;

		dwLocationLength = snprintf(szLibraryName,
			MAX_PATH * 4 + 1, "%s", pszLocation);
		if (dwLocationLength > MAX_PATH * 4)
			return FALSE;

		if (szLibraryName[dwLocationLength - 1] == '\\')
			dwLocationLength--;

		if (dwLocationLength + sizeof(NC_HOST_CP_LIB_NAME) >
				MAX_PATH * 4)
		{
			return FALSE;
		}

		snprintf(szLibraryName + dwLocationLength,
			MAX_PATH * 4 + 1 - dwLocationLength,
			"\\%s", NC_HOST_CP_LIB_NAME);

		hLibrary = LoadLibraryA(szLibraryName);
	}
#else // NC_HOST_INTERNAL
	hLibrary = OSLoadLibrary(NC_HOST_CP_LIB_NAME);
#endif // NC_HOST_INTERNAL
	if(!hLibrary)
		return FALSE;

	pGetInterface = (PNC_HOST_CP_GET_INTERFACE) 
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostGetInterface");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostGetInterface");
#endif // NC_HOST_INTERNAL

	pFreeInterface = (PNC_HOST_CP_FREE_INTERFACE) 
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostFreeInterface");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostFreeInterface");
#endif // NC_HOST_INTERNAL

	pGetInterfaceEx = (PNC_HOST_CP_GET_INTERFACE_EX) 
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostGetInterfaceEx");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostGetInterfaceEx");
#endif // NC_HOST_INTERNAL

	pFreeInterfaceEx = (PNC_HOST_CP_FREE_INTERFACE_EX) 
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostFreeInterfaceEx");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostFreeInterfaceEx");
#endif // NC_HOST_INTERNAL

	pGetInterfaceCAGateway = (PNC_HOST_CP_GET_INTERFACE_CA_GATEWAY)
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostGetInterfaceCAGateway");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostGetInterfaceCAGateway");
#endif // NC_HOST_INTERNAL

	pFreeInterfaceCAGateway = (PNC_HOST_CP_FREE_INTERFACE_CA_GATEWAY)
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostFreeInterfaceCAGateway");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostFreeInterfaceCAGateway");
#endif // NC_HOST_INTERNAL

	if (pGetInterface == NULL ||
		pFreeInterface == NULL ||
		pGetInterfaceEx == NULL ||
		pFreeInterfaceEx == NULL ||
		pGetInterfaceCAGateway == NULL ||
		pFreeInterfaceCAGateway == NULL)
	{
#ifndef NC_HOST_INTERNAL
		FreeLibrary(hLibrary);
#else // NC_HOST_INTERNAL
		OSUnloadLibrary(hLibrary);
#endif // NC_HOST_INTERNAL
		hLibrary = NULL;

		return FALSE;
	}

	pGetInterfaceJSONServer = (PNC_HOST_CP_GET_INTERFACE_JSON_SERVER)
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostGetInterfaceJSONServer");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostGetInterfaceJSONServer");
#endif // NC_HOST_INTERNAL

	pFreeInterfaceJSONServer = (PNC_HOST_CP_FREE_INTERFACE_JSON_SERVER)
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostFreeInterfaceJSONServer");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostFreeInterfaceJSONServer");
#endif // NC_HOST_INTERNAL

	pGetVersion = (PNC_HOST_CP_GET_VERSION)
#ifndef NC_HOST_INTERNAL
		GetProcAddress(hLibrary, "NCHostGetVersion");
#else // NC_HOST_INTERNAL
		OSGetFunctionAddress(hLibrary, "NCHostGetVersion");
#endif // NC_HOST_INTERNAL

	return TRUE;
}

//-----------------------------------------------------------------------------

VOID NCHostCP::Unload()
{
	if(hLibrary != NULL)
	{
#ifndef NC_HOST_INTERNAL
		FreeLibrary(hLibrary);
#else // NC_HOST_INTERNAL
		OSUnloadLibrary(hLibrary);
#endif // NC_HOST_INTERNAL
		hLibrary = NULL;
	}
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE NCHostCP::GetInterface()
{
	if (hLibrary == NULL)
		return NULL;

	return pGetInterface();
}

//-----------------------------------------------------------------------------

VOID NCHostCP::FreeInterface(
	PNC_HOST_CP_INTERFACE	pInterface)
{
	if (hLibrary == NULL)
		return;

	pFreeInterface(pInterface);
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE_EX NCHostCP::GetInterfaceEx()
{
	if (hLibrary == NULL)
		return NULL;

	return pGetInterfaceEx();
}

//-----------------------------------------------------------------------------

VOID NCHostCP::FreeInterfaceEx(
	PNC_HOST_CP_INTERFACE_EX	pInterface)
{
	if(hLibrary == NULL)
		return;

	pFreeInterfaceEx(pInterface);
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE_CA_GATEWAY
NCHostCP::GetInterfaceCAGateway()
{
	if (hLibrary == NULL)
		return NULL;

	return pGetInterfaceCAGateway();
}

//-----------------------------------------------------------------------------

VOID NCHostCP::FreeInterfaceCAGateway(
	PNC_HOST_CP_INTERFACE_CA_GATEWAY
							pInterface)
{
	if(hLibrary == NULL)
		return;

	pFreeInterfaceCAGateway(pInterface);
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE_JSON_SERVER
NCHostCP::GetInterfaceJSONServer()
{
	if (hLibrary == NULL)
		return NULL;

	if(pGetInterfaceJSONServer == NULL)
		return NULL;

	return pGetInterfaceJSONServer();
}

//-----------------------------------------------------------------------------

VOID NCHostCP::FreeInterfaceJSONServer(
	PNC_HOST_CP_INTERFACE_JSON_SERVER
							pInterface)
{
	if(hLibrary == NULL)
		return;

	if(pFreeInterfaceJSONServer == NULL)
		return;

	pFreeInterfaceJSONServer(pInterface);
}

//-----------------------------------------------------------------------------

UINT NCHostCP::GetVersion()
{
	if(hLibrary == NULL)
		return NC_HOST_CP_NONE_VERSION;

	if(pGetVersion == NULL)
		return NC_HOST_CP_NONE_VERSION;

	return pGetVersion();
}

//-----------------------------------------------------------------------------

#ifndef NC_HOST_INTERNAL
VOID NCHostCP::ReportError(
	PSTR								pszCaption,
	PNC_HOST_CP_INTERFACE	pInterface,
	DWORD								dwError,
	PSTR								pszError,
	BOOL								bShow,
	HWND								hParentWindow)
{
	CHAR	szError[NC_HOST_CP_MAX_ERROR_DESCR_LENGTH + 1];
	CHAR	szErrorShow[NC_HOST_CP_MAX_ERROR_DESCR_LENGTH + 1];

	pInterface->GetErrorDescr(dwError, szError);

	if (pszCaption)
	{
		if (pszError)
		{
			snprintf(pszError,
				NC_HOST_CP_MAX_ERROR_DESCR_LENGTH + 1,
				"%s. Опис помилки: %s", pszCaption, szError);
		}

		if (bShow)
		{
			snprintf(szErrorShow,
				NC_HOST_CP_MAX_ERROR_DESCR_LENGTH + 1,
				"%s.\nОпис помилки: %s", pszCaption, szError);
		}
	}
	else
	{
		if (pszError)
		{
			snprintf(pszError,
				NC_HOST_CP_MAX_ERROR_DESCR_LENGTH + 1,
				"%s", szError);
		}

		if (bShow)
		{
			snprintf(szErrorShow,
				NC_HOST_CP_MAX_ERROR_DESCR_LENGTH + 1,
				"%s", szError);
		}
	}

	if (bShow)
	{
		MessageBoxA(hParentWindow,
			szErrorShow,
			"Повідомлення оператору",
			MB_TASKMODAL | MB_OK | MB_ICONERROR);
	}
}
#endif // NC_HOST_INTERNAL

//==============================================================================

BOOL NCHostICPInitialize()
{
	if (s_dwRefCount == 0)
	{
		s_pNCHostICP = new NCHostCP();
		if (s_pNCHostICP == NULL)
			return FALSE;

		if (!s_pNCHostICP->Load())
		{
			delete s_pNCHostICP;

			return FALSE;
		}
	}

	++s_dwRefCount;

	return TRUE;
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE NCHostICPGetInterface()
{
	if (s_dwRefCount == 0)
		return NULL;

	return s_pNCHostICP->GetInterface();
}

//-----------------------------------------------------------------------------

VOID NCHostICPFreeInterface(
	PNC_HOST_CP_INTERFACE	pInterface)
{
	if (s_dwRefCount == 0)
		return;

	s_pNCHostICP->FreeInterface(pInterface);
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE_EX NCHostICPGetInterfaceEx()
{
	if (s_dwRefCount == 0)
		return NULL;

	return s_pNCHostICP->GetInterfaceEx();
}

//-----------------------------------------------------------------------------

VOID NCHostICPFreeInterfaceEx(
	PNC_HOST_CP_INTERFACE_EX	pInterface)
{
	if (s_dwRefCount == 0)
		return;

	s_pNCHostICP->FreeInterfaceEx(pInterface);
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE_CA_GATEWAY NCHostICPGetInterfaceCAGateway()
{
	if (s_dwRefCount == 0)
		return NULL;

	return s_pNCHostICP->GetInterfaceCAGateway();
}

//-----------------------------------------------------------------------------

VOID NCHostICPFreeInterfaceCAGateway(
	PNC_HOST_CP_INTERFACE_CA_GATEWAY
									pInterface)
{
	if (s_dwRefCount == 0)
		return;

	s_pNCHostICP->FreeInterfaceCAGateway(pInterface);
}

//-----------------------------------------------------------------------------

PNC_HOST_CP_INTERFACE_JSON_SERVER NCHostICPGetInterfaceJSONServer()
{
	if (s_dwRefCount == 0)
		return NULL;

	return s_pNCHostICP->GetInterfaceJSONServer();
}

//-----------------------------------------------------------------------------

VOID NCHostICPFreeInterfaceJSONServer(
	PNC_HOST_CP_INTERFACE_JSON_SERVER
									pInterface)
{
	if (s_dwRefCount == 0)
		return;

	s_pNCHostICP->FreeInterfaceJSONServer(pInterface);
}

//-----------------------------------------------------------------------------

UINT NCHostICPGetVersion()
{
	if (s_dwRefCount == 0)
		return NC_HOST_CP_NONE_VERSION;

	return s_pNCHostICP->GetVersion();
}

//-----------------------------------------------------------------------------

VOID NCHostICPFinalize()
{
	if (s_dwRefCount > 0 && --s_dwRefCount == 0)
		delete s_pNCHostICP;
}

//==============================================================================
