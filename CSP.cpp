//======================================================================================================================

#include "CSP.h"

//======================================================================================================================

#define GOST28147_ACQUIRE_STATE() \
	PGOST28147_STATE pGOST28147State; \
	pGOST28147State = Base.F.GOST28147AcquireState(); \
	if(pGOST28147State == NULL) \
	return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define GOST28147_RELEASE_STATE() \
	Base.F.GOST28147ReleaseState(pGOST28147State);

//----------------------------------------------------------------------------------------------------------------------

#define GOST34311_ACQUIRE_STATE() \
	PGOST34311_STATE pGOST34311State; \
	pGOST34311State = Base.F.GOST34311AcquireState(); \
	if(pGOST34311State == NULL) \
	return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define GOST34311_RELEASE_STATE() \
	Base.F.GOST34311ReleaseState(pGOST34311State);

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_ACQUIRE_STATE_EX(WithCheck) \
	PDSTU4145_STATE pDSTU4145State; \
	pDSTU4145State = Base.F.DSTU4145AcquireState(WithCheck, 0); \
	if(pDSTU4145State == NULL) \
	return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_ACQUIRE_STATE() \
	DSTU4145_ACQUIRE_STATE_EX(FALSE)

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_ACQUIRE_STATE_WITH_CHECK() \
	DSTU4145_ACQUIRE_STATE_EX(TRUE)

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_RELEASE_STATE() \
	Base.F.DSTU4145ReleaseState(pDSTU4145State);

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_PRNG_INITIALIZE() \
	pPRNGState = Base.F.DSTU4145PseudoRNGInitialize(WorkS, \
	DateTime, Key, SBox); \
	if(pPRNGState == NULL) \
	return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU4145_PRNG_DEINITIALIZE() \
	if(pPRNGState != NULL) \
	{ \
	Base.F.DSTU4145PseudoRNGDeinitialize(pPRNGState); \
	pPRNGState = NULL; \
	}

//----------------------------------------------------------------------------------------------------------------------

#define GOST34311HMAC_ACQUIRE_STATE() \
	if(m_pBaseEx == NULL || m_pBaseEx->GOST34311HMACAcquireState == NULL) \
	return CSP_ERROR_PROGRAM_FAILURE; \
	PGOST34311HMAC_STATE pGOST34311HMACState; \
	pGOST34311HMACState = m_pBaseEx->GOST34311HMACAcquireState(); \
	if(pGOST34311HMACState == NULL) \
	return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define GOST34311HMAC_RELEASE_STATE() \
	if(m_pBaseEx == NULL || m_pBaseEx->GOST34311HMACReleaseState == NULL) \
	return CSP_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->GOST34311HMACReleaseState(pGOST34311HMACState);

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_ACQUIRE_STATE() \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU7564AcquireState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	PDSTU7564_STATE pDSTU7564State; \
	pDSTU7564State = m_pBaseEx->DSTU7564AcquireState(); \
	if(pDSTU7564State == NULL) \
		return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_RELEASE_STATE(pDSTU7564State) \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU7564ReleaseState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->DSTU7564ReleaseState(pDSTU7564State);

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_ACQUIRE_STATE() \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU7624AcquireState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	PDSTU7624_STATE pDSTU7624State; \
	pDSTU7624State = m_pBaseEx->DSTU7624AcquireState(); \
	if(pDSTU7624State == NULL) \
		return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7624_RELEASE_STATE(pDSTU7624State) \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU7624ReleaseState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->DSTU7624ReleaseState(pDSTU7624State);

//----------------------------------------------------------------------------------------------------------------------

#define DSTU8845_ACQUIRE_STATE() \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU8845AcquireState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	PDSTU8845_STATE pDSTU8845State; \
	pDSTU8845State = m_pBaseEx->DSTU8845AcquireState(); \
	if(pDSTU8845State == NULL) \
		return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU8845_RELEASE_STATE(pDSTU8845State) \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU8845ReleaseState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->DSTU8845ReleaseState(pDSTU8845State);

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_HMAC_ACQUIRE_STATE() \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU7564HMACAcquireState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	PDSTU7564_HMAC_STATE pDSTU7564HMACState; \
	pDSTU7564HMACState = m_pBaseEx->DSTU7564HMACAcquireState(); \
	if(pDSTU7564HMACState == NULL) \
		return CSP_ERROR_ALLOCATE_MEMORY;

//----------------------------------------------------------------------------------------------------------------------

#define DSTU7564_HMAC_RELEASE_STATE(pDSTU7564HMACState) \
	if(m_pBaseEx == NULL || m_pBaseEx->DSTU7564HMACReleaseState == NULL) \
		return CSP_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->DSTU7564HMACReleaseState(pDSTU7564HMACState);

//======================================================================================================================

#define CSP_BAD_HRNG_INITIALIZE_SEQUENCES_LIMIT	2
#define CSP_BAD_HRNG_SEQUENCES_LIMIT		16

//======================================================================================================================

#ifndef OS_NO_EXCEPTIONS
#define CSP_TRY() \
	__try {

#define CSP_CATCH() \
} __except(EXCEPTION_EXECUTE_HANDLER){ return; }

#define CSP_CATCH_DWORD() \
}__except(EXCEPTION_EXECUTE_HANDLER){ \
	return CSP_ERROR_PROGRAM_FAILURE; }
#else
#define CSP_TRY()
#define CSP_CATCH()
#define CSP_CATCH_DWORD()
#endif

//======================================================================================================================

#ifdef CSP_SBOX_UA

static GOST28147_COMPRESSED_SBOX DefaultPRNGSBox =
{
	0x8A, 0x09, 0xCD, 0x46, 0x9E, 0x6B, 0x74, 0xB5,
	0x2F, 0x31, 0x13, 0xFC, 0x57, 0xE0, 0xA8, 0xD2,
	0x3F, 0x86, 0xD5, 0x98, 0x6E, 0xBB, 0xFA, 0x04,
	0x2C, 0x50, 0xC3, 0xA7, 0x42, 0xE9, 0x11, 0x7D,
	0x2F, 0x88, 0x9E, 0x79, 0x57, 0xF2, 0x00, 0xBD,
	0xCC, 0x16, 0xD1, 0xE5, 0xAB, 0x34, 0x63, 0x4A,
	0x13, 0x28, 0x3B, 0xE5, 0x66, 0xD4, 0xBE, 0x8A,
	0xF2, 0xAC, 0xC1, 0x57, 0x79, 0x9F, 0x0D, 0x40
};

#else // CSP_SBOX_UA

static GOST28147_COMPRESSED_SBOX DefaultPRNGSBox =
{
	0xE4, 0xBA, 0x49, 0xC2, 0x6D, 0xD8, 0xF0, 0xAE,
	0x26, 0x3B, 0x81, 0x1C, 0x07, 0x7F, 0x55, 0x93,
	0x75, 0xD8, 0xA1, 0x1D, 0x0A, 0x83, 0x94, 0xF2,
	0xEE, 0x4F, 0x6C, 0xC7, 0xB6, 0x20, 0x59, 0x3B,
	0x46, 0xBC, 0xA7, 0x01, 0x75, 0x2F, 0x1D, 0xD8,
	0x34, 0x6A, 0x89, 0x5E, 0x90, 0xC3, 0xFB, 0xE2,
	0x1D, 0xFB, 0xD4, 0x01, 0x53, 0x7F, 0xA5, 0x49,
	0x90, 0x2A, 0x3E, 0xE7, 0x66, 0xB8, 0x82, 0xCC
};

#endif // CSP_SBOX_UA

//======================================================================================================================

typedef DWORD (WINAPI CSP::*PGENERATE_RPRN_BYTES)(
	PCSP_CTX pContext,
	PBYTE pbRPRNBytes,
	DWORD dwRPRNBytes);

//======================================================================================================================

BOOL				g_bNoCSPSelfTests = FALSE;

//======================================================================================================================

CSP::CSP()
{
	pPRNGState = NULL;

	m_pHardwareRNG = NULL;
	m_pHardwareCSP = NULL;

	m_dwState = 0;

	m_pBaseEx = NULL;

	m_pszParamsPassword = NULL;

	Parameters.SetCSP(this);
}

//----------------------------------------------------------------------------------------------------------------------

