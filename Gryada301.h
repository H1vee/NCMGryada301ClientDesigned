#ifndef NCM_GRYADA301_H
#define NCM_GRYADA301_H

//==============================================================================

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else // OS_NIX
#include <windows.h>
#endif // OS_NIX

//==============================================================================

#include "CSP.h"
#include "CSPI.h"

//==============================================================================

#define G301_ADDRESS_MIN_LENGTH 7
#define G301_ADDRESS_MAX_LENGTH 15
#define G301_BACKUP_KM_NAME_MAX_LENGTH 64

#define G301_MAX_DEVICES 256

#define G301_NAME_LENGTH 64
#define G301_SN_LENGTH 3
#define G301_IMAGE_MIN_VERSION_LENGTH 7
#define G301_IMAGE_VERSION_LENGTH 15
#define G301_IMAGE_VERSION_FORMAT "%d.%d.%d.%d"
#define G301_IMAGE_MIN_VERSION 0x01000001 // 1.0.0.1
#define G301_IMAGE_MAX_VERSION 0xFFFFFFFF // 255.255.255.255

#define G301_IMAGE_COMPATIBLE2_VERSION 0x0102042B // 1.2.4.43
#define G301_IMAGE_COMPATIBLE5_VERSION 0x01020430 // 1.2.4.48
#define G301_IMAGE_COMPATIBLE7_VERSION 0x01020436 // 1.2.4.54
#define G301_IMAGE_COMPATIBLE8_VERSION 0x01020437 // 1.2.4.55
#define G301_IMAGE_COMPATIBLE9_VERSION 0x01020439 // 1.2.4.57
#define G301_IMAGE_COMPATIBLE10_VERSION 0x0102043A // 1.2.4.58
#define G301_IMAGE_COMPATIBLE11_VERSION 0x0102043B // 1.2.4.59
#define G301_IMAGE_COMPATIBLE12_VERSION 0x0102043D // 1.2.4.61
#define G301_IMAGE_COMPATIBLE13_VERSION 0x0102043E // 1.2.4.62

#define G301_MIN_SN 1
#define G301_MAX_SN 999

#define G301_MAX_DATA_SIZE (8 * 1024)

#define G301_POINT_NAME_LENGTH 31
#define G301_MAX_DATA_LABEL_LENGTH 64
#define G301_DATA_LABEL_DELIMITER "--"
#define G301_DATA_LABEL_DELIMITER_LENGTH 2

#define G301_MAX_PASSWORD_LENGTH 63

#define G301_CLIENT_NAME_MAX_LENGTH 63
#define G301_CLIENT_LOGIN_MAX_LENGTH 31

#define G301_LOGIN_PASSWORD_DELIMITER "##"
#define G301_LOGIN_PASSWORD_PREFIX G301_LOGIN_PASSWORD_DELIMITER

#define G301_LOGIN_DEF_FAILURES_LIMIT 15

#define G301_LOGIN_MIN_FAILURES_LIMIT 3
#define G301_LOGIN_MAX_FAILURES_LIMIT 255

#define G301_MAX_ERROR_LENGTH 384
#define G301_MAX_EKEY_NAME_LENGTH 16

//------------------------------------------------------------------------------

#define G301_PASSWORD_KM_DELIMITER "::"
#define G301_PASSWORD_KM_PREFIX G301_PASSWORD_KM_DELIMITER

#define G301_PASSWORD_KM_EKEY_CRYSTAL1 "�.���� ��� �������-1"
#define G301_PASSWORD_KM_EKEY_ALMAZ1C "�.���� ��� �����-1�"

#define G301_PASSWORD_KM_EKEY_CRYSTAL1_ALIAS "ekc1"
#define G301_PASSWORD_KM_EKEY_ALMAZ1C_ALIAS "eka1c"

//------------------------------------------------------------------------------

#define G301_MAX_KEYS_OWNER_DESCR_LENGTH 96

#define G301_KEYS_OWNER_NONE_LABEL ""
#define G301_KEYS_OWNER_CA_LABEL "1"
#define G301_KEYS_OWNER_CMP_SERVER_LABEL "2"
#define G301_KEYS_OWNER_TSP_SERVER_LABEL "3"
#define G301_KEYS_OWNER_OCSP_SERVER_LABEL "4"
#define G301_KEYS_OWNER_RA_ADMIN_LABEL "5"
#define G301_KEYS_OWNER_END_USER_LABEL "6"
#define G301_KEYS_OWNER_ALL_LABEL "**"

#define G301_KEYS_OWNER_NONE_DESCR \
	"������������ (��� ���� �� �� �������� �����)"
#define G301_KEYS_OWNER_CA_DESCR "���"
#define G301_KEYS_OWNER_CMP_SERVER_DESCR "CMP-������ ���"
#define G301_KEYS_OWNER_TSP_SERVER_DESCR "TSP-������ ���"
#define G301_KEYS_OWNER_OCSP_SERVER_DESCR "OCSP-������ ���"
#define G301_KEYS_OWNER_RA_ADMIN_DESCR "������������ ��������� ���"
#define G301_KEYS_OWNER_END_USER_DESCR "���������� ���"
#define G301_KEYS_OWNER_ALL_DESCR "������������ (�� �����)"

//------------------------------------------------------------------------------

#define G301_MAX_KEYS_ALGOS_DESCR_LENGTH 96

#define G301_KEYS_ALGOS_STATE 0
#define G301_KEYS_ALGOS_INTERNATIONAL 1
#define G301_KEYS_ALGOS_ALL 2

#define G301_KEYS_ALGOS_STATE_DESCR "���������"
#define G301_KEYS_ALGOS_INTERNATIONAL_DESCR "���������"
#define G301_KEYS_ALGOS_ALL_DESCR "������������ (�� �����)"

//------------------------------------------------------------------------------

#define G301_REVISION1_DESCR "���� 1"

//------------------------------------------------------------------------------

#define G301_KEYS_BACKUP_OPERATION_START 1
#define G301_KEYS_BACKUP_OPERATION_GET_STATUS 2
#define G301_KEYS_BACKUP_OPERATION_STOP 3

#define G301_KEYS_BACKUP_OPERATION_NONE 0
#define G301_KEYS_BACKUP_OPERATION_MASK 0xFF

#define G301_KEYS_RESTORE_OPERATION_FLAG_ONLY_CHECK 0x100
#define G301_KEYS_RESTORE_OPERATION_FLAG_DONT_ERASE_ALL 0x200

#define G301_INITIAL_BACKUP_KM_INDEX 0

#define G301_SUB_BACKUP_KM_EKEY "�.����"
#define G301_SUB_BACKUP_KM_DISK "����"
#define G301_SUB_BACKUP_KM_PEER "�����"

//------------------------------------------------------------------------------

#define G301_CLIENT_TYPE_DESCRIPTION_LENGTH 128

#define G301_CLIENT_TYPE_ADMINISTRATOR 1
#define G301_CLIENT_TYPE_OPERATOR 2
#define G301_CLIENT_TYPE_BOTH 3
#define G301_CLIENT_TYPE_CLIENTS_MANAGER 4
#define G301_CLIENT_TYPE_KEYS_MANAGER 5

#define G301_CLIENT_TYPE_ADMINISTRATOR_DESCRIPTION "������������"
#define G301_CLIENT_TYPE_OPERATOR_DESCRIPTION "��������"
#define G301_CLIENT_TYPE_BOTH_DESCRIPTION "������������ �� ��������"

#define G301_CLIENT_TYPE_ADMINISTRATOR_DESCRIPTION_TITLE "������������"
#define G301_CLIENT_TYPE_OPERATOR_DESCRIPTION_TITLE "��������"
#define G301_CLIENT_TYPE_BOTH_DESCRIPTION_TITLE "������������ � ��������"

//------------------------------------------------------------------------------

#define G301_PUBLIC_KEY_TYPE_DS 0x1
#define G301_PUBLIC_KEY_TYPE_KEP 0x2
#define G301_PUBLIC_KEY_TYPE_RSA 0x4
#define G301_PUBLIC_KEY_TYPE_ECDSA 0x8

