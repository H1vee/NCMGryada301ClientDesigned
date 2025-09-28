#ifndef CSPI_H
#define CSPI_H

//==============================================================================

#include "CSPIBase.h"
#include "CSPIParameters.h"

//------------------------------------------------------------------------------

#include "ICSPI.h"

//==============================================================================

#define CSPI_CHECK_COMPATIBLE(pCSPI, dwCompatibleLevel, bCompatible)\
	{															\
		RSA_PARAMETERS		Parameters;							\
		Parameters.dwHash = 0;									\
		Parameters.dwBits = dwCompatibleLevel;					\
		bCompatible = (pCSPI->RSAGenerateKeys(					\
			&Parameters, NULL, NULL) == CSPI_NO_ERROR);			\
	}															\

#define CSPI_CHECK_COMPATIBLE_CTX(pCSPI, pContext,				\
	dwCompatibleLevel, bCompatible)								\
	{															\
		RSA_PARAMETERS		Parameters;							\
		Parameters.dwHash = 0;									\
		Parameters.dwBits = dwCompatibleLevel;					\
		bCompatible = (pCSPI->RSAGenerateKeysCtx(				\
			pContext, &Parameters, NULL,						\
			NULL) == CSPI_NO_ERROR);							\
	}															\

#define CSPI_COMPATIBLE_LEVEL_PKCS12						1
#define CSPI_COMPATIBLE_LEVEL_RECOVER_PUBLIC_KEY			2
#define CSPI_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY	3
#define CSPI_COMPATIBLE_LEVEL_HARDWARE_RSA_DECRYPT_DATA		4
#define CSPI_COMPATIBLE_LEVEL_ITERATIVE_I_ENCRYPTION		5
#define CSPI_COMPATIBLE_LEVEL_CTX							6
#define CSPI_COMPATIBLE_LEVEL_HARDWARE_RSA_PSS_SIGN			7
#define CSPI_COMPATIBLE_LEVEL_RSA_PSS_SIGN					8
#define CSPI_COMPATIBLE_LEVEL_AES_GCM						9
#define CSPI_COMPATIBLE_LEVEL_HARDWARE_ECDSA_COUPLE			10
#define CSPI_COMPATIBLE_LEVEL_ECDSA_COUPLE					11
#define CSPI_COMPATIBLE_LEVEL_PBKDF2_SHA_DERIVE_KEY			12

//------------------------------------------------------------------------------

#define CSPI_GET_ALIGNED_DATA_SIZE(DataSize, BlockSize)\
	(((DataSize) / (BlockSize) + 1) * (BlockSize))

#define CSPI_GET_PBE_DATA_SIZE(DataSize, BlockSize)\
	CSPI_GET_ALIGNED_DATA_SIZE(DataSize, BlockSize)

//==============================================================================

#if defined(EM_SDK) || defined(OS_IOS)
#define CSPI_DISABLE_SELF_TESTS
#endif // EM_SDK || OS_IOS

//======================================================================================================================

typedef struct
{
	ICSPIHardwareRNG					*pHardwareRNG;
	ICSPIHardware 						*pHardwareCSP;

	PDSTU4145_PSEUDO_RNG_STATE			pPRNGState;
} CSPI_CTX, *PCSPI_CTX;

#define CSPI_CTX_INITIALIZE(Context)							\
	(Context).pHardwareRNG =									\
		(m_dwState & CSPI_STATE_HRNG_INITIALIZED) ?				\
			m_pHardwareRNG : NULL;								\
	(Context).pHardwareCSP =									\
		(m_dwState & CSPI_STATE_HARDWARE_CSP_INITIALIZED) ?		\
			m_pHardwareCSP : NULL;								\
	(Context).pPRNGState = pPRNGState;							\

//==============================================================================

class CSPI
{
public:
	CSPI();
	~CSPI();

public:
	CSPIBase						Base;
	CSPIParameters					Parameters;

	PDSTU4145_PSEUDO_RNG_STATE		pPRNGState;

private:
	ICSPIHardwareRNG				*m_pHardwareRNG;
	ICSPIHardware 					*m_pHardwareCSP;

