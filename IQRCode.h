#ifndef IQR_CODE_H
#define IQR_CODE_H

//==============================================================================

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else
#include <windows.h>
#endif

//==============================================================================

#define QR_CODE_MIN_TEXT_DATA_LENGTH		1
#define QR_CODE_MAX_TEXT_DATA_LENGTH		(64 * 1024)

//------------------------------------------------------------------------------

#define QR_CODE_MIN_IMAGE_SIZE				8
#define QR_CODE_MAX_IMAGE_SIZE				(8 * 1024)

//------------------------------------------------------------------------------

#define QR_CODE_MIN_MIN_MODULE_PIXEL_SIZE	1
#define QR_CODE_MAX_MIN_MODULE_PIXEL_SIZE	128

#define QR_CODE_DEF_MIN_MODULE_PIXEL_SIZE	1

//------------------------------------------------------------------------------

#define QR_CODE_ECC_LEVEL_LOW				0
#define QR_CODE_ECC_LEVEL_MEDIUM			1
#define QR_CODE_ECC_LEVEL_QUARTILE			2
#define QR_CODE_ECC_LEVEL_HIGH				3

#define QR_CODE_DEF_ECC_LEVEL				QR_CODE_ECC_LEVEL_MEDIUM

//==============================================================================

class IQRCode
{
public:
	virtual VOID	WINAPI Release() PURE;

	virtual BOOL	WINAPI Generate(
		PSTR	pszTextData,
		INT		nImageSize,
		INT		nMinModulePixelSize,
		INT		nECCLevel,
		PSTR	pszImageFile) PURE;

	virtual BOOL	WINAPI GenerateBinary(
		PSTR	pszTextData,
		INT		nImageSize,
		INT		nMinModulePixelSize,
		INT		nECCLevel,
		PBYTE	*ppImage,
		PDWORD	pdwImage) PURE;

	virtual VOID	WINAPI Free(
		PBYTE	pImage,
		DWORD	dwImage) PURE;
};

//==============================================================================

#endif // IQR_CODE_H
