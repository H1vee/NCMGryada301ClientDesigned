#ifndef NC_HOST_CRYPTO_PROVIDER_H
#define NC_HOST_CRYPTO_PROVIDER_H

//=============================================================================

#ifndef NC_HOST_INTERNAL
#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else
#include <windows.h>
#include <stdio.h>
#define PACKED
#endif // OS_NIX
#define OS_API	WINAPI
#else // NC_HOST_INTERNAL
#include "OSRoutines.h"
#define PACKED
#endif // NC_HOST_INTERNAL

#if defined(OS_NIX) || !defined(_WIN64)
#define DWORDP	DWORD
#else // OS_NIX || !_WIN64
#define DWORDP	PVOID
#endif // OS_NIX || !_WIN64

typedef DWORDP	*PDWORDP;

//=============================================================================

#define NC_HOST_CP_MAX_ERROR_DESCR_LENGTH		1024

#define NC_HOST_CP_MAX_CERT_ISSUER_LENGTH		1024
#define NC_HOST_CP_MAX_CERT_SUBJECT_LENGTH		1024
#define NC_HOST_CP_MAX_CERT_CN_LENGTH			64
#define NC_HOST_CP_MAX_CERT_SERIAL_LENGTH		40

#define NC_HOST_CP_MAX_CERT_ID_LENGTH			\
	NC_HOST_CP_MAX_CERT_SUBJECT_LENGTH

//-----------------------------------------------------------------------------

#define NC_HOST_CP_SESSION_ID_LENGTH			32
#define NC_HOST_CP_REAUTH_CLIENT_SEND_LENGTH	\
	NC_HOST_CP_SESSION_ID_LENGTH

//-----------------------------------------------------------------------------

#define	NC_HOST_CP_ERROR_NONE					0
#define	NC_HOST_CP_ERROR_BAD_PARAMETER			0x0002
#define	NC_HOST_CP_WARNING_END_OF_ENUM			0x0007
#define	NC_HOST_CP_ERROR_CANCELED_BY_GUI		0x000C
#define	NC_HOST_CP_ERROR_OFFLINE_MODE			0x000D
#define	NC_HOST_CP_ERROR_PKI_FORMATS_FAILED		0x0021
#define	NC_HOST_CP_ERROR_CSP_FAILED				0x0022
#define NC_HOST_CP_ERROR_BAD_SIGNATURE			0x0023
#define	NC_HOST_CP_ERROR_NOT_SUPPORTED			0xFFFE
#define	NC_HOST_CP_ERROR_UNKNOWN				0xFFFF

//-----------------------------------------------------------------------------

#define NC_HOST_CP_MAX_PASSWORD_LENGTH			64
#define NC_HOST_CP_MAX_PROT_PASSWORD_OVERHEAD	24
#define NC_HOST_CP_MAX_PROT_PASSWORD_LENGTH		\
		(NC_HOST_CP_MAX_PASSWORD_LENGTH * 2 +	\
		NC_HOST_CP_MAX_PROT_PASSWORD_OVERHEAD)

#define NC_HOST_CP_MAX_KMS_COUNT				32
#define NC_HOST_CP_MAX_KM_DESCR_LENGTH			256

#ifdef OS_NIX
#define NC_HOST_CP_FIXED_KMS_COUNT				1
#else // OS_NIX
#define NC_HOST_CP_FIXED_KMS_COUNT				3
#endif // OS_NIX

//-----------------------------------------------------------------------------

#define NC_HOST_CP_KEY_SIZE						32
#define NC_HOST_CP_IV_SIZE						8
#define NC_HOST_CP_SBOX_SIZE					4096
#define NC_HOST_CP_MAC_SIZE						4
#define NC_HOST_CP_DATA_PROTECT_MAX_ADD_SIZE	12

#define NC_HOST_CP_KEY_ALGO2_SIZE				32
#define NC_HOST_CP_IV_ALGO2_SIZE				32
#define NC_HOST_CP_SBOX_ALGO2_SIZE				1024
#define NC_HOST_CP_MAC_ALGO2_SIZE				32
#define NC_HOST_CP_DATA_PROT_MAX_ADD_ALGO2_SIZE	64

#define NC_HOST_CP_KEY_ALGO3_SIZE				32
#define NC_HOST_CP_IV_ALGO3_SIZE				32
#define NC_HOST_CP_SBOX_ALGO3_SIZE				1024

//-----------------------------------------------------------------------------

#define NC_HOST_CP_SUBJ_TYPE_UNDIFFERENCED		0
#define NC_HOST_CP_SUBJ_TYPE_CA					1
#define NC_HOST_CP_SUBJ_TYPE_CA_SERVER			2
#define NC_HOST_CP_SUBJ_TYPE_RA_ADMINISTRATOR	3
#define NC_HOST_CP_SUBJ_TYPE_END_USER			4

#define NC_HOST_CP_SUBJ_CA_SERVER_SUB_TYPE		0
#define NC_HOST_CP_SUBJ_CA_SERVER_SUB_TYPE_CMP	1
#define NC_HOST_CP_SUBJ_CA_SERVER_SUB_TYPE_TSP	2
#define NC_HOST_CP_SUBJ_CA_SERVER_SUB_TYPE_OCSP	3

//-----------------------------------------------------------------------------

#define NC_HOST_CP_SETTING_TYPE_COMMON			0x1
#define NC_HOST_CP_SETTING_TYPE_KEY_MEDIAS		0x2

#define NC_HOST_CP_SETTING_TYPE_ALL				\
	(NC_HOST_CP_SETTING_TYPE_COMMON |			\
	NC_HOST_CP_SETTING_TYPE_KEY_MEDIAS)

//-----------------------------------------------------------------------------

#define NC_HOST_CP_OTP_DEF_TIME_STEP			30

#define NC_HOST_CP_OTP_KEY_LENGTH				20

#define NC_HOST_CP_OTP_MIN_DIGITS				1
#define NC_HOST_CP_OTP_MAX_DIGITS				8
#define NC_HOST_CP_OTP_DEF_DIGITS				6

//-----------------------------------------------------------------------------

#define NC_HOST_CP_HASH_ALGO_GOST34311			1
#define NC_HOST_CP_HASH_ALGO_DSTU7564			2

#define NC_HOST_CP_PROT_ALGO_GOST28147			1
#define NC_HOST_CP_PROT_ALGO_DSTU7624			2

#define NC_HOST_CP_ENCR_ALGO_GOST28147			1
#define NC_HOST_CP_ENCR_ALGO_DSTU7624			2
#define NC_HOST_CP_ENCR_ALGO_DSTU8845			3

#define NC_HOST_CP_CRYPTO_SUITE_GOSTS_DESCR		\
	"� ����� ���� 34.311-95 �� ������ ���� ���� 28147"
#define NC_HOST_CP_CRYPTO_SUITE_DSTUS_DESCR		\
	"� ����� ���� 7564 �� ������� ���� 7624 � 8845"

//-----------------------------------------------------------------------------

#define NC_HOST_CP_PARAMETERS_TYPE1				1
#define NC_HOST_CP_PARAMETERS_TYPE2				2

#define NC_HOST_CP_PARAMETERS_TYPE1_DESCR		\
	"��� 1 (����� � ������ ���� ���� 28147)"
#define NC_HOST_CP_PARAMETERS_TYPE2_DESCR		\
	"��� 2 (� ������� ���� 7624 �� 8845)"

//=============================================================================

