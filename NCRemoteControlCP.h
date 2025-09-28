#ifndef NC_REMOTE_CONTROL_CRYPTO_PROVIDER_H
#define NC_REMOTE_CONTROL_CRYPTO_PROVIDER_H

//=============================================================================

#ifdef OS_NIX
    #include "./OSIntermediate/OSIntermediate.h"
#else // OS_NIX
	#include <windows.h>
	#include <stdio.h>
#endif // OS_NIX

//=============================================================================

#define NC_REMOTE_CONTROL_CP_MAX_ERROR_DESCR_LENGTH		1024
#define NC_REMOTE_CONTROL_CP_MAX_CERT_ID_LENGTH			1024

//-----------------------------------------------------------------------------

#define	NC_REMOTE_CONTROL_CP_ERROR_NONE					0
#define	NC_REMOTE_CONTROL_CP_WARNING_END_OF_ENUM		0x0007
#define	NC_REMOTE_CONTROL_CP_ERROR_CANCELED_BY_GUI		0x000C
#define	NC_REMOTE_CONTROL_CP_PKI_FORMATS_FAILED			0x0021
#define	NC_REMOTE_CONTROL_CP_CSP_FAILED					0x0022
#define	NC_REMOTE_CONTROL_CP_ERROR_BAD_CERT				0x0032
#define	NC_REMOTE_CONTROL_CP_ERROR_NOT_SUPPORTED		0xFFFE

#ifndef NC_HOST_CP_ERROR_NONE
#define NC_HOST_CP_ERROR_NONE							\
		NC_REMOTE_CONTROL_CP_ERROR_NONE
#endif

//-----------------------------------------------------------------------------

#define NC_REMOTE_CONTROL_CP_MAX_PASSWORD_LENGTH		64
#define NC_REMOTE_CONTROL_CP_MAX_PROT_PASSWORD_OVERHEAD	24
#define NC_REMOTE_CONTROL_CP_MAX_PROT_PASSWORD_LENGTH	\
		(NC_REMOTE_CONTROL_CP_MAX_PASSWORD_LENGTH * 2 +	\
		NC_REMOTE_CONTROL_CP_MAX_PROT_PASSWORD_OVERHEAD)

#define NC_REMOTE_CONTROL_CP_MAX_KM_DESCR_LENGTH		256
	
//-----------------------------------------------------------------------------

#ifndef NC_HOST_CP_MAC_SIZE
#define NC_HOST_CP_MAC_SIZE								4
#define NC_HOST_CP_DATA_PROTECT_MAX_ADD_SIZE			12

#define NC_HOST_CP_MAC_ALGO2_SIZE						32
#define NC_HOST_CP_DATA_PROT_MAX_ADD_ALGO2_SIZE			64

#define NC_HOST_CP_PROT_ALGO_DSTU7624					2
#endif // NC_HOST_CP_MAC_SIZE

//-----------------------------------------------------------------------------

#define NC_REMOTE_CONTROL_CP_CERT_TYPE_OWN				1
#define NC_REMOTE_CONTROL_CP_CERT_TYPE_HOST				2

//-----------------------------------------------------------------------------

#define NC_REMOTE_CONTROL_CP_OTP_DEF_TIME_STEP			30

#define NC_REMOTE_CONTROL_CP_OTP_KEY_LENGTH				20

#define NC_REMOTE_CONTROL_CP_OTP_MIN_DIGITS				1
#define NC_REMOTE_CONTROL_CP_OTP_MAX_DIGITS				8
#define NC_REMOTE_CONTROL_CP_OTP_DEF_DIGITS				6

//-----------------------------------------------------------------------------

#define NC_REMOTE_CONTROL_CP_HASH_ALGO_GOST34311		1
#define NC_REMOTE_CONTROL_CP_HASH_ALGO_DSTU7564			2

#define NC_REMOTE_CONTROL_CP_PROT_ALGO_GOST28147		1
#define NC_REMOTE_CONTROL_CP_PROT_ALGO_DSTU7624			2