#define G301_PUBLIC_KEY_TYPE_ALL \
	(G301_PUBLIC_KEY_TYPE_DS | \
	G301_PUBLIC_KEY_TYPE_KEP | \
	G301_PUBLIC_KEY_TYPE_RSA | \
	G301_PUBLIC_KEY_TYPE_ECDSA)

#define G301_MAX_DATA_DESCR_LENGTH 64

#define G301_PUBLIC_KEY_TYPE_DS_DESCRIPTION "³������� �� (���� 4145)"
#define G301_PUBLIC_KEY_TYPE_KEP_DESCRIPTION "³������� ��� (�-�)"
#define G301_PUBLIC_KEY_TYPE_RSA_DESCRIPTION "³������� RSA"
#define G301_PUBLIC_KEY_TYPE_ECDSA_DESCRIPTION "³������� ECDSA"

#define G301_KEYS_TYPE_DS 0x10
#define G301_KEYS_TYPE_KEP 0x20
#define G301_KEYS_TYPE_RSA 0x40
#define G301_KEYS_TYPE_ECDSA 0x80

#define G301_DATA_TYPE_CLIENT 0x100
#define G301_DATA_TYPE_MODULE 0x200

#define G301_KEYS_TYPE_SBOXES 0x400

#define G301_DATA_TYPE_ALL1 \
	(G301_PUBLIC_KEY_TYPE_ALL | \
	G301_KEYS_TYPE_DS | \
	G301_KEYS_TYPE_KEP | \
	G301_KEYS_TYPE_RSA | \
	G301_KEYS_TYPE_ECDSA | \
	G301_DATA_TYPE_CLIENT | \
	G301_DATA_TYPE_MODULE)

#define G301_DATA_TYPE_ALL \
	(G301_DATA_TYPE_ALL1 | \
	G301_KEYS_TYPE_SBOXES)

#define G301_KEYS_TYPE_DS_DESCRIPTION "�� (���� 4145)"
#define G301_KEYS_TYPE_KEP_DESCRIPTION "��� (�-�)"
#define G301_KEYS_TYPE_RSA_DESCRIPTION "RSA"
#define G301_KEYS_TYPE_ECDSA_DESCRIPTION "ECDSA"

#define G301_DATA_TYPE_CLIENT_DESCRIPTION "���� �����������"
#define G301_DATA_TYPE_MODULE_DESCRIPTION "���� ������"

#define G301_KEYS_TYPE_SBOXES_DESCRIPTION "���"

//------------------------------------------------------------------------------

#define G301_PUBLIC_KEY_ID_MAX_LENGTH 32

#define G301_PUBLIC_UA_KEY_ID_LENGTH 32
#define G301_PUBLIC_SHA1_KEY_ID_LENGTH 20

//------------------------------------------------------------------------------

#define G301_CLIENT_SECURITY_FLAGS_NONE 0
#define G301_CLIENT_SECURITY_FLAG_CANT_CHANGE_PASSWORD 0x1
#define G301_CLIENT_SECURITY_FLAG_MUST_CHANGE_PASSWORD 0x2
#define G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_CHANGE_PASSWORD 0x4
#define G301_CLIENT_SECURITY_FLAG_MUST_USE_OTP 0x8
#define G301_CLIENT_SECURITY_FLAG_OTP_IN_USE 0x10

#define G301_CLIENT_SECURITY_FLAGS_UNSUPPORTED 0x80000000

#define G301_CLIENT_SECURITY_FLAGS_ALL \
	(G301_CLIENT_SECURITY_FLAG_CANT_CHANGE_PASSWORD | \
	G301_CLIENT_SECURITY_FLAG_MUST_CHANGE_PASSWORD | \
	G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_CHANGE_PASSWORD | \
	G301_CLIENT_SECURITY_FLAG_MUST_USE_OTP | \
	G301_CLIENT_SECURITY_FLAG_OTP_IN_USE | \
	G301_CLIENT_SECURITY_FLAGS_UNSUPPORTED)

#define G301_CLIENT_SECURITY_FLAGS_NONE_DESCR \
	"�� �����������"
#define G301_CLIENT_SECURITY_FLAG_CANT_CHANGE_PASSWORD_DESCR_TITLE \
	"�������� ���� ������"
#define G301_CLIENT_SECURITY_FLAG_CANT_CHANGE_PASSWORD_DESCR \
	"�������� ���� ������"
#define G301_CLIENT_SECURITY_FLAG_MUST_CHANGE_PASSWORD_DESCR_TITLE \
	"��������� ������ ������"
#define G301_CLIENT_SECURITY_FLAG_MUST_CHANGE_PASSWORD_DESCR \
	"��������� ������ ������"
#define G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_PASS_CHANGE_DESCR_TITLE \
	"�������� �������������� ����"
#define G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_PASS_CHANGE_DESCR	\
	"�������� �������������� ����"
#define G301_CLIENT_SECURITY_FLAG_MUST_USE_OTP_DESCR_TITLE \
	"����'������� OTP-������"
#define G301_CLIENT_SECURITY_FLAG_MUST_USE_OTP_DESCR \
	"����'������� OTP-������"
#define G301_CLIENT_SECURITY_FLAG_OTP_IN_USE_DESCR_TITLE \
	"OTP-������ �����������"
#define G301_CLIENT_SECURITY_FLAG_OTP_IN_USE_DESCR \
	G301_CLIENT_SECURITY_FLAG_OTP_IN_USE_DESCR_TITLE

//------------------------------------------------------------------------------

#define G301_CLIENT_OTP_KEY_LENGTH 20

#define G301_CLIENT_OTP_TIME_STEP_MIN 30
#define G301_CLIENT_OTP_TIME_STEP_MAX 600

#define G301_CLIENT_OTP_TIME_STEP_INC 30

#define G301_CLIENT_OTP_TIME_STEP_DEF 30

#define G301_CLIENT_OTP_DIGITS_MIN 6
#define G301_CLIENT_OTP_DIGITS_MAX 8

#define G301_CLIENT_OTP_DIGITS_DEF 6

//==============================================================================

typedef struct
{
	UINT dwAddress;
	CHAR szAddress[G301_ADDRESS_MAX_LENGTH + 1];
	UINT dwAddressMask;
	CHAR szAddressMask[G301_ADDRESS_MAX_LENGTH + 1];
	UINT dwSN;
	WORD wPort;
	WORD wData;
} G301_MODULE_INFO, *PG301_MODULE_INFO;

typedef struct
{
	UINT dwAddress;
	CHAR szAddress[G301_ADDRESS_MAX_LENGTH + 1];
	UINT dwAddressMask;
	CHAR szAddressMask[G301_ADDRESS_MAX_LENGTH + 1];
	UINT dwSN;
	WORD wPort;
	WORD wData;
	CHAR szName[G301_NAME_LENGTH + 1];
	CHAR szSN[G301_SN_LENGTH + 1];
	CHAR szImageVersion[G301_IMAGE_VERSION_LENGTH + 1];
	DWORDLONG dwlTotalConfigMemory;
	DWORDLONG dwlFreeConfigMemory;
} G301_MODULE_INFO_EX, *PG301_MODULE_INFO_EX;

//------------------------------------------------------------------------------

typedef struct
{
	UINT dwAddress;
	UINT dwAddressMask;
} G301_MODULE_PARAMS, *PG301_MODULE_PARAMS;

typedef struct
{
	UINT dwRouterAddress;
} G301_MODULE_PARAMS2, *PG301_MODULE_PARAMS2;

//------------------------------------------------------------------------------

typedef struct
{
	BOOL blClustered;
	BOOL blMainNode;
	UINT dwExternalAddress;
	UINT dwExternalMask;
	UINT dwInternalAddress;
	UINT dwInternalMask;
	UINT dwPeerExternalAddress;
	UINT dwPeerInternalAddress;
} G301_CLUSTER_PARAMS, *PG301_CLUSTER_PARAMS;

//------------------------------------------------------------------------------

typedef struct
{
	CHAR szName[G301_CLIENT_NAME_MAX_LENGTH + 1];
	CHAR szLogin[G301_CLIENT_LOGIN_MAX_LENGTH + 1];
	UINT dwType;
	CHAR szPassword[G301_MAX_PASSWORD_LENGTH + 1];
	UINT dwAddress;
	UINT uiSecurityFlags;
} G301_CLIENT, *PG301_CLIENT;

