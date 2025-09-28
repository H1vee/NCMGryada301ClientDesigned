#ifndef CSPI_BASE_H
#define CSPI_BASE_H

//==============================================================================

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else // OS_NIX
#include <windows.h>

#ifdef HP_ARMV4I
#undef GetProcAddress
#define GetProcAddress GetProcAddressA
#endif
#endif // OS_NIX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

//==============================================================================

#include "CSPIDefines.h"

//==============================================================================

#ifndef CSP_H

//==============================================================================

#define GOST28147_PARAMETERS_TYPE_KEY 1
#define GOST28147_PARAMETERS_TYPE_SBOX 2
#define GOST28147_PARAMETERS_TYPE_IV 3
#define GOST28147_PARAMETERS_TYPE_MAC 4
#define GOST28147_PARAMETERS_TYPE_IV_OFFSET 5

//------------------------------------------------------------------------------

#define GOST34311_PARAMETERS_TYPE_SBOX 1
#define GOST34311_PARAMETERS_TYPE_HASH 2

//==============================================================================

#endif // CSP_H

//==============================================================================

#define ECDSA_PARAMETERS_TYPE_PARAMETERS 1
#define ECDSA_PARAMETERS_TYPE_PARAMETER_EC 2
#define ECDSA_PARAMETERS_TYPE_PARAMETER_P 3
#define ECDSA_PARAMETERS_TYPE_PARAMETER_P_FULL 4
#define ECDSA_PARAMETERS_TYPE_KEY_D 5
#define ECDSA_PARAMETERS_TYPE_KEY_Q 6
#define ECDSA_PARAMETERS_TYPE_KEY_Q_FULL 7
#define ECDSA_PARAMETERS_TYPE_PRNG 8
#define ECDSA_PARAMETERS_TYPE_SIGNATURE 9
#define ECDSA_PARAMETERS_TYPE_SIGNATURE_R 10
#define ECDSA_PARAMETERS_TYPE_SIGNATURE_S 11
#define ECDSA_PARAMETERS_TYPE_HASH 12
#define ECDSA_PARAMETERS_TYPE_KEY_K 13
#define ECDSA_PARAMETERS_TYPE_HASH_LENGTH 14
#define ECDSA_PARAMETERS_TYPE_CHECK 15
#define ECDSA_PARAMETERS_TYPE_DECIMAL_PARAMETER_EC 16
#define ECDSA_PARAMETERS_TYPE_DECIMAL_HASH 17
#define ECDSA_PARAMETERS_TYPE_DECIMAL_PARAMETERS 18
#define ECDSA_PARAMETERS_TYPE_DECIMAL_KEY_D 19
#define ECDSA_PARAMETERS_TYPE_DECIMAL_SIGNATURE 20
#define ECDSA_PARAMETERS_TYPE_DECIMAL_SIGNATURE_R 21
#define ECDSA_PARAMETERS_TYPE_DECIMAL_SIGNATURE_S 22
#define ECDSA_PARAMETERS_TYPE_DECIMAL_KEY_K 23
#define ECDSA_PARAMETERS_TYPE_EC_ALGORITHM 24
#define ECDSA_PARAMETERS_TYPE_PARAMETER_P_COMPRESSED 25
#define ECDSA_PARAMETERS_TYPE_KEY_Q_COMPRESSED 26
#define ECDSA_PARAMETERS_TYPE_PAILLIER_PRIVATE_KEY 27
#define ECDSA_PARAMETERS_TYPE_PAILLIER_SHORT_PRIVATE_KEY 28
#define ECDSA_PARAMETERS_TYPE_PAILLIER_PUBLIC_KEY 29

#define ECDSA_GENERATE_PARAMETERS_TYPE_KEY_K 0
#define ECDSA_GENERATE_PARAMETERS_TYPE_KEY_D 1
#define ECDSA_GENERATE_PARAMETERS_TYPE_KEY_Q 2
#define ECDSA_GENERATE_PARAMETERS_TYPE_KEYS 3
#define ECDSA_GENERATE_PARAMETERS_TYPE_PARAMETER_P 4

//------------------------------------------------------------------------------

#define ECDSA_ALGORITHM 1
#define GOSTR3410_ALGORITHM 2

//------------------------------------------------------------------------------

#define RSA_PARAMETERS_TYPE_PARAMETERS 1
#define RSA_PARAMETERS_TYPE_PRIVATE_KEY 2
#define RSA_PARAMETERS_TYPE_SHORT_PRIVATE_KEY 3
#define RSA_PARAMETERS_TYPE_PUBLIC_KEY 4
#define RSA_PARAMETERS_TYPE_PRNG 5
#define RSA_PARAMETERS_TYPE_SIGNATURE 6
#define RSA_PARAMETERS_TYPE_HASH 7
#define RSA_PARAMETERS_TYPE_CHECK 8
#define RSA_PARAMETERS_TYPE_STATE 9
#define RSA_PARAMETERS_TYPE_SALT 10
#define RSA_PARAMETERS_TYPE_SEED 11
#define RSA_PARAMETERS_TYPE_SECURITY_STRENGTH 12
#define RSA_PARAMETERS_TYPE_PUBLIC_EXPONENT 13
#define RSA_PARAMETERS_TYPE_SHORT_KEYS 14
#define RSA_PARAMETERS_TYPE_KEYS 15
#define RSA_PARAMETERS_TYPE_VERSION 16
#define RSA_PARAMETERS_TYPE_KEYS_FAST 17
#define RSA_PARAMETERS_TYPE_PRIVATE_KEY_FAST 18
#define RSA_PARAMETERS_TYPE_ENCRYPT_SEED 19
#define RSA_PARAMETERS_TYPE_EXTERNAL_PRIVATE_KEY 20
#define RSA_PARAMETERS_TYPE_AUXILIARY_PRIMES_LENGTH 21

#define RSA_GENERATE_PARAMETERS_TYPE_KEYS 0

//------------------------------------------------------------------------------

#define DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS 1
#define DSA_PARAMETERS_TYPE_SECURITY_STRENGTH 2
#define DSA_PARAMETERS_TYPE_PRIVATE_KEY 3
#define DSA_PARAMETERS_TYPE_PER_MESSAGE_SECRET_NUMBER 4
#define DSA_PARAMETERS_TYPE_PUBLIC_KEY 5
#define DSA_PARAMETERS_TYPE_PRNG 6
#define DSA_PARAMETERS_TYPE_SIGNATURE 7
#define DSA_PARAMETERS_TYPE_HASH 8
#define DSA_PARAMETERS_TYPE_HASH_LENGTH 9
#define DSA_PARAMETERS_TYPE_SEED_LENGTH 10
#define DSA_PARAMETERS_TYPE_SEED 11
#define DSA_PARAMETERS_TYPE_H 12
#define DSA_PARAMETERS_TYPE_C 13
#define DSA_PARAMETERS_TYPE_R 14

//------------------------------------------------------------------------------

#define DSA_GENERATE_PARAMETERS_TYPE_PQ 0
#define DSA_GENERATE_PARAMETERS_TYPE_G 1
#define DSA_GENERATE_PARAMETERS_TYPE_KEYS 2
#define DSA_GENERATE_PARAMETERS_TYPE_SECRET_NUMBER 3
#define DSA_GENERATE_PARAMETERS_TYPE_PUBLIC_KEY 4

//------------------------------------------------------------------------------

#define AES_MODES_PARAMETERS_CBC_IV 1
#define AES_MODES_PARAMETERS_CFB1_IV 2
#define AES_MODES_PARAMETERS_CFB8_IV 3
#define AES_MODES_PARAMETERS_CFB128_IV 4
#define AES_MODES_PARAMETERS_OFB_IV 5
#define AES_MODES_PARAMETERS_CTR_ALL 6
#define AES_MODES_PARAMETERS_MAC_ALL 7
#define AES_MODES_PARAMETERS_MAC_PARAMETERS 8

#ifdef CSPI_AES_GCM
#define AES_MODES_PARAMETERS_GCM_PARAMETERS 9
#endif // CSPI_AES_GCM

#if defined(CSPI_AES_GET_PARAMETERS) && defined(CSPI_AES_GCM)
#define AES_MODES_PARAMETERS_GCM_MAC 10
#endif // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM

#define AES_MODES_PARAMETERS_KEY_TYPE_128 128
#define AES_MODES_PARAMETERS_KEY_TYPE_192 192
#define AES_MODES_PARAMETERS_KEY_TYPE_256 256

#define AES_MODES_GCM_STANDARD_IV_LENGTH 12

//------------------------------------------------------------------------------

#define SHA_PARAMETERS_TYPE_LENGTH 1
#define SHA_PARAMETERS_TYPE_HASH 2

