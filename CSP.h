#ifndef CSP_H
#define CSP_H

//======================================================================================================================

#include "CSPBase.h"
#include "CSPParameters.h"

//----------------------------------------------------------------------------------------------------------------------

#include "ICSP.h"

//======================================================================================================================

#ifdef PC_PERFORMANCE_TEST

//----------------------------------------------------------------------------------------------------------------------

#define PC_PERFORMANCE_TEST_START(TestName)						\
	static	LARGE_INTEGER	li##TestName##Frequency;			\
	static	DWORD			dw##TestName##Tests = 1;			\
	static	double			d##TestName##Duration = 0;			\
			LARGE_INTEGER	liOne##TestName##Duration;			\
			LARGE_INTEGER	li##TestName##Start;				\
			LARGE_INTEGER	li##TestName##Stop;					\
	QueryPerformanceFrequency(&li##TestName##Frequency);		\
	QueryPerformanceCounter(&li##TestName##Start);				\

//----------------------------------------------------------------------------------------------------------------------

#define PC_PERFORMANCE_TEST_STOP(TestName)						\
	QueryPerformanceCounter(&li##TestName##Stop);				\
	liOne##TestName##Duration.QuadPart =						\
		(li##TestName##Stop.QuadPart -							\
			li##TestName##Start.QuadPart) * 1000;				\
	d##TestName##Duration +=									\
		(double) liOne##TestName##Duration.QuadPart /			\
			(double) li##TestName##Frequency.QuadPart;			\
	printf("% 8d " #TestName " (ms): %f\n",						\
		dw##TestName##Tests,									\
		(double) liOne##TestName##Duration.QuadPart /			\
			(double) li##TestName##Frequency.QuadPart);			\
	if(dw##TestName##Tests == 100)								\
	{															\
		printf(" Medium: " #TestName " (ms): %f\n",				\
			d##TestName##Duration /								\
				(double) dw##TestName##Tests);					\
		d##TestName##Duration = 0;								\
		dw##TestName##Tests = 0;								\
	}															\
	dw##TestName##Tests++;										\

//----------------------------------------------------------------------------------------------------------------------

#else // PC_PERFORMANCE_TEST

//----------------------------------------------------------------------------------------------------------------------

#define PC_PERFORMANCE_TEST_START(TestName)
#define PC_PERFORMANCE_TEST_STOP(TestName)

//----------------------------------------------------------------------------------------------------------------------

#endif // PC_PERFORMANCE_TEST

//======================================================================================================================

#define CSP_CHECK_COMPATIBLE(pCSP, dwCompatibleLevel,			\
	bCompatible)												\
	{															\
		DSTU4145_PARAMETER_EC	ECCompat;						\
		DSTU4145_PARAMETER_P	PCompat;						\
		ZeroMemory(&ECCompat,									\
			sizeof(DSTU4145_PARAMETER_EC));						\
		ZeroMemory(&PCompat,									\
			sizeof(DSTU4145_PARAMETER_P));						\
		PCompat.dwBits = dwCompatibleLevel;						\
		bCompatible = (pCSP->GenerateDSKeys(					\
				&ECCompat, &PCompat, NULL, NULL) ==				\
			CSP_NO_ERROR);										\
	}															\

#define CSP_CHECK_COMPATIBLE_CTX(pCSP, pContext,				\
	dwCompatibleLevel, bCompatible)								\
	{															\
		DSTU4145_PARAMETER_EC	ECCompat;						\
		DSTU4145_PARAMETER_P	PCompat;						\
		ZeroMemory(&ECCompat,									\
			sizeof(DSTU4145_PARAMETER_EC));						\
		ZeroMemory(&PCompat,									\
			sizeof(DSTU4145_PARAMETER_P));						\
		PCompat.dwBits = dwCompatibleLevel;						\
		bCompatible = (pCSP->GenerateDSKeysCtx(					\
				pContext, &ECCompat, &PCompat,					\
				NULL, NULL) == CSP_NO_ERROR);					\
	}															\

#define CSP_COMPATIBLE_LEVEL_KDF_UA							8
#define CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION			9
#define CSP_COMPATIBLE_LEVEL_RECOVER_PUBLIC_KEY				10
#define CSP_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY	11
#define CSP_COMPATIBLE_LEVEL_PARAMS_PASSWORD				12
#define CSP_COMPATIBLE_LEVEL_CTX							13
#define CSP_COMPATIBLE_LEVEL_HARDWARE_DS_COUPLE				14
#define CSP_COMPATIBLE_LEVEL_DSTU7624						15
#define CSP_COMPATIBLE_LEVEL_DSTU7564						16
#define CSP_COMPATIBLE_LEVEL_HARDWARE_SIGN_DSTU_HASH		17
#define CSP_COMPATIBLE_LEVEL_DSTU8845						18
#define CSP_COMPATIBLE_LEVEL_KDF_DSTU7564					19
#define CSP_COMPATIBLE_LEVEL_DSTU7624_WRAP_KEY				20
#define CSP_COMPATIBLE_LEVEL_HARDWARE_DSTU7624_WRAP_KEY		21
#define CSP_COMPATIBLE_LEVEL_ITERATIVE_DSTU7624_CFB_MODE	22
#define CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA			23
#define CSP_COMPATIBLE_LEVEL_DENSE_NUMBERS					24

//======================================================================================================================

#define DSTU7624_PROTECTED_DATA_EX(DataBytes, BlockBytes,		\
		MACBytes)												\
	((BlockBytes) + DSTU7624_CBC_MODE_OUTPUT_DATA(				\
		(DataBytes) * 8, (BlockBytes) * 8) / 8 +				\
	(MACBytes) + 1)

#define DSTU7624_PROTECTED_DATA(DataBytes, BlockBytes)			\
	DSTU7624_PROTECTED_DATA_EX(DataBytes, BlockBytes,			\
		BlockBytes)

//======================================================================================================================

#if defined(EM_SDK) || defined(OS_IOS)
#define CSP_DISABLE_SELF_TESTS
#endif // EM_SDK || OS_IOS

//======================================================================================================================

typedef struct
{
	ICSPHardwareRNG						*pHardwareRNG;
	ICSPHardware 						*pHardwareCSP;

	PDSTU4145_PSEUDO_RNG_STATE			pPRNGState;
} CSP_CTX, *PCSP_CTX;

#define CSP_CTX_INITIALIZE(Context)								\
	(Context).pHardwareRNG =									\
		(m_dwState & CSP_STATE_HRNG_INITIALIZED) ?				\
			m_pHardwareRNG : NULL;								\
	(Context).pHardwareCSP =									\
		(m_dwState & CSP_STATE_HARDWARE_CSP_INITIALIZED) ?		\
			m_pHardwareCSP : NULL;								\
	(Context).pPRNGState = pPRNGState;							\

//======================================================================================================================

class CSP
{
public:
	CSP();
	~CSP();

public:
	CSPBase								Base;
	CSPParameters						Parameters;

	PDSTU4145_PSEUDO_RNG_STATE			pPRNGState;

private:
	ICSPHardwareRNG						*m_pHardwareRNG;
	ICSPHardware 						*m_pHardwareCSP;

	DWORD								m_dwState;

	PCSP_BASE_FUNCTIONS_EX				m_pBaseEx;

	PSTR								m_pszParamsPassword;

	CRITICAL_SECTION					m_CriticalSection;

public:
	virtual DWORD 	WINAPI Initialize();

	virtual DWORD 	WINAPI InitializePRNG(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_BLOCK 			pSeed,
			GOST28147_KEY				pKey);

	virtual DWORD 	WINAPI InitializeHRNG(
			ICSPHardwareRNG				*pHardwareRNG);

	virtual DWORD 	WINAPI GeneratePRNSequence(
			PBYTE 						pbSequence,
			DWORD 						dwSequence);
	
	virtual DWORD 	WINAPI GenerateRNSequence(
			PBYTE 						pbSequence,
			DWORD 						dwSequence);

	virtual DWORD 	WINAPI GenerateRPRNSequence(
			PBYTE 						pbSequence,
			DWORD 						dwSequence);

	virtual DWORD 	WINAPI ProtectData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			GOST28147_MAC 				pMAC,
			GOST28147_BLOCK 			pDataAligment,
			PDWORD 						pdwDataAligment,
			PCHAR 						pcPassword,
			GOST28147_KEY 				pKey);

	virtual DWORD 	WINAPI UnprotectData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			GOST28147_MAC 				pMAC,
			GOST28147_BLOCK 			pDataAligment,
			DWORD 						dwDataAligment,
			PCHAR 						pcPassword,
			GOST28147_KEY 				pKey);

	virtual DWORD 	WINAPI HashData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			GOST34311_HASH 				pHash);

	virtual DWORD 	WINAPI InitializeHashData(
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			PGOST34311_STATE 			*ppGOST34311State);

	virtual DWORD 	WINAPI ContinueHashData(
			PBYTE 						pbData,
			DWORD 						dwData,
			PGOST34311_STATE 			*ppGOST34311State);

	virtual DWORD 	WINAPI FinalizeHashData(
			GOST34311_HASH 				pHash,
			PGOST34311_STATE 			*ppGOST34311State);

	virtual DWORD 	WINAPI CheckDataHash(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			GOST34311_HASH 				pHash);

	virtual DWORD 	WINAPI EncryptData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV);

	virtual DWORD 	WINAPI DecryptData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV);

	virtual DWORD 	WINAPI InitializeEncryptData(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV,
			BOOL 						blGenerateKeyAndIV,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI ContinueEncryptData(
			PBYTE 						pbData,
			DWORD 						dwData,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI ContinueEncryptDataByOffset(
			PBYTE 						pbData,
			DWORD 						dwData,
			DWORDLONG 					dwlDataOffset,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI FinalizeEncryptData(
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD 	WINAPI InitializeDecryptData(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI ContinueDecryptData(
			PBYTE 						pbData,
			DWORD 						dwData,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI ContinueDecryptDataByOffset(
			PBYTE 						pbData,
			DWORD 						dwData,
			DWORDLONG 					dwlDataOffset,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI FinalizeDecryptData(
			PGOST28147_STATE 			*ppGOST28147State);

	virtual VOID 	WINAPI SetHardwareCSP(
			ICSPHardware				*pHardwareCSP);

	virtual DWORD 	WINAPI SignHash(
			GOST34311_HASH				pHash,
			PDSTU4145_PARAMETER_EC	 	pParameterEC,
			PDSTU4145_PARAMETER_P	 	pParameterP,
			DSTU4145_KEY_D 				pKeyD,
			DSTU4145_SIGNATURE 			pSignature);

	virtual DWORD 	WINAPI VerifySignature(
			GOST34311_HASH 				pHash,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pSignatureKeyQ,
			DSTU4145_SIGNATURE 			pSignature);

	virtual DWORD 	WINAPI ProtectSharedData(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_D 				pKeyDa,
			DSTU4145_KEY_Q 				pKeyQb,
			ECDH_EXTENDED_DATA 			pData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_MAC 				pMAC);

	virtual DWORD 	WINAPI UnprotectSharedData(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_D 				pKeyDa,
			DSTU4145_KEY_Q 				pKeyQb,
			ECDH_EXTENDED_DATA 			pData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_MAC 				pMAC);

	virtual DWORD 	WINAPI CheckDSParameters(
			PDSTU4145_PARAMETER_EC	 	pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP);

	virtual DWORD 	WINAPI CheckKEPParameters(
			PDSTU4145_PARAMETER_EC	 	pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP);

	virtual DWORD 	WINAPI GenerateDSKeys(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_D 				pKeyD,
			DSTU4145_KEY_Q 				pKeyQ);

	virtual DWORD 	WINAPI GenerateKEPKeys(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_D 				pKeyD,
			DSTU4145_KEY_Q 				pKeyQ);

	virtual DWORD 	WINAPI CheckDSKeys(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_D 				pKeyD,
			DSTU4145_KEY_Q 				pKeyQ);

	virtual DWORD 	WINAPI CheckKEPKeys(
			PDSTU4145_PARAMETER_EC	 	pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_D 				pKeyD,
			DSTU4145_KEY_Q 				pKeyQ);

	virtual DWORD	WINAPI HashKEPKey(
			DSTU4145_KEY_D				pKeyD,
			DWORD 						dwBits,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			GOST34311_HASH 				pHash);

	virtual DWORD 	WINAPI SetSBoxes(
			GOST28147_COMPRESSED_SBOX	pEncryptionSBox,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST28147_COMPRESSED_SBOX	pECDHSBox,
			GOST28147_COMPRESSED_SBOX	pPRNGSBox);

#ifdef CSP_GOST28147_CFB
	virtual DWORD 	WINAPI EncryptDataFeedback(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV);

	virtual DWORD 	WINAPI DecryptDataFeedback(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV);

	virtual DWORD 	WINAPI InitializeEncryptDataFeedback(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV,
			BOOL 						blGenerateKeyAndIV,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI ContinueEncryptDataFeedback(
			PBYTE 						pbData,
			DWORD 						dwData,
			PGOST28147_STATE 			*ppGOST28147State);
	
	virtual DWORD 	WINAPI FinalizeEncryptDataFeedback(
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD 	WINAPI InitializeDecryptDataFeedback(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI ContinueDecryptDataFeedback(
			PBYTE 						pbData,
			DWORD 						dwData,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD 	WINAPI FinalizeDecryptDataFeedback(
			PGOST28147_STATE 			*ppGOST28147State);
#endif // CSP_GOST28147_CFB

#ifdef CSP_ECDH_UA
	virtual DWORD	WINAPI WrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST34311_HASH				pInitialHash,
			GOST28147_COMPRESSED_SBOX	pWrapSBox,
			GOST28147_KEY				pKey,
			GOST28147_WRAPED_KEY		pWrappedKey);

	virtual DWORD	WINAPI UnwrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST34311_HASH				pInitialHash,
			GOST28147_COMPRESSED_SBOX	pWrapSBox,
			GOST28147_WRAPED_KEY		pWrappedKey,
			GOST28147_KEY				pKey);
#endif // CSP_ECDH_UA

	virtual DWORD	WINAPI EncryptDataFeedbackEx(
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV				pIV,
			BOOL						blGenerateKey,
			BOOL						blGenerateIV);

	virtual DWORD	WINAPI InitializeEncryptDataFeedbackEx(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV,
			BOOL						blGenerateKey,
			BOOL						blGenerateIV,
			PGOST28147_STATE 			*ppGOST28147State);

	virtual DWORD	WINAPI DeriveProtectionKey(
			PBYTE						pbPassword,
			DWORD						dwPassword,
			PBYTE						pbSalt,
			DWORD						dwSalt,
			BOOL						blGenerateSalt,
			DWORD						dwCounter,
			GOST28147_COMPRESSED_SBOX	pPRFSBox,
			GOST34311_HASH				pPRFInitHash,
			GOST28147_KEY				pDerivedKey);

	virtual DWORD	WINAPI DeriveMACKey(
			PBYTE						pbPassword,
			DWORD						dwPassword,
			PBYTE						pbSalt,
			DWORD						dwSalt,
			BOOL						blGenerateSalt,
			DWORD						dwCounter,
			GOST28147_COMPRESSED_SBOX	pPRFSBox,
			GOST34311_HASH				pPRFInitHash,
			GOST28147_KEY				pDerivedKey);

	virtual DWORD	WINAPI GetDataHMAC(
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_COMPRESSED_SBOX 	pSBox,
			GOST34311_HASH 				pInitialHash,
			GOST28147_KEY				pKey,
			GOST34311_HASH				pHash);

	virtual DWORD	WINAPI CheckDataHMAC(
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST34311_HASH				pInitialHash,
			GOST28147_KEY				pKey,
			GOST34311_HASH				pHash);

	virtual DWORD	WINAPI RecoverDSPublicKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI RecoverKEPPublicKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI SetParamsPassword(
			PCSTR						pszParamsPassword);

	virtual PCSTR	WINAPI GetParamsPassword();

	virtual DWORD	WINAPI RestoreParameters(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			BOOL						bWithCheck);

	virtual DWORD	WINAPI GenerateRNSequenceCtx(
			PCSP_CTX					pContext,
			PBYTE						pbSequence,
			DWORD						dwSequence);

	virtual DWORD	WINAPI GeneratePRNGParametersCtx(
			PCSP_CTX					pContext,
			GOST28147_BLOCK				pSeed,
			GOST28147_KEY				pKey,
			GOST28147_BLOCK				pWorkS);

	virtual DWORD	WINAPI InitializePRNGCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_BLOCK				pSeed,
			GOST28147_KEY				pKey);

	virtual DWORD	WINAPI ReinitializePRNGCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_BLOCK 			pSeed,
			GOST28147_KEY				pKey);

	virtual DWORD	WINAPI InitializeHRNGCtx(
			PCSP_CTX					pContext);

	virtual DWORD	WINAPI GeneratePRNSequenceCtx(
			PCSP_CTX					pContext,
			PBYTE						pbSequence,
			DWORD						dwSequence);

	virtual DWORD	WINAPI GenerateRPRNSequenceCtx(
			PCSP_CTX					pContext,
			PBYTE						pbSequence,
			DWORD						dwSequence);

	virtual DWORD	WINAPI EncryptDataCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV);

	virtual DWORD	WINAPI SignHashCtx(
			PCSP_CTX					pContext,
			GOST34311_HASH				pHash,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_SIGNATURE			pSignature);

	virtual DWORD	WINAPI VerifySignatureCtx(
			PCSP_CTX					pContext,
			GOST34311_HASH				pHash,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQ,
			DSTU4145_SIGNATURE			pSignature);

	virtual DWORD	WINAPI ProtectSharedDataCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			ECDH_EXTENDED_DATA			pData,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST34311_HASH				pInitialHash,
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_MAC				pMAC);

	virtual DWORD	WINAPI UnprotectSharedDataCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			ECDH_EXTENDED_DATA			pData,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST34311_HASH				pInitialHash,
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_MAC				pMAC);

	virtual DWORD	WINAPI GenerateDSKeysCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI GenerateKEPKeysCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI CheckDSKeysCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI CheckKEPKeysCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI InitializeEncryptDataCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV,
			BOOL						blGenerateKeyAndIV,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI ContinueEncryptDataCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI ContinueEncryptDataByOffsetCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			DWORDLONG					dwlDataOffset,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI FinalizeEncryptDataCtx(
			PCSP_CTX					pContext,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI InitializeDecryptDataCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI ContinueDecryptDataCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI ContinueDecryptDataByOffsetCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			DWORDLONG					dwlDataOffset,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI FinalizeDecryptDataCtx(
			PCSP_CTX					pContext,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI HashKEPKeyCtx(
			PCSP_CTX					pContext,
			DSTU4145_KEY_D				pKeyD,
			DWORD						dwBits,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST34311_HASH				pInitialHash,
			GOST34311_HASH				pHash);

	virtual DWORD	WINAPI SetSBoxesCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pEncryptionSBox,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST28147_COMPRESSED_SBOX	pECDHSBox,
			GOST28147_COMPRESSED_SBOX	pPRNGSBox);

	virtual DWORD	WINAPI EncryptDataFeedbackCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV);

	virtual DWORD	WINAPI InitializeEncryptDataFeedbackCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV,
			BOOL						blGenerateKeyAndIV,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI WrapSharedKeyCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST34311_HASH				pInitialHash,
			GOST28147_COMPRESSED_SBOX	pWrapSBox,
			GOST28147_KEY				pKey,
			GOST28147_WRAPED_KEY		pWrappedKey);

	virtual DWORD	WINAPI UnwrapSharedKeyCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST34311_HASH				pInitialHash,
			GOST28147_COMPRESSED_SBOX	pWrapSBox,
			GOST28147_WRAPED_KEY		pWrappedKey,
			GOST28147_KEY				pKey);

	virtual DWORD	WINAPI EncryptDataFeedbackExCtx(
			PCSP_CTX					pContext,
			PBYTE						pbData,
			DWORD						dwData,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV,
			BOOL						blGenerateKey,
			BOOL						blGenerateIV);

	virtual DWORD	WINAPI InitializeEncryptDataFeedbackExCtx(
			PCSP_CTX					pContext,
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY				pKey,
			GOST28147_IV				pIV,
			BOOL						blGenerateKey,
			BOOL						blGenerateIV,
			PGOST28147_STATE			*ppGOST28147State);

	virtual DWORD	WINAPI DeriveProtectionKeyCtx(
			PCSP_CTX					pContext,
			PBYTE						pbPassword,
			DWORD						dwPassword,
			PBYTE						pbSalt,
			DWORD						dwSalt,
			BOOL						blGenerateSalt,
			DWORD						dwCounter,
			GOST28147_COMPRESSED_SBOX	pPRFSBox,
			GOST34311_HASH				pPRFInitHash,
			GOST28147_KEY				pDerivedKey);

	virtual DWORD	WINAPI DeriveMACKeyCtx(
			PCSP_CTX					pContext,
			PBYTE						pbPassword,
			DWORD						dwPassword,
			PBYTE						pbSalt,
			DWORD						dwSalt,
			BOOL						blGenerateSalt,
			DWORD						dwCounter,
			GOST28147_COMPRESSED_SBOX	pPRFSBox,
			GOST34311_HASH				pPRFInitHash,
			GOST28147_KEY				pDerivedKey);

	virtual DWORD	WINAPI RecoverDSPublicKeyCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI RecoverKEPPublicKeyCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_KEY_Q				pKeyQ);

	virtual DWORD	WINAPI SetHRNG(
			ICSPHardwareRNG				*pHardwareRNG);

	virtual DWORD	WINAPI CoupleDSMakeCommonPublicKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQ1,
			DSTU4145_KEY_Q				pKeyQ2,
			DSTU4145_KEY_Q				pCommonKeyQ);

	virtual DWORD	WINAPI CoupleDSPart1Step1(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_NUMBER				pKeyK1,
			DSTU4145_NUMBER				pComponentR1);

	virtual DWORD	WINAPI CoupleDSPart1Step1Ctx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_NUMBER				pKeyK1,
			DSTU4145_NUMBER				pComponentR1);

	virtual DWORD	WINAPI CoupleDSPart2Step1(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			GOST34311_HASH				pHash,
			DSTU4145_NUMBER				pComponentR1,
			DSTU4145_NUMBER				pKeyK2,
			DSTU4145_NUMBER				pCommonComponentR);

	virtual DWORD	WINAPI CoupleDSPart2Step1Ctx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			GOST34311_HASH				pHash,
			DSTU4145_NUMBER				pComponentR1,
			DSTU4145_NUMBER				pKeyK2,
			DSTU4145_NUMBER				pCommonComponentR);

	virtual DWORD	WINAPI CoupleDSPart1Step2(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD1,
			DSTU4145_NUMBER				pKeyK1,
			DSTU4145_NUMBER				pCommonComponentR,
			DSTU4145_NUMBER				pComponentS1);

	virtual DWORD	WINAPI CoupleDSPart1Step2Ctx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD1,
			DSTU4145_NUMBER				pKeyK1,
			DSTU4145_NUMBER				pCommonComponentR,
			DSTU4145_NUMBER				pComponentS1);

	virtual DWORD	WINAPI CoupleDSPart2Step2(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD2,
			DSTU4145_NUMBER				pKeyK2,
			DSTU4145_NUMBER				pCommonComponentR,
			DSTU4145_NUMBER				pComponentS1,
			DSTU4145_SIGNATURE			pSignature);

	virtual DWORD	WINAPI CoupleDSPart2Step2Ctx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD2,
			DSTU4145_NUMBER				pKeyK2,
			DSTU4145_NUMBER				pCommonComponentR,
			DSTU4145_NUMBER				pComponentS1,
			DSTU4145_SIGNATURE			pSignature);

	virtual DWORD	WINAPI DSTU7564InitializeState(
			DSTU7564_SBOX				pSBox,
			DWORD						dwHash,
			PDSTU7564_STATE				*ppDSTU7564State);

	virtual DWORD	WINAPI DSTU7564FinalizeState(
			DSTU7564_HASH				pHash,
			PDSTU7564_STATE				*ppDSTU7564State);

	virtual DWORD	WINAPI DSTU7564StateHashData(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU7564_STATE				*ppDSTU7564State);

	virtual DWORD	WINAPI DSTU7564HashData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7564_SBOX				pSBox,
			DWORD						dwHash,
			DSTU7564_HASH				pHash);

	virtual DWORD	WINAPI DSTU7564CheckDataHash(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7564_SBOX				pSBox,
			DWORD						dwHash,
			DSTU7564_HASH				pHash);

	virtual DWORD	WINAPI DSTU7624GenerateParameters(
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwIV);

	virtual DWORD	WINAPI DSTU7624GenerateParametersCtx(
			PCSP_CTX					pContext,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwIV);

	virtual DWORD	WINAPI DSTU7624InitializeState(
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624FinalizeState(
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624ECBEncryptData(
			PBYTE						pbData,
			DWORD						dwDataBlocks,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624ECBDecryptData(
			PBYTE						pbData,
			DWORD						dwDataBlocks,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624CTRStateEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624CTRStateEncryptDataByOffset(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbIV,
			DWORDLONG					dwlDataOffset,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624CTREncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624CTRStateDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624CTRStateDecryptDataByOffset(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbIV,
			DWORDLONG					dwlDataOffset,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624CTRDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624CFBEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock,
			DWORD						dwGammaBits);

	virtual DWORD	WINAPI DSTU7624CFBDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock,
			DWORD						dwGammaBits);

	virtual DWORD	WINAPI DSTU7624GetDataCMAC(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock,
			PBYTE						pbCMAC,
			DWORD						dwCMAC);

	virtual DWORD	WINAPI DSTU7624CheckDataCMAC(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbCMAC,
			DWORD						dwCMAC,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624CBCEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DWORD						dwOutputData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624CBCDecryptData(
			PBYTE						pbData,
			PDWORD						pdwData,
			BOOL						bPadding,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624OFBStateEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624OFBEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624OFBStateDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624OFBDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624GCMEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbPublicData,
			DWORD						dwPublicData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock,
			PBYTE						pbGMAC,
			DWORD						dwGMAC);

	virtual DWORD	WINAPI DSTU7624GCMDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbPublicData,
			DWORD						dwPublicData,
			PBYTE						pbGMAC,
			DWORD						dwGMAC,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624GetDataGMAC(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock,
			PBYTE						pbGMAC,
			DWORD						dwGMAC);

	virtual DWORD	WINAPI DSTU7624CheckDataGMAC(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbGMAC,
			DWORD						dwGMAC,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624CCMEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DWORD						dwOutputData,
			PBYTE						pbPublicData,
			DWORD						dwPublicData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock,
			DWORD						dwDataBytes,
			DWORD						dwMAC);

	virtual DWORD	WINAPI DSTU7624CCMDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbPublicData,
			DWORD						dwPublicData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock,
			DWORD						dwDataBytes,
			DWORD						dwMAC);

	virtual DWORD	WINAPI DSTU7624XTSEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624XTSDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624KWEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DWORD						dwOutputData,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DWORD						dwBlock);

	virtual DWORD	WINAPI DSTU7624KWDecryptData(
			PBYTE						pbData,
			PDWORD						pdwData,
			BOOL						bPadding,
			DSTU7624_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PBYTE						pbIV,
			DWORD						dwBlock);

	virtual DWORD	WINAPI SignDSTUHash(
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_SIGNATURE 			pSignature);

	virtual DWORD	WINAPI SignDSTUHashCtx(
			PCSP_CTX					pContext,
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyD,
			DSTU4145_SIGNATURE			pSignature);

	virtual DWORD	WINAPI VerifyDSTUSignature(
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQ,
			DSTU4145_SIGNATURE			pSignature);

	virtual DWORD	WINAPI DSTU8845GenerateParameters(
			PBYTE						pbKey,
			DWORD						dwKey,
			DSTU8845_IV					pIV);

	virtual DWORD	WINAPI DSTU8845GenerateParametersCtx(
			PCSP_CTX					pContext,
			PBYTE						pbKey,
			DWORD						dwKey,
			DSTU8845_IV					pIV);

	virtual DWORD	WINAPI DSTU8845InitializeState(
			DSTU8845_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DSTU8845_IV					pIV,
			PDSTU8845_STATE				*ppDSTU8845State);

	virtual DWORD	WINAPI DSTU8845FinalizeState(
			PDSTU8845_STATE				*ppDSTU8845State);

	virtual DWORD	WINAPI DSTU8845StateEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU8845_STATE				*ppDSTU8845State);

	virtual DWORD	WINAPI DSTU8845StateEncryptDataByOffset(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU8845_IV					pIV,
			DWORDLONG					dwlDataOffset,
			PDSTU8845_STATE				*ppDSTU8845State);

	virtual DWORD	WINAPI DSTU8845EncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU8845_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DSTU8845_IV					pIV);

	virtual DWORD	WINAPI DSTU7564DeriveMACKey(
			PBYTE						pbPassword,
			DWORD						dwPassword,
			PBYTE						pbSalt,
			DWORD						dwSalt,
			DWORD						dwIterationCount,
			DSTU7564_SBOX				pPRFSBox,
			PBYTE						pbDerivedKey,
			DWORD						dwDerivedKey);

	virtual DWORD	WINAPI DSTU7564InitializeHMACState(
			DSTU7564_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			PDSTU7564_HMAC_STATE		*ppDSTU7564HMACState);

	virtual DWORD	WINAPI DSTU7564FinalizeHMACState(
			DSTU7564_HASH				pHMac,
			PDSTU7564_HMAC_STATE		*ppDSTU7564HMACState);

	virtual DWORD	WINAPI DSTU7564StateGetDataHMAC(
			PBYTE						pbData,
			DWORD						dwData,
			PDSTU7564_HMAC_STATE		*ppDSTU7564HMACState);

	virtual DWORD	WINAPI DSTU7564GetDataHMAC(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7564_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DSTU7564_HASH				pHMac);

	virtual DWORD	WINAPI DSTU7564CheckDataHMAC(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU7564_SBOX				pSBox,
			PBYTE						pbKey,
			DWORD						dwKey,
			DSTU7564_HASH				pHMac);

	virtual DWORD	WINAPI DSTU7564HMACDeriveProtectionKey(
			PBYTE						pbPassword,
			DWORD						dwPassword,
			PBYTE						pbSalt,
			DWORD						dwSalt,
			DWORD						dwIterationCount,
			DSTU7564_SBOX				pPRFSBox,
			DWORD						dwHash,
			PBYTE						pbDerivedKey,
			DWORD						dwDerivedKey);

	virtual DWORD	WINAPI DSTU7624DuplicateState(
			PDSTU7624_STATE				*ppDSTU7624State,
			PVOID						pvState,
			PDWORD						pdwState);

	virtual DWORD	WINAPI DSTU7624RestoreState(
			PDSTU7624_STATE				*ppDSTU7624State,
			PVOID						pvState,
			DWORD						dwState);

	virtual DWORD	WINAPI DSTU8845DuplicateState(
			PDSTU8845_STATE				*ppDSTU8845State,
			PVOID						pvState,
			PDWORD						pdwState);

	virtual DWORD	WINAPI DSTU8845RestoreState(
			PDSTU8845_STATE				*ppDSTU8845State,
			PVOID						pvState,
			DWORD						dwState);

	virtual DWORD	WINAPI DSTU7624ProtectData(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbProtectedData,
			DWORD						dwProtectedData,
			DSTU7624_SBOX				pSBox,
			PCHAR						pcPassword,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pIV);

	virtual DWORD	WINAPI DSTU7624UnprotectData(
			PBYTE						pbProtectedData,
			DWORD						dwProtectedData,
			PBYTE						*ppbData,
			PDWORD						pdwData,
			DSTU7624_SBOX				pSBox,
			PCHAR						pcPassword,
			PBYTE						pKey,
			DWORD						dwKey);

	virtual DWORD	WINAPI DSTU7564HashKEPKey(
			DSTU4145_KEY_D				pKeyD,
			DWORD						dwBits,
			DSTU7564_SBOX				pSBox,
			DWORD						dwHash,
			DSTU7564_HASH				pHash);

	virtual DWORD	WINAPI DSTU7564HashKEPKeyCtx(
			PCSP_CTX					pContext,
			DSTU4145_KEY_D				pKeyD,
			DWORD						dwBits,
			DSTU7564_SBOX				pSBox,
			DWORD						dwHash,
			DSTU7564_HASH				pHash);

	virtual DWORD	WINAPI DSTU7624WrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey);

	virtual DWORD	WINAPI DSTU7624UnwrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey,
			PBYTE						pKey,
			DWORD						dwKey);

	virtual DWORD	WINAPI DSTU7624WrapSharedKeyCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey);

	virtual DWORD	WINAPI DSTU7624UnwrapSharedKeyCtx(
			PCSP_CTX					pContext,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_D				pKeyDa,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey,
			PBYTE						pKey,
			DWORD						dwKey);

	virtual DWORD	WINAPI DSTU7624CFBStateEncryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DWORD						dwGammaBits,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI DSTU7624CFBStateDecryptData(
			PBYTE						pbData,
			DWORD						dwData,
			DWORD						dwGammaBits,
			PDSTU7624_STATE				*ppDSTU7624State);

	virtual DWORD	WINAPI InitializeMultiAlgoPRNG(
			DWORD						dwAlgoType,
			PVOID						pvAlgoSBox,
			PVOID						pvAlgoKey,
			PVOID						pvAlgoSeed);

	virtual DWORD	WINAPI GeneratePRNGParameterCtx(
			PCSP_CTX					pContext,
			PBYTE						pbParameter,
			DWORD						dwParameter);

	virtual DWORD	WINAPI InitializeMultiAlgoPRNGCtx(
			PCSP_CTX					pContext,
			DWORD						dwAlgoType,
			PVOID						pvAlgoSBox,
			PVOID						pvAlgoKey,
			PVOID						pvAlgoSeed);

	virtual DWORD	WINAPI ReinitializeMultiAlgoPRNGCtx(
			PCSP_CTX					pContext,
			DWORD						dwAlgoType,
			PVOID						pvAlgoSBox,
			PVOID						pvAlgoKey,
			PVOID						pvAlgoSeed);

	virtual DWORD	WINAPI DSTU7624ProtectDataEx(
			PBYTE						pbData,
			DWORD						dwData,
			PBYTE						pbProtectedData,
			DWORD						dwProtectedData,
			DSTU7624_SBOX				pSBox,
			PCHAR						pcPassword,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pIV,
			DWORD						dwIV,
			DWORD						dwMac);

	virtual DWORD	WINAPI DSTU7624UnprotectDataEx(
			PBYTE						pbProtectedData,
			DWORD						dwProtectedData,
			PBYTE						*ppbData,
			PDWORD						pdwData,
			DSTU7624_SBOX				pSBox,
			PCHAR						pcPassword,
			PBYTE						pKey,
			DWORD						dwKey);

	virtual DWORD	WINAPI DSTU8845StateEncryptDataByPacketOffset(
			PBYTE						pbData,
			DWORD						dwData,
			DSTU8845_IV					pIV,
			DWORDLONG					dwlDataOffset,
			PDSTU8845_STATE				*ppDSTU8845State);

	virtual DWORD	WINAPI CheckParametersD(
			PBYTE						pbParameters,
			DWORD						dwParameters);

	virtual DWORD	WINAPI GenerateKeysD(
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ);

	virtual DWORD	WINAPI GenerateKeysDCtx(
			PCSP_CTX					pContext,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ);

	virtual DWORD	WINAPI CheckKeysD(
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ);

	virtual DWORD	WINAPI CheckKeysDCtx(
			PCSP_CTX					pContext,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ);

	virtual DWORD	WINAPI RecoverPublicKeyD(
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ);

	virtual DWORD	WINAPI RecoverPublicKeyDCtx(
			PCSP_CTX					pContext,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ);

	virtual DWORD	WINAPI RestoreParametersD(
			PBYTE						pbParameters,
			DWORD						dwParameters,
			BOOL						bWithCheck);

	virtual DWORD	WINAPI SignDSTU7564HashD(
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbSignature,
			DWORD						dwSignature);

	virtual DWORD	WINAPI SignDSTU7564HashDCtx(
			PCSP_CTX					pContext,
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyD,
			DWORD						dwKeyD,
			PBYTE						pbSignature,
			DWORD						dwSignature);

	virtual DWORD	WINAPI VerifyDSTU7564HashSignatureD(
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyQ,
			DWORD						dwKeyQ,
			PBYTE						pbSignature,
			DWORD						dwSignature);

	virtual DWORD	WINAPI DSTU7624WrapSharedKeyD(
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyDa,
			DWORD						dwKeyDa,
			PBYTE						pbKeyQb,
			DWORD						dwKeyQb,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey);

	virtual DWORD	WINAPI DSTU7624WrapSharedKeyDCtx(
			PCSP_CTX					pContext,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyDa,
			DWORD						dwKeyDa,
			PBYTE						pbKeyQb,
			DWORD						dwKeyQb,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey);

	virtual DWORD	WINAPI DSTU7624UnwrapSharedKeyD(
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyDa,
			DWORD						dwKeyDa,
			PBYTE						pbKeyQb,
			DWORD						dwKeyQb,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey,
			PBYTE						pKey,
			DWORD						dwKey);

	virtual DWORD	WINAPI DSTU7624UnwrapSharedKeyDCtx(
			PCSP_CTX					pContext,
			PBYTE						pbParameters,
			DWORD						dwParameters,
			PBYTE						pbKeyDa,
			DWORD						dwKeyDa,
			PBYTE						pbKeyQb,
			DWORD						dwKeyQb,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey,
			PBYTE						pKey,
			DWORD						dwKey);
};

//======================================================================================================================

extern BOOL				g_bNoCSPSelfTests;

//======================================================================================================================

#endif // CSP_H
