#ifndef ICSPI_HARDWARE_H
#define ICSPI_HARDWARE_H

//======================================================================================================================

#include "CSPIBase.h"

//======================================================================================================================

class ICSPIHardware
{
public:
	virtual BOOL WINAPI SetSBoxes(
		GOST28147_COMPRESSED_SBOX	pPRNGSBox) PURE;

	virtual BOOL WINAPI RSAGenerateKeys(
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey) PURE;

	virtual BOOL WINAPI RSASignHash(
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		RSA_SIGNATURE 				pSignature) PURE;

	virtual BOOL WINAPI RSACheckKeys(
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey) PURE;
	
	virtual BOOL WINAPI DSASignHash(
		DWORD						dwHash,
		SHA_HASH					pHash,
		PDSA_PARAMETERS				pParameters,
		PDSA_SIGNATURE 				pSignature) PURE;

	virtual BOOL WINAPI DSAGenerateKeys(
		PDSA_PARAMETERS				pParameters,
		PDSA_PUBLIC_KEY				pPublicKey) PURE;

	virtual BOOL WINAPI DSACheckKeys(
		PDSA_PARAMETERS				pParameters,
		PDSA_PUBLIC_KEY				pPublicKey) PURE;

	virtual BOOL WINAPI ECDSASignHash(
		DWORD						dwHash,
		SHA_HASH					pHash,
		PECDSA_PARAMETERS 			pParameters,
		PECDSA_SIGNATURE 			pSignature)	PURE;

	virtual BOOL WINAPI ECDSAGenerateKeys(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_Q					pPublicKey) PURE;

	virtual BOOL WINAPI ECDSACheckKeys(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_Q					pPublicKey) PURE;

	virtual BOOL WINAPI ECDHCalculateSharedSecret(
		PECDSA_PARAMETERS 			pParameters,
		ECDSA_KEY_Q 				pRecipientPublicKey,
		ECDSA_NUMBER				pSharedSecret) PURE;
	
	virtual BOOL WINAPI DHCalculateSharedSecret(
		PDSA_PARAMETERS				pParameters,
		DSA_NUMBER 					pRecipientPublicKey,
		DSA_NUMBER					pSharedSecret) PURE;

	virtual BOOL WINAPI RSARecoverPublicKey(
		PRSA_PARAMETERS				pParameters,
		PRSA_PUBLIC_KEY				pPublicKey) PURE;

	virtual BOOL WINAPI DSARecoverPublicKey(
		PDSA_PARAMETERS				pParameters,
		PDSA_PUBLIC_KEY				pPublicKey) PURE;

	virtual BOOL WINAPI ECDSARecoverPublicKey(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_Q					pPublicKey) PURE;

	virtual BOOL WINAPI RSADecryptData(
		PBYTE						pbData,
		PDWORD						pdwData,
		PRSA_PARAMETERS				pParameters,
		BOOL						blUnpadData) PURE;

	virtual BOOL WINAPI RSAPSSSignHash(
		SHA_HASH					pHash,
		PRSA_PARAMETERS				pParameters,
		RSA_SIGNATURE 				pSignature) PURE;

	virtual BOOL WINAPI ECDSACouplePart2Step(
		DWORD						dwHash,
		SHA_HASH					pHash,
		RSA_NUMBER					pPaillierPublicKey,
		PECDSA_PARAMETERS			pParameters,
		ECDSA_ENCODED_POINT			pComponentR1,
		PAILLIER_NUMBER				pEncryptedPrivateKey1,
		ECDSA_NUMBER				pCommonComponentR,
		PAILLIER_NUMBER				pComponentS2) PURE;

	virtual BOOL WINAPI ECDSACoupleMakeCommonPublicKey(
		PECDSA_PARAMETERS			pParameters,
		ECDSA_KEY_Q					pPublicKeyB,
		ECDSA_KEY_Q					pCommonPublicKey) PURE;
};

//======================================================================================================================

#endif // ICSPI_HARDWARE_H