#pragma pack(push, 1)
typedef struct
{
	UINT			dwTypeIndex;
	UINT			dwDevIndex;
	CHAR			szPassword[NC_HOST_CP_MAX_PASSWORD_LENGTH + 1];
} PACKED NC_HOST_CP_KEY_MEDIA, *PNC_HOST_CP_KEY_MEDIA;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_KEY_MEDIA(x)			\
	do {										\
		SWAP_PUINT(&(x)->dwTypeIndex);			\
		SWAP_PUINT(&(x)->dwDevIndex);			\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	BYTE			bSBox[NC_HOST_CP_SBOX_SIZE];
} PACKED NC_HOST_CP_ENCRYPTION_PARAMS, *PNC_HOST_CP_ENCRYPTION_PARAMS;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_ENCRYPTION_PARAMS(x)	\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	BYTE			bOwnKey[NC_HOST_CP_KEY_SIZE];
	BYTE			bOwnIV[NC_HOST_CP_IV_SIZE];
	BYTE			bOtherKey[NC_HOST_CP_KEY_SIZE];
	BYTE			bOtherIV[NC_HOST_CP_IV_SIZE];
} PACKED NC_HOST_CP_SESSION_KEYS, *PNC_HOST_CP_SESSION_KEYS;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_SESSION_KEYS(x)		\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	BYTE			bSBox[NC_HOST_CP_SBOX_ALGO2_SIZE];
} PACKED NC_HOST_CP_ENCR_PARAMS_ALGO2, *PNC_HOST_CP_ENCR_PARAMS_ALGO2;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_ENCR_PARAMS_ALGO2(x)	\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	BYTE			bOwnKey[NC_HOST_CP_KEY_ALGO2_SIZE];
	BYTE			bOwnIV[NC_HOST_CP_IV_ALGO2_SIZE];
	BYTE			bOtherKey[NC_HOST_CP_KEY_ALGO2_SIZE];
	BYTE			bOtherIV[NC_HOST_CP_IV_ALGO2_SIZE];
} PACKED NC_HOST_CP_SESSION_KEYS_ALGO2, *PNC_HOST_CP_SESSION_KEYS_ALGO2;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_SESSION_KEYS_ALGO2(x)	\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	BYTE			bSBox[NC_HOST_CP_SBOX_ALGO3_SIZE];
} PACKED NC_HOST_CP_ENCR_PARAMS_ALGO3, *PNC_HOST_CP_ENCR_PARAMS_ALGO3;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_ENCR_PARAMS_ALGO3(x)	\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	BYTE			bOwnKey[NC_HOST_CP_KEY_ALGO3_SIZE];
	BYTE			bOwnIV[NC_HOST_CP_IV_ALGO3_SIZE];
	BYTE			bOtherKey[NC_HOST_CP_KEY_ALGO3_SIZE];
	BYTE			bOtherIV[NC_HOST_CP_IV_ALGO3_SIZE];
} PACKED NC_HOST_CP_SESSION_KEYS_ALGO3, *PNC_HOST_CP_SESSION_KEYS_ALGO3;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_SESSION_KEYS_ALGO3(x)	\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	CHAR			szIssuer[NC_HOST_CP_MAX_CERT_ISSUER_LENGTH + 1];
	CHAR			szSerial[NC_HOST_CP_MAX_CERT_SERIAL_LENGTH + 1];
	CHAR			szIssuerCN[NC_HOST_CP_MAX_CERT_CN_LENGTH + 1];
	CHAR			szSubject[
		NC_HOST_CP_MAX_CERT_ISSUER_LENGTH + 1];
	CHAR			szSubjectCN[NC_HOST_CP_MAX_CERT_CN_LENGTH + 1];
	SYSTEMTIME		CertBeginTime;
	SYSTEMTIME		CertEndTime;
	SYSTEMTIME		PrivKeyBeginTime;
	SYSTEMTIME		PrivKeyEndTime;
} PACKED NC_HOST_CP_CERT_INFO, *PNC_HOST_CP_CERT_INFO;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_CERT_INFO(x)			\
	do {										\
		SWAP_SYSTEMTIME((x)->CertBeginTime);	\
		SWAP_SYSTEMTIME((x)->CertEndTime);		\
		SWAP_SYSTEMTIME((x)->PrivKeyBeginTime);	\
		SWAP_SYSTEMTIME((x)->PrivKeyEndTime);	\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	CHAR			szIssuer[
		NC_HOST_CP_MAX_CERT_ISSUER_LENGTH + 1];
	CHAR			szSerial[
		NC_HOST_CP_MAX_CERT_SERIAL_LENGTH + 1];
} PACKED NC_HOST_CP_CERT_INFO_ID, *PNC_HOST_CP_CERT_INFO_ID;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_CERT_INFO_ID(x)		\
	do {										\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	CHAR			szIssuer[
		NC_HOST_CP_MAX_CERT_ISSUER_LENGTH + 1];
	UINT			uiCRLNumber;
	CHAR			szIssuerCN[NC_HOST_CP_MAX_CERT_CN_LENGTH];
	SYSTEMTIME		ThisUpdate;
	SYSTEMTIME		NextUpdate;
} PACKED NC_HOST_CP_CRL_INFO, *PNC_HOST_CP_CRL_INFO;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_CRL_INFO(x)			\
	do {										\
		SWAP_PUINT(&(x)->uiCRLNumber);			\
		SWAP_SYSTEMTIME((x)->ThisUpdate);		\
		SWAP_SYSTEMTIME((x)->NextUpdate);		\
	} while(0)
#endif

//-----------------------------------------------------------------------------

typedef struct
{
	CHAR			szIssuer[
		NC_HOST_CP_MAX_CERT_ISSUER_LENGTH + 1];
	UINT			uiCRLNumber;
} PACKED NC_HOST_CP_CRL_INFO_ID, *PNC_HOST_CP_CRL_INFO_ID;

#ifdef HP_BIG_ENDIAN
#define SWAP_PNC_HOST_CP_CRL_INFO_ID(x)			\
	do {										\
		SWAP_PUINT(&(x)->uiCRLNumber);			\
	} while(0)
#endif
#pragma pack(pop)

//=============================================================================

typedef DWORD (OS_API *PNC_HOST_CP_INITIALIZE)(
	PSTR	pszSettPath,
	BOOL	bOnlyCrypto);

typedef DWORD (OS_API *PNC_HOST_CP_FINALIZE)();

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_SET_HOST_SETTINGS)(
	PBYTE	pbSettings,
	DWORD	dwSettingsSize,
	PSTR	pszSettPath);

typedef DWORD (OS_API *PNC_HOST_CP_GET_HOST_SETTINGS)(
	PBYTE	*ppbSettings,
	PDWORD	pdwSettingsSize,
	PSTR	pszSettPath);

typedef DWORD (OS_API *PNC_HOST_CP_SET_HOST_SETTINGS_EX)(
	DWORD	dwType,
	PBYTE	pbSettings,
	DWORD	dwSettingsSize,
	PSTR	pszSettPath);

typedef DWORD (OS_API *PNC_HOST_CP_GET_HOST_SETTINGS_EX)(
	DWORD	dwType,
	PBYTE	*ppbSettings,
	PDWORD	pdwSettingsSize,
	PSTR	pszSettPath);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_PRIVATE_KEY)(
	PSTR								pszParamsPath,
	PSTR								pszPassword,
	PBYTE								*ppbPrivKey,
	PDWORD								pdwKeySize,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize);

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_PRIVATE_KEY_EX)(
	PSTR								pszParamsPath,
	PSTR								pszPassword,
	PBYTE								*ppbPrivKey,
	PDWORD								pdwKeySize,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize,
	PBYTE								*ppbKEPRequest,
	PDWORD								pdwKEPRequestSize);

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_PRIVATE_KEY_MEDIA)(
	PSTR								pszParamsPath,
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize);

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_PRIVATE_KEY_MEDIA_EX)(
	PSTR								pszParamsPath,
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize,
	PBYTE								*ppbKEPRequest,
	PDWORD								pdwKEPRequestSize);

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_NEW_PRIVATE_KEY_MEDIA_EX)(
	PSTR								pszParamsPath,
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize,
	PBYTE								*ppbKEPRequest,
	PDWORD								pdwKEPRequestSize);

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_NEW_PRIVATE_KEY_MEDIA)(
	PSTR								pszParamsPath,
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize);

typedef DWORD (OS_API *PNC_HOST_CP_READ_PRIVATE_KEY)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PDWORDP								pdwPrivKey,
	BOOL								bWithoutCert);

