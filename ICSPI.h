#ifndef ICSPI_H
#define ICSPI_H

//======================================================================================================================

#include "ICSPIHardware.h"
#include "ICSPIHardwareRNG.h"

//======================================================================================================================

#define CSPI_NO_ERROR							0

#define CSPI_ERROR_LIBRARIES_NOT_LOADED			1
#define CSPI_ERROR_NOT_INITIALIZED				2
#define CSPI_ERROR_BAD_PARAMETERS				3

#define CSPI_ERROR_LIBRARIES_CORRUPTED			11
#define CSPI_ERROR_LOAD_CSP_LIBRARY				12
#define CSPI_ERROR_ALLOCATE_MEMORY				13
#define CSPI_ERROR_PRNG_CALL					14
#define CSPI_ERROR_PROGRAM_FAILURE				15

#define CSPI_ERROR_HRNG_FAILURE					21
#define CSPI_ERROR_BAD_HRNG_SEQUENCE			22
#define CSPI_ERROR_HARDWARE_CSP_FAILURE			23

#define CSPI_ERROR_DATA_CORRUPTED				31
#define CSPI_ERROR_BAD_SIGNATURE				32
#define CSPI_ERROR_WRONG_PARAMETERS				33

//----------------------------------------------------------------------------------------------------------------------

#define CSPI_STATE_CSP_LIBRARIES_LOADED			0x1
#define CSPI_STATE_HRNG_INITIALIZED				0x2
#define CSPI_STATE_HARDWARE_CSP_INITIALIZED		0x4

//======================================================================================================================

DWORD CSPIInitialize(
	CSPI			**ppCSPI);

VOID CSPIFinalize(
	CSPI			**ppCSPI);

//======================================================================================================================

extern CSPI										*g_pCSPI;

//======================================================================================================================

#endif // ICSPI_H