	DWORD							m_dwState;

	PCSPI_BASE_FUNCTIONS_EX			m_pBaseEx;

	CRITICAL_SECTION				m_CriticalSection;

public:
	virtual DWORD 	WINAPI Initialize();

	virtual DWORD 	WINAPI InitializePRNG(
		GOST28147_COMPRESSED_SBOX	pSBox,
		GOST28147_BLOCK 			pSeed,
		GOST28147_KEY				pKey);

	virtual DWORD 	WINAPI InitializeHRNG(
		ICSPIHardwareRNG			*pHardwareRNG);

	virtual DWORD 	WINAPI GenerateRNSequence(
		PBYTE 						pbSequence,
		DWORD 						dwSequence);

	virtual DWORD 	WINAPI GeneratePRNSequence(
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

	virtual DWORD 	WINAPI GOST34311HashData(
		PBYTE 						pbData,
		DWORD 						dwData,
		GOST28147_COMPRESSED_SBOX 	pSBox,
		GOST34311_HASH 				pInitialHash,
		GOST34311_HASH 				pHash);

	virtual DWORD 	WINAPI GOST34311CheckDataHash(
		PBYTE 						pbData,
		DWORD 						dwData,
		GOST28147_COMPRESSED_SBOX 	pSBox,
		GOST34311_HASH 				pInitialHash,
		GOST34311_HASH 				pHash);

	virtual VOID 	WINAPI SetHardwareCSPI(
		ICSPIHardware				*pHardwareCSP);

	virtual DWORD 	WINAPI SHAHashData(
		PBYTE 						pbData,
		DWORD 						dwData,
		DWORD 						dwHash,
		SHA_HASH					pHash);

	virtual DWORD 	WINAPI RSASignHash(
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		RSA_SIGNATURE 				pSignature);

	virtual DWORD 	WINAPI RSAVerifySignature(
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey,
		RSA_SIGNATURE 				pSignature);

	virtual DWORD	WINAPI RSAEncryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey,
		RSA_BLOCK					pEncryptedData);

	virtual DWORD 	WINAPI RSADecryptData(
		PBYTE						pbData,
		PDWORD						pdwData,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		BOOL						blUnpadData);

	virtual DWORD 	WINAPI RSACheckParameters(
		PRSA_PARAMETERS				pParameters);