//------------------------------------------------------------------------------

typedef struct
{
	CHAR szName[G301_CLIENT_NAME_MAX_LENGTH + 1];
	UINT uiType;
} G301_CLIENT_INFO, *PG301_CLIENT_INFO;

//------------------------------------------------------------------------------

typedef struct
{
	UINT uiFlags;
	UINT uiOTPTimeStep;
	UINT uiOTPDigits;
	UINT uiOTPKeyLength;
	BYTE bOTPKey[G301_CLIENT_OTP_KEY_LENGTH];
} G301_CLIENT_SECURITY, *PG301_CLIENT_SECURITY;

//==============================================================================

typedef PVOID G301MODULE;
typedef G301MODULE *PG301MODULE;

//==============================================================================

#define G301_SUCCESS 0

#define G301_ERROR_BAD_REQUEST 1
#define G301_ERROR_WRONG_PASSWORD 2

#define G301_ERROR_NOT_LOGGED 3
#define G301_ALREADY_LOGGED 4

#define G301_ERROR_NO_SBOXES 5
#define G301_ERROR_NO_DS_KEYS 6
#define G301_ERROR_NO_KEP_KEYS 7
#define G301_ERROR_NO_RSA_KEYS 16
#define G301_ERROR_NO_ECDSA_KEYS 17

#define G301_ERROR_BAD_SBOXES 8
#define G301_ERROR_BAD_DS_KEYS 9
#define G301_ERROR_BAD_KEP_KEYS 10

#define G301_ERROR_WRONG_PUBLIC_KEY 11

#define G301_ERROR_NO_DATA 12
#define G301_ERROR_BAD_DATA 13

#define G301_ERROR_BAD_SIGNATURE 14

#define G301_ERROR_ERROR_BAD_RESPOND 15

#define G301_INTERNAL_ERROR 0xFFFF

#define G301_ERROR_COMMUNICATE 0xFFFFFFFF

//==============================================================================

typedef BOOL (WINAPI *PG301_LOCATE_MODULES)();

typedef BOOL (WINAPI *PG301_ENUM_MODULES)(
	DWORD iModule,
	PG301_MODULE_INFO pInfo);

typedef BOOL (WINAPI *PG301_CONNECT_MODULE)(
	DWORD iModule,
	PG301MODULE phModule);

typedef VOID (WINAPI *PG301_DISCONNECT_MODULE)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_FORMAT)(
	G301MODULE hModule,
	PSTR pszPassword);

typedef DWORD (WINAPI *PG301_LOG_ON)(
	G301MODULE hModule,
	PSTR pszPassword);

typedef DWORD (WINAPI *PG301_LOG_OFF)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_CHANGE_PASSWORD)(
	G301MODULE hModule,
	PSTR pszNewPassword);

typedef DWORD (WINAPI *PG301_GENERATE_RN_SEQUENCE)(
	G301MODULE hModule,
	PBYTE pbSequence,
	DWORD cbSequence);

typedef DWORD (WINAPI *PG301_SET_SBOXES)(
	G301MODULE hModule,
	GOST28147_COMPRESSED_SBOX pECDHSBox,
	GOST28147_COMPRESSED_SBOX pPRNGSBox);

typedef DWORD (WINAPI *PG301_GENERATE_KEYS)(
	G301MODULE hModule,
	BOOL blDSKeys,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ);

typedef DWORD (WINAPI *PG301_HASH_PRIVATE_KEY)(
	G301MODULE hModule,
	GOST34311_HASH pHash);

typedef DWORD (WINAPI *PG301_SIGN_HASH)(
	G301MODULE hModule,
	GOST34311_HASH pHash,
	DSTU4145_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_SIGN_DSTU_HASH)(
	G301MODULE hModule,
	DWORD dwHash,
	DSTU7564_HASH pHash,
	DSTU4145_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_MAKE_COUPLE_SIGN_COMPONENT_S)(
	G301MODULE hModule,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_NUMBER	pKeyK,
	DSTU4145_NUMBER	pCommonComponentR,
	DSTU4145_NUMBER	pComponentS);

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE2)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_VERIFY_SIGN)(
	G301MODULE hModule,
	GOST34311_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_VERIFY_DSTU_SIGN)(
	G301MODULE hModule,
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_SIGN_DSTU_HASH_KEP)(
	G301MODULE hModule,
	DWORD dwHash,
	DSTU7564_HASH pHash,
	DSTU4145_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_CHECK_PUBLIC_KEY)(
	G301MODULE hModule,
	BOOL blDSKey,
	DSTU4145_KEY_Q pKeyQ);

typedef DWORD (WINAPI *PG301_GET_PUBLIC_KEY)(
	G301MODULE hModule,
	BOOL blDSKey,
	DSTU4145_KEY_Q pKeyQ);

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PG301_ENUM_BACKUP_KEY_MEDIAS)(
	INT nIndex,
	PSTR pszName);

typedef DWORD (WINAPI *PG301_BACKUP_KEYS)(
	G301MODULE hModule,
	DWORD dwKeyMedia);

typedef DWORD (WINAPI *PG301_RESTORE_KEYS)(
	G301MODULE hModule,
	DWORD dwKeyMedia);

typedef DWORD (WINAPI *PG301_BACKUP_KEYS_WITH_PASSWORD)(
	G301MODULE hModule,
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword);

typedef DWORD (WINAPI *PG301_RESTORE_KEYS_WITH_PASSWORD)(
	G301MODULE hModule,
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword);

typedef DWORD (WINAPI *PG301_ERASE_KEYS)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_ERASE_BACKUP_KEYS)(
	G301MODULE hModule,
	DWORD dwKeyMedia);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_ENUM_BACKUP_EKEYS_LOCAL)(
	G301MODULE hModule,
	DWORD dwIndex,
	DWORD dwKeyMedia,
	PSTR pszEKey,
	PSTR pszError);

typedef DWORD (WINAPI *PG301_BACKUP_KEYS_REMOTE)(
	G301MODULE hModule,
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword,
	PSTR pszEKey1,
	PSTR pszEKey2,
	PSTR pszRemovableDisk,
	PSTR pszError);

typedef DWORD (WINAPI *PG301_RESTORE_KEYS_REMOTE)(
	G301MODULE hModule,
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword,
	PSTR pszEKey1,
	PSTR pszEKey2,
	PSTR pszRemovableDisk,
	PHANDLE	phKeysDBFile,
	PSTR pszError);

typedef DWORD (WINAPI *PG301_ERASE_BACKUP_KEYS_LOCAL)(
	G301MODULE hModule,
	DWORD dwKeyMedia,
	PSTR pszEKey1,
	PSTR pszEKey2,
	PSTR pszRemovableDisk,
	PSTR pszError);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_PROTECT_SHARED_DATA)(
	G301MODULE hModule,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	PBYTE pbData,
	DWORD cbData,
	GOST28147_MAC pMAC);

typedef DWORD (WINAPI *PG301_UNPROTECT_SHARED_DATA)(
	G301MODULE hModule,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	PBYTE pbData,
	DWORD cbData,
	GOST28147_MAC pMAC);

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE3)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_MAKE_SHARED_KEY)(
	G301MODULE hModule,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_KEY pKey);

typedef DWORD (WINAPI *PG301_STORE_DATA)(
	G301MODULE hModule,
	PBYTE pbData,
	DWORD cbData);

typedef DWORD (WINAPI *PG301_LOAD_DATA)(
	G301MODULE hModule,
	PBYTE pbData,
	PDWORD pcbData);

typedef DWORD (WINAPI *PG301_ERASE_DATA)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_STORE_MODULE_DATA)(
	G301MODULE hModule,
	UINT uiReserved,
	PBYTE pbData,
	DWORD cbData);

typedef DWORD (WINAPI *PG301_LOAD_MODULE_DATA)(
	G301MODULE hModule,
	UINT uiReserved,
	PBYTE pbData,
	PDWORD pcbData);

