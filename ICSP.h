#ifndef ICSP_H
#define ICSP_H

//======================================================================================================================

#include "ICSPHardware.h"
#include "ICSPHardwareRNG.h"

//======================================================================================================================

#define CSP_NO_ERROR						0

#define CSP_ERROR_LIBRARIES_NOT_LOADED		1
#define CSP_ERROR_NOT_INITIALIZED			2
#define CSP_ERROR_BAD_PARAMETERS			3

#define CSP_ERROR_LIBRARIES_CORRUPTED		11
#define CSP_ERROR_LOAD_CSP_LIBRARY			12
#define CSP_ERROR_ALLOCATE_MEMORY			13
#define CSP_ERROR_PRNG_CALL					14
#define CSP_ERROR_PROGRAM_FAILURE			15

#define CSP_ERROR_HRNG_FAILURE				21
#define CSP_ERROR_BAD_HRNG_SEQUENCE			22
#define CSP_ERROR_HARDWARE_CSP_FAILURE		23

#define CSP_ERROR_DATA_CORRUPTED			31
#define CSP_ERROR_BAD_SIGNATURE				32
#define CSP_ERROR_WRONG_PARAMETERS			33

//----------------------------------------------------------------------------------------------------------------------

#define CSP_STATE_LIBRARIES_LOADED			0x1
#define CSP_STATE_HRNG_INITIALIZED			0x2
#define CSP_STATE_HARDWARE_CSP_INITIALIZED	0x4

//======================================================================================================================

DWORD CSPInitialize(
	CSP			**ppCSP,
	BOOL		bInitializePRNG = TRUE);

VOID CSPFinalize(
	CSP			**ppCSP);

//======================================================================================================================

extern CSP		*g_pCSP;

//======================================================================================================================

#endif // ICSP_H