//------------------------------------------------------------------------------

#define TDEA_PARAMETERS_TYPE_KEY 0x1
#define TDEA_PARAMETERS_TYPE_CBCIV 0x2

#define TDEA_STATE_KEY_SETUPED 0x1
#define TDEA_STATE_CBCIV_SETUPED 0x2

//------------------------------------------------------------------------------

#ifdef CSPI_PKCS12

//------------------------------------------------------------------------------

#define SHA1_HMAC_PARAMETERS_TYPE_KEY 1
#define SHA1_HMAC_PARAMETERS_TYPE_HMAC 2
#define SHA1_HMAC_PARAMETERS_TYPE_LONG_KEY 3

//------------------------------------------------------------------------------

#define RC2_PARAMETERS_TYPE_KEY_EFFECTIVE_BIT_LENGTH 1
#define RC2_PARAMETERS_TYPE_KEY_BYTE_LENGTH 2
#define RC2_PARAMETERS_TYPE_KEY 3
#define RC2_PARAMETERS_TYPE_IV 4

//------------------------------------------------------------------------------

#endif // CSPI_PKCS12

//------------------------------------------------------------------------------

#define SHA_HMAC_PARAMETERS_TYPE_HASH_LENGTH	1
#define SHA_HMAC_PARAMETERS_TYPE_KEY_SIZE		2
#define SHA_HMAC_PARAMETERS_TYPE_KEY			3
#define SHA_HMAC_PARAMETERS_TYPE_HMAC			4

//------------------------------------------------------------------------------

#define GOSTR3410_CURVE_TYPE_ALGORITHM ECDSA_PARAMETERS_TYPE_EC_ALGORITHM

#define GOSTR3410_CURVE_TYPE_ALGORITHM ECDSA_PARAMETERS_TYPE_EC_ALGORITHM
#define GOSTR3410_PARAMETERS_TYPE_STATE ECDSA_PARAMETERS_TYPE_STATE
#define GOSTR3410_PARAMETERS_TYPE_CHECK ECDSA_PARAMETERS_TYPE_CHECK
#define GOSTR3410_PARAMETERS_TYPE_PRNG ECDSA_PARAMETERS_TYPE_PRNG
#define GOSTR3410_PARAMETERS_TYPE_PARAMETER_EC ECDSA_PARAMETERS_TYPE_PARAMETER_EC
#define GOSTR3410_PARAMETERS_TYPE_PARAMETER_P_FULL ECDSA_PARAMETERS_TYPE_PARAMETER_P_FULL
#define GOSTR3410_PARAMETERS_TYPE_PARAMETERS ECDSA_PARAMETERS_TYPE_PARAMETERS
#define GOSTR3410_PARAMETERS_TYPE_KEY_D ECDSA_PARAMETERS_TYPE_KEY_D
#define GOSTR3410_PARAMETERS_TYPE_KEY_K ECDSA_PARAMETERS_TYPE_KEY_K
#define GOSTR3410_PARAMETERS_TYPE_KEY_Q_DECOMPRESSED ECDSA_PARAMETERS_TYPE_KEY_Q_FULL
#define GOSTR3410_PARAMETERS_TYPE_HASH ECDSA_PARAMETERS_TYPE_HASH
#define GOSTR3410_PARAMETERS_TYPE_HASH_LENGTH ECDSA_PARAMETERS_TYPE_HASH_LENGTH
#define GOSTR3410_PARAMETERS_TYPE_HASH_LENGTH ECDSA_PARAMETERS_TYPE_HASH_LENGTH
#define GOSTR3410_PARAMETERS_TYPE_SIGNATURE_R ECDSA_PARAMETERS_TYPE_SIGNATURE_R
#define GOSTR3410_PARAMETERS_TYPE_SIGNATURE_S ECDSA_PARAMETERS_TYPE_SIGNATURE_S
#define GOSTR3410_PARAMETERS_TYPE_SIGNATURE ECDSA_PARAMETERS_TYPE_SIGNATURE

#define GOSTR3410_STATE_PRNG_SETUPED ECDSA_STATE_PRNG_SETUPED
#define GOSTR3410_STATE_PARAMETER_EC_SETUPED ECDSA_STATE_PARAMETER_EC_SETUPED
#define GOSTR3410_STATE_PARAMETER_P_SETUPED ECDSA_STATE_PARAMETER_P_SETUPED
#define GOSTR3410_STATE_PARAMETERS_SETUPED ECDSA_STATE_PARAMETERS_SETUPED
#define GOSTR3410_STATE_KEY_D_SETUPED ECDSA_STATE_KEY_D_SETUPED
#define GOSTR3410_STATE_KEY_D_0_SETUPED ECDSA_STATE_KEY_D_0_SETUPED
#define GOSTR3410_STATE_KEY_K_SETUPED ECDSA_STATE_KEY_K_SETUPED
#define GOSTR3410_STATE_KEY_Q_SETUPED ECDSA_STATE_KEY_Q_SETUPED
#define GOSTR3410_STATE_KEY_Q_0_SETUPED ECDSA_STATE_KEY_Q_0_SETUPED
#define GOSTR3410_STATE_HASH_LENGTH_SETUPED ECDSA_STATE_HASH_LENGTH_SETUPED
#define GOSTR3410_STATE_HASH_SETUPED ECDSA_STATE_HASH_SETUPED
#define GOSTR3410_STATE_SIGNATURE_R_SETUPED ECDSA_STATE_SIGNATURE_R_SETUPED
#define GOSTR3410_STATE_SIGNATURE_S_SETUPED ECDSA_STATE_SIGNATURE_S_SETUPED
#define GOSTR3410_STATE_SIGNATURE_SETUPED ECDSA_STATE_SIGNATURE_SETUPED

#define GOSTR3410_GENERATE_PARAMETERS_TYPE_KEY_D ECDSA_GENERATE_PARAMETERS_TYPE_KEY_D
#define GOSTR3410_GENERATE_PARAMETERS_TYPE_KEY_Q ECDSA_GENERATE_PARAMETERS_TYPE_KEY_Q
#define GOSTR3410_GENERATE_PARAMETERS_TYPE_KEY_K ECDSA_GENERATE_PARAMETERS_TYPE_KEY_K

//==============================================================================

#ifndef CSP_H

//==============================================================================

typedef PVOID *PGOST28147_STATE;

//==============================================================================

typedef UINT GOST28147_BLOCK[2];

typedef UINT GOST28147_KEY[8];
typedef BYTE GOST28147_COMPRESSED_SBOX[64];
typedef UINT GOST28147_EXTENDED_SBOX[1024];

typedef UINT GOST28147_IV[2];
typedef UINT GOST28147_MAC[1];

//==============================================================================

#endif // CSP_H

//==============================================================================

#define APPEND_LIBRARY_PREFIX(FunctionName)\
	CSPI_##FunctionName

//------------------------------------------------------------------------------

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_SELF_TEST)();
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147SelfTest)();
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef PGOST28147_STATE (WINAPI *PGOST28147_ACQUIRE_STATE)();
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C PGOST28147_STATE WINAPI APPEND_LIBRARY_PREFIX(GOST28147AcquireState)();
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef VOID (WINAPI *PGOST28147_RELEASE_STATE)(
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI APPEND_LIBRARY_PREFIX(GOST28147ReleaseState)(
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_SET_STATE_PARAMETERS)(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147SetStateParameters)(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_GET_STATE_PARAMETERS)(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147GetStateParameters)(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_ENCRYPT_DATA_SS_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147EncryptDataSSMode)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_DECRYPT_DATA_SS_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147DecryptDataSSMode)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_ENCRYPT_DATA_G_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147EncryptDataGMode)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_ENCRYPT_DATA_GOFB_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147EncryptDataGOFBMode)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_DECRYPT_DATA_GOFB_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147DecryptDataGOFBMode)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST28147_GET_DATA_MAC)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST28147GetDataMAC)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

#ifndef CSP_H

//==============================================================================

typedef PVOID *PGOST34311_STATE;

//==============================================================================

typedef UINT GOST34311_HASH[8];

//==============================================================================

#endif // CSP_H

