//==============================================================================

#include "StringCoder.h"

//==============================================================================

BOOL WStringToUTF8String(
	PCWSTR				pwszString,
	PSTR				*ppszString,
	PDWORD				pdwString,
	BOOL				bNoTerminatingCharacter)
{
	PSTR				pszString;
	DWORD				dwString;

#ifndef OS_NIX
	SetLastError(0);
#endif // OS_NIX

	dwString = WideCharToMultiByte(CP_UTF8, 0,
		pwszString, -1, NULL, 0, NULL, NULL);
	if (dwString == 0 
#ifndef OS_NIX
		|| GetLastError() != 0
#endif // OS_NIX
		)
	{
		return FALSE;
	}

	pszString = new CHAR[dwString];
	if (pszString == NULL)
		return FALSE;

	if (!WideCharToMultiByte(CP_UTF8, 0, 
			pwszString, -1, pszString, dwString,
			NULL, NULL))
	{
		delete[] pszString;

		return FALSE;
	}

	if (bNoTerminatingCharacter)
	{
		if (dwString > 0)
			dwString--;
	}

	*ppszString = pszString;
	*pdwString = dwString;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL UTF8StringToWString(
	PCSTR				pszString,
	DWORD				dwString,
	PWSTR				*ppwszString)
{
	LPWSTR				pwszString;
	DWORD				dwSize;
	
#ifndef OS_NIX
	SetLastError(0);
#endif // OS_NIX

	dwSize = MultiByteToWideChar(CP_UTF8, 0,
		pszString, dwString, NULL, 0);
	if (dwSize == 0
#ifndef OS_NIX
		|| GetLastError() != 0
#endif // OS_NIX
		)
	{
		return FALSE;
	}

	pwszString = new WCHAR[dwSize + 1];
	if (pwszString == NULL)
		return FALSE;

	pwszString[dwSize] = L'\0';

	if (!MultiByteToWideChar(CP_UTF8, 0,
			pszString, dwString, pwszString, dwSize))
	{
		delete [] pwszString;
		return FALSE;
	}

	*ppwszString = pwszString;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL StringToWString(
	PCSTR				pszString,
	DWORD				dwMaxLength,
	PWSTR				pwszString,
	UINT				uiEncoding)
{
	DWORD				dwSize;

	if (pszString == NULL)
		pszString = "";

	dwSize = MultiByteToWideChar(uiEncoding, 0,
		pszString, -1, NULL, 0);
	if (dwSize == 0)
		return FALSE;

	if (dwSize > (dwMaxLength + 1))
		return FALSE;

	if (MultiByteToWideChar(uiEncoding, 0,
			pszString, -1, pwszString, dwSize) != dwSize)
	{
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL StringToWString(
	PCSTR				pszString,
	PWSTR				*ppwszString,
	UINT				uiEncoding)
{
	PWSTR				pwszStr;
	DWORD				dwSize;
	
	if (pszString == NULL)
		pszString = "";

	dwSize = MultiByteToWideChar(uiEncoding, 0,
		pszString, -1, NULL, 0);
	if (dwSize == 0)
		return FALSE;

	pwszStr = new WCHAR[dwSize];
	if (pwszStr == 0)
		return FALSE;

	if (MultiByteToWideChar(uiEncoding, 0,
			pszString, -1, pwszStr, dwSize) != dwSize)
	{
		delete [] pwszStr;

		return FALSE;
	}

	*ppwszString = pwszStr;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WStringToString(
	PCWSTR				pwszString,
	DWORD				dwMaxLength,
	PSTR				*ppszString,
	UINT				uiEncoding)
{
	PSTR				pszStr;
	DWORD				dwSize;

#ifndef OS_NIX
	SetLastError(0);
#endif // OS_NIX

	dwSize = WideCharToMultiByte(uiEncoding, 0,
		pwszString, -1, NULL, 0, NULL, NULL);
	if (dwSize == 0
#ifndef OS_NIX
		|| GetLastError() != 0
#endif // OS_NIX
		)
	{
		return FALSE;
	}

	if (dwMaxLength != 0 && (dwSize > (dwMaxLength + 1)))
		return FALSE;

	pszStr = new CHAR[dwSize];
	if (pszStr == NULL)
		return FALSE;

	if (!WideCharToMultiByte(uiEncoding, 0,
			pwszString, -1, pszStr, dwSize,
			NULL, NULL))
	{
		delete[] pszStr;

		return FALSE;
	}

	*ppszString = pszStr;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WStringToString(
	PCWSTR				pwszString,
	DWORD				dwMaxLength,
	PSTR				pszString,
	UINT				uiEncoding)
{
	DWORD				dwSize;

#ifndef OS_NIX
	SetLastError(0);
#endif // OS_NIX

	dwSize = WideCharToMultiByte(uiEncoding, 0,
		pwszString, -1, NULL, 0, NULL, NULL);
	if (dwSize == 0
#ifndef OS_NIX
		|| GetLastError() != 0
#endif // OS_NIX
		)
	{
		return FALSE;
	}

	if (dwSize > (dwMaxLength + 1))
		return FALSE;

	if (!WideCharToMultiByte(uiEncoding, 0,
			pwszString, -1, pszString, dwSize,
			NULL, NULL))
	{
		return FALSE;
	}

	return TRUE;
}

//==============================================================================
