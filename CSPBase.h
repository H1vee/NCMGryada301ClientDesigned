#ifndef CSP_BASE_H
#define CSP_BASE_H

//======================================================================================================================

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

//======================================================================================================================

#include "CSPDefines.h"

//======================================================================================================================

typedef UINT GOST28147_BLOCK[2];

typedef UINT GOST28147_KEY[8];
typedef BYTE GOST28147_COMPRESSED_SBOX[64];
typedef UINT GOST28147_EXTENDED_SBOX[1024];

typedef UINT GOST28147_IV[2];
typedef UINT GOST28147_MAC[1];

//----------------------------------------------------------------------------------------------------------------------

#define GOST28147_PARAMETERS_TYPE_KEY 1
#define GOST28147_PARAMETERS_TYPE_SBOX 2
#define GOST28147_PARAMETERS_TYPE_IV 3
#define GOST28147_PARAMETERS_TYPE_MAC 4
#define GOST28147_PARAMETERS_TYPE_IV_OFFSET 5

//----------------------------------------------------------------------------------------------------------------------

#pragma pack(push, 16)
typedef struct
{
	GOST28147_KEY Key;
	GOST28147_EXTENDED_SBOX SBox;
	GOST28147_IV StartIV;
	GOST28147_IV IV;
	GOST28147_BLOCK GBlock;
	GOST28147_BLOCK MACBlock;
	UINT dwState;
} GOST28147_STATE, *PGOST28147_STATE;
#pragma pack(pop)

//----------------------------------------------------------------------------------------------------------------------

typedef UINT GOST34311_HASH[8];

typedef PVOID *PGOST34311_STATE;

//----------------------------------------------------------------------------------------------------------------------

#define GOST34311_PARAMETERS_TYPE_SBOX 1
#define GOST34311_PARAMETERS_TYPE_HASH 2

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_KDF_UA
typedef PVOID *PGOST34311HMAC_STATE;

//----------------------------------------------------------------------------------------------------------------------

#define GOST34311HMAC_PARAMETERS_TYPE_SBOX 1
#define GOST34311HMAC_PARAMETERS_TYPE_HASH 2
#define GOST34311HMAC_PARAMETERS_TYPE_KEY 3
#define GOST34311HMAC_PARAMETERS_TYPE_HMAC 4
#endif // CSP_KDF_UA

//----------------------------------------------------------------------------------------------------------------------

typedef PVOID *PDSTU4145_PSEUDO_RNG_STATE;

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_MULTI_ALGO_PRNG
#define DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_ALGO 1
#define DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_SBOX 2
#define DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_KEY 3
#define DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_S 4
#define DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_DATETIME 5
#endif // CSP_MULTI_ALGO_PRNG

#define DSTU4145_PSEUDO_RNG_ALGO_GOST28147 0
#define DSTU4145_PSEUDO_RNG_ALGO_DSTU7624 1

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_MAX_EC_LENGTH 19

//----------------------------------------------------------------------------------------------------------------------

typedef UINT DSTU4145_KEY_D[DSTU4145_MAX_EC_LENGTH];
typedef UINT DSTU4145_KEY_Q[DSTU4145_MAX_EC_LENGTH];
typedef UINT DSTU4145_SIGNATURE[DSTU4145_MAX_EC_LENGTH * 2];
typedef UINT DSTU4145_NUMBER[DSTU4145_MAX_EC_LENGTH];

typedef struct
{
	DSTU4145_NUMBER dwX;
	DSTU4145_NUMBER dwY;
	DSTU4145_NUMBER dwN;
} DSTU4145_KEY_Q_DECOMPRESSED, *PDSTU4145_KEY_Q_DECOMPRESSED;

typedef struct
{
	UINT dwA;
	DSTU4145_NUMBER B;
	UINT dwM, dwK1, dwK2, dwK3;
	UINT dwCF;
} DSTU4145_PARAMETER_EC, *PDSTU4145_PARAMETER_EC;

typedef struct
{
	DSTU4145_NUMBER dwX;
	DSTU4145_NUMBER dwY;
	DSTU4145_NUMBER dwN;
	UINT dwBits;
} DSTU4145_PARAMETER_P_FULL, *PDSTU4145_PARAMETER_P_FULL;

typedef struct
{
	DSTU4145_NUMBER dwX;
	DSTU4145_NUMBER dwN;
	UINT dwBits;
} DSTU4145_PARAMETER_P, *PDSTU4145_PARAMETER_P;

typedef struct
{
	DSTU4145_PARAMETER_EC EC;
	DSTU4145_NUMBER U;
	DSTU4145_PARAMETER_P BasePoint;
	UINT dwBits;
} DSTU4145_PARAMETERS, *PDSTU4145_PARAMETERS;

typedef struct
{
	DSTU4145_NUMBER e;
	DSTU4145_NUMBER Fe;
} DSTU4145_PRESIGNATURE, *PDSTU4145_PRESIGNATURE;

typedef struct
{
	UINT dwM;
	UINT dwK1;
	UINT dwK2;
	UINT dwK3;
	UINT dwCF;
	UINT dwA;
	UINT dwBits;
	UINT dwReserved;
} DSTU4145_DENSE_PARAMETERS_DESC,
*PDSTU4145_DENSE_PARAMETERS_DESC;

typedef PVOID *PDSTU4145_STATE;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_PARAMETERS_TYPE_PARAMETERS 1
#define DSTU4145_PARAMETERS_TYPE_PARAMETER_EC 2
#define DSTU4145_PARAMETERS_TYPE_PARAMETER_P 3
#define DSTU4145_PARAMETERS_TYPE_PARAMETER_P_FULL 4
#define DSTU4145_PARAMETERS_TYPE_KEY_D 5
#define DSTU4145_PARAMETERS_TYPE_KEY_Q 6
#define DSTU4145_PARAMETERS_TYPE_KEY_Q_DECOMPRESSED 7
#define DSTU4145_PARAMETERS_TYPE_PRNG 8
#define DSTU4145_PARAMETERS_TYPE_SIGNATURE 9
#define DSTU4145_PARAMETERS_TYPE_SIGNATURE_R 10
#define DSTU4145_PARAMETERS_TYPE_SIGNATURE_S 11
#define DSTU4145_PARAMETERS_TYPE_HASH 12
#define DSTU4145_PARAMETERS_TYPE_PRESIGNATURE_E 13
#define DSTU4145_PARAMETERS_TYPE_NUMBER_U 14
#define DSTU4145_PARAMETERS_TYPE_NUMBER_LD 15
#define DSTU4145_PARAMETERS_TYPE_KEY_K 16
#define DSTU4145_PARAMETERS_TYPE_PRESIGNATURE 17
#define DSTU4145_PARAMETERS_TYPE_HASH_SIZE 18
#ifdef CAP_VERIFICATOR
#define DSTU4145_PARAMETERS_TYPE_N 19
#endif // CAP_VERIFICATOR
#define DSTU4145_PARAMETERS_TYPE_P_LENGTH 20
#ifdef CAP_VERIFICATOR
#define DSTU4145_PARAMETERS_TYPE_CHECK 21
#define DSTU4145_PARAMETERS_TYPE_STATE 22
#define DSTU4145_PARAMETERS_TYPE_PRESIGNATURE_FROM_ARRAY_0 23
#define DSTU4145_PARAMETERS_TYPE_KEY_Q_DECOMPRESSED_X 24
#define DSTU4145_PARAMETERS_TYPE_KEY_Q_DECOMPRESSED_Y 25
#endif // CAP_VERIFICATOR
#define DSTU4145_PARAMETERS_TYPE_KEY_Q_DECOMPRESSED_X_LENGTH 26
#define DSTU4145_PARAMETERS_TYPE_KEY_Q_DECOMPRESSED_Y_LENGTH 27
#define DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS 28
#define DSTU4145_PARAMETERS_TYPE_DENSE_KEY_D 29
#define DSTU4145_PARAMETERS_TYPE_DENSE_KEY_Q 30
#define DSTU4145_PARAMETERS_TYPE_DENSE_SIGNATURE 31

#define DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET 16