	virtual DWORD 	WINAPI RSAGenerateKeys(
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		PRSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD 	WINAPI RSACheckKeys(
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		PRSA_PUBLIC_KEY				pPublicKey);
	
	virtual DWORD WINAPI DSASignHash(
		DWORD						dwHash,
		SHA_HASH					pHash,
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_SIGNATURE 				pSignature);

	virtual DWORD WINAPI DSAVerifySignature(
		DWORD						dwHash,
		SHA_HASH					pHash,
		PDSA_PARAMETERS				pParameters,
		PDSA_PUBLIC_KEY				pPublicKey,
		PDSA_SIGNATURE 				pSignature);

	virtual DWORD WINAPI DSACheckParameters(
		PDSA_PARAMETERS				pParameters);

	virtual DWORD WINAPI DSAGenerateKeys(
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD WINAPI DSACheckKeys(
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD WINAPI ECDSASignHash(
		DWORD						dwHash,
		SHA_HASH					pHash,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D 				pPrivateKey,
		PECDSA_SIGNATURE 			pSignature);

	virtual DWORD WINAPI ECDSAVerifySignature(
		DWORD						dwHash,
		SHA_HASH					pHash,
		PECDSA_PARAMETERS	 		pParameters,
		ECDSA_KEY_Q 				pPublicKey,
		PECDSA_SIGNATURE 			pSignature);

	virtual DWORD WINAPI ECDSACheckParameters(
		PECDSA_PARAMETERS			pParameters);

	virtual DWORD WINAPI ECDSAGenerateKeys(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pPublicKey);

	virtual DWORD WINAPI ReservedFunction1();

	virtual DWORD WINAPI ReservedFunction2();

	virtual DWORD WINAPI ReservedFunction3();

	virtual DWORD WINAPI ReservedFunction4();

	virtual DWORD WINAPI ECDSACheckKeys(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pPublicKey);

	virtual DWORD WINAPI ECDHCalculateSharedSecret(
		PECDSA_PARAMETERS 			pParameters,
		ECDSA_KEY_D 				pPrivateKey,
		ECDSA_KEY_Q 				pRecipientPublicKey,
		ECDSA_NUMBER				pSharedSecret);

	virtual DWORD WINAPI DHCalculateSharedSecret(
		PDSA_PARAMETERS 			pParameters,
		DSA_NUMBER 					pPrivateKey,
		DSA_NUMBER 					pRecipientPublicKey,
		DSA_NUMBER					pSharedSecret);

	virtual DWORD WINAPI TDEAEncryptData(
		PBYTE 						pbData,
		DWORD 						dwData,
		PTDEA_KEYS 					pKeys,
		DES_IV 						pIV,
		DES_BLOCK 					pDataAligment,
		PDWORD 						pdwDataAligment);

	virtual DWORD WINAPI TDEADecryptData(
		PBYTE 						pbData,
		DWORD 						dwData,
		PTDEA_KEYS 					pKeys,
		DES_IV 						pIV,
		DES_BLOCK 					pDataAligment,
		DWORD 						dwDataAligment);

	virtual DWORD WINAPI AESEncryptData(
		PBYTE 						pbData,
		DWORD 						dwData,
		PBYTE 						pKey,
		DWORD 						dwKey,
		AES_IV 						pIV,
		AES_BLOCK 					pDataAligment,
		PDWORD 						pdwDataAligment);

	virtual DWORD WINAPI AESDecryptData(
		PBYTE						pbData,
		DWORD 						dwData,
		PBYTE 						pKey,
		DWORD 						dwKey,
		AES_IV 						pIV,
		AES_BLOCK 					pDataAligment,
		DWORD 						dwDataAligment);

	virtual DWORD 	WINAPI AESGetDataMAC(
		PBYTE 						pbData,
		DWORD						dwBitDataLength,
		PBYTE						pKey,
		DWORD						dwKey,
		AES_BLOCK					pRandom,
		DWORD						dwBitsRandomLength, 
		AES_MAC 					pMAC);

	virtual DWORD 	WINAPI AESCheckDataMAC(
		PBYTE 						pbData,
		DWORD						dwBitDataLength,
		PBYTE						pKey,
		DWORD						dwKey,
		AES_BLOCK					pRandom,
		DWORD						dwBitsRandomLength, 
		AES_MAC 					pMAC);

	virtual DWORD 	WINAPI TDEAGetDataMAC(
		PBYTE 						pbData,
		DWORD						dwBitDataLength,
		PTDEA_KEYS 					pKeys,
		DES_IV						pIV,
		DES_BLOCK 					pMAC);

	virtual DWORD 	WINAPI TDEACheckDataMAC(
		PBYTE 						pbData,
		DWORD						dwBitDataLength,
		PTDEA_KEYS 					pKeys,
		DES_IV						pIV,
		DES_BLOCK 					pMAC);


	virtual DWORD 	WINAPI InitializeSHAHashData(
		DWORD						dwHash,
		PSHA_STATE					*ppSHAState);

	virtual DWORD 	WINAPI ContinueSHAHashData(
		PBYTE						pbData,
		DWORD						dwData,
		PSHA_STATE					*ppSHAState);

	virtual DWORD 	WINAPI FinalizeSHAHashData(
		SHA_HASH					pHash,
		PSHA_STATE					*ppSHAState);


	virtual DWORD 	WINAPI TDESEncryptData(
		PBYTE 						pbData,
		DWORD 						dwData,
		PTDEA_KEYS 					pKeys,
		DES_IV 						pIV,
		BOOL						blGenerateKeyAndIV,
		DES_BLOCK 					pDataAligment,
		PDWORD 						pdwDataAligment);

	virtual DWORD 	WINAPI PBESHA1RC2Encrypt(
		PBYTE						pbData,
		PDWORD						pdwData,
		DWORD						dwDataMaxSize,
		DWORD						dwKeySize,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter);

	virtual DWORD 	WINAPI PBESHA1RC2Decrypt(
		PBYTE						pbData,
		PDWORD						pdwData,
		DWORD						dwKeySize,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		DWORD						dwCounter);

	virtual DWORD 	WINAPI PBESHA1TDESEncrypt(
		PBYTE						pbData,
		PDWORD						pdwData,
		DWORD						dwDataMaxSize,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter);

	virtual DWORD 	WINAPI PBESHA1TDESDecrypt(
		PBYTE						pbData,
		PDWORD						pdwData,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		DWORD						dwCounter);

	virtual DWORD 	WINAPI SHA1CreateHMAC(
		PBYTE						pbData,
		DWORD						dwData,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter,
		SHA1_HMAC_HASH				pHash);

	virtual DWORD 	WINAPI SHA1CheckHMAC(
		PBYTE						pbData,
		DWORD						dwData,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		DWORD						dwCounter,
		SHA1_HMAC_HASH				pHash);


	virtual DWORD	WINAPI RSARecoverPublicKey(
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		PRSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD WINAPI DSARecoverPublicKey(
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD WINAPI ECDSARecoverPublicKey(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pPublicKey);


	virtual DWORD	WINAPI PBKDF2IDeriveKey(
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter,
		PTDEA_KEYS					pDerivedKey);

public:
	virtual VOID	WINAPI SetParityBits(
		PDES_KEY					pKey);

	virtual DWORD	WINAPI InitializeTDESEncryptData(
		PTDEA_KEYS					pKey,
		DES_IV						pIV,
		BOOL						blGenerateKeyAndIV,
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD	WINAPI ContinueTDESEncryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD	WINAPI FinalizeTDESEncryptData(
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD 	WINAPI InitializeTDESDecryptData(
		PTDEA_KEYS					pKey,
		DES_IV						pIV,
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD 	WINAPI ContinueTDESDecryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD 	WINAPI FinalizeTDESDecryptData(
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD	WINAPI InitializeAESEncryptData(
		PAES_CIPHER_KEY				pKey,
		DWORD						dwKey,
		AES_IV						pIV,
		BOOL						blGenerateKeyAndIV,
		PAES_STATE					*ppAESState);

	virtual DWORD	WINAPI ContinueAESEncryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PAES_STATE					*ppAESState);

	virtual DWORD	WINAPI FinalizeAESEncryptData(
		PAES_STATE					*ppAESState);

	virtual DWORD 	WINAPI InitializeAESDecryptData(
		PAES_CIPHER_KEY				pKey,
		DWORD						dwKey,
		AES_IV						pIV,
		PAES_STATE					*ppAESState);

	virtual DWORD 	WINAPI ContinueAESDecryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PAES_STATE					*ppAESState);

	virtual DWORD 	WINAPI FinalizeAESDecryptData(
		PAES_STATE					*ppAESState);


public:
	virtual DWORD	WINAPI SetHRNG(
		ICSPIHardwareRNG			*pHardwareRNG);

	virtual DWORD	WINAPI GenerateRNSequenceCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbSequence,
		DWORD						dwSequence);

	virtual DWORD	WINAPI GeneratePRNGParametersCtx(
		PCSPI_CTX					pContext,
		GOST28147_BLOCK				pSeed,
		GOST28147_KEY				pKey,
		GOST28147_BLOCK				pWorkS);

	virtual DWORD	WINAPI InitializePRNGCtx(
		PCSPI_CTX					pContext,
		GOST28147_COMPRESSED_SBOX	pSBox,
		GOST28147_BLOCK				pSeed,
		GOST28147_KEY				pKey);

	virtual DWORD	WINAPI ReinitializePRNGCtx(
		PCSPI_CTX					pContext,
		GOST28147_COMPRESSED_SBOX	pSBox,
		GOST28147_BLOCK 			pSeed,
		GOST28147_KEY				pKey);

	virtual DWORD	WINAPI InitializeHRNGCtx(
		PCSPI_CTX					pContext);

	virtual DWORD	WINAPI GeneratePRNSequenceCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbSequence,
		DWORD						dwSequence);

	virtual DWORD	WINAPI GenerateRPRNSequenceCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbSequence,
		DWORD						dwSequence);

	virtual DWORD	WINAPI RSASignHashCtx(
		PCSPI_CTX					pContext,
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		RSA_SIGNATURE 				pSignature);

	virtual DWORD	WINAPI RSAEncryptDataCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwData,
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey,
		RSA_BLOCK					pEncryptedData);

	virtual DWORD	WINAPI RSADecryptDataCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		PDWORD						pdwData,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		BOOL						blUnpadData);

	virtual DWORD	WINAPI RSAGenerateKeysCtx(
		PCSPI_CTX					pContext,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		PRSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD	WINAPI RSACheckKeysCtx(
		PCSPI_CTX					pContext,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		PRSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD	WINAPI DSASignHashCtx(
		PCSPI_CTX					pContext,
		DWORD						dwHash,
		SHA_HASH					pHash,
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_SIGNATURE				pSignature);

	virtual DWORD	WINAPI ECDSASignHashCtx(
		PCSPI_CTX					pContext,
		DWORD						dwHash,
		SHA_HASH					pHash,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		PECDSA_SIGNATURE			pSignature);

	virtual DWORD	WINAPI ECDHCalculateSharedSecretCtx(
		PCSPI_CTX					pContext,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pRecipientPublicKey,
		ECDSA_NUMBER				pSharedSecret);

	virtual DWORD	WINAPI DHCalculateSharedSecretCtx(
		PCSPI_CTX					pContext,
		PDSA_PARAMETERS				pParameters,
		DSA_NUMBER					pPrivateKey,
		DSA_NUMBER					pRecipientPublicKey,
		DSA_NUMBER					pSharedSecret);

	virtual DWORD	WINAPI DSAGenerateKeysCtx(
		PCSPI_CTX					pContext,
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD	WINAPI DSACheckKeysCtx(
		PCSPI_CTX					pContext,
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD	WINAPI ECDSAGenerateKeysCtx(
		PCSPI_CTX					pContext,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pPublicKey);

	virtual DWORD	WINAPI ECDSACheckKeysCtx(
		PCSPI_CTX					pContext,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pPublicKey);

	virtual DWORD	WINAPI TDEAEncryptDataCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwData,
		PTDEA_KEYS					pKeys,
		DES_IV						pIV,
		DES_BLOCK					pDataAligment,
		PDWORD						pdwDataAligment);

	virtual DWORD	WINAPI AESEncryptDataCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwData,
		PBYTE						pKey,
		DWORD						dwKey,
		AES_IV						pIV,
		AES_BLOCK					pDataAligment,
		PDWORD						pdwDataAligment);

	virtual DWORD	WINAPI AESGetDataMACCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwBitDataLength,
		PBYTE						pKey,
		DWORD						dwKey,
		AES_BLOCK					pRandom,
		DWORD						dwBitsRandomLength,
		AES_MAC						pMAC);

	virtual DWORD	WINAPI TDEAGetDataMACCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwBitDataLength,
		PTDEA_KEYS					pKeys,
		DES_IV						pIV,
		DES_BLOCK					pMAC);

	virtual DWORD	WINAPI TDESEncryptDataCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwData,
		PTDEA_KEYS					pKeys,
		DES_IV						pIV,
		BOOL						blGenerateKeyAndIV,
		DES_BLOCK					pDataAligment,
		PDWORD						pdwDataAligment);

	virtual DWORD	WINAPI PBESHA1RC2EncryptCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		PDWORD						pdwData,
		DWORD						dwDataMaxSize,
		DWORD						dwKeySize,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter);