#define NC_REMOTE_CONTROL_CP_ENCR_ALGO_GOST28147		1
#define NC_REMOTE_CONTROL_CP_ENCR_ALGO_DSTU7624			2
#define NC_REMOTE_CONTROL_CP_ENCR_ALGO_DSTU8845			3

#define NC_REMOTE_CONTROL_CP_CRYPTO_SUITE_GOSTS_DESCR	\
	"� ����� ���� 34.311-95 �� ������ ���� ���� 28147"
#define NC_REMOTE_CONTROL_CP_CRYPTO_SUITE_DSTUS_DESCR	\
	"� ����� ���� 7564 �� ������� ���� 7624 � 8845"

//-----------------------------------------------------------------------------

#define NC_REMOTE_CONTROL_CP_PARAMETERS_TYPE1			1
#define NC_REMOTE_CONTROL_CP_PARAMETERS_TYPE2			2

#define NC_REMOTE_CONTROL_CP_PARAMETERS_TYPE1_DESCR		\
	"��� 1 (����� � ������ ���� ���� 28147)"
#define NC_REMOTE_CONTROL_CP_PARAMETERS_TYPE2_DESCR		\
	"��� 2 (� ������� ���� 7624 �� 8845)"

//=============================================================================

#pragma pack(push, 1)
typedef struct
{
	DWORD			dwTypeIndex;
	DWORD			dwDevIndex;
	CHAR			szPassword[
		NC_REMOTE_CONTROL_CP_MAX_PASSWORD_LENGTH + 1];
} NC_REMOTE_CONTROL_CP_KEY_MEDIA, *PNC_REMOTE_CONTROL_CP_KEY_MEDIA;
#pragma pack(pop)

//=============================================================================

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_INITIALIZE)(
	BOOL	bOnlyCrypto);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_FINALIZE)();

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SET_SETTINGS)();

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SET_HOST_SETTINGS)(
	PBYTE	pbInputSettings,
	DWORD	dwInputSettings,
	PBYTE	*ppbOutputSettings,
	PDWORD	pdwOutputSettings);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_PRIVATE_KEY_MEDIA)(
	PNC_REMOTE_CONTROL_CP_KEY_MEDIA		pKeyMedia);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_READ_PRIVATE_KEY)(
	PNC_REMOTE_CONTROL_CP_KEY_MEDIA		pKeyMedia,
	PDWORD 								pdwPrivKey);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_PRIVATE_KEY_CERT_ID)(
	DWORD 								dwPrivKey,
	PSTR								pszCertID);