typedef DWORD (OS_API *PNC_HOST_CP_WRITE_PRIVATE_KEY)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	DWORDP								dwPrivKey);

typedef DWORD (OS_API *PNC_HOST_CP_GET_PRIVATE_KEY_EXPIRATION)(
	DWORDP								dwPrivKey,
	PSYSTEMTIME							pEndTime,
	PDWORD								pdwLeftDays,
	PDWORD								pdwLeftSeconds);

typedef DWORD (OS_API *PNC_HOST_CP_GET_PRIVATE_KEY_CERT_ID)(
	DWORDP								dwPrivKey,
	PSTR								pszCertID);

typedef DWORD (OS_API *PNC_HOST_CP_GET_ENCRYPTION_PARAMS)(
	DWORDP								dwPrivKey,
	PNC_HOST_CP_ENCRYPTION_PARAMS		pEncryptionParams);

typedef DWORD (OS_API *PNC_HOST_CP_FREE_PRIVATE_KEY)(
	DWORDP								dwPrivKey);

typedef DWORD (OS_API *PNC_HOST_CP_WRITE_PRIVATE_KEY_MEDIA)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PBYTE								pbPKey,
	DWORD								dwPrivKeySize);

typedef DWORD (OS_API *PNC_HOST_CP_DESTROY_PRIVATE_KEY)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia);

typedef DWORD (OS_API *PNC_HOST_CP_GET_KEY_MEDIA_DESCR)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	PSTR								pszTypeDescr,
	PSTR								pszDeviceDescr);

typedef DWORD (OS_API *PNC_HOST_CP_GET_KEY_MEDIA)(
	PSTR								pszTypeDescr,
	PSTR								pszDeviceDescr,
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia);

typedef DWORD (OS_API *PNC_HOST_CP_GET_KEY_MEDIA_TYPE)(
	PSTR								pszTypeDescr,
	PDWORD								pdwTypeIndex);

typedef DWORD (OS_API *PNC_HOST_CP_IS_KEY_MEDIA_AVAIBLE)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia);

typedef DWORD (OS_API *PNC_HOST_CP_WRITE_KEY_MEDIA)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	DWORD								dwKeyIndex,
	PBYTE								pbKey,
	DWORD								dwKeySize);

typedef DWORD (OS_API *PNC_HOST_CP_READ_KEY_MEDIA)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	DWORD								dwKeyIndex,
	PBYTE								*ppbKey,
	PDWORD								pdwKeySize);

typedef DWORD (OS_API *PNC_HOST_CP_DESTROY_KEY_MEDIA)(
	PNC_HOST_CP_KEY_MEDIA				pKeyMedia,
	DWORD								dwKeyIndex);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_AUTH_STEP1_CLIENT)(
	DWORDP		dwPrivKey,
	PBYTE		*ppbSend,
	PDWORD		pdwSendSize,
	PDWORDP		pdwSession);

typedef DWORD (OS_API *PNC_HOST_CP_AUTH_STEP1_SERVER)(
	DWORDP		dwPrivKey,
	PBYTE		pbReceive,
	DWORD		dwReceiveSize,
	BOOL		blSignSend,
	PBYTE		*ppbSend,
	PDWORD		pdwSendSize,
	PDWORDP		pdwClientCertificate,
	PDWORDP		pdwSession);

typedef DWORD (OS_API *PNC_HOST_CP_AUTH_STEP2_CLIENT)(
	DWORDP		dwSession,
	PBYTE		pbReceive,
	DWORD		dwReceiveSize,
	PDWORDP		pdwServerCertificate);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_REAUTH_STEP1_CLIENT)(
	DWORDP		dwPrivKey,
	DWORDP		dwExistSession,
	PBYTE		*ppbSendPtr,
	PDWORD		pdwSendSize,
	PDWORDP		pdwSession);

typedef DWORD (WINAPI *PNC_HOST_CP_REAUTH_STEP1_SERVER)(
	DWORDP		dwPrivKey,
	DWORDP		dwExistSession,
	PBYTE		pbReceive,
	DWORD		dwReceiveSize,
	PBYTE		*ppbSend,
	PDWORD		pdwSendSize,
	PDWORDP		pdwSession);

typedef DWORD (WINAPI *PNC_HOST_CP_REAUTH_STEP2_CLIENT)(
	DWORDP		dwExistSession,
	DWORDP		dwSession,
	PBYTE		pbReceive,
	DWORD		dwReceiveSize);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_PRE_SHARED_AUTH_STEP1_CLIENT)(
	PSTR		pszPassword,
	PBYTE		*ppbSend,
	PDWORD		pdwSendSize,
	PDWORDP		pdwSession);

typedef DWORD (OS_API *PNC_HOST_CP_PRE_SHARED_AUTH_STEP1_SERVER)(
	PSTR		pszPassword,
	PBYTE		pbReceive,
	DWORD		dwReceiveSize,
	PBYTE		*ppbSend,
	PDWORD		pdwSendSize,
	PDWORDP		pdwSession);

typedef DWORD (OS_API *PNC_HOST_CP_PRE_SHARED_AUTH_STEP2_CLIENT)(
	DWORDP		dwSession,
	PBYTE		pbReceive,
	DWORD		dwReceiveSize);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GET_SESSION_KEYS)(
	DWORDP		dwSession,
	PNC_HOST_CP_SESSION_KEYS
				pSessionKeys);

typedef DWORD (WINAPI *PNC_HOST_CP_DUPLICATE_SESSION)(
	DWORDP		dwExistSession,
	PDWORDP		pdwSession);

typedef DWORD (WINAPI *PNC_HOST_CP_GET_SESSION_ID)(
	DWORDP		dwSession,
	PBYTE		pbSessionID);

typedef DWORD (OS_API *PNC_HOST_CP_CLOSE_SESSION)(
	DWORDP		dwSession);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_ENCRYPT_DATA)(
	DWORDP	dwSession,
	PBYTE	pbData,
	DWORD	dwDataSize);

typedef DWORD (OS_API *PNC_HOST_CP_RESET_ENC_STATE)(
	DWORDP	dwSession);

typedef DWORD (OS_API *PNC_HOST_CP_DECRYPT_DATA)(
	DWORDP	dwSession,
	PBYTE	pbEncrypted,
	DWORD	dwEncryptedSize,
	BOOL	blResetOffset);

typedef DWORD (OS_API *PNC_HOST_CP_GET_DATA_MAC)(
	DWORDP	dwSession,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	pbMAC);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_HASH_DATA)(
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbHash,
	PDWORD	pdwHashSize);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_GENERATE_RN_SEQUENCE)(
	PBYTE	pbSequence,
	DWORD	dwSequenceSize);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_PASSWORD)(
	PSTR	pszPassword,
	DWORD	dwPasswordLength);

typedef DWORD (OS_API *PNC_HOST_CP_PROTECT_PASSWORD)(
	PSTR	pszPassword,
	PSTR	pszProtectedPassword,
	PSTR	pszProtectionPassword);

typedef DWORD (OS_API *PNC_HOST_CP_UNPROTECT_PASSWORD)(
	PSTR	pszProtectedPassword,
	PSTR	pszPassword,
	PSTR	pszProtectionPassword);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_PROTECT_DATA)(
	PSTR	pszPassword,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbProtectedData,
	PDWORD	pdwProtectedDataSize);

typedef DWORD (OS_API *PNC_HOST_CP_UNPROTECT_DATA)(
	PSTR	pszPassword,
	PBYTE	pbProtectedData,
	DWORD	dwProtectedDataSize,
	PBYTE	*ppbData,
	PDWORD	pdwDataSize);

typedef DWORD (OS_API *PNC_HOST_CP_PROTECT_DATA_BY_KEYS)(
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	pbKey1,
	PBYTE	pbKey2,
	PBYTE	*ppbProtectedData,
	PDWORD	pdwProtectedDataSize);

