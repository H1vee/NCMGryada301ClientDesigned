#ifndef ICSP_HARDWARE_RNG_H
#define ICSP_HARDWARE_RNG_H

//======================================================================================================================

#include "CSPBase.h"

//======================================================================================================================

class ICSPHardwareRNG
{
public:
	virtual BOOL WINAPI GenerateSequence(
			PBYTE 	pbSequence,
			DWORD 	dwSequence) PURE;
};

//======================================================================================================================

#endif // ICSP_HARDWARE_RNG_H