typedef VOID (WINAPI *PNC_REMOTE_CONTROL_CP_SHOW_CERT_BY_PRIV_KEY)(
	DWORD 								dwPrivKey);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_FREE_PRIVATE_KEY)(
	DWORD 								dwPrivKey);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GENERATE_PRIVATE_KEY)(
	PSTR								pszParamsPath,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize,
	PSTR								pszReqFileName);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GENERATE_PRIVATE_KEY_EX)(
	PSTR								pszParamsPath,
	PBYTE								*ppbRequest,
	PDWORD								pdwRequestSize,
	PSTR								pszReqFileName,
	PBYTE								*ppbKEPRequest,
	PDWORD								pdwKEPRequestSize,
	PSTR								pszKEPReqFileName);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_AUTH_STEP1_CLIENT)(
	DWORD 	dwPrivKey,
	PBYTE 	*ppbSend,
	PDWORD 	pdwSendSize,
	PDWORD 	pdwSession);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_AUTH_STEP1_SERVER)(
	DWORD 	dwPrivKey,
	PBYTE 	pbReceive,
	DWORD 	dwReceiveSize,
	PBYTE 	*ppbSend,
	PDWORD 	pdwSendSize,
	PDWORD 	pdwClientCertificate,
	PDWORD 	pdwSession);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_AUTH_STEP2_CLIENT)(
	DWORD 	dwSession,
	PBYTE 	pbReceive,
	DWORD 	dwReceiveSize,
	PDWORD 	pdwServerCertificate);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP1_CLIENT)(
	PSTR	pszPassword,
	PBYTE 	*ppbSend,
	PDWORD 	pdwSendSize,
	PDWORD 	pdwSession);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP1_SERVER)(
	PSTR	pszPassword,
	PBYTE 	pbReceive,
	DWORD 	dwReceiveSize,
	PBYTE 	*ppbSend,
	PDWORD 	pdwSendSize,
	PDWORD 	pdwSession);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP2_CLIENT)(
	DWORD 	dwSession,
	PBYTE 	pbReceive,
	DWORD 	dwReceiveSize);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_CLOSE_SESSION)(
	DWORD 	dwSession);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_ENCRYPT_DATA)(
	DWORD 	dwSession,
	PBYTE 	pbData,
	DWORD 	dwDataSize);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_RESET_ENC_STATE)(
	DWORD	dwSession);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_DECRYPT_DATA)(
	DWORD 	dwSession,
	PBYTE 	pbEncrypted,
	DWORD 	dwEncryptedSize,
	BOOL 	blResetOffset);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_DATA_MAC)(
	DWORD	dwSession,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	pbMAC);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_HASH_DATA)(
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbHash,
	PDWORD	pdwHashSize);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GENERATE_PASSWORD)(
	PSTR	pszPassword,
	DWORD	dwPasswordLength);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_PROTECT_DATA)(
	PSTR	pszPassword,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbProtectedData,
	PDWORD	pdwProtectedDataSize);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_UNPROTECT_DATA)(
	PSTR	pszPassword,
	PBYTE	pbProtectedData,
	DWORD	dwProtectedDataSize,
	PBYTE	*ppbData,
	PDWORD	pdwDataSize);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_CERT_ID)(
	DWORD 	dwCertificate,
	PSTR 	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_CHECK_CERT_BY_ID)(
	PSTR 	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_IMPORT_CERTIFICATE)(
	DWORD 	dwCertificate);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SHOW_CERT_BY_ID)(
	PSTR 	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_FREE_CERTIFICATE)(
	DWORD 	dwCertificate);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_CERTIFICATES)(
	PBYTE	*ppbCertsChain,
	PDWORD	pdwCertsChainSize,
	PSTR	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_CERTS_BY_REQUEST)(
	PBYTE	pbRequest,
	DWORD	dwRequestSize,
	PBYTE	*ppbCertsChain,
	PDWORD	pdwCertsChainSize,
	PSTR	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_CERTS_BY_REQUEST_EX)(
	PBYTE	pbRequest,
	DWORD	dwRequestSize,
	PBYTE	pbKEPRequest,
	DWORD	dwKEPRequestSize,
	PBYTE	*ppbCertsChain,
	PDWORD	pdwCertsChainSize,
	PSTR	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_PRIVATE_KEY_AND_CERTS)(
	PSTR	pszPassword,
	PBYTE	*ppbPrivateKey,
	PDWORD	pdwPrivateKeySize,
	PBYTE	*ppbCertsChain,
	PDWORD	pdwCertsChainSize,
	PSTR	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SELECT_CERTIFICATE)(
	DWORD	dwCertType,
	PSTR	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_PARSE_CERTIFICATE)(
	PBYTE	pbCertificate,
	DWORD	dwCertSize,
	DWORD	dwCertType,
	BOOL	blShow,
	PSTR	pszCertID);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SHOW_CERTIFICATE)(
	PBYTE	pbCertificate,
	DWORD	dwCertSize,
	PSTR	pszCaption);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SHOW_CRL)(
	PBYTE	pbCRL,
	DWORD	dwCRLSize,
	PSTR	pszCaption);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_CHECK_CERTIFICATE)(
	PBYTE	pbCertificate,
	DWORD	dwCertSize);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_IMPORT_CERT_BY_DATA)(
	PBYTE	pbCertificate,
	DWORD	dwCertSize);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_CHANGE_PRIV_KEY_PASSWORD)();

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_DESTROY_PRIV_KEY)();

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_BACKUP_PRIV_KEY)();

typedef VOID (WINAPI *PNC_REMOTE_CONTROL_CP_SHOW_CERTS)();

typedef VOID (WINAPI *PNC_REMOTE_CONTROL_CP_SHOW_CRLS)();

//-----------------------------------------------------------------------------