typedef DWORD (OS_API *PNC_HOST_CP_UNPROTECT_DATA_BY_KEYS)(
	PBYTE	pbKey1,
	PBYTE	pbKey2,
	PBYTE	pbProtectedData,
	DWORD	dwProtectedDataSize,
	PBYTE	*ppbData,
	PDWORD	pdwDataSize);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_SIGN_DATA)(
	DWORDP		dwPrivKey,
	PBYTE		pbData,
	DWORD		dwDataSize,
	PBYTE		*ppbSign,
	PDWORD		pdwSignSize);

typedef DWORD (OS_API *PNC_HOST_CP_VERIFY_SIGN)(
	PBYTE		pbSign,
	DWORD		dwSignSize,
	PBYTE		*ppbData,
	PDWORD		pdwDataSize,
	PDWORDP		pdwSignerCert);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_BEGIN_HASH_DATA)(
	DWORDP		dwPrivKey,
	PDWORDP		pdwHash);

typedef DWORD (OS_API *PNC_HOST_CP_CONTINUE_HASH_DATA)(
	DWORDP		dwHash,
	PBYTE		pbData,
	DWORD		dwDataSize);

typedef DWORD (OS_API *PNC_HOST_CP_END_HASH_DATA)(
	DWORDP		dwHash,
	PBYTE		*ppbHash,
	PDWORD		pdwHashSize);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_SIGN_HASH)(
	DWORDP		dwPrivKey,
	PBYTE		pbHash,
	DWORD		dwHashSize,
	PBYTE		*ppbSign,
	PDWORD		pdwSignSize);

typedef DWORD (OS_API *PNC_HOST_CP_VERIFY_HASH_SIGN)(
	PBYTE		pbHash,
	DWORD		dwHashSize,
	PBYTE		pbSign,
	DWORD		dwSignSize,
	PDWORDP		pdwSignerCert);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GET_CERT_ID)(
	DWORDP	dwCertificate,
	PSTR	pszCertID);

typedef DWORD (OS_API *PNC_HOST_CP_CHECK_CERT_BY_ID)(
	PSTR	pszCertID);

typedef DWORD (OS_API *PNC_HOST_CP_FREE_CERTIFICATE)(
	DWORDP	dwCertificate);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GET_CERTS_COUNT)(
	DWORD	dwSubjectType,
	DWORD	dwSubjectSubType,
	PDWORD	pdwCount);

typedef DWORD (OS_API *PNC_HOST_CP_ENUM_CERTIFICATES)(
	DWORD	dwSubjectType,
	DWORD	dwSubjectSubType,
	DWORD	dwIndex,
	PNC_HOST_CP_CERT_INFO
			pInfo);

typedef DWORD (OS_API *PNC_HOST_CP_GET_CRLS_COUNT)(
	PDWORD	pdwCount);

typedef DWORD (OS_API *PNC_HOST_CP_ENUM_CRLS)(
	DWORD	dwIndex,
	PNC_HOST_CP_CRL_INFO
			pInfo);

typedef DWORD (OS_API *PNC_HOST_CP_GET_CERTIFICATE)(
	PNC_HOST_CP_CERT_INFO_ID
			pInfoID,
	PBYTE	*ppbCert,
	PDWORD	pdwCertSize);

typedef DWORD (OS_API *PNC_HOST_CP_GET_CRL)(
	PNC_HOST_CP_CRL_INFO_ID
			pInfoID,
	PBYTE	*ppbCRL,
	PDWORD	pdwCRLSize);

typedef DWORD (OS_API *PNC_HOST_CP_CHECK_CERTIFICATE)(
	PNC_HOST_CP_CERT_INFO_ID
			pInfoID);

typedef DWORD (OS_API *PNC_HOST_CP_LOAD_CERTIFICATES)(
	PSTR	pszCertsPath);

typedef DWORD (OS_API *PNC_HOST_CP_LOAD_CERTIFICATE)(
	PBYTE	pbCert,
	DWORD	dwCertSize);

typedef DWORD (OS_API *PNC_HOST_CP_LOAD_CRL)(
	PBYTE	pbCRL,
	DWORD	dwCRLSize,
	BOOL	bFull);

typedef DWORD (OS_API *PNC_HOST_CP_DELETE_CERTIFICATE)(
	PNC_HOST_CP_CERT_INFO_ID
			pInfoID);

typedef DWORD (OS_API *PNC_HOST_CP_DELETE_CRL)(
	PNC_HOST_CP_CRL_INFO_ID
			pInfoID);

//-----------------------------------------------------------------------------

typedef VOID (OS_API *PNC_HOST_CP_GET_ERROR_DESCR)(
	DWORD	dwError,
	PSTR	pszErrorDescr);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_FREE_MEMORY)(
	PBYTE	pbMemory);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_SET_SETTINGS)();

//-----------------------------------------------------------------------------

typedef VOID (WINAPI *PNC_HOST_CP_SHOW_CERTS)();

typedef VOID (WINAPI *PNC_HOST_CP_SHOW_CRLS)();

//-----------------------------------------------------------------------------

typedef VOID (WINAPI *PNC_HOST_CP_SHOW_CERT_BY_PRIV_KEY)(
	DWORDP	dwPrivKey);

typedef DWORD (WINAPI *PNC_HOST_CP_CHANGE_PRIV_KEY_PASSWORD)();

typedef DWORD (WINAPI *PNC_HOST_CP_DESTROY_PRIV_KEY_BY_DIALOG)();

typedef DWORD (WINAPI *PNC_HOST_CP_BACKUP_PRIV_KEY)();

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_LOAD_PARAMETERS)(
	PSTR			pszParamsPath,
	PBYTE			*ppbParameters,
	PDWORD			pdwParametersSize);

typedef DWORD (WINAPI *PNC_HOST_CP_SAVE_PARAMETERS)(
	PBYTE			pbParameters,
	DWORD			dwParametersSize,
	PSTR			pszParamsPath);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_INITIALIZE_KEY_MEDIA_RNG)(
	PNC_HOST_CP_KEY_MEDIA				
					pKeyMedia);

typedef BOOL (WINAPI *PNC_HOST_CP_IS_KEY_MEDIA_RNG_INITIALIZED)();

typedef DWORD (WINAPI *PNC_HOST_CP_GENERATE_KEY_MEDIA_RN_SEQUENCE)(
	PBYTE			pbSequence,
	DWORD			dwSequenceSize);

typedef VOID (WINAPI *PNC_HOST_CP_FINALIZE_KEY_MEDIA_RNG)();

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_ENCODE_BASE32)(
	PBYTE			pbData,
	DWORD			dwDataLength,
	PSTR			pszString);

typedef DWORD (WINAPI *PNC_HOST_CP_DECODE_BASE32)(
	PSTR			pszString,
	PBYTE			pbData,
	DWORD			dwDataLength);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_GET_OTP_TIME_LEFT)(
	DWORD			dwTimeStep,
	PSYSTEMTIME		pstBeginTime,
	PSYSTEMTIME		pstTime,
	PDWORD			pdwTimeLeft);

typedef DWORD (WINAPI *PNC_HOST_CP_GENERATE_OTP)(
	DWORD			dwTimeStep,
	PSYSTEMTIME		pstBeginTime,
	PSYSTEMTIME		pstTime,
	PBYTE			pbKey,
	DWORD			dwKeyLength,
	DWORD			dwDigits,
	PSTR			pszOTP);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_HOST_CP_GET_ENCR_PARAMS_ALGO2)(
	DWORDP	dwPrivKey,
	PNC_HOST_CP_ENCR_PARAMS_ALGO2
			pEncryptionParams);

typedef DWORD (WINAPI *PNC_HOST_CP_GET_ENCR_PARAMS_ALGO3)(
	DWORDP	dwPrivKey,
	PNC_HOST_CP_ENCR_PARAMS_ALGO3
			pEncryptionParams);

typedef DWORD (WINAPI *PNC_HOST_CP_GET_SESSION_KEYS_ALGO2)(
	DWORDP	dwSession,
	PNC_HOST_CP_SESSION_KEYS_ALGO2
			pSessionKeys);