typedef DWORD (WINAPI *PG301_ERASE_MODULE_DATA)(
	G301MODULE hModule,
	UINT uiReserved);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_SET_PARAMS)(
	G301MODULE hModule,
	PG301_MODULE_PARAMS pParams);

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE4)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_SET_TIME)(
	G301MODULE hModule,
	PSYSTEMTIME pTime);

typedef DWORD (WINAPI *PG301_SET_CLUSTER_PARAMS)(
	G301MODULE hModule,
	PG301_CLUSTER_PARAMS pClusterParams);

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE5)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_SET_PARAMS2)(
	G301MODULE hModule,
	PG301_MODULE_PARAMS2 pParams2);

typedef DWORD (WINAPI *PG301_REBOOT)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_SHUTDOWN)(
	G301MODULE hModule);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE6)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_SET_SET_USE_DS_KEYS_AS_KEP)(
	G301MODULE hModule,
	BOOL blUse);

typedef DWORD (WINAPI *PG301_SIGN_HASH_KEP)(
	G301MODULE hModule,
	GOST34311_HASH pHash,
	DSTU4145_SIGNATURE pSignature);

#ifdef CSP_ECDH_UA
typedef DWORD (WINAPI *PG301_WRAP_SHARED_KEY)(
	G301MODULE hModule,
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	GOST28147_KEY pKey,
	GOST28147_WRAPED_KEY pWrappedKey);

typedef DWORD (WINAPI *PG301_UNWRAP_SHARED_KEY)(
	G301MODULE hModule,
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey);
#endif // CSP_ECDH_UA

typedef DWORD (WINAPI *PG301_DSTU_WRAP_SHARED_KEY)(
	G301MODULE hModule,
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey);

typedef DWORD (WINAPI *PG301_DSTU_UNWRAP_SHARED_KEY)(
	G301MODULE hModule,
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE7)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_GET_CLUSTER_PARAMS)(
	G301MODULE hModule,
	PG301_CLUSTER_PARAMS pClusterParams);

typedef DWORD (WINAPI *PG301_GET_PARAMS2)(
	G301MODULE hModule,
	PG301_MODULE_PARAMS2 pParams2);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_IS_REVISION1)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_SET_DATA_LABEL)(
	G301MODULE hModule,
	BOOL blAppend,
	PSTR pszLabel);

typedef DWORD (WINAPI *PG301_SET_DATA_PASSWORD)(
	G301MODULE hModule,
	PSTR pszPassword);

typedef DWORD (WINAPI *PG301_CHANGE_DATA_PASSWORD)(
	G301MODULE hModule,
	PSTR pszNewPassword);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_GENERATE_RSA_KEYS)(
	G301MODULE hModule,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey);

typedef DWORD (WINAPI *PG301_RSA_SIGN_HASH)(
	G301MODULE hModule,
	SHA_HASH pHash,
	RSA_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_RSA_SIGN_HASH_EX)(
	G301MODULE hModule,
	DWORD dwVersion,
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_CHECK_RSA_PUBLIC_KEY)(
	G301MODULE hModule,
	PRSA_PUBLIC_KEY pPublicKey);

typedef DWORD (WINAPI *PG301_GET_RSA_PUBLIC_KEY)(
	G301MODULE hModule,
	PRSA_PUBLIC_KEY pPublicKey);

typedef DWORD (WINAPI *PG301_RSA_DECRYPT_DATA)(
	G301MODULE hModule,
	PBYTE pbData,
	PDWORD pdwData,
	PRSA_PARAMETERS pParameters,
	BOOL blUnpadData);

typedef DWORD (WINAPI *PG301_GENERATE_ECDSA_KEYS)(
	G301MODULE hModule,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey);

typedef DWORD (WINAPI *PG301_ECDSA_SIGN_HASH)(
	G301MODULE hModule,
	DWORD dwHash,
	SHA_HASH pHash,
	PECDSA_SIGNATURE pSignature);

typedef DWORD (WINAPI *PG301_ECDSA_COUPLE_PART2_STEP)(
	G301MODULE hModule,
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_NUMBER pPaillierPublicKey,
	ECDSA_ENCODED_POINT pComponentR1,
	PAILLIER_NUMBER pEncryptedPrivateKey1,
	ECDSA_NUMBER pCommonComponentR,
	PAILLIER_NUMBER pComponentS2);

typedef DWORD (WINAPI *PG301_CHECK_ECDSA_PUBLIC_KEY)(
	G301MODULE hModule,
	ECDSA_KEY_Q pPublicKey);

typedef DWORD (WINAPI *PG301_GET_ECDSA_PUBLIC_KEY)(
	G301MODULE hModule,
	ECDSA_KEY_Q pPublicKey);

typedef DWORD (WINAPI *PG301_MAKE_ECDSA_COUPLE_COMMON_PUB_KEY)(
	G301MODULE hModule,
	ECDSA_KEY_Q pPublicKeyB,
	ECDSA_KEY_Q pCommonPublicKey);

typedef DWORD (WINAPI *PG301_ECDH_CALCULATE_SHARED_SECRET)(
	G301MODULE hModule,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pRecipientPublicKey,
	ECDSA_NUMBER pSharedSecret);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_GET_FIRST_CLIENTS)(
	G301MODULE hModule,
	PDWORD pdwClients,
	PG301_CLIENT *ppClients);

typedef DWORD (WINAPI *PG301_GET_NEXT_CLIENTS)(
	G301MODULE hModule,
	PDWORD pdwClients,
	PG301_CLIENT *ppClients);

typedef VOID (WINAPI *PG301_FREE_CLIENTS)(
	PG301_CLIENT *ppClients);

typedef DWORD (WINAPI *PG301_ADD_CLIENT)(
	G301MODULE hModule,
	PG301_CLIENT pClient);

typedef DWORD (WINAPI *PG301_CHANGE_CLIENT)(
	G301MODULE hModule,
	PSTR pszClientName,
	PG301_CLIENT pChangedClient);

typedef DWORD (WINAPI *PG301_REMOVE_CLIENT)(
	G301MODULE hModule,
	PSTR pszClientName);

//------------------------------------------------------------------------------

typedef DWORD (WINAPI *PG301_IS_COMPATIBLE8)(
	G301MODULE hModule);

typedef DWORD (WINAPI *PG301_ENUM_PUBLIC_KEYS)(
	G301MODULE hModule,
	BOOL blFirst,
	UINT uiType,
	BOOL blAppendedLabel,
	PSTR pszSubLabel,
	PUINT puiType,
	PSTR pszAppendedLabel,
	PSTR pszPartialLabel);

typedef DWORD (WINAPI *PG301_GET_LABELED_PUBLIC_KEY)(
	G301MODULE hModule,
	BOOL blDSKey,
	PSTR pszLabel,
	BOOL blAppendLabel,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ);

typedef DWORD (WINAPI *PG301_GET_LABELED_RSA_PUBLIC_KEY)(
	G301MODULE hModule,
	PSTR pszLabel,
	BOOL blAppendLabel,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey);

typedef DWORD (WINAPI *PG301_GET_LABELED_ECDSA_PUBLIC_KEY)(
	G301MODULE hModule,
	PSTR pszLabel,
	BOOL blAppendLabel,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey);

typedef DWORD (WINAPI *PG301_FIND_PUBLIC_KEY_BY_ID)(
	G301MODULE hModule,
	UINT uiType,
	BOOL blAppendedLabel,
	PSTR pszSubLabel,
	PBYTE pbKeyID,
	UINT cbKeyID,
	PUINT puiType,
	PSTR pszAppendedLabel,
	PSTR pszPartialLabel);

typedef DWORD (WINAPI *PG301_GET_INFO)(
	G301MODULE hModule,
	PSTR pszName,
	PSTR pszSN,
	PSTR pszImageVersion,
	PDWORDLONG pdwlTotalConfigMemory,
	PDWORDLONG pdwlFreeConfigMemory);

typedef DWORD (WINAPI *PG301_ENUM_DATA)(
	G301MODULE hModule,
	BOOL blFirst,
	UINT uiType,
	BOOL blAppendedLabel,
	PSTR pszSubLabel,
	PUINT puiType,
	PSTR pszAppendedLabel,
	PSTR pszPartialLabel);

