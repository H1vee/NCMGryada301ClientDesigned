#ifndef ICSPI_HARDWARE_RNG_H
#define ICSPI_HARDWARE_RNG_H

//======================================================================================================================

#include "CSPIBase.h"

//======================================================================================================================

class ICSPIHardwareRNG
{
public:
	virtual BOOL WINAPI GenerateSequence(
			PBYTE 	pbSequence,
			DWORD 	dwSequence) PURE;
};

//======================================================================================================================

#endif // ICSPI_HARDWARE_RNG_H