	virtual DWORD	WINAPI PBESHA1TDESEncryptCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		PDWORD						pdwData,
		DWORD						dwDataMaxSize,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter);

	virtual DWORD	WINAPI SHA1CreateHMACCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbData,
		DWORD						dwData,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter,
		SHA1_HMAC_HASH				pHash);

	virtual DWORD	WINAPI RSARecoverPublicKeyCtx(
		PCSPI_CTX					pContext,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		PRSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD	WINAPI DSARecoverPublicKeyCtx(
		PCSPI_CTX					pContext,
		PDSA_PARAMETERS				pParameters,
		PDSA_PRIVATE_KEY			pPrivateKey,
		PDSA_PUBLIC_KEY				pPublicKey);

	virtual DWORD	WINAPI ECDSARecoverPublicKeyCtx(
		PCSPI_CTX					pContext,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey,
		ECDSA_KEY_Q					pPublicKey);

	virtual DWORD	WINAPI PBKDF2IDeriveKeyCtx(
		PCSPI_CTX					pContext,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter,
		PTDEA_KEYS					pDerivedKey);

	virtual DWORD	WINAPI InitializeTDESEncryptDataCtx(
		PCSPI_CTX					pContext,
		PTDEA_KEYS					pKeys,
		DES_IV						pIV,
		BOOL						blGenerateKeyAndIV,
		PTDEA_STATE					*ppTDEAState);

	virtual DWORD	WINAPI InitializeAESEncryptDataCtx(
		PCSPI_CTX					pContext,
		PAES_CIPHER_KEY				pKey,
		DWORD						dwKey,
		AES_IV						pIV,
		BOOL						blGenerateKeyAndIV,
		PAES_STATE					*ppAESState);

public:
	virtual DWORD	WINAPI SHA1CreateHMACWithKey(
		PBYTE						pbData,
		DWORD						dwData,
		SHA1_HMAC_KEY				pKey,
		SHA1_HMAC_HASH				pHash);

	virtual DWORD	WINAPI SHA1CheckHMACWithKey(
		PBYTE						pbData,
		DWORD						dwData,
		SHA1_HMAC_KEY				pKey,
		SHA1_HMAC_HASH				pHash);

public:
	virtual DWORD	WINAPI RSAPSSSignHash(
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		RSA_SIGNATURE 				pSignature);

	virtual DWORD	WINAPI RSAPSSVerifySignature(
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey,
		RSA_SIGNATURE 				pSignature);

	virtual DWORD	WINAPI RSAPSSSignHashCtx(
		PCSPI_CTX					pContext,
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		PRSA_PRIVATE_KEY			pPrivateKey,
		RSA_SIGNATURE 				pSignature);

public:
	virtual DWORD	WINAPI InitializeAESGCMEncryptData(
		PAES_CIPHER_KEY				pKey,
		DWORD						dwKey,
		PBYTE						pbIV,
		DWORD						dwIV,
		PBYTE						pbAuthData,
		DWORD						dwAuthData,
		BOOL						blGenerateKey,
		BOOL						blGenerateIV,
		BOOL						blGenerateAuthData,
		PAES_STATE					*ppAESState);

	virtual DWORD	WINAPI InitializeAESGCMEncryptDataCtx(
		PCSPI_CTX					pContext,
		PAES_CIPHER_KEY				pKey,
		DWORD						dwKey,
		PBYTE						pbIV,
		DWORD						dwIV,
		PBYTE						pbAuthData,
		DWORD						dwAuthData,
		BOOL						blGenerateKey,
		BOOL						blGenerateIV,
		BOOL						blGenerateAuthData,
		PAES_STATE					*ppAESState);

	virtual DWORD	WINAPI ContinueAESGCMEncryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PAES_STATE					*ppAESState);

	virtual DWORD	WINAPI FinalizeAESGCMEncryptData(
		AES_MAC						pGCMMAC,
		PAES_STATE					*ppAESState);

	virtual DWORD 	WINAPI InitializeAESGCMDecryptData(
		PAES_CIPHER_KEY				pKey,
		DWORD						dwKey,
		PBYTE						pbIV,
		DWORD						dwIV,
		PBYTE						pbAuthData,
		DWORD						dwAuthData,
		PAES_STATE					*ppAESState);

	virtual DWORD 	WINAPI ContinueAESGCMDecryptData(
		PBYTE						pbData,
		DWORD						dwData,
		PAES_STATE					*ppAESState);

	virtual DWORD 	WINAPI FinalizeAESGCMDecryptData(
		AES_MAC						pGCMMAC,
		PAES_STATE					*ppAESState);