#ifdef CAP_VERIFICATOR
#define DSTU4145_SELFTESTING_SHORT_TEST_NORMAL 0x181
#define DSTU4145_SELFTESTING_FULL_TEST_NORMAL 0x1AF
#define DSTU4145_SELFTESTING_SHORT_TEST_POLYNOMIAL 0x180
#define DSTU4145_SELFTESTING_FULL_TEST_POLYNOMIAL 0x3AE
#endif // CAP_VERIFICATOR

#define DSTU4145_STATE_PARAMETER_EC_SETUPED 1
#define DSTU4145_STATE_PARAMETER_P_SETUPED 2
#define DSTU4145_STATE_PARAMETERS_SETUPED 3
#define DSTU4145_STATE_KEY_D_SETUPED 4
#define DSTU4145_STATE_KEY_Q_SETUPED 8
#define DSTU4145_STATE_PARAMETER_PRNG_SETUPED 0x10
#define DSTU4145_STATE_SIGNATURE_SETUPED 0x60
#define DSTU4145_STATE_SIGNATURE_R_SETUPED 0x20
#define DSTU4145_STATE_SIGNATURE_S_SETUPED 0x40
#define DSTU4145_STATE_HASH_SETUPED 0x80
#define DSTU4145_STATE_PRESIGNATURE_SETUPED 0x100
#define DSTU4145_STATE_NUMBER_U_SETUPED 0x200
#define DSTU4145_STATE_KEY_K_SETUPED 0x400
#define DSTU4145_STATE_NUMBER_LD_SETUPED 0x800

#define DSTU4145_FLAG_GENERATE_KEY_K 0
#define DSTU4145_FLAG_GENERATE_KEY_D 1
#define DSTU4145_FLAG_GENERATE_KEY_Q 2
#define DSTU4145_FLAG_GENERATE_KEYS 3
#define DSTU4145_FLAG_GENERATE_PARAMETER_P 4
#define DSTU4145_FLAG_GENERATE_PARAMETER_P_FROM_U 5
#define DSTU4145_FLAG_GENERATE_PRESIGNATURES 6
#define DSTU4145_FLAG_FILL_PRESIGNATURE 7
#define DSTU4145_FLAG_GET_RS_FROM_D 8
#define DSTU4145_FLAG_GET_D_FROM_RS 9
#define DSTU4145_FLAG_CLEAR_PRESIGNATURE 10
#define DSTU4145_FLAG_GENERATE_PRESIGNATURE 11
#ifdef CAP_VERIFICATOR
#define DSTU4145_FLAG_GENERATE_PARAMETER_P_FROM_N 12
#endif // CAP_VERIFICATOR

#define DSTU4145_DENSE_NUMBER_SIZE(M) ((M + 7) / 8)
#define DSTU4145_DENSE_SIGNATURE_SIZE(M) \
	(2 * DSTU4145_DENSE_NUMBER_SIZE(M))
#define DSTU4145_DENSE_PARAMETERS_SIZE(M) \
	(3 * DSTU4145_DENSE_NUMBER_SIZE(M))

#define DSTU4145_DENSE_PARAMETERS_M(DenseParams) \
	(((PBYTE) DenseParams)[0] | \
	(((PBYTE) DenseParams)[1] << 8) | \
	(((PBYTE) DenseParams)[2] << 16) | \
	(((PBYTE) DenseParams)[3] << 24))

#define DSTU4145_DENSE_PARAMETERS_BITS(DenseParams) \
	(((PBYTE) DenseParams)[24] | \
	(((PBYTE) DenseParams)[25] << 8) | \
	(((PBYTE) DenseParams)[26] << 16) | \
	(((PBYTE) DenseParams)[27] << 24))

#define DSTU4145_SET_DENSE_PARAMETERS_BITS(DenseParams, Bits) \
	((PBYTE) DenseParams)[24] = Bits & 0xFF; \
	((PBYTE) DenseParams)[25] = (Bits >> 8) & 0xFF; \
	((PBYTE) DenseParams)[26] = (Bits >> 16) & 0xFF; \
	((PBYTE) DenseParams)[27] = (Bits >> 24) & 0XFF;

//----------------------------------------------------------------------------------------------------------------------

typedef BYTE ECDH_EXTENDED_DATA[8];

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_ECDH_UA
typedef BYTE GOST28147_WRAPED_KEY[sizeof(GOST28147_IV) +
	sizeof(GOST28147_KEY) + sizeof(GOST28147_MAC)];
#endif // CSP_ECDH_UA

//----------------------------------------------------------------------------------------------------------------------

typedef PVOID *PDSTU7624_STATE;

typedef BYTE DSTU7624_SBOX[1024];

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_KEY_128 128
#define DSTU7624_KEY_256 256
#define DSTU7624_KEY_512 512

#define DSTU7624_KEY_128_LENGTH 16
#define DSTU7624_KEY_256_LENGTH 32
#define DSTU7624_KEY_512_LENGTH 64

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_BLOCK_128 128
#define DSTU7624_BLOCK_256 256
#define DSTU7624_BLOCK_512 512

#define DSTU7624_BLOCK_128_LENGTH 16
#define DSTU7624_BLOCK_256_LENGTH 32
#define DSTU7624_BLOCK_512_LENGTH 64

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_IV_128_LENGTH DSTU7624_BLOCK_128_LENGTH
#define DSTU7624_IV_256_LENGTH DSTU7624_BLOCK_256_LENGTH
#define DSTU7624_IV_512_LENGTH DSTU7624_BLOCK_512_LENGTH

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_MAC_64_LENGTH 8
#define DSTU7624_MAC_128_LENGTH DSTU7624_BLOCK_128_LENGTH
#define DSTU7624_MAC_256_LENGTH DSTU7624_BLOCK_256_LENGTH
#define DSTU7624_MAC_512_LENGTH DSTU7624_BLOCK_512_LENGTH

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_G_BITS_1 1
#define DSTU7624_G_BITS_8 8
#define DSTU7624_G_BITS_64 64
#define DSTU7624_G_BITS_128 DSTU7624_BLOCK_128
#define DSTU7624_G_BITS_256 DSTU7624_BLOCK_256
#define DSTU7624_G_BITS_512 DSTU7624_BLOCK_512

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU7624

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_PARAMETERS_TYPE_SBOX 1
#define DSTU7624_PARAMETERS_TYPE_BLOCK_SIZE 2
#define DSTU7624_PARAMETERS_TYPE_KEY_SIZE 3
#define DSTU7624_PARAMETERS_TYPE_KEYS 4
#define DSTU7624_PARAMETERS_TYPE_IV 5
#define DSTU7624_PARAMETERS_TYPE_MAC_SIZE 6
#define DSTU7624_PARAMETERS_TYPE_MAC 7
#ifdef CAP_VERIFICATOR
#define DSTU7624_PARAMETERS_TYPE_ROUND_KEYS 8
#define DSTU7624_PARAMETERS_TYPE_INVERSE_ROUND_KEYS 9
#endif // CAP_VERIFICATOR
#define DSTU7624_PARAMETERS_TYPE_STATE_SIZE 10
#define DSTU7624_PARAMETERS_TYPE_STATE 11
#define DSTU7624_PARAMETERS_TYPE_CTR 12

//----------------------------------------------------------------------------------------------------------------------

#endif // CSP_DSTU7624

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_ROUND_TO_BLOCK(DataBits, BlockBits) \
	(((DataBits) + (BlockBits) - 1) / (BlockBits)) * \
		(BlockBits)

#define DSTU7624_CBC_MODE_OUTPUT_DATA(DataBits, BlockBits) \
	DSTU7624_ROUND_TO_BLOCK(DataBits, BlockBits)

#define DSTU7624_CCM_MODE_OUTPUT_DATA_BITS(DataLength, MACLength) \
	((DataLength) + (MACLength))

#define DSTU7624_KW_MODE_OUTPUT_DATA_BITS(DataBits, BlockBits) \
	(((DataBits) % (BlockBits)) ? \
		((DataBits) - ((DataBits) % (BlockBits)) + \
			DSTU7624_ROUND_TO_BLOCK( \
				((DataBits) % (BlockBits)) + \
				(BlockBits) / 2 + 1, BlockBits) + (BlockBits)) : \
		((DataBits) + (BlockBits)))

//----------------------------------------------------------------------------------------------------------------------

typedef PVOID *PDSTU7564_STATE;

