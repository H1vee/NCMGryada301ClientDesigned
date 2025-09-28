//==============================================================================

#include "QRCode.h"
//==============================================================================

typedef BOOL (WINAPI *QR_CODE_INTERFACE_FUNC) (IQRCode **);

//==============================================================================

#ifdef OS_MAC
const PCSTR                             QR_CODE_LIB_FILE_NAME = "qrcode.dylib";
#elif  OS_NIX
const PCSTR				QR_CODE_LIB_FILE_NAME = "qrcode.so";
#else
const PCSTR				QR_CODE_LIB_FILE_NAME = "QRCode.dll";
#endif

const PCSTR				QR_CODE_GET_INTERFACE_FUNC_NAME	= 
							"QRCodeGetInterface";

static BOOL				s_dwRefCount = 0;
static HMODULE			s_hDll = NULL;

static QR_CODE_INTERFACE_FUNC	s_pfnGetInterface;

//==============================================================================

BOOL QRCodeLoad()
{
#ifndef PC_STATIC_LIBS
	if (!s_hDll)
	{
#ifdef PC_LIBS_IN_CURRENT
		CHAR szDLLFile[MAX_PATH * 4 + 1];
		GetCurrentDirectory(MAX_PATH * 4, szDLLFile);

		if(szDLLFile[strlen(szDLLFile) - 1] != '\\')
			strcat(szDLLFile, "\\");

		strcat(szDLLFile, QR_CODE_LIB_FILE_NAME);
		s_hDll = LoadLibraryA(szDLLFile);
#else // PC_LIBS_IN_CURRENT
		s_hDll = LoadLibraryA(QR_CODE_LIB_FILE_NAME);


#endif // PC_LIBS_IN_CURRENT
		if (!s_hDll)
			return FALSE;

		s_pfnGetInterface = (QR_CODE_INTERFACE_FUNC)
			GetProcAddress(s_hDll,
				QR_CODE_GET_INTERFACE_FUNC_NAME);

		if (!s_pfnGetInterface)
		{
			FreeLibrary(s_hDll);
			s_hDll = NULL;

			return FALSE;
		}
	}

	s_dwRefCount++;

	return TRUE;
#else // PC_STATIC_LIBS
	return FALSE;
#endif // PC_STATIC_LIBS
}

//==============================================================================

BOOL QRCodeGetInterface(
	IQRCode		**ppInterface)
{
	if (!s_hDll)
		return FALSE;

	return s_pfnGetInterface(ppInterface);
}

//==============================================================================

VOID QRCodeUnload()
{
#ifndef PC_STATIC_LIBS
	if (s_hDll && --s_dwRefCount == 0)
	{
		FreeLibrary(s_hDll);
		s_hDll = NULL;
	}
#endif // PC_STATIC_LIBS
}

//==============================================================================