typedef DWORD (WINAPI *PNC_HOST_CP_GET_SESSION_KEYS_ALGO3)(
	DWORDP	dwSession,
	PNC_HOST_CP_SESSION_KEYS_ALGO3
			pSessionKeys);

typedef DWORD (WINAPI *PNC_HOST_CP_GET_DATA_MAC_SIZE)(
	DWORDP	dwSession);

typedef DWORD (WINAPI *PNC_HOST_CP_HASH_DATA_EX)(
	DWORD	dwHashType,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbHash,
	PDWORD	pdwHashSize);

typedef DWORD (WINAPI *PNC_HOST_CP_SIGN_DATA_EX)(
	DWORDP	dwPrivKey,
	DWORD	dwHashType,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbSign,
	PDWORD	pdwSignSize);

typedef DWORD (WINAPI *PNC_HOST_CP_SIGN_HASH_EX)(
	DWORDP	dwPrivKey,
	DWORD	dwHashType,
	PBYTE	pbHash,
	DWORD	dwHashSize,
	PBYTE	*ppbSign,
	PDWORD	pdwSignSize);

typedef DWORD (WINAPI *PNC_HOST_CP_VERIFY_HASH_SIGN_EX)(
	DWORD	dwHashType,
	PBYTE	pbHash,
	DWORD	dwHashSize,
	PBYTE	pbSign,
	DWORD	dwSignSize,
	PDWORDP	pdwSignerCert);

typedef DWORD (WINAPI *PNC_HOST_CP_LOAD_PARAMETERS_EX)(
	PSTR	pszParamsPath,
	UINT	uiParamsType,
	PBYTE	*ppbParameters,
	PDWORD	pdwParametersSize);

typedef DWORD (WINAPI *PNC_HOST_CP_SAVE_PARAMETERS_EX)(
	PBYTE	pbParameters,
	DWORD	dwParametersSize,
	PSTR	pszParamsPath,
	PUINT	puiParamsType);

typedef DWORD (WINAPI *PNC_HOST_CP_SET_CRYPTO_SUITE)(
	DWORD	dwHashAlgo,
	DWORD	dwProtAlgo,
	DWORD	dwEncrAlgo);

typedef DWORD (OS_API *PNC_HOST_CP_PRE_SHARED_AUTH_STEP1_CLIENT_EX)(
	DWORD	dwProtAlgo,
	PSTR	pszPassword,
	PBYTE	*ppbSend,
	PDWORD	pdwSendSize,
	PDWORDP	pdwSession);

//=============================================================================

#define NC_HOST_CP_RAW_COUPLE_SIGN_257_PARAMS_TYPE	6

#define NC_HOST_CP_RAW_COUPLE_SIGN_257_KEYS_SIZE	33
#define NC_HOST_CP_RAW_COUPLE_SIGN_257_SIZE			64

#define NC_HOST_CP_RAW_COUPLE_SIGN_257_HASH_SIZE	32

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GENERATE_RAW_COUPLE_SIGN_KEYS)(
	DWORD	dwParametersType,
	PBYTE	pbPrivateKey1,
	PBYTE	pbPrivateKey2,
	PBYTE	pbCommonPublicKey,
	DWORD	dwKeysSize);

typedef DWORD (OS_API *PNC_HOST_CP_RAW_COUPLE_SIGN)(
	DWORD	dwParametersType,
	PBYTE	pbPrivateKey1,
	PBYTE	pbPrivateKey2,
	PBYTE	pbCommonPublicKey,
	DWORD	dwKeysSize,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	pbSign,
	DWORD	dwSignSize);

typedef DWORD (OS_API *PNC_HOST_CP_VERIFY_RAW_COUPLE_SIGN)(
	DWORD	dwParametersType,
	PBYTE	pbCommonPublicKey,
	DWORD	dwCommonPublicKeySize,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	pbSign,
	DWORD	dwSignSize);

typedef DWORD (OS_API *PNC_HOST_CP_HASH_RAW_COUPLE_SIGN_DATA)(
	DWORD	dwParametersType,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	pbHash,
	DWORD	dwHashSize);

typedef DWORD (OS_API *PNC_HOST_CP_RAW_COUPLE_SIGN_HASH)(
	DWORD	dwParametersType,
	PBYTE	pbPrivateKey1,
	PBYTE	pbPrivateKey2,
	PBYTE	pbCommonPublicKey,
	DWORD	dwKeysSize,
	PBYTE	pbHash,
	DWORD	dwHashSize,
	PBYTE	pbSign,
	DWORD	dwSignSize);

typedef DWORD (OS_API *PNC_HOST_CP_VERIFY_RAW_COUPLE_SIGN_HASH)(
	DWORD	dwParametersType,
	PBYTE	pbCommonPublicKey,
	DWORD	dwCommonPublicKeySize,
	PBYTE	pbHash,
	DWORD	dwHashSize,
	PBYTE	pbSign,
	DWORD	dwSignSize);

typedef DWORD (OS_API *PNC_HOST_CP_CHECK_RAW_COUPLE_SIGN_PUBLIC_KEY)(
	DWORD	dwParametersType,
	PBYTE	pbCommonPublicKey,
	DWORD	dwCommonPublicKeySize);

//=============================================================================