typedef DWORD (WINAPI *PG301_ERASE_LABELED_DATA)(
	G301MODULE hModule,
	UINT uiType,
	PSTR pszLabel,
	BOOL blAppendLabel);

typedef DWORD (WINAPI *PG301_RENAME_DATA)(
	G301MODULE hModule,
	UINT uiType,
	PSTR pszLabel,
	BOOL blAppendLabel,
	PSTR pszNewLabel);
	
typedef DWORD (WINAPI *PG301_GET_CLIENT_INFO)(
	G301MODULE hModule,
	PG301_CLIENT_INFO pClientInfo);

typedef DWORD (WINAPI *PG301_GET_CLIENT_SECURITY)(
	G301MODULE hModule,
	PG301_CLIENT_SECURITY pSecurity);

typedef DWORD (WINAPI *PG301_SET_CLIENT_SECURITY)(
	G301MODULE hModule,
	PG301_CLIENT_SECURITY pSecurity);

//==============================================================================

typedef struct
{
	PG301_LOCATE_MODULES LocateModules;
	PG301_ENUM_MODULES EnumModules;
	PG301_CONNECT_MODULE ConnectModule;
	PG301_DISCONNECT_MODULE DisconnectModule;
	PG301_FORMAT Format;
	PG301_LOG_ON LogOn;
	PG301_LOG_OFF LogOff;
	PG301_CHANGE_PASSWORD ChangePassword;
	PG301_GENERATE_RN_SEQUENCE GenerateRNSequence;
	PG301_SET_SBOXES SetSBoxes;
	PG301_GENERATE_KEYS GenerateKeys;
	PG301_HASH_PRIVATE_KEY HashPrivateKey;
	PG301_SIGN_HASH SignHash;
	PG301_CHECK_PUBLIC_KEY CheckPublicKey;
	PG301_ENUM_BACKUP_KEY_MEDIAS EnumBackupKeyMedias;
	PG301_BACKUP_KEYS BackupKeys;
	PG301_RESTORE_KEYS RestoreKeys;
	PG301_ERASE_KEYS EraseKeys;
	PG301_PROTECT_SHARED_DATA ProtectSharedData;
	PG301_UNPROTECT_SHARED_DATA UnprotectSharedData;
	PG301_STORE_DATA StoreData;
	PG301_LOAD_DATA LoadData;
	PG301_ERASE_DATA EraseData;
	PG301_SET_PARAMS SetParams;
	PG301_IS_COMPATIBLE2 IsCompatible2;
	PG301_VERIFY_SIGN VerifySign;
	PG301_IS_COMPATIBLE2 IsCompatible3;
	PG301_MAKE_SHARED_KEY MakeSharedKey;
	PG301_IS_COMPATIBLE4 IsCompatible4;
	PG301_SET_TIME SetTime;
	PG301_SET_CLUSTER_PARAMS SetClusterParams;
	PG301_IS_COMPATIBLE4 IsCompatible5;
	PG301_SET_PARAMS2 SetParams2;
	PG301_REBOOT Reboot;
	PG301_SHUTDOWN Shutdown;
	PG301_IS_COMPATIBLE6 IsCompatible6;
	PG301_SET_SET_USE_DS_KEYS_AS_KEP SetUseDSKeysAsKEP;
	PG301_SIGN_HASH_KEP SignHashKEP;
#ifdef CSP_ECDH_UA
	PG301_WRAP_SHARED_KEY WrapSharedKey;
	PG301_UNWRAP_SHARED_KEY UnwrapSharedKey;
#endif // CSP_ECDH_UA
	PG301_IS_COMPATIBLE7 IsCompatible7;
	PG301_GET_CLUSTER_PARAMS GetClusterParams;
	PG301_GET_PARAMS2 GetParams2;
	PG301_IS_REVISION1 IsRevision1;
	PG301_GET_PUBLIC_KEY GetPublicKey;
	PG301_SET_DATA_LABEL SetDataLabel;
	PG301_SET_DATA_PASSWORD SetDataPassword;
	PG301_CHANGE_DATA_PASSWORD ChangeDataPassword;
	PG301_BACKUP_KEYS_WITH_PASSWORD BackupKeysWithPassword;
	PG301_RESTORE_KEYS_WITH_PASSWORD RestoreKeysWithPassword;
	PG301_ERASE_BACKUP_KEYS EraseBackupKeys;
	PG301_GENERATE_RSA_KEYS GenerateRSAKeys;
	PG301_RSA_SIGN_HASH RSASignHash;
	PG301_CHECK_RSA_PUBLIC_KEY CheckRSAPublicKey;
	PG301_GET_RSA_PUBLIC_KEY GetRSAPublicKey;
	PG301_RSA_DECRYPT_DATA RSADecryptData;
	PG301_GENERATE_ECDSA_KEYS GenerateECDSAKeys;
	PG301_ECDSA_SIGN_HASH ECDSASignHash;
	PG301_CHECK_ECDSA_PUBLIC_KEY CheckECDSAPublicKey;
	PG301_GET_ECDSA_PUBLIC_KEY GetECDSAPublicKey;
	PG301_ECDH_CALCULATE_SHARED_SECRET ECDHCalculateSharedSecret;
	PG301_STORE_MODULE_DATA StoreModuleData;
	PG301_LOAD_MODULE_DATA LoadModuleData;
	PG301_ERASE_MODULE_DATA EraseModuleData;
	PG301_GET_FIRST_CLIENTS GetFirstClients;
	PG301_GET_NEXT_CLIENTS GetNextClients;
	PG301_FREE_CLIENTS FreeClients;
	PG301_ADD_CLIENT AddClient;
	PG301_CHANGE_CLIENT ChangeClient;
	PG301_REMOVE_CLIENT RemoveClient;
	PG301_IS_COMPATIBLE8 IsCompatible8;
	PG301_ENUM_PUBLIC_KEYS EnumPublicKeys;
	PG301_GET_LABELED_PUBLIC_KEY GetLabeledPublicKey;
	PG301_GET_LABELED_RSA_PUBLIC_KEY GetLabeledRSAPublicKey;
	PG301_GET_LABELED_ECDSA_PUBLIC_KEY GetLabeledECDSAPublicKey;
	PG301_FIND_PUBLIC_KEY_BY_ID FindPublicKeyByID;
	PG301_GET_INFO GetInfo;
	PG301_ENUM_DATA EnumData;
	PG301_ERASE_LABELED_DATA EraseLabeledData;
	PG301_GET_CLIENT_INFO GetClientInfo;
	PG301_MAKE_COUPLE_SIGN_COMPONENT_S CoupleDSMakeComponentS;
	PG301_ENUM_BACKUP_EKEYS_LOCAL EnumBackupEKeysLocal;
	PG301_BACKUP_KEYS_REMOTE BackupKeysRemote;
	PG301_RESTORE_KEYS_REMOTE RestoreKeysRemote;
	PG301_ERASE_BACKUP_KEYS_LOCAL EraseBackupKeysLocal;
	PG301_ECDSA_COUPLE_PART2_STEP ECDSACouplePart2Step;
	PG301_MAKE_ECDSA_COUPLE_COMMON_PUB_KEY MakeECDSACoupleCommonPublicKey;
	PG301_GET_CLIENT_SECURITY GetClientSecurity;
	PG301_SET_CLIENT_SECURITY SetClientSecurity;
	PG301_SIGN_DSTU_HASH SignDSTUHash;
	PG301_VERIFY_DSTU_SIGN VerifyDSTUSign;
	PG301_SIGN_DSTU_HASH_KEP SignDSTUHashKEP;
	PG301_DSTU_WRAP_SHARED_KEY DSTUWrapSharedKey;
	PG301_DSTU_UNWRAP_SHARED_KEY DSTUUnwrapSharedKey;
	PG301_RSA_SIGN_HASH_EX RSASignHashEx;
	PG301_RENAME_DATA RenameData;
} G301_FUNCTIONS, *PG301_FUNCTIONS;

//------------------------------------------------------------------------------

#ifdef CSP_ECDH_UA
#define G301_EXT_FUNCTIONS_COUNT 72
#else // CSP_ECDH_UA
#define G301_EXT_FUNCTIONS_COUNT 70
#endif // CSP_ECDH_UA