typedef VOID (WINAPI *PNC_REMOTE_CONTROL_CP_GET_ERROR_DESCR)(
	DWORD 	dwError,
	PSTR 	pszErrorDescr);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_FREE_MEMORY)(
	PBYTE 	pbMemory);


//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_LOAD_PARAMETERS)(
	PSTR			pszParamsPath,
	PBYTE			*ppbParameters,
	PDWORD			pdwParametersSize);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SAVE_PARAMETERS)(
	PBYTE			pbParameters,
	DWORD			dwParametersSize,
	PSTR			pszParamsPath);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_ENCODE_BASE32)(
	PBYTE			pbData,
	DWORD			dwDataLength,
	PSTR			pszString);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_DECODE_BASE32)(
	PSTR			pszString,
	PBYTE			pbData,
	DWORD			dwDataLength);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_OTP_TIME_LEFT)(
	DWORD					dwTimeStep,
	PSYSTEMTIME				pstBeginTime,
	PSYSTEMTIME				pstTime,
	PDWORD					pdwTimeLeft);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GENERATE_OTP)(
	DWORD					dwTimeStep,
	PSYSTEMTIME				pstBeginTime,
	PSYSTEMTIME				pstTime,
	PBYTE					pbKey,
	DWORD					dwKeyLength,
	DWORD					dwDigits,
	PSTR					pszOTP);

//-----------------------------------------------------------------------------

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_GET_DATA_MAC_SIZE)(
	DWORD	dwSession);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_HASH_DATA_EX)(
	DWORD	dwHashType,
	PBYTE	pbData,
	DWORD	dwDataSize,
	PBYTE	*ppbHash,
	PDWORD	pdwHashSize);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_LOAD_PARAMETERS_EX)(
	PSTR	pszParamsPath,
	UINT	uiParamsType,
	PBYTE	*ppbParameters,
	PDWORD	pdwParametersSize);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SAVE_PARAMETERS_EX)(
	PBYTE	pbParameters,
	DWORD	dwParametersSize,
	PSTR	pszParamsPath,
	PUINT	puiParamsType);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_SET_CRYPTO_SUITE)(
	DWORD	dwHashAlgo,
	DWORD	dwProtAlgo,
	DWORD	dwEncrAlgo);

typedef DWORD (WINAPI *PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP1_CLIENT_EX)(
	DWORD	dwProtAlgo,
	PSTR	pszPassword,
	PBYTE	*ppbSend,
	PDWORD	pdwSendSize,
	PDWORD	pdwSession);

//=============================================================================