typedef struct
{
	PNC_HOST_CP_INITIALIZE				Initialize;
	PNC_HOST_CP_FINALIZE				Finalize;

	PNC_HOST_CP_SET_HOST_SETTINGS		SetHostSettings;
	PNC_HOST_CP_GET_HOST_SETTINGS		GetHostSettings;

	PNC_HOST_CP_GENERATE_PRIVATE_KEY	GeneratePrivateKey;
	PNC_HOST_CP_GENERATE_PRIVATE_KEY_MEDIA
										GeneratePrivateKeyMedia;
	PNC_HOST_CP_READ_PRIVATE_KEY		ReadPrivateKey;
	PNC_HOST_CP_WRITE_PRIVATE_KEY		WritePrivateKey;
	PNC_HOST_CP_GET_PRIVATE_KEY_EXPIRATION
										GetPrivateKeyExpiration;
	PNC_HOST_CP_GET_PRIVATE_KEY_CERT_ID
										GetPrivateKeyCertID;
	PNC_HOST_CP_GET_ENCRYPTION_PARAMS
										GetEncryptionParams;
	PNC_HOST_CP_FREE_PRIVATE_KEY		FreePrivateKey;
	PNC_HOST_CP_WRITE_PRIVATE_KEY_MEDIA
										WritePrivateKeyMedia;
	PNC_HOST_CP_DESTROY_PRIVATE_KEY		DestroyPrivateKey;
	PNC_HOST_CP_GET_KEY_MEDIA_DESCR		GetKeyMediaDescr;
	PNC_HOST_CP_GET_KEY_MEDIA			GetKeyMedia;
	PNC_HOST_CP_GET_KEY_MEDIA_TYPE		GetKeyMediaType;
	PNC_HOST_CP_IS_KEY_MEDIA_AVAIBLE	IsKeyMediaAvaible;
	PNC_HOST_CP_WRITE_KEY_MEDIA			WriteKeyMedia;
	PNC_HOST_CP_READ_KEY_MEDIA			ReadKeyMedia;
	PNC_HOST_CP_DESTROY_KEY_MEDIA		DestroyKeyMedia;

	PNC_HOST_CP_AUTH_STEP1_CLIENT		AuthStep1Client;
	PNC_HOST_CP_AUTH_STEP1_SERVER		AuthStep1Server;
	PNC_HOST_CP_AUTH_STEP2_CLIENT		AuthStep2Client;

	PNC_HOST_CP_REAUTH_STEP1_CLIENT		ReauthStep1Client;
	PNC_HOST_CP_REAUTH_STEP1_SERVER		ReauthStep1Server;
	PNC_HOST_CP_REAUTH_STEP2_CLIENT		ReauthStep2Client;

	PNC_HOST_CP_PRE_SHARED_AUTH_STEP1_CLIENT
										PreSharedAuthStep1Client;
	PNC_HOST_CP_PRE_SHARED_AUTH_STEP1_SERVER
										PreSharedAuthStep1Server;
	PNC_HOST_CP_PRE_SHARED_AUTH_STEP2_CLIENT
										PreSharedAuthStep2Client;

	PNC_HOST_CP_GET_SESSION_KEYS		GetSessionKeys;
	PNC_HOST_CP_DUPLICATE_SESSION		DuplicateSession;
	PNC_HOST_CP_GET_SESSION_ID			GetSessionID;
	PNC_HOST_CP_CLOSE_SESSION			CloseSession;

	PNC_HOST_CP_SIGN_DATA				SignData;
	PNC_HOST_CP_VERIFY_SIGN				VerifySign;

	PNC_HOST_CP_GET_CERT_ID				GetCertID;
	PNC_HOST_CP_CHECK_CERT_BY_ID		CheckCertByID;
	PNC_HOST_CP_FREE_CERTIFICATE		FreeCertificate;

	PNC_HOST_CP_ENCRYPT_DATA			EncryptData;
	PNC_HOST_CP_RESET_ENC_STATE			ResetEncState;
	PNC_HOST_CP_DECRYPT_DATA			DecryptData;
	PNC_HOST_CP_GET_DATA_MAC			GetDataMAC;

	PNC_HOST_CP_HASH_DATA				HashData;

	PNC_HOST_CP_GENERATE_PASSWORD		GeneratePassword;
	PNC_HOST_CP_PROTECT_PASSWORD		ProtectPassword;
	PNC_HOST_CP_UNPROTECT_PASSWORD		UnprotectPassword;

	PNC_HOST_CP_PROTECT_DATA			ProtectData;
	PNC_HOST_CP_UNPROTECT_DATA			UnprotectData;
	PNC_HOST_CP_PROTECT_DATA_BY_KEYS	ProtectDataByKeys;
	PNC_HOST_CP_UNPROTECT_DATA_BY_KEYS	UnprotectDataByKeys;

	PNC_HOST_CP_GET_CERTS_COUNT			GetCertsCount;
	PNC_HOST_CP_ENUM_CERTIFICATES		EnumCertificates;
	PNC_HOST_CP_GET_CRLS_COUNT			GetCRLsCount;
	PNC_HOST_CP_ENUM_CRLS				EnumCRLs;
	PNC_HOST_CP_GET_CERTIFICATE			GetCertificate;
	PNC_HOST_CP_GET_CRL					GetCRL;
	PNC_HOST_CP_CHECK_CERTIFICATE		CheckCertificate;
	PNC_HOST_CP_LOAD_CERTIFICATES		LoadCertificates;
	PNC_HOST_CP_LOAD_CERTIFICATE		LoadCertificate;
	PNC_HOST_CP_LOAD_CRL				LoadCRL;
	PNC_HOST_CP_DELETE_CERTIFICATE		DeleteCertificate;
	PNC_HOST_CP_DELETE_CRL				DeleteCRL;

	PNC_HOST_CP_GET_ERROR_DESCR			GetErrorDescr;

	PNC_HOST_CP_FREE_MEMORY				FreeMemory;

	PNC_HOST_CP_SET_SETTINGS			SetSettings;

	PNC_HOST_CP_SHOW_CERTS				ShowCertificates;
	PNC_HOST_CP_SHOW_CRLS				ShowCRLs;

	PNC_HOST_CP_SHOW_CERT_BY_PRIV_KEY	ShowCertByPrivKey;
	PNC_HOST_CP_CHANGE_PRIV_KEY_PASSWORD
										ChangePrivateKeyPassword;
	PNC_HOST_CP_DESTROY_PRIV_KEY_BY_DIALOG
										DestroyPrivateKeyByDialog;
	PNC_HOST_CP_BACKUP_PRIV_KEY			BackupPrivateKey;

	PNC_HOST_CP_SET_HOST_SETTINGS_EX	SetHostSettingsEx;
	PNC_HOST_CP_GET_HOST_SETTINGS_EX	GetHostSettingsEx;

	PNC_HOST_CP_INITIALIZE_KEY_MEDIA_RNG	
										InitializeKeyMediaRNG;
	PNC_HOST_CP_IS_KEY_MEDIA_RNG_INITIALIZED
										IsKeyMediaRNGInitialized;
	PNC_HOST_CP_GENERATE_KEY_MEDIA_RN_SEQUENCE
										GenerateKeyMediaRNSequence;
	PNC_HOST_CP_FINALIZE_KEY_MEDIA_RNG	
										FinalizeKeyMediaRNG;
} NC_HOST_CP_INTERFACE, *PNC_HOST_CP_INTERFACE;

//-----------------------------------------------------------------------------

typedef struct
{
	PNC_HOST_CP_GENERATE_PRIVATE_KEY_EX	GeneratePrivateKeyEx;
	PNC_HOST_CP_GENERATE_PRIVATE_KEY_MEDIA_EX
										GeneratePrivateKeyMediaEx;
	PNC_HOST_CP_GENERATE_NEW_PRIVATE_KEY_MEDIA_EX
										GenerateNewPrivateKeyMediaEx;
	PNC_HOST_CP_GENERATE_NEW_PRIVATE_KEY_MEDIA
										GenerateNewPrivateKeyMedia;

	PNC_HOST_CP_LOAD_PARAMETERS			LoadParameters;
	PNC_HOST_CP_SAVE_PARAMETERS			SaveParameters;

	PNC_HOST_CP_BEGIN_HASH_DATA			BeginHashData;
	PNC_HOST_CP_CONTINUE_HASH_DATA		ContinueHashData;
	PNC_HOST_CP_END_HASH_DATA			EndHashData;

	PNC_HOST_CP_SIGN_HASH				SignHash;
	PNC_HOST_CP_VERIFY_HASH_SIGN		VerifyHashSign;

	PNC_HOST_CP_GENERATE_RN_SEQUENCE	GenerateRNSequence;

	PNC_HOST_CP_ENCODE_BASE32			EncodeBase32;
	PNC_HOST_CP_DECODE_BASE32			DecodeBase32;

	PNC_HOST_CP_GET_OTP_TIME_LEFT		GetOTPTimeLeft;
	PNC_HOST_CP_GENERATE_OTP			GenerateOTP;

	PNC_HOST_CP_GET_ENCR_PARAMS_ALGO2	GetEncrParamsAlgo2;
	PNC_HOST_CP_GET_ENCR_PARAMS_ALGO3	GetEncrParamsAlgo3;
	PNC_HOST_CP_GET_SESSION_KEYS_ALGO2	GetSessionKeysAlgo2;
	PNC_HOST_CP_GET_SESSION_KEYS_ALGO3	GetSessionKeysAlgo3;
	PNC_HOST_CP_GET_DATA_MAC_SIZE		GetDataMACSize;
	PNC_HOST_CP_HASH_DATA_EX			HashDataEx;
	PNC_HOST_CP_SIGN_DATA_EX			SignDataEx;
	PNC_HOST_CP_SIGN_HASH_EX			SignHashEx;
	PNC_HOST_CP_VERIFY_HASH_SIGN_EX		VerifyHashSignEx;
	PNC_HOST_CP_LOAD_PARAMETERS_EX		LoadParametersEx;
	PNC_HOST_CP_SAVE_PARAMETERS_EX		SaveParametersEx;
	PNC_HOST_CP_SET_CRYPTO_SUITE		SetCryptoSuite;
	PNC_HOST_CP_PRE_SHARED_AUTH_STEP1_CLIENT_EX
										PreSharedAuthStep1ClientEx;
	PNC_HOST_CP_GENERATE_RAW_COUPLE_SIGN_KEYS
										GenerateRawCoupleSignKeys;
	PNC_HOST_CP_RAW_COUPLE_SIGN			RawCoupleSign;
	PNC_HOST_CP_VERIFY_RAW_COUPLE_SIGN	VerifyRawCoupleSign;
	PNC_HOST_CP_HASH_RAW_COUPLE_SIGN_DATA
										HashRawCoupleSignData;
	PNC_HOST_CP_RAW_COUPLE_SIGN_HASH	RawCoupleSignHash;
	PNC_HOST_CP_VERIFY_RAW_COUPLE_SIGN_HASH
										VerifyRawCoupleSignHash;
	PNC_HOST_CP_CHECK_RAW_COUPLE_SIGN_PUBLIC_KEY
										CheckRawCoupleSignPublicKey;
} NC_HOST_CP_INTERFACE_EX, *PNC_HOST_CP_INTERFACE_EX;

