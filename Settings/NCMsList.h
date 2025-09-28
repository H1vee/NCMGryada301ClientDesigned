#ifndef NCMS_LIST_H
#define NCMS_LIST_H

//==============================================================================

#include "CommonSettings.h"

//==============================================================================

#define NCMS_LIST_ROOT_KEY		HKEY_LOCAL_MACHINE
#define NCMS_LIST_REGISTRY_BASE						\
		"SOFTWARE\\"								\
		"Institute of Informational Technologies\\"	\
		"Key Medias\\NCM Gryada-301\\"

//==============================================================================

#define NCMS_LIST_SUBKEY				"Modules\\"

#define NCM_SN_VALUE					"SN"
#define NCM_ADDRESS_VALUE				"Address"
#define NCM_ADDRESS_MASK_VALUE			"AddressMask"
#define NCM_INITIAL_PORT_VALUE			"InitialPort%d"
#define NCM_ORDER_NUMBER_VALUE			"OrderNumber"

#define NCM_NO_ORDER_NUMBER				0xFFFFFFFF

//==============================================================================
	
#define NCM_SN_LENGTH					3
#define NCM_MIN_SN						1
#define NCM_MAX_SN						999

#define NCM_ADDRESS_MAX_LENGTH			15
#define NCM_PORT_MAX_LENGTH				5

#define NCM_INITIAL_POINTS				6

#define NCM_INITIAL_POINT_FIRST_PORT	3011

//==============================================================================

class NCMsList : CommonSettings
{
	DWORD						m_dwLastOrderNumber;

public:
	NCMsList();

	NCMsList(
		HKEY 					hRootKey);

	NCMsList(
		HKEY 					hRootKey,
		PCSTR 					szPath);

	~NCMsList();

public:
	INT	WINAPI CountModules();

	BOOL	WINAPI EnumModules(
		StringList				**ppList);

	BOOL	WINAPI IsModulesExists();

	BOOL	WINAPI AddModule(
		PSTR					pszName);

	BOOL	WINAPI SetModule(
		PSTR					pszName,
		PSTR					pszSN,
		PSTR					pszAddress,
		PSTR					pszAddressMask);

	BOOL	WINAPI GetModule(
		PSTR					pszName,
		PSTR					pszSN,
		PSTR					pszAddress,
		PSTR					pszAddressMask);

	BOOL	WINAPI SetModuleInitialPort(
		PSTR					pszName,
		INT						iPoint,
		PSTR					pszPort);

	BOOL	WINAPI GetModuleInitialPort(
		PSTR					pszName,
		INT						iPoint,
		PSTR					pszPort);

	BOOL	WINAPI DeleteModule(
		PSTR					pszName);

	BOOL	WINAPI DeleteModules();

};

//==============================================================================

#endif // NCMS_LIST_H