CSP::~CSP()
{
	DSTU4145_PRNG_DEINITIALIZE();

	if(m_dwState & CSP_STATE_LIBRARIES_LOADED)
	{
		DeleteCriticalSection(&m_CriticalSection);

		Base.UnloadEx(&m_pBaseEx);
		Base.Unload();
	}

	if (m_pszParamsPassword != NULL)
	{
		memset(m_pszParamsPassword, 0,
			strlen(m_pszParamsPassword));
		delete[] m_pszParamsPassword;
	}
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::Initialize()
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
	{
		if(!Base.Load())
			return CSP_ERROR_LOAD_CSP_LIBRARY;

#ifndef CSP_DISABLE_SELF_TESTS
		if(!g_bNoCSPSelfTests)
		{
			if(!Base.F.GOST28147SelfTest() ||
				!Base.F.GOST34311SelfTest() ||
				!Base.F.DSTU4145PseudoRNGSelfTest() ||
				!Base.F.DSTU4145SelfTest(0) ||
				!Base.F.ECDHSelfTest(TRUE))
			{
				return CSP_ERROR_LIBRARIES_CORRUPTED;
			}

#ifdef CSP_ECDH_UA
			if(!Base.F.ECDHUASelfTest(TRUE))
				return CSP_ERROR_LIBRARIES_CORRUPTED;
#endif // CSP_ECDH_UA
		}
#endif // CSP_DISABLE_SELF_TESTS

		InitializeCriticalSection(&m_CriticalSection);

		m_dwState |= CSP_STATE_LIBRARIES_LOADED;

		Base.LoadEx(&m_pBaseEx);

#ifndef CSP_DISABLE_SELF_TESTS
		if(!g_bNoCSPSelfTests)
		{
#ifdef CSP_DSTU4145_COUPLE
			if(m_pBaseEx == NULL ||
				m_pBaseEx->DSTU4145CoupleSelfTest == NULL)
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(!m_pBaseEx->DSTU4145CoupleSelfTest())
				return CSP_ERROR_LIBRARIES_CORRUPTED;
#endif // CSP_DSTU4145_COUPLE

#ifdef CSP_DSTU7624
			if(m_pBaseEx == NULL ||
				m_pBaseEx->DSTU7624SelfTest == NULL)
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(!m_pBaseEx->DSTU7624SelfTest())
				return CSP_ERROR_LIBRARIES_CORRUPTED;
#endif // CSP_DSTU7624

#ifdef CSP_DSTU7564
			if(m_pBaseEx == NULL ||
				m_pBaseEx->DSTU7564SelfTest == NULL)
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(!m_pBaseEx->DSTU7564SelfTest())
				return CSP_ERROR_LIBRARIES_CORRUPTED;
#endif // CSP_DSTU7564

#ifdef CSP_DSTU8845
			if(m_pBaseEx == NULL ||
				m_pBaseEx->DSTU8845SelfTest == NULL)
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(!m_pBaseEx->DSTU8845SelfTest())
				return CSP_ERROR_LIBRARIES_CORRUPTED;
#endif // CSP_DSTU8845

#ifdef CSP_KDF_DSTU7564
			if(m_pBaseEx == NULL ||
				m_pBaseEx->DSTU7564HMACSelfTest == NULL ||
				m_pBaseEx->PKCS5PBKDF2DSTU7564SelfTest == NULL ||
				m_pBaseEx->PKCS12PBKDFDSTU7564SelfTest == NULL)
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(!m_pBaseEx->DSTU7564HMACSelfTest() ||
				!m_pBaseEx->PKCS5PBKDF2DSTU7564SelfTest() ||
				!m_pBaseEx->PKCS12PBKDFDSTU7564SelfTest())
			{
				return CSP_ERROR_LIBRARIES_CORRUPTED;
			}
#endif // CSP_KDF_DSTU7564

#ifdef CSP_DSTU7624_WRAP
			if(m_pBaseEx == NULL ||
				m_pBaseEx->ECDHDSTUSelfTest == NULL)
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(!m_pBaseEx->ECDHDSTUSelfTest(TRUE))
				return CSP_ERROR_LIBRARIES_CORRUPTED;
#endif // CSP_DSTU7624_WRAP
		}
#endif // CSP_DISABLE_SELF_TESTS
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializePRNG(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ReinitializePRNGCtx(
		&Context, pSBox, pSeed, pKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	EnterCriticalSection(&m_CriticalSection);

	if (pPRNGState == NULL)
		pPRNGState = Context.pPRNGState;

	LeaveCriticalSection(&m_CriticalSection);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeHRNG(
	ICSPHardwareRNG *pHardwareRNG)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	SetHRNG(NULL);

	CSP_CTX_INITIALIZE(Context);
	Context.pHardwareRNG = pHardwareRNG;

	dwError = InitializeHRNGCtx(
		&Context);
	if (dwError != CSP_NO_ERROR)
		return dwError;

	return SetHRNG(pHardwareRNG);

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GeneratePRNSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = GeneratePRNSequenceCtx(
		&Context, pbSequence, dwSequence);
	if (dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateRNSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = GenerateRNSequenceCtx(
		&Context, pbSequence, dwSequence);
	if (dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateRPRNSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = GenerateRPRNSequenceCtx(
		&Context, pbSequence, dwSequence);
	if (dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ProtectData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_MAC pMAC,
	GOST28147_BLOCK pDataAligment,
	PDWORD pdwDataAligment,
	PCHAR pcPassword,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	GOST28147_ACQUIRE_STATE();
	GOST34311_ACQUIRE_STATE();

	if(pcPassword != NULL || pKey != NULL)
	{
		GOST34311_HASH Hash;

		if(pcPassword != NULL)
		{
			if(!Base.F.GOST34311SetStateParameters(pGOST34311State,
				(PVOID) pSBox, GOST34311_PARAMETERS_TYPE_SBOX) ||
				!Base.F.GOST34311SetStateParameters(pGOST34311State,
				(PVOID) pInitialHash, GOST34311_PARAMETERS_TYPE_HASH) ||
				!Base.F.GOST34311HashData((PBYTE) pcPassword,
				(DWORD) strlen(pcPassword), pGOST34311State) ||
				!Base.F.GOST34311FinalizeHash(0, pGOST34311State) ||
				!Base.F.GOST34311GetStateParameters(pGOST34311State,
				(PVOID) Hash, GOST34311_PARAMETERS_TYPE_HASH))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSP_ERROR_PROGRAM_FAILURE;
			}
		}

		if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
			(PVOID) pSBox, GOST28147_PARAMETERS_TYPE_SBOX))
		{
			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(pcPassword == NULL)
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) pKey, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSP_ERROR_PROGRAM_FAILURE;
			}
		}
		else
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) Hash, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
		}
	}

	if((dwData % sizeof(GOST28147_BLOCK)) == 0)
	{
		pbAlignedData = pbData;
		dwAlignedData = dwData;
	}
	else
	{
		dwAlignedData = ((dwData / sizeof(GOST28147_BLOCK)) + 1) * 
			sizeof(GOST28147_BLOCK);
		pbAlignedData = (PBYTE) malloc(dwAlignedData);
		if(pbAlignedData == NULL)
		{
			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSP_ERROR_ALLOCATE_MEMORY;
		}

		memset((PVOID) pbAlignedData, 0, dwAlignedData);
		memcpy((PVOID) pbAlignedData, (PVOID) pbData,
			dwData);
	}

	if(pcPassword  != NULL || pKey != NULL)
	{
		if(!Base.F.GOST28147GetDataMAC(pbAlignedData, dwData,
			pGOST28147State) ||
			!Base.F.GOST28147GetStateParameters(pGOST28147State,
			(PVOID) pMAC, GOST28147_PARAMETERS_TYPE_MAC) ||
			!Base.F.GOST28147EncryptDataSSMode(pbAlignedData,
			dwAlignedData /
			sizeof(GOST28147_BLOCK), pGOST28147State))
		{
			if((dwData % sizeof(GOST28147_BLOCK)) != 0)
				free((PVOID) pbAlignedData);

			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}
	else
		return CSP_ERROR_BAD_PARAMETERS;

	if((dwData % sizeof(GOST28147_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData,
			dwData);

		memset((PVOID) pDataAligment, 0, sizeof(GOST28147_BLOCK));

		*pdwDataAligment = dwAlignedData - dwData;
		memcpy((PVOID) pDataAligment,
			(PVOID) (pbAlignedData + dwData),
			*pdwDataAligment);
		free((PVOID) pbAlignedData);
	}
	else
		*pdwDataAligment = 0;

	GOST28147_RELEASE_STATE();
	GOST34311_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::UnprotectData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_MAC pMAC,
	GOST28147_BLOCK pDataAligment,
	DWORD dwDataAligment,
	PCHAR pcPassword,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	GOST28147_MAC MAC;
	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	GOST28147_ACQUIRE_STATE();
	GOST34311_ACQUIRE_STATE();

	if(pcPassword  != NULL || pKey != NULL)
	{
		GOST34311_HASH Hash;

		if(pcPassword != NULL)
		{
			if(!Base.F.GOST34311SetStateParameters(pGOST34311State,
				(PVOID) pSBox, GOST34311_PARAMETERS_TYPE_SBOX) ||
				!Base.F.GOST34311SetStateParameters(pGOST34311State,
				(PVOID) pInitialHash, GOST34311_PARAMETERS_TYPE_HASH) ||
				!Base.F.GOST34311HashData((PBYTE) pcPassword,
				(DWORD) strlen(pcPassword), pGOST34311State) ||
				!Base.F.GOST34311FinalizeHash(0, pGOST34311State) ||
				!Base.F.GOST34311GetStateParameters(pGOST34311State,
				(PVOID) Hash, GOST34311_PARAMETERS_TYPE_HASH))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSP_ERROR_PROGRAM_FAILURE;
			}
		}

		if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
			(PVOID) pSBox, GOST28147_PARAMETERS_TYPE_SBOX))
		{
			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(pcPassword == NULL)
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) pKey, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSP_ERROR_PROGRAM_FAILURE;
			}
		}
		else
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) Hash, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
		}
	}

	if((dwData % sizeof(GOST28147_BLOCK)) == 0)
	{
		pbAlignedData = pbData;
		dwAlignedData = dwData;
	}
	else
	{
		dwAlignedData = ((dwData / sizeof(GOST28147_BLOCK)) + 1) *
			sizeof(GOST28147_BLOCK);
		pbAlignedData = (PBYTE) malloc(dwAlignedData);
		if(pbAlignedData == NULL)
		{
			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSP_ERROR_ALLOCATE_MEMORY;
		}

		memcpy((PVOID) pbAlignedData, (PVOID) pbData,
			dwData);
		memcpy((PVOID) (pbAlignedData + dwData),
			(PVOID) pDataAligment,
			dwDataAligment);
	}

	if(pcPassword  != NULL || pKey != NULL)
	{
		if(!Base.F.GOST28147DecryptDataSSMode(pbAlignedData, 
			dwAlignedData /
			sizeof(GOST28147_BLOCK), pGOST28147State) ||
			!Base.F.GOST28147GetDataMAC(pbAlignedData, dwData, 
			pGOST28147State) ||
			!Base.F.GOST28147GetStateParameters(pGOST28147State,
			(PVOID) MAC, GOST28147_PARAMETERS_TYPE_MAC))
		{
			if((dwData % sizeof(GOST28147_BLOCK)) != 0)
				free((PVOID) pbAlignedData);

			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(MAC[0] != pMAC[0])
		{
			if((dwData % sizeof(GOST28147_BLOCK)) != 0)
				free((PVOID) pbAlignedData);

			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSP_ERROR_DATA_CORRUPTED;
		}
	}
	else
		return CSP_ERROR_BAD_PARAMETERS;

	if((dwData % sizeof(GOST28147_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData,
			dwData);
		free((PVOID) pbAlignedData);
	}

	GOST28147_RELEASE_STATE();
	GOST34311_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::HashData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST34311_HASH pHash)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	GOST34311_ACQUIRE_STATE();

	if(!Base.F.GOST34311SetStateParameters(pGOST34311State,
		(PVOID) pSBox, GOST34311_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST34311SetStateParameters(pGOST34311State,
		(PVOID) pInitialHash, GOST34311_PARAMETERS_TYPE_HASH) ||
		!Base.F.GOST34311HashData((PBYTE) pbData,
		dwData, pGOST34311State) ||
		!Base.F.GOST34311FinalizeHash(0, pGOST34311State) ||
		!Base.F.GOST34311GetStateParameters(pGOST34311State,
		(PVOID) pHash, GOST34311_PARAMETERS_TYPE_HASH))
	{
		GOST34311_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST34311_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckDataHash(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST34311_HASH pHash)
{
	CSP_TRY();

	GOST34311_HASH Hash;
	DWORD dwError;

	if((dwError = HashData(pbData, dwData, pSBox, pInitialHash,
		Hash)) != CSP_NO_ERROR)
		return dwError;

	if(memcmp((PVOID) Hash, (PVOID) pHash, sizeof(GOST34311_HASH)))
	{
		memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));
		return CSP_ERROR_DATA_CORRUPTED;
	}

	memset((PVOID) Hash, 0, sizeof(GOST34311_HASH));

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::EncryptData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = EncryptDataCtx(
		&Context, pbData, dwData, pSBox,
		pKey, pIV);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DecryptData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	GOST28147_ACQUIRE_STATE();

	if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
		(PVOID) pSBox, GOST28147_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST28147SetStateParameters(pGOST28147State,
		(PVOID) pKey, GOST28147_PARAMETERS_TYPE_KEY) ||
		!Base.F.GOST28147SetStateParameters(pGOST28147State,
		(PVOID) pIV, GOST28147_PARAMETERS_TYPE_IV) ||
		!Base.F.GOST28147EncryptDataGMode(pbData, dwData,
		pGOST28147State))
	{
		GOST28147_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST28147_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

VOID WINAPI CSP::SetHardwareCSP(
	ICSPHardware *pHardwareCSP)
{
	CSP_TRY();

	m_pHardwareCSP = pHardwareCSP;

	if(pHardwareCSP != NULL)
		m_dwState |= CSP_STATE_HARDWARE_CSP_INITIALIZED;
	else
		m_dwState &= ~CSP_STATE_HARDWARE_CSP_INITIALIZED;

	CSP_CATCH();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SignHash(
	GOST34311_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = SignHashCtx(
		&Context, pHash, pParameterEC,
		pParameterP, pKeyD, pSignature);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::VerifySignature(
	GOST34311_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = VerifySignatureCtx(
		&Context, pHash, pParameterEC,
		pParameterP, pKeyQ, pSignature);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ProtectSharedData(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_MAC pMAC)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ProtectSharedDataCtx(
		&Context, pParameterEC, pParameterP,
		pKeyDa, pKeyQb, pData, pSBox, pInitialHash,
		pbData, dwData, pMAC);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::UnprotectSharedData(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_MAC pMAC)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = UnprotectSharedDataCtx(
		&Context, pParameterEC, pParameterP,
		pKeyDa, pKeyQb, pData, pSBox, pInitialHash,
		pbData, dwData, pMAC);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateDSKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = GenerateDSKeysCtx(
		&Context, pParameterEC, pParameterP,
		pKeyD, pKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateKEPKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = GenerateKEPKeysCtx(
		&Context, pParameterEC, pParameterP,
		pKeyD, pKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckDSKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CheckDSKeysCtx(
		&Context, pParameterEC, pParameterP,
		pKeyD, pKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckKEPKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CheckKEPKeysCtx(
		&Context, pParameterEC, pParameterP,
		pKeyD, pKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckDSParameters(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP)
{
	CSP_TRY();

	DWORD dwError;

	dwError = RestoreParameters(
		pParameterEC, pParameterP, TRUE);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckKEPParameters(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP)
{
	return CheckDSParameters(
		pParameterEC, pParameterP);
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeHashData(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	PGOST34311_STATE *ppGOST34311State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	*ppGOST34311State = Base.F.GOST34311AcquireState();
	if(!*ppGOST34311State)
		return CSP_ERROR_ALLOCATE_MEMORY;

	if(!Base.F.GOST34311SetStateParameters(
			*ppGOST34311State, (PVOID) pSBox,
			GOST34311_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST34311SetStateParameters(
			*ppGOST34311State, (PVOID) pInitialHash,
			GOST34311_PARAMETERS_TYPE_HASH))
	{
		Base.F.GOST34311ReleaseState(*ppGOST34311State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueHashData(
	PBYTE pbData,
	DWORD dwData,
	PGOST34311_STATE *ppGOST34311State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(!Base.F.GOST34311HashData(
			(PBYTE) pbData, dwData, *ppGOST34311State))
	{
		Base.F.GOST34311ReleaseState(*ppGOST34311State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeHashData(
	GOST34311_HASH pHash,
	PGOST34311_STATE *ppGOST34311State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(!Base.F.GOST34311FinalizeHash(
			0, *ppGOST34311State) ||
		!Base.F.GOST34311GetStateParameters(
			*ppGOST34311State, (PVOID) pHash,
			GOST34311_PARAMETERS_TYPE_HASH))
	{
		Base.F.GOST34311ReleaseState(*ppGOST34311State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	Base.F.GOST34311ReleaseState(*ppGOST34311State);
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_HARDWARE_ENCRYPTION
BOOL CSPIsHardwareEncryptionKey(
	GOST28147_KEY pKey)
{
	DWORD dwBlock =
		sizeof(GOST28147_KEY) / sizeof(UINT);

	for(; dwBlock > 1; dwBlock--)
	{
		if(pKey[dwBlock - 1] != 0)
			return FALSE;
	}

	return TRUE;
}
#endif // CSP_HARDWARE_ENCRYPTION

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeEncryptData(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKeyAndIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = InitializeEncryptDataCtx(
		&Context, pSBox, pKey, pIV,
		blGenerateKeyAndIV, ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ContinueEncryptDataCtx(
		&Context, pbData, dwData,
		ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueEncryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	DWORDLONG dwlDataOffset,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ContinueEncryptDataByOffsetCtx(
		&Context, pbData, dwData,
		dwlDataOffset, ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeEncryptData(
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = FinalizeEncryptDataCtx(
		&Context, ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeDecryptData(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = InitializeDecryptDataCtx(
		&Context, pSBox, pKey, pIV,
		ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueDecryptData(
	PBYTE pbData,
	DWORD dwData,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ContinueDecryptDataCtx(
		&Context, pbData, dwData,
		ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueDecryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	DWORDLONG dwlDataOffset,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ContinueDecryptDataByOffsetCtx(
		&Context, pbData, dwData,
		dwlDataOffset, ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeDecryptData(
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = FinalizeDecryptDataCtx(
		&Context, ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::HashKEPKey(
	DSTU4145_KEY_D pKeyD,
	DWORD dwBits,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST34311_HASH pHash)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = HashKEPKeyCtx(
		&Context, pKeyD, dwBits,
		pSBox, pInitialHash, pHash);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SetSBoxes(
	GOST28147_COMPRESSED_SBOX pEncryptionSBox,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST28147_COMPRESSED_SBOX pECDHSBox,
	GOST28147_COMPRESSED_SBOX pPRNGSBox)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = SetSBoxesCtx(
		&Context, pEncryptionSBox,
		pHashSBox, pECDHSBox, pPRNGSBox);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_GOST28147_CFB
DWORD WINAPI CSP::EncryptDataFeedback(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = EncryptDataFeedbackCtx(
		&Context, pbData, dwData,
		pSBox, pKey, pIV);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DecryptDataFeedback(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	GOST28147_ACQUIRE_STATE();

	if(!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pSBox,
			GOST28147_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pKey,
			GOST28147_PARAMETERS_TYPE_KEY) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pIV,
			GOST28147_PARAMETERS_TYPE_IV) ||
		!Base.F.GOST28147DecryptDataGOFBMode(
			pbData, dwData, pGOST28147State))
	{
		GOST28147_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST28147_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeEncryptDataFeedback(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKeyAndIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = InitializeEncryptDataFeedbackCtx(
		&Context, pSBox, pKey, pIV,
		blGenerateKeyAndIV, ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueEncryptDataFeedback(
	PBYTE pbData,
	DWORD dwData,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(!Base.F.GOST28147EncryptDataGOFBMode(
			pbData, dwData, *ppGOST28147State))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeEncryptDataFeedback(
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	return FinalizeEncryptData(ppGOST28147State);

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeDecryptDataFeedback(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	return InitializeDecryptData(pSBox, pKey, pIV,
		ppGOST28147State);

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueDecryptDataFeedback(
	PBYTE pbData,
	DWORD dwData,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(!Base.F.GOST28147DecryptDataGOFBMode(
			pbData, dwData, *ppGOST28147State))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeDecryptDataFeedback(
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	return FinalizeDecryptData(ppGOST28147State);

	CSP_CATCH_DWORD();
}
#endif // CSP_GOST28147_CFB

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_ECDH_UA
DWORD WINAPI CSP::WrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_KEY pKey,
	GOST28147_WRAPED_KEY pWrappedKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = WrapSharedKeyCtx(
		&Context, pParameterEC, pParameterP,
		pKeyDa, pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo, pHashSBox,
		pInitialHash, pWrapSBox, pKey,
		pWrappedKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::UnwrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = UnwrapSharedKeyCtx(
		&Context, pParameterEC, pParameterP,
		pKeyDa, pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo, pHashSBox,
		pInitialHash, pWrapSBox, pWrappedKey,
		pKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD()
}
#endif // CSP_ECDH_UA

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::EncryptDataFeedbackEx(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKey,
	BOOL blGenerateIV)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = EncryptDataFeedbackExCtx(
		&Context, pbData, dwData, pSBox,
		pKey, pIV, blGenerateKey, blGenerateIV);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeEncryptDataFeedbackEx(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKey,
	BOOL blGenerateIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = InitializeEncryptDataFeedbackExCtx(
		&Context, pSBox, pKey, pIV,
		blGenerateKey, blGenerateIV,
		ppGOST28147State);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DeriveProtectionKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pPRFSBox,
	GOST34311_HASH pPRFInitHash,
	GOST28147_KEY pDerivedKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DeriveProtectionKeyCtx(
		&Context, pbPassword, dwPassword,
		pbSalt, dwSalt, blGenerateSalt,
		dwCounter, pPRFSBox, pPRFInitHash,
		pDerivedKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD()
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DeriveMACKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pPRFSBox,
	GOST34311_HASH pPRFInitHash,
	GOST28147_KEY pDerivedKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DeriveMACKeyCtx(
		&Context, pbPassword, dwPassword,
		pbSalt, dwSalt, blGenerateSalt,
		dwCounter, pPRFSBox, pPRFInitHash,
		pDerivedKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD()
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GetDataHMAC(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_KEY pKey,
	GOST34311_HASH pHash)
{
	CSP_TRY();

#ifdef CSP_KDF_UA
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->GOST34311HMACSetStateParameters == NULL ||
		m_pBaseEx->GOST34311HMACUpdateData == NULL ||
		m_pBaseEx->GOST34311HMACFinalizeDataMac == NULL ||
		m_pBaseEx->GOST34311HMACGetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST34311HMAC_ACQUIRE_STATE();

	if(!m_pBaseEx->GOST34311HMACSetStateParameters(
			pGOST34311HMACState, (PVOID) pSBox,
			GOST34311HMAC_PARAMETERS_TYPE_SBOX) ||
		!m_pBaseEx->GOST34311HMACSetStateParameters(
			pGOST34311HMACState, (PVOID) pInitialHash,
			GOST34311HMAC_PARAMETERS_TYPE_HASH) ||
		!m_pBaseEx->GOST34311HMACSetStateParameters(
			pGOST34311HMACState, (PVOID) pKey,
			GOST34311HMAC_PARAMETERS_TYPE_KEY) ||
		!m_pBaseEx->GOST34311HMACUpdateData(
			(PBYTE) pbData, dwData, pGOST34311HMACState) ||
		!m_pBaseEx->GOST34311HMACFinalizeDataMac(
			pGOST34311HMACState) ||
		!m_pBaseEx->GOST34311HMACGetStateParameters(
			pGOST34311HMACState, (PVOID) pHash,
			GOST34311HMAC_PARAMETERS_TYPE_HMAC))
	{
		GOST34311HMAC_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST34311HMAC_RELEASE_STATE();

	return CSP_NO_ERROR;
#else // CSP_KDF_UA
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckDataHMAC(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_KEY pKey,
	GOST34311_HASH pHash)
{
	CSP_TRY();

#ifdef CSP_KDF_UA
	GOST34311_HASH Hash;
	DWORD dwError;

	dwError = GetDataHMAC(
		pbData, dwData, pSBox,
		pInitialHash, pKey, Hash);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	if(memcmp((PVOID) Hash, (PVOID) pHash,
			sizeof(GOST34311_HASH)))
	{
		memset((PVOID) Hash, 0,
			sizeof(GOST34311_HASH));

		return CSP_ERROR_DATA_CORRUPTED;
	}

	memset((PVOID) Hash, 0,
		sizeof(GOST34311_HASH));

	return CSP_NO_ERROR;
#else // CSP_KDF_UA
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RecoverDSPublicKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = RecoverDSPublicKeyCtx(
		&Context, pParameterEC, pParameterP,
		pKeyD, pKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RecoverKEPPublicKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = RecoverKEPPublicKeyCtx(
		&Context, pParameterEC, pParameterP,
		pKeyD, pKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SetParamsPassword(
	PCSTR pszParamsPassword)
{
	CSP_TRY();

	if (m_pszParamsPassword != NULL)
	{
		delete[] m_pszParamsPassword;
		m_pszParamsPassword = NULL;
	}

	if (pszParamsPassword != NULL)
	{
		m_pszParamsPassword = new CHAR[
			strlen(pszParamsPassword) + 1];
		if (m_pszParamsPassword == NULL)
			return CSP_ERROR_ALLOCATE_MEMORY;

		strcpy(m_pszParamsPassword,
			pszParamsPassword);
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

PCSTR WINAPI CSP::GetParamsPassword()
{
	return (PCSTR) m_pszParamsPassword;
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RestoreParameters(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	BOOL bWithCheck)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	DSTU4145_ACQUIRE_STATE_EX(bWithCheck);

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterEC,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterP,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &pParameterP->dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	DSTU4145_RELEASE_STATE();

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateRNSequenceCtx(
	PCSP_CTX pContext,
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSP_TRY();

	DWORD dwIterations = 0;
	DWORD dwBadIterationsLimit;
	PBS_STATISTIC pStatistic;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	dwBadIterationsLimit =
		(dwSequence != AIS31_SEQUENCE_SIZE_BYTES) ?
			CSP_BAD_HRNG_SEQUENCES_LIMIT :
			CSP_BAD_HRNG_INITIALIZE_SEQUENCES_LIMIT;

	while(TRUE)
	{
		if(!pContext->pHardwareRNG->GenerateSequence(
				pbSequence, dwSequence))
		{
			return CSP_ERROR_HRNG_FAILURE;
		}

		if((dwSequence < BS_MIN_SEQUENCE_BYTES ||
				dwSequence > BS_MAX_SEQUENCE_BYTES) &&
			dwSequence != AIS31_SEQUENCE_SIZE_BYTES)
		{
			break;
		}

		if(Base.ExtensionF.BSTestSequence(&pStatistic,
				pbSequence, dwSequence * 8))
		{
			Base.ExtensionF.BSReleaseStatistic(pStatistic);
			break;
		}

		Base.ExtensionF.BSReleaseStatistic(pStatistic);

		dwIterations++;

		if(dwIterations > dwBadIterationsLimit)
			return CSP_ERROR_BAD_HRNG_SEQUENCE;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GeneratePRNGParametersCtx(
	PCSP_CTX pContext,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey,
	GOST28147_BLOCK pWorkS)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL &&
		!Base.ExtensionF.TSCGIsEnable())
	{
		return CSP_ERROR_PRNG_CALL;
	}

	DWORD dwError;

	if(pSeed != NULL)
	{
		if(pContext->pHardwareRNG == NULL)
		{
			dwError = CSP_NO_ERROR;

			if(!Base.ExtensionF.TSCGGenerateSequence(
					(PBYTE) pSeed, sizeof(GOST28147_BLOCK)))
			{
				dwError = CSP_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(pContext,
				(PBYTE) pSeed, sizeof(GOST28147_BLOCK));
		}

		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(pKey != NULL)
	{
		if(pContext->pHardwareRNG == NULL)
		{
			dwError = CSP_NO_ERROR;

			if(!Base.ExtensionF.TSCGGenerateSequence(
					(PBYTE) pKey, sizeof(GOST28147_KEY)))
			{
				dwError = CSP_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(pContext,
				(PBYTE) pKey, sizeof(GOST28147_KEY));
		}

		if(dwError != CSP_NO_ERROR)
		{
			if(pSeed != NULL)
				memset((PVOID) pSeed, 0, sizeof(GOST28147_BLOCK));

			return dwError;
		}
	}

	if(pWorkS != NULL)
	{
		if(pContext->pHardwareRNG == NULL)
		{
			dwError = CSP_NO_ERROR;

			if(!Base.ExtensionF.TSCGGenerateSequence(
					(PBYTE) pWorkS, sizeof(GOST28147_BLOCK)))
			{
				dwError = CSP_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(pContext,
				(PBYTE) pWorkS, sizeof(GOST28147_BLOCK));
		}

		if(dwError != CSP_NO_ERROR)
		{
			if(pKey != NULL)
				memset((PVOID) pKey, 0, sizeof(GOST28147_KEY));
			if(pSeed != NULL)
				memset((PVOID) pSeed, 0, sizeof(GOST28147_BLOCK));

			return dwError;
		}
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializePRNGCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	GOST28147_BLOCK WorkS, DateTime;
	DWORD dwError;
	GOST28147_KEY Key;
	GOST28147_BLOCK Seed;
	GOST28147_COMPRESSED_SBOX SBox;
	PDSTU4145_PSEUDO_RNG_STATE pPRNGState;
	CSP_CTX Context;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pSBox == NULL)
	{
		memcpy((PVOID) SBox, (PVOID) DefaultPRNGSBox,
			sizeof(GOST28147_COMPRESSED_SBOX));
	}
	else
	{
		memcpy((PVOID) SBox, (PVOID) pSBox,
			sizeof(GOST28147_COMPRESSED_SBOX));
	}

	if(pSeed != NULL)
	{
		memcpy((PVOID) Seed, (PVOID) pSeed,
			sizeof(GOST28147_BLOCK));
	}

	if(pKey != NULL)
	{
		memcpy((PVOID) Key, (PVOID) pKey,
			sizeof(GOST28147_KEY));
	}

	if(pContext->pHardwareRNG != NULL ||
		this->pPRNGState == NULL)
	{
		dwError = GeneratePRNGParametersCtx(pContext,
			(pSeed == NULL) ? Seed : NULL,
			(pKey == NULL) ? Key : NULL, WorkS);
		if(dwError != CSP_NO_ERROR)
		{
			memset((PVOID) SBox, 0,
				sizeof(GOST28147_COMPRESSED_SBOX));

			return CSP_ERROR_PRNG_CALL;
		}
	}
	else
	{
		memset((PVOID) &Context, 0, sizeof(CSP_CTX));
		Context.pPRNGState = this->pPRNGState;

		if(pSeed == NULL)
		{
			dwError = GeneratePRNSequenceCtx(
				&Context, (PBYTE) Seed,
				sizeof(GOST28147_BLOCK));
			if(dwError != CSP_NO_ERROR)
			{
				memset((PVOID) SBox, 0,
					sizeof(GOST28147_COMPRESSED_SBOX));

				return CSP_ERROR_PRNG_CALL;
			}
		}

		if(pKey == NULL)
		{
			dwError = GeneratePRNSequenceCtx(
				&Context, (PBYTE) Key,
				sizeof(GOST28147_KEY));
			if(dwError != CSP_NO_ERROR)
			{
				memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
				memset((PVOID) SBox, 0,
					sizeof(GOST28147_COMPRESSED_SBOX));

				return CSP_ERROR_PRNG_CALL;
			}
		}

		dwError = GeneratePRNSequenceCtx(
			&Context, (PBYTE) WorkS,
			sizeof(GOST28147_BLOCK));
		if(dwError != CSP_NO_ERROR)
		{
			memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
			memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
			memset((PVOID) SBox, 0,
				sizeof(GOST28147_COMPRESSED_SBOX));

			return CSP_ERROR_PRNG_CALL;
		}
	}

	WorkS[0] ^= Seed[0];
	WorkS[1] ^= Seed[1];

	SYSTEMTIME stTime;
	FILETIME FileTime;

	GetSystemTime(&stTime);
	SystemTimeToFileTime(&stTime, &FileTime);

	DateTime[0] = FileTime.dwLowDateTime;
	DateTime[1] = FileTime.dwHighDateTime;

	pPRNGState = Base.F.DSTU4145PseudoRNGInitialize(
		WorkS, DateTime, Key, SBox);
	if(pPRNGState == NULL)
	{
		memset((PVOID) WorkS, 0, sizeof(GOST28147_BLOCK));
		memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
		memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
		memset((PVOID) SBox, 0,
			sizeof(GOST28147_COMPRESSED_SBOX));

		return CSP_ERROR_ALLOCATE_MEMORY;
	}

	memset((PVOID) WorkS, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
	memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) SBox, 0,
		sizeof(GOST28147_COMPRESSED_SBOX));

	pContext->pPRNGState = pPRNGState;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ReinitializePRNGCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	GOST28147_BLOCK WorkS, DateTime;
	DWORD dwError;
	GOST28147_KEY Key;
	GOST28147_BLOCK Seed;
	GOST28147_COMPRESSED_SBOX SBox;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
	{
		return InitializePRNGCtx(pContext,
			pSBox, pSeed, pKey);
	}

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGReinitialize == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pSBox == NULL)
	{
		memcpy((PVOID) SBox, (PVOID) DefaultPRNGSBox,
			sizeof(GOST28147_COMPRESSED_SBOX));
	}
	else
	{
		memcpy((PVOID) SBox, (PVOID) pSBox,
			sizeof(GOST28147_COMPRESSED_SBOX));
	}

	if(pSeed != NULL)
	{
		memcpy((PVOID) Seed, (PVOID) pSeed,
			sizeof(GOST28147_BLOCK));
	}

	if(pKey != NULL)
	{
		memcpy((PVOID) Key, (PVOID) pKey,
			sizeof(GOST28147_KEY));
	}

	dwError = GeneratePRNGParametersCtx(pContext,
		(pSeed == NULL) ? Seed : NULL,
		(pKey == NULL) ? Key : NULL, WorkS);
	if (dwError != CSP_NO_ERROR)
	{
		memset((PVOID) SBox, 0,
			sizeof(GOST28147_COMPRESSED_SBOX));

		return CSP_ERROR_PRNG_CALL;
	}

	WorkS[0] ^= Seed[0];
	WorkS[1] ^= Seed[1];

	SYSTEMTIME stTime;
	FILETIME FileTime;

	GetSystemTime(&stTime);
	SystemTimeToFileTime(&stTime, &FileTime);

	DateTime[0] = FileTime.dwLowDateTime;
	DateTime[1] = FileTime.dwHighDateTime;

	if(!m_pBaseEx->DSTU4145PseudoRNGReinitialize(
			WorkS, DateTime, Key, SBox, pContext->pPRNGState))
	{
		memset((PVOID) WorkS, 0, sizeof(GOST28147_BLOCK));
		memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
		memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
		memset((PVOID) SBox, 0,
			sizeof(GOST28147_COMPRESSED_SBOX));

		return CSP_ERROR_ALLOCATE_MEMORY;
	}

	memset((PVOID) WorkS, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
	memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) SBox, 0,
		sizeof(GOST28147_COMPRESSED_SBOX));

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeHRNGCtx(
	PCSP_CTX pContext)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL)
		return CSP_NO_ERROR;

	BYTE bSequence[AIS31_SEQUENCE_SIZE_BYTES];
	DWORD dwError;

	dwError = GenerateRNSequenceCtx(pContext,
		bSequence, AIS31_SEQUENCE_SIZE_BYTES);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GeneratePRNSequenceCtx(
	PCSP_CTX pContext,
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	Base.F.DSTU4145PseudoRNGGenerateSequence(
		pbSequence, dwSequence, pContext->pPRNGState);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateRPRNSequenceCtx(
	PCSP_CTX pContext,
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSP_TRY();

	DWORD dwError;

	if((dwError = GenerateRNSequenceCtx(pContext,
			pbSequence, dwSequence)) != CSP_NO_ERROR &&
		(dwError = GeneratePRNSequenceCtx(pContext,
			pbSequence, dwSequence)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::EncryptDataCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	dwError = GenerateRPRNSequenceCtx(pContext,
		(PBYTE) pKey, sizeof(GOST28147_KEY));
	if(dwError != CSP_NO_ERROR)
		return dwError;

	dwError = GenerateRPRNSequenceCtx(pContext,
		(PBYTE) pIV, sizeof(GOST28147_IV));
	if(dwError != CSP_NO_ERROR)
		return dwError;

	GOST28147_ACQUIRE_STATE();

	if(!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pSBox,
			GOST28147_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pKey,
			GOST28147_PARAMETERS_TYPE_KEY) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pIV,
			GOST28147_PARAMETERS_TYPE_IV) ||
		!Base.F.GOST28147EncryptDataGMode(
			pbData, dwData, pGOST28147State))
	{
		GOST28147_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST28147_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SignHashCtx(
	PCSP_CTX pContext,
	GOST34311_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	PC_PERFORMANCE_TEST_START(SignHash)

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->SignHash(
				pParameterEC, pParameterP, pHash,
				pSignature))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}

		PC_PERFORMANCE_TEST_STOP(SignHash)
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pHash,
				DSTU4145_PARAMETERS_TYPE_HASH) ||
			!Base.F.DSTU4145SignHash(pDSTU4145State) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pSignature,
				DSTU4145_PARAMETERS_TYPE_SIGNATURE) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_RELEASE_STATE();

		PC_PERFORMANCE_TEST_STOP(SignHash)
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::VerifySignatureCtx(
	PCSP_CTX pContext,
	GOST34311_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	PC_PERFORMANCE_TEST_START(VerifySignature)

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
	{
		return CSP_ERROR_LIBRARIES_NOT_LOADED;
	}

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	while(pContext->pHardwareCSP != NULL)
	{
		DSTU4145_PARAMETER_EC CompatibleParameterEC;
		DSTU4145_PARAMETER_P CompatibleParameterP;

		memset((PVOID) &CompatibleParameterEC, 0,
			sizeof(DSTU4145_PARAMETER_EC));
		memset((PVOID) &CompatibleParameterP, 0,
			sizeof(DSTU4145_PARAMETER_P));

		CompatibleParameterP.dwBits = 2;

		if(GenerateKEPKeysCtx(pContext,
				&CompatibleParameterEC,
				&CompatibleParameterP,
				NULL, NULL) != CSP_NO_ERROR)
		{
			break;
		}

		DWORD dwError;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		PVOID pvParameterEC;

		pvParameterEC = malloc(sizeof(DSTU4145_PARAMETER_EC) +
			sizeof(DSTU4145_KEY_Q));
		if(pvParameterEC == NULL)
			break;

		memset(pvParameterEC, 0, sizeof(DSTU4145_PARAMETER_EC) +
			sizeof(DSTU4145_KEY_Q));
		memcpy(pvParameterEC, (PVOID) pParameterEC,
			sizeof(DSTU4145_PARAMETER_EC));
		memcpy((PVOID) (((PBYTE) pvParameterEC) + 
			sizeof(DSTU4145_PARAMETER_EC)),
			(PVOID) pKeyQ, sizeof(DSTU4145_KEY_Q));

		((PDSTU4145_PARAMETER_EC) pvParameterEC)->dwCF =
			0xFFFFFFFF;

		if(!pContext->pHardwareCSP->SignHash(
				(PDSTU4145_PARAMETER_EC) pvParameterEC,
				pParameterP, pHash, pSignature))
		{
			free(pvParameterEC);
			return CSP_ERROR_BAD_SIGNATURE;
		}

		free(pvParameterEC);

		PC_PERFORMANCE_TEST_STOP(VerifySignature)

		return CSP_NO_ERROR;
	}

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterEC,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterP,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pKeyQ,
			DSTU4145_PARAMETERS_TYPE_KEY_Q) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pSignature,
			DSTU4145_PARAMETERS_TYPE_SIGNATURE))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pHash,
			DSTU4145_PARAMETERS_TYPE_HASH))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!Base.F.DSTU4145VerifySignature(pDSTU4145State))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_BAD_SIGNATURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(VerifySignature)

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ProtectSharedDataCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_MAC pMAC)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if((dwData % sizeof(GOST28147_BLOCK)) != 0)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwError;

	if(pMAC != NULL)
	{
		dwError = GenerateRPRNSequenceCtx(pContext,
			(PBYTE) pData, sizeof(ECDH_EXTENDED_DATA));
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(pKeyDa == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		if(pMAC == NULL)
		{
			DSTU4145_PARAMETER_EC CompatibleParameterEC;
			DSTU4145_PARAMETER_P CompatibleParameterP;

			memset((PVOID) &CompatibleParameterEC, 0,
				sizeof(DSTU4145_PARAMETER_EC));
			memset((PVOID) &CompatibleParameterP, 0,
				sizeof(DSTU4145_PARAMETER_P));

			CompatibleParameterP.dwBits = 3;

			if(GenerateKEPKeysCtx(pContext,
					&CompatibleParameterEC,
					&CompatibleParameterP,
					NULL, NULL) != CSP_NO_ERROR)
			{
				return CSP_ERROR_BAD_PARAMETERS;
			}
		}

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->ProtectSharedData(
				pParameterEC, pParameterP, pKeyQb, pData,
				pbData, dwData, pMAC))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		GOST28147_KEY Key;

		if(!Base.F.ECDHCalculateSharedKey(
				pParameterEC, pParameterP, pKeyDa,
				pKeyQb, pData, pSBox, pInitialHash,
				Key))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(pMAC == NULL)
		{
			memcpy((PVOID) pbData, (PVOID) Key,
				sizeof(GOST28147_KEY));
		}
		else
		{
			DWORD dwDataAligment = 0;

			dwError = ProtectData(
				pbData, dwData, pSBox, NULL, pMAC,
				NULL, &dwDataAligment, NULL, Key);
			if(dwError != CSP_NO_ERROR)
			{
				memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
				return dwError;
			}
		}

		memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::UnprotectSharedDataCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_MAC pMAC)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if((dwData % sizeof(GOST28147_BLOCK)) != 0)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwA;
	DWORD dwError;

	dwA = pParameterEC->dwA;

	if(pParameterEC->dwA & 0x80000000)
		pParameterEC->dwA &= (~0x80000000);

	if(pKeyDa == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pParameterEC->dwA = dwA;

		if(!pContext->pHardwareCSP->UnprotectSharedData(
				pParameterEC, pParameterP, pKeyQb, pData,
				pbData, dwData, pMAC))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		GOST28147_KEY Key;

		if(!Base.F.ECDHCalculateSharedKey(
				pParameterEC, pParameterP, pKeyDa,
				pKeyQb, pData, pSBox, pInitialHash,
				Key))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DWORD dwDataAligment = 0, dwError;

		dwError = UnprotectData(
			pbData, dwData, pSBox, NULL, pMAC,
			NULL, 0, NULL, Key);
		if(dwError != CSP_NO_ERROR)
		{
			memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
			return dwError;
		}

		memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateDSKeysCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL && pKeyQ == NULL &&
		pParameterEC->dwM == 0)
	{
		switch(pParameterP->dwBits)
		{
		case CSP_COMPATIBLE_LEVEL_KDF_UA:
#ifdef CSP_KDF_UA
			return CSP_NO_ERROR;
#else // CSP_KDF_UA
			return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

		case CSP_COMPATIBLE_LEVEL_RECOVER_PUBLIC_KEY:
			return CSP_NO_ERROR;

		case CSP_COMPATIBLE_LEVEL_PARAMS_PASSWORD:
			return CSP_NO_ERROR;

		case CSP_COMPATIBLE_LEVEL_CTX:
			return CSP_NO_ERROR;

		case CSP_COMPATIBLE_LEVEL_DSTU7624:
#ifdef CSP_DSTU7624
			return CSP_NO_ERROR;
#else // CSP_DSTU7624
			return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

		case CSP_COMPATIBLE_LEVEL_DSTU7564:
#ifdef CSP_DSTU7564
			return CSP_NO_ERROR;
#else // CSP_DSTU7564
			return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

		case CSP_COMPATIBLE_LEVEL_DSTU8845:
#ifdef CSP_DSTU8845
			return CSP_NO_ERROR;
#else // CSP_DSTU8845
			return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

		case CSP_COMPATIBLE_LEVEL_KDF_DSTU7564:
#ifdef CSP_KDF_DSTU7564
			return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
			return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

		case CSP_COMPATIBLE_LEVEL_DSTU7624_WRAP_KEY:
#ifdef CSP_DSTU7624_WRAP
			return CSP_NO_ERROR;
#else // CSP_DSTU7624_WRAP
			return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624_WRAP

		case CSP_COMPATIBLE_LEVEL_ITERATIVE_DSTU7624_CFB_MODE:
			return CSP_NO_ERROR;

		case CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA:
			return CSP_NO_ERROR;

		case CSP_COMPATIBLE_LEVEL_DENSE_NUMBERS:
			if(m_pBaseEx != NULL &&
				m_pBaseEx->DSTU4145IsDenseNumbersSupported &&
				m_pBaseEx->DSTU4145IsDenseNumbersSupported())
			{
				return CSP_NO_ERROR;
			}
			else
			{
				return CSP_ERROR_PROGRAM_FAILURE;
			}
		}
	}

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		if(pParameterEC->dwM != 0)
		{
			dwError = RestoreParameters(
				pParameterEC, pParameterP, FALSE);
			if(dwError != CSP_NO_ERROR)
				return dwError;
		}

		if(!pContext->pHardwareCSP->GenerateDSKeys(
				pParameterEC, pParameterP, pKeyQ))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145GenerateParameters(
				pDSTU4145State, DSTU4145_FLAG_GENERATE_KEYS) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pKeyQ,
				DSTU4145_PARAMETERS_TYPE_KEY_Q) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_RELEASE_STATE();
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateKEPKeysCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		if(pParameterEC->dwM != 0)
		{
			dwError = RestoreParameters(
				pParameterEC, pParameterP, FALSE);
			if(dwError != CSP_NO_ERROR)
				return dwError;
		}

		if(!pContext->pHardwareCSP->GenerateKEPKeys(
				pParameterEC, pParameterP, pKeyQ))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145GenerateParameters(
				pDSTU4145State, DSTU4145_FLAG_GENERATE_KEYS) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pKeyQ,
				DSTU4145_PARAMETERS_TYPE_KEY_Q) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_RELEASE_STATE();
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckDSKeysCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	DSTU4145_KEY_Q KeyQ;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, TRUE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->CheckDSKeys(
				pParameterEC, pParameterP, pKeyQ))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(pKeyQ != NULL)
		{
			if(!Base.F.DSTU4145SetStateParameters(
					pDSTU4145State, (PVOID) pKeyQ,
					DSTU4145_PARAMETERS_TYPE_KEY_Q))
			{
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_WRONG_PARAMETERS;
			}

			memset((PVOID) KeyQ, 0, sizeof(DSTU4145_KEY_Q));

			if(!Base.F.DSTU4145SetStateParameters(
					pDSTU4145State, (PVOID) pContext->pPRNGState,
					DSTU4145_PARAMETERS_TYPE_PRNG) ||
				!Base.F.DSTU4145GenerateParameters(
					pDSTU4145State, DSTU4145_FLAG_GENERATE_KEY_Q) ||
				!Base.F.DSTU4145GetStateParameters(
					pDSTU4145State, (PVOID) KeyQ,
					DSTU4145_PARAMETERS_TYPE_KEY_Q))
			{
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(memcmp((PVOID) pKeyQ, (PVOID) KeyQ,
					sizeof(DSTU4145_KEY_Q)))
			{
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_WRONG_PARAMETERS;
			}
		}

		DSTU4145_RELEASE_STATE();
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckKEPKeysCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	DSTU4145_KEY_Q KeyQ;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, TRUE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->CheckKEPKeys(
				pParameterEC, pParameterP, pKeyQ))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(pKeyQ != NULL)
		{
			if(!Base.F.DSTU4145SetStateParameters(
					pDSTU4145State, (PVOID) pKeyQ,
					DSTU4145_PARAMETERS_TYPE_KEY_Q))
			{
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_WRONG_PARAMETERS;
			}

			memset((PVOID) KeyQ, 0, sizeof(DSTU4145_KEY_Q));

			if(!Base.F.DSTU4145SetStateParameters(
					pDSTU4145State, (PVOID) pContext->pPRNGState,
					DSTU4145_PARAMETERS_TYPE_PRNG) ||
				!Base.F.DSTU4145GenerateParameters(
					pDSTU4145State, DSTU4145_FLAG_GENERATE_KEY_Q) ||
				!Base.F.DSTU4145GetStateParameters(
					pDSTU4145State, (PVOID) KeyQ,
					DSTU4145_PARAMETERS_TYPE_KEY_Q))
			{
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_PROGRAM_FAILURE;
			}

			if(memcmp((PVOID) pKeyQ, (PVOID) KeyQ,
					sizeof(DSTU4145_KEY_Q)))
			{
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_WRONG_PARAMETERS;
			}
		}

		DSTU4145_RELEASE_STATE();
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeEncryptDataCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKeyAndIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKey != NULL && pIV != NULL)
	{
#ifdef CSP_HARDWARE_ENCRYPTION
		if(!blGenerateKeyAndIV &&
			pContext->pHardwareCSP != NULL &&
			CSPIsHardwareEncryptionKey(pKey))
		{
			BOOL	bHardwareEncryption;

			CSP_CHECK_COMPATIBLE_CTX(this, pContext,
				CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
				bHardwareEncryption);
			if(!bHardwareEncryption)
				return CSP_ERROR_HARDWARE_CSP_FAILURE;

			if(!pContext->pHardwareCSP->InitializeEncryptData(
					pSBox, pKey, pIV, blGenerateKeyAndIV))
			{
				return CSP_ERROR_HARDWARE_CSP_FAILURE;
			}
		}
		else
		{
#endif // CSP_HARDWARE_ENCRYPTION
			if(blGenerateKeyAndIV)
			{
				dwError = GenerateRPRNSequenceCtx(
					pContext, (PBYTE) pKey,
					sizeof(GOST28147_KEY));
				if(dwError != CSP_NO_ERROR)
					return dwError;

				dwError = GenerateRPRNSequenceCtx(
					pContext, (PBYTE) pIV,
					sizeof(GOST28147_IV));
				if(dwError != CSP_NO_ERROR)
					return dwError;
			}
#ifdef CSP_HARDWARE_ENCRYPTION
		}
#endif // CSP_HARDWARE_ENCRYPTION
	}

	PGOST28147_STATE pGOST28147State;

	pGOST28147State = Base.F.GOST28147AcquireState();
	if(pGOST28147State == NULL)
		return CSP_ERROR_ALLOCATE_MEMORY;

	if(pKey != NULL && pIV != NULL)
	{
		if(!Base.F.GOST28147SetStateParameters(
				pGOST28147State, (PVOID) pSBox,
				GOST28147_PARAMETERS_TYPE_SBOX) ||
			!Base.F.GOST28147SetStateParameters(
				pGOST28147State, (PVOID) pKey,
				GOST28147_PARAMETERS_TYPE_KEY) ||
			!Base.F.GOST28147SetStateParameters(
				pGOST28147State, (PVOID) pIV,
				GOST28147_PARAMETERS_TYPE_IV))
		{
			Base.F.GOST28147ReleaseState(pGOST28147State);
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}
	else
	{
#ifdef CSP_HARDWARE_ENCRYPTION
		DSTU4145_PARAMETER_EC CompatibleParameterEC;
		DSTU4145_PARAMETER_P CompatibleParameterP;

		memset((PVOID) &CompatibleParameterEC, 0,
			sizeof(DSTU4145_PARAMETER_EC));
		memset((PVOID) &CompatibleParameterP, 0,
			sizeof(DSTU4145_PARAMETER_P));

		CompatibleParameterP.dwBits = 7;

		if(pContext->pHardwareCSP != NULL &&
			GenerateKEPKeysCtx(pContext,
				&CompatibleParameterEC,
				&CompatibleParameterP,
				NULL, NULL) == CSP_NO_ERROR)
		{
			if(!pContext->pHardwareCSP->GetEncryptionSBox(
					pGOST28147State->SBox))
			{
				Base.F.GOST28147ReleaseState(pGOST28147State);
				return CSP_ERROR_HARDWARE_CSP_FAILURE;
			}
		}
		else
		{
#endif // CSP_HARDWARE_ENCRYPTION
			if(!Base.F.GOST28147SetStateParameters(
					pGOST28147State, (PVOID) pSBox,
					GOST28147_PARAMETERS_TYPE_SBOX))
			{
				Base.F.GOST28147ReleaseState(pGOST28147State);
				return CSP_ERROR_PROGRAM_FAILURE;
			}
#ifdef CSP_HARDWARE_ENCRYPTION
		}
#endif // CSP_HARDWARE_ENCRYPTION
	}

	*ppGOST28147State = new GOST28147_STATE;
	if(*ppGOST28147State == NULL)
	{
		Base.F.GOST28147ReleaseState(pGOST28147State);
		return CSP_ERROR_ALLOCATE_MEMORY;
	}

	memcpy((PVOID) *ppGOST28147State, (PVOID) pGOST28147State,
		sizeof(GOST28147_STATE));

	Base.F.GOST28147ReleaseState(pGOST28147State);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueEncryptDataCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

#ifdef CSP_HARDWARE_ENCRYPTION
	if(pContext->pHardwareCSP != NULL &&
		CSPIsHardwareEncryptionKey(
			(*ppGOST28147State)->Key))
	{
		BOOL	bHardwareEncryption;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
			bHardwareEncryption);
		if(!bHardwareEncryption)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->ContinueEncryptData(
				pbData, dwData, (*ppGOST28147State)->Key))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
#endif // CSP_HARDWARE_ENCRYPTION

		if(!Base.F.GOST28147EncryptDataGMode(
				pbData, dwData, *ppGOST28147State))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

#ifdef CSP_HARDWARE_ENCRYPTION
	}
#endif // CSP_HARDWARE_ENCRYPTION

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueEncryptDataByOffsetCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	DWORDLONG dwlDataOffset,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

#ifdef CSP_HARDWARE_ENCRYPTION
	if(pContext->pHardwareCSP != NULL &&
		CSPIsHardwareEncryptionKey(
			(*ppGOST28147State)->Key))
	{
		BOOL	bHardwareEncryption;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
			bHardwareEncryption);
		if(!bHardwareEncryption)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->ContinueEncryptDataByOffset(
				pbData, dwData, (*ppGOST28147State)->Key,
				dwlDataOffset))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
#endif // CSP_HARDWARE_ENCRYPTION

		if(!Base.F.GOST28147SetStateParameters(
				*ppGOST28147State, (PVOID) &dwlDataOffset,
				GOST28147_PARAMETERS_TYPE_IV_OFFSET) ||
			!Base.F.GOST28147EncryptDataGMode(
				pbData, dwData, *ppGOST28147State))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

#ifdef CSP_HARDWARE_ENCRYPTION
	}
#endif // CSP_HARDWARE_ENCRYPTION

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeEncryptDataCtx(
	PCSP_CTX pContext,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(ppGOST28147State != NULL &&
		(*ppGOST28147State) != NULL)
	{
#ifdef CSP_HARDWARE_ENCRYPTION
		if(pContext->pHardwareCSP != NULL &&
			CSPIsHardwareEncryptionKey(
				(*ppGOST28147State)->Key))
		{
			BOOL	bHardwareEncryption;

			CSP_CHECK_COMPATIBLE_CTX(this, pContext,
				CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
				bHardwareEncryption);
			if(!bHardwareEncryption)
				return CSP_ERROR_HARDWARE_CSP_FAILURE;

			if(!pContext->pHardwareCSP->FinalizeEncryptData(
					(*ppGOST28147State)->Key))
			{
				return CSP_ERROR_HARDWARE_CSP_FAILURE;
			}
		}
#endif // CSP_HARDWARE_ENCRYPTION

		memset((PVOID) *ppGOST28147State, 0,
			sizeof(GOST28147_STATE));
		delete (*ppGOST28147State);
		*ppGOST28147State = NULL;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeDecryptDataCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

#ifdef CSP_HARDWARE_ENCRYPTION
	if(pContext->pHardwareCSP != NULL &&
		CSPIsHardwareEncryptionKey(pKey))
	{
		BOOL	bHardwareEncryption;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
			bHardwareEncryption);
		if(!bHardwareEncryption)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->InitializeDecryptData(
				pSBox, pKey, pIV))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
#endif // CSP_HARDWARE_ENCRYPTION

	PGOST28147_STATE pGOST28147State;

	pGOST28147State = Base.F.GOST28147AcquireState();
	if(pGOST28147State == NULL)
		return CSP_ERROR_ALLOCATE_MEMORY;

	if(!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pSBox,
			GOST28147_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pKey,
			GOST28147_PARAMETERS_TYPE_KEY) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pIV,
			GOST28147_PARAMETERS_TYPE_IV))
	{
		Base.F.GOST28147ReleaseState(pGOST28147State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*ppGOST28147State = new GOST28147_STATE;
	if(*ppGOST28147State == NULL)
	{
		Base.F.GOST28147ReleaseState(pGOST28147State);
		return CSP_ERROR_ALLOCATE_MEMORY;
	}

	memcpy((PVOID) *ppGOST28147State, (PVOID) pGOST28147State,
		sizeof(GOST28147_STATE));

	Base.F.GOST28147ReleaseState(pGOST28147State);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueDecryptDataCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

#ifdef CSP_HARDWARE_ENCRYPTION
	if(pContext->pHardwareCSP != NULL &&
		CSPIsHardwareEncryptionKey(
			(*ppGOST28147State)->Key))
	{
		BOOL	bHardwareEncryption;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
			bHardwareEncryption);
		if(!bHardwareEncryption)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->ContinueDecryptData(
				pbData, dwData, (*ppGOST28147State)->Key))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
#endif // CSP_HARDWARE_ENCRYPTION

		if(!Base.F.GOST28147EncryptDataGMode(
				pbData, dwData, *ppGOST28147State))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

#ifdef CSP_HARDWARE_ENCRYPTION
	}
#endif // CSP_HARDWARE_ENCRYPTION

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ContinueDecryptDataByOffsetCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	DWORDLONG dwlDataOffset,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

#ifdef CSP_HARDWARE_ENCRYPTION
	if(pContext->pHardwareCSP != NULL &&
		CSPIsHardwareEncryptionKey(
			(*ppGOST28147State)->Key))
	{
		BOOL	bHardwareEncryption;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
			bHardwareEncryption);
		if(!bHardwareEncryption)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->ContinueDecryptDataByOffset(
				pbData, dwData, (*ppGOST28147State)->Key,
				dwlDataOffset))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
#endif // CSP_HARDWARE_ENCRYPTION

		if(!Base.F.GOST28147SetStateParameters(
				*ppGOST28147State, (PVOID) &dwlDataOffset,
				GOST28147_PARAMETERS_TYPE_IV_OFFSET) ||
			!Base.F.GOST28147EncryptDataGMode(
				pbData, dwData, *ppGOST28147State))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

#ifdef CSP_HARDWARE_ENCRYPTION
	}
#endif // CSP_HARDWARE_ENCRYPTION

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::FinalizeDecryptDataCtx(
	PCSP_CTX pContext,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(ppGOST28147State != NULL &&
		(*ppGOST28147State) != NULL)
	{
#ifdef CSP_HARDWARE_ENCRYPTION
		if(pContext->pHardwareCSP != NULL &&
			CSPIsHardwareEncryptionKey(
				(*ppGOST28147State)->Key))
		{
			BOOL	bHardwareEncryption;

			CSP_CHECK_COMPATIBLE_CTX(this, pContext,
				CSP_COMPATIBLE_LEVEL_HARDWARE_ENCRYPTION,
				bHardwareEncryption);
			if(!bHardwareEncryption)
				return CSP_ERROR_HARDWARE_CSP_FAILURE;

			if(!pContext->pHardwareCSP->FinalizeDecryptData(
					(*ppGOST28147State)->Key))
			{
				return CSP_ERROR_HARDWARE_CSP_FAILURE;
			}
		}
#endif // CSP_HARDWARE_ENCRYPTION

		memset((PVOID) *ppGOST28147State, 0,
			sizeof(GOST28147_STATE));
		delete (*ppGOST28147State);
		*ppGOST28147State = NULL;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::HashKEPKeyCtx(
	PCSP_CTX pContext,
	DSTU4145_KEY_D pKeyD,
	DWORD dwBits,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST34311_HASH pHash)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->HashKEPKey(pHash))
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		return CSP_NO_ERROR;
	}
	else
	{
		return HashData((PBYTE) pKeyD, dwBits / 8,
			pSBox, pInitialHash, pHash);
	}

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SetSBoxesCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pEncryptionSBox,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST28147_COMPRESSED_SBOX pECDHSBox,
	GOST28147_COMPRESSED_SBOX pPRNGSBox)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareCSP == NULL)
		return CSP_NO_ERROR;

	if(!pContext->pHardwareCSP->SetSBoxes(
			pEncryptionSBox, pHashSBox,
			pECDHSBox, pPRNGSBox))
	{
		return CSP_ERROR_HARDWARE_CSP_FAILURE;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::EncryptDataFeedbackCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	dwError = GenerateRPRNSequenceCtx(
		pContext, (PBYTE) pKey, sizeof(GOST28147_KEY));
	if(dwError != CSP_NO_ERROR)
		return dwError;

	dwError = GenerateRPRNSequenceCtx(
		pContext, (PBYTE) pIV, sizeof(GOST28147_IV));
	if(dwError != CSP_NO_ERROR)
		return dwError;

	GOST28147_ACQUIRE_STATE();

	if(!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pSBox,
			GOST28147_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pKey,
			GOST28147_PARAMETERS_TYPE_KEY) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pIV,
			GOST28147_PARAMETERS_TYPE_IV) ||
		!Base.F.GOST28147EncryptDataGOFBMode(
			pbData, dwData, pGOST28147State))
	{
		GOST28147_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST28147_RELEASE_STATE();
	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeEncryptDataFeedbackCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKeyAndIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

	return InitializeEncryptDataCtx(
		pContext, pSBox, pKey, pIV,
		blGenerateKeyAndIV, ppGOST28147State);

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::WrapSharedKeyCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_KEY pKey,
	GOST28147_WRAPED_KEY pWrappedKey)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwError;

	if(pKeyDa == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->WrapSharedKey(
				pParameterEC, pParameterP, pKeyQb,
				blCofactorMethod, pbSharedInfo,
				dwSharedInfo, pHashSBox, pWrapSBox,
				pKey, pWrappedKey))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		GOST28147_KEY SharedKey;

		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		if(!Base.F.ECDHUACalculateSharedKey(
				pParameterEC, pParameterP, pKeyDa,
				pKeyQb, blCofactorMethod, pbSharedInfo,
				dwSharedInfo, pHashSBox, pInitialHash,
				SharedKey) ||
			!Base.F.GOST28147WrapSharedKey(
				SharedKey, pWrapSBox, pKey, NULL,
				pContext->pPRNGState, pWrappedKey))
		{
			memset((PVOID) SharedKey, 0,
				sizeof(GOST28147_KEY));

			return CSP_ERROR_PROGRAM_FAILURE;
		}

		memset((PVOID) SharedKey, 0,
			sizeof(GOST28147_KEY));
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::UnwrapSharedKeyCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST34311_HASH pInitialHash,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwA;
	DWORD dwError;

	dwA = pParameterEC->dwA;

	if(pParameterEC->dwA & 0x80000000)
		pParameterEC->dwA &= (~0x80000000);

	if(pKeyDa == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pParameterEC->dwA = dwA;

		if(!pContext->pHardwareCSP->UnwrapSharedKey(
				pParameterEC, pParameterP, pKeyQb,
				blCofactorMethod, pbSharedInfo,
				dwSharedInfo, pHashSBox, pWrapSBox,
				pWrappedKey, pKey))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		GOST28147_KEY SharedKey;

		if(!Base.F.ECDHUACalculateSharedKey(
				pParameterEC, pParameterP, pKeyDa,
				pKeyQb, blCofactorMethod, pbSharedInfo,
				dwSharedInfo, pHashSBox, pInitialHash,
				SharedKey) ||
			!Base.F.GOST28147UnwrapSharedKey(
				SharedKey, pWrapSBox, pWrappedKey, pKey))
		{
			memset((PVOID) SharedKey, 0,
				sizeof(GOST28147_KEY));

			return CSP_ERROR_PROGRAM_FAILURE;
		}

		memset((PVOID) SharedKey, 0,
			sizeof(GOST28147_KEY));
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD()
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::EncryptDataFeedbackExCtx(
	PCSP_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKey,
	BOOL blGenerateIV)
{
	CSP_TRY();

#ifdef CSP_KDF_UA
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(blGenerateKey)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, (PBYTE) pKey,
			sizeof(GOST28147_KEY));
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(blGenerateIV)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, (PBYTE) pIV,
			sizeof(GOST28147_IV));
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	GOST28147_ACQUIRE_STATE();

	if(!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pSBox,
			GOST28147_PARAMETERS_TYPE_SBOX) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pKey,
			GOST28147_PARAMETERS_TYPE_KEY) ||
		!Base.F.GOST28147SetStateParameters(
			pGOST28147State, (PVOID) pIV,
			GOST28147_PARAMETERS_TYPE_IV) ||
		!Base.F.GOST28147EncryptDataGOFBMode(
			pbData, dwData, pGOST28147State))
	{
		GOST28147_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	GOST28147_RELEASE_STATE();

	return CSP_NO_ERROR;
#else // CSP_KDF_UA
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeEncryptDataFeedbackExCtx(
	PCSP_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKey,
	BOOL blGenerateIV,
	PGOST28147_STATE *ppGOST28147State)
{
	CSP_TRY();

#ifdef CSP_KDF_UA
	BOOL blGenerateKeyAndIV;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if((!blGenerateKey) != (!blGenerateIV))
	{
		if(blGenerateKey)
		{
			dwError = GenerateRPRNSequenceCtx(
				pContext, (PBYTE) pKey,
				sizeof(GOST28147_KEY));
		}
		else
		{
			dwError = GenerateRPRNSequenceCtx(
				pContext, (PBYTE) pIV,
				sizeof(GOST28147_IV));
		}

		if(dwError != CSP_NO_ERROR)
			return dwError;

		blGenerateKeyAndIV = FALSE;
	}
	else
		blGenerateKeyAndIV = blGenerateKey;

	return InitializeEncryptDataCtx(
		pContext, pSBox, pKey, pIV,
		blGenerateKeyAndIV, ppGOST28147State);
#else // CSP_KDF_UA
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DeriveProtectionKeyCtx(
	PCSP_CTX pContext,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pPRFSBox,
	GOST34311_HASH pPRFInitHash,
	GOST28147_KEY pDerivedKey)
{
	CSP_TRY();

#ifdef CSP_KDF_UA
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PBKDF2DeriveKey == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(!m_pBaseEx->PBKDF2DeriveKey(
			pbPassword, dwPassword,
			pbSalt, dwSalt, dwCounter,
			pPRFSBox, pPRFInitHash,
			pDerivedKey))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_KDF_UA
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

	CSP_CATCH_DWORD()
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DeriveMACKeyCtx(
	PCSP_CTX pContext,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	GOST28147_COMPRESSED_SBOX pPRFSBox,
	GOST34311_HASH pPRFInitHash,
	GOST28147_KEY pDerivedKey)
{
	CSP_TRY();

#ifdef CSP_KDF_UA
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PBKDFMACDeriveKey == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(!m_pBaseEx->PBKDFMACDeriveKey(
			pbPassword, dwPassword,
			pbSalt, dwSalt, dwCounter,
			pPRFSBox, pPRFInitHash,
			pDerivedKey))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_KDF_UA
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_UA

	CSP_CATCH_DWORD()
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RecoverDSPublicKeyCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwError;

	if(pKeyD == NULL)
	{
		BOOL	bHardwareRecoverPublicKey;

		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY,
			bHardwareRecoverPublicKey);
		if(!bHardwareRecoverPublicKey)
			return CSP_ERROR_PROGRAM_FAILURE;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, TRUE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->RecoverDSPublicKey(
				pParameterEC, pParameterP, pKeyQ))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		memset((PVOID) pKeyQ, 0, sizeof(DSTU4145_KEY_Q));

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145GenerateParameters(
				pDSTU4145State, DSTU4145_FLAG_GENERATE_KEY_Q) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pKeyQ,
				DSTU4145_PARAMETERS_TYPE_KEY_Q))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_RELEASE_STATE();
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RecoverKEPPublicKeyCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_KEY_Q pKeyQ)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwError;

	if(pKeyD == NULL)
	{
		BOOL	bHardwareRecoverPublicKey;

		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY,
			bHardwareRecoverPublicKey);
		if(!bHardwareRecoverPublicKey)
			return CSP_ERROR_PROGRAM_FAILURE;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, TRUE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		if(!pContext->pHardwareCSP->RecoverKEPPublicKey(
				pParameterEC, pParameterP, pKeyQ))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		memset((PVOID) pKeyQ, 0, sizeof(DSTU4145_KEY_Q));

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145GenerateParameters(
				pDSTU4145State, DSTU4145_FLAG_GENERATE_KEY_Q) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pKeyQ,
				DSTU4145_PARAMETERS_TYPE_KEY_Q))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_RELEASE_STATE();
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SetHRNG(
	ICSPHardwareRNG *pHardwareRNG)
{
	CSP_TRY();

	m_pHardwareRNG = NULL;
	m_dwState &= ~CSP_STATE_HRNG_INITIALIZED;

	if(pHardwareRNG != NULL)
	{
		m_pHardwareRNG = pHardwareRNG;
		m_dwState |= CSP_STATE_HRNG_INITIALIZED;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSMakeCommonPublicKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ1,
	DSTU4145_KEY_Q pKeyQ2,
	DSTU4145_KEY_Q pCommonKeyQ)
{
	CSP_TRY();

#ifdef CSP_DSTU4145_COUPLE
	PC_PERFORMANCE_TEST_START(CoupleDSMakeCommonPublicKey)

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145CoupleMakeCommonKeyQ == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterEC,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterP,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pKeyQ2,
			DSTU4145_PARAMETERS_TYPE_KEY_Q))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	if(!m_pBaseEx->DSTU4145CoupleMakeCommonKeyQ(
			pDSTU4145State, pKeyQ1) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) pCommonKeyQ,
			DSTU4145_PARAMETERS_TYPE_KEY_Q))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(CoupleDSMakeCommonPublicKey)

	return CSP_NO_ERROR;
#else // CSP_DSTU4145_COUPLE
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU4145_COUPLE

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart1Step1(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_NUMBER pKeyK1,
	DSTU4145_NUMBER pComponentR1)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CoupleDSPart1Step1Ctx(&Context, 
		pParameterEC, pParameterP, 
		pKeyK1, pComponentR1);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart1Step1Ctx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_NUMBER pKeyK1,
	DSTU4145_NUMBER pComponentR1)
{
	CSP_TRY();

#ifdef CSP_DSTU4145_COUPLE
	PC_PERFORMANCE_TEST_START(CoupleDSPart1Step1Ctx)

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145CoupleMakeSignR == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterEC,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterP,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_P))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pContext->pPRNGState,
			DSTU4145_PARAMETERS_TYPE_PRNG) ||
		!m_pBaseEx->DSTU4145CoupleMakeSignR(
			pDSTU4145State, pComponentR1) ||
		!Base.F.DSTU4145GetStateParameters(pDSTU4145State, 
			(PVOID) pKeyK1, DSTU4145_PARAMETERS_TYPE_KEY_K))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(CoupleDSPart1Step1Ctx)

	return CSP_NO_ERROR;
#else // CSP_DSTU4145_COUPLE
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU4145_COUPLE

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart2Step1(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST34311_HASH pHash,
	DSTU4145_NUMBER	pComponentR1,
	DSTU4145_NUMBER pKeyK2,
	DSTU4145_NUMBER	pCommonComponentR)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CoupleDSPart2Step1Ctx(&Context, 
		pParameterEC, pParameterP, 
		pHash, pComponentR1,
		pKeyK2, pCommonComponentR);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart2Step1Ctx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST34311_HASH pHash,
	DSTU4145_NUMBER	pComponentR1,
	DSTU4145_NUMBER pKeyK2,
	DSTU4145_NUMBER	pCommonComponentR)
{
	CSP_TRY();

#ifdef CSP_DSTU4145_COUPLE
	PC_PERFORMANCE_TEST_START(CoupleDSPart2Step1Ctx)

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145CoupleMakeSignR == NULL ||
		m_pBaseEx->DSTU4145CoupleMakeCommonSignR == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterEC,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterP,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_P))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	DSTU4145_NUMBER	ComponentR2;

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pContext->pPRNGState,
			DSTU4145_PARAMETERS_TYPE_PRNG) ||
		!m_pBaseEx->DSTU4145CoupleMakeSignR(
			pDSTU4145State, ComponentR2) ||
		!Base.F.DSTU4145GetStateParameters(pDSTU4145State, 
			(PVOID) pKeyK2, DSTU4145_PARAMETERS_TYPE_KEY_K))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pHash,
			DSTU4145_PARAMETERS_TYPE_HASH) ||
		!m_pBaseEx->DSTU4145CoupleMakeCommonSignR(
			pDSTU4145State, ComponentR2, pComponentR1, 
			pCommonComponentR))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(CoupleDSPart2Step1Ctx)

	return CSP_NO_ERROR;
#else // CSP_DSTU4145_COUPLE
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU4145_COUPLE

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart1Step2(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD1,
	DSTU4145_NUMBER	pKeyK1,
	DSTU4145_NUMBER	pCommonComponentR,
	DSTU4145_NUMBER pComponentS1)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CoupleDSPart1Step2Ctx(&Context, 
		pParameterEC, pParameterP, 
		pKeyD1, pKeyK1, pCommonComponentR,
		pComponentS1);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart1Step2Ctx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD1,
	DSTU4145_NUMBER	pKeyK1,
	DSTU4145_NUMBER	pCommonComponentR,
	DSTU4145_NUMBER pComponentS1)
{
	CSP_TRY();

#ifdef CSP_DSTU4145_COUPLE
	PC_PERFORMANCE_TEST_START(CoupleDSPart1Step2Ctx)

	DWORD dwError;
	BOOL bHardwareDSCouple;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD1 == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_DS_COUPLE,
			bHardwareDSCouple);
		if(!bHardwareDSCouple)
			return CSP_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->CoupleDSMakeComponentS(
				pParameterEC, pParameterP, 
				pKeyK1, pCommonComponentR, 
				pComponentS1))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(m_pBaseEx == NULL ||
			m_pBaseEx->DSTU4145CoupleMakeSignS == NULL)
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_ACQUIRE_STATE();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD1,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyK1,
				DSTU4145_PARAMETERS_TYPE_KEY_K) ||
			!m_pBaseEx->DSTU4145CoupleMakeSignS(
				pDSTU4145State, pCommonComponentR, 
				pComponentS1))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		DSTU4145_RELEASE_STATE();
	}

	PC_PERFORMANCE_TEST_STOP(CoupleDSPart1Step2Ctx)

	return CSP_NO_ERROR;
#else // CSP_DSTU4145_COUPLE
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU4145_COUPLE

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart2Step2(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD2,
	DSTU4145_NUMBER pKeyK2,
	DSTU4145_NUMBER	pCommonComponentR,
	DSTU4145_NUMBER pComponentS1,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CoupleDSPart2Step2Ctx(&Context, 
		pParameterEC, pParameterP, 
		pKeyD2, pKeyK2, pCommonComponentR, pComponentS1,
		pSignature);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CoupleDSPart2Step2Ctx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD2,
	DSTU4145_NUMBER pKeyK2,
	DSTU4145_NUMBER	pCommonComponentR,
	DSTU4145_NUMBER pComponentS1,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

#ifdef CSP_DSTU4145_COUPLE
	PC_PERFORMANCE_TEST_START(CoupleDSPart2Step2Ctx)

	DWORD dwError;
	BOOL bHardwareDSCouple;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DSTU4145_ACQUIRE_STATE();

	DSTU4145_NUMBER	ComponentS2;

	if(pKeyD2 == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_NOT_INITIALIZED;
		}

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
		{
			DSTU4145_RELEASE_STATE();
			return dwError;
		}

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_DS_COUPLE,
			bHardwareDSCouple);
		if(!bHardwareDSCouple)
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(!pContext->pHardwareCSP->CoupleDSMakeComponentS(
				pParameterEC, pParameterP, 
				pKeyK2, pCommonComponentR, 
				ComponentS2))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}
	}
	else
	{
		if(m_pBaseEx == NULL ||
			m_pBaseEx->DSTU4145CoupleMakeSignS == NULL)
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD2,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyK2,
				DSTU4145_PARAMETERS_TYPE_KEY_K) ||
			!m_pBaseEx->DSTU4145CoupleMakeSignS(
				pDSTU4145State, pCommonComponentR, 
				ComponentS2))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145CoupleMakeCommonSignS == NULL ||
		m_pBaseEx->DSTU4145CoupleMakeCommonSign == NULL)
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_NUMBER	CommonComponentS;

	if(!m_pBaseEx->DSTU4145CoupleMakeCommonSignS(
			pDSTU4145State, ComponentS2, pComponentS1, 
			CommonComponentS) ||
		!m_pBaseEx->DSTU4145CoupleMakeCommonSign(
			pDSTU4145State, pCommonComponentR, CommonComponentS) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) pSignature,
			DSTU4145_PARAMETERS_TYPE_SIGNATURE) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &pParameterP->dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(CoupleDSPart2Step2Ctx)

	return CSP_NO_ERROR;
#else // CSP_DSTU4145_COUPLE
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU4145_COUPLE

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564InitializeState(
	DSTU7564_SBOX pSBox,
	DWORD dwHash,
	PDSTU7564_STATE *ppDSTU7564State)
{
	CSP_TRY();

#ifdef CSP_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7564SetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	UINT nHashBits;

	DSTU7564_ACQUIRE_STATE();

	nHashBits = (UINT) dwHash * 8;

	if(((pSBox != NULL) ?
		!m_pBaseEx->DSTU7564SetStateParameters(
			pDSTU7564State, (PVOID) pSBox,
			DSTU7564_PARAMETERS_TYPE_SBOX) : FALSE) ||
		!m_pBaseEx->DSTU7564SetStateParameters(
			pDSTU7564State, (PVOID) &nHashBits,
			DSTU7564_PARAMETERS_TYPE_HASH_SIZE))
	{
		DSTU7564_RELEASE_STATE(pDSTU7564State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*ppDSTU7564State = pDSTU7564State;
	return CSP_NO_ERROR;
#else // CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564FinalizeState(
	DSTU7564_HASH pHash,
	PDSTU7564_STATE *ppDSTU7564State)
{
	CSP_TRY();

#ifdef CSP_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7564FinalizeHash == NULL ||
		m_pBaseEx->DSTU7564GetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pHash != NULL)
	{
		if(!m_pBaseEx->DSTU7564FinalizeHash(
				*ppDSTU7564State) ||
			!m_pBaseEx->DSTU7564GetStateParameters(
				*ppDSTU7564State, pHash,
				DSTU7564_PARAMETERS_TYPE_HASH))
		{
			DSTU7564_RELEASE_STATE(*ppDSTU7564State);
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}

	DSTU7564_RELEASE_STATE(*ppDSTU7564State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564StateHashData(
	PBYTE pbData,
	DWORD dwData,
	PDSTU7564_STATE *ppDSTU7564State)
{
	CSP_TRY();

#ifdef CSP_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7564HashData == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7564HashData(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7564State))
	{
		DSTU7564_RELEASE_STATE(*ppDSTU7564State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564HashData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7564_SBOX pSBox,
	DWORD dwHash,
	DSTU7564_HASH pHash)
{
	CSP_TRY();

#ifdef CSP_DSTU7564
	PDSTU7564_STATE pDSTU7654State;
	DWORD dwError;

	if((dwError = DSTU7564InitializeState(
			pSBox, dwHash, &pDSTU7654State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU7564StateHashData(
			pbData, dwData, &pDSTU7654State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU7564FinalizeState(
			pHash, &pDSTU7654State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564CheckDataHash(
	PBYTE pbData,
	DWORD dwData,
	DSTU7564_SBOX pSBox,
	DWORD dwHash,
	DSTU7564_HASH pHash)
{
	CSP_TRY();

#ifdef CSP_DSTU7564
	DSTU7564_HASH Hash;
	DWORD dwError;

	dwError = DSTU7564HashData(
		pbData, dwData, pSBox, dwHash, Hash);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	if(memcmp(Hash, pHash, dwHash) != 0)
	{
		memset((PVOID) Hash, 0, sizeof(DSTU7564_HASH));
		return CSP_ERROR_DATA_CORRUPTED;
	}

	memset((PVOID) Hash, 0, sizeof(DSTU7564_HASH));
	return CSP_NO_ERROR;
#else // CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624GenerateParameters(
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwIV)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU7624GenerateParametersCtx(
		&Context, pbKey, dwKey, pbIV, dwIV);
	if (dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624GenerateParametersCtx(
	PCSP_CTX pContext,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwIV)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pbKey != NULL)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbKey, dwKey);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(pbIV != NULL)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbIV, dwIV);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624InitializeState(
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	UINT nBlockBits;
	UINT nKeyBits;

	DSTU7624_ACQUIRE_STATE();

	nBlockBits = (UINT) dwBlock * 8;
	nKeyBits = (UINT) dwKey * 8;

	if(((pSBox != NULL) ?
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) pSBox,
			DSTU7624_PARAMETERS_TYPE_SBOX) : FALSE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nBlockBits,
			DSTU7624_PARAMETERS_TYPE_BLOCK_SIZE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nKeyBits,
			DSTU7624_PARAMETERS_TYPE_KEY_SIZE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) pbKey,
			DSTU7624_PARAMETERS_TYPE_KEYS) ||
		((pbIV != NULL) ?
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) pbIV,
			DSTU7624_PARAMETERS_TYPE_IV) : FALSE))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*ppDSTU7624State = pDSTU7624State;
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624FinalizeState(
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	DSTU7624_RELEASE_STATE(*ppDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624ECBEncryptData(
	PBYTE pbData,
	DWORD dwDataBlocks,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataECBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataECBMode(
			pbData, dwDataBlocks, pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624ECBDecryptData(
	PBYTE pbData,
	DWORD dwDataBlocks,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataECBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataECBMode(
			pbData, dwDataBlocks, pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CTRStateEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataCTRMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataCTRMode(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CTRStateEncryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbIV,
	DWORDLONG dwlDataOffset,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	UINT nBlockBits;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624EncryptDataCTRMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624GetStateParameters(
			*ppDSTU7624State, (PVOID) &nBlockBits,
			DSTU7624_PARAMETERS_TYPE_BLOCK_SIZE) ||
		(dwlDataOffset /= (nBlockBits / 8), FALSE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			*ppDSTU7624State, (PVOID) pbIV,
			DSTU7624_PARAMETERS_TYPE_IV) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			*ppDSTU7624State, (PVOID) &dwlDataOffset,
			DSTU7624_PARAMETERS_TYPE_CTR) ||
		!m_pBaseEx->DSTU7624EncryptDataCTRMode(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CTREncryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR ||
		(dwError = DSTU7624CTRStateEncryptData(
			pbData, dwData, &pDSTU7624State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU7624FinalizeState(
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CTRStateDecryptData(
	PBYTE pbData,
	DWORD dwData,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataCTRMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataCTRMode(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CTRStateDecryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbIV,
	DWORDLONG dwlDataOffset,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	UINT nBlockBits;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624DecryptDataCTRMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624GetStateParameters(
			*ppDSTU7624State, (PVOID) &nBlockBits,
			DSTU7624_PARAMETERS_TYPE_BLOCK_SIZE) ||
		(dwlDataOffset /= (nBlockBits / 8), FALSE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			*ppDSTU7624State, (PVOID) pbIV,
			DSTU7624_PARAMETERS_TYPE_IV) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			*ppDSTU7624State, (PVOID) &dwlDataOffset,
			DSTU7624_PARAMETERS_TYPE_CTR) ||
		!m_pBaseEx->DSTU7624DecryptDataCTRMode(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CTRDecryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR ||
		(dwError = DSTU7624CTRStateDecryptData(
			pbData, dwData, &pDSTU7624State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU7624FinalizeState(
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CFBEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock,
	DWORD dwGammaBits)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataCFBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataCFBMode(
			pbData, (UINT64) dwData * 8ULL,
			dwGammaBits, pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CFBDecryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock,
	DWORD dwGammaBits)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataCFBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataCFBMode(
			pbData, (UINT64) dwData * 8ULL,
			dwGammaBits, pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624GetDataCMAC(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock,
	PBYTE pbCMAC,
	DWORD dwCMAC)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL ||
		m_pBaseEx->DSTU7624GetDataCMAC == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwCMAC * 8;

	if(!m_pBaseEx->DSTU7624GetDataCMAC(
			pbData, (UINT64) dwData * 8ULL,
			pDSTU7624State) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624GetStateParameters(
			pDSTU7624State, (PVOID) pbCMAC,
			DSTU7624_PARAMETERS_TYPE_MAC))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CheckDataCMAC(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbCMAC,
	DWORD dwCMAC,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624CheckDataCMAC == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwCMAC * 8;

	if(!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) pbCMAC,
			DSTU7624_PARAMETERS_TYPE_MAC) ||
		!m_pBaseEx->DSTU7624CheckDataCMAC(
			pbData, (UINT64) dwData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CBCEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DWORD dwOutputData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataCBCMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataCBCMode(
			pbData, (UINT64) dwData * 8ULL,
			(UINT64) dwOutputData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CBCDecryptData(
	PBYTE pbData,
	PDWORD pdwData,
	BOOL bPadding,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT64 dwOutputDataBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataCBCMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataCBCMode(
			pbData, (UINT64) *pdwData * 8ULL,
			bPadding, &dwOutputDataBits, pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*pdwData = (DWORD) ((dwOutputDataBits + 7) / 8);

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624OFBStateEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataOFBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataOFBMode(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624OFBEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR ||
		(dwError = DSTU7624OFBStateEncryptData(
			pbData, dwData, &pDSTU7624State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU7624FinalizeState(
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624OFBStateDecryptData(
	PBYTE pbData,
	DWORD dwData,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataOFBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataOFBMode(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624OFBDecryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR ||
		(dwError = DSTU7624OFBStateDecryptData(
			pbData, dwData, &pDSTU7624State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU7624FinalizeState(
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624GCMEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbPublicData,
	DWORD dwPublicData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock,
	PBYTE pbGMAC,
	DWORD dwGMAC)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL ||
		m_pBaseEx->DSTU7624EncryptDataGCMMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwGMAC * 8;

	if(!m_pBaseEx->DSTU7624EncryptDataGCMMode(
			pbData, (UINT64) dwData * 8ULL,
			pbPublicData, (UINT64) dwPublicData * 8ULL,
			pDSTU7624State) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624GetStateParameters(
			pDSTU7624State, (PVOID) pbGMAC,
			DSTU7624_PARAMETERS_TYPE_MAC))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624GCMDecryptData(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbPublicData,
	DWORD dwPublicData,
	PBYTE pbGMAC,
	DWORD dwGMAC,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624DecryptDataGCMMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwGMAC * 8;

	if(!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) pbGMAC,
			DSTU7624_PARAMETERS_TYPE_MAC) ||
		!m_pBaseEx->DSTU7624DecryptDataGCMMode(
			pbData, (UINT64) dwData * 8ULL,
			pbPublicData, (UINT64) dwPublicData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624GetDataGMAC(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock,
	PBYTE pbGMAC,
	DWORD dwGMAC)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL ||
		m_pBaseEx->DSTU7624GetDataGMAC == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwGMAC * 8;

	if(!m_pBaseEx->DSTU7624GetDataGMAC(
			pbData, (UINT64) dwData * 8ULL,
			pDSTU7624State) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624GetStateParameters(
			pDSTU7624State, (PVOID) pbGMAC,
			DSTU7624_PARAMETERS_TYPE_MAC))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CheckDataGMAC(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbGMAC,
	DWORD dwGMAC,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624CheckDataGMAC == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwGMAC * 8;

	if(!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) pbGMAC,
			DSTU7624_PARAMETERS_TYPE_MAC) ||
		!m_pBaseEx->DSTU7624CheckDataGMAC(
			pbData, (UINT64) dwData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CCMEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DWORD dwOutputData,
	PBYTE pbPublicData,
	DWORD dwPublicData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock,
	DWORD dwDataBytes,
	DWORD dwMAC)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624EncryptDataCCMMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwMAC * 8;

	if(!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624EncryptDataCCMMode(
			pbData, dwData, dwOutputData,
			pbPublicData, dwPublicData, dwDataBytes,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CCMDecryptData(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbPublicData,
	DWORD dwPublicData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock,
	DWORD dwDataBytes,
	DWORD dwMAC)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nMACBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL ||
		m_pBaseEx->DSTU7624DecryptDataCCMMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	nMACBits = (UINT) dwMAC * 8;

	if(!m_pBaseEx->DSTU7624SetStateParameters(
			pDSTU7624State, (PVOID) &nMACBits,
			DSTU7624_PARAMETERS_TYPE_MAC_SIZE) ||
		!m_pBaseEx->DSTU7624DecryptDataCCMMode(
			pbData, dwData, pbPublicData, dwPublicData,
			dwDataBytes, pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624XTSEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataXTSMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataXTSMode(
			pbData, (UINT64) dwData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624XTSDecryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataXTSMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, pbIV, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataXTSMode(
			pbData, (UINT64) dwData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624KWEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DWORD dwOutputData,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataKWMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataKWMode(
			pbData, (UINT64) dwData * 8ULL,
			(UINT64) dwOutputData * 8ULL,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624KWDecryptData(
	PBYTE pbData,
	PDWORD pdwData,
	BOOL bPadding,
	DSTU7624_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PBYTE pbIV,
	DWORD dwBlock)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT64 dwOutputDataBits;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataKWMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if((dwError = DSTU7624InitializeState(
			pSBox, pbKey, dwKey, NULL, dwBlock,
			&pDSTU7624State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataKWMode(
			pbData, (UINT64) *pdwData * 8ULL,
			bPadding, &dwOutputDataBits,
			pDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(pDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*pdwData = (DWORD) ((dwOutputDataBits + 7) / 8);

	DSTU7624_RELEASE_STATE(pDSTU7624State);
	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SignDSTUHash(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = SignDSTUHashCtx(
		&Context, dwHash, pHash, pParameterEC,
		pParameterP, pKeyD, pSignature);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SignDSTUHashCtx(
	PCSP_CTX pContext,
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyD,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	PC_PERFORMANCE_TEST_START(SignDSTUHash)

	UINT Hash[DSTU7564_HASH_512_LENGTH / sizeof(UINT)];
	UINT dwHashWords;
	BOOL bHardwareSignDSTUHash;
	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(dwHash > DSTU7564_HASH_512_LENGTH)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_SIGN_DSTU_HASH,
			bHardwareSignDSTUHash);
		if(!bHardwareSignDSTUHash)
		{
			if(dwHash != sizeof(GOST34311_HASH))
				return CSP_ERROR_PROGRAM_FAILURE;

			ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
			CopyMemory((PVOID) Hash, pHash, dwHash);
			dwHashWords =
				(dwHash + sizeof(UINT) - 1) / sizeof(UINT);

#ifdef HP_BIG_ENDIAN
			SWAP_BYTES_32_ARRAY_SIZE(Hash, dwHashWords);
#endif /* HP_BIG_ENDIAN */

			if(!pContext->pHardwareCSP->SignHash(
					pParameterEC, pParameterP, Hash,
					pSignature))
			{
				ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
				return CSP_ERROR_HARDWARE_CSP_FAILURE;
			}

			ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
		}
		else
		{
			if(!pContext->pHardwareCSP->SignDSTUHash(
					pParameterEC, pParameterP,
					dwHash, pHash, pSignature))
			{
				return CSP_ERROR_HARDWARE_CSP_FAILURE;
			}
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		DSTU4145_ACQUIRE_STATE();

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterEC,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pParameterP,
				DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pKeyD,
				DSTU4145_PARAMETERS_TYPE_KEY_D))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
		CopyMemory((PVOID) Hash, pHash, dwHash);
		dwHashWords =
			(dwHash + sizeof(UINT) - 1) / sizeof(UINT);

#ifdef HP_BIG_ENDIAN
		SWAP_BYTES_32_ARRAY_SIZE(Hash, dwHashWords);
#endif /* HP_BIG_ENDIAN */

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) &dwHashWords,
				DSTU4145_PARAMETERS_TYPE_HASH_SIZE) ||
			!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) Hash,
				DSTU4145_PARAMETERS_TYPE_HASH) ||
			!Base.F.DSTU4145SignHash(pDSTU4145State) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pSignature,
				DSTU4145_PARAMETERS_TYPE_SIGNATURE) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) &pParameterP->dwBits,
				DSTU4145_PARAMETERS_TYPE_P_LENGTH))
		{
			ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
		DSTU4145_RELEASE_STATE();
	}

	PC_PERFORMANCE_TEST_STOP(SignDSTUHash)

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::VerifyDSTUSignature(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature)
{
	CSP_TRY();

	PC_PERFORMANCE_TEST_START(VerifyDSTUSignature)

	UINT Hash[DSTU7564_HASH_512_LENGTH / sizeof(UINT)];
	UINT dwHashWords;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(dwHash > DSTU7564_HASH_512_LENGTH)
		return CSP_ERROR_BAD_PARAMETERS;

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterEC,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_EC) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pParameterP,
			DSTU4145_PARAMETERS_TYPE_PARAMETER_P) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pKeyQ,
			DSTU4145_PARAMETERS_TYPE_KEY_Q) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pSignature,
			DSTU4145_PARAMETERS_TYPE_SIGNATURE))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
	CopyMemory((PVOID) Hash, pHash, dwHash);
	dwHashWords =
		(dwHash + sizeof(UINT) - 1) / sizeof(UINT);

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY_SIZE(Hash, dwHashWords);
#endif /* HP_BIG_ENDIAN */

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) &dwHashWords,
			DSTU4145_PARAMETERS_TYPE_HASH_SIZE) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) Hash,
			DSTU4145_PARAMETERS_TYPE_HASH))
	{
		ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);

	if(!Base.F.DSTU4145VerifySignature(pDSTU4145State))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_BAD_SIGNATURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(VerifyDSTUSignature)

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845GenerateParameters(
	PBYTE pbKey,
	DWORD dwKey,
	DSTU8845_IV pIV)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU8845GenerateParametersCtx(
		&Context, pbKey, dwKey, pIV);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845GenerateParametersCtx(
	PCSP_CTX pContext,
	PBYTE pbKey,
	DWORD dwKey,
	DSTU8845_IV pIV)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pbKey != NULL)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbKey, dwKey);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(pIV != NULL)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pIV, DSTU8845_IV_256_LENGTH);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845InitializeState(
	DSTU8845_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DSTU8845_IV pIV,
	PDSTU8845_STATE *ppDSTU8845State)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU8845SetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	UINT nKeyBits;

	DSTU8845_ACQUIRE_STATE();

	nKeyBits = (UINT) dwKey * 8;

	if(((pSBox != NULL) ?
		!m_pBaseEx->DSTU8845SetStateParameters(
			pDSTU8845State, (PVOID) pSBox,
			DSTU8845_PARAMETERS_TYPE_SBOX) : FALSE) ||
		!m_pBaseEx->DSTU8845SetStateParameters(
			pDSTU8845State, (PVOID) &nKeyBits,
			DSTU8845_PARAMETERS_TYPE_KEY_SIZE) ||
		!m_pBaseEx->DSTU8845SetStateParameters(
			pDSTU8845State, (PVOID) pbKey,
			DSTU8845_PARAMETERS_TYPE_KEY) ||
		((pIV != NULL) ?
		!m_pBaseEx->DSTU8845SetStateParameters(
			pDSTU8845State, (PVOID) pIV,
			DSTU8845_PARAMETERS_TYPE_IV) : FALSE))
	{
		DSTU8845_RELEASE_STATE(pDSTU8845State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*ppDSTU8845State = pDSTU8845State;
	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845FinalizeState(
	PDSTU8845_STATE *ppDSTU8845State)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	DSTU8845_RELEASE_STATE(*ppDSTU8845State);
	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845StateEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PDSTU8845_STATE *ppDSTU8845State)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU8845EncryptData == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU8845EncryptData(
			pbData, dwData, *ppDSTU8845State))
	{
		DSTU8845_RELEASE_STATE(*ppDSTU8845State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845StateEncryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	DSTU8845_IV pIV,
	DWORDLONG dwlDataOffset,
	PDSTU8845_STATE *ppDSTU8845State)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU8845GetStateParameters == NULL ||
		m_pBaseEx->DSTU8845SetStateParameters == NULL ||
		m_pBaseEx->DSTU8845EncryptData == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU8845SetStateParameters(
			*ppDSTU8845State, (PVOID) pIV,
			DSTU8845_PARAMETERS_TYPE_IV) ||
		!m_pBaseEx->DSTU8845SetStateParameters(
			*ppDSTU8845State, (PVOID) &dwlDataOffset,
			DSTU8845_PARAMETERS_TYPE_IV_OFFSET) ||
		!m_pBaseEx->DSTU8845EncryptData(
			pbData, dwData, *ppDSTU8845State))
	{
		DSTU8845_RELEASE_STATE(*ppDSTU8845State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845StateEncryptDataByPacketOffset(
	PBYTE pbData,
	DWORD dwData,
	DSTU8845_IV pIV,
	DWORDLONG dwlDataOffset,
	PDSTU8845_STATE *ppDSTU8845State)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU8845GetStateParameters == NULL ||
		m_pBaseEx->DSTU8845SetStateParameters == NULL ||
		m_pBaseEx->DSTU8845EncryptData == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU8845SetStateParameters(
			*ppDSTU8845State, (PVOID) pIV,
			DSTU8845_PARAMETERS_TYPE_IV) ||
		!m_pBaseEx->DSTU8845SetStateParameters(
			*ppDSTU8845State, (PVOID) &dwlDataOffset,
			DSTU8845_PARAMETERS_TYPE_IV_PACKET_OFFSET) ||
		!m_pBaseEx->DSTU8845EncryptData(
			pbData, dwData, *ppDSTU8845State))
	{
		DSTU8845_RELEASE_STATE(*ppDSTU8845State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845EncryptData(
	PBYTE pbData,
	DWORD dwData,
	DSTU8845_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DSTU8845_IV pIV)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	PDSTU8845_STATE pDSTU8845State;
	DWORD dwError;

	if((dwError = DSTU8845InitializeState(
			pSBox, pbKey, dwKey, pIV,
			&pDSTU8845State)) != CSP_NO_ERROR ||
		(dwError = DSTU8845StateEncryptData(
			pbData, dwData, &pDSTU8845State)) !=
		CSP_NO_ERROR ||
		(dwError = DSTU8845FinalizeState(
			&pDSTU8845State)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564DeriveMACKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	DWORD dwIterationCount,
	DSTU7564_SBOX pPRFSBox,
	PBYTE pbDerivedKey,
	DWORD dwDerivedKey)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFDSTU7564DeriveKey == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->PKCS12PBKDFDSTU7564DeriveKey(
			pbPassword, dwPassword, pbSalt, dwSalt,
			dwIterationCount, pPRFSBox, dwDerivedKey * 8,
			pbDerivedKey, dwDerivedKey))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564InitializeHMACState(
	DSTU7564_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	PDSTU7564_HMAC_STATE *ppDSTU7564HMACState)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7564HMACSetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	UINT nHashBits;

	DSTU7564_HMAC_ACQUIRE_STATE();

	nHashBits = (UINT) dwKey * 8;

	if((pSBox != NULL &&
		!m_pBaseEx->DSTU7564HMACSetStateParameters(
			pDSTU7564HMACState, (PVOID) pSBox,
			DSTU7564_HMAC_PARAMETERS_TYPE_SBOX)) ||
		!m_pBaseEx->DSTU7564HMACSetStateParameters(
			pDSTU7564HMACState, (PVOID) &nHashBits,
			DSTU7564_HMAC_PARAMETERS_TYPE_HASH_BIT_LENGTH) ||
		!m_pBaseEx->DSTU7564HMACSetStateParameters(
			pDSTU7564HMACState, pbKey,
			DSTU7564_HMAC_PARAMETERS_TYPE_KEY))
	{
		DSTU7564_HMAC_RELEASE_STATE(pDSTU7564HMACState);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	*ppDSTU7564HMACState = pDSTU7564HMACState;
	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564FinalizeHMACState(
	DSTU7564_HASH pHMac,
	PDSTU7564_HMAC_STATE *ppDSTU7564HMACState)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7564HMACFinalizeDataMac == NULL ||
		m_pBaseEx->DSTU7564HMACGetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pHMac != NULL)
	{
		if(!m_pBaseEx->DSTU7564HMACFinalizeDataMac(
				*ppDSTU7564HMACState) ||
			!m_pBaseEx->DSTU7564HMACGetStateParameters(
				*ppDSTU7564HMACState, pHMac,
				DSTU7564_HMAC_PARAMETERS_TYPE_HMAC))
		{
			DSTU7564_HMAC_RELEASE_STATE(*ppDSTU7564HMACState);
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}

	DSTU7564_HMAC_RELEASE_STATE(*ppDSTU7564HMACState);
	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564StateGetDataHMAC(
	PBYTE pbData,
	DWORD dwData,
	PDSTU7564_HMAC_STATE *ppDSTU7564HMACState)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7564HMACUpdateData == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7564HMACUpdateData(
			pbData, (UINT64) dwData * 8ULL,
			*ppDSTU7564HMACState))
	{
		DSTU7564_RELEASE_STATE(*ppDSTU7564HMACState);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564GetDataHMAC(
	PBYTE pbData,
	DWORD dwData,
	DSTU7564_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DSTU7564_HASH pHMac)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	PDSTU7564_HMAC_STATE pDSTU7564HMACState;
	DWORD dwError;

	if((dwError = DSTU7564InitializeHMACState(
			pSBox, pbKey, dwKey,
			&pDSTU7564HMACState)) != CSP_NO_ERROR ||
		(dwError = DSTU7564StateGetDataHMAC(
			pbData, dwData,
			&pDSTU7564HMACState)) != CSP_NO_ERROR ||
		(dwError = DSTU7564FinalizeHMACState(
			pHMac,
			&pDSTU7564HMACState)) != CSP_NO_ERROR)
	{
		return dwError;
	}

	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564CheckDataHMAC(
	PBYTE pbData,
	DWORD dwData,
	DSTU7564_SBOX pSBox,
	PBYTE pbKey,
	DWORD dwKey,
	DSTU7564_HASH pHMac)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	DSTU7564_HASH HMac;
	DWORD dwError;

	dwError = DSTU7564GetDataHMAC(
		pbData, dwData, pSBox,
		pbKey, dwKey, HMac);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	if(memcmp(HMac, pHMac, dwKey) != 0)
	{
		memset(HMac, 0, sizeof(DSTU7564_HASH));

		return CSP_ERROR_DATA_CORRUPTED;
	}

	memset(HMac, 0, sizeof(DSTU7564_HASH));

	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564HMACDeriveProtectionKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	DWORD dwIterationCount,
	DSTU7564_SBOX pPRFSBox,
	DWORD dwHash,
	PBYTE pbDerivedKey,
	DWORD dwDerivedKey)
{
	CSP_TRY();

#ifdef CSP_KDF_DSTU7564
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS5PBKDF2DSTU7564DeriveKey == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->PKCS5PBKDF2DSTU7564DeriveKey(
			pbPassword, dwPassword, pbSalt, dwSalt,
			dwIterationCount, pPRFSBox, dwHash * 8,
			pbDerivedKey, dwDerivedKey))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_KDF_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_KDF_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624DuplicateState(
	PDSTU7624_STATE *ppDSTU7624State,
	PVOID pvState,
	PDWORD pdwState)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	UINT nStateSize;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if (!m_pBaseEx->DSTU7624GetStateParameters(
			*ppDSTU7624State, (PVOID) &nStateSize,
			DSTU7624_PARAMETERS_TYPE_STATE_SIZE))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if (pvState != NULL)
	{
		if (!m_pBaseEx->DSTU7624GetStateParameters(
				*ppDSTU7624State, pvState,
				DSTU7624_PARAMETERS_TYPE_STATE))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}

	if (pdwState != NULL)
		*pdwState = (DWORD) nStateSize;

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624RestoreState(
	PDSTU7624_STATE *ppDSTU7624State,
	PVOID pvState,
	DWORD dwState)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	PDSTU7624_STATE pDSTU7624State;
	UINT nStateSize;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624AcquireState == NULL ||
		m_pBaseEx->DSTU7624ReleaseState == NULL ||
		m_pBaseEx->DSTU7624GetStateParameters == NULL ||
		m_pBaseEx->DSTU7624SetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	pDSTU7624State = NULL;

	if(*ppDSTU7624State == NULL)
	{
		pDSTU7624State = m_pBaseEx->DSTU7624AcquireState();
		if(pDSTU7624State == NULL)
			return CSP_ERROR_ALLOCATE_MEMORY;

		*ppDSTU7624State = pDSTU7624State;
	}

	if(!m_pBaseEx->DSTU7624GetStateParameters(
			*ppDSTU7624State, (PVOID) &nStateSize,
			DSTU7624_PARAMETERS_TYPE_STATE_SIZE) ||
		(DWORD) nStateSize != dwState ||
		!m_pBaseEx->DSTU7624SetStateParameters(
			*ppDSTU7624State, pvState,
			DSTU7624_PARAMETERS_TYPE_STATE))
	{
		if(pDSTU7624State != NULL)
		{
			m_pBaseEx->DSTU7624ReleaseState(
				pDSTU7624State);
			*ppDSTU7624State = NULL;
		}

		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845DuplicateState(
	PDSTU8845_STATE *ppDSTU8845State,
	PVOID pvState,
	PDWORD pdwState)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	UINT nStateSize;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU8845GetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if (!m_pBaseEx->DSTU8845GetStateParameters(
			*ppDSTU8845State, (PVOID) &nStateSize,
			DSTU8845_PARAMETERS_TYPE_STATE_SIZE))
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if (pvState != NULL)
	{
		if (!m_pBaseEx->DSTU8845GetStateParameters(
				*ppDSTU8845State, pvState,
				DSTU8845_PARAMETERS_TYPE_STATE))
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}
	}

	if (pdwState != NULL)
		*pdwState = (DWORD) nStateSize;

	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU8845RestoreState(
	PDSTU8845_STATE *ppDSTU8845State,
	PVOID pvState,
	DWORD dwState)
{
	CSP_TRY();

#ifdef CSP_DSTU8845
	PDSTU8845_STATE pDSTU8845State;
	UINT nStateSize;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU8845AcquireState == NULL ||
		m_pBaseEx->DSTU8845ReleaseState == NULL ||
		m_pBaseEx->DSTU8845GetStateParameters == NULL ||
		m_pBaseEx->DSTU8845SetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	pDSTU8845State = NULL;

	if(*ppDSTU8845State == NULL)
	{
		pDSTU8845State = m_pBaseEx->DSTU8845AcquireState();
		if(pDSTU8845State == NULL)
			return CSP_ERROR_ALLOCATE_MEMORY;

		*ppDSTU8845State = pDSTU8845State;
	}

	if (!m_pBaseEx->DSTU8845GetStateParameters(
			*ppDSTU8845State, (PVOID) &nStateSize,
			DSTU8845_PARAMETERS_TYPE_STATE_SIZE) ||
		(DWORD) nStateSize != dwState ||
		!m_pBaseEx->DSTU8845SetStateParameters(
			*ppDSTU8845State, pvState,
			DSTU8845_PARAMETERS_TYPE_STATE))
	{
		if(pDSTU8845State != NULL)
		{
			m_pBaseEx->DSTU8845ReleaseState(
				pDSTU8845State);
			*ppDSTU8845State = NULL;
		}

		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU8845
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU8845

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624ProtectData(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbProtectedData,
	DWORD dwProtectedData,
	DSTU7624_SBOX pSBox,
	PCHAR pcPassword,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pIV)
{
	CSP_TRY();

#if defined(CSP_DSTU7624) && defined(CSP_DSTU7564)
	BYTE bKey[DSTU7624_KEY_512_LENGTH];
	BYTE bIV[DSTU7624_KEY_512_LENGTH];
	DWORD dwIV;
	DWORD dwAlignedData;
	DWORD dwError;

	dwIV = dwKey;
	dwAlignedData = DSTU7624_CBC_MODE_OUTPUT_DATA(
		dwData * 8, dwIV * 8) / 8;

	if(dwProtectedData !=
		dwIV + dwAlignedData + dwIV + 1)
	{
		return CSP_ERROR_BAD_PARAMETERS;
	}

	if(pcPassword == NULL && pKey == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pcPassword != NULL)
	{
		dwError = DSTU7564HashData(
			(PBYTE) pcPassword,
			(DWORD) strlen(pcPassword),
			(PBYTE) pSBox, dwKey, bKey);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pKey = (PBYTE) bKey;
	}

	if(pIV == NULL)
	{
		dwError = GeneratePRNSequence(bIV, dwIV);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pIV = (PBYTE) bIV;
	}

	memcpy(pbProtectedData, pIV, dwIV);
	memcpy(pbProtectedData + dwIV, pbData, dwData);

	dwError = DSTU7624GetDataCMAC(
		pbProtectedData + dwIV, dwData, pSBox,
		pKey, dwKey, dwIV, pbProtectedData +
		dwIV + dwAlignedData, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

		return dwError;
	}

	dwError = DSTU7624CBCEncryptData(
		pbProtectedData + dwIV, dwData,
		dwAlignedData, pSBox, pKey, dwKey,
		pIV, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

		return dwError;
	}

	memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

	*(pbProtectedData + dwIV + dwAlignedData + dwIV) =
		(dwData != dwAlignedData);

	return CSP_NO_ERROR;
#else // CSP_DSTU7624 && CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624 && CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624UnprotectData(
	PBYTE pbProtectedData,
	DWORD dwProtectedData,
	PBYTE *ppbData,
	PDWORD pdwData,
	DSTU7624_SBOX pSBox,
	PCHAR pcPassword,
	PBYTE pKey,
	DWORD dwKey)
{
	CSP_TRY();

#if defined(CSP_DSTU7624) && defined(CSP_DSTU7564)
	BYTE bKey[DSTU7624_KEY_512_LENGTH];
	DWORD dwIV;
	DWORD dwAlignedData;
	DWORD dwData;
	DWORD dwError;
	BOOL bPadding;

	if (dwProtectedData < 3 * dwKey + 1)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pcPassword == NULL && pKey == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pcPassword != NULL)
	{
		dwError = DSTU7564HashData(
			(PBYTE) pcPassword,
			(DWORD) strlen(pcPassword),
			(PBYTE) pSBox, dwKey, bKey);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pKey = (PBYTE) bKey;
	}

	dwIV = dwKey;
	dwAlignedData = dwProtectedData - 2 * dwIV - 1;
	dwData = dwAlignedData;

	bPadding =
		*(pbProtectedData + dwProtectedData - 1);

	dwError = DSTU7624CBCDecryptData(
		pbProtectedData + dwIV, &dwData,
		bPadding, pSBox, pKey, dwKey,
		pbProtectedData, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

		return dwError;
	}

	dwError = DSTU7624CheckDataCMAC(
		pbProtectedData + dwIV, dwData,
		pbProtectedData + dwIV + dwAlignedData,
		dwIV, pSBox, pKey, dwKey, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

		return dwError;
	}

	memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

	*ppbData = pbProtectedData + dwIV;
	*pdwData = dwData;

	return CSP_NO_ERROR;
#else // CSP_DSTU7624 && CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624 && CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564HashKEPKey(
	DSTU4145_KEY_D pKeyD,
	DWORD dwBits,
	DSTU7564_SBOX pSBox,
	DWORD dwHash,
	DSTU7564_HASH pHash)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU7564HashKEPKeyCtx(
		&Context, pKeyD, dwBits,
		pSBox, dwHash, pHash);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7564HashKEPKeyCtx(
	PCSP_CTX pContext,
	DSTU4145_KEY_D pKeyD,
	DWORD dwBits,
	DSTU7564_SBOX pSBox,
	DWORD dwHash,
	DSTU7564_HASH pHash)
{
	CSP_TRY();

#ifdef CSP_DSTU7564
	GOST34311_HASH Hash;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pKeyD == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		if(dwHash != DSTU7564_HASH_256_LENGTH)
			return CSP_ERROR_BAD_PARAMETERS;

		if(!pContext->pHardwareCSP->HashKEPKey(Hash))
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

#ifdef HP_BIG_ENDIAN
		SWAP_BYTES_32_ARRAY_SIZE(Hash,
			sizeof(GOST34311_HASH) / sizeof(UINT));
#endif /* HP_BIG_ENDIAN */

		memcpy(pHash, Hash, dwHash);

		return CSP_NO_ERROR;
	}
	else
	{
		return DSTU7564HashData(
			(PBYTE) pKeyD, dwBits / 8,
			pSBox, dwHash, pHash);
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624WrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU7624WrapSharedKeyCtx(
		&Context, pParameterEC, pParameterP,
		pKeyDa, pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo, pWrapSBox,
		pKey, dwKey, pWrappedKey, dwWrappedKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624UnwrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU7624UnwrapSharedKeyCtx(
		&Context, pParameterEC, pParameterP,
		pKeyDa, pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo, pWrapSBox,
		pWrappedKey, dwWrappedKey, pKey, dwKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624WrapSharedKeyCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey)
{
	CSP_TRY();

#ifdef CSP_DSTU7624_WRAP
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwError;

	if(pKeyDa == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		BOOL bHardwareCompatible;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_DSTU7624_WRAP_KEY,
			bHardwareCompatible);
		if(!bHardwareCompatible)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->DSTU7624WrapSharedKey(
				pParameterEC, pParameterP, pKeyQb,
				blCofactorMethod, pbSharedInfo,
				dwSharedInfo, pWrapSBox, pKey, dwKey,
				pWrappedKey, dwWrappedKey))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(m_pBaseEx == NULL ||
			m_pBaseEx->ECDHKDFDSTU7564CalculateSharedKey == NULL ||
			m_pBaseEx->DSTU7624WrapSharedKey == NULL)
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(pContext->pPRNGState == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		BYTE SharedKey[DSTU7624_KEY_256_LENGTH];

		if(!m_pBaseEx->ECDHKDFDSTU7564CalculateSharedKey(
				pParameterEC, pParameterP, pKeyDa,
				pKeyQb, blCofactorMethod, pbSharedInfo,
				dwSharedInfo, NULL, DSTU7564_HASH_256,
				SharedKey, DSTU7624_KEY_256_LENGTH) ||
			!m_pBaseEx->DSTU7624WrapSharedKey(
				SharedKey, DSTU7624_KEY_256_LENGTH,
				pWrapSBox, pKey, dwKey, NULL,
				DSTU7624_IV_256_LENGTH, pContext->pPRNGState,
				pWrappedKey, dwWrappedKey))
		{
			memset((PVOID) SharedKey, 0,
				DSTU7624_KEY_256_LENGTH);

			return CSP_ERROR_PROGRAM_FAILURE;
		}

		memset((PVOID) SharedKey, 0,
			DSTU7624_KEY_256_LENGTH);
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624_WRAP
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624_WRAP

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624UnwrapSharedKeyCtx(
	PCSP_CTX pContext,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_D pKeyDa,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey)
{
	CSP_TRY();

#ifdef CSP_DSTU7624_WRAP
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	DWORD dwError;

	if(pKeyDa == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSP_ERROR_NOT_INITIALIZED;

		dwError = RestoreParameters(
			pParameterEC, pParameterP, FALSE);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		BOOL bHardwareCompatible;

		CSP_CHECK_COMPATIBLE_CTX(this, pContext,
			CSP_COMPATIBLE_LEVEL_HARDWARE_DSTU7624_WRAP_KEY,
			bHardwareCompatible);
		if(!bHardwareCompatible)
			return CSP_ERROR_HARDWARE_CSP_FAILURE;

		if(!pContext->pHardwareCSP->DSTU7624UnwrapSharedKey(
				pParameterEC, pParameterP, pKeyQb,
				blCofactorMethod, pbSharedInfo,
				dwSharedInfo, pWrapSBox,
				pWrappedKey, dwWrappedKey, pKey, dwKey))
		{
			return CSP_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(m_pBaseEx == NULL ||
			m_pBaseEx->ECDHKDFDSTU7564CalculateSharedKey == NULL ||
			m_pBaseEx->DSTU7624UnwrapSharedKey == NULL)
		{
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		BYTE SharedKey[DSTU7624_KEY_256_LENGTH];

		if(!m_pBaseEx->ECDHKDFDSTU7564CalculateSharedKey(
				pParameterEC, pParameterP, pKeyDa,
				pKeyQb, blCofactorMethod, pbSharedInfo,
				dwSharedInfo, NULL, DSTU7564_HASH_256,
				SharedKey, DSTU7624_KEY_256_LENGTH) ||
			!m_pBaseEx->DSTU7624UnwrapSharedKey(
				SharedKey, DSTU7624_KEY_256_LENGTH,
				pWrapSBox, pWrappedKey, dwWrappedKey,
				pKey, dwKey))
		{
			memset((PVOID) SharedKey, 0,
				DSTU7624_KEY_256_LENGTH);

			return CSP_ERROR_PROGRAM_FAILURE;
		}

		memset((PVOID) SharedKey, 0,
			DSTU7624_KEY_256_LENGTH);
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624_WRAP
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624_WRAP

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CFBStateEncryptData(
	PBYTE pbData,
	DWORD dwData,
	DWORD dwGammaBits,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624EncryptDataCFBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624EncryptDataCFBMode(
			pbData, (UINT64) dwData * 8ULL,
			dwGammaBits, *ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624CFBStateDecryptData(
	PBYTE pbData,
	DWORD dwData,
	DWORD dwGammaBits,
	PDSTU7624_STATE *ppDSTU7624State)
{
	CSP_TRY();

#ifdef CSP_DSTU7624
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU7624DecryptDataCFBMode == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(!m_pBaseEx->DSTU7624DecryptDataCFBMode(
			pbData, (UINT64) dwData * 8ULL,
			dwGammaBits, *ppDSTU7624State))
	{
		DSTU7624_RELEASE_STATE(*ppDSTU7624State);
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	return CSP_NO_ERROR;
#else // CSP_DSTU7624
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeMultiAlgoPRNG(
	DWORD dwAlgoType,
	PVOID pvAlgoSBox,
	PVOID pvAlgoKey,
	PVOID pvAlgoSeed)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = ReinitializeMultiAlgoPRNGCtx(
		&Context, dwAlgoType, pvAlgoSBox,
		pvAlgoKey, pvAlgoSeed);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	EnterCriticalSection(&m_CriticalSection);

	if (pPRNGState == NULL)
		pPRNGState = Context.pPRNGState;

	LeaveCriticalSection(&m_CriticalSection);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GeneratePRNGParameterCtx(
	PCSP_CTX pContext,
	PBYTE pbParameter,
	DWORD dwParameter)
{
	CSP_TRY();

	DWORD dwError;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL &&
		!Base.ExtensionF.TSCGIsEnable())
	{
		return CSP_ERROR_PRNG_CALL;
	}

	if(pbParameter != NULL)
	{
		if(pContext->pHardwareRNG == NULL)
		{
			if(!Base.ExtensionF.TSCGGenerateSequence(
					pbParameter, dwParameter))
			{
				return CSP_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(
				pContext, pbParameter, dwParameter);
			if(dwError != CSP_NO_ERROR)
				return dwError;
		}
	}

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::InitializeMultiAlgoPRNGCtx(
	PCSP_CTX pContext,
	DWORD dwAlgoType,
	PVOID pvAlgoSBox,
	PVOID pvAlgoKey,
	PVOID pvAlgoSeed)
{
	CSP_TRY();

	if(dwAlgoType == DSTU4145_PSEUDO_RNG_ALGO_GOST28147)
	{
		return InitializePRNGCtx(
			pContext, (PBYTE) pvAlgoSBox,
			(PUINT) pvAlgoSeed, (PUINT) pvAlgoKey);
	}

#ifdef CSP_MULTI_ALGO_PRNG
	DWORD dwError;
	DWORD dwIndex;
	DWORD dwKeyLength;
	DWORD dwSeedLength;
	BYTE Key[DSTU7624_KEY_256_LENGTH];
	BYTE WorkS[DSTU7624_BLOCK_256_LENGTH];
	BYTE Seed[DSTU7624_BLOCK_256_LENGTH];

	PGENERATE_RPRN_BYTES pfGenerateRPRNBytes;
	PDSTU4145_PSEUDO_RNG_STATE pPRNGState;
	CSP_CTX PRNGContext;
	PCSP_CTX pPRNGContext;

	UINT nAlgoType;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGAcquireState == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGSetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	switch(dwAlgoType)
	{
	case DSTU4145_PSEUDO_RNG_ALGO_DSTU7624:
		dwKeyLength = DSTU7624_KEY_256_LENGTH;
		dwSeedLength = DSTU7624_BLOCK_256_LENGTH;
		break;

	default:
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pContext->pHardwareRNG != NULL ||
		this->pPRNGState == NULL)
	{
		pfGenerateRPRNBytes = &CSP::GeneratePRNGParameterCtx;
		pPRNGContext = pContext;
	}
	else
	{
		pfGenerateRPRNBytes = &CSP::GeneratePRNSequenceCtx;
		pPRNGContext = &PRNGContext;

		memset((PVOID) &PRNGContext, 0, sizeof(CSP_CTX));
		PRNGContext.pPRNGState = this->pPRNGState;
	}

	if(pvAlgoKey != NULL)
	{
		memcpy((PVOID) Key, pvAlgoKey, dwKeyLength);
	}
	else
	{
		dwError = (this->*pfGenerateRPRNBytes)(
			pPRNGContext, Key, dwKeyLength);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(pvAlgoSeed != NULL)
	{
		memcpy((PVOID) Seed, pvAlgoSeed, dwSeedLength);
	}
	else
	{
		dwError = (this->*pfGenerateRPRNBytes)(
			pPRNGContext, Seed, dwSeedLength);
		if(dwError != CSP_NO_ERROR)
		{
			memset((PVOID) Key, 0, dwKeyLength);
			return dwError;
		}
	}

	dwError = (this->*pfGenerateRPRNBytes)(
		pPRNGContext, WorkS, dwSeedLength);
	if(dwError != CSP_NO_ERROR)
	{
		memset((PVOID) Key, 0, dwKeyLength);
		memset((PVOID) Seed, 0, dwSeedLength);
		return dwError;
	}

	for(dwIndex = 0; dwIndex < dwSeedLength; dwIndex++)
		WorkS[dwIndex] ^= Seed[dwIndex];

	SYSTEMTIME stTime;
	FILETIME FileTime;
	LARGE_INTEGER liTime;

	GetSystemTime(&stTime);
	SystemTimeToFileTime(&stTime, &FileTime);

	liTime.LowPart = FileTime.dwLowDateTime;
	liTime.HighPart = FileTime.dwHighDateTime;

	pPRNGState = m_pBaseEx->DSTU4145PseudoRNGAcquireState();
	if(pPRNGState == NULL)
	{
		memset((PVOID) Key, 0, dwKeyLength);
		memset((PVOID) Seed, 0, dwSeedLength);
		memset((PVOID) WorkS, 0, dwSeedLength);
		return CSP_ERROR_ALLOCATE_MEMORY;
	}

	nAlgoType = (UINT) dwAlgoType;

	if(!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pPRNGState, &nAlgoType,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_ALGO) ||
		(pvAlgoSBox ?
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pPRNGState, pvAlgoSBox,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_SBOX) :
		FALSE) ||
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pPRNGState, Key,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_KEY) ||
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pPRNGState, WorkS,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_S) ||
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pPRNGState, &liTime.QuadPart,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_DATETIME))
	{
		memset((PVOID) Key, 0, dwKeyLength);
		memset((PVOID) Seed, 0, dwSeedLength);
		memset((PVOID) WorkS, 0, dwSeedLength);
		return CSP_ERROR_PRNG_CALL;
	}

	memset((PVOID) Key, 0, dwKeyLength);
	memset((PVOID) Seed, 0, dwSeedLength);
	memset((PVOID) WorkS, 0, dwSeedLength);

	pContext->pPRNGState = pPRNGState;
	return CSP_NO_ERROR;
#else // CSP_MULTI_ALGO_PRNG
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_MULTI_ALGO_PRNG

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::ReinitializeMultiAlgoPRNGCtx(
	PCSP_CTX pContext,
	DWORD dwAlgoType,
	PVOID pvAlgoSBox,
	PVOID pvAlgoKey,
	PVOID pvAlgoSeed)
{
	CSP_TRY();

	if(dwAlgoType == DSTU4145_PSEUDO_RNG_ALGO_GOST28147)
	{
		return ReinitializePRNGCtx(
			pContext, (PBYTE) pvAlgoSBox,
			(PUINT) pvAlgoSeed, (PUINT) pvAlgoKey);
	}

#ifdef CSP_MULTI_ALGO_PRNG
	DWORD dwError;
	DWORD dwIndex;
	DWORD dwKeyLength;
	DWORD dwSeedLength;
	BYTE Key[DSTU7624_KEY_256_LENGTH];
	BYTE WorkS[DSTU7624_BLOCK_256_LENGTH];
	BYTE Seed[DSTU7624_BLOCK_256_LENGTH];

	UINT nAlgoType;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
	{
		return InitializeMultiAlgoPRNGCtx(
			pContext, dwAlgoType, pvAlgoSBox,
			pvAlgoKey, pvAlgoSeed);
	}

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGLockState == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGUnlockState == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGSetStateParameters == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	switch(dwAlgoType)
	{
	case DSTU4145_PSEUDO_RNG_ALGO_DSTU7624:
		dwKeyLength = DSTU7624_KEY_256_LENGTH;
		dwSeedLength = DSTU7624_BLOCK_256_LENGTH;
		break;

	default:
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pvAlgoKey != NULL)
	{
		memcpy((PVOID) Key, pvAlgoKey, dwKeyLength);
	}
	else
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, Key, dwKeyLength);
		if(dwError != CSP_NO_ERROR)
			return dwError;
	}

	if(pvAlgoSeed != NULL)
	{
		memcpy((PVOID) Seed, pvAlgoSeed, dwSeedLength);
	}
	else
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, Seed, dwSeedLength);
		if(dwError != CSP_NO_ERROR)
		{
			memset((PVOID) Key, 0, dwKeyLength);
			return dwError;
		}
	}

	dwError = GenerateRPRNSequenceCtx(
		pContext, WorkS, dwSeedLength);
	if(dwError != CSP_NO_ERROR)
	{
		memset((PVOID) Key, 0, dwKeyLength);
		memset((PVOID) Seed, 0, dwSeedLength);
		return dwError;
	}

	for(dwIndex = 0; dwIndex < dwSeedLength; dwIndex++)
		WorkS[dwIndex] ^= Seed[dwIndex];

	SYSTEMTIME stTime;
	FILETIME FileTime;
	LARGE_INTEGER liTime;

	GetSystemTime(&stTime);
	SystemTimeToFileTime(&stTime, &FileTime);

	liTime.LowPart = FileTime.dwLowDateTime;
	liTime.HighPart = FileTime.dwHighDateTime;

	nAlgoType = (UINT) dwAlgoType;

	m_pBaseEx->DSTU4145PseudoRNGLockState(
		pContext->pPRNGState);

	if(!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pContext->pPRNGState, &nAlgoType,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_ALGO) ||
		(pvAlgoSBox ?
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pContext->pPRNGState, pvAlgoSBox,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_SBOX) :
		FALSE) ||
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pContext->pPRNGState, Key,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_KEY) ||
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pContext->pPRNGState, WorkS,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_S) ||
		!m_pBaseEx->DSTU4145PseudoRNGSetStateParameters(
			pContext->pPRNGState, &liTime.QuadPart,
			DSTU4145_PSEUDO_RNG_PARAMETERS_TYPE_DATETIME))
	{
		m_pBaseEx->DSTU4145PseudoRNGUnlockState(
			pContext->pPRNGState);

		memset((PVOID) Key, 0, dwKeyLength);
		memset((PVOID) Seed, 0, dwSeedLength);
		memset((PVOID) WorkS, 0, dwSeedLength);
		return CSP_ERROR_PRNG_CALL;
	}

	m_pBaseEx->DSTU4145PseudoRNGUnlockState(
		pContext->pPRNGState);

	memset((PVOID) Key, 0, dwKeyLength);
	memset((PVOID) Seed, 0, dwSeedLength);
	memset((PVOID) WorkS, 0, dwSeedLength);
	return CSP_NO_ERROR;

#else // CSP_MULTI_ALGO_PRNG
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_MULTI_ALGO_PRNG

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624ProtectDataEx(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbProtectedData,
	DWORD dwProtectedData,
	DSTU7624_SBOX pSBox,
	PCHAR pcPassword,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pIV,
	DWORD dwIV,
	DWORD dwMac)
{
	CSP_TRY();

#if defined(CSP_DSTU7624) && defined(CSP_DSTU7564)
	BYTE bKey[DSTU7624_KEY_512_LENGTH];
	BYTE bIV[DSTU7624_KEY_512_LENGTH];
	BYTE bTail;
	BYTE bMacFactor;
	DWORD dwAlignedData;
	DWORD dwError;

	bTail = 0;

	if(dwKey == DSTU7624_KEY_512_LENGTH)
		bTail |= 0x02;

	if(dwIV != dwKey && dwIV * 2 != dwKey)
		return CSP_ERROR_BAD_PARAMETERS;

	if(dwIV < dwKey)
		bTail |= 0x04;

	bMacFactor = 0;
	while(bMacFactor < 4 && dwKey > dwMac << bMacFactor)
		bMacFactor++;

	if(dwKey != dwMac << bMacFactor)
		return CSP_ERROR_BAD_PARAMETERS;

	bTail |= bMacFactor << 3;

	dwAlignedData = DSTU7624_CBC_MODE_OUTPUT_DATA(
		dwData * 8, dwIV * 8) / 8;

	if(dwData != dwAlignedData)
		bTail |= 0x01;

	if(dwProtectedData !=
		dwIV + dwAlignedData + dwMac + 1)
	{
		return CSP_ERROR_BAD_PARAMETERS;
	}

	if(pcPassword == NULL && pKey == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pcPassword != NULL)
	{
		dwError = DSTU7564HashData(
			(PBYTE) pcPassword,
			(DWORD) strlen(pcPassword),
			(PBYTE) pSBox, dwKey, bKey);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pKey = (PBYTE) bKey;
	}

	if(pIV == NULL)
	{
		dwError = GeneratePRNSequence(bIV, dwIV);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pIV = (PBYTE) bIV;
	}

	memcpy(pbProtectedData, pIV, dwIV);
	memcpy(pbProtectedData + dwIV, pbData, dwData);

	dwError = DSTU7624GetDataCMAC(
		pbProtectedData + dwIV, dwData, pSBox,
		pKey, dwKey, dwIV, pbProtectedData +
		dwIV + dwAlignedData, dwMac);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);
		return dwError;
	}

	dwError = DSTU7624CBCEncryptData(
		pbProtectedData + dwIV, dwData,
		dwAlignedData, pSBox, pKey, dwKey,
		pIV, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);
		return dwError;
	}

	memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

	*(pbProtectedData + dwIV + dwAlignedData + dwMac) =
		bTail;

	return CSP_NO_ERROR;
#else // CSP_DSTU7624 && CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624 && CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624UnprotectDataEx(
	PBYTE pbProtectedData,
	DWORD dwProtectedData,
	PBYTE *ppbData,
	PDWORD pdwData,
	DSTU7624_SBOX pSBox,
	PCHAR pcPassword,
	PBYTE pKey,
	DWORD dwKey)
{
	CSP_TRY();

#if defined(CSP_DSTU7624) && defined(CSP_DSTU7564)
	BYTE bKey[DSTU7624_KEY_512_LENGTH];
	DWORD dwKeyExpected;
	DWORD dwIV;
	DWORD dwMac;
	DWORD dwAlignedData;
	DWORD dwData;
	DWORD dwError;
	BYTE bTail;

	if(dwProtectedData == 0)
		return CSP_ERROR_BAD_PARAMETERS;

	bTail = *(pbProtectedData + dwProtectedData - 1);

	dwKeyExpected = DSTU7624_KEY_256_LENGTH;
	if(bTail & 0x02)
		dwKeyExpected <<= 1;

	dwIV = dwKeyExpected;
	if(bTail & 0x04)
		dwIV >>= 1;

	dwMac = dwKeyExpected;
	if(bTail & 0x18)
		dwMac = dwKeyExpected >> ((bTail >> 3) & 0x03);

	if(dwProtectedData < 2 * dwIV + dwMac + 1)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pcPassword == NULL && pKey == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pcPassword != NULL)
	{
		dwError = DSTU7564HashData(
			(PBYTE) pcPassword,
			(DWORD) strlen(pcPassword),
			(PBYTE) pSBox, dwKeyExpected, bKey);
		if(dwError != CSP_NO_ERROR)
			return dwError;

		pKey = (PBYTE) bKey;
		dwKey = dwKeyExpected;
	}
	else if(dwKey != dwKeyExpected)
		return CSP_ERROR_BAD_PARAMETERS;

	dwAlignedData = dwProtectedData - dwIV - dwMac - 1;
	dwData = dwAlignedData;

	dwError = DSTU7624CBCDecryptData(
		pbProtectedData + dwIV, &dwData,
		bTail & 0x01, pSBox, pKey, dwKey,
		pbProtectedData, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);
		return dwError;
	}

	dwError = DSTU7624CheckDataCMAC(
		pbProtectedData + dwIV, dwData,
		pbProtectedData + dwIV + dwAlignedData,
		dwMac, pSBox, pKey, dwKey, dwIV);
	if(dwError != CSP_NO_ERROR)
	{
		memset(bKey, 0, DSTU7624_KEY_512_LENGTH);
		return dwError;
	}

	memset(bKey, 0, DSTU7624_KEY_512_LENGTH);

	*ppbData = pbProtectedData + dwIV;
	*pdwData = dwData;

	return CSP_NO_ERROR;
#else // CSP_DSTU7624 && CSP_DSTU7564
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624 && CSP_DSTU7564

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckParametersD(
	PBYTE pbParameters,
	DWORD dwParameters)
{
	CSP_TRY();

	DWORD dwError;

	dwError = RestoreParametersD(
		pbParameters, dwParameters, TRUE);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateKeysD(
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbKeyQ,
	DWORD dwKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = GenerateKeysDCtx(
		&Context, pbParameters, dwParameters,
		pbKeyD, dwKeyD, pbKeyQ, dwKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::GenerateKeysDCtx(
	PCSP_CTX pContext,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbKeyQ,
	DWORD dwKeyQ)
{
	CSP_TRY();

	UINT dwBits;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbParameters,
			DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS |
			(dwParameters <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pContext->pPRNGState,
			DSTU4145_PARAMETERS_TYPE_PRNG) ||
		!Base.F.DSTU4145GenerateParameters(
			pDSTU4145State, DSTU4145_FLAG_GENERATE_KEYS) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) pbKeyD,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_D |
			(dwKeyD <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) pbKeyQ,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_Q |
			(dwKeyQ <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_RELEASE_STATE();

	DSTU4145_SET_DENSE_PARAMETERS_BITS(
		pbParameters, dwBits);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckKeysD(
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbKeyQ,
	DWORD dwKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = CheckKeysDCtx(
		&Context, pbParameters, dwParameters,
		pbKeyD, dwKeyD, pbKeyQ, dwKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::CheckKeysDCtx(
	PCSP_CTX pContext,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbKeyQ,
	DWORD dwKeyQ)
{
	CSP_TRY();

	PBYTE pbStateKeyQ;
	UINT dwM;
	UINT dwStateKeyQ;
	UINT dwBits;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	DSTU4145_ACQUIRE_STATE_WITH_CHECK();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbParameters,
			DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS |
			(dwParameters <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbKeyD,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_D |
			(dwKeyD <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	DSTU4145_SET_DENSE_PARAMETERS_BITS(
		pbParameters, dwBits);

	if(pbKeyQ != NULL)
	{
		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pbKeyQ,
				DSTU4145_PARAMETERS_TYPE_DENSE_KEY_Q |
				(dwKeyQ <<
					DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		dwM = DSTU4145_DENSE_PARAMETERS_M(pbParameters);
		dwStateKeyQ = DSTU4145_DENSE_NUMBER_SIZE(dwM);

		pbStateKeyQ = new BYTE[dwStateKeyQ];
		if(pbStateKeyQ == NULL)
		{
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_ALLOCATE_MEMORY;
		}

		memset((PVOID) pbStateKeyQ, 0, dwStateKeyQ);

		if(!Base.F.DSTU4145SetStateParameters(
				pDSTU4145State, (PVOID) pContext->pPRNGState,
				DSTU4145_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSTU4145GenerateParameters(
				pDSTU4145State, DSTU4145_FLAG_GENERATE_KEY_Q) ||
			!Base.F.DSTU4145GetStateParameters(
				pDSTU4145State, (PVOID) pbStateKeyQ,
				DSTU4145_PARAMETERS_TYPE_DENSE_KEY_Q |
				(dwStateKeyQ <<
					DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
		{
			delete[] pbStateKeyQ;
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_PROGRAM_FAILURE;
		}

		if(memcmp((PVOID) pbKeyQ, (PVOID) pbStateKeyQ,
				(dwKeyQ < dwStateKeyQ) ? dwKeyQ : dwStateKeyQ))
		{
			delete[] pbStateKeyQ;
			DSTU4145_RELEASE_STATE();
			return CSP_ERROR_WRONG_PARAMETERS;
		}

		for(UINT i = dwKeyQ; i < dwStateKeyQ; i++)
		{
			if(pbStateKeyQ[i] != 0)
			{
				delete[] pbStateKeyQ;
				DSTU4145_RELEASE_STATE();
				return CSP_ERROR_WRONG_PARAMETERS;
			}
		}

		delete[] pbStateKeyQ;
	}

	DSTU4145_RELEASE_STATE();

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RecoverPublicKeyD(
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbKeyQ,
	DWORD dwKeyQ)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = RecoverPublicKeyDCtx(
		&Context, pbParameters, dwParameters,
		pbKeyD, dwKeyD, pbKeyQ, dwKeyQ);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RecoverPublicKeyDCtx(
	PCSP_CTX pContext,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbKeyQ,
	DWORD dwKeyQ)
{
	CSP_TRY();

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	UINT dwBits;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	DSTU4145_ACQUIRE_STATE_WITH_CHECK();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbParameters,
			DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS |
			(dwParameters <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbKeyD,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_D |
			(dwKeyD <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	DSTU4145_SET_DENSE_PARAMETERS_BITS(
		pbParameters, dwBits);

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pContext->pPRNGState,
			DSTU4145_PARAMETERS_TYPE_PRNG) ||
		!Base.F.DSTU4145GenerateParameters(
			pDSTU4145State, DSTU4145_FLAG_GENERATE_KEY_Q) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) pbKeyQ,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_Q |
			(dwKeyQ <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	DSTU4145_RELEASE_STATE();

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::RestoreParametersD(
	PBYTE pbParameters,
	DWORD dwParameters,
	BOOL bWithCheck)
{
	CSP_TRY();

	UINT dwBits;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	DSTU4145_ACQUIRE_STATE_EX(bWithCheck);

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbParameters,
			DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS |
			(dwParameters <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	DSTU4145_RELEASE_STATE();

	DSTU4145_SET_DENSE_PARAMETERS_BITS(
		pbParameters, dwBits);

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SignDSTU7564HashD(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbSignature,
	DWORD dwSignature)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = SignDSTU7564HashDCtx(
		&Context, dwHash, pHash,
		pbParameters, dwParameters,
		pbKeyD, dwKeyD, pbSignature,
		dwSignature);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::SignDSTU7564HashDCtx(
	PCSP_CTX pContext,
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyD,
	DWORD dwKeyD,
	PBYTE pbSignature,
	DWORD dwSignature)
{
	CSP_TRY();

	PC_PERFORMANCE_TEST_START(SignDSTU7564HashD)

	UINT Hash[DSTU7564_HASH_512_LENGTH / sizeof(UINT)];
	UINT dwHashWords;
	UINT dwBits;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(dwHash > DSTU7564_HASH_512_LENGTH)
		return CSP_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbParameters,
			DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS |
			(dwParameters <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbKeyD,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_D |
			(dwKeyD <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
	CopyMemory((PVOID) Hash, pHash, dwHash);
	dwHashWords =
		(dwHash + sizeof(UINT) - 1) / sizeof(UINT);

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY_SIZE(Hash, dwHashWords);
#endif /* HP_BIG_ENDIAN */

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pContext->pPRNGState,
			DSTU4145_PARAMETERS_TYPE_PRNG) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) &dwHashWords,
			DSTU4145_PARAMETERS_TYPE_HASH_SIZE) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) Hash,
			DSTU4145_PARAMETERS_TYPE_HASH) ||
		!Base.F.DSTU4145SignHash(pDSTU4145State) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) pbSignature,
			DSTU4145_PARAMETERS_TYPE_DENSE_SIGNATURE |
			(dwSignature <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145GetStateParameters(
			pDSTU4145State, (PVOID) &dwBits,
			DSTU4145_PARAMETERS_TYPE_P_LENGTH))
	{
		ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
	DSTU4145_RELEASE_STATE();

	DSTU4145_SET_DENSE_PARAMETERS_BITS(
		pbParameters, dwBits);

	PC_PERFORMANCE_TEST_STOP(SignDSTU7564HashD)

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::VerifyDSTU7564HashSignatureD(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyQ,
	DWORD dwKeyQ,
	PBYTE pbSignature,
	DWORD dwSignature)
{
	CSP_TRY();

	PC_PERFORMANCE_TEST_START(VerifyDSTU7564HashSignatureD)

	UINT Hash[DSTU7564_HASH_512_LENGTH / sizeof(UINT)];
	UINT dwHashWords;

	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(dwHash > DSTU7564_HASH_512_LENGTH)
		return CSP_ERROR_BAD_PARAMETERS;

	DSTU4145_ACQUIRE_STATE();

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbParameters,
			DSTU4145_PARAMETERS_TYPE_DENSE_PARAMETERS |
			(dwParameters <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbKeyQ,
			DSTU4145_PARAMETERS_TYPE_DENSE_KEY_Q |
			(dwKeyQ <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) pbSignature,
			DSTU4145_PARAMETERS_TYPE_DENSE_SIGNATURE |
			(dwSignature <<
				DSTU4145_PARAMETERS_TYPE_SIZE_OFFSET)))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_WRONG_PARAMETERS;
	}

	ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
	CopyMemory((PVOID) Hash, pHash, dwHash);
	dwHashWords =
		(dwHash + sizeof(UINT) - 1) / sizeof(UINT);

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY_SIZE(Hash, dwHashWords);
#endif /* HP_BIG_ENDIAN */

	if(!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) &dwHashWords,
			DSTU4145_PARAMETERS_TYPE_HASH_SIZE) ||
		!Base.F.DSTU4145SetStateParameters(
			pDSTU4145State, (PVOID) Hash,
			DSTU4145_PARAMETERS_TYPE_HASH))
	{
		ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	ZeroMemory((PVOID) Hash, DSTU7564_HASH_512_LENGTH);

	if(!Base.F.DSTU4145VerifySignature(pDSTU4145State))
	{
		DSTU4145_RELEASE_STATE();
		return CSP_ERROR_BAD_SIGNATURE;
	}

	DSTU4145_RELEASE_STATE();

	PC_PERFORMANCE_TEST_STOP(VerifyDSTU7564HashSignatureD)

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624WrapSharedKeyD(
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyDa,
	DWORD dwKeyDa,
	PBYTE pbKeyQb,
	DWORD dwKeyQb,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU7624WrapSharedKeyDCtx(
		&Context, pbParameters, dwParameters,
		pbKeyDa, dwKeyDa, pbKeyQb, dwKeyQb,
		pbSharedInfo, dwSharedInfo, pWrapSBox,
		pKey, dwKey, pWrappedKey, dwWrappedKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624WrapSharedKeyDCtx(
	PCSP_CTX pContext,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyDa,
	DWORD dwKeyDa,
	PBYTE pbKeyQb,
	DWORD dwKeyQb,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey)
{
	CSP_TRY();

#ifdef CSP_DSTU7624_WRAP
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->ECDHKDFDSTU7564CalculateDenseSharedKey == NULL ||
		m_pBaseEx->DSTU7624WrapSharedKey == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	if(pContext->pPRNGState == NULL)
		return CSP_ERROR_NOT_INITIALIZED;

	BYTE SharedKey[DSTU7624_KEY_256_LENGTH];

	if(!m_pBaseEx->ECDHKDFDSTU7564CalculateDenseSharedKey(
			pbParameters, dwParameters,
			pbKeyDa, dwKeyDa, pbKeyQb, dwKeyQb,
			pbSharedInfo, dwSharedInfo, NULL,
			DSTU7564_HASH_256, SharedKey,
			DSTU7624_KEY_256_LENGTH) ||
		!m_pBaseEx->DSTU7624WrapSharedKey(
			SharedKey, DSTU7624_KEY_256_LENGTH,
			pWrapSBox, pKey, dwKey, NULL,
			DSTU7624_IV_256_LENGTH, pContext->pPRNGState,
			pWrappedKey, dwWrappedKey))
	{
		memset((PVOID) SharedKey, 0,
			DSTU7624_KEY_256_LENGTH);

		return CSP_ERROR_PROGRAM_FAILURE;
	}

	memset((PVOID) SharedKey, 0,
		DSTU7624_KEY_256_LENGTH);

	return CSP_NO_ERROR;
#else // CSP_DSTU7624_WRAP
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624_WRAP

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624UnwrapSharedKeyD(
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyDa,
	DWORD dwKeyDa,
	PBYTE pbKeyQb,
	DWORD dwKeyQb,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey)
{
	CSP_TRY();

	CSP_CTX Context;
	DWORD dwError;

	CSP_CTX_INITIALIZE(Context);

	dwError = DSTU7624UnwrapSharedKeyDCtx(
		&Context, pbParameters, dwParameters,
		pbKeyDa, dwKeyDa, pbKeyQb, dwKeyQb,
		pbSharedInfo, dwSharedInfo, pWrapSBox,
		pWrappedKey, dwWrappedKey, pKey, dwKey);
	if(dwError != CSP_NO_ERROR)
		return dwError;

	return CSP_NO_ERROR;

	CSP_CATCH_DWORD();
}

//----------------------------------------------------------------------------------------------------------------------

DWORD WINAPI CSP::DSTU7624UnwrapSharedKeyDCtx(
	PCSP_CTX pContext,
	PBYTE pbParameters,
	DWORD dwParameters,
	PBYTE pbKeyDa,
	DWORD dwKeyDa,
	PBYTE pbKeyQb,
	DWORD dwKeyQb,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	DSTU7624_SBOX pWrapSBox,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey)
{
	CSP_TRY();

#ifdef CSP_DSTU7624_WRAP
	if(!(m_dwState & CSP_STATE_LIBRARIES_LOADED))
		return CSP_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSP_ERROR_BAD_PARAMETERS;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->ECDHKDFDSTU7564CalculateDenseSharedKey == NULL ||
		m_pBaseEx->DSTU7624UnwrapSharedKey == NULL)
	{
		return CSP_ERROR_PROGRAM_FAILURE;
	}

	BYTE SharedKey[DSTU7624_KEY_256_LENGTH];

	if(!m_pBaseEx->ECDHKDFDSTU7564CalculateDenseSharedKey(
			pbParameters, dwParameters,
			pbKeyDa, dwKeyDa, pbKeyQb, dwKeyQb,
			pbSharedInfo, dwSharedInfo, NULL,
			DSTU7564_HASH_256, SharedKey,
			DSTU7624_KEY_256_LENGTH) ||
		!m_pBaseEx->DSTU7624UnwrapSharedKey(
			SharedKey, DSTU7624_KEY_256_LENGTH,
			pWrapSBox, pWrappedKey, dwWrappedKey,
			pKey, dwKey))
	{
		memset((PVOID) SharedKey, 0,
			DSTU7624_KEY_256_LENGTH);

		return CSP_ERROR_PROGRAM_FAILURE;
	}

	memset((PVOID) SharedKey, 0,
		DSTU7624_KEY_256_LENGTH);

	return CSP_NO_ERROR;
#else // CSP_DSTU7624_WRAP
	return CSP_ERROR_PROGRAM_FAILURE;
#endif // CSP_DSTU7624_WRAP

	CSP_CATCH_DWORD();
}

//======================================================================================================================