public:
	virtual DWORD	WINAPI ECDSACouplePart1EncryptKey(
		RSA_NUMBER					pPaillierPublicKey,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey1,
		PAILLIER_NUMBER				pEncryptedPrivateKey1);

	virtual DWORD	WINAPI ECDSACouplePart1EncryptKeyCtx(
		PCSPI_CTX					pContext,
		RSA_NUMBER					pPaillierPublicKey,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey1,
		PAILLIER_NUMBER				pEncryptedPrivateKey1);

	virtual DWORD	WINAPI ECDSACouplePart1Step1(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_NUMBER				pKeyK1,
		ECDSA_ENCODED_POINT			pComponentR1);

	virtual DWORD	WINAPI ECDSACouplePart1Step1Ctx(
		PCSPI_CTX					pContext,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_NUMBER				pKeyK1,
		ECDSA_ENCODED_POINT			pComponentR1);

	virtual DWORD	WINAPI ECDSACouplePart2Step(
		DWORD						dwHash,
		SHA_HASH					pHash,
		RSA_NUMBER					pPaillierPublicKey,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey2,
		ECDSA_ENCODED_POINT			pComponentR1,
		PAILLIER_NUMBER				pEncryptedPrivateKey1,
		ECDSA_NUMBER				pCommonComponentR,
		PAILLIER_NUMBER				pComponentS2);

	virtual DWORD	WINAPI ECDSACouplePart2StepCtx(
		PCSPI_CTX					pContext,
		DWORD						dwHash,
		SHA_HASH					pHash,
		RSA_NUMBER					pPaillierPublicKey,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKey2,
		ECDSA_ENCODED_POINT			pComponentR1,
		PAILLIER_NUMBER				pEncryptedPrivateKey1,
		ECDSA_NUMBER				pCommonComponentR,
		PAILLIER_NUMBER				pComponentS2);

	virtual DWORD	WINAPI ECDSACouplePart1Step2(
		PRSA_PRIVATE_KEY			pPaillierPrivateKey,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_NUMBER				pKeyK1,
		ECDSA_NUMBER				pCommonComponentR,
		PAILLIER_NUMBER				pComponentS2,
		PECDSA_SIGNATURE			pSignature);

	virtual DWORD	WINAPI ECDSACoupleMakeCommonPublicKey(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKeyA,
		ECDSA_KEY_Q					pPublicKeyB,
		ECDSA_KEY_Q					pCommonPublicKey);

	virtual DWORD	WINAPI ECDSACoupleMakeCommonPublicKeyCtx(
		PCSPI_CTX					pContext,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_D					pPrivateKeyA,
		ECDSA_KEY_Q					pPublicKeyB,
		ECDSA_KEY_Q					pCommonPublicKey);

public:
	virtual DWORD	WINAPI PBKDF2SHADeriveKey(
		DWORD						dwHash,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter,
		DWORD						dwDeriverdKey,
		PBYTE						pDerivedKey);

	virtual DWORD	WINAPI PBKDF2SHADeriveKeyCtx(
		PCSPI_CTX					pContext,
		DWORD						dwHash,
		PBYTE						pbPassword,
		DWORD						dwPassword,
		PBYTE						pbSalt,
		DWORD						dwSalt,
		BOOL						blGenerateSalt,
		DWORD						dwCounter,
		DWORD						dwDerivedKey,
		PBYTE						pDerivedKey);
};

//==============================================================================

extern BOOL				g_bNoCSPISelfTests;

//==============================================================================

#endif // CSPI_H