typedef BYTE DSTU7564_SBOX[1024];
typedef BYTE DSTU7564_HASH[64];

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_HASH_256 256
#define DSTU7564_HASH_384 384
#define DSTU7564_HASH_512 512

#define DSTU7564_HASH_256_LENGTH 32
#define DSTU7564_HASH_384_LENGTH 48
#define DSTU7564_HASH_512_LENGTH 64

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU7564

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_PARAMETERS_TYPE_SBOX 1
#define DSTU7564_PARAMETERS_TYPE_HASH_SIZE 2
#define DSTU7564_PARAMETERS_TYPE_HASH 3

//----------------------------------------------------------------------------------------------------------------------

#endif // CSP_DSTU7564

//----------------------------------------------------------------------------------------------------------------------

typedef PVOID *PDSTU7564_HMAC_STATE;

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_KDF_DSTU7564

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_HMAC_PARAMETERS_TYPE_SBOX 1
#define DSTU7564_HMAC_PARAMETERS_TYPE_HASH_BIT_LENGTH 2
#define DSTU7564_HMAC_PARAMETERS_TYPE_KEY 3
#define DSTU7564_HMAC_PARAMETERS_TYPE_PKCS_KEY_BIT_LENGTH 4
#define DSTU7564_HMAC_PARAMETERS_TYPE_PKCS_KEY 5
#define DSTU7564_HMAC_PARAMETERS_TYPE_HMAC 6

//----------------------------------------------------------------------------------------------------------------------

#endif // CSP_KDF_DSTU7564

//----------------------------------------------------------------------------------------------------------------------

typedef PVOID *PDSTU8845_STATE;

typedef BYTE DSTU8845_SBOX[1024];

//----------------------------------------------------------------------------------------------------------------------

#define DSTU8845_KEY_256 256
#define DSTU8845_KEY_512 512

#define DSTU8845_KEY_256_LENGTH 32
#define DSTU8845_KEY_512_LENGTH 64

//----------------------------------------------------------------------------------------------------------------------

#define DSTU8845_IV_256 256

#define DSTU8845_IV_256_LENGTH 32

typedef BYTE DSTU8845_IV[DSTU8845_IV_256_LENGTH];

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU8845

//----------------------------------------------------------------------------------------------------------------------

#define DSTU8845_PARAMETERS_TYPE_SBOX 1

#define DSTU8845_PARAMETERS_TYPE_KEY_SIZE 2
#define DSTU8845_PARAMETERS_TYPE_KEY 3

#define DSTU8845_PARAMETERS_TYPE_IV 4
#define DSTU8845_PARAMETERS_TYPE_IV_OFFSET 5
#define DSTU8845_PARAMETERS_TYPE_IV_PACKET_OFFSET 6
#define DSTU8845_PARAMETERS_TYPE_STATE_SIZE 7
#define DSTU8845_PARAMETERS_TYPE_STATE 8

//----------------------------------------------------------------------------------------------------------------------

#endif // CSP_DSTU8845

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_WRAPPED_KEY_LENGTH 96

//----------------------------------------------------------------------------------------------------------------------

#define AIS31_SEQUENCE_SIZE_BYTES	2500

//----------------------------------------------------------------------------------------------------------------------

#define BS_MIN_SEQUENCE_BYTES		4
#define BS_MAX_SEQUENCE_BYTES		(2 * 1024)

//----------------------------------------------------------------------------------------------------------------------

typedef PVOID BS_STATISTIC, *PBS_STATISTIC;

//======================================================================================================================

