#ifndef ICSP_HARDWARE_H
#define ICSP_HARDWARE_H

//======================================================================================================================

#include "CSPBase.h"

//======================================================================================================================

class ICSPHardware
{
public:
	virtual BOOL WINAPI GenerateDSKeys(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQ) PURE;

	virtual BOOL WINAPI GenerateKEPKeys(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQ) PURE;

	virtual BOOL WINAPI SignHash(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST34311_HASH 				pHash,
			DSTU4145_SIGNATURE 			pSignature) PURE;

	virtual BOOL WINAPI ProtectSharedData(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQb,
			ECDH_EXTENDED_DATA 			pData,
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_MAC 				pMAC) PURE;

	virtual BOOL WINAPI UnprotectSharedData(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQb,
			ECDH_EXTENDED_DATA 			pData,
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_MAC 				pMAC) PURE;

	virtual BOOL WINAPI CheckDSKeys(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQ) PURE;

	virtual BOOL WINAPI CheckKEPKeys(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQ) PURE;

	virtual BOOL WINAPI SetSBoxes(
			GOST28147_COMPRESSED_SBOX 	pEncryptionSBox,
			GOST28147_COMPRESSED_SBOX 	pHashSBox,
			GOST28147_COMPRESSED_SBOX 	pECDHSBox,
			GOST28147_COMPRESSED_SBOX	pPRNGSBox) PURE;

	virtual BOOL WINAPI HashKEPKey(
			GOST34311_HASH				pHash) PURE;

#ifdef CSP_ECDH_UA
	virtual BOOL WINAPI WrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST28147_COMPRESSED_SBOX	pWrapSBox,
			GOST28147_KEY				pKey,
			GOST28147_WRAPED_KEY		pWrappedKey) PURE;

	virtual BOOL WINAPI UnwrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			GOST28147_COMPRESSED_SBOX	pHashSBox,
			GOST28147_COMPRESSED_SBOX	pWrapSBox,
			GOST28147_WRAPED_KEY		pWrappedKey,
			GOST28147_KEY				pKey) PURE;
#endif // CSP_ECDH_UA

	virtual BOOL WINAPI GetEncryptionSBox(
			GOST28147_EXTENDED_SBOX		pSBox) PURE;

	virtual BOOL WINAPI InitializeEncryptData(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV,
			BOOL 						blGenerateKeyAndIV) PURE;

	virtual BOOL WINAPI ContinueEncryptData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_KEY 				pKey) PURE;

	virtual BOOL WINAPI ContinueEncryptDataByOffset(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_KEY 				pKey,
			DWORDLONG 					dwlDataOffset) PURE;

	virtual BOOL WINAPI FinalizeEncryptData(
			GOST28147_KEY 				pKey) PURE;

	virtual BOOL WINAPI InitializeDecryptData(
			GOST28147_COMPRESSED_SBOX	pSBox,
			GOST28147_KEY 				pKey,
			GOST28147_IV 				pIV) PURE;

	virtual BOOL WINAPI ContinueDecryptData(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_KEY 				pKey) PURE;

	virtual BOOL WINAPI ContinueDecryptDataByOffset(
			PBYTE 						pbData,
			DWORD 						dwData,
			GOST28147_KEY 				pKey,
			DWORDLONG 					dwlDataOffset) PURE;

	virtual BOOL WINAPI FinalizeDecryptData(
			GOST28147_KEY 				pKey) PURE;

	virtual BOOL WINAPI RecoverDSPublicKey(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQ) PURE;

	virtual BOOL WINAPI RecoverKEPPublicKey(
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			DSTU4145_KEY_Q 				pKeyQ) PURE;

	virtual BOOL WINAPI CoupleDSMakeComponentS(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_NUMBER				pKeyK,
			DSTU4145_NUMBER				pCommonComponentR,
			DSTU4145_NUMBER				pComponentS) PURE;

	virtual BOOL WINAPI SignDSTUHash(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DWORD						dwHash,
			DSTU7564_HASH				pHash,
			DSTU4145_SIGNATURE			pSignature) PURE;

	virtual BOOL WINAPI DSTU7624WrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pKey,
			DWORD						dwKey,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey) PURE;

	virtual BOOL WINAPI DSTU7624UnwrapSharedKey(
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP,
			DSTU4145_KEY_Q				pKeyQb,
			BOOL						blCofactorMethod,
			PBYTE						pbSharedInfo,
			DWORD						dwSharedInfo,
			DSTU7624_SBOX				pWrapSBox,
			PBYTE						pWrappedKey,
			DWORD						dwWrappedKey,
			PBYTE						pKey,
			DWORD						dwKey) PURE;
};

//======================================================================================================================

#endif // ICSP_HARDWARE_H
