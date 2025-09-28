//======================================================================================================================

#include "CSP.h"

//======================================================================================================================

CSP					*g_pCSP = NULL;

//======================================================================================================================

DWORD CSPInitialize(
	CSP				**ppCSP,
	BOOL			bInitializePRNG)
{
	DWORD			dwError;

	if(ppCSP == NULL)
		ppCSP = &g_pCSP;

	*ppCSP = new CSP();
	if(*ppCSP == NULL)
		return CSP_ERROR_ALLOCATE_MEMORY;
	
	dwError = (*ppCSP)->Initialize();
	if(dwError != CSP_NO_ERROR)
	{
		delete *ppCSP;
		*ppCSP = NULL;

		return dwError;
	}

	if (bInitializePRNG)
	{
		dwError = (*ppCSP)->InitializePRNG(
			NULL, NULL, NULL);
		if(dwError != CSP_NO_ERROR)
		{
			delete *ppCSP;
			*ppCSP = NULL;

			return dwError;
		}
	}

	return CSP_NO_ERROR;
}

//----------------------------------------------------------------------------------------------------------------------

VOID CSPFinalize(
	CSP				**ppCSP)
{
	if(ppCSP == NULL)
		ppCSP = &g_pCSP;

	if(*ppCSP != NULL)
	{
		delete *ppCSP;
		*ppCSP = NULL;
	}
}

//======================================================================================================================