//=============================================================================

#define NC_HOST_CP_EVENT_TYPE_UNKNOWN							0
#define NC_HOST_CP_EVENT_TYPE_INFORMATION						1
#define NC_HOST_CP_EVENT_TYPE_WARNING							2
#define NC_HOST_CP_EVENT_TYPE_ERROR								3

#define NC_HOST_CP_PEER_IP_ADDRESS_NONE							0

#define NC_HOST_CP_MAX_MESSAGE_LENGTH							255
#define NC_HOST_CP_MAX_CERT_OWNER_LENGTH						511

#define NC_HOST_CP_CA_DEFAULT_TCP_PORT							80
#define NC_HOST_CP_MAX_CA_GATEWAY_CONNECTORS					64

#define NC_HOST_CP_MAX_JSON_SERVER_CONNECTORS					4

//-----------------------------------------------------------------------------

#define NC_HOST_CP_EVENT_CODE_UNKNOWN							0
#define NC_HOST_CP_EVENT_START_CA_GATEWAY						1
#define NC_HOST_CP_EVENT_STOP_CA_GATEWAY						2
#define NC_HOST_CP_EVENT_CODE_CORRUPTED_REQUEST_RECEPTION		3
#define NC_HOST_CP_EVENT_CODE_TSP_REQUEST_RECEPTION				4
#define NC_HOST_CP_EVENT_CODE_TSP_REQUEST_PARSING				5
#define NC_HOST_CP_EVENT_CODE_TSP_REQUEST_PROCESSING			6
#define NC_HOST_CP_EVENT_CODE_OCSP_REQUEST_RECEPTION			7
#define NC_HOST_CP_EVENT_CODE_OCSP_REQUEST_PARSING				8
#define NC_HOST_CP_EVENT_CODE_OCSP_REQUEST_PROCESSING			9
#define NC_HOST_CP_EVENT_CODE_CMP_REQUEST_RECEPTION				10
#define NC_HOST_CP_EVENT_CODE_CMP_REQUEST_PARSING				11
#define NC_HOST_CP_EVENT_CODE_CMP_REQUEST_PROCESSING			12
#define NC_HOST_CP_EVENT_CODE_CRL_DOWNLOAD_RECEPTION			13
#define NC_HOST_CP_EVENT_CODE_CRL_DOWNLOAD_PARSING				14
#define NC_HOST_CP_EVENT_CODE_CRL_DOWNLOAD_PROCESSING			15

#define NC_HOST_CP_CA_GATEWAY_EVENT_CODES						16

//-----------------------------------------------------------------------------

typedef VOID (OS_API *PNC_HOST_CP_REPORT_GATEWAY_EVENT_CALLBACK)(
	UINT		uiType,
	UINT		uiCode,
	UINT		uiError,
	UINT		uiPeerAddress,
	PSTR		pszCertOwner,
	PSTR		pszMessage);

typedef BOOL (OS_API *PNC_HOST_CP_CHECK_GATEWAY_ACCESS_CALLBACK)(
	UINT		uiPeerAddress,
	PSTR		pszCertOwner);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_START_CA_GATEWAY)(
	PCSTR	pszAddress,
	WORD	wPort,
	UINT	uiConectors,
	PNC_HOST_CP_REPORT_GATEWAY_EVENT_CALLBACK
			pReportEventCallback,
	PNC_HOST_CP_CHECK_GATEWAY_ACCESS_CALLBACK
			pCheckAccessCallback);

typedef VOID (OS_API *PNC_HOST_CP_STOP_CA_GATEWAY)();

//-----------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct
{
	DWORDLONG		dwlCorruptedRequests;

	DWORDLONG		dwlReceivedTSPRequests;
	DWORDLONG		dwlProcessedTSPRequests;
	DWORDLONG		dwlUnprocessedTSPRequests;

	DWORDLONG		dwlReceivedOCSPRequests;
	DWORDLONG		dwlProcessedOCSPRequests;
	DWORDLONG		dwlUnprocessedOCSPRequests;

	DWORDLONG		dwlReceivedCMPRequests;
	DWORDLONG		dwlProcessedCMPRequests;
	DWORDLONG		dwlUnprocessedCMPRequests;

	DWORDLONG		dwlReceivedCRLDownloads;
	DWORDLONG		dwlProcessedCRLDownloads;
	DWORDLONG		dwlUnprocessedCRLDownloads;

	SYSTEMTIME		LastReceivedRequestTime;
	SYSTEMTIME		LastProcessedRequestTime;
	SYSTEMTIME		LastUnprocessedRequestTime;
} PACKED NC_HOST_CP_CA_GATEWAY_STAT, *PNC_HOST_CP_CA_GATEWAY_STAT;

#ifdef HP_BIG_ENDIAN	
#define SWAP_PNC_HOST_CP_CA_GATEWAY_STAT(x)						\
	do {														\
		SWAP_PDWORDLONG(&(x)->dwlCorruptedRequests);			\
		SWAP_PDWORDLONG(&(x)->dwlReceivedTSPRequests);			\
		SWAP_PDWORDLONG(&(x)->dwlProcessedTSPRequests);			\
		SWAP_PDWORDLONG(&(x)->dwlUnprocessedTSPRequests);		\
		SWAP_PDWORDLONG(&(x)->dwlReceivedOCSPRequests);			\
		SWAP_PDWORDLONG(&(x)->dwlProcessedOCSPRequests);		\
		SWAP_PDWORDLONG(&(x)->dwlUnprocessedOCSPRequests);		\
		SWAP_PDWORDLONG(&(x)->dwlReceivedCMPRequests);			\
		SWAP_PDWORDLONG(&(x)->dwlProcessedCMPRequests);			\
		SWAP_PDWORDLONG(&(x)->dwlUnprocessedCMPRequests);		\
		SWAP_PDWORDLONG(&(x)->dwlReceivedCRLDownloads);			\
		SWAP_PDWORDLONG(&(x)->dwlProcessedCRLDownloads);		\
		SWAP_PDWORDLONG(&(x)->dwlUnprocessedCRLDownloads);		\
		SWAP_SYSTEMTIME((x)->LastReceivedRequestTime);			\
		SWAP_SYSTEMTIME((x)->LastProcessedRequestTime);			\
		SWAP_SYSTEMTIME((x)->LastUnprocessedRequestTime);		\
	} while(0)
#endif
#pragma pack(pop)

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_GET_CA_GATEWAY_STAT)(
	PNC_HOST_CP_CA_GATEWAY_STAT	pStat);

//-----------------------------------------------------------------------------

#define NC_HOST_CP_CA_GATEWAY_REPORT_EVENTS_MODE_DEFAULT		0
#define NC_HOST_CP_CA_GATEWAY_REPORT_EVENTS_MODE_ALL_INFOS		0x00000001

//-----------------------------------------------------------------------------

typedef VOID (OS_API *PNC_HOST_CP_SET_CA_GATEWAY_REPORT_EVENTS_MODE)(
	UINT	uiMode);

//=============================================================================

typedef struct
{
	PNC_HOST_CP_START_CA_GATEWAY	StartCAGateway;
	PNC_HOST_CP_STOP_CA_GATEWAY		StopCAGateway;

	PNC_HOST_CP_GET_CA_GATEWAY_STAT	GetCAGatewayStat;
	PNC_HOST_CP_SET_CA_GATEWAY_REPORT_EVENTS_MODE
									SetCAGatewayReportEventsMode;
} NC_HOST_CP_INTERFACE_CA_GATEWAY, *PNC_HOST_CP_INTERFACE_CA_GATEWAY;

