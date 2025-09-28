#ifndef COMMON_SETTINGS_H
#define COMMON_SETTINGS_H

//==============================================================================

#ifdef OS_NIX
    #include "./OSIntermediate/OSIntermediate.h"
	#define StringList	NCMG301StringList
#else // OS_NIX
	#include <windows.h>
	#include <stdio.h>
#endif // OS_NIX

//==============================================================================

#define	COMMON_SETTINGS_VALUE					\
	"SOFTWARE\\"								\
	"Institute of Informational Technologies\\"

//==============================================================================

class StringList
{
private:
typedef struct tagNode
{
	tagNode				*pNextNode;
	PSTR				pszNodeData;
} STRING_LIST_NODE, *PSTRING_LIST_NODE;

	INT					m_nItems;
	PSTRING_LIST_NODE	m_pFirstItem;
	PSTRING_LIST_NODE	m_pLastItem;

public:
	StringList();

	~StringList();

public:
	VOID	WINAPI Clear();

	INT	WINAPI GetItemsCount();

	PSTR WINAPI GetItem(
		INT		nItem);

	BOOL WINAPI AddItem(
		PSTR	pszItem);
};

//==============================================================================

class CommonSettings
{
#ifndef OS_NIX
private:
typedef LONG (WINAPI *pRegDeleteKeyEx)(
	HKEY	hKey,
	PCSTR	pSubKey,
	REGSAM	samDesired,
	DWORD	Reserved);

	HMODULE		m_hAdvApi32;
	pRegDeleteKeyEx	m_RegDeleteKeyEx;
#endif

private:
	HKEY		m_hRootKey;
	CHAR		m_szRegKey[MAX_PATH * 4 + 1];

protected:
	CommonSettings(
		HKEY	hRootKey,
		PCSTR	szPath);

	~CommonSettings();

protected:
	VOID	SetBaseRegKey(
		HKEY	hRootKey,
		PCSTR	szPath);

	VOID	GetBaseRegKey(
		HKEY	*phRootKey,
		PSTR	pszPath);


	DWORD RegGetKeyWOW64();


	BOOL OpenRegKey(
		HKEY	*pKey,
		BOOL	bWrite = FALSE);

	BOOL GetDWORD(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		PDWORD	pdwValue);

	BOOL GetUINT(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		PUINT	puiValue);

	BOOL GetBOOL(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		PBOOL	pblValue);

	BOOL GetString(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		PSTR	pszValue,
		DWORD	dwMaxSize);

	BOOL SetDWORD(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		DWORD	dwValue);

	BOOL SetUINT(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		UINT	uiValue);

	BOOL SetBOOL(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		BOOL	bValue);

	BOOL SetString(
		PCSTR	szSubKey,
		PCSTR	szValueName,
		PCSTR	szValue);


	BOOL CopyRegistryKey(
		HKEY	hSourceRootKey,
		PSTR	pszSourceKey,
		HKEY	hDestRegRoot,
		PSTR	pszDestRegPath);


	BOOL EnumSubKeys(
		StringList	**ppList);

	BOOL CreateSubKey(
		PCSTR	szSubKey);

	BOOL IsSubKeyExist(
		PCSTR	szSubKey);

	BOOL DeleteSubKey(
		PCSTR	szSubKey);

	BOOL EnumValues(
		PCSTR	szSubKey,
		StringList	**ppList);
};

//==============================================================================

#endif // COMMON_SETTINGS_H