//==============================================================================

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST34311_SELF_TEST)();
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST34311SelfTest)();
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef PGOST34311_STATE (WINAPI *PGOST34311_ACQUIRE_STATE)();
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C PGOST34311_STATE WINAPI APPEND_LIBRARY_PREFIX(GOST34311AcquireState)();
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef VOID (WINAPI *PGOST34311_RELEASE_STATE)(
	PGOST34311_STATE pState);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI APPEND_LIBRARY_PREFIX(GOST34311ReleaseState)(
	PGOST34311_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST34311_SET_STATE_PARAMETERS)(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST34311SetStateParameters)(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST34311_GET_STATE_PARAMETERS)(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST34311GetStateParameters)(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST34311_HASH_DATA)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST34311_STATE pState);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST34311HashData)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST34311_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef BOOL (WINAPI *PGOST34311_FINALIZE_HASH)(
	UINT dwSubscribeBits,
	PGOST34311_STATE pState);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(GOST34311FinalizeHash)(
	UINT dwSubscribeBits,
	PGOST34311_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

#ifndef CSP_H
typedef PVOID *PDSTU4145_PSEUDO_RNG_STATE;
#endif //CSP_H

//==============================================================================

#ifndef CSP_H
typedef BOOL (WINAPI *PDSTU4145_PSEUDO_RNG_SELF_TEST)();
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGSelfTest)();
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef PDSTU4145_PSEUDO_RNG_STATE (WINAPI *PDSTU4145_PSEUDO_RNG_INITIALIZE)(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU4145_PSEUDO_RNG_STATE WINAPI APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGInitialize)(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_DEINITIALIZE)(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGDeinitialize)(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

#ifndef CSP_H
typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE)(
	PBYTE pbSequence,
	UINT dwBytes,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif //CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGGenerateSequence)(
	PBYTE pbSequence,
	UINT dwBytes,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE_INBITS)(
	PBYTE pbSequence,
	UINT dwBits,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGGenerateSequenceInBits)(
	PBYTE pbSequence,
	UINT dwBits,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PRSA_STATE;

//==============================================================================

#define RSA_PKCS1_V15_VERSION 15
#define RSA_PKCS1_V21_VERSION 21

//------------------------------------------------------------------------------

#define RSA_MAX_NUMBER_LENGTH 600

#define RSA_MAX_MOD_NUMBER_LENGTH 1152
#define RSA_MAX_EXP_NUMBER_LENGTH 48

//------------------------------------------------------------------------------

typedef BYTE RSA_NUMBER[RSA_MAX_NUMBER_LENGTH];
typedef BYTE RSA_SIGNATURE[RSA_MAX_NUMBER_LENGTH];
typedef BYTE RSA_BLOCK[RSA_MAX_NUMBER_LENGTH << 2];

typedef BYTE RSA_MOD_NUMBER[RSA_MAX_MOD_NUMBER_LENGTH];
typedef BYTE RSA_EXP_NUMBER[RSA_MAX_EXP_NUMBER_LENGTH];
typedef BYTE RSA_SIGNATURE_EX[RSA_MAX_MOD_NUMBER_LENGTH];

typedef struct
{
	UINT dwBits;
	UINT dwHash;
} RSA_PARAMETERS, *PRSA_PARAMETERS;

typedef struct
{
	RSA_NUMBER n;
	RSA_NUMBER e;
	RSA_NUMBER d;
	RSA_NUMBER p;
	RSA_NUMBER q;
	RSA_NUMBER dp, dq;
	RSA_NUMBER iq;
} RSA_PRIVATE_KEY, *PRSA_PRIVATE_KEY;

typedef struct
{
	RSA_NUMBER d;
	RSA_NUMBER p;
	RSA_NUMBER q;
} RSA_SHORT_PRIVATE_KEY, *PRSA_SHORT_PRIVATE_KEY;

typedef struct
{
	RSA_NUMBER n;
	RSA_NUMBER e;
} RSA_PUBLIC_KEY, *PRSA_PUBLIC_KEY;

typedef struct
{
	RSA_MOD_NUMBER n;
	RSA_EXP_NUMBER e;
} RSA_PUBLIC_KEY_EX, *PRSA_PUBLIC_KEY_EX;

//-----------------------------------------------------------------------------

typedef BOOL (WINAPI *PRSA_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSASelfTest(
	BOOL blFullTest);
#endif // PC_STATIC_LIBS

typedef PRSA_STATE (WINAPI *PRSA_ACQUIRE_STATE)(
	BOOL blChecked);
#ifdef PC_STATIC_LIBS
EXTERN_C PRSA_STATE WINAPI RSAAcquireState(
	BOOL blChecked);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PRSA_RELEASE_STATE)(
	PRSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI RSAReleaseState(
	PRSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_SET_STATE_PARAMETERS)(
	PRSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSASetStateParameters(
	PRSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_GET_STATE_PARAMETERS)(
	PRSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSAGetStateParameters(
	PRSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_GENERATE_PARAMETERS)(
	PRSA_STATE pState,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSAGenerateParameters(
	PRSA_STATE pState,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_SIGN_HASH)(
	PRSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSASignHash(
	PRSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_VERIFY_SIGNATURE)(
	PRSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSAVerifySignature(
	PRSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_ENCRYPT_DATA)(
	PRSA_STATE pState,
	PBYTE pbData,
	UINT dwDataLength,
	PBYTE pbEncryptData,
	PUINT pdwEncryptDataLength);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSAEncryptData(
	PRSA_STATE pState,
	PBYTE pbData,
	UINT dwDataLength,
	PBYTE pbEncryptData,
	PUINT pdwEncryptDataLength);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRSA_DECRYPT_DATA)(
	PRSA_STATE pState,
	PBYTE pbEncryptData,
	UINT dwEncryptDataLength,
	PBYTE pbDecryptData,
	PUINT pdwDecryptDataLength,
	BOOL blUnpadData);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RSADecryptData(
	PRSA_STATE pState,
	PBYTE pbEncryptData,
	UINT dwEncryptDataLength,
	PBYTE pbDecryptData,
	PUINT pdwDecryptDataLength,
	BOOL blUnpadData);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PSHA_STATE;

//==============================================================================

#define SHA_MAX_HASH_LENGTH 64

//------------------------------------------------------------------------------

typedef BYTE SHA_HASH[SHA_MAX_HASH_LENGTH];

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PSHA_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHASelfTest();
#endif // PC_STATIC_LIBS

typedef PSHA_STATE (WINAPI *PSHA_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PSHA_STATE WINAPI SHAAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PSHA_RELEASE_STATE)(
	PSHA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI SHAReleaseState(
	PSHA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_SET_STATE_PARAMETERS)(
	PSHA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHASetStateParameters(
	PSHA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_GET_STATE_PARAMETERS)(
	PSHA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAGetStateParameters(
	PSHA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_HASH_DATA)(
	PBYTE pbData,
	UINT dwDataBytes,
	PSHA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAHashData(
	PBYTE pbData,
	UINT dwDataBytes,
	PSHA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_FINALIZE_HASH)(
	PSHA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAFinalizeHash(
	PSHA_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI CSPIInitialize();
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PDSA_STATE;

//==============================================================================

#define DSA_MAX_NUMBER_LENGTH 100

//------------------------------------------------------------------------------

typedef UINT DSA_NUMBER[DSA_MAX_NUMBER_LENGTH];
typedef DSA_NUMBER *PDSA_NUMBER;

#define DSA_PRIVATE_KEY DSA_NUMBER
#define DSA_PUBLIC_KEY DSA_NUMBER

typedef DSA_PRIVATE_KEY *PDSA_PRIVATE_KEY;
typedef DSA_PUBLIC_KEY *PDSA_PUBLIC_KEY;

//------------------------------------------------------------------------------

typedef struct
{
	DSA_NUMBER r;
	DSA_NUMBER s;
} DSA_SIGNATURE, *PDSA_SIGNATURE;

typedef struct
{
	UINT dwL;
	UINT dwN;

	DSA_NUMBER p;
	DSA_NUMBER q;
	DSA_NUMBER g;
} DSA_PARAMETERS, *PDSA_PARAMETERS;

typedef struct
{
	UINT dwL;
	UINT dwN;
} DSA_SECURITY_STRENGTH, *PDSA_SECURITY_STRENGTH;

//------------------------------------------------------------------------------

typedef PDSA_STATE (WINAPI *PDSA_ACQUIRE_STATE)(
	BOOL blChecked);
#ifdef PC_STATIC_LIBS
EXTERN_C PDSA_STATE WINAPI DSAAcquireState(
	BOOL blChecked);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSA_RELEASE_STATE)(
	PDSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSAReleaseState(
	PDSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSA_SET_STATE_PARAMETERS)(
	PDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSASetStateParameters(
	PDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSA_GET_STATE_PARAMETERS)(
	PDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSAGetStateParameters(
	PDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSA_GENERATE_PARAMETERS)(
	PDSA_STATE pState,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSAGenerateParameters(
	PDSA_STATE pState,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSA_SIGN_HASH)(
	PRSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSASignHash(
	PRSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSA_VERIFY_SIGNATURE)(
	PRSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSAVerifySignature(
	PRSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSA_SELF_TEST)(
	BOOL bFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSASelfTest(
	BOOL bFullTest);
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PDH_CALCULATE_SHARED_SECRET)(
	PVOID pParameters,
	PUINT pXa,
	PUINT pYb,
	PUINT pSharedSecret);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DHCalculateSharedSecret(
	PVOID pParameters,
	PUINT pXa,
	PUINT pYb,
	PUINT pSharedSecret);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDH_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DHSelfTest(
	BOOL blFullTest);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PTDEA_STATE;

//==============================================================================

typedef BYTE DES_BLOCK[8];
typedef BYTE DES_KEY[8];
typedef BYTE DES_IV[8];

typedef DES_KEY *PDES_KEY;
typedef DES_BLOCK *PDES_BLOCK;

//------------------------------------------------------------------------------

typedef struct
{
	DES_KEY Key1;
	DES_KEY Key2;
	DES_KEY Key3;
} TDEA_KEYS, *PTDEA_KEYS;

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PTDEA_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEASelfTest();
#endif // PC_STATIC_LIBS

typedef PTDEA_STATE (WINAPI *PTDEA_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PTDEA_STATE WINAPI TDEAAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PTDEA_RELEASE_STATE)(
	PTDEA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI TDEAReleaseState(
	PTDEA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_SET_STATE_PARAMETERS)(
	PTDEA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEASetStateParameters(
	PTDEA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_GET_STATE_PARAMETERS)(
	PTDEA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEAGetStateParameters(
	PTDEA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_ENCRYPT_DATA_SS_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PTDEA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEAEncryptDataSSMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PTDEA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_DECRYPT_DATA_SS_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PTDEA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEADecryptDataSSMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PTDEA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_GET_DATA_MAC)(
	PBYTE pbData,
	DES_IV SSC,
	UINT dwBitDataLength,
	PTDEA_STATE pState,
	DES_BLOCK DataMAC);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEAGetDataMAC(
	PBYTE pbData,
	DES_IV SSC,
	UINT dwBitDataLength,
	PTDEA_STATE pState,
	DES_BLOCK DataMAC);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_ENCRYPT_DATA_CBC_MODE) (
	PBYTE pbData,
	UINT dwDataLength,
	PTDEA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEAEncryptDataCBCMode(
	PBYTE pbData,
	UINT dwDataLength,
	PTDEA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTDEA_DECRYPT_DATA_CBC_MODE) (
	PBYTE pbData,
	UINT dwDataLength,
	PTDEA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TDEADecryptDataCBCMode(
	PBYTE pbData,
	UINT dwDataLength,
	PTDEA_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PECDSA_STATE;

//==============================================================================

#define ECDSA_NUMBER_MAX_LEN 76
#define ECDSA_POINT_MAX_LEN \
	(ECDSA_NUMBER_MAX_LEN * 2)
#define ECDSA_NUMBER_MAX_STR_LEN \
	(((ECDSA_NUMBER_MAX_LEN * 8 / 3) + 7) & ~7)

//------------------------------------------------------------------------------

typedef BYTE ECDSA_NUMBER[ECDSA_NUMBER_MAX_LEN];
typedef BYTE ECDSA_ENCODED_POINT[ECDSA_POINT_MAX_LEN];

typedef ECDSA_NUMBER ECDSA_KEY_D;
typedef ECDSA_ENCODED_POINT ECDSA_KEY_Q;

//------------------------------------------------------------------------------

typedef struct
{
	BYTE R[ECDSA_NUMBER_MAX_STR_LEN];
	BYTE S[ECDSA_NUMBER_MAX_STR_LEN];
} ECDSA_DECIMAL_SIGNATURE,
*PECDSA_DECIMAL_SIGNATURE;

typedef struct
{
	ECDSA_NUMBER R;
	ECDSA_NUMBER S;
} ECDSA_SIGNATURE,
*PECDSA_SIGNATURE;

//------------------------------------------------------------------------------

typedef struct
{
	WORD wM, wH;
	BYTE p[ECDSA_NUMBER_MAX_STR_LEN];
	ECDSA_NUMBER a, b;
	ECDSA_NUMBER Seed;
} ECDSA_DECIMAL_PARAMETER_EC,
*PECDSA_DECIMAL_PARAMETER_EC;

typedef struct
{
	WORD wM, wH;
	ECDSA_NUMBER p;
	ECDSA_NUMBER a, b;
	ECDSA_NUMBER Seed;
} ECDSA_PARAMETER_EC,
*PECDSA_PARAMETER_EC;

typedef struct
{
	ECDSA_ENCODED_POINT BasePoint;
	ECDSA_NUMBER n;
} ECDSA_PARAMETER_P,
*PECDSA_PARAMETER_P;

typedef struct
{
	ECDSA_NUMBER x;
	ECDSA_NUMBER y;
} ECDSA_POINT,
*PECDSA_POINT;

typedef struct
{
	ECDSA_POINT BasePoint;
	ECDSA_NUMBER n;
} ECDSA_PARAMETER_P_FULL,
*PECDSA_PARAMETER_P_FULL;

typedef struct
{
	ECDSA_DECIMAL_PARAMETER_EC EC;
	ECDSA_PARAMETER_P P;
} ECDSA_DECIMAL_PARAMETERS,
*PECDSA_DECIMAL_PARAMETERS;

typedef struct
{
	ECDSA_PARAMETER_EC EC;
	ECDSA_PARAMETER_P P;
} ECDSA_PARAMETERS,
*PECDSA_PARAMETERS;

typedef struct
{
	ECDSA_PARAMETERS System;
	UINT dwHash;
} ECDSA_PARAMETERS_EX,
*PECDSA_PARAMETERS_EX;

//------------------------------------------------------------------------------

typedef PECDSA_STATE (WINAPI *PECDSA_ACQUIRE_STATE)(
	BOOL blChecked);
#ifdef PC_STATIC_LIBS
EXTERN_C PECDSA_STATE WINAPI ECDSAAcquireState(
	BOOL blChecked);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PECDSA_RELEASE_STATE)(
	PECDSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI ECDSAReleaseState(
	PECDSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSASET_STATE_PARAMETERS)(
	PECDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSASetStateParameters(
	PECDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_TEST_ON_STANDART_PARAMETERS)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSATestOnStandartParameters();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_GENERATE_PARAMETERS)(
	PECDSA_STATE pState,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSAGenerateParameters(
	PECDSA_STATE pState,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_SIGN_HASH)(
	PECDSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSASignHash(
	PECDSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_VERIFY_SIGNATURE)(
	PECDSA_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSAVerifySignature(
	PECDSA_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSAGET_STATE_PARAMETERS)(
	PECDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSAGetStateParameters(
	PECDSA_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_SELF_TEST)(
	UINT dwTestType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSASelfTest(
	UINT dwTestType);
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PECDH_CALCULATE_SHARED_SECRET)(
	PECDSA_PARAMETER_EC pParameterEC,
	PECDSA_PARAMETER_P pParameterP,
	ECDSA_NUMBER pKeyDa,
	ECDSA_ENCODED_POINT pKeyQb,
	ECDSA_NUMBER pSharedSecret);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHCalculateSharedSecret(
	PECDSA_PARAMETER_EC pParameterEC,
	PECDSA_PARAMETER_P pParameterP,
	ECDSA_NUMBER pKeyDa,
	ECDSA_ENCODED_POINT pKeyQb,
	ECDSA_NUMBER pSharedSecret);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDH_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(ECDHSelfTest)(
	BOOL blFullTest);
#endif // PC_STATIC_LIBS

//==============================================================================

#define PGOSTR3410_STATE PECDSA_STATE
#define GOSTR3410_STATE ECDSA_STATE

//==============================================================================

#define GOSTR3410_MAX_NUMBER_LEN 34

//------------------------------------------------------------------------------

typedef struct
{
	WORD bLen;
	BYTE Number[GOSTR3410_MAX_NUMBER_LEN];
} GOSTR3410_NUMBER, *PGOSTR3410_NUMBER;

typedef struct{
	GOSTR3410_NUMBER a, b;
	GOSTR3410_NUMBER p;
} GOSTR3410_CURVE , *PGOSTR3410_CURVE;

typedef struct
{
	GOSTR3410_NUMBER n;
	GOSTR3410_NUMBER x, y;
} GOSTR3410_POINT, *PGOSTR3410_POINT;

typedef struct
{
	GOSTR3410_NUMBER x, y;
} GOSTR3410_SHORT_POINT, *PGOSTR3410_SHORT_POINT;

typedef struct
{
	GOSTR3410_CURVE Curve;
	GOSTR3410_POINT BasePoint;
} GOSTR3410_PARAMETERS, *PGOSTR3410_PARAMETERS;

typedef struct
{
	GOSTR3410_NUMBER R, S;
} GOSTR3410_SIGNATURE, *PGOSTR3410_SIGNATURE;

//------------------------------------------------------------------------------

typedef PGOSTR3410_STATE (WINAPI *PGOSTR3410_ACQUIRE_STATE)(
	BOOL blChecked);
#ifdef PC_STATIC_LIBS
EXTERN_C PGOSTR3410_STATE WINAPI GOSTR3410AcquireState(
	BOOL blChecked);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PGOSTR3410_RELEASE_STATE)(
	PGOSTR3410_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI GOSTR3410ReleaseState(
	PGOSTR3410_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410SET_STATE_PARAMETERS)(
	PGOSTR3410_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410SetStateParameters(
	PGOSTR3410_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410GET_STATE_PARAMETERS)(
	PGOSTR3410_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410GetStateParameters(
	PGOSTR3410_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410_TEST_ON_STANDART_PARAMETERS)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410TestOnStandartParameters();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410_GENERATE_PARAMETERS)(
	PGOSTR3410_STATE pState,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410GenerateParameters(
	PGOSTR3410_STATE pState,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410_SIGN_HASH)(
	PGOSTR3410_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410SignHash(
	PGOSTR3410_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410_VERIFY_SIGNATURE)(
	PGOSTR3410_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410VerifySignature(
	PGOSTR3410_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOSTR3410_SELF_TEST)(
	UINT dwTestType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOSTR3410SelfTest(
	UINT dwTestType);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PAES_STATE;

//==============================================================================

#define AES_NB 4
#define AES_NR128 10
#define AES_NR192 12
#define AES_NR256 14
#define AES_NK128 4
#define AES_NK192 6
#define AES_NK256 8

#define AES_CIPHER_KEY_TYPE_128 128
#define AES_CIPHER_KEY_TYPE_192 192
#define AES_CIPHER_KEY_TYPE_256 256

typedef BYTE AES_CIPHER_KEY128[AES_NK128 * sizeof(UINT)];
typedef BYTE AES_CIPHER_KEY192[AES_NK192 * sizeof(UINT)];
typedef BYTE AES_CIPHER_KEY256[AES_NK256 * sizeof(UINT)];

typedef PBYTE PAES_CIPHER_KEY;

typedef UINT AES_ROUND_KEY128[AES_NB * (AES_NR128 + 1)];
typedef UINT AES_ROUND_KEY192[AES_NB * (AES_NR192 + 1)];
typedef UINT AES_ROUND_KEY256[AES_NB * (AES_NR256 + 1)];

typedef PUINT PAES_ROUND_KEY_WORDS;

#define AES_MODE_CTR_COUNTER_MODIFICATION_TYPE_INCREMENT 1
#define AES_MODE_CTR_COUNTER_MODIFICATION_TYPE_EXTERNAL 2

typedef BYTE AES_BLOCK[AES_NB * sizeof(UINT)];

typedef AES_BLOCK AES_MAC;
typedef AES_BLOCK AES_IV;

//------------------------------------------------------------------------------

typedef VOID (WINAPI *PAES_MODE_CTR_COUNTER_MODIFICATION)(
	AES_BLOCK pCounter);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI AESModeCtrCounterModification(
	AES_BLOCK pCounter);
#endif // PC_STATIC_LIBS

typedef struct
{
	INT iNrValue;
	AES_ROUND_KEY256 RoundKey;
	AES_ROUND_KEY256 InverseRoundKey;
} AES_ROUND_KEY, *PAES_ROUND_KEY;

typedef struct
{
	AES_BLOCK Counter;
	INT iCTRCounterModificationType;
	PAES_MODE_CTR_COUNTER_MODIFICATION CounterModificationRoutine;
} AES_MODE_CTR_PARAMETERS, *PAES_MODE_CTR_PARAMETERS;

typedef struct
{
	AES_BLOCK Random;
	UINT dwBitRandomLength;
	INT iDeriveKeysInternaly;
	AES_CIPHER_KEY256 DerivedKey1;
	AES_CIPHER_KEY256 DerivedKey2;
} AES_MODE_MAC_PARAMETERS, *PAES_MODE_MAC_PARAMETERS;

#ifdef CSPI_AES_GCM
typedef struct
{
	PBYTE pbIV;
	DWORD dwIVLength;
	PBYTE pbAuthData;
	DWORD dwAuthDataLength;
} AES_MODE_GCM_PARAMETERS, *PAES_MODE_GCM_PARAMETERS;
#endif // CSPI_AES_GCM

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PAES_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESSelfTest();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_SET_STATE_PARAMETERS)(
	PAES_STATE pState,
	PVOID pParameters,
	INT iParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESSetStateParameters(
	PAES_STATE pState,
	PVOID pParameters,
	INT iParametersType);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PAES_RELEASE_STATE)(
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI AESReleaseState(
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENCRYPT_DATA_ECB_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEncryptDataECBMode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_DECRYPT_DATA_ECB_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESDecryptDataECBMode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENCRYPT_DATA_CBC_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEncryptDataCBCMode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_DECRYPT_DATA_CBC_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESDecryptDataCBCMode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENCRYPT_DATA_CFB1_MODE)(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEncryptDataCFB1Mode(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_DECRYPT_DATA_CFB1_MODE)(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESDecryptDataCFB1Mode(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENCRYPT_DATA_CFB8_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEncryptDataCFB8Mode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_DECRYPT_DATA_CFB8_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESDecryptDataCFB8Mode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENCRYPT_DATA_CFB128_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEncryptDataCFB128Mode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_DECRYPT_DATA_CFB128_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESDecryptDataCFB128Mode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENDECRYPT_DATA_OFB_MODE)(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEnDecryptDataOFBMode(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_ENDECRYPT_DATA_CTR_MODE)(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEnDecryptDataCTRMode(
	PBYTE pbInputData,
	UINT dwBitDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_GET_DATA_MAC)(
	PBYTE pbData,
	UINT dwBitDataLength,
	AES_MAC pMAC,
	UINT dwBitMACLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESGetDataMAC(
	PBYTE pbData,
	UINT dwBitDataLength,
	AES_MAC pMAC,
	UINT dwBitMACLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef INT (WINAPI *PAES_EXPAND_KEY)(
	PAES_CIPHER_KEY pCipherKey,
	PAES_ROUND_KEY pRoundKey,
	INT iNkValue);
#ifdef PC_STATIC_LIBS
EXTERN_C INT WINAPI AESExpandKey(
	PAES_CIPHER_KEY pCipherKey,
	PAES_ROUND_KEY pRoundKey,
	INT iNkValue);
#endif // PC_STATIC_LIBS

typedef INT (WINAPI *PAES_CIPHER)(
	AES_BLOCK pInputBlock,
	AES_BLOCK pOutputBlock,
	PAES_ROUND_KEY pRoundKey);
#ifdef PC_STATIC_LIBS
EXTERN_C INT WINAPI AESCipher(
	AES_BLOCK pInputBlock,
	AES_BLOCK pOutputBlock,
	PAES_ROUND_KEY pRoundKey);
#endif // PC_STATIC_LIBS

typedef INT (WINAPI *PAES_INVERSE_CIPHER)(
	AES_BLOCK pInputBlock,
	AES_BLOCK pOutputBlock,
	PAES_ROUND_KEY pRoundKey);
#ifdef PC_STATIC_LIBS
EXTERN_C INT WINAPI AESInverseCipher(
	AES_BLOCK pInputBlock,
	AES_BLOCK pOutputBlock,
	PAES_ROUND_KEY pRoundKey);
#endif // PC_STATIC_LIBS

typedef PAES_STATE (WINAPI *PAES_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PAES_STATE WINAPI AESAcquireState();
#endif // PC_STATIC_LIBS

//==============================================================================

#ifdef CSPI_AES_GET_PARAMETERS

//==============================================================================

typedef BOOL (WINAPI *PAES_GET_STATE_PARAMETERS)(
	PAES_STATE pState,
	PVOID pParameters,
	INT iParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESGetStateParameters(
	PAES_STATE pState,
	PVOID pParameters,
	INT iParametersType);
#endif // PC_STATIC_LIBS

//==============================================================================

#endif // CSPI_AES_GET_PARAMETERS

//==============================================================================

#ifdef CSPI_AES_GCM

//==============================================================================

typedef BOOL (WINAPI *PAES_ENCRYPT_DATA_GCM_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESEncryptDataGCMMode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PAES_DECRYPT_DATA_GCM_MODE)(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI AESDecryptDataGCMMode(
	PBYTE pbInputData,
	UINT dwDataLength,
	PAES_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

#endif // CSPI_AES_GCM

//==============================================================================

#ifdef CSPI_PKCS12

//==============================================================================

typedef PVOID *PSHA1_HMAC_STATE;

//==============================================================================

#endif // CSPI_PKCS12

//------------------------------------------------------------------------------

typedef BYTE SHA1_HMAC_KEY[20];
typedef BYTE SHA1_HMAC_LONG_KEY[64];
typedef BYTE SHA1_HMAC_HASH[20];

//------------------------------------------------------------------------------

#ifdef CSPI_PKCS12

//------------------------------------------------------------------------------

typedef PSHA1_HMAC_STATE (WINAPI *PSHA1_HMAC_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PSHA1_HMAC_STATE WINAPI SHA1HMACAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PSHA1_HMAC_RELEASE_STATE)(
	PSHA1_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI SHA1HMACReleaseState(
	PSHA1_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA1_HMAC_SET_STATE_PARAMETERS)(
	PSHA1_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHA1HMACSetStateParameters(
	PSHA1_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA1_HMAC_GET_STATE_PARAMETERS)(
	PSHA1_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHA1HMACGetStateParameters(
	PSHA1_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA1_HMAC_INITIALIZE_DATA_MAC)(
	PSHA1_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHA1HMACInitializeDataMac(
	PSHA1_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA1_HMAC_UPDATE_DATA)(
	PBYTE pbData,
	UINT dwDataBytes,
	PSHA1_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHA1HMACUpdateData(
	PBYTE pbData,
	UINT dwDataBytes,
	PSHA1_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA1_HMAC_FINALIZE_DATA_MAC)(
	PSHA1_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHA1HMACFinalizeDataMac(
	PSHA1_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA1_HMAC_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHA1HMACSelfTest();
#endif // PC_STATIC_LIBS

//==============================================================================

typedef PVOID *PRC2_STATE;

//==============================================================================

typedef BYTE RC2_BLOCK[8];
typedef BYTE RC2_KEY[128];
typedef BYTE RC2_IV[8];

//------------------------------------------------------------------------------

typedef PRC2_STATE (WINAPI *PRC2_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PRC2_STATE WINAPI RC2AcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PRC2_RELEASE_STATE)(
	PRC2_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI RC2ReleaseState(
	PRC2_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRC2_SET_STATE_PARAMETERS)(
	PRC2_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RC2SetStateParameters(
	PRC2_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRC2_GET_STATE_PARAMETERS)(
	PRC2_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RC2GetStateParameters(
	PRC2_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRC2_ENCRYPT_DATA_CBC_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PRC2_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RC2EncryptDataCBCMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PRC2_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRC2_DECRYPT_DATA_CBC_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PRC2_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RC2DecryptDataCBCMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PRC2_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PRC2_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI RC2SelfTest();
#endif // PC_STATIC_LIBS

//==============================================================================

typedef BOOL (WINAPI *PPKCS12_PBKDF_TDES_DERIVE_KEY)(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	PTDEA_KEYS pKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFTDESDeriveKey(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	PTDEA_KEYS pKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_TDES_DERIVE_IV)(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	DES_IV pIV);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFTDESDeriveIV(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	DES_IV pIV);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_RC2_DERIVE_KEY)(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	UINT dwKey,
	RC2_KEY pKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFRC2DeriveKey(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	UINT dwKey,
	RC2_KEY pKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_RC2_DERIVE_IV)(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	RC2_IV pIV);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFRC2DeriveIV(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	RC2_IV pIV);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_SHA1_DERIVE_HMAC_KEY)(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	SHA1_HMAC_KEY pKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFSHA1DeriveHMACKey(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	SHA1_HMAC_KEY pKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFSelfTest();
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PPBKDF2I_DERIVE_KEY)(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	PTDEA_KEYS pDerivedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDF2IDeriveKey(
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	PTDEA_KEYS pDerivedKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPBKDF2I_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDF2ISelfTest(
	BOOL blFullTest);
#endif // PC_STATIC_LIBS

//==============================================================================

#endif // CSPI_PKCS12

//==============================================================================

#ifdef CSPI_REINITIALIZE_PRNG

//==============================================================================

#ifndef CSP_H
typedef BOOL (WINAPI *PDSTU4145_PSEUDO_RNG_REINITIALIZE)(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // CSP_H
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGReinitialize)(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

//==============================================================================

#endif // CSPI_REINITIALIZE_PRNG

//==============================================================================

#define PAILLIER_NUMBER_MAX_LEN 512

//------------------------------------------------------------------------------

typedef BYTE PAILLIER_NUMBER[PAILLIER_NUMBER_MAX_LEN];

//------------------------------------------------------------------------------

#ifdef CSPI_ECDSA_COUPLE

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PECDSA_COUPLE_PART1_ENCRYPT_KEY)(
	PECDSA_STATE pState,
	PAILLIER_NUMBER pEncKeyD1);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSACouplePart1EncryptKey(
	PECDSA_STATE pState,
	PAILLIER_NUMBER pEncKeyD1);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_COUPLE_PART1_STEP1)(
	PECDSA_STATE pState,
	ECDSA_ENCODED_POINT pR1);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSACouplePart1Step1(
	PECDSA_STATE pState,
	ECDSA_ENCODED_POINT pR1);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_COUPLE_PART2_STEP)(
	PECDSA_STATE pState,
	ECDSA_ENCODED_POINT pR1,
	PAILLIER_NUMBER pEncKeyD1,
	ECDSA_NUMBER pR,
	PAILLIER_NUMBER pS2);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSACouplePart2Step(
	PECDSA_STATE pState,
	ECDSA_ENCODED_POINT pR1,
	PAILLIER_NUMBER pEncKeyD1,
	ECDSA_NUMBER pR,
	PAILLIER_NUMBER pS2);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_COUPLE_PART1_STEP2)(
	PECDSA_STATE pState,
	ECDSA_NUMBER pR,
	PAILLIER_NUMBER pS2);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSACouplePart1Step2(
	PECDSA_STATE pState,
	ECDSA_NUMBER pR,
	PAILLIER_NUMBER pS2);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_COUPLE_MAKE_COMMON_KEY)(
	PECDSA_STATE pState,
	ECDSA_ENCODED_POINT pKeyQb,
	ECDSA_ENCODED_POINT pKeyQ);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSACoupleMakeCommonKey(
	PECDSA_STATE pState,
	ECDSA_ENCODED_POINT pKeyQb,
	ECDSA_ENCODED_POINT pKeyQ);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDSA_COUPLE_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDSACoupleSelfTest();
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

#endif // CSPI_ECDSA_COUPLE

//==============================================================================

typedef PVOID *PSHA_HMAC_STATE;

//==============================================================================

typedef PSHA_HMAC_STATE (WINAPI *PSHA_HMAC_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PSHA_HMAC_STATE WINAPI SHAHMACAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PSHA_HMAC_RELEASE_STATE)(
	PSHA_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI SHAHMACReleaseState(
	PSHA_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_HMAC_SET_STATE_PARAMETERS)(
	PSHA_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAHMACSetStateParameters(
	PSHA_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_HMAC_GET_STATE_PARAMETERS)(
	PSHA_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAHMACGetStateParameters(
	PSHA_HMAC_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_HMAC_UPDATE_DATA)(
	PBYTE pbData,
	UINT dwDataBytes,
	PSHA_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAHMACUpdateData(
	PBYTE pbData,
	UINT dwDataBytes,
	PSHA_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_HMAC_FINALIZE_DATA_MAC)(
	PSHA_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAHMACFinalizeDataMac(
	PSHA_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PSHA_HMAC_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI SHAHMACSelfTest();
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PPBKDF2_SHA_DERIVE_KEY)(
	DWORD dwHash,
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	UINT dwDerivedKey,
	PBYTE pDerivedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDF2SHADeriveKey(
	DWORD dwHash,
	PBYTE pbPassword,
	UINT dwPassword,
	PBYTE pbSalt,
	UINT dwSalt,
	UINT dwCounter,
	UINT dwDerivedKey,
	PBYTE pDerivedKey);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef struct
{
	PDSTU4145_PSEUDO_RNG_SELF_TEST DSTU4145PseudoRNGSelfTest;
	PDSTU4145_PSEUDO_RNG_INITIALIZE DSTU4145PseudoRNGInitialize;
	PDSTU4145_PSEUDO_RNG_DEINITIALIZE DSTU4145PseudoRNGDeinitialize;
	PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE DSTU4145PseudoRNGGenerateSequence;
	PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE_INBITS DSTU4145PseudoRNGGenerateSequenceInBits;

	PGOST28147_SELF_TEST GOST28147SelfTest;
	PGOST28147_ACQUIRE_STATE GOST28147AcquireState;
	PGOST28147_RELEASE_STATE GOST28147ReleaseState;
	PGOST28147_SET_STATE_PARAMETERS GOST28147SetStateParameters;
	PGOST28147_GET_STATE_PARAMETERS GOST28147GetStateParameters;
	PGOST28147_ENCRYPT_DATA_SS_MODE GOST28147EncryptDataSSMode;
	PGOST28147_DECRYPT_DATA_SS_MODE GOST28147DecryptDataSSMode;
	PGOST28147_ENCRYPT_DATA_G_MODE GOST28147EncryptDataGMode;
	PGOST28147_ENCRYPT_DATA_GOFB_MODE GOST28147EncryptDataGOFBMode;
	PGOST28147_DECRYPT_DATA_GOFB_MODE GOST28147DecryptDataGOFBMode;
	PGOST28147_GET_DATA_MAC GOST28147GetDataMAC;

	PGOST34311_SELF_TEST GOST34311SelfTest;
	PGOST34311_ACQUIRE_STATE GOST34311AcquireState;
	PGOST34311_RELEASE_STATE GOST34311ReleaseState;
	PGOST34311_SET_STATE_PARAMETERS GOST34311SetStateParameters;
	PGOST34311_GET_STATE_PARAMETERS GOST34311GetStateParameters;
	PGOST34311_HASH_DATA GOST34311HashData;
	PGOST34311_FINALIZE_HASH GOST34311FinalizeHash;

	PRSA_SELF_TEST RSASelfTest;
	PRSA_ACQUIRE_STATE RSAAcquireState;
	PRSA_RELEASE_STATE RSAReleaseState;
	PRSA_SET_STATE_PARAMETERS RSASetStateParameters;
	PRSA_GET_STATE_PARAMETERS RSAGetStateParameters;
	PRSA_GENERATE_PARAMETERS RSAGenerateParameters;
	PRSA_SIGN_HASH RSASignHash;
	PRSA_VERIFY_SIGNATURE RSAVerifySignature;
	PRSA_ENCRYPT_DATA RSAEncryptData;
	PRSA_DECRYPT_DATA RSADecryptData;

	PSHA_SELF_TEST SHASelfTest;
	PSHA_ACQUIRE_STATE SHAAcquireState;
	PSHA_RELEASE_STATE SHAReleaseState;
	PSHA_SET_STATE_PARAMETERS SHASetStateParameters;
	PSHA_GET_STATE_PARAMETERS SHAGetStateParameters;
	PSHA_HASH_DATA SHAHashData;
	PSHA_FINALIZE_HASH SHAFinalizeHash;

	PECDSA_SELF_TEST ECDSASelfTest;
	PECDSA_ACQUIRE_STATE ECDSAAcquireState;
	PECDSA_RELEASE_STATE ECDSAReleaseState;
	PECDSASET_STATE_PARAMETERS ECDSASetStateParameters;
	PECDSA_GENERATE_PARAMETERS ECDSAGenerateParameters;
	PECDSA_SIGN_HASH ECDSASignHash;
	PECDSA_VERIFY_SIGNATURE ECDSAVerifySignature;
	PECDSAGET_STATE_PARAMETERS ECDSAGetStateParameters;
	PECDSA_TEST_ON_STANDART_PARAMETERS ECDSATestOnStandartParameters;

	PGOSTR3410_SELF_TEST GOSTR3410SelfTest;
	PGOSTR3410_ACQUIRE_STATE GOSTR3410AcquireState;
	PGOSTR3410_RELEASE_STATE GOSTR3410ReleaseState;
	PGOSTR3410SET_STATE_PARAMETERS GOSTR3410SetStateParameters;
	PGOSTR3410GET_STATE_PARAMETERS GOSTR3410GetStateParameters;
	PGOSTR3410_GENERATE_PARAMETERS GOSTR3410GenerateParameters;
	PGOSTR3410_SIGN_HASH GOSTR3410SignHash;
	PGOSTR3410_VERIFY_SIGNATURE GOSTR3410VerifySignature;
	PGOSTR3410_TEST_ON_STANDART_PARAMETERS GOSTR3410TestOnStandartParameters;

	PTDEA_SELF_TEST TDEASelfTest;
	PTDEA_ACQUIRE_STATE TDEAAcquireState;
	PTDEA_RELEASE_STATE TDEAReleaseState;
	PTDEA_SET_STATE_PARAMETERS TDEASetStateParameters;
	PTDEA_GET_STATE_PARAMETERS TDEAGetStateParameters;
	PTDEA_ENCRYPT_DATA_SS_MODE TDEAEncryptDataSSMode;
	PTDEA_DECRYPT_DATA_SS_MODE TDEADecryptDataSSMode;
	PTDEA_ENCRYPT_DATA_CBC_MODE TDEAEncryptDataCBCMode;
	PTDEA_DECRYPT_DATA_CBC_MODE TDEADecryptDataCBCMode;
	PTDEA_GET_DATA_MAC TDEAGetDataMAC;

	PDSA_SELF_TEST DSASelfTest;
	PDSA_ACQUIRE_STATE DSAAcquireState;
	PDSA_RELEASE_STATE DSAReleaseState;
	PDSA_SET_STATE_PARAMETERS DSASetStateParameters;
	PDSA_GET_STATE_PARAMETERS DSAGetStateParameters;
	PDSA_GENERATE_PARAMETERS DSAGenerateParameters;
	PDSA_SIGN_HASH DSASignHash;
	PDSA_VERIFY_SIGNATURE DSAVerifySignature;

	PAES_SELF_TEST AESSelfTest;
	PAES_ACQUIRE_STATE AESAcquireState;
	PAES_SET_STATE_PARAMETERS AESSetStateParameters;
	PAES_RELEASE_STATE AESReleaseState;
	PAES_ENCRYPT_DATA_ECB_MODE AESEncryptDataECBMode;
	PAES_DECRYPT_DATA_ECB_MODE AESDecryptDataECBMode;
	PAES_ENCRYPT_DATA_CBC_MODE AESEncryptDataCBCMode;
	PAES_DECRYPT_DATA_CBC_MODE AESDecryptDataCBCMode;
	PAES_ENCRYPT_DATA_CFB1_MODE AESEncryptDataCFB1Mode;
	PAES_DECRYPT_DATA_CFB1_MODE AESDecryptDataCFB1Mode;
	PAES_ENCRYPT_DATA_CFB8_MODE AESEncryptDataCFB8Mode;
	PAES_DECRYPT_DATA_CFB8_MODE AESDecryptDataCFB8Mode;
	PAES_ENCRYPT_DATA_CFB128_MODE AESEncryptDataCFB128Mode;
	PAES_DECRYPT_DATA_CFB128_MODE AESDecryptDataCFB128Mode;
	PAES_ENDECRYPT_DATA_OFB_MODE AESEnDecryptDataOFBMode;
	PAES_ENDECRYPT_DATA_CTR_MODE AESEnDecryptDataCTRMode;
	PAES_GET_DATA_MAC AESGetDataMAC;
	PAES_EXPAND_KEY AESExpandKey;
	PAES_CIPHER AESCipher;
	PAES_INVERSE_CIPHER AESInverseCipher;

	PDH_SELF_TEST DHSelfTest;
	PDH_CALCULATE_SHARED_SECRET DHCalculateSharedSecret;

	PECDH_SELF_TEST ECDHSelfTest;
	PECDH_CALCULATE_SHARED_SECRET ECDHCalculateSharedSecret;
} CSPI_BASE_FUNCTIONS, *PCSPI_BASE_FUNCTIONS;

//------------------------------------------------------------------------------

typedef struct
{
	UINT nSize;
	UINT nReserved;

#ifdef CSPI_PKCS12
	PSHA1_HMAC_ACQUIRE_STATE SHA1HMACAcquireState;
	PSHA1_HMAC_RELEASE_STATE SHA1HMACReleaseState;
	PSHA1_HMAC_SET_STATE_PARAMETERS SHA1HMACSetStateParameters;
	PSHA1_HMAC_GET_STATE_PARAMETERS SHA1HMACGetStateParameters;
	PSHA1_HMAC_INITIALIZE_DATA_MAC SHA1HMACInitializeDataMac;
	PSHA1_HMAC_UPDATE_DATA SHA1HMACUpdateData;
	PSHA1_HMAC_FINALIZE_DATA_MAC SHA1HMACFinalizeDataMac;
	PSHA1_HMAC_SELF_TEST SHA1HMACSelfTest;

	PRC2_ACQUIRE_STATE RC2AcquireState;
	PRC2_RELEASE_STATE RC2ReleaseState;
	PRC2_SET_STATE_PARAMETERS RC2SetStateParameters;
	PRC2_GET_STATE_PARAMETERS RC2GetStateParameters;
	PRC2_ENCRYPT_DATA_CBC_MODE RC2EncryptDataCBCMode;
	PRC2_DECRYPT_DATA_CBC_MODE RC2DecryptDataCBCMode;
	PRC2_SELF_TEST RC2SelfTest;

	PPKCS12_PBKDF_RC2_DERIVE_KEY PKCS12PBKDFRC2DeriveKey;
	PPKCS12_PBKDF_RC2_DERIVE_IV PKCS12PBKDFRC2DeriveIV;
	PPKCS12_PBKDF_TDES_DERIVE_KEY PKCS12PBKDFTDESDeriveKey;
	PPKCS12_PBKDF_TDES_DERIVE_IV PKCS12PBKDFTDESDeriveIV;
	PPKCS12_PBKDF_SHA1_DERIVE_HMAC_KEY PKCS12PBKDFSHA1DeriveHMACKey;
	PPKCS12_PBKDF_SELF_TEST PKCS12PBKDFSelfTest;

	PPBKDF2I_DERIVE_KEY PBKDF2IDeriveKey;
	PPBKDF2I_SELF_TEST PBKDF2ISelfTest;
#else // CSPI_PKCS12
	FARPROC SHA1HMACAcquireState;
	FARPROC SHA1HMACReleaseState;
	FARPROC SHA1HMACSetStateParameters;
	FARPROC SHA1HMACGetStateParameters;
	FARPROC SHA1HMACInitializeDataMac;
	FARPROC SHA1HMACUpdateData;
	FARPROC SHA1HMACFinalizeDataMac;
	FARPROC SHA1HMACSelfTest;

	FARPROC RC2AcquireState;
	FARPROC RC2ReleaseState;
	FARPROC RC2SetStateParameters;
	FARPROC RC2GetStateParameters;
	FARPROC RC2EncryptDataCBCMode;
	FARPROC RC2DecryptDataCBCMode;
	FARPROC RC2SelfTest;

	FARPROC PKCS12PBKDFRC2DeriveKey;
	FARPROC PKCS12PBKDFRC2DeriveIV;
	FARPROC PKCS12PBKDFTDESDeriveKey;
	FARPROC PKCS12PBKDFTDESDeriveIV;
	FARPROC PKCS12PBKDFSHA1DeriveHMACKey;
	FARPROC PKCS12PBKDFSelfTest;

	FARPROC PBKDF2IDeriveKey;
	FARPROC PBKDF2ISelfTest;
#endif // CSP_PKCS12

#ifdef CSPI_REINITIALIZE_PRNG
	PDSTU4145_PSEUDO_RNG_REINITIALIZE DSTU4145PseudoRNGReinitialize;
#else // CSPI_REINITIALIZE_PRNG
	FARPROC DSTU4145PseudoRNGReinitialize;
#endif // CSPI_REINITIALIZE_PRNG

#ifdef CSPI_AES_GET_PARAMETERS
	PAES_GET_STATE_PARAMETERS AESGetStateParameters;
#else // CSPI_AES_GET_PARAMETERS
	FARPROC AESGetStateParameters;
#endif // CSPI_AES_GET_PARAMETERS

#ifdef CSPI_AES_GCM
	PAES_ENCRYPT_DATA_GCM_MODE AESEncryptDataGCMMode;
	PAES_DECRYPT_DATA_GCM_MODE AESDecryptDataGCMMode;
#else // CSPI_AES_GCM
	FARPROC AESEncryptDataGCMMode;
	FARPROC AESDecryptDataGCMMode;
#endif // CSPI_AES_GCM

#ifdef CSPI_ECDSA_COUPLE
	PECDSA_COUPLE_PART1_ENCRYPT_KEY ECDSACouplePart1EncryptKey;
	PECDSA_COUPLE_PART1_STEP1 ECDSACouplePart1Step1;
	PECDSA_COUPLE_PART2_STEP ECDSACouplePart2Step;
	PECDSA_COUPLE_PART1_STEP2 ECDSACouplePart1Step2;
	PECDSA_COUPLE_MAKE_COMMON_KEY ECDSACoupleMakeCommonKey;
	PECDSA_COUPLE_SELF_TEST ECDSACoupleSelfTest;
#else // CSPI_ECDSA_COUPLE
	FARPROC ECDSACouplePart1EncryptKey;
	FARPROC ECDSACouplePart1Step1;
	FARPROC ECDSACouplePart2Step;
	FARPROC ECDSACouplePart1Step2;
	FARPROC ECDSACoupleMakeCommonKey;
	FARPROC ECDSACoupleSelfTest;
#endif // CSPI_ECDSA_COUPLE

	PSHA_HMAC_ACQUIRE_STATE SHAHMACAcquireState;
	PSHA_HMAC_RELEASE_STATE SHAHMACReleaseState;
	PSHA_HMAC_SET_STATE_PARAMETERS SHAHMACSetStateParameters;
	PSHA_HMAC_GET_STATE_PARAMETERS SHAHMACGetStateParameters;
	PSHA_HMAC_UPDATE_DATA SHAHMACUpdateData;
	PSHA_HMAC_FINALIZE_DATA_MAC SHAHMACFinalizeDataMac;
	PSHA_HMAC_SELF_TEST SHAHMACSelfTest;

	PPBKDF2_SHA_DERIVE_KEY PBKDF2SHADeriveKey;

} CSPI_BASE_FUNCTIONS_EX, *PCSPI_BASE_FUNCTIONS_EX;

//==============================================================================

#ifndef CSP_H

//==============================================================================

#define AIS31_SEQUENCE_SIZE_BYTES	2500

//------------------------------------------------------------------------------

#define BS_MIN_SEQUENCE_BYTES		4
#define BS_MAX_SEQUENCE_BYTES		(2 * 1024)

//------------------------------------------------------------------------------

typedef PVOID BS_STATISTIC, *PBS_STATISTIC;

//==============================================================================

typedef BOOL (WINAPI *PTSCG_IS_ENABLE)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TSCGIsEnable();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PTSCG_GENERATE_SEQUENCE)(
	PBYTE pbSequence,
	UINT dwBytes);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI TSCGGenerateSequence(
	PBYTE pbSequence,
	UINT dwBytes);
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

typedef BOOL (WINAPI *PBS_TEST_SEQUENCE)(
	PBS_STATISTIC *ppStatistic,
	PBYTE pbSequence,
	UINT dwBits);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI BSTestSequence(
	PBS_STATISTIC *ppStatistic,
	PBYTE pbSequence,
	UINT dwBits);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PBS_RELEASE_STATISTIC)(
	PBS_STATISTIC pStatistic);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI BSReleaseStatistic(
	PBS_STATISTIC pStatistic);
#endif // PC_STATIC_LIBS

//------------------------------------------------------------------------------

typedef UINT (WINAPI *PCRC32_COUNT)(
	PBYTE pbData,
	UINT cbData);
#ifdef PC_STATIC_LIBS
EXTERN_C UINT WINAPI CRC32Count(
	PBYTE pbData,
	UINT cbData);
#endif // PC_STATIC_LIBS

//==============================================================================

typedef struct
{
	PTSCG_IS_ENABLE TSCGIsEnable;
	PTSCG_GENERATE_SEQUENCE TSCGGenerateSequence;

	PBS_TEST_SEQUENCE BSTestSequence;
	PBS_RELEASE_STATISTIC BSReleaseStatistic;

	PCRC32_COUNT CRC32Count;
} CSP_EXTENSION_FUNCTIONS, *PCSP_EXTENSION_FUNCTIONS;

//==============================================================================

#endif // CSP_H

//==============================================================================

class CSPIBase
{
private:
	HMODULE m_hBaseLibrary;
	HMODULE m_hExtensionLibrary;

public:
	CSPI_BASE_FUNCTIONS F;
	CSP_EXTENSION_FUNCTIONS ExtensionF;

public:
	CSPIBase();
	~CSPIBase();

public:
	BOOL WINAPI Load();
	VOID WINAPI Unload();
	BOOL WINAPI LoadEx(
		PCSPI_BASE_FUNCTIONS_EX *ppBaseEx);
	VOID WINAPI UnloadEx(
		PCSPI_BASE_FUNCTIONS_EX *ppBaseEx);
};

//==============================================================================

#endif // CSPI_BASE_H