typedef struct
{
	PNC_REMOTE_CONTROL_CP_INITIALIZE				Initialize;
	PNC_REMOTE_CONTROL_CP_FINALIZE					Finalize;

	PNC_REMOTE_CONTROL_CP_SET_SETTINGS				SetSettings;
	PNC_REMOTE_CONTROL_CP_SET_HOST_SETTINGS			SetHostSettings;

	PNC_REMOTE_CONTROL_CP_GET_PRIVATE_KEY_MEDIA		GetPrivateKeyMedia;
	PNC_REMOTE_CONTROL_CP_READ_PRIVATE_KEY			ReadPrivateKey;
	PNC_REMOTE_CONTROL_CP_GET_PRIVATE_KEY_CERT_ID	GetPrivateKeyCertID;
	PNC_REMOTE_CONTROL_CP_SHOW_CERT_BY_PRIV_KEY		ShowCertByPrivKey;
	PNC_REMOTE_CONTROL_CP_FREE_PRIVATE_KEY			FreePrivateKey;
	PNC_REMOTE_CONTROL_CP_GENERATE_PRIVATE_KEY		GeneratePrivateKey;

	PNC_REMOTE_CONTROL_CP_AUTH_STEP1_CLIENT			AuthStep1Client;
	PNC_REMOTE_CONTROL_CP_AUTH_STEP1_SERVER			AuthStep1Server;
	PNC_REMOTE_CONTROL_CP_AUTH_STEP2_CLIENT			AuthStep2Client;

	PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP1_CLIENT	
													PreSharedAuthStep1Client;
	PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP1_SERVER	
													PreSharedAuthStep1Server;
	PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP2_CLIENT	
													PreSharedAuthStep2Client;

	PNC_REMOTE_CONTROL_CP_CLOSE_SESSION				CloseSession;

	PNC_REMOTE_CONTROL_CP_GET_CERT_ID				GetCertID;
	PNC_REMOTE_CONTROL_CP_CHECK_CERT_BY_ID			CheckCertByID;
	PNC_REMOTE_CONTROL_CP_IMPORT_CERTIFICATE		ImportCertificate;
	PNC_REMOTE_CONTROL_CP_SHOW_CERT_BY_ID			ShowCertByID;
	PNC_REMOTE_CONTROL_CP_FREE_CERTIFICATE			FreeCertificate;
	PNC_REMOTE_CONTROL_CP_GET_CERTIFICATES			GetCertificates;
	PNC_REMOTE_CONTROL_CP_GET_CERTS_BY_REQUEST		GetCertsByRequest;
	PNC_REMOTE_CONTROL_CP_GET_PRIVATE_KEY_AND_CERTS
													GetPrivateKeyAndCerts;
	PNC_REMOTE_CONTROL_CP_SELECT_CERTIFICATE		SelectCertificate;
	PNC_REMOTE_CONTROL_CP_PARSE_CERTIFICATE			ParseCertificate;
	PNC_REMOTE_CONTROL_CP_SHOW_CERTIFICATE			ShowCertificate;
	PNC_REMOTE_CONTROL_CP_SHOW_CRL					ShowCRL;
	PNC_REMOTE_CONTROL_CP_CHECK_CERTIFICATE			CheckCertificate;
	PNC_REMOTE_CONTROL_CP_IMPORT_CERT_BY_DATA		ImportCertByData;

	PNC_REMOTE_CONTROL_CP_ENCRYPT_DATA				EncryptData;
	PNC_REMOTE_CONTROL_CP_RESET_ENC_STATE			ResetEncState;
	PNC_REMOTE_CONTROL_CP_DECRYPT_DATA				DecryptData;
	PNC_REMOTE_CONTROL_CP_GET_DATA_MAC				GetDataMAC;

	PNC_REMOTE_CONTROL_CP_HASH_DATA					HashData;

	PNC_REMOTE_CONTROL_CP_GENERATE_PASSWORD			GeneratePassword;

	PNC_REMOTE_CONTROL_CP_PROTECT_DATA				ProtectData;
	PNC_REMOTE_CONTROL_CP_UNPROTECT_DATA			UnprotectData;

	PNC_REMOTE_CONTROL_CP_CHANGE_PRIV_KEY_PASSWORD	ChangePrivateKeyPassword;
	PNC_REMOTE_CONTROL_CP_DESTROY_PRIV_KEY			DestroyPrivateKey;
	PNC_REMOTE_CONTROL_CP_BACKUP_PRIV_KEY			BackupPrivateKey;
	PNC_REMOTE_CONTROL_CP_SHOW_CERTS				ShowCertificates;
	PNC_REMOTE_CONTROL_CP_SHOW_CRLS					ShowCRLs;

	PNC_REMOTE_CONTROL_CP_GET_ERROR_DESCR			GetErrorDescr;

	PNC_REMOTE_CONTROL_CP_FREE_MEMORY				FreeMemory;
} NC_REMOTE_CONTROL_CP_INTERFACE, *PNC_REMOTE_CONTROL_CP_INTERFACE;

//------------------------------------------------------------------------------