//==============================================================================

#ifdef OS_MAC
#define G301_DLL_NAME "ncmg301.dylib"
#elif defined(ANDROID_NDK)
#define G301_DLL_NAME "libncmg301.so"
#elif defined (OS_NIX)
#define G301_DLL_NAME "ncmg301.so"
#else // OS_NIX
#define G301_DLL_NAME "NCMGryada301.dll"
#endif // OS_NIX

//==============================================================================

class Gryada301;

//==============================================================================

class CSPHardwareImplementationGryada301 : ICSPHardware
{
public:
	virtual BOOL WINAPI GenerateDSKeys(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	virtual BOOL WINAPI GenerateKEPKeys(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	virtual BOOL WINAPI SignHash(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		GOST34311_HASH pHash,
		DSTU4145_SIGNATURE pSignature);

	virtual BOOL WINAPI ProtectSharedData(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQb,
		ECDH_EXTENDED_DATA pData,
		PBYTE pbData,
		DWORD dwData,
		GOST28147_MAC pMAC);

	virtual BOOL WINAPI UnprotectSharedData(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQb,
		ECDH_EXTENDED_DATA pData,
		PBYTE pbData,
		DWORD dwData,
		GOST28147_MAC pMAC);

	virtual BOOL WINAPI CheckDSKeys(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	virtual BOOL WINAPI CheckKEPKeys(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	virtual BOOL WINAPI SetSBoxes(
		GOST28147_COMPRESSED_SBOX pEncryptionSBox,
		GOST28147_COMPRESSED_SBOX pHashSBox,
		GOST28147_COMPRESSED_SBOX pECDHSBox,
		GOST28147_COMPRESSED_SBOX pPRNGSBox);

	virtual BOOL WINAPI HashKEPKey(
		GOST34311_HASH pHash);

#ifdef CSP_ECDH_UA
	virtual BOOL WINAPI WrapSharedKey(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD dwSharedInfo,
		GOST28147_COMPRESSED_SBOX pHashSBox,
		GOST28147_COMPRESSED_SBOX pWrapSBox,
		GOST28147_KEY pKey,
		GOST28147_WRAPED_KEY pWrappedKey);

	virtual BOOL WINAPI UnwrapSharedKey(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD dwSharedInfo,
		GOST28147_COMPRESSED_SBOX pHashSBox,
		GOST28147_COMPRESSED_SBOX pWrapSBox,
		GOST28147_WRAPED_KEY pWrappedKey,
		GOST28147_KEY pKey);
#endif // CSP_ECDH_UA

	virtual BOOL WINAPI GetEncryptionSBox(
		GOST28147_EXTENDED_SBOX pSBox);

	virtual BOOL WINAPI InitializeEncryptData(
		GOST28147_COMPRESSED_SBOX pSBox,
		GOST28147_KEY pKey,
		GOST28147_IV pIV,
		BOOL blGenerateKeyAndIV);

	virtual BOOL WINAPI ContinueEncryptData(
		PBYTE pbData,
		DWORD dwData,
		GOST28147_KEY pKey);

	virtual BOOL WINAPI ContinueEncryptDataByOffset(
		PBYTE pbData,
		DWORD dwData,
		GOST28147_KEY pKey,
		DWORDLONG dwlDataOffset);

	virtual BOOL WINAPI FinalizeEncryptData(
		GOST28147_KEY pKey);

	virtual BOOL WINAPI InitializeDecryptData(
		GOST28147_COMPRESSED_SBOX pSBox,
		GOST28147_KEY pKey,
		GOST28147_IV pIV);

	virtual BOOL WINAPI ContinueDecryptData(
		PBYTE pbData,
		DWORD dwData,
		GOST28147_KEY pKey);

	virtual BOOL WINAPI ContinueDecryptDataByOffset(
		PBYTE pbData,
		DWORD dwData,
		GOST28147_KEY pKey,
		DWORDLONG dwlDataOffset);

	virtual BOOL WINAPI FinalizeDecryptData(
		GOST28147_KEY pKey);

	virtual BOOL WINAPI RecoverDSPublicKey(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	virtual BOOL WINAPI RecoverKEPPublicKey(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	virtual BOOL WINAPI CoupleDSMakeComponentS(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_NUMBER	pKeyK,
		DSTU4145_NUMBER	pCommonComponentR,
		DSTU4145_NUMBER	pComponentS);

	virtual BOOL WINAPI SignDSTUHash(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DWORD dwHash,
		DSTU7564_HASH pHash,
		DSTU4145_SIGNATURE pSignature);

	virtual BOOL WINAPI DSTU7624WrapSharedKey(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD dwSharedInfo,
		DSTU7624_SBOX pWrapSBox,
		PBYTE pKey,
		DWORD dwKey,
		PBYTE pWrappedKey,
		DWORD dwWrappedKey);

	virtual BOOL WINAPI DSTU7624UnwrapSharedKey(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD dwSharedInfo,
		DSTU7624_SBOX pWrapSBox,
		PBYTE pWrappedKey,
		DWORD dwWrappedKey,
		PBYTE pKey,
		DWORD dwKey);

public:
	CSPHardwareImplementationGryada301(Gryada301 *pGryada301);

private:
	Gryada301 *pGryada301;
};

//==============================================================================

class CSPHardwareRNGImplementationGryada301 : ICSPHardwareRNG
{
public:
	virtual BOOL WINAPI GenerateSequence(
		PBYTE pbSequence,
		DWORD dwSequence);

public:
	CSPHardwareRNGImplementationGryada301(Gryada301 *pGryada301);

private:
	Gryada301 *pGryada301;
};

//==============================================================================

class CSPIHardwareImplementationGryada301 : ICSPIHardware
{
public:
	virtual BOOL WINAPI SetSBoxes(
		GOST28147_COMPRESSED_SBOX pPRNGSBox);

	virtual BOOL WINAPI RSAGenerateKeys(
		PRSA_PARAMETERS pParameters,
		PRSA_PUBLIC_KEY pPublicKey);

	virtual BOOL WINAPI RSASignHash(
		SHA_HASH pHash,
		PRSA_PARAMETERS pParameters,
		RSA_SIGNATURE pSignature);

	virtual BOOL WINAPI RSACheckKeys(
		PRSA_PARAMETERS pParameters,
		PRSA_PUBLIC_KEY	pPublicKey);

	virtual BOOL WINAPI DSASignHash(
		DWORD dwHash,
		SHA_HASH pHash,
		PDSA_PARAMETERS pParameters,
		PDSA_SIGNATURE pSignature);

	virtual BOOL WINAPI DSAGenerateKeys(
		PDSA_PARAMETERS	pParameters,
		PDSA_PUBLIC_KEY pPublicKey);

	virtual BOOL WINAPI DSACheckKeys(
		PDSA_PARAMETERS	pParameters,
		PDSA_PUBLIC_KEY	pPublicKey);

	virtual BOOL WINAPI ECDSASignHash(
		DWORD dwHash,
		SHA_HASH pHash,
		PECDSA_PARAMETERS pParameters,
		PECDSA_SIGNATURE pSignature);

	virtual BOOL WINAPI ECDSAGenerateKeys(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pPublicKey);

	virtual BOOL WINAPI ECDSACheckKeys(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pPublicKey);

	virtual BOOL WINAPI ECDHCalculateSharedSecret(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pRecipientPublicKey,
		ECDSA_NUMBER pSharedSecret);

	virtual BOOL WINAPI DHCalculateSharedSecret(
		PDSA_PARAMETERS	pParameters,
		DSA_NUMBER pRecipientPublicKey,
		DSA_NUMBER pSharedSecret);

	virtual BOOL WINAPI RSARecoverPublicKey(
		PRSA_PARAMETERS pParameters,
		PRSA_PUBLIC_KEY pPublicKey);

	virtual BOOL WINAPI DSARecoverPublicKey(
		PDSA_PARAMETERS	pParameters,
		PDSA_PUBLIC_KEY	pPublicKey);

	virtual BOOL WINAPI ECDSARecoverPublicKey(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pPublicKey);

	virtual BOOL WINAPI RSADecryptData(
		PBYTE pbData,
		PDWORD pdwData,
		PRSA_PARAMETERS pParameters,
		BOOL blUnpadData);

	virtual BOOL WINAPI RSAPSSSignHash(
		SHA_HASH pHash,
		PRSA_PARAMETERS pParameters,
		RSA_SIGNATURE pSignature);

	virtual BOOL WINAPI ECDSACouplePart2Step(
		DWORD dwHash,
		SHA_HASH pHash,
		RSA_NUMBER pPaillierPublicKey,
		PECDSA_PARAMETERS pParameters,
		ECDSA_ENCODED_POINT pComponentR1,
		PAILLIER_NUMBER pEncryptedPrivateKey1,
		ECDSA_NUMBER pCommonComponentR,
		PAILLIER_NUMBER pComponentS2);

	virtual BOOL WINAPI ECDSACoupleMakeCommonPublicKey(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pPublicKeyB,
		ECDSA_KEY_Q pCommonPublicKey);

public:
	CSPIHardwareImplementationGryada301(Gryada301 *pGryada301);

private:
	Gryada301 *pGryada301;
};

//==============================================================================

class Gryada301
{
public:
	Gryada301();
	~Gryada301();

	static BOOL WINAPI Load();
	static BOOL WINAPI LoadEx(
		HMODULE hModule);
	static VOID WINAPI Unload();

	ICSPHardware* WINAPI GetCSPInterface();
	ICSPHardwareRNG* WINAPI GetHRNGInterface();
	ICSPIHardware* WINAPI GetCSPIInterface();

	static BOOL WINAPI LocateModules();

	static BOOL WINAPI EnumModules(
		DWORD iModule,
		PG301_MODULE_INFO pInfo);

	BOOL WINAPI ConnectModule(
		DWORD iModule);

	VOID WINAPI DisconnectModule();

	DWORD WINAPI Format(
		PSTR pszPassword);

	DWORD WINAPI LogOn(
		PSTR pszPassword);

	DWORD WINAPI LogOff();

	DWORD WINAPI ChangePassword(
		PSTR pszNewPassword);

	DWORD WINAPI GenerateRNSequence(
		PBYTE pbSequence,
		DWORD cbSequence);

	DWORD WINAPI SetSBoxes(
		GOST28147_COMPRESSED_SBOX pPRNGSBox,
		GOST28147_COMPRESSED_SBOX pDHSBox);

	DWORD WINAPI GenerateKeys(
		BOOL blDSKeys,
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	DWORD WINAPI HashPrivateKey(
		GOST34311_HASH pHash);

	DWORD WINAPI SignHash(
		GOST34311_HASH pHash,
		DSTU4145_SIGNATURE pSignature);

	DWORD WINAPI SignDSTUHash(
		DWORD dwHash,
		DSTU7564_HASH pHash,
		DSTU4145_SIGNATURE pSignature);

	DWORD WINAPI CoupleDSMakeComponentS(
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_NUMBER pKeyK,
		DSTU4145_NUMBER pCommonComponentR,
		DSTU4145_NUMBER pComponentS);

	DWORD WINAPI CheckPublicKey(
		BOOL blDSKey,
		DSTU4145_KEY_Q pKeyQ);

	DWORD WINAPI GetPublicKey(
		BOOL blDSKey,
		DSTU4145_KEY_Q pKeyQ);

	BOOL WINAPI EnumBackupKeyMedias(
		INT nIndex,
		PSTR pszName);

	DWORD WINAPI BackupKeys(
		DWORD dwKeyMedia);

	DWORD WINAPI RestoreKeys(
		DWORD dwKeyMedia);

	DWORD WINAPI BackupKeysWithPassword(
		DWORD dwKeyMedia,
		UINT uiKeysAlgos,
		UINT uiOperation,
		PSTR pszPassword);

	DWORD WINAPI RestoreKeysWithPassword(
		DWORD dwKeyMedia,
		UINT uiKeysAlgos,
		UINT uiOperation,
		PSTR pszPassword);

	DWORD WINAPI EraseKeys();

	DWORD WINAPI EraseBackupKeys(
		DWORD dwKeyMedia);

	DWORD WINAPI EnumBackupEKeysLocal(
		DWORD dwIndex,
		DWORD dwKeyMedia,
		PSTR pszEKey,
		PSTR pszError);

	DWORD WINAPI BackupKeysRemote(
		DWORD dwKeyMedia,
		UINT uiKeysAlgos,
		UINT uiOperation,
		PSTR pszPassword,
		PSTR pszEKey1,
		PSTR pszEKey2,
		PSTR pszRemovableDisk,
		PSTR pszError);

	DWORD WINAPI RestoreKeysRemote(
		DWORD dwKeyMedia,
		UINT uiKeysAlgos,
		UINT uiOperation,
		PSTR pszPassword,
		PSTR pszEKey1,
		PSTR pszEKey2,
		PSTR pszRemovableDisk,
		PHANDLE	phKeysDBFile,
		PSTR pszError);

	DWORD WINAPI EraseBackupKeysLocal(
		DWORD dwKeyMedia,
		PSTR pszEKey1,
		PSTR pszEKey2,
		PSTR pszRemovableDisk,
		PSTR pszError);

	DWORD WINAPI ProtectSharedData(
		DSTU4145_KEY_Q pKeyQ,
		ECDH_EXTENDED_DATA pData,
		PBYTE pbData,
		DWORD cbData,
		GOST28147_MAC pMAC);

	DWORD WINAPI UnprotectSharedData(
		DSTU4145_KEY_Q pKeyQ,
		ECDH_EXTENDED_DATA pData,
		PBYTE pbData,
		DWORD cbData,
		GOST28147_MAC pMAC);

	DWORD WINAPI StoreData(
		PBYTE pbData,
		DWORD cbData);

	DWORD WINAPI LoadData(
		PBYTE pbData,
		PDWORD pcbData);

	DWORD WINAPI EraseData();

	DWORD WINAPI SetParams(
		PG301_MODULE_PARAMS pParams);

	DWORD WINAPI IsCompatible2();

	DWORD WINAPI VerifySign(
		GOST34311_HASH pHash,
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ,
		DSTU4145_SIGNATURE pSignature);

	DWORD WINAPI VerifyDSTUSign(
		DWORD dwHash,
		DSTU7564_HASH pHash,
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ,
		DSTU4145_SIGNATURE pSignature);

	DWORD WINAPI IsCompatible3();

	DWORD WINAPI MakeSharedKey(
		DSTU4145_KEY_Q pKeyQ,
		ECDH_EXTENDED_DATA pData,
		GOST28147_KEY pKey);

	DWORD WINAPI IsCompatible4();

	DWORD WINAPI SetTime(
		PSYSTEMTIME pTime);

	DWORD WINAPI SetClusterParams(
		PG301_CLUSTER_PARAMS pClusterParams);

	DWORD WINAPI IsCompatible5();

	DWORD WINAPI SetParams2(
		PG301_MODULE_PARAMS2 pParams2);

	DWORD WINAPI Reboot();

	DWORD WINAPI Shutdown();

	DWORD WINAPI IsCompatible6();

	DWORD WINAPI SetUseDSKeysAsKEP(
		BOOL blUse);

	DWORD WINAPI SignHashKEP(
		GOST34311_HASH pHash,
		DSTU4145_SIGNATURE pSignature);

	DWORD WINAPI SignDSTUHashKEP(
		DWORD dwHash,
		DSTU7564_HASH pHash,
		DSTU4145_SIGNATURE pSignature);

#ifdef CSP_ECDH_UA
	DWORD WINAPI WrapSharedKey(
		UINT dwParameterECM,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD cbSharedInfo,
		GOST28147_KEY pKey,
		GOST28147_WRAPED_KEY pWrappedKey);

	DWORD WINAPI UnwrapSharedKey(
		UINT dwParameterECM,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD cbSharedInfo,
		GOST28147_WRAPED_KEY pWrappedKey,
		GOST28147_KEY pKey);
#endif // CSP_ECDH_UA

	DWORD WINAPI DSTUWrapSharedKey(
		UINT dwParameterECM,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD cbSharedInfo,
		PBYTE pKey,
		DWORD dwKey,
		PBYTE pWrappedKey,
		DWORD dwWrappedKey);

	DWORD WINAPI DSTUUnwrapSharedKey(
		UINT dwParameterECM,
		DSTU4145_KEY_Q pKeyQb,
		BOOL blCofactorMethod,
		PBYTE pbSharedInfo,
		DWORD cbSharedInfo,
		PBYTE pWrappedKey,
		DWORD dwWrappedKey,
		PBYTE pKey,
		DWORD dwKey);

	DWORD WINAPI IsCompatible7();

	DWORD WINAPI GetClusterParams(
		PG301_CLUSTER_PARAMS pClusterParams);

	DWORD WINAPI GetParams2(
		PG301_MODULE_PARAMS2 pParams2);

	DWORD WINAPI IsRevision1();

	DWORD WINAPI SetDataLabel(
		BOOL blAppend,
		PSTR pszLabel);

	DWORD WINAPI SetDataPassword(
		PSTR pszPassword);

	DWORD WINAPI ChangeDataPassword(
		PSTR pszNewPassword);

	BOOL WINAPI EnumKeysOwners(
		INT nIndex,
		PSTR pszLabel,
		PSTR pszDescr);

	BOOL WINAPI EnumKeysAlgos(
		INT nIndex,
		PSTR pszDescr);

	DWORD WINAPI GenerateRSAKeys(
		PRSA_PARAMETERS pParameters,
		PRSA_PUBLIC_KEY pPublicKey);

	DWORD WINAPI RSASignHash(
		SHA_HASH pHash,
		RSA_SIGNATURE pSignature);

	DWORD WINAPI RSASignHashEx(
		DWORD dwVersion,
		DWORD dwHash,
		SHA_HASH pHash,
		RSA_SIGNATURE pSignature);

	DWORD WINAPI CheckRSAPublicKey(
		PRSA_PUBLIC_KEY pPublicKey);

	DWORD WINAPI GetRSAPublicKey(
		PRSA_PUBLIC_KEY pPublicKey);

	DWORD WINAPI RSADecryptData(
		PBYTE pbData,
		PDWORD pdwData,
		PRSA_PARAMETERS pParameters,
		BOOL blUnpadData);

	DWORD WINAPI GenerateECDSAKeys(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pPublicKey);

	DWORD WINAPI ECDSASignHash(
		DWORD dwHash,
		SHA_HASH pHash,
		PECDSA_SIGNATURE pSignature);

	DWORD WINAPI ECDSACouplePart2Step(
		DWORD dwHash,
		SHA_HASH pHash,
		RSA_NUMBER pPaillierPublicKey,
		ECDSA_ENCODED_POINT pComponentR1,
		PAILLIER_NUMBER pEncryptedPrivateKey1,
		ECDSA_NUMBER pCommonComponentR,
		PAILLIER_NUMBER pComponentS2);

	DWORD WINAPI CheckECDSAPublicKey(
		ECDSA_KEY_Q pPublicKey);

	DWORD WINAPI GetECDSAPublicKey(
		ECDSA_KEY_Q pPublicKey);

	DWORD WINAPI MakeECDSACoupleCommonPublicKey(
		ECDSA_KEY_Q pPublicKeyB,
		ECDSA_KEY_Q pCommonPublicKey);

	DWORD WINAPI ECDHCalculateSharedSecret(
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pRecipientPublicKey,
		ECDSA_NUMBER pSharedSecret);

	DWORD WINAPI StoreModuleData(
		UINT uiReserved,
		PBYTE pbData,
		DWORD cbData);

	DWORD WINAPI LoadModuleData(
		UINT uiReserved,
		PBYTE pbData,
		PDWORD pcbData);

	DWORD WINAPI EraseModuleData(
		UINT uiReserved);

	DWORD WINAPI GetFirstClients(
		PDWORD pdwClients,
		PG301_CLIENT *ppClients);

	DWORD WINAPI GetNextClients(
		PDWORD pdwClients,
		PG301_CLIENT *ppClients);

	VOID WINAPI FreeClients(
		PG301_CLIENT *ppClients);

	DWORD WINAPI AddClient(
		PG301_CLIENT pClient);

	DWORD WINAPI ChangeClient(
		PSTR pszClientName,
		PG301_CLIENT pChangedClient);

	DWORD WINAPI RemoveClient(
		PSTR pszClientName);

	BOOL WINAPI EnumClientsTypes(
		INT nIndex,
		PSTR pszDescr,
		PSTR pszDescrTitle);

	DWORD WINAPI IsCompatible8();

	DWORD WINAPI EnumPublicKeys(
		BOOL blFirst,
		UINT uiType,
		BOOL blAppendedLabel,
		PSTR pszSubLabel,
		PUINT puiType,
		PSTR pszAppendedLabel,
		PSTR pszPartialLabel);

	DWORD WINAPI GetLabeledPublicKey(
		BOOL blDSKey,
		PSTR pszLabel,
		BOOL blAppendLabel,
		PDSTU4145_PARAMETER_EC pParameterEC,
		PDSTU4145_PARAMETER_P pParameterP,
		DSTU4145_KEY_Q pKeyQ);

	DWORD WINAPI GetLabeledRSAPublicKey(
		PSTR pszLabel,
		BOOL blAppendLabel,
		PRSA_PARAMETERS pParameters,
		PRSA_PUBLIC_KEY pPublicKey);

	DWORD WINAPI GetLabeledECDSAPublicKey(
		PSTR pszLabel,
		BOOL blAppendLabel,
		PECDSA_PARAMETERS pParameters,
		ECDSA_KEY_Q pPublicKey);

	DWORD WINAPI FindPublicKeyByID(
		UINT uiType,
		BOOL blAppendedLabel,
		PSTR pszSubLabel,
		PBYTE pbKeyID,
		UINT cbKeyID,
		PUINT puiType,
		PSTR pszAppendedLabel,
		PSTR pszPartialLabel);

	DWORD WINAPI GetInfo(
		PSTR pszName,
		PSTR pszSN,
		PSTR pszImageVersion,
		PDWORDLONG pdwlTotalConfigMemory,
		PDWORDLONG pdwlFreeConfigMemory);

	DWORD WINAPI EnumData(
		BOOL blFirst,
		UINT uiType,
		BOOL blAppendedLabel,
		PSTR pszSubLabel,
		PUINT puiType,
		PSTR pszAppendedLabel,
		PSTR pszPartialLabel);

	PSTR WINAPI GetDataTypeDescr(
		UINT uiType,
		PSTR pszDescr);

	DWORD WINAPI EraseLabeledData(
		UINT uiType,
		PSTR pszLabel,
		BOOL blAppendLabel);

	DWORD WINAPI RenameData(
		UINT uiType,
		PSTR pszLabel,
		BOOL blAppendLabel,
		PSTR pszNewLabel);

	DWORD WINAPI GetClientInfo(
		PG301_CLIENT_INFO pClientInfo);

	DWORD WINAPI GetClientSecurity(
		PG301_CLIENT_SECURITY pSecurity);

	DWORD WINAPI SetClientSecurity(
		PG301_CLIENT_SECURITY pSecurity);

	BOOL WINAPI StringToImageVersion(
		PSTR pszVersion,
		PUINT puiVersion);

	UINT WINAPI GetImageVersion();

private:
	static BOOL GetModulePath(
		HMODULE hModule,
		PSTR pszPath);

private:
	static HINSTANCE hDLL;

public:
	static G301_FUNCTIONS F;

private:
	G301MODULE hModule;

	ICSPHardware *pCSPInterface;
	ICSPHardwareRNG *pHRNGInterface;
	ICSPIHardware *pCSPIInterface;

	BOOL blCompat2Checked, blCompatible2;
	BOOL blCompat3Checked, blCompatible3;
	BOOL blCompat4Checked, blCompatible4;
	BOOL blCompat5Checked, blCompatible5;
	BOOL blCompat6Checked, blCompatible6;
	BOOL blCompat7Checked, blCompatible7;
	BOOL blCompat8Checked, blCompatible8;
	BOOL blRev1Checked, blRevision1;

	UINT uiImageVersion;
};

//==============================================================================

#endif // NCM_GRYADA301_H