typedef BOOL (WINAPI *PDSTU4145_SELF_TEST)(
	UINT dwTestType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145SelfTest(
	UINT dwTestType);
#endif // PC_STATIC_LIBS

typedef PDSTU4145_STATE (WINAPI *PDSTU4145_ACQUIRE_STATE)(
	BOOL blChecked,
	UINT dwCountOfPreSignature);
#ifdef PC_STATIC_LIBS
EXTERN_C  PDSTU4145_STATE WINAPI DSTU4145AcquireState(
	BOOL blChecked,
	UINT dwCountOfPreSignature);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU4145_RELEASE_STATE)(
	PDSTU4145_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU4145ReleaseState(
	PDSTU4145_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_SET_STATE_PARAMETERS)(
	PDSTU4145_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145SetStateParameters(
	PDSTU4145_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_GET_STATE_PARAMETERS)(
	PDSTU4145_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145GetStateParameters(
	PDSTU4145_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_GENERATE_PARAMETERS)(
	PDSTU4145_STATE pState,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145GenerateParameters(
	PDSTU4145_STATE pState,
	UINT dwParametersType); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_SIGN_HASH)(
	PDSTU4145_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145SignHash(
	PDSTU4145_STATE pState); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_VERIFY_SIGNATURE)(
	PDSTU4145_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145VerifySignature(
	PDSTU4145_STATE pState); 
#endif // PC_STATIC_LIBS

typedef UINT (WINAPI *PDSTU4145_TRACE)(
   PDSTU4145_STATE pState,
   DSTU4145_NUMBER x);
#ifdef PC_STATIC_LIBS
EXTERN_C UINT WINAPI DSTU4145Trace(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER x);  
#endif // PC_STATIC_LIBS
	
typedef BOOL (WINAPI *PDSTU4145_HALF_TRACE)(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER x,
	DSTU4145_NUMBER z);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145HalfTrace(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER x,
	DSTU4145_NUMBER z); 
#endif // PC_STATIC_LIBS

typedef BYTE (WINAPI *PDSTU4145_SOLVE_QUAD_EQUAL)(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER u,
	DSTU4145_NUMBER w,
	DSTU4145_NUMBER z);
#ifdef PC_STATIC_LIBS
EXTERN_C BYTE WINAPI DSTU4145SolveQuadEqual(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER u,
	DSTU4145_NUMBER w,
	DSTU4145_NUMBER z); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_IS_DENSE_NUMBERS_SUPPORTED)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145IsDenseNumbersSupported();
#endif // PC_STATIC_LIBS

//----------------------------------------------------------------------------------------------------------------------

typedef BOOL (WINAPI *PDSTU4145_PSEUDO_RNG_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145PseudoRNGSelfTest();
#endif // PC_STATIC_LIBS

typedef PDSTU4145_PSEUDO_RNG_STATE (WINAPI *PDSTU4145_PSEUDO_RNG_INITIALIZE)(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox);
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU4145_PSEUDO_RNG_STATE WINAPI DSTU4145PseudoRNGInitialize(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_DEINITIALIZE)(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU4145PseudoRNGDeinitialize(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE)(
	PBYTE pbSequence,
	UINT dwBytes,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU4145PseudoRNGGenerateSequence(
	PBYTE pbSequence,
	UINT dwBytes,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU4145_COUPLE
typedef BOOL (WINAPI *PDSTU4145_COUPLE_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleSelfTest();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_COUPLE_GENERATE_COMMON_KEY_Q)(
	PDSTU4145_STATE pState2,
	DSTU4145_KEY_Q KeyQ1);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleMakeCommonKeyQ(
	PDSTU4145_STATE pState2,
	DSTU4145_KEY_Q KeyQ1);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_COUPLE_MAKE_SIGN_R)(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER R);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleMakeSignR(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER R);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_COUPLE_MAKE_COMMON_SIGN_R)(
	PDSTU4145_STATE pState2,
	DSTU4145_NUMBER R2,
	DSTU4145_NUMBER R1,
	DSTU4145_NUMBER CommonR);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleMakeCommonSignR(
	PDSTU4145_STATE pState2,
	DSTU4145_NUMBER R2,
	DSTU4145_NUMBER R1,
	DSTU4145_NUMBER CommonR);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_COUPLE_MAKE_SIGN_S)(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER CommonR,
	DSTU4145_NUMBER S);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleMakeSignS(
	PDSTU4145_STATE pState,
	DSTU4145_NUMBER CommonR,
	DSTU4145_NUMBER S);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_COUPLE_MAKE_COMMON_SIGN_S)(
	PDSTU4145_STATE pState2,
	DSTU4145_NUMBER S2,
	DSTU4145_NUMBER S1,
	DSTU4145_NUMBER CommonS);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleMakeCommonSignS(
	PDSTU4145_STATE pState2,
	DSTU4145_NUMBER S2,
	DSTU4145_NUMBER S1,
	DSTU4145_NUMBER CommonS);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_COUPLE_MAKE_COMMON_SIGN)(
	PDSTU4145_STATE pState2,
	DSTU4145_NUMBER CommonR,
	DSTU4145_NUMBER CommonS);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145CoupleMakeCommonSign(
	PDSTU4145_STATE pState2,
	DSTU4145_NUMBER CommonR,
	DSTU4145_NUMBER CommonS);
#endif // PC_STATIC_LIBS
#endif // CSP_DSTU4145_COUPLE

//----------------------------------------------------------------------------------------------------------------------

typedef BOOL (WINAPI *PECDH_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHSelfTest(
	BOOL blFullTest); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDH_CALCULATE_SHARED_KEY)(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_KEY pSharedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHCalculateSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_KEY pSharedKey); 
#endif // PC_STATIC_LIBS

#ifdef CSP_ECDH_UA
typedef BOOL (WINAPI *PECDH_UA_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHUASelfTest(
	BOOL blFullTest); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDH_UA_CALCULATE_SHARED_KEY)(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_KEY pSharedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHUACalculateSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_KEY pSharedKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_WRAP_SHARED_KEY)(
	GOST28147_KEY pSharedKey,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	PDSTU4145_PSEUDO_RNG_STATE pRNGState,
	GOST28147_WRAPED_KEY pWrappedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147WrapSharedKey(
	GOST28147_KEY pSharedKey,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	PDSTU4145_PSEUDO_RNG_STATE pRNGState,
	GOST28147_WRAPED_KEY pWrappedKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_UNWRAP_SHARED_KEY)(
	GOST28147_KEY pSharedKey,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147UnwrapSharedKey(
	GOST28147_KEY pSharedKey,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey); 
#endif // PC_STATIC_LIBS
#endif // CSP_ECDH_UA

//----------------------------------------------------------------------------------------------------------------------

typedef BOOL (WINAPI *PGOST28147_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147SelfTest(); 
#endif // PC_STATIC_LIBS

typedef PGOST28147_STATE (WINAPI *PGOST28147_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PGOST28147_STATE WINAPI GOST28147AcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PGOST28147_RELEASE_STATE)(
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI GOST28147ReleaseState(
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_SET_STATE_PARAMETERS)(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147SetStateParameters(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_GET_STATE_PARAMETERS)(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147GetStateParameters(
	PGOST28147_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_ENCRYPT_DATA_SS_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS 
EXTERN_C BOOL WINAPI GOST28147EncryptDataSSMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_DECRYPT_DATA_SS_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147DecryptDataSSMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_ENCRYPT_DATA_G_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147EncryptDataGMode(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_ENCRYPT_DATA_GOFB_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147EncryptDataGOFBMode(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_DECRYPT_DATA_GOFB_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147DecryptDataGOFBMode(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST28147_GET_DATA_MAC)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST28147GetDataMAC(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST28147_STATE pState); 
#endif // PC_STATIC_LIBS

//----------------------------------------------------------------------------------------------------------------------

typedef BOOL (WINAPI *PGOST34311_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311SelfTest();
#endif // PC_STATIC_LIBS

typedef PGOST34311_STATE (WINAPI *PGOST34311_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PGOST34311_STATE WINAPI GOST34311AcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PGOST34311_RELEASE_STATE)(
	PGOST34311_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI GOST34311ReleaseState(
	PGOST34311_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311_SET_STATE_PARAMETERS)(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311SetStateParameters(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311_GET_STATE_PARAMETERS)(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311GetStateParameters(
	PGOST34311_STATE pState,
	PVOID pvParameters,
	UINT dwParametersType); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311_HASH_DATA)(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST34311_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311HashData(
	PBYTE pbData,
	UINT dwDataBytes,
	PGOST34311_STATE pState); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311_FINALIZE_HASH)(
	UINT dwSubscribeBits,
	PGOST34311_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311FinalizeHash(
	UINT dwSubscribeBits,
	PGOST34311_STATE pState);
#endif // PC_STATIC_LIBS

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_KDF_UA
typedef BOOL (WINAPI *PGOST34311HMAC_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311HMACSelfTest();
#endif // PC_STATIC_LIBS

typedef PGOST34311HMAC_STATE (WINAPI *PGOST34311HMAC_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PGOST34311HMAC_STATE WINAPI GOST34311HMACAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PGOST34311HMAC_RELEASE_STATE)(
	PGOST34311HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI GOST34311HMACReleaseState(
	PGOST34311HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311HMAC_SET_STATE_PARAMETERS)(
	PGOST34311HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311HMACSetStateParameters(
	PGOST34311HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311HMAC_GET_STATE_PARAMETERS)(
	PGOST34311HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311HMACGetStateParameters(
	PGOST34311HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311HMAC_UPDATE_DATA)(
	PBYTE pbData,
	DWORD dwDataBytes,
	PGOST34311HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311HMACUpdateData(
	PBYTE pbData,
	DWORD dwDataBytes,
	PGOST34311HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PGOST34311HMAC_FINALIZE_DATA_MAC)(
	PGOST34311HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI GOST34311HMACFinalizeDataMac(
	PGOST34311HMAC_STATE pState);
#endif // PC_STATIC_LIBS

//----------------------------------------------------------------------------------------------------------------------

typedef BOOL (WINAPI *PPBKDF2_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDF2SelfTest();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPBKDF2_DERIVE_KEY)(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pPRFSBox,
	GOST34311_HASH pPRFInitHash,
	GOST28147_KEY pDerivedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDF2DeriveKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pPRFSBox,
	GOST34311_HASH pPRFInitHash,
	GOST28147_KEY pDerivedKey);
#endif // PC_STATIC_LIBS

//----------------------------------------------------------------------------------------------------------------------

typedef BOOL (WINAPI *PPBKDFMAC_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDFMACSelfTest();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPBKDFMAC_DERIVE_KEY)(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitHash,
	GOST28147_KEY pDerivedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PBKDFMACDeriveKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitHash,
	GOST28147_KEY pDerivedKey);
#endif // PC_STATIC_LIBS
#endif // CSP_KDF_UA

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_REINITIALIZE_PRNG
typedef BOOL (WINAPI *PDSTU4145_PSEUDO_RNG_REINITIALIZE)(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145PseudoRNGReinitialize(
	GOST28147_BLOCK S,
	GOST28147_BLOCK DateTime,
	GOST28147_KEY pKeyK,
	GOST28147_COMPRESSED_SBOX pSBox,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS
#endif // CSP_REINITIALIZE_PRNG

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_MULTI_ALGO_PRNG
typedef PDSTU4145_PSEUDO_RNG_STATE (
	WINAPI *PDSTU4145_PSEUDO_RNG_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU4145_PSEUDO_RNG_STATE WINAPI DSTU4145PseudoRNGAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_LOCK_STATE)(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU4145PseudoRNGLockState(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_UNLOCK_STATE)(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU4145PseudoRNGUnlockState(
	PDSTU4145_PSEUDO_RNG_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_PSEUDO_RNG_SET_STATE_PARAMETERS)(
	PDSTU4145_PSEUDO_RNG_STATE pState,
	PVOID pParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145PseudoRNGSetStateParameters(
	PDSTU4145_PSEUDO_RNG_STATE pState,
	PVOID pParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS
#endif // CSP_MULTI_ALGO_PRNG

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU7624
typedef BOOL (WINAPI *PDSTU7624_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624SelfTest();
#endif // PC_STATIC_LIBS

typedef PDSTU7624_STATE (WINAPI *PDSTU7624_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU7624_STATE WINAPI DSTU7624AcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU7624_RELEASE_STATE)(
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU7624ReleaseState(
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_SET_STATE_PARAMETERS)(
	PDSTU7624_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624SetStateParameters(
	PDSTU7624_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_GET_STATE_PARAMETERS)(
	PDSTU7624_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624GetStateParameters(
	PDSTU7624_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_ECB_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataECBMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_ECB_MODE)(
	PBYTE pbData,
	UINT dwDataBlocks,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataECBMode(
	PBYTE pbData,
	UINT dwDataBlocks,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_CTR_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataCTRMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_CTR_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataCTRMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_CFB_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT dwGBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataCFBMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT dwGBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_CFB_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT dwGBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataCFBMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT dwGBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_GET_DATA_CMAC)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624GetDataCMAC(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_CHECK_DATA_CMAC)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624CheckDataCMAC(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_CBC_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT64 dwOutputDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataCBCMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT64 dwOutputDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_CBC_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	BOOL bPadding,
	PUINT64 pdwOutputDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataCBCMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	BOOL bPadding,
	PUINT64 pdwOutputDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_OFB_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataOFBMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_OFB_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataOFBMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_GCM_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PBYTE pbPublicData,
	UINT64 dwPublicDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataGCMMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PBYTE pbPublicData,
	UINT64 dwPublicDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_GCM_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PBYTE pbPublicData,
	UINT64 dwPublicDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataGCMMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PBYTE pbPublicData,
	UINT64 dwPublicDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_GET_DATA_GMAC)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624GetDataGMAC(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_CHECK_DATA_GMAC)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624CheckDataGMAC(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_CCM_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	UINT dwOutputDataBytes,
	PBYTE pbPublicData,
	UINT dwPublicDataBytes,
	UINT dwDataLengthBytes,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataCCMMode(
	PBYTE pbData,
	UINT dwDataBytes,
	UINT dwOutputDataBytes,
	PBYTE pbPublicData,
	UINT dwPublicDataBytes,
	UINT dwDataLengthBytes,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_CCM_MODE)(
	PBYTE pbData,
	UINT dwDataBytes,
	PBYTE pbPublicData,
	UINT dwPublicDataBytes,
	UINT dwDataLengthBytes,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataCCMMode(
	PBYTE pbData,
	UINT dwDataBytes,
	PBYTE pbPublicData,
	UINT dwPublicDataBytes,
	UINT dwDataLengthBytes,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_XTS_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataXTSMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_XTS_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataXTSMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_ENCRYPT_DATA_KW_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT64 dwOutputDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624EncryptDataKWMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	UINT64 dwOutputDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_DECRYPT_DATA_KW_MODE)(
	PBYTE pbData,
	UINT64 dwDataBits,
	BOOL bPadding,
	PUINT64 pdwOutputDataBits,
	PDSTU7624_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624DecryptDataKWMode(
	PBYTE pbData,
	UINT64 dwDataBits,
	BOOL bPadding,
	PUINT64 pdwOutputDataBits,
	PDSTU7624_STATE pState);
#endif // PC_STATIC_LIBS
#endif // CSP_DSTU7624

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU7564
typedef BOOL (WINAPI *PDSTU7564_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564SelfTest();
#endif // PC_STATIC_LIBS

typedef PDSTU7564_STATE (WINAPI *PDSTU7564_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU7564_STATE WINAPI DSTU7564AcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU7564_RELEASE_STATE)(
	PDSTU7564_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU7564ReleaseState(
	PDSTU7564_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_SET_STATE_PARAMETERS)(
	PDSTU7564_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564SetStateParameters(
	PDSTU7564_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_GET_STATE_PARAMETERS)(
	PDSTU7564_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564GetStateParameters(
	PDSTU7564_STATE pState,
	PVOID pParameters,
	UINT dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_HASH_DATA)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7564_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564HashData(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7564_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_FINALIZE_HASH)(
	PDSTU7564_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564FinalizeHash(
	PDSTU7564_STATE pState);
#endif // PC_STATIC_LIBS
#endif // CSP_DSTU7564

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU8845
typedef BOOL (WINAPI *PDSTU8845_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU8845SelfTest();
#endif // PC_STATIC_LIBS

typedef PDSTU8845_STATE (WINAPI *PDSTU8845_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU8845_STATE WINAPI DSTU8845AcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU8845_RELEASE_STATE)(
	PDSTU8845_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU8845ReleaseState(
	PDSTU8845_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU8845_SET_STATE_PARAMETERS)(
	PDSTU8845_STATE pState,
	PVOID pParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU8845SetStateParameters(
	PDSTU8845_STATE pState,
	PVOID pParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU8845_GET_STATE_PARAMETERS)(
	PDSTU8845_STATE pState,
	PVOID pParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU8845GetStateParameters(
	PDSTU8845_STATE pState,
	PVOID pParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU8845_ENCRYPT_DATA)(
	PBYTE pbData,
	DWORD dwDataLength,
	PDSTU8845_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU8845EncryptData(
	PBYTE pbData,
	DWORD dwDataLength,
	PDSTU8845_STATE pState);
#endif // PC_STATIC_LIBS
#endif // CSP_DSTU8845

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_KDF_DSTU7564
typedef BOOL (WINAPI *PDSTU7564_HMAC_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564HMACSelfTest();
#endif // PC_STATIC_LIBS

typedef PDSTU7564_HMAC_STATE (WINAPI *PDSTU7564_HMAC_ACQUIRE_STATE)();
#ifdef PC_STATIC_LIBS
EXTERN_C PDSTU7564_HMAC_STATE WINAPI DSTU7564HMACAcquireState();
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU7564_HMAC_RELEASE_STATE)(
	PDSTU7564_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU7564HMACReleaseState(
	PDSTU7564_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_HMAC_SET_STATE_PARAMETERS)(
	PDSTU7564_HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564HMACSetStateParameters(
	PDSTU7564_HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_HMAC_GET_STATE_PARAMETERS)(
	PDSTU7564_HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564HMACGetStateParameters(
	PDSTU7564_HMAC_STATE pState,
	PVOID pvParameters,
	DWORD dwParametersType);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_HMAC_UPDATE_DATA)(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7564_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564HMACUpdateData(
	PBYTE pbData,
	UINT64 dwDataBits,
	PDSTU7564_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7564_HMAC_FINALIZE_DATA_MAC)(
	PDSTU7564_HMAC_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7564HMACFinalizeDataMac(
	PDSTU7564_HMAC_STATE pState);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS5_PBKDF2_DSTU7564_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS5PBKDF2DSTU7564SelfTest();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS5_PBKDF2_DSTU7564_DERIVE_KEY)(
	PBYTE pbPassword,
	DWORD dwPasswordBytes,
	PBYTE pbSalt,
	DWORD dwSaltBytes,
	DWORD dwIterationCount,
	DSTU7564_SBOX pPRFSBox,
	DWORD dwHashBits,
	PBYTE pbDerivedKey,
	DWORD dwDerivedKeyBytes);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS5PBKDF2DSTU7564DeriveKey(
	PBYTE pbPassword,
	DWORD dwPasswordBytes,
	PBYTE pbSalt,
	DWORD dwSaltBytes,
	DWORD dwIterationCount,
	DSTU7564_SBOX pPRFSBox,
	DWORD dwHashBits,
	PBYTE pbDerivedKey,
	DWORD dwDerivedKeyBytes);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_DSTU7564_SELF_TEST)();
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFDSTU7564SelfTest();
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PPKCS12_PBKDF_DSTU7564_DERIVE_KEY)(
	PBYTE pbPassword,
	DWORD dwPasswordBytes,
	PBYTE pbSalt,
	DWORD dwSaltBytes,
	DWORD dwIterationCount,
	DSTU7564_SBOX pPRFSBox,
	DWORD dwHashBits,
	PBYTE pbDerivedKey,
	DWORD dwDerivedKeyBytes);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI PKCS12PBKDFDSTU7564DeriveKey(
	PBYTE pbPassword,
	DWORD dwPasswordBytes,
	PBYTE pbSalt,
	DWORD dwSaltBytes,
	DWORD dwIterationCount,
	DSTU7564_SBOX pPRFSBox,
	DWORD dwHashBits,
	PBYTE pbDerivedKey,
	DWORD dwDerivedKeyBytes);
#endif // PC_STATIC_LIBS
#endif // CSP_KDF_DSTU7564

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_DSTU7624_WRAP
typedef BOOL (WINAPI *PECDH_DSTU_SELF_TEST)(
	BOOL blFullTest);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHDSTUSelfTest(
	BOOL blFullTest);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PECDH_KDF_DSTU7564_CALCULATE_SHARED_KEY)(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL bCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7564_SBOX pHashSBox,
	DWORD dwHashBitLength,
	PBYTE pSharedKey,
	DWORD dwSharedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI ECDHKDFDSTU7564CalculateSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL bCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7564_SBOX pHashSBox,
	DWORD dwHashBitLength,
	PBYTE pSharedKey,
	DWORD dwSharedKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_WRAP_SHARED_KEY)(
	PBYTE pSharedKey,
	DWORD dwSharedKey,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pIV,
	DWORD dwIV,
	PDSTU4145_PSEUDO_RNG_STATE pRNGState,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624WrapSharedKey(
	PBYTE pSharedKey,
	DWORD dwSharedKey,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pIV,
	DWORD dwIV,
	PDSTU4145_PSEUDO_RNG_STATE pRNGState,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU7624_UNWRAP_SHARED_KEY)(
	PBYTE pSharedKey,
	DWORD dwSharedKey,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU7624UnwrapSharedKey(
	PBYTE pSharedKey,
	DWORD dwSharedKey,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey);
#endif // PC_STATIC_LIBS

#endif // CSP_DSTU7624_WRAP

typedef BOOL (WINAPI *PECDH_KDF_DSTU7564_CALCULATE_DENSE_SHARED_KEY)(
	PBYTE pbDenseParameters,
	DWORD dwDenseParameters,
	PBYTE pbDenseKeyDa,
	DWORD dwDenseKeyDa,
	PBYTE pbDenseKeyQb,
	DWORD dwDenseKeyQb,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7564_SBOX pHashSBox,
	DWORD dwHashBitLength,
	PBYTE pSharedKey,
	DWORD dwSharedKey);
#ifdef PC_STATIC_LIBS
BOOL WINAPI ECDHKDFDSTU7564CalculateDenseSharedKey(
	PBYTE pbDenseParameters,
	DWORD dwDenseParameters,
	PBYTE pbDenseKeyDa,
	DWORD dwDenseKeyDa,
	PBYTE pbDenseKeyQb,
	DWORD dwDenseKeyQb,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7564_SBOX pHashSBox,
	DWORD dwHashBitLength,
	PBYTE pSharedKey,
	DWORD dwSharedKey);
#endif // PC_STATIC_LIBS

//======================================================================================================================

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

//----------------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------------

typedef UINT (WINAPI *PCRC32_COUNT)(
	PBYTE pbData,
	UINT cbData);
#ifdef PC_STATIC_LIBS
EXTERN_C UINT WINAPI CRC32Count(
	PBYTE pbData,
	UINT cbData);
#endif // PC_STATIC_LIBS

//======================================================================================================================

#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI CSPInitialize();
#endif // PC_STATIC_LIBS

//======================================================================================================================

typedef VOID (WINAPI *PCSP_FINALIZE)();
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI CSPFinalize();
#endif // PC_STATIC_LIBS

//======================================================================================================================

#ifdef CAP_VERIFICATOR
typedef UINT (WINAPI *PDSTU4145_P_POLINOM_TO_NUMBER) (
	DSTU4145_NUMBER x,
	DSTU4145_NUMBER n,
	DSTU4145_NUMBER z);
#ifdef PC_STATIC_LIBS
EXTERN_C UINT WINAPI DSTU4145PPolinomToNumber(
	DSTU4145_NUMBER x,
	DSTU4145_NUMBER n,
	DSTU4145_NUMBER z);
#endif // PC_STATIC_LIBS

typedef UINT (WINAPI *PDSTU4145_N_POLINOM_TO_NUMBER)(
	DSTU4145_NUMBER x,
	DSTU4145_NUMBER n,
	DSTU4145_NUMBER z);
#ifdef PC_STATIC_LIBS
EXTERN_C  UINT WINAPI DSTU4145NPolinomToNumber(
	DSTU4145_NUMBER x,
	DSTU4145_NUMBER n,
	DSTU4145_NUMBER z);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_SR_TO_D)(
	PUINT S,
	PUINT R,
	PUINT D,
	UINT dwLd);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145SRToD(
	PUINT S,
	PUINT R,
	PUINT D,
	UINT dwLd);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_IS_POLYNOM_PERMISSIBLE)(
	UINT m,
	UINT k3,
	UINT k2,
	UINT k1);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145IsPolynomPermissible(
	UINT m,
	UINT k3,
	UINT k2,
	UINT k1);
#endif // PC_STATIC_LIBS

typedef INT (WINAPI *PDSTU4145_CHECK_N)(
	DSTU4145_NUMBER n,
	UINT dwBlocks,
	UINT dwM);
#ifdef PC_STATIC_LIBS
EXTERN_C INT WINAPI DSTU4145CheckN(
	DSTU4145_NUMBER n,
	UINT dwBlocks,
	UINT dwM);
#endif // PC_STATIC_LIBS

typedef INT (WINAPI *PDSTU4145_TEST_ON_STANDART_PARAMETERS)();
#ifdef PC_STATIC_LIBS
EXTERN_C INT WINAPI DSTU4145TestOnStandartParameters();
#endif // PC_STATIC_LIBS

typedef INT (WINAPI *PDSTU4145_IS_IN_RANGE)(
	DSTU4145_NUMBER n, UINT dwM);
#ifdef PC_STATIC_LIBS
EXTERN_C INT WINAPI DSTU4145IsInRange(
	DSTU4145_NUMBER n, UINT dwM);
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_IS_PRIME)(
	PUINT n);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145IsPrime(
	PUINT n); 
#endif // PC_STATIC_LIBS

typedef BOOL (WINAPI *PDSTU4145_IS_MOV)(
	PUINT n,
	UINT dwM);
#ifdef PC_STATIC_LIBS
EXTERN_C BOOL WINAPI DSTU4145IsMOV(
	PUINT n,
	UINT dwM); 
#endif // PC_STATIC_LIBS

typedef VOID (WINAPI *PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE_INBITS)(
	PBYTE pbSequence,
	DWORD dwBits,
	PDSTU4145_PSEUDO_RNG_STATE pState);
#ifdef PC_STATIC_LIBS
EXTERN_C VOID WINAPI DSTU4145PseudoRNGGenerateSequenceInBits(
	PBYTE pbSequence,
	DWORD dwBits,
	PDSTU4145_PSEUDO_RNG_STATE pState); 
#endif // PC_STATIC_LIBS
#endif // CAP_VERIFICATOR

//======================================================================================================================

typedef struct
{
	PDSTU4145_SELF_TEST DSTU4145SelfTest;
	PDSTU4145_ACQUIRE_STATE DSTU4145AcquireState;
	PDSTU4145_RELEASE_STATE DSTU4145ReleaseState;
	PDSTU4145_SET_STATE_PARAMETERS DSTU4145SetStateParameters;
	PDSTU4145_GET_STATE_PARAMETERS DSTU4145GetStateParameters;
	PDSTU4145_GENERATE_PARAMETERS DSTU4145GenerateParameters;
	PDSTU4145_SIGN_HASH DSTU4145SignHash;
	PDSTU4145_VERIFY_SIGNATURE DSTU4145VerifySignature;
	PDSTU4145_TRACE DSTU4145Trace;
	PDSTU4145_HALF_TRACE DSTU4145HalfTrace;
	PDSTU4145_SOLVE_QUAD_EQUAL DSTU4145SolveQuadEqual;

	PDSTU4145_PSEUDO_RNG_SELF_TEST DSTU4145PseudoRNGSelfTest;
	PDSTU4145_PSEUDO_RNG_INITIALIZE DSTU4145PseudoRNGInitialize;
	PDSTU4145_PSEUDO_RNG_DEINITIALIZE DSTU4145PseudoRNGDeinitialize;
	PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE DSTU4145PseudoRNGGenerateSequence;

	PECDH_SELF_TEST ECDHSelfTest;
	PECDH_CALCULATE_SHARED_KEY ECDHCalculateSharedKey;

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

#ifdef CSP_ECDH_UA
	PECDH_UA_SELF_TEST ECDHUASelfTest;
	PECDH_UA_CALCULATE_SHARED_KEY ECDHUACalculateSharedKey;

	PGOST28147_WRAP_SHARED_KEY GOST28147WrapSharedKey;
	PGOST28147_UNWRAP_SHARED_KEY GOST28147UnwrapSharedKey;
#endif // CSP_ECDH_UA
} CSP_BASE_FUNCTIONS, *PCSP_BASE_FUNCTIONS;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	UINT nSize;
	UINT nReserved;

#ifdef CSP_KDF_UA
	PGOST34311HMAC_SELF_TEST GOST34311HMACSelfTest;
	PGOST34311HMAC_ACQUIRE_STATE GOST34311HMACAcquireState;
	PGOST34311HMAC_RELEASE_STATE GOST34311HMACReleaseState;
	PGOST34311HMAC_SET_STATE_PARAMETERS GOST34311HMACSetStateParameters;
	PGOST34311HMAC_GET_STATE_PARAMETERS GOST34311HMACGetStateParameters;
	PGOST34311HMAC_UPDATE_DATA GOST34311HMACUpdateData;
	PGOST34311HMAC_FINALIZE_DATA_MAC GOST34311HMACFinalizeDataMac;

	PPBKDF2_SELF_TEST PBKDF2SelfTest;
	PPBKDF2_DERIVE_KEY PBKDF2DeriveKey;

	PPBKDFMAC_SELF_TEST PBKDFMACSelfTest;
	PPBKDFMAC_DERIVE_KEY PBKDFMACDeriveKey;
#else // CSP_KDF_UA
	FARPROC GOST34311HMACSelfTest;
	FARPROC GOST34311HMACAcquireState;
	FARPROC GOST34311HMACReleaseState;
	FARPROC GOST34311HMACSetStateParameters;
	FARPROC GOST34311HMACGetStateParameters;
	FARPROC GOST34311HMACUpdateData;
	FARPROC GOST34311HMACFinalizeDataMac;

	FARPROC PBKDF2SelfTest;
	FARPROC PBKDF2DeriveKey;

	FARPROC PBKDFMACSelfTest;
	FARPROC PBKDFMACDeriveKey;
#endif // CSP_KDF_UA

#ifdef CSP_REINITIALIZE_PRNG
	PDSTU4145_PSEUDO_RNG_REINITIALIZE DSTU4145PseudoRNGReinitialize;
#else // CSP_REINITIALIZE_PRNG
	FARPROC DSTU4145PseudoRNGReinitialize;
#endif // CSP_REINITIALIZE_PRNG

#ifdef CSP_DSTU4145_COUPLE
	PDSTU4145_COUPLE_SELF_TEST DSTU4145CoupleSelfTest;
	PDSTU4145_COUPLE_GENERATE_COMMON_KEY_Q DSTU4145CoupleMakeCommonKeyQ;
	PDSTU4145_COUPLE_MAKE_SIGN_R DSTU4145CoupleMakeSignR;
	PDSTU4145_COUPLE_MAKE_COMMON_SIGN_R DSTU4145CoupleMakeCommonSignR;
	PDSTU4145_COUPLE_MAKE_SIGN_S DSTU4145CoupleMakeSignS;
	PDSTU4145_COUPLE_MAKE_COMMON_SIGN_S DSTU4145CoupleMakeCommonSignS;
	PDSTU4145_COUPLE_MAKE_COMMON_SIGN DSTU4145CoupleMakeCommonSign;
#else // CSP_DSTU4145_COUPLE
	FARPROC DSTU4145CoupleSelfTest;
	FARPROC DSTU4145CoupleMakeCommonKeyQ;
	FARPROC DSTU4145CoupleMakeSignR;
	FARPROC DSTU4145CoupleMakeCommonSignR;
	FARPROC DSTU4145CoupleMakeSignS;
	FARPROC DSTU4145CoupleMakeCommonSignS;
	FARPROC DSTU4145CoupleMakeCommonSign;
#endif // CSP_DSTU4145_COUPLE

#ifdef CSP_DSTU7624
	PDSTU7624_SELF_TEST DSTU7624SelfTest;
	PDSTU7624_ACQUIRE_STATE DSTU7624AcquireState;
	PDSTU7624_RELEASE_STATE DSTU7624ReleaseState;
	PDSTU7624_SET_STATE_PARAMETERS DSTU7624SetStateParameters;
	PDSTU7624_GET_STATE_PARAMETERS DSTU7624GetStateParameters;

	PDSTU7624_ENCRYPT_DATA_ECB_MODE DSTU7624EncryptDataECBMode;
	PDSTU7624_DECRYPT_DATA_ECB_MODE DSTU7624DecryptDataECBMode;
	PDSTU7624_ENCRYPT_DATA_CTR_MODE DSTU7624EncryptDataCTRMode;
	PDSTU7624_DECRYPT_DATA_CTR_MODE DSTU7624DecryptDataCTRMode;
	PDSTU7624_ENCRYPT_DATA_CFB_MODE DSTU7624EncryptDataCFBMode;
	PDSTU7624_DECRYPT_DATA_CFB_MODE DSTU7624DecryptDataCFBMode;
	PDSTU7624_GET_DATA_CMAC DSTU7624GetDataCMAC;
	PDSTU7624_CHECK_DATA_CMAC DSTU7624CheckDataCMAC;
	PDSTU7624_ENCRYPT_DATA_CBC_MODE DSTU7624EncryptDataCBCMode;
	PDSTU7624_DECRYPT_DATA_CBC_MODE DSTU7624DecryptDataCBCMode;
	PDSTU7624_ENCRYPT_DATA_OFB_MODE DSTU7624EncryptDataOFBMode;
	PDSTU7624_DECRYPT_DATA_OFB_MODE DSTU7624DecryptDataOFBMode;
	PDSTU7624_ENCRYPT_DATA_GCM_MODE DSTU7624EncryptDataGCMMode;
	PDSTU7624_DECRYPT_DATA_GCM_MODE DSTU7624DecryptDataGCMMode;
	PDSTU7624_GET_DATA_GMAC DSTU7624GetDataGMAC;
	PDSTU7624_CHECK_DATA_GMAC DSTU7624CheckDataGMAC;
	PDSTU7624_ENCRYPT_DATA_CCM_MODE DSTU7624EncryptDataCCMMode;
	PDSTU7624_DECRYPT_DATA_CCM_MODE DSTU7624DecryptDataCCMMode;
	PDSTU7624_ENCRYPT_DATA_XTS_MODE DSTU7624EncryptDataXTSMode;
	PDSTU7624_DECRYPT_DATA_XTS_MODE DSTU7624DecryptDataXTSMode;
	PDSTU7624_ENCRYPT_DATA_KW_MODE DSTU7624EncryptDataKWMode;
	PDSTU7624_DECRYPT_DATA_KW_MODE DSTU7624DecryptDataKWMode;
#else // CSP_DSTU7624
	FARPROC DSTU7624SelfTest;
	FARPROC DSTU7624AcquireState;
	FARPROC DSTU7624ReleaseState;
	FARPROC DSTU7624SetStateParameters;
	FARPROC DSTU7624GetStateParameters;

	FARPROC DSTU7624EncryptDataECBMode;
	FARPROC DSTU7624DecryptDataECBMode;
	FARPROC DSTU7624EncryptDataCTRMode;
	FARPROC DSTU7624DecryptDataCTRMode;
	FARPROC DSTU7624EncryptDataCFBMode;
	FARPROC DSTU7624DecryptDataCFBMode;
	FARPROC DSTU7624GetDataCMAC;
	FARPROC DSTU7624CheckDataCMAC;
	FARPROC DSTU7624EncryptDataCBCMode;
	FARPROC DSTU7624DecryptDataCBCMode;
	FARPROC DSTU7624EncryptDataOFBMode;
	FARPROC DSTU7624DecryptDataOFBMode;
	FARPROC DSTU7624EncryptDataGCMMode;
	FARPROC DSTU7624DecryptDataGCMMode;
	FARPROC DSTU7624GetDataGMAC;
	FARPROC DSTU7624CheckDataGMAC;
	FARPROC DSTU7624EncryptDataCCMMode;
	FARPROC DSTU7624DecryptDataCCMMode;
	FARPROC DSTU7624EncryptDataXTSMode;
	FARPROC DSTU7624DecryptDataXTSMode;
	FARPROC DSTU7624EncryptDataKWMode;
	FARPROC DSTU7624DecryptDataKWMode;
#endif // CSP_DSTU7624

#ifdef CSP_DSTU7564
	PDSTU7564_SELF_TEST DSTU7564SelfTest;
	PDSTU7564_ACQUIRE_STATE DSTU7564AcquireState;
	PDSTU7564_RELEASE_STATE DSTU7564ReleaseState;
	PDSTU7564_SET_STATE_PARAMETERS DSTU7564SetStateParameters;
	PDSTU7564_GET_STATE_PARAMETERS DSTU7564GetStateParameters;

	PDSTU7564_HASH_DATA DSTU7564HashData;
	PDSTU7564_FINALIZE_HASH DSTU7564FinalizeHash;
#else // CSP_DSTU7564
	FARPROC DSTU7564SelfTest;
	FARPROC DSTU7564AcquireState;
	FARPROC DSTU7564ReleaseState;
	FARPROC DSTU7564SetStateParameters;
	FARPROC DSTU7564GetStateParameters;

	FARPROC DSTU7564HashData;
	FARPROC DSTU7564FinalizeHash;
#endif // CSP_DSTU7564

#ifdef CSP_DSTU8845
	PDSTU8845_SELF_TEST DSTU8845SelfTest;
	PDSTU8845_ACQUIRE_STATE DSTU8845AcquireState;
	PDSTU8845_RELEASE_STATE DSTU8845ReleaseState;
	PDSTU8845_SET_STATE_PARAMETERS DSTU8845SetStateParameters;
	PDSTU8845_GET_STATE_PARAMETERS DSTU8845GetStateParameters;

	PDSTU8845_ENCRYPT_DATA DSTU8845EncryptData;
#else // CSP_DSTU8845
	FARPROC DSTU8845SelfTest;
	FARPROC DSTU8845AcquireState;
	FARPROC DSTU8845ReleaseState;
	FARPROC DSTU8845SetStateParameters;
	FARPROC DSTU8845GetStateParameters;

	FARPROC DSTU8845EncryptData;
#endif // CSP_DSTU8845

#ifdef CSP_KDF_DSTU7564
	PDSTU7564_HMAC_SELF_TEST DSTU7564HMACSelfTest;
	PDSTU7564_HMAC_ACQUIRE_STATE DSTU7564HMACAcquireState;
	PDSTU7564_HMAC_RELEASE_STATE DSTU7564HMACReleaseState;
	PDSTU7564_HMAC_SET_STATE_PARAMETERS DSTU7564HMACSetStateParameters;
	PDSTU7564_HMAC_GET_STATE_PARAMETERS DSTU7564HMACGetStateParameters;

	PDSTU7564_HMAC_UPDATE_DATA DSTU7564HMACUpdateData;
	PDSTU7564_HMAC_FINALIZE_DATA_MAC DSTU7564HMACFinalizeDataMac;

	PPKCS5_PBKDF2_DSTU7564_SELF_TEST PKCS5PBKDF2DSTU7564SelfTest;
	PPKCS5_PBKDF2_DSTU7564_DERIVE_KEY PKCS5PBKDF2DSTU7564DeriveKey;

	PPKCS12_PBKDF_DSTU7564_SELF_TEST PKCS12PBKDFDSTU7564SelfTest;
	PPKCS12_PBKDF_DSTU7564_DERIVE_KEY PKCS12PBKDFDSTU7564DeriveKey;
#else // CSP_KDF_DSTU7564
	FARPROC DSTU7564HMACSelfTest;
	FARPROC DSTU7564HMACAcquireState;
	FARPROC DSTU7564HMACReleaseState;
	FARPROC DSTU7564HMACSetStateParameters;
	FARPROC DSTU7564HMACGetStateParameters;

	FARPROC DSTU7564HMACUpdateData;
	FARPROC DSTU7564HMACFinalizeDataMac;

	FARPROC PKCS5PBKDF2DSTU7564SelfTest;
	FARPROC PKCS5PBKDF2DSTU7564DeriveKey;

	FARPROC PKCS12PBKDFDSTU7564SelfTest;
	FARPROC PKCS12PBKDFDSTU7564DeriveKey;
#endif // CSP_KDF_DSTU7564

#ifdef CSP_DSTU7624_WRAP
	PECDH_DSTU_SELF_TEST ECDHDSTUSelfTest;
	PECDH_KDF_DSTU7564_CALCULATE_SHARED_KEY
		ECDHKDFDSTU7564CalculateSharedKey;
	PDSTU7624_WRAP_SHARED_KEY DSTU7624WrapSharedKey;
	PDSTU7624_UNWRAP_SHARED_KEY DSTU7624UnwrapSharedKey;
#else // CSP_DSTU7624_WRAP
	FARPROC ECDHDSTUSelfTest;
	FARPROC ECDHKDFDSTU7564CalculateSharedKey;
	FARPROC DSTU7624WrapSharedKey;
	FARPROC DSTU7624UnwrapSharedKey;
#endif // CSP_DSTU7624_WRAP

#ifdef CSP_MULTI_ALGO_PRNG
	PDSTU4145_PSEUDO_RNG_ACQUIRE_STATE DSTU4145PseudoRNGAcquireState;
	PDSTU4145_PSEUDO_RNG_LOCK_STATE DSTU4145PseudoRNGLockState;
	PDSTU4145_PSEUDO_RNG_UNLOCK_STATE DSTU4145PseudoRNGUnlockState;
	PDSTU4145_PSEUDO_RNG_SET_STATE_PARAMETERS
		DSTU4145PseudoRNGSetStateParameters;
#else // CSP_MULTI_ALGO_PRNG
	FARPROC DSTU4145PseudoRNGAcquireState;
	FARPROC DSTU4145PseudoRNGLockState;
	FARPROC DSTU4145PseudoRNGUnlockState;
	FARPROC DSTU4145PseudoRNGSetStateParameters;
#endif // CSP_MULTI_ALGO_PRNG

	PDSTU4145_IS_DENSE_NUMBERS_SUPPORTED
		DSTU4145IsDenseNumbersSupported;
	PECDH_KDF_DSTU7564_CALCULATE_DENSE_SHARED_KEY
		ECDHKDFDSTU7564CalculateDenseSharedKey;
} CSP_BASE_FUNCTIONS_EX, *PCSP_BASE_FUNCTIONS_EX;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	PTSCG_IS_ENABLE TSCGIsEnable;
	PTSCG_GENERATE_SEQUENCE TSCGGenerateSequence;

	PBS_TEST_SEQUENCE BSTestSequence;
	PBS_RELEASE_STATISTIC BSReleaseStatistic;

	PCRC32_COUNT CRC32Count;
} CSP_EXTENSION_FUNCTIONS, *PCSP_EXTENSION_FUNCTIONS;

//----------------------------------------------------------------------------------------------------------------------

#ifdef CAP_VERIFICATOR
typedef struct
{
	PDSTU4145_P_POLINOM_TO_NUMBER DSTU4145PPolinomToNumber;
	PDSTU4145_N_POLINOM_TO_NUMBER DSTU4145NPolinomToNumber;
	PDSTU4145_SR_TO_D DSTU4145SRToD;
	PDSTU4145_IS_POLYNOM_PERMISSIBLE DSTU4145IsPolynomPermissible;
	PDSTU4145_CHECK_N DSTU4145CheckN;
	PDSTU4145_TEST_ON_STANDART_PARAMETERS 
		DSTU4145TestOnStandartParameters;
	PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE_INBITS 
		DSTU4145PseudoRNGGenerateSequenceInBits;
	PDSTU4145_IS_IN_RANGE DSTU4145IsInRange;
	PDSTU4145_IS_PRIME DSTU4145IsPrime;
	PDSTU4145_IS_MOV DSTU4145IsMOV;
} CSP_VERIFICATION_FUNCTIONS, *PCSP_VERIFICATION_FUNCTIONS;
#endif // CAP_VERIFICATOR

//======================================================================================================================

class CSPBase
{
private:
	HMODULE m_hBaseLibrary;
	HMODULE m_hExtensionLibrary;

public:
	CSP_BASE_FUNCTIONS F;
	CSP_EXTENSION_FUNCTIONS ExtensionF;

#ifdef CAP_VERIFICATOR
	CSP_VERIFICATION_FUNCTIONS VerificationF;
#endif // CAP_VERIFICATOR

public:
	CSPBase();
	~CSPBase();

public:
	BOOL WINAPI Load();
	VOID WINAPI Unload();

	BOOL WINAPI LoadEx(
		PCSP_BASE_FUNCTIONS_EX *ppBaseEx);
	VOID WINAPI UnloadEx(
		PCSP_BASE_FUNCTIONS_EX *ppBaseEx);
};

//======================================================================================================================

#endif // CSP_BASE_H
