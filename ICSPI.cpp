//======================================================================================================================

#include "CSPI.h"

//======================================================================================================================

CSPI				*g_pCSPI = NULL;

//======================================================================================================================

DWORD CSPIInitialize(
	CSPI			**ppCSPI)
{
	DWORD			dwError;

	if(ppCSPI == NULL)
		ppCSPI = &g_pCSPI;

	*ppCSPI = new CSPI();
	if(*ppCSPI == NULL)
		return CSPI_ERROR_ALLOCATE_MEMORY;
	
	dwError = (*ppCSPI)->Initialize();
	if(dwError != CSPI_NO_ERROR)
	{
		delete *ppCSPI;
		*ppCSPI = NULL;

		return dwError;
	}

	dwError = (*ppCSPI)->InitializePRNG(NULL, NULL, NULL);
	if(dwError != CSPI_NO_ERROR)
	{
		delete *ppCSPI;
		*ppCSPI = NULL;

		return dwError;
	}

	return CSPI_NO_ERROR;
}

//----------------------------------------------------------------------------------------------------------------------

VOID CSPIFinalize(
	CSPI			**ppCSPI)
{
	if(ppCSPI == NULL)
		ppCSPI = &g_pCSPI;

	if(*ppCSPI != NULL)
	{
		delete *ppCSPI;
		*ppCSPI = NULL;
	}
}

//======================================================================================================================
