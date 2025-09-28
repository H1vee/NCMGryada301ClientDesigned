#ifndef QR_CODE_H
#define QR_CODE_H

//==============================================================================

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else
#include <windows.h>
#endif

//------------------------------------------------------------------------------

#include "IQRCode.h"

//==============================================================================

BOOL QRCodeLoad();

BOOL QRCodeGetInterface(
	IQRCode		**ppInterface);

VOID QRCodeUnload();

//==============================================================================

#endif // QR_CODE_H 
