#ifndef STRING_CODER_H
#define STRING_CODER_H

//==============================================================================

#ifdef OS_NIX
	#include "OSIntermediate.h"
#else
	#include <windows.h>
#endif // OS_NIX

//==============================================================================

BOOL WStringToUTF8String(
	PCWSTR				pwszString,
	PSTR				*ppszString,
	PDWORD				pdwString,
	BOOL				bNoTerminatingCharacter = FALSE);

BOOL UTF8StringToWString(
	PCSTR				pszString,
	DWORD				dwString,
	PWSTR				*ppwszString);

BOOL StringToWString(
	PCSTR				pszString,
	DWORD				dwMaxLength,
	PWSTR				pwszString,
	UINT				uiSrcEncoding = 1251);

BOOL StringToWString(
	PCSTR				pszString,
	PWSTR				*ppwszString,
	UINT				uiSrcEncoding = 1251);

BOOL WStringToString(
	PCWSTR				pwszString,
	DWORD				dwMaxLength,
	PSTR				*ppszString,
	UINT				uiDstEncoding = 1251);

BOOL WStringToString(
	PCWSTR				pwszString,
	DWORD				dwMaxLength,
	PSTR				pszString,
	UINT				uiDstEncoding = 1251);

//==============================================================================

#endif // STRING_CODER_H