typedef struct
{
	PNC_REMOTE_CONTROL_CP_GENERATE_PRIVATE_KEY_EX	GeneratePrivateKeyEx;
	PNC_REMOTE_CONTROL_CP_GET_CERTS_BY_REQUEST_EX	GetCertsByRequestEx;

	PNC_REMOTE_CONTROL_CP_LOAD_PARAMETERS			LoadParameters;
	PNC_REMOTE_CONTROL_CP_SAVE_PARAMETERS			SaveParameters;

	PNC_REMOTE_CONTROL_CP_ENCODE_BASE32				EncodeBase32;
	PNC_REMOTE_CONTROL_CP_DECODE_BASE32				DecodeBase32;

	PNC_REMOTE_CONTROL_CP_GET_OTP_TIME_LEFT			GetOTPTimeLeft;
	PNC_REMOTE_CONTROL_CP_GENERATE_OTP				GenerateOTP;

	PNC_REMOTE_CONTROL_CP_GET_DATA_MAC_SIZE			GetDataMACSize;
	PNC_REMOTE_CONTROL_CP_HASH_DATA_EX				HashDataEx;
	PNC_REMOTE_CONTROL_CP_LOAD_PARAMETERS_EX			LoadParametersEx;
	PNC_REMOTE_CONTROL_CP_SAVE_PARAMETERS_EX			SaveParametersEx;
	PNC_REMOTE_CONTROL_CP_SET_CRYPTO_SUITE			SetCryptoSuite;
	PNC_REMOTE_CONTROL_CP_PRE_SHARED_AUTH_STEP1_CLIENT_EX
													PreSharedAuthStep1ClientEx;
} NC_REMOTE_CONTROL_CP_INTERFACE_EX, *PNC_REMOTE_CONTROL_CP_INTERFACE_EX;

//=============================================================================

#define NC_REMOTE_CONTROL_CP_DLL_NAME		"NCRemoteControlCP.dll"

//=============================================================================

typedef PNC_REMOTE_CONTROL_CP_INTERFACE (WINAPI *
	PNC_REMOTE_CONTROL_CP_GET_INTERFACE)();

typedef VOID (WINAPI *PNC_REMOTE_CONTROL_CP_FREE_INTERFACE)(
	PNC_REMOTE_CONTROL_CP_INTERFACE 	pInterface);

typedef PNC_REMOTE_CONTROL_CP_INTERFACE_EX (WINAPI *
	PNC_REMOTE_CONTROL_CP_GET_INTERFACE_EX)();

typedef VOID (WINAPI *PNC_REMOTE_CONTROL_CP_FREE_INTERFACE_EX)(
	PNC_REMOTE_CONTROL_CP_INTERFACE_EX	pInterface);

//------------------------------------------------------------------------------

typedef UINT (WINAPI *PNC_REMOTE_CONTROL_CP_GET_VERSION)();

//=============================================================================

class NCRemoteControlCP
{
private:
	HMODULE	hDLL;

private:
	PNC_REMOTE_CONTROL_CP_GET_INTERFACE		pGetInterface;
	PNC_REMOTE_CONTROL_CP_FREE_INTERFACE	pFreeInterface;
	PNC_REMOTE_CONTROL_CP_GET_INTERFACE_EX	pGetInterfaceEx;
	PNC_REMOTE_CONTROL_CP_FREE_INTERFACE_EX	pFreeInterfaceEx;

	PNC_REMOTE_CONTROL_CP_GET_VERSION		pGetVersion;

public:
	NCRemoteControlCP();
	~NCRemoteControlCP();

public:
	BOOL 	Load();

	VOID 	Unload();

public:
	PNC_REMOTE_CONTROL_CP_INTERFACE 
			GetInterface();

	VOID 	FreeInterface(
			PNC_REMOTE_CONTROL_CP_INTERFACE	pInterface);

	PNC_REMOTE_CONTROL_CP_INTERFACE_EX 
			GetInterfaceEx();

	VOID 	FreeInterfaceEx(
			PNC_REMOTE_CONTROL_CP_INTERFACE_EX	pInterface);

	UINT	GetVersion();

public:
	VOID	ReportError(
			PSTR							pszCaption,
			PNC_REMOTE_CONTROL_CP_INTERFACE	pInterface,
			DWORD							dwError,
			PSTR							pszError,
			BOOL							bShow,
			HWND							hParentWindow);
};

//==============================================================================

#ifndef NC_HOST_CP_NONE_VERSION
#define NC_HOST_CP_NONE_VERSION								1

#define NC_HOST_CP_SET_CRYPTO_SUITE_COMPATIBLE_VERSION		31
#endif // NC_HOST_CP_NONE_VERSION

//==============================================================================

#endif // NC_REMOTE_CONTROL_CRYPTO_PROVIDER_H