//=============================================================================

typedef BOOL (OS_API *PNC_HOST_CP_JSON_SERVER_CHECK_ACCESS_CALLBACK)(
	UINT	uiPeerAddress);

typedef BOOL (OS_API *PNC_HOST_CP_JSON_SERVER_HANDLE_REQUEST_CALLBACK)(
	UINT	uiPeerAddress,
	PBYTE	pbRequest,
	DWORD	dwRequestSize,
	PBYTE	*ppbResponse,
	PDWORD	pdwResponseSize);

typedef BOOL (OS_API *PNC_HOST_CP_JSON_SERVER_FREE_RESPONSE_CALLBACK)(
	PBYTE	pbResponse,
	DWORD	dwResponseSize);

//-----------------------------------------------------------------------------

typedef DWORD (OS_API *PNC_HOST_CP_START_JSON_SERVER)(
	PCSTR	pszAddress,
	WORD	wPort,
	UINT	uiConectors,
	PNC_HOST_CP_JSON_SERVER_CHECK_ACCESS_CALLBACK
			pCheckAccessCallback,
	PNC_HOST_CP_JSON_SERVER_HANDLE_REQUEST_CALLBACK
			pHandleRequestCallback,
	PNC_HOST_CP_JSON_SERVER_FREE_RESPONSE_CALLBACK
			pFreeResponseCallback);

typedef VOID (OS_API *PNC_HOST_CP_STOP_JSON_SERVER)();

//=============================================================================

typedef struct
{
	PNC_HOST_CP_START_JSON_SERVER	StartJSONServer;
	PNC_HOST_CP_STOP_JSON_SERVER	StopJSONServer;
} NC_HOST_CP_INTERFACE_JSON_SERVER,
*PNC_HOST_CP_INTERFACE_JSON_SERVER;

//=============================================================================

#ifndef NC_HOST_INTERNAL
#ifdef OS_MAC
#define NC_HOST_CP_LIB_NAME		"nchcp.dylib"
#elif defined(ANDROID_NDK)
#define NC_HOST_CP_LIB_NAME		"libnchcp.so"
#elif defined (OS_NIX)
#define NC_HOST_CP_LIB_NAME		"nchcp.so"
#else
#define NC_HOST_CP_LIB_NAME		"NCHostCP.dll"
#endif // OS_NIX
#else // NC_HOST_INTERNAL
#ifdef OS_LINUX
#define NC_HOST_CP_LIB_NAME		"nchcp.so"
#else
#define NC_HOST_CP_LIB_NAME		"NCHostCP.dll"
#endif // OS_LINUX
#endif // NC_HOST_INTERNAL

//=============================================================================

typedef PNC_HOST_CP_INTERFACE (OS_API *PNC_HOST_CP_GET_INTERFACE)();

typedef VOID (OS_API *PNC_HOST_CP_FREE_INTERFACE)(
	PNC_HOST_CP_INTERFACE		pInterface);

typedef PNC_HOST_CP_INTERFACE_EX (OS_API *PNC_HOST_CP_GET_INTERFACE_EX)();

typedef VOID (OS_API *PNC_HOST_CP_FREE_INTERFACE_EX)(
	PNC_HOST_CP_INTERFACE_EX	pInterface);

//------------------------------------------------------------------------------

typedef PNC_HOST_CP_INTERFACE_CA_GATEWAY 
	(OS_API *PNC_HOST_CP_GET_INTERFACE_CA_GATEWAY)();

typedef VOID (OS_API *PNC_HOST_CP_FREE_INTERFACE_CA_GATEWAY)(
	PNC_HOST_CP_INTERFACE_CA_GATEWAY	pInterface);

//------------------------------------------------------------------------------

typedef PNC_HOST_CP_INTERFACE_JSON_SERVER
	(OS_API *PNC_HOST_CP_GET_INTERFACE_JSON_SERVER)();

typedef VOID (OS_API *PNC_HOST_CP_FREE_INTERFACE_JSON_SERVER)(
	PNC_HOST_CP_INTERFACE_JSON_SERVER	pInterface);

//------------------------------------------------------------------------------

typedef UINT (OS_API *PNC_HOST_CP_GET_VERSION)();

//=============================================================================

class NCHostCP
{
private:
	HMODULE	hLibrary;

private:
	PNC_HOST_CP_GET_INTERFACE		pGetInterface;
	PNC_HOST_CP_FREE_INTERFACE		pFreeInterface;
	PNC_HOST_CP_GET_INTERFACE_EX	pGetInterfaceEx;
	PNC_HOST_CP_FREE_INTERFACE_EX	pFreeInterfaceEx;

	PNC_HOST_CP_GET_INTERFACE_CA_GATEWAY
									pGetInterfaceCAGateway;
	PNC_HOST_CP_FREE_INTERFACE_CA_GATEWAY
									pFreeInterfaceCAGateway;

	PNC_HOST_CP_GET_VERSION			pGetVersion;

	PNC_HOST_CP_GET_INTERFACE_JSON_SERVER
									pGetInterfaceJSONServer;
	PNC_HOST_CP_FREE_INTERFACE_JSON_SERVER
									pFreeInterfaceJSONServer;

public:
	NCHostCP();
	~NCHostCP();

public:
	BOOL	Load(
			PCSTR					pszLocation = NULL);

	VOID	Unload();

public:
	PNC_HOST_CP_INTERFACE
			GetInterface();

	VOID	FreeInterface(
			PNC_HOST_CP_INTERFACE	pInterface);

	PNC_HOST_CP_INTERFACE_EX
			GetInterfaceEx();

	VOID	FreeInterfaceEx(
			PNC_HOST_CP_INTERFACE_EX
									pInterface);

	PNC_HOST_CP_INTERFACE_CA_GATEWAY
			GetInterfaceCAGateway();

	VOID	FreeInterfaceCAGateway(
			PNC_HOST_CP_INTERFACE_CA_GATEWAY
									pInterface);

	PNC_HOST_CP_INTERFACE_JSON_SERVER
			GetInterfaceJSONServer();

	VOID	FreeInterfaceJSONServer(
			PNC_HOST_CP_INTERFACE_JSON_SERVER
									pInterface);

	UINT	GetVersion();

public:
#ifndef NC_HOST_INTERNAL
	VOID	ReportError(
			PSTR					pszCaption,
			PNC_HOST_CP_INTERFACE	pInterface,
			DWORD					dwError,
			PSTR					pszError,
			BOOL					bShow,
			HWND					hParentWindow);
#endif // NC_HOST_INTERNAL
};

//==============================================================================

#define NC_HOST_CP_NONE_VERSION								1

#define NC_HOST_CP_SET_CRYPTO_SUITE_COMPATIBLE_VERSION		31

//==============================================================================

BOOL NCHostICPInitialize();

PNC_HOST_CP_INTERFACE NCHostICPGetInterface();

VOID NCHostICPFreeInterface(
	PNC_HOST_CP_INTERFACE			pInterface);

PNC_HOST_CP_INTERFACE_EX NCHostICPGetInterfaceEx();

VOID NCHostICPFreeInterfaceEx(
	PNC_HOST_CP_INTERFACE_EX		pInterface);

PNC_HOST_CP_INTERFACE_CA_GATEWAY NCHostICPGetInterfaceCAGateway();

VOID NCHostICPFreeInterfaceCAGateway(
	PNC_HOST_CP_INTERFACE_CA_GATEWAY
									pInterface);

PNC_HOST_CP_INTERFACE_JSON_SERVER NCHostICPGetInterfaceJSONServer();

VOID NCHostICPFreeInterfaceJSONServer(
	PNC_HOST_CP_INTERFACE_JSON_SERVER
									pInterface);

UINT NCHostICPGetVersion();

VOID NCHostICPFinalize();

//==============================================================================

#endif // NC_HOST_CRYPTO_PROVIDER_H
