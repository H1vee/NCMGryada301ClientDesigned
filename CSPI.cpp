//==============================================================================

#include "CSPI.h"

//==============================================================================

#define GOST28147_ACQUIRE_STATE() \
	PGOST28147_STATE pGOST28147State; \
	pGOST28147State = Base.F.GOST28147AcquireState(); \
	if(pGOST28147State == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define GOST28147_RELEASE_STATE() \
	Base.F.GOST28147ReleaseState(pGOST28147State);

//------------------------------------------------------------------------------

#define TDEA_ACQUIRE_STATE() \
	PTDEA_STATE pTDEAState; \
	pTDEAState = Base.F.TDEAAcquireState(); \
	if(pTDEAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define TDEA_RELEASE_STATE() \
	Base.F.TDEAReleaseState(pTDEAState);

//------------------------------------------------------------------------------

#define AES_ACQUIRE_STATE() \
	PAES_STATE pAESState; \
	pAESState = Base.F.AESAcquireState(); \
	if(pAESState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define AES_RELEASE_STATE() \
	Base.F.AESReleaseState(pAESState);

//------------------------------------------------------------------------------

#define GOST34311_ACQUIRE_STATE() \
	PGOST34311_STATE pGOST34311State; \
	pGOST34311State = Base.F.GOST34311AcquireState(); \
	if(pGOST34311State == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define GOST34311_RELEASE_STATE() \
	Base.F.GOST34311ReleaseState(pGOST34311State);

//------------------------------------------------------------------------------

#define ECDSA_ACQUIRE_STATE() \
	PECDSA_STATE pECDSAState; \
	pECDSAState = Base.F.ECDSAAcquireState(FALSE); \
	if(pECDSAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define ECDSA_ACQUIRE_STATE_WITH_CHECK() \
	PECDSA_STATE pECDSAState; \
	pECDSAState = Base.F.ECDSAAcquireState(TRUE); \
	if(pECDSAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define ECDSA_RELEASE_STATE() \
	Base.F.ECDSAReleaseState(pECDSAState);

//------------------------------------------------------------------------------

#define DSTU4145_PRNG_INITIALIZE() \
	pPRNGState = Base.F.DSTU4145PseudoRNGInitialize(WorkS, \
	DateTime, Key, SBox); \
	if(pPRNGState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define DSTU4145_PRNG_DEINITIALIZE() \
	if(pPRNGState != NULL) \
{ \
	Base.F.DSTU4145PseudoRNGDeinitialize(pPRNGState); \
	pPRNGState = NULL; \
}

//------------------------------------------------------------------------------

#define SHA_ACQUIRE_STATE() \
	PSHA_STATE pSHAState; \
	pSHAState = Base.F.SHAAcquireState(); \
	if(pSHAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define SHA_RELEASE_STATE() \
	Base.F.SHAReleaseState(pSHAState);

//------------------------------------------------------------------------------

#define RSA_ACQUIRE_STATE() \
	PRSA_STATE pRSAState; \
	pRSAState = Base.F.RSAAcquireState(FALSE); \
	if(pRSAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define RSA_ACQUIRE_STATE_WITH_CHECK() \
	PRSA_STATE pRSAState; \
	pRSAState = Base.F.RSAAcquireState(TRUE); \
	if(pRSAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define RSA_RELEASE_STATE() \
	Base.F.RSAReleaseState(pRSAState);

//------------------------------------------------------------------------------

#define DSA_ACQUIRE_STATE() \
	PDSA_STATE pDSAState; \
	pDSAState = Base.F.DSAAcquireState(FALSE); \
	if(pDSAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define DSA_ACQUIRE_STATE_WITH_CHECK() \
	PDSA_STATE pDSAState; \
	pDSAState = Base.F.DSAAcquireState(TRUE); \
	if(pDSAState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define DSA_RELEASE_STATE() \
	Base.F.DSAReleaseState(pDSAState);

//------------------------------------------------------------------------------

#define SHA1_HMAC_ACQUIRE_STATE() \
	if (m_pBaseEx == NULL || m_pBaseEx->SHA1HMACAcquireState == NULL) \
	return CSPI_ERROR_PROGRAM_FAILURE; \
	PSHA1_HMAC_STATE pSHA1HMACState; \
	pSHA1HMACState = m_pBaseEx->SHA1HMACAcquireState(); \
	if(pSHA1HMACState == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define SHA1_HMAC_RELEASE_STATE() \
	if (m_pBaseEx == NULL || m_pBaseEx->SHA1HMACReleaseState == NULL) \
	return CSPI_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->SHA1HMACReleaseState(pSHA1HMACState);

//------------------------------------------------------------------------------

#define RC2_ACQUIRE_STATE() \
	if (m_pBaseEx == NULL || m_pBaseEx->RC2AcquireState == NULL) \
	return CSPI_ERROR_PROGRAM_FAILURE; \
	PRC2_STATE pRC2State; \
	pRC2State = m_pBaseEx->RC2AcquireState(); \
	if(pRC2State == NULL) \
	return CSPI_ERROR_ALLOCATE_MEMORY;

//------------------------------------------------------------------------------

#define RC2_RELEASE_STATE() \
	if (m_pBaseEx == NULL || m_pBaseEx->RC2ReleaseState == NULL) \
	return CSPI_ERROR_PROGRAM_FAILURE; \
	m_pBaseEx->RC2ReleaseState(pRC2State);

//==============================================================================

#define CSPI_BAD_HRNG_INITIALIZE_SEQUENCES_LIMIT 2
#define CSPI_BAD_HRNG_SEQUENCES_LIMIT 16

//==============================================================================

#ifndef OS_NO_EXCEPTIONS
#define CSPI_TRY() \
	__try {

#define CSPI_CATCH() \
} __except(EXCEPTION_EXECUTE_HANDLER){ return; }

#define CSPI_CATCH_DWORD() \
}__except(EXCEPTION_EXECUTE_HANDLER){ \
	return CSPI_ERROR_PROGRAM_FAILURE; }
#else
#define CSPI_TRY() 
#define CSPI_CATCH()
#define CSPI_CATCH_DWORD()
#endif

//==============================================================================

#ifdef CSPI_SBOX_UA

GOST28147_COMPRESSED_SBOX DefaultPRNGSBox =
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

#else // CSPI_SBOX_UA

GOST28147_COMPRESSED_SBOX DefaultPRNGSBox =
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

#endif // CSPI_SBOX_UA

//------------------------------------------------------------------------------

#ifdef CSPI_SBOX_UA

GOST28147_COMPRESSED_SBOX DefaultProtectionSBox =
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

#else // CSPI_SBOX_UA

GOST28147_COMPRESSED_SBOX DefaultProtectionSBox =
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

#endif // CSPI_SBOX_UA

//------------------------------------------------------------------------------

#ifdef CSPI_SBOX_UA

GOST28147_COMPRESSED_SBOX DefaultHashSBox =
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

#else // CSPI_SBOX_UA

GOST28147_COMPRESSED_SBOX DefaultHashSBox =
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

#endif // CSPI_SBOX_UA

//==============================================================================

BOOL				g_bNoCSPISelfTests = FALSE;

//==============================================================================

CSPI::CSPI()
{
	pPRNGState = NULL;

	m_pHardwareRNG = NULL;
	m_pHardwareCSP = NULL;

	m_dwState = 0;

	m_pBaseEx = NULL;

	Parameters.SetCSP(this);
}

//------------------------------------------------------------------------------

CSPI::~CSPI()
{
	DSTU4145_PRNG_DEINITIALIZE();

	Parameters.SetCSP(NULL);

	if(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED)
	{
		DeleteCriticalSection(&m_CriticalSection);

		Base.UnloadEx(&m_pBaseEx);
		Base.Unload();
	}
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::Initialize()
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
	{
		if(!Base.Load())
			return CSPI_ERROR_LOAD_CSP_LIBRARY;

#ifndef CSPI_DISABLE_SELF_TESTS
		if(!g_bNoCSPISelfTests)
		{
			if(!Base.F.GOST28147SelfTest() ||
				!Base.F.GOST34311SelfTest() ||
				!Base.F.DSTU4145PseudoRNGSelfTest() ||
				!Base.F.AESSelfTest() ||
				!Base.F.TDEASelfTest() ||
				!Base.F.RSASelfTest(FALSE) ||
				!Base.F.DSASelfTest(FALSE) ||
				!Base.F.ECDSASelfTest(0) ||
				!Base.F.SHASelfTest() ||
				!Base.F.DHSelfTest(FALSE) ||
				!Base.F.ECDHSelfTest(FALSE))
			{
				return CSPI_ERROR_LIBRARIES_CORRUPTED;
			}
		}
#endif // CSPI_DISABLE_SELF_TESTS

		InitializeCriticalSection(&m_CriticalSection);

		m_dwState |= CSPI_STATE_CSP_LIBRARIES_LOADED;

		Base.LoadEx(&m_pBaseEx);

#ifdef CSPI_PKCS12
#ifndef CSPI_DISABLE_SELF_TESTS
		if(!g_bNoCSPISelfTests)
		{
			if(m_pBaseEx != NULL &&
				m_pBaseEx->RC2SelfTest != NULL)
			{
				if(!m_pBaseEx->RC2SelfTest())
					return CSPI_ERROR_LIBRARIES_CORRUPTED;
			}

			if(m_pBaseEx != NULL &&
				m_pBaseEx->SHA1HMACSelfTest != NULL)
			{
				if(!m_pBaseEx->SHA1HMACSelfTest())
					return CSPI_ERROR_LIBRARIES_CORRUPTED;
			}

			if(m_pBaseEx != NULL &&
				m_pBaseEx->PKCS12PBKDFSelfTest != NULL)
			{
				if(!m_pBaseEx->PKCS12PBKDFSelfTest())
					return CSPI_ERROR_LIBRARIES_CORRUPTED;
			}

			if(m_pBaseEx != NULL &&
				m_pBaseEx->PBKDF2ISelfTest != NULL)
			{
				if(!m_pBaseEx->PBKDF2ISelfTest(FALSE))
					return CSPI_ERROR_LIBRARIES_CORRUPTED;
			}
		}
#endif // CSPI_DISABLE_SELF_TESTS
#endif // CSPI_PKCS12

#ifdef CSPI_ECDSA_COUPLE
#ifndef CSPI_DISABLE_SELF_TESTS
		if(!g_bNoCSPISelfTests)
		{
			if(m_pBaseEx != NULL &&
				m_pBaseEx->ECDSACoupleSelfTest != NULL)
			{
				if(!m_pBaseEx->ECDSACoupleSelfTest())
					return CSPI_ERROR_LIBRARIES_CORRUPTED;
			}
		}
#endif // CSPI_DISABLE_SELF_TESTS
#endif // CSPI_ECDSA_COUPLE
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializePRNG(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ReinitializePRNGCtx(
		&Context, pSBox, pSeed, pKey);
	if(dwError != CSPI_NO_ERROR)
		return dwError;

	EnterCriticalSection(&m_CriticalSection);

	if (pPRNGState == NULL)
		pPRNGState = Context.pPRNGState;

	LeaveCriticalSection(&m_CriticalSection);

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeHRNG(
	ICSPIHardwareRNG *pHardwareRNG)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	SetHRNG(NULL);

	CSPI_CTX_INITIALIZE(Context);
	Context.pHardwareRNG = pHardwareRNG;

	dwError = InitializeHRNGCtx(
		&Context);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return SetHRNG(pHardwareRNG);

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GeneratePRNSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = GeneratePRNSequenceCtx(
		&Context, pbSequence, dwSequence);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GenerateRNSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = GenerateRNSequenceCtx(
		&Context, pbSequence, dwSequence);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GenerateRPRNSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = GenerateRPRNSequenceCtx(
		&Context, pbSequence, dwSequence);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ProtectData(
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
	CSPI_TRY();

	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pSBox == NULL)
		pSBox = DefaultProtectionSBox;

	GOST28147_ACQUIRE_STATE();
	GOST34311_ACQUIRE_STATE();

	if(pcPassword != NULL || pKey != NULL)
	{
		GOST34311_HASH Hash;

		if(pcPassword != NULL)
		{
			if(!Base.F.GOST34311SetStateParameters(
					pGOST34311State, (PVOID) pSBox,
					GOST34311_PARAMETERS_TYPE_SBOX) ||
				!Base.F.GOST34311SetStateParameters(
					pGOST34311State, (PVOID) pInitialHash,
					GOST34311_PARAMETERS_TYPE_HASH) ||
				!Base.F.GOST34311HashData(
					(PBYTE) pcPassword,
					(UINT) strlen(pcPassword),
					pGOST34311State) ||
				!Base.F.GOST34311FinalizeHash(
					0, pGOST34311State) ||
				!Base.F.GOST34311GetStateParameters(
					pGOST34311State, (PVOID) Hash,
					GOST34311_PARAMETERS_TYPE_HASH))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
		}

		if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
			(PVOID) pSBox, GOST28147_PARAMETERS_TYPE_SBOX))
		{
			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(pcPassword == NULL)
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) pKey, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
		}
		else
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) Hash, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
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
			return CSPI_ERROR_ALLOCATE_MEMORY;
		}

		memset((PVOID) pbAlignedData, 0, dwAlignedData);
		memcpy((PVOID) pbAlignedData, (PVOID) pbData,
			dwData);
	}

	if(pcPassword != NULL || pKey != NULL)
	{
		if(!Base.F.GOST28147GetDataMAC(pbAlignedData, dwData,
			pGOST28147State) ||
			!Base.F.GOST28147GetStateParameters(pGOST28147State,
			(PVOID) pMAC, GOST28147_PARAMETERS_TYPE_MAC) ||
			!Base.F.GOST28147EncryptDataSSMode(pbAlignedData,
			dwAlignedData /
			sizeof(GOST28147_BLOCK),
			pGOST28147State))
		{
			if((dwData % sizeof(GOST28147_BLOCK)) != 0)
				free((PVOID) pbAlignedData);

			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}
	}
	else
		return CSPI_ERROR_BAD_PARAMETERS;

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
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::UnprotectData(
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
	CSPI_TRY();

	GOST28147_MAC MAC;
	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pSBox == NULL)
		pSBox = DefaultProtectionSBox;

	GOST28147_ACQUIRE_STATE();
	GOST34311_ACQUIRE_STATE();

	if(pcPassword != NULL || pKey != NULL)
	{
		GOST34311_HASH Hash;

		if(pcPassword != NULL)
		{
			if(!Base.F.GOST34311SetStateParameters(
					pGOST34311State, (PVOID) pSBox,
					GOST34311_PARAMETERS_TYPE_SBOX) ||
				!Base.F.GOST34311SetStateParameters(
					pGOST34311State, (PVOID) pInitialHash,
					GOST34311_PARAMETERS_TYPE_HASH) ||
				!Base.F.GOST34311HashData(
					(PBYTE) pcPassword,
					(UINT) strlen(pcPassword),
					pGOST34311State) ||
				!Base.F.GOST34311FinalizeHash(
					0, pGOST34311State) ||
				!Base.F.GOST34311GetStateParameters(
					pGOST34311State, (PVOID) Hash,
					GOST34311_PARAMETERS_TYPE_HASH))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
		}

		if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
			(PVOID) pSBox, GOST28147_PARAMETERS_TYPE_SBOX))
		{
			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(pcPassword == NULL)
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) pKey, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
		}
		else
		{
			if(!Base.F.GOST28147SetStateParameters(pGOST28147State,
				(PVOID) Hash, GOST28147_PARAMETERS_TYPE_KEY))
			{
				GOST28147_RELEASE_STATE();
				GOST34311_RELEASE_STATE();
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
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
			return CSPI_ERROR_ALLOCATE_MEMORY;
		}

		memcpy((PVOID) pbAlignedData, (PVOID) pbData,
			dwData);
		memcpy((PVOID) (pbAlignedData + dwData),
			(PVOID) pDataAligment,
			dwDataAligment);
	}

	if(pcPassword != NULL || pKey != NULL)
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
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(MAC[0] != pMAC[0])
		{
			if((dwData % sizeof(GOST28147_BLOCK)) != 0)
				free((PVOID) pbAlignedData);

			GOST28147_RELEASE_STATE();
			GOST34311_RELEASE_STATE();
			return CSPI_ERROR_DATA_CORRUPTED;
		}
	}
	else
		return CSPI_ERROR_BAD_PARAMETERS;

	if((dwData % sizeof(GOST28147_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData,
			dwData);
		free((PVOID) pbAlignedData);
	}

	GOST28147_RELEASE_STATE();
	GOST34311_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GOST34311HashData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST34311_HASH pHash)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pSBox == NULL)
		pSBox = DefaultHashSBox;

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
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	GOST34311_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GOST34311CheckDataHash(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST34311_HASH pInitialHash,
	GOST34311_HASH pHash)
{
	CSPI_TRY();

	GOST34311_HASH Hash;
	DWORD dwError;

	if(pSBox == NULL)
		pSBox = DefaultHashSBox;

	if((dwError = GOST34311HashData(pbData, dwData, pSBox, pInitialHash,
		Hash)) != CSPI_NO_ERROR)
		return dwError;

	if(memcmp((PVOID) Hash, (PVOID) pHash, sizeof(GOST34311_HASH)))
		return CSPI_ERROR_DATA_CORRUPTED;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

VOID WINAPI CSPI::SetHardwareCSPI(
	ICSPIHardware *pHardwareCSP)
{
	CSPI_TRY();

	this->m_pHardwareCSP = pHardwareCSP;

	if(pHardwareCSP != NULL)
		m_dwState |= CSPI_STATE_HARDWARE_CSP_INITIALIZED;
	else
		m_dwState &= ~CSPI_STATE_HARDWARE_CSP_INITIALIZED;

	CSPI_CATCH();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::SHAHashData(
	PBYTE pbData,
	DWORD dwData,
	DWORD dwHash,
	SHA_HASH pHash)
{
	UINT uiHash;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	SHA_ACQUIRE_STATE();

	uiHash = dwHash;

	if(!Base.F.SHASetStateParameters(pSHAState,
		(PVOID) &uiHash, SHA_PARAMETERS_TYPE_LENGTH) ||
		!Base.F.SHAHashData((PBYTE) pbData,
		dwData, pSHAState) ||
		!Base.F.SHAFinalizeHash(pSHAState) ||
		!Base.F.SHAGetStateParameters(pSHAState,
		(PVOID) pHash, SHA_PARAMETERS_TYPE_HASH))
	{
		SHA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	SHA_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSASignHash(
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	RSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSASignHashCtx(
		&Context, pHash, pParameters,
		pPrivateKey, pSignature);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey,
	RSA_BLOCK pEncryptedData)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSAEncryptDataCtx(
		&Context, pbData, dwData,
		pParameters, pPublicKey,
		pEncryptedData);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSADecryptData(
	PBYTE pbData,
	PDWORD pdwData,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	BOOL blUnpadData)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSADecryptDataCtx(
		&Context, pbData, pdwData,
		pParameters, pPrivateKey,
		blUnpadData);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAVerifySignature(
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey,
	RSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	RSA_ACQUIRE_STATE();

	if(!Base.F.RSASetStateParameters(pRSAState, (PVOID) pParameters,
		RSA_PARAMETERS_TYPE_PARAMETERS) ||
		!Base.F.RSASetStateParameters(pRSAState, (PVOID) pPublicKey,
		RSA_PARAMETERS_TYPE_PUBLIC_KEY) ||
		!Base.F.RSASetStateParameters(pRSAState, (PVOID) pSignature,
		RSA_PARAMETERS_TYPE_SIGNATURE))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.RSASetStateParameters(pRSAState, (PVOID) pHash,
		RSA_PARAMETERS_TYPE_HASH))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!Base.F.RSAVerifySignature(pRSAState))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_BAD_SIGNATURE;
	}

	RSA_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSACheckParameters(
	PRSA_PARAMETERS pParameters)
{
	RSA_ACQUIRE_STATE_WITH_CHECK();

	if(!Base.F.RSASetStateParameters(pRSAState,
		(PVOID) pParameters, RSA_PARAMETERS_TYPE_PARAMETERS))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	RSA_RELEASE_STATE();

	return CSPI_NO_ERROR;
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAGenerateKeys(
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	PRSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSAGenerateKeysCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSACheckKeys(
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	PRSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSACheckKeysCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSASignHash(
	DWORD dwHash,
	SHA_HASH pHash,
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = DSASignHashCtx(
		&Context, dwHash, pHash,
		pParameters, pPrivateKey,
		pSignature);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}
//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSAVerifySignature(
	DWORD dwHash,
	SHA_HASH pHash,
	PDSA_PARAMETERS pParameters,
	PDSA_PUBLIC_KEY pPublicKey,
	PDSA_SIGNATURE pSignature)
{
	UINT uiHash;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	DSA_ACQUIRE_STATE();

	if(!Base.F.DSASetStateParameters(pDSAState, (PVOID) pParameters,
		DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS) ||
		!Base.F.DSASetStateParameters(pDSAState, (PVOID) pPublicKey,
		DSA_PARAMETERS_TYPE_PUBLIC_KEY) ||
		!Base.F.DSASetStateParameters(pDSAState, (PVOID) pSignature,
		DSA_PARAMETERS_TYPE_SIGNATURE))
	{
		DSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	uiHash = dwHash;

	if(!Base.F.DSASetStateParameters(pDSAState,
		(PVOID) &uiHash, DSA_PARAMETERS_TYPE_HASH_LENGTH) ||
		!Base.F.DSASetStateParameters(pDSAState, (PVOID) pHash,
		DSA_PARAMETERS_TYPE_HASH))
	{
		DSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!Base.F.DSAVerifySignature(pDSAState))
	{
		DSA_RELEASE_STATE();
		return CSPI_ERROR_BAD_SIGNATURE;
	}

	DSA_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSASignHash(
	DWORD dwHash,
	SHA_HASH pHash,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	PECDSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSASignHashCtx(
		&Context, dwHash, pHash,
		pParameters, pPrivateKey,
		pSignature);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSAVerifySignature(
	DWORD dwHash,
	SHA_HASH pHash,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey,
	PECDSA_SIGNATURE pSignature)
{
	UINT uiHash;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	ECDSA_ACQUIRE_STATE();

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pParameters,
			ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
		!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pPublicKey,
			ECDSA_PARAMETERS_TYPE_KEY_Q) ||
		!Base.F.ECDSASetStateParameters(
			pECDSAState, pSignature,
			ECDSA_PARAMETERS_TYPE_SIGNATURE))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	uiHash = dwHash;

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) &uiHash,
			ECDSA_PARAMETERS_TYPE_HASH_LENGTH) ||
		!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pHash,
			ECDSA_PARAMETERS_TYPE_HASH))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!Base.F.ECDSAVerifySignature(pECDSAState))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_BAD_SIGNATURE;
	}

	ECDSA_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDHCalculateSharedSecret(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pRecipientPublicKey,
	ECDSA_NUMBER pSharedSecret)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDHCalculateSharedSecretCtx(
		&Context, pParameters, pPrivateKey,
		pRecipientPublicKey, pSharedSecret);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DHCalculateSharedSecret(
	PDSA_PARAMETERS pParameters,
	DSA_NUMBER pPrivateKey,
	DSA_NUMBER pRecipientPublicKey,
	DSA_NUMBER pSharedSecret)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = DHCalculateSharedSecretCtx(
		&Context, pParameters, pPrivateKey,
		pRecipientPublicKey, pSharedSecret);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSACheckParameters(
	PDSA_PARAMETERS pParameters)
{
	DSA_ACQUIRE_STATE_WITH_CHECK();

	if(!Base.F.DSASetStateParameters(pDSAState,
		(PVOID) pParameters, DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS))
	{
		DSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	DSA_RELEASE_STATE();

	return CSPI_NO_ERROR;
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSAGenerateKeys(
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = DSAGenerateKeysCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSACheckKeys(
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = DSACheckKeysCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACheckParameters(
	PECDSA_PARAMETERS pParameters)
{
	CSPI_TRY();

	ECDSA_ACQUIRE_STATE_WITH_CHECK();

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pParameters,
			ECDSA_PARAMETERS_TYPE_PARAMETERS))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	ECDSA_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSAGenerateKeys(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSAGenerateKeysCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ReservedFunction1()
{
	CSPI_TRY();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ReservedFunction2()
{
	CSPI_TRY();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ReservedFunction3()
{
	CSPI_TRY();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ReservedFunction4()
{
	CSPI_TRY();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACheckKeys(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSACheckKeysCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDEAEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	DES_BLOCK pDataAligment,
	PDWORD pdwDataAligment)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = TDEAEncryptDataCtx(
		&Context, pbData, dwData,
		pKeys, pIV, pDataAligment,
		pdwDataAligment);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDEADecryptData(
	PBYTE pbData,
	DWORD dwData,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	DES_BLOCK pDataAligment,
	DWORD dwDataAligment)
{
	CSPI_TRY();

	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	TDEA_ACQUIRE_STATE();

	if((dwData % sizeof(DES_BLOCK)) == 0)
	{
		pbAlignedData = pbData;
		dwAlignedData = dwData;
	}
	else
	{
		dwAlignedData = ((dwData / sizeof(DES_BLOCK)) + 1) *
			sizeof(DES_BLOCK);

		pbAlignedData = (PBYTE) malloc(dwAlignedData);
		if(pbAlignedData == NULL)
		{
			TDEA_RELEASE_STATE();
			return CSPI_ERROR_ALLOCATE_MEMORY;
		}

		memcpy((PVOID) pbAlignedData, (PVOID) pbData, dwData);
		memcpy((PVOID) (pbAlignedData + dwData),
			(PVOID) pDataAligment, dwDataAligment);
	}

	if(!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pKeys, TDEA_PARAMETERS_TYPE_KEY) ||
		!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pIV, TDEA_PARAMETERS_TYPE_CBCIV) ||
		!Base.F.TDEADecryptDataCBCMode(pbAlignedData,
		dwAlignedData, pTDEAState))
	{
		if((dwData % sizeof(DES_BLOCK)) != 0)
			free((PVOID) pbAlignedData);

		TDEA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if((dwData % sizeof(DES_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData, dwData);
		free((PVOID) pbAlignedData);
	}

	TDEA_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::AESEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pKey,
	DWORD dwKey,
	AES_IV pIV,
	AES_BLOCK pDataAligment,
	PDWORD pdwDataAligment)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = AESEncryptDataCtx(
		&Context, pbData, dwData,
		pKey, dwKey, pIV, pDataAligment,
		pdwDataAligment);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::AESDecryptData(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pKey,
	DWORD dwKey,
	AES_IV pIV,
	AES_BLOCK pDataAligment,
	DWORD dwDataAligment)
{
	CSPI_TRY();

	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	AES_ACQUIRE_STATE();

	if((dwData % sizeof(AES_BLOCK)) == 0)
	{
		pbAlignedData = pbData;
		dwAlignedData = dwData;
	}
	else
	{
		dwAlignedData = ((dwData / sizeof(AES_BLOCK)) + 1) *
			sizeof(AES_BLOCK);

		pbAlignedData = (PBYTE) malloc(dwAlignedData);
		if(pbAlignedData == NULL)
		{
			AES_RELEASE_STATE();
			return CSPI_ERROR_ALLOCATE_MEMORY;
		}

		memcpy((PVOID) pbAlignedData, (PVOID) pbData, dwData);
		memcpy((PVOID) (pbAlignedData + dwData),
			(PVOID) pDataAligment, dwDataAligment);
	}

	if(!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pIV, AES_MODES_PARAMETERS_CBC_IV) ||
		!Base.F.AESDecryptDataCBCMode(pbAlignedData,
		dwAlignedData, pAESState))
	{
		if((dwData % sizeof(AES_BLOCK)) != 0)
			free((PVOID) pbAlignedData);

		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if((dwData % sizeof(AES_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData, dwData);
		free((PVOID) pbAlignedData);
	}

	AES_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::AESGetDataMAC(
	PBYTE pbData,
	DWORD dwBitDataLength,
	PBYTE pKey,
	DWORD dwKey,
	AES_BLOCK pRandom,
	DWORD dwBitsRandomLength,
	AES_MAC pMAC)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = AESGetDataMACCtx(
		&Context, pbData, dwBitDataLength,
		pKey, dwKey, pRandom,
		dwBitsRandomLength, pMAC);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::AESCheckDataMAC(
	PBYTE pbData,
	DWORD dwBitDataLength,
	PBYTE pKey,
	DWORD dwKey,
	AES_BLOCK pRandom,
	DWORD dwBitsRandomLength,
	AES_MAC pMAC)
{
	CSPI_TRY();

	AES_MAC MAC;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	AES_ACQUIRE_STATE();

	AES_MODE_MAC_PARAMETERS Parameters;

	Parameters.dwBitRandomLength = dwBitsRandomLength;
	Parameters.iDeriveKeysInternaly = TRUE;
	memcpy((PVOID) Parameters.Random, (PVOID) pRandom, 
		sizeof(AES_BLOCK));

	if(!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
		(PVOID) &Parameters, AES_MODES_PARAMETERS_MAC_ALL) ||
		!Base.F.AESGetDataMAC(pbData, dwBitDataLength,
		MAC, sizeof(AES_BLOCK) * 8, pAESState))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(memcmp((PVOID) MAC, (PVOID) pMAC, sizeof(AES_MAC)))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_DATA_CORRUPTED;
	}

	AES_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDEAGetDataMAC(
	PBYTE pbData,
	DWORD dwBitDataLength,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	DES_BLOCK pMAC)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = TDEAGetDataMACCtx(
		&Context, pbData, dwBitDataLength,
		pKeys, pIV, pMAC);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDEACheckDataMAC(
	PBYTE pbData,
	DWORD dwBitDataLength,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	DES_BLOCK pMAC)
{
	CSPI_TRY();

	DES_BLOCK MAC;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	TDEA_ACQUIRE_STATE();

	if(!Base.F.TDEASetStateParameters(pTDEAState, (PVOID) pKeys,
		TDEA_PARAMETERS_TYPE_KEY) ||
		!Base.F.TDEAGetDataMAC(pbData, pIV,
		dwBitDataLength, pTDEAState, MAC))
	{
		TDEA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(memcmp((PVOID) MAC, (PVOID) pMAC, sizeof(DES_BLOCK)))
	{
		TDEA_RELEASE_STATE();
		return CSPI_ERROR_DATA_CORRUPTED;
	}

	TDEA_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeSHAHashData(
	DWORD						dwHash,
	PSHA_STATE					*ppSHAState)
{
	UINT uiHash;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	*ppSHAState = Base.F.SHAAcquireState();
	if(!*ppSHAState)
		return CSPI_ERROR_ALLOCATE_MEMORY;

	uiHash = dwHash;

	if(!Base.F.SHASetStateParameters(*ppSHAState,
		(PVOID) &uiHash, SHA_PARAMETERS_TYPE_LENGTH))
	{
		Base.F.SHAReleaseState(*ppSHAState);
		*ppSHAState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueSHAHashData(
	PBYTE						pbData,
	DWORD						dwData,
	PSHA_STATE					*ppSHAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(!Base.F.SHAHashData((PBYTE) pbData,
		dwData, *ppSHAState))
	{
		Base.F.SHAReleaseState(*ppSHAState);
		*ppSHAState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeSHAHashData(
	SHA_HASH					pHash,
	PSHA_STATE					*ppSHAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(!Base.F.SHAFinalizeHash(*ppSHAState) ||
		!Base.F.SHAGetStateParameters(*ppSHAState,
		(PVOID) pHash, SHA_PARAMETERS_TYPE_HASH))
	{
		Base.F.SHAReleaseState(*ppSHAState);
		*ppSHAState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	Base.F.SHAReleaseState(*ppSHAState);
	*ppSHAState = NULL;
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::TDESEncryptData(
	PBYTE pbData,
	DWORD dwData,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	BOOL blGenerateKeyAndIV,
	DES_BLOCK pDataAligment,
	PDWORD pdwDataAligment)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = TDESEncryptDataCtx(
		&Context, pbData, dwData,
		pKeys, pIV, blGenerateKeyAndIV,
		pDataAligment, pdwDataAligment);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::PBESHA1RC2Encrypt(
	PBYTE pbData,
	PDWORD pdwData,
	DWORD dwDataMaxSize,
	DWORD dwKeySize,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = PBESHA1RC2EncryptCtx(
		&Context, pbData, pdwData,
		dwDataMaxSize, dwKeySize,
		pbPassword, dwPassword,
		pbSalt, dwSalt, blGenerateSalt,
		dwCounter);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBESHA1RC2Decrypt(
	PBYTE						pbData,
	PDWORD						pdwData,
	DWORD						dwKeySize,
	PBYTE						pbPassword,
	DWORD						dwPassword,
	PBYTE						pbSalt,
	DWORD						dwSalt,
	DWORD						dwCounter)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD						dwKeyEffectiveBitLen;
	RC2_KEY						Key;
	RC2_IV						IV;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFRC2DeriveKey == NULL ||
		m_pBaseEx->PKCS12PBKDFRC2DeriveIV == NULL ||
		m_pBaseEx->RC2SetStateParameters == NULL ||
		m_pBaseEx->RC2DecryptDataCBCMode == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(*pdwData % sizeof(RC2_BLOCK) != 0 ||
		*pdwData / sizeof(RC2_BLOCK) < 2)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(dwKeySize > sizeof(RC2_KEY))
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	dwKeyEffectiveBitLen = dwKeySize * 8;

	if(!m_pBaseEx->PKCS12PBKDFRC2DeriveKey(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		dwKeySize, Key) ||
		!m_pBaseEx->PKCS12PBKDFRC2DeriveIV(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		IV))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	RC2_ACQUIRE_STATE();

	if(!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) &dwKeyEffectiveBitLen,
		RC2_PARAMETERS_TYPE_KEY_EFFECTIVE_BIT_LENGTH) ||
		!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) &dwKeySize,
		RC2_PARAMETERS_TYPE_KEY_BYTE_LENGTH) ||
		!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) Key, RC2_PARAMETERS_TYPE_KEY) ||
		!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) IV, RC2_PARAMETERS_TYPE_IV) ||
		!m_pBaseEx->RC2DecryptDataCBCMode(pbData,
		*pdwData / sizeof(RC2_BLOCK), pRC2State) ||
		pbData[*pdwData - 1] > sizeof(RC2_BLOCK))
	{
		RC2_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*pdwData = *pdwData - pbData[*pdwData - 1];

	RC2_RELEASE_STATE();

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBESHA1TDESEncrypt(
	PBYTE pbData,
	PDWORD pdwData,
	DWORD dwDataMaxSize,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = PBESHA1TDESEncryptCtx(
		&Context, pbData, pdwData,
		dwDataMaxSize, pbPassword,
		dwPassword, pbSalt, dwSalt,
		blGenerateSalt, dwCounter);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBESHA1TDESDecrypt(
	PBYTE						pbData,
	PDWORD						pdwData,
	PBYTE						pbPassword,
	DWORD						dwPassword,
	PBYTE						pbSalt,
	DWORD						dwSalt,
	DWORD						dwCounter)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD						dwError;
	TDEA_KEYS					Key;
	DES_IV						IV;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFTDESDeriveKey == NULL ||
		m_pBaseEx->PKCS12PBKDFTDESDeriveIV == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(*pdwData % sizeof(DES_BLOCK) != 0 ||
		*pdwData / sizeof(DES_BLOCK) < 2)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!m_pBaseEx->PKCS12PBKDFTDESDeriveKey(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		&Key) ||
		!m_pBaseEx->PKCS12PBKDFTDESDeriveIV(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		IV))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	dwError = TDEADecryptData(
		pbData, *pdwData,
		&Key, IV, NULL, 0);
	if(dwError != CSPI_NO_ERROR ||
		pbData[*pdwData - 1] > sizeof(DES_BLOCK))
	{
		return dwError;
	}

	*pdwData = *pdwData - pbData[*pdwData - 1];

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::SHA1CreateHMAC(
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	SHA1_HMAC_HASH pHash)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = SHA1CreateHMACCtx(
		&Context, pbData, dwData,
		pbPassword, dwPassword,
		pbSalt, dwSalt, blGenerateSalt,
		dwCounter, pHash);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::SHA1CheckHMAC(
	PBYTE						pbData,
	DWORD						dwData,
	PBYTE						pbPassword,
	DWORD						dwPassword,
	PBYTE						pbSalt,
	DWORD						dwSalt,
	DWORD						dwCounter,
	SHA1_HMAC_HASH				pHash)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD						dwError;
	SHA1_HMAC_HASH				Hash;

	if((dwError = SHA1CreateHMAC(
		pbData, dwData,
		pbPassword, dwPassword,
		pbSalt, dwSalt, FALSE,
		dwCounter, Hash)) != CSPI_NO_ERROR)
	{
		return dwError;
	}

	if(memcmp((PVOID) Hash, (PVOID) pHash,
		sizeof(SHA1_HMAC_HASH)) != 0)
	{
		return CSPI_ERROR_DATA_CORRUPTED;
	}

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::RSARecoverPublicKey(
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	PRSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSARecoverPublicKeyCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSARecoverPublicKey(
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = DSARecoverPublicKeyCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSARecoverPublicKey(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSARecoverPublicKeyCtx(
		&Context, pParameters,
		pPrivateKey, pPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::PBKDF2IDeriveKey(
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	PTDEA_KEYS pDerivedKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = PBKDF2IDeriveKeyCtx(
		&Context, pbPassword,
		dwPassword, pbSalt, dwSalt,
		blGenerateSalt, dwCounter,
		pDerivedKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

VOID WINAPI CSPI::SetParityBits(
	PDES_KEY				pKey)
{
	CSPI_TRY();

	BYTE bByte;

	for (int i = 0; i < sizeof(DES_KEY); i++)
	{
		bByte = ((*pKey)[i] & 0xFE) | 0x1;
		for (int j = 1; j < 8; j++)
			bByte ^= ((bByte >> j) & 0x1);

		(*pKey)[i] = bByte;
	}

	CSPI_CATCH()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeTDESEncryptData(
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	BOOL blGenerateKeyAndIV,
	PTDEA_STATE *ppTDEAState)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = InitializeTDESEncryptDataCtx(
		&Context, pKeys, pIV,
		blGenerateKeyAndIV,
		ppTDEAState);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueTDESEncryptData(
	PBYTE					pbData,
	DWORD					dwData,
	PTDEA_STATE				*ppTDEAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwData % sizeof(DES_BLOCK))
	{
		Base.F.TDEAReleaseState(*ppTDEAState);
		*ppTDEAState = NULL;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!Base.F.TDEAEncryptDataCBCMode(pbData, dwData,
			*ppTDEAState))
	{
		Base.F.TDEAReleaseState(*ppTDEAState);
		*ppTDEAState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeTDESEncryptData(
	PTDEA_STATE				*ppTDEAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	Base.F.TDEAReleaseState(*ppTDEAState);
	*ppTDEAState = NULL;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeTDESDecryptData(
	PTDEA_KEYS				pKeys,
	DES_IV					pIV,
	PTDEA_STATE				*ppTDEAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if (pKeys == NULL || pIV == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	TDEA_ACQUIRE_STATE();

	if(!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pKeys, TDEA_PARAMETERS_TYPE_KEY) ||
		!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pIV, TDEA_PARAMETERS_TYPE_CBCIV))
	{
		TDEA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*ppTDEAState = pTDEAState;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueTDESDecryptData(
	PBYTE					pbData,
	DWORD					dwData,
	PTDEA_STATE				*ppTDEAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwData % sizeof(DES_BLOCK))
	{
		Base.F.TDEAReleaseState(*ppTDEAState);
		*ppTDEAState = NULL;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!Base.F.TDEADecryptDataCBCMode(pbData, dwData,
			*ppTDEAState))
	{
		Base.F.TDEAReleaseState(*ppTDEAState);
		*ppTDEAState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeTDESDecryptData(
	PTDEA_STATE				*ppTDEAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	Base.F.TDEAReleaseState(*ppTDEAState);
	*ppTDEAState = NULL;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::InitializeAESEncryptData(
	PAES_CIPHER_KEY pKey,
	DWORD dwKey,
	AES_IV pIV,
	BOOL blGenerateKeyAndIV,
	PAES_STATE *ppAESState)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = InitializeAESEncryptDataCtx(
		&Context, pKey, dwKey, pIV,
		blGenerateKeyAndIV, ppAESState);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueAESEncryptData(
	PBYTE					pbData,
	DWORD					dwData,
	PAES_STATE				*ppAESState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwData % sizeof(AES_BLOCK))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!Base.F.AESEncryptDataCBCMode(pbData, dwData,
			*ppAESState))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeAESEncryptData(
	PAES_STATE				*ppAESState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	Base.F.AESReleaseState(*ppAESState);
	*ppAESState = NULL;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeAESDecryptData(
	PAES_CIPHER_KEY			pKey,
	DWORD					dwKey,
	AES_IV					pIV,
	PAES_STATE				*ppAESState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pKey == NULL || pIV == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	AES_ACQUIRE_STATE();

	if(!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pIV, AES_MODES_PARAMETERS_CBC_IV))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*ppAESState = pAESState;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueAESDecryptData(
	PBYTE					pbData,
	DWORD					dwData,
	PAES_STATE				*ppAESState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwData % sizeof(AES_BLOCK))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!Base.F.AESDecryptDataCBCMode(pbData, dwData,
			*ppAESState))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeAESDecryptData(
	PAES_STATE				*ppAESState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	Base.F.AESReleaseState(*ppAESState);
	*ppAESState = NULL;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::SetHRNG(
	ICSPIHardwareRNG *pHardwareRNG)
{
	CSPI_TRY();

	m_pHardwareRNG = NULL;
	m_dwState &= ~CSPI_STATE_HRNG_INITIALIZED;

	if(pHardwareRNG != NULL)
	{
		m_pHardwareRNG = pHardwareRNG;
		m_dwState |= CSPI_STATE_HRNG_INITIALIZED;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GenerateRNSequenceCtx(
	PCSPI_CTX pContext,
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSPI_TRY();

	DWORD dwIterations = 0;
	DWORD dwBadIterationsLimit;
	PBS_STATISTIC pStatistic;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL)
		return CSPI_ERROR_NOT_INITIALIZED;

	dwBadIterationsLimit =
		(dwSequence != AIS31_SEQUENCE_SIZE_BYTES) ?
			CSPI_BAD_HRNG_SEQUENCES_LIMIT :
			CSPI_BAD_HRNG_INITIALIZE_SEQUENCES_LIMIT;

	while(TRUE)
	{
		if(!pContext->pHardwareRNG->GenerateSequence(
				pbSequence, dwSequence))
		{
			return CSPI_ERROR_HRNG_FAILURE;
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
			return CSPI_ERROR_BAD_HRNG_SEQUENCE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GeneratePRNGParametersCtx(
	PCSPI_CTX pContext,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey,
	GOST28147_BLOCK pWorkS)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL &&
		!Base.ExtensionF.TSCGIsEnable())
	{
		return CSPI_ERROR_PRNG_CALL;
	}

	DWORD dwError;

	if(pSeed != NULL)
	{
		if(pContext->pHardwareRNG == NULL)
		{
			dwError = CSPI_NO_ERROR;

			if(!Base.ExtensionF.TSCGGenerateSequence(
					(PBYTE) pSeed, sizeof(GOST28147_BLOCK)))
			{
				dwError = CSPI_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(pContext,
				(PBYTE) pSeed, sizeof(GOST28147_BLOCK));
		}

		if(dwError != CSPI_NO_ERROR)
			return dwError;
	}

	if(pKey != NULL)
	{
		if(pContext->pHardwareRNG == NULL)
		{
			dwError = CSPI_NO_ERROR;

			if(!Base.ExtensionF.TSCGGenerateSequence(
					(PBYTE) pKey, sizeof(GOST28147_KEY)))
			{
				dwError = CSPI_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(pContext,
				(PBYTE) pKey, sizeof(GOST28147_KEY));
		}

		if(dwError != CSPI_NO_ERROR)
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
			dwError = CSPI_NO_ERROR;

			if(!Base.ExtensionF.TSCGGenerateSequence(
					(PBYTE) pWorkS, sizeof(GOST28147_BLOCK)))
			{
				dwError = CSPI_ERROR_PRNG_CALL;
			}
		}
		else
		{
			dwError = GenerateRNSequenceCtx(pContext,
				(PBYTE) pWorkS, sizeof(GOST28147_BLOCK));
		}

		if(dwError != CSPI_NO_ERROR)
		{
			if(pKey != NULL)
				memset((PVOID) pKey, 0, sizeof(GOST28147_KEY));
			if(pSeed != NULL)
				memset((PVOID) pSeed, 0, sizeof(GOST28147_BLOCK));

			return dwError;
		}
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializePRNGCtx(
	PCSPI_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey)
{
	CSPI_TRY();

	GOST28147_BLOCK WorkS, DateTime;
	DWORD dwError;
	GOST28147_KEY Key;
	GOST28147_BLOCK Seed;
	GOST28147_COMPRESSED_SBOX SBox;
	PDSTU4145_PSEUDO_RNG_STATE pPRNGState;
	CSPI_CTX Context;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

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
		if(dwError != CSPI_NO_ERROR)
		{
			memset((PVOID) SBox, 0,
				sizeof(GOST28147_COMPRESSED_SBOX));

			return CSPI_ERROR_PRNG_CALL;
		}
	}
	else
	{
		memset((PVOID) &Context, 0, sizeof(CSPI_CTX));
		Context.pPRNGState = this->pPRNGState;

		if(pSeed == NULL)
		{
			dwError = GeneratePRNSequenceCtx(
				&Context, (PBYTE) Seed,
				sizeof(GOST28147_BLOCK));
			if(dwError != CSPI_NO_ERROR)
			{
				memset((PVOID) SBox, 0,
					sizeof(GOST28147_COMPRESSED_SBOX));

				return CSPI_ERROR_PRNG_CALL;
			}
		}

		if(pKey == NULL)
		{
			dwError = GeneratePRNSequenceCtx(
				&Context, (PBYTE) Key,
				sizeof(GOST28147_KEY));
			if(dwError != CSPI_NO_ERROR)
			{
				memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
				memset((PVOID) SBox, 0,
					sizeof(GOST28147_COMPRESSED_SBOX));

				return CSPI_ERROR_PRNG_CALL;
			}
		}

		dwError = GeneratePRNSequenceCtx(
			&Context, (PBYTE) WorkS,
			sizeof(GOST28147_BLOCK));
		if(dwError != CSPI_NO_ERROR)
		{
			memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
			memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
			memset((PVOID) SBox, 0,
				sizeof(GOST28147_COMPRESSED_SBOX));

			return CSPI_ERROR_PRNG_CALL;
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

		return CSPI_ERROR_ALLOCATE_MEMORY;
	}

	memset((PVOID) WorkS, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
	memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) SBox, 0,
		sizeof(GOST28147_COMPRESSED_SBOX));

	pContext->pPRNGState = pPRNGState;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ReinitializePRNGCtx(
	PCSPI_CTX pContext,
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_BLOCK pSeed,
	GOST28147_KEY pKey)
{
	CSPI_TRY();

	GOST28147_BLOCK WorkS, DateTime;
	DWORD dwError;
	GOST28147_KEY Key;
	GOST28147_BLOCK Seed;
	GOST28147_COMPRESSED_SBOX SBox;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
	{
		return InitializePRNGCtx(pContext,
			pSBox, pSeed, pKey);
	}

	if(m_pBaseEx == NULL ||
		m_pBaseEx->DSTU4145PseudoRNGReinitialize == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
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
	if (dwError != CSPI_NO_ERROR)
	{
		memset((PVOID) SBox, 0,
			sizeof(GOST28147_COMPRESSED_SBOX));

		return CSPI_ERROR_PRNG_CALL;
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

		return CSPI_ERROR_ALLOCATE_MEMORY;
	}

	memset((PVOID) WorkS, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) Key, 0, sizeof(GOST28147_KEY));
	memset((PVOID) Seed, 0, sizeof(GOST28147_BLOCK));
	memset((PVOID) SBox, 0,
		sizeof(GOST28147_COMPRESSED_SBOX));

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeHRNGCtx(
	PCSPI_CTX pContext)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pHardwareRNG == NULL)
		return CSPI_NO_ERROR;

	BYTE bSequence[AIS31_SEQUENCE_SIZE_BYTES];
	DWORD dwError;

	dwError = GenerateRNSequenceCtx(pContext,
		bSequence, AIS31_SEQUENCE_SIZE_BYTES);
	if(dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GeneratePRNSequenceCtx(
	PCSPI_CTX pContext,
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSPI_ERROR_NOT_INITIALIZED;

	Base.F.DSTU4145PseudoRNGGenerateSequence(
		pbSequence, dwSequence, pContext->pPRNGState);

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::GenerateRPRNSequenceCtx(
	PCSPI_CTX pContext,
	PBYTE pbSequence,
	DWORD dwSequence)
{
	CSPI_TRY();

	DWORD dwError;

	if((dwError = GenerateRNSequenceCtx(pContext,
			pbSequence, dwSequence)) != CSPI_NO_ERROR &&
		(dwError = GeneratePRNSequenceCtx(pContext,
			pbSequence, dwSequence)) != CSPI_NO_ERROR)
	{
		return dwError;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSASignHashCtx(
	PCSPI_CTX pContext,
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	RSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->RSASignHash(
				pHash, pParameters, pSignature))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		RSA_ACQUIRE_STATE();

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pParameters,
				RSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pPrivateKey,
				RSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pContext->pPRNGState,
				RSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pHash,
				RSA_PARAMETERS_TYPE_HASH) ||
			!Base.F.RSASignHash(pRSAState) ||
			!Base.F.RSAGetStateParameters(
				pRSAState, (PVOID) pSignature,
				RSA_PARAMETERS_TYPE_SIGNATURE))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		RSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAEncryptDataCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey,
	RSA_BLOCK pEncryptedData)
{
	UINT	dwLength;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
		return CSPI_ERROR_NOT_INITIALIZED;

	RSA_ACQUIRE_STATE();

	if(!Base.F.RSASetStateParameters(
			pRSAState,
			(PVOID) pContext->pPRNGState,
			RSA_PARAMETERS_TYPE_PRNG) ||
		!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) pParameters,
			RSA_PARAMETERS_TYPE_PARAMETERS) ||
		!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) pPublicKey,
			RSA_PARAMETERS_TYPE_PUBLIC_KEY))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.RSAEncryptData(
			pRSAState, pbData, dwData,
			(PBYTE) pEncryptedData, &dwLength))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_BAD_SIGNATURE;
	}

	RSA_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSADecryptDataCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	PDWORD pdwData,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	BOOL blUnpadData)
{
	CSPI_TRY();

	UINT	dwDecryptedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareRSADecryptData;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_RSA_DECRYPT_DATA,
			bHardwareRSADecryptData);
		if (!bHardwareRSADecryptData)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->RSADecryptData(
				pbData, pdwData, pParameters,
				blUnpadData))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		RSA_ACQUIRE_STATE();

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pParameters,
				RSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pPrivateKey,
				RSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		RSA_BLOCK DecryptedData;

		if(!Base.F.RSADecryptData(
				pRSAState, pbData, *pdwData,
				(PBYTE) DecryptedData,
				&dwDecryptedData, blUnpadData))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		memset((PVOID) pbData, 0, *pdwData);

		memcpy((PVOID) pbData, (PVOID) DecryptedData,
			dwDecryptedData);
		*pdwData = dwDecryptedData;

		RSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAGenerateKeysCtx(
	PCSPI_CTX pContext,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	PRSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if (pPrivateKey == NULL &&
		pPublicKey == NULL &&
		pParameters->dwHash == 0)
	{
		switch(pParameters->dwBits)
		{
		case CSPI_COMPATIBLE_LEVEL_PKCS12:
#ifdef CSPI_PKCS12
			return CSPI_NO_ERROR;
#else // CSPI_PKCS12
			return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

		case CSPI_COMPATIBLE_LEVEL_RECOVER_PUBLIC_KEY:
			return CSPI_NO_ERROR;

		case CSPI_COMPATIBLE_LEVEL_ITERATIVE_I_ENCRYPTION:
			return CSPI_NO_ERROR;

		case CSPI_COMPATIBLE_LEVEL_CTX:
			return CSPI_NO_ERROR;

		case CSPI_COMPATIBLE_LEVEL_RSA_PSS_SIGN:
			return CSPI_NO_ERROR;

		case CSPI_COMPATIBLE_LEVEL_AES_GCM:
#if defined(CSPI_AES_GET_PARAMETERS) && defined(CSPI_AES_GCM)
			return CSPI_NO_ERROR;
#else // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM
			return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM

		case CSPI_COMPATIBLE_LEVEL_ECDSA_COUPLE:
#ifdef CSPI_ECDSA_COUPLE
			return CSPI_NO_ERROR;
#else // CSPI_ECDSA_COUPLE
			return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_ECDSA_COUPLE

		case CSPI_COMPATIBLE_LEVEL_PBKDF2_SHA_DERIVE_KEY:
			if(m_pBaseEx != NULL &&
				m_pBaseEx->PBKDF2SHADeriveKey != NULL)
			{
				return CSPI_NO_ERROR;
			}
			else
			{
				return CSPI_ERROR_PROGRAM_FAILURE;
			}
		}
	}

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->RSAGenerateKeys(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		RSA_ACQUIRE_STATE();

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pParameters,
				RSA_PARAMETERS_TYPE_PARAMETERS))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pContext->pPRNGState,
				RSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.RSAGenerateParameters(
				pRSAState,
				RSA_PARAMETERS_TYPE_KEYS_FAST) ||
			!Base.F.RSAGetStateParameters(
				pRSAState, (PVOID) pPrivateKey,
				RSA_PARAMETERS_TYPE_PRIVATE_KEY) ||
			!Base.F.RSAGetStateParameters(
				pRSAState, (PVOID) pPublicKey,
				RSA_PARAMETERS_TYPE_PUBLIC_KEY))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		RSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSACheckKeysCtx(
	PCSPI_CTX pContext,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	PRSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->RSACheckKeys(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		RSA_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pContext->pPRNGState,
				RSA_PARAMETERS_TYPE_PRNG))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pParameters,
				RSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pPrivateKey,
				RSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(pPublicKey != NULL)
		{
			if(!Base.F.RSASetStateParameters(
					pRSAState, (PVOID) pPublicKey,
					RSA_PARAMETERS_TYPE_PUBLIC_KEY))
			{
				RSA_RELEASE_STATE();
				return CSPI_ERROR_WRONG_PARAMETERS;
			}
		}

		RSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSASignHashCtx(
	PCSPI_CTX pContext,
	DWORD dwHash,
	SHA_HASH pHash,
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_SIGNATURE pSignature)
{
	UINT uiHash;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->DSASignHash(
				dwHash, pHash, pParameters, pSignature))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		DSA_ACQUIRE_STATE();

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pParameters,
				DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS) ||
			!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pPrivateKey,
				DSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		uiHash = dwHash;

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pContext->pPRNGState,
				DSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) &uiHash,
				DSA_PARAMETERS_TYPE_HASH_LENGTH) ||
			!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pHash,
				DSA_PARAMETERS_TYPE_HASH))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.DSAGenerateParameters(
				pDSAState,
				DSA_GENERATE_PARAMETERS_TYPE_SECRET_NUMBER) ||
			!Base.F.DSASignHash(pDSAState) ||
			!Base.F.DSAGetStateParameters(
				pDSAState, (PVOID) pSignature,
				DSA_PARAMETERS_TYPE_SIGNATURE))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		DSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSASignHashCtx(
	PCSPI_CTX pContext,
	DWORD dwHash,
	SHA_HASH pHash,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	PECDSA_SIGNATURE pSignature)
{
	UINT uiAlgoID;
	UINT uiHash;

	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->ECDSASignHash(
				dwHash, pHash, pParameters, pSignature))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		ECDSA_ACQUIRE_STATE();

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pParameters,
				ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pPrivateKey,
				ECDSA_PARAMETERS_TYPE_KEY_D))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		uiAlgoID = ECDSA_ALGORITHM;
		uiHash = dwHash;

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) &uiAlgoID,
				ECDSA_PARAMETERS_TYPE_EC_ALGORITHM) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pContext->pPRNGState,
				ECDSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) &uiHash,
				ECDSA_PARAMETERS_TYPE_HASH_LENGTH) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pHash,
				ECDSA_PARAMETERS_TYPE_HASH) ||
			!Base.F.ECDSASignHash(pECDSAState) ||
			!Base.F.ECDSAGetStateParameters(
				pECDSAState, (PVOID) pSignature,
				ECDSA_PARAMETERS_TYPE_SIGNATURE))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		ECDSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDHCalculateSharedSecretCtx(
	PCSPI_CTX pContext,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pRecipientPublicKey,
	ECDSA_NUMBER pSharedSecret)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->ECDHCalculateSharedSecret(
				pParameters, pRecipientPublicKey,
				pSharedSecret))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(!Base.F.ECDHCalculateSharedSecret(
				&pParameters->EC, &pParameters->P,
				pPrivateKey, pRecipientPublicKey,
				pSharedSecret))
		{
			return CSPI_ERROR_PROGRAM_FAILURE;
		}
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DHCalculateSharedSecretCtx(
	PCSPI_CTX pContext,
	PDSA_PARAMETERS pParameters,
	DSA_NUMBER pPrivateKey,
	DSA_NUMBER pRecipientPublicKey,
	DSA_NUMBER pSharedSecret)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->DHCalculateSharedSecret(
				pParameters, pRecipientPublicKey,
				pSharedSecret))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(!Base.F.DHCalculateSharedSecret(
				pParameters, pPrivateKey,
				pRecipientPublicKey,
				pSharedSecret))
		{
			return CSPI_ERROR_PROGRAM_FAILURE;
		}
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSAGenerateKeysCtx(
	PCSPI_CTX pContext,
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->DSAGenerateKeys(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		DSA_ACQUIRE_STATE();

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pParameters,
				DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pContext->pPRNGState,
				DSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.DSAGenerateParameters(
				pDSAState,
				DSA_GENERATE_PARAMETERS_TYPE_KEYS) ||
			!Base.F.DSAGetStateParameters(
				pDSAState, (PVOID) pPrivateKey,
				DSA_PARAMETERS_TYPE_PRIVATE_KEY) ||
			!Base.F.DSAGetStateParameters(
				pDSAState, (PVOID) pPublicKey,
				DSA_PARAMETERS_TYPE_PUBLIC_KEY))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		DSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSACheckKeysCtx(
	PCSPI_CTX pContext,
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->DSACheckKeys(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		DSA_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pContext->pPRNGState,
				DSA_PARAMETERS_TYPE_PRNG))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pParameters,
				DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS) ||
			!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pPrivateKey,
				DSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(pPublicKey != NULL)
		{
			if(!Base.F.DSASetStateParameters(
					pDSAState, (PVOID) pPublicKey,
					DSA_PARAMETERS_TYPE_PUBLIC_KEY))
			{
				DSA_RELEASE_STATE();
				return CSPI_ERROR_WRONG_PARAMETERS;
			}
		}

		DSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSAGenerateKeysCtx(
	PCSPI_CTX pContext,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->ECDSAGenerateKeys(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		ECDSA_ACQUIRE_STATE();

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pParameters,
				ECDSA_PARAMETERS_TYPE_PARAMETERS))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pContext->pPRNGState,
				ECDSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.ECDSAGenerateParameters(
				pECDSAState,
				ECDSA_GENERATE_PARAMETERS_TYPE_KEY_D) ||
			!Base.F.ECDSAGenerateParameters(
				pECDSAState,
				ECDSA_GENERATE_PARAMETERS_TYPE_KEY_Q))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.ECDSAGetStateParameters(
				pECDSAState, (PVOID) pPrivateKey,
				ECDSA_PARAMETERS_TYPE_KEY_D) ||
			!Base.F.ECDSAGetStateParameters(
				pECDSAState, (PVOID) pPublicKey,
				ECDSA_PARAMETERS_TYPE_KEY_Q))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		ECDSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACheckKeysCtx(
	PCSPI_CTX pContext,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		if(!pContext->pHardwareCSP->ECDSACheckKeys(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		ECDSA_ACQUIRE_STATE_WITH_CHECK();

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pContext->pPRNGState,
				ECDSA_PARAMETERS_TYPE_PRNG))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pParameters,
				ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pPrivateKey,
				ECDSA_PARAMETERS_TYPE_KEY_D))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(pPublicKey != NULL)
		{
			if(!Base.F.ECDSASetStateParameters(
					pECDSAState, (PVOID) pPublicKey,
					ECDSA_PARAMETERS_TYPE_KEY_Q))
			{
				ECDSA_RELEASE_STATE();
				return CSPI_ERROR_WRONG_PARAMETERS;
			}
		}

		ECDSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDEAEncryptDataCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	DES_BLOCK pDataAligment,
	PDWORD pdwDataAligment)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(GenerateRPRNSequenceCtx(
			pContext, (PBYTE) &pKeys->Key1,
			sizeof(DES_KEY)) != CSPI_NO_ERROR ||
		GenerateRPRNSequenceCtx(
			pContext, (PBYTE) &pKeys->Key2,
			sizeof(DES_KEY)) != CSPI_NO_ERROR ||
		GenerateRPRNSequenceCtx(
			pContext, (PBYTE) pIV,
			sizeof(DES_IV)) != CSPI_NO_ERROR)
	{
		return CSPI_ERROR_PRNG_CALL;
	}

	memcpy((PVOID) (&pKeys->Key3),
		(PVOID) (&pKeys->Key1), sizeof(DES_KEY));

	return TDESEncryptDataCtx(
		pContext, pbData, dwData,
		pKeys, pIV, FALSE, pDataAligment,
		pdwDataAligment);

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::AESEncryptDataCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PBYTE pKey,
	DWORD dwKey,
	AES_IV pIV,
	AES_BLOCK pDataAligment,
	PDWORD pdwDataAligment)
{
	CSPI_TRY();

	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(GenerateRPRNSequenceCtx(
			pContext, pKey,
			dwKey / 8) != CSPI_NO_ERROR ||
		GenerateRPRNSequenceCtx(
			pContext, (PBYTE) pIV,
			sizeof(AES_IV)) != CSPI_NO_ERROR)
	{
		return CSPI_ERROR_PRNG_CALL;
	}

	AES_ACQUIRE_STATE();

	if((dwData % sizeof(AES_BLOCK)) == 0)
	{
		pbAlignedData = pbData;
		dwAlignedData = dwData;
	}
	else
	{
		dwAlignedData = ((dwData / sizeof(AES_BLOCK)) + 1) *
			sizeof(AES_BLOCK);

		pbAlignedData = (PBYTE) malloc(dwAlignedData);
		if(pbAlignedData == NULL)
		{
			AES_RELEASE_STATE();
			return CSPI_ERROR_ALLOCATE_MEMORY;
		}

		memset((PVOID) pbAlignedData, 0, dwAlignedData);
		memcpy((PVOID) pbAlignedData, (PVOID) pbData, dwData);
	}

	if(!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pIV, AES_MODES_PARAMETERS_CBC_IV) ||
		!Base.F.AESEncryptDataCBCMode(pbAlignedData,
		dwAlignedData, pAESState))
	{
		if((dwData % sizeof(AES_BLOCK)) != 0)
			free((PVOID) pbAlignedData);

		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if((dwData % sizeof(AES_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData, dwData);
		memset((PVOID) pDataAligment, 0, sizeof(AES_BLOCK));

		*pdwDataAligment = dwAlignedData - dwData;

		memcpy((PVOID) pDataAligment,
			(PVOID) (pbAlignedData + dwData),
			*pdwDataAligment);

		free((PVOID) pbAlignedData);
	}
	else
	{
		*pdwDataAligment = 0;
	}

	AES_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::AESGetDataMACCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwBitDataLength,
	PBYTE pKey,
	DWORD dwKey,
	AES_BLOCK pRandom,
	DWORD dwBitsRandomLength,
	AES_MAC pMAC)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(GenerateRPRNSequenceCtx(
			pContext, pKey,
			dwKey / 8) != CSPI_NO_ERROR ||
		GenerateRPRNSequenceCtx(
			pContext, pRandom,
			dwBitsRandomLength / 8) != CSPI_NO_ERROR)
	{
		return CSPI_ERROR_PRNG_CALL;
	}

	AES_ACQUIRE_STATE();

	AES_MODE_MAC_PARAMETERS Parameters;

	Parameters.dwBitRandomLength = dwBitsRandomLength;
	Parameters.iDeriveKeysInternaly = TRUE;
	memcpy((PVOID) Parameters.Random, (PVOID) pRandom, 
		sizeof(AES_BLOCK));

	if(!Base.F.AESSetStateParameters(pAESState,
		(PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
		(PVOID) &Parameters, AES_MODES_PARAMETERS_MAC_ALL) ||
		!Base.F.AESGetDataMAC(pbData, dwBitDataLength,
		pMAC, sizeof(AES_BLOCK) * 8, pAESState))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	AES_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDEAGetDataMACCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwBitDataLength,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	DES_BLOCK pMAC)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(GenerateRPRNSequenceCtx(
			pContext, (PBYTE) &pKeys->Key1,
			sizeof(DES_KEY)) != CSPI_NO_ERROR ||
		GenerateRPRNSequenceCtx(
			pContext, (PBYTE) &pKeys->Key2,
			sizeof(DES_KEY)) != CSPI_NO_ERROR ||
		GenerateRPRNSequenceCtx(
			pContext, (PBYTE) pIV,
			sizeof(DES_IV)) != CSPI_NO_ERROR)
	{
		return CSPI_ERROR_PRNG_CALL;
	}

	memcpy((PVOID) (&pKeys->Key3), (PVOID) (&pKeys->Key1),
		sizeof(DES_KEY));

	TDEA_ACQUIRE_STATE();

	if(!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pKeys, TDEA_PARAMETERS_TYPE_KEY) ||
		!Base.F.TDEAGetDataMAC(pbData, pIV, dwBitDataLength,
		pTDEAState, pMAC))
	{
		TDEA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	TDEA_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::TDESEncryptDataCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	BOOL blGenerateKeyAndIV,
	DES_BLOCK pDataAligment,
	PDWORD pdwDataAligment)
{
	CSPI_TRY();

	PBYTE pbAlignedData;
	DWORD dwAlignedData;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(blGenerateKeyAndIV)
	{
		if(GenerateRPRNSequenceCtx(
				pContext, (PBYTE) &pKeys->Key1,
				sizeof(DES_KEY)) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) &pKeys->Key2,
				sizeof(DES_KEY)) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) &pKeys->Key3,
				sizeof(DES_KEY)) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) pIV,
				sizeof(DES_IV)) != CSPI_NO_ERROR)
		{
			return CSPI_ERROR_PRNG_CALL;
		}
	}

	TDEA_ACQUIRE_STATE();

	if((dwData % sizeof(DES_BLOCK)) == 0)
	{
		pbAlignedData = pbData;
		dwAlignedData = dwData;
	}
	else
	{
		dwAlignedData = ((dwData / sizeof(DES_BLOCK)) + 1) *
			sizeof(DES_BLOCK);

		pbAlignedData = (PBYTE) malloc(dwAlignedData);
		if(pbAlignedData == NULL)
		{
			TDEA_RELEASE_STATE();
			return CSPI_ERROR_ALLOCATE_MEMORY;
		}

		memset((PVOID) pbAlignedData, 0, dwAlignedData);
		memcpy((PVOID) pbAlignedData, (PVOID) pbData, dwData);
	}

	if(!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pKeys, TDEA_PARAMETERS_TYPE_KEY) ||
		!Base.F.TDEASetStateParameters(pTDEAState,
		(PVOID) pIV, TDEA_PARAMETERS_TYPE_CBCIV) ||
		!Base.F.TDEAEncryptDataCBCMode(pbAlignedData,
		dwAlignedData, pTDEAState))
	{
		if((dwData % sizeof(DES_BLOCK)) != 0)
			free((PVOID) pbAlignedData);

		TDEA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if((dwData % sizeof(DES_BLOCK)) != 0)
	{
		memcpy((PVOID) pbData, (PVOID) pbAlignedData, dwData);
		memset((PVOID) pDataAligment, 0, sizeof(DES_BLOCK));

		*pdwDataAligment = dwAlignedData - dwData;

		memcpy((PVOID) pDataAligment,
			(PVOID) (pbAlignedData + dwData),
			*pdwDataAligment);

		free((PVOID) pbAlignedData);
	}
	else
	{
		*pdwDataAligment = 0;
	}

	TDEA_RELEASE_STATE();

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBESHA1RC2EncryptCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	PDWORD pdwData,
	DWORD dwDataMaxSize,
	DWORD dwKeySize,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD dwError;
	DWORD dwKeyEffectiveBitLen;
	DWORD dwPBEData;
	RC2_KEY Key;
	RC2_IV IV;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFRC2DeriveKey == NULL ||
		m_pBaseEx->PKCS12PBKDFRC2DeriveIV == NULL ||
		m_pBaseEx->RC2SetStateParameters == NULL ||
		m_pBaseEx->RC2EncryptDataCBCMode == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	dwPBEData = CSPI_GET_PBE_DATA_SIZE(
		*pdwData, sizeof(RC2_BLOCK));
	if(dwPBEData > dwDataMaxSize)
	{
		*pdwData = dwPBEData;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(dwKeySize > sizeof(RC2_KEY))
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	dwKeyEffectiveBitLen = dwKeySize * 8;

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSPI_NO_ERROR)
			return dwError;
	}

	if(!m_pBaseEx->PKCS12PBKDFRC2DeriveKey(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		dwKeySize, Key) ||
		!m_pBaseEx->PKCS12PBKDFRC2DeriveIV(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		IV))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	memset((PVOID) (pbData + *pdwData),
		dwPBEData - *pdwData,
		dwPBEData - *pdwData);

	RC2_ACQUIRE_STATE();

	if(!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) &dwKeyEffectiveBitLen,
		RC2_PARAMETERS_TYPE_KEY_EFFECTIVE_BIT_LENGTH) ||
		!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) &dwKeySize,
		RC2_PARAMETERS_TYPE_KEY_BYTE_LENGTH) ||
		!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) Key, RC2_PARAMETERS_TYPE_KEY) ||
		!m_pBaseEx->RC2SetStateParameters(pRC2State,
		(PVOID) IV, RC2_PARAMETERS_TYPE_IV) ||
		!m_pBaseEx->RC2EncryptDataCBCMode(pbData,
		dwPBEData / sizeof(RC2_BLOCK), pRC2State))
	{
		RC2_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*pdwData = dwPBEData;

	RC2_RELEASE_STATE();

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBESHA1TDESEncryptCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	PDWORD pdwData,
	DWORD dwDataMaxSize,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD						dwError;
	DWORD						dwPBEData;
	DWORD						dwAligment;
	TDEA_KEYS					Key;
	DES_IV						IV;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFTDESDeriveKey == NULL ||
		m_pBaseEx->PKCS12PBKDFTDESDeriveIV == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	dwPBEData = CSPI_GET_PBE_DATA_SIZE(
		*pdwData, sizeof(DES_BLOCK));
	if(dwPBEData > dwDataMaxSize)
	{
		*pdwData = dwPBEData;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSPI_NO_ERROR)
			return dwError;
	}

	if(!m_pBaseEx->PKCS12PBKDFTDESDeriveKey(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		&Key) ||
		!m_pBaseEx->PKCS12PBKDFTDESDeriveIV(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		IV))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	memset((PVOID) (pbData + *pdwData),
		dwPBEData - *pdwData,
		dwPBEData - *pdwData);

	dwError = TDESEncryptData(
		pbData, dwPBEData,
		&Key, IV, FALSE, NULL,
		&dwAligment);
	if(dwError != CSPI_NO_ERROR)
	{
		return dwError;
	}

	*pdwData = dwPBEData;

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::SHA1CreateHMACCtx(
	PCSPI_CTX pContext,
	PBYTE pbData,
	DWORD dwData,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	SHA1_HMAC_HASH pHash)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD						dwError;
	SHA1_HMAC_KEY				Key;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFSHA1DeriveHMACKey == NULL ||
		m_pBaseEx->SHA1HMACSetStateParameters == NULL ||
		m_pBaseEx->SHA1HMACInitializeDataMac == NULL ||
		m_pBaseEx->SHA1HMACUpdateData == NULL ||
		m_pBaseEx->SHA1HMACFinalizeDataMac == NULL ||
		m_pBaseEx->SHA1HMACGetStateParameters == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSPI_NO_ERROR)
			return dwError;
	}

	if(!m_pBaseEx->PKCS12PBKDFSHA1DeriveHMACKey(
		pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter,
		Key))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return SHA1CreateHMACWithKey(pbData, dwData, Key, pHash);
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSARecoverPublicKeyCtx(
	PCSPI_CTX pContext,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	PRSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareRecoverPublicKey;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY,
			bHardwareRecoverPublicKey);
		if (!bHardwareRecoverPublicKey)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->RSARecoverPublicKey(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		RSA_ACQUIRE_STATE();

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pContext->pPRNGState,
				RSA_PARAMETERS_TYPE_PRNG))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pParameters,
				RSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pPrivateKey,
				RSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		RSA_RELEASE_STATE();

		memcpy((PVOID) pPublicKey->n,
			(PVOID) pPrivateKey->n,
			sizeof(RSA_NUMBER));
		memcpy((PVOID) pPublicKey->e,
			(PVOID) pPrivateKey->e,
			sizeof(RSA_NUMBER));
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::DSARecoverPublicKeyCtx(
	PCSPI_CTX pContext,
	PDSA_PARAMETERS pParameters,
	PDSA_PRIVATE_KEY pPrivateKey,
	PDSA_PUBLIC_KEY pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareRecoverPublicKey;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY,
			bHardwareRecoverPublicKey);
		if (!bHardwareRecoverPublicKey)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->DSARecoverPublicKey(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		DSA_ACQUIRE_STATE();

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pContext->pPRNGState,
				DSA_PARAMETERS_TYPE_PRNG))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pParameters,
				DSA_PARAMETERS_TYPE_DOMAIN_PARAMETERS) ||
			!Base.F.DSASetStateParameters(
				pDSAState, (PVOID) pPrivateKey,
				DSA_PARAMETERS_TYPE_PRIVATE_KEY) ||
			!Base.F.DSAGenerateParameters(
				pDSAState,
				DSA_GENERATE_PARAMETERS_TYPE_PUBLIC_KEY) ||
			!Base.F.DSAGetStateParameters(
				pDSAState, (PVOID) pPublicKey,
				DSA_PARAMETERS_TYPE_PUBLIC_KEY))
		{
			DSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		DSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSARecoverPublicKeyCtx(
	PCSPI_CTX pContext,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey,
	ECDSA_KEY_Q pPublicKey)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareRecoverPublicKey;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY,
			bHardwareRecoverPublicKey);
		if (!bHardwareRecoverPublicKey)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->ECDSARecoverPublicKey(
				pParameters, pPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		ECDSA_ACQUIRE_STATE();

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pContext->pPRNGState,
				ECDSA_PARAMETERS_TYPE_PRNG))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pParameters,
				ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pPrivateKey,
				ECDSA_PARAMETERS_TYPE_KEY_D) ||
			!Base.F.ECDSAGenerateParameters(
				pECDSAState,
				ECDSA_GENERATE_PARAMETERS_TYPE_KEY_Q))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.ECDSAGetStateParameters(
				pECDSAState, (PVOID) pPublicKey,
				ECDSA_PARAMETERS_TYPE_KEY_Q))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		ECDSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBKDF2IDeriveKeyCtx(
	PCSPI_CTX pContext,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	PTDEA_KEYS pDerivedKey)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12
	DWORD dwError;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if (m_pBaseEx == NULL ||
		m_pBaseEx->PBKDF2IDeriveKey == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSPI_NO_ERROR)
			return dwError;
	}

	if(!m_pBaseEx->PBKDF2IDeriveKey(pbPassword, dwPassword,
		pbSalt, dwSalt, dwCounter, pDerivedKey))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeTDESEncryptDataCtx(
	PCSPI_CTX pContext,
	PTDEA_KEYS pKeys,
	DES_IV pIV,
	BOOL blGenerateKeyAndIV,
	PTDEA_STATE *ppTDEAState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if (pKeys == NULL || pIV == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(blGenerateKeyAndIV)
	{
		if(GenerateRPRNSequenceCtx(
				pContext, (PBYTE) &pKeys->Key1,
				sizeof(DES_KEY)) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) &pKeys->Key2,
				sizeof(DES_KEY)) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) &pKeys->Key3,
				sizeof(DES_KEY)) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) pIV,
				sizeof(DES_IV)) != CSPI_NO_ERROR)
		{
			return CSPI_ERROR_PRNG_CALL;
		}

		SetParityBits(&pKeys->Key1);
		SetParityBits(&pKeys->Key2);
		SetParityBits(&pKeys->Key3);
	}

	TDEA_ACQUIRE_STATE();

	if(!Base.F.TDEASetStateParameters(
			pTDEAState, (PVOID) pKeys,
			TDEA_PARAMETERS_TYPE_KEY) ||
		!Base.F.TDEASetStateParameters(
			pTDEAState, (PVOID) pIV,
			TDEA_PARAMETERS_TYPE_CBCIV))
	{
		TDEA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*ppTDEAState = pTDEAState;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeAESEncryptDataCtx(
	PCSPI_CTX pContext,
	PAES_CIPHER_KEY pKey,
	DWORD dwKey,
	AES_IV pIV,
	BOOL blGenerateKeyAndIV,
	PAES_STATE *ppAESState)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pKey == NULL || pIV == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(blGenerateKeyAndIV)
	{
		if(GenerateRPRNSequenceCtx(
				pContext, pKey,
				dwKey / 8) != CSPI_NO_ERROR ||
			GenerateRPRNSequenceCtx(
				pContext, (PBYTE) pIV,
				sizeof(AES_IV)) != CSPI_NO_ERROR)
		{
			return CSPI_ERROR_PRNG_CALL;
		}
	}

	AES_ACQUIRE_STATE();

	if(!Base.F.AESSetStateParameters(
			pAESState, (PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(
			pAESState, (PVOID) pIV,
			AES_MODES_PARAMETERS_CBC_IV))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*ppAESState = pAESState;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD()
}

//==============================================================================

DWORD WINAPI CSPI::SHA1CreateHMACWithKey(
	PBYTE						pbData,
	DWORD						dwData,
	SHA1_HMAC_KEY				pKey,
	SHA1_HMAC_HASH				pHash)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PKCS12PBKDFSHA1DeriveHMACKey == NULL ||
		m_pBaseEx->SHA1HMACSetStateParameters == NULL ||
		m_pBaseEx->SHA1HMACInitializeDataMac == NULL ||
		m_pBaseEx->SHA1HMACUpdateData == NULL ||
		m_pBaseEx->SHA1HMACFinalizeDataMac == NULL ||
		m_pBaseEx->SHA1HMACGetStateParameters == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	SHA1_HMAC_ACQUIRE_STATE();

	if(!m_pBaseEx->SHA1HMACSetStateParameters(
		pSHA1HMACState, (PVOID) pKey,
		SHA1_HMAC_PARAMETERS_TYPE_KEY) ||
		!m_pBaseEx->SHA1HMACInitializeDataMac(
		pSHA1HMACState) ||
		!m_pBaseEx->SHA1HMACUpdateData(
		pbData, dwData, pSHA1HMACState) ||
		!m_pBaseEx->SHA1HMACFinalizeDataMac(
		pSHA1HMACState) ||
		!m_pBaseEx->SHA1HMACGetStateParameters(
		pSHA1HMACState,
		(PVOID) pHash,
		SHA1_HMAC_PARAMETERS_TYPE_HMAC))
	{
		SHA1_HMAC_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	SHA1_HMAC_RELEASE_STATE();

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::SHA1CheckHMACWithKey(
	PBYTE						pbData,
	DWORD						dwData,
	SHA1_HMAC_KEY				pKey,
	SHA1_HMAC_HASH				pHash)
{
	CSPI_TRY();

#ifdef CSPI_PKCS12

	DWORD						dwError;
	SHA1_HMAC_HASH				Hash;

	if((dwError = SHA1CreateHMACWithKey(
		pbData, dwData, pKey, Hash)) != CSPI_NO_ERROR)
	{
		return dwError;
	}

	if(memcmp((PVOID) Hash, (PVOID) pHash,
		sizeof(SHA1_HMAC_HASH)) != 0)
	{
		return CSPI_ERROR_DATA_CORRUPTED;
	}

	return CSPI_NO_ERROR;
#else // CSPI_PKCS12
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_PKCS12

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::RSAPSSSignHash(
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	RSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = RSAPSSSignHashCtx(
		&Context, pHash, pParameters,
		pPrivateKey, pSignature);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAPSSVerifySignature(
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey,
	RSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	UINT dwVersion;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	RSA_ACQUIRE_STATE();

	dwVersion = RSA_PKCS1_V21_VERSION;

	if(!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) &dwVersion,
			RSA_PARAMETERS_TYPE_VERSION) ||
		!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) pParameters,
			RSA_PARAMETERS_TYPE_PARAMETERS) ||
		!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) pPublicKey,
			RSA_PARAMETERS_TYPE_PUBLIC_KEY) ||
		!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) pSignature,
			RSA_PARAMETERS_TYPE_SIGNATURE))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.RSASetStateParameters(
			pRSAState, (PVOID) pHash,
			RSA_PARAMETERS_TYPE_HASH))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!Base.F.RSAVerifySignature(pRSAState))
	{
		RSA_RELEASE_STATE();
		return CSPI_ERROR_BAD_SIGNATURE;
	}

	RSA_RELEASE_STATE();
	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::RSAPSSSignHashCtx(
	PCSPI_CTX pContext,
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	PRSA_PRIVATE_KEY pPrivateKey,
	RSA_SIGNATURE pSignature)
{
	CSPI_TRY();

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareRSAPSS;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_RSA_PSS_SIGN,
			bHardwareRSAPSS);
		if (!bHardwareRSAPSS)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->RSAPSSSignHash(
				pHash, pParameters, pSignature))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		UINT dwVersion;

		RSA_ACQUIRE_STATE();

		dwVersion = RSA_PKCS1_V21_VERSION;

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) &dwVersion,
				RSA_PARAMETERS_TYPE_VERSION) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pParameters,
				RSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pPrivateKey,
				RSA_PARAMETERS_TYPE_PRIVATE_KEY))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pContext->pPRNGState,
				RSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.RSASetStateParameters(
				pRSAState, (PVOID) pHash,
				RSA_PARAMETERS_TYPE_HASH) ||
			!Base.F.RSASignHash(pRSAState) ||
			!Base.F.RSAGetStateParameters(
				pRSAState, (PVOID) pSignature,
				RSA_PARAMETERS_TYPE_SIGNATURE))
		{
			RSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		RSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::InitializeAESGCMEncryptData(
	PAES_CIPHER_KEY				pKey,
	DWORD						dwKey,
	PBYTE						pbIV,
	DWORD						dwIV,
	PBYTE						pbAuthData,
	DWORD						dwAuthData,
	BOOL						blGenerateKey,
	BOOL						blGenerateIV,
	BOOL						blGenerateAuthData,
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = InitializeAESGCMEncryptDataCtx(
		&Context, pKey, dwKey,
		pbIV, dwIV,
		pbAuthData, dwAuthData,
		blGenerateKey, blGenerateIV,
		blGenerateAuthData, ppAESState);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeAESGCMEncryptDataCtx(
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
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

#ifdef CSPI_AES_GCM

	if (m_pBaseEx == NULL ||
		m_pBaseEx->AESEncryptDataGCMMode == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if (!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if (pKey == NULL || pbIV == NULL ||
		(pbAuthData == NULL && dwAuthData != 0))
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(blGenerateKey)
	{
		if(GenerateRPRNSequenceCtx(
				pContext, pKey,
				dwKey / 8) != CSPI_NO_ERROR)
		{
			return CSPI_ERROR_PRNG_CALL;
		}
	}

	if(blGenerateIV)
	{
		if(GenerateRPRNSequenceCtx(
				pContext, pbIV, dwIV) != CSPI_NO_ERROR)
		{
			return CSPI_ERROR_PRNG_CALL;
		}
	}

	if(blGenerateAuthData)
	{
		if(GenerateRPRNSequenceCtx(
				pContext, pbAuthData,
				dwAuthData) != CSPI_NO_ERROR)
		{
			return CSPI_ERROR_PRNG_CALL;
		}
	}

	AES_MODE_GCM_PARAMETERS GCMParameters;

	GCMParameters.pbIV = pbIV;
	GCMParameters.dwIVLength = dwIV;
	GCMParameters.pbAuthData = pbAuthData;
	GCMParameters.dwAuthDataLength = dwAuthData;

	AES_ACQUIRE_STATE();

	if(!Base.F.AESSetStateParameters(
			pAESState, (PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
			(PVOID) &GCMParameters,
			AES_MODES_PARAMETERS_GCM_PARAMETERS))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*ppAESState = pAESState;

	return CSPI_NO_ERROR;
#else // CSPI_AES_GCM
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GCM

	CSPI_CATCH_DWORD()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueAESGCMEncryptData(
	PBYTE						pbData,
	DWORD						dwData,
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

#ifdef CSPI_AES_GCM

	if (m_pBaseEx == NULL ||
		m_pBaseEx->AESEncryptDataGCMMode == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(!m_pBaseEx->AESEncryptDataGCMMode(pbData, dwData,
			*ppAESState))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;
#else // CSPI_AES_GCM
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GCM

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeAESGCMEncryptData(
	AES_MAC						pGCMMAC,
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

#if defined(CSPI_AES_GET_PARAMETERS) && defined(CSPI_AES_GCM)

	if (m_pBaseEx == NULL ||
		m_pBaseEx->AESGetStateParameters == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pGCMMAC == NULL)
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!m_pBaseEx->AESGetStateParameters(*ppAESState,
		pGCMMAC, AES_MODES_PARAMETERS_GCM_MAC))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	Base.F.AESReleaseState(*ppAESState);
	*ppAESState = NULL;

	return CSPI_NO_ERROR;
#else // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::InitializeAESGCMDecryptData(
	PAES_CIPHER_KEY				pKey,
	DWORD						dwKey,
	PBYTE						pbIV,
	DWORD						dwIV,
	PBYTE						pbAuthData,
	DWORD						dwAuthData,
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

#ifdef CSPI_AES_GCM

	if (m_pBaseEx == NULL ||
		m_pBaseEx->AESDecryptDataGCMMode == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pKey == NULL || pbIV == NULL ||
		(pbAuthData == NULL && dwAuthData != 0))
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(dwKey != AES_CIPHER_KEY_TYPE_128 &&
		dwKey != AES_CIPHER_KEY_TYPE_192 &&
		dwKey != AES_CIPHER_KEY_TYPE_256)
	{
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	AES_MODE_GCM_PARAMETERS GCMParameters;

	GCMParameters.pbIV = pbIV;
	GCMParameters.dwIVLength = dwIV;
	GCMParameters.pbAuthData = pbAuthData;
	GCMParameters.dwAuthDataLength = dwAuthData;

	AES_ACQUIRE_STATE();

	if(!Base.F.AESSetStateParameters(
			pAESState, (PVOID) pKey, dwKey) ||
		!Base.F.AESSetStateParameters(pAESState,
			(PVOID) &GCMParameters,
			AES_MODES_PARAMETERS_GCM_PARAMETERS))
	{
		AES_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	*ppAESState = pAESState;

	return CSPI_NO_ERROR;
#else // CSPI_AES_GCM
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GCM

	CSPI_CATCH_DWORD()
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ContinueAESGCMDecryptData(
	PBYTE						pbData,
	DWORD						dwData,
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

#ifdef CSPI_AES_GCM

	if (m_pBaseEx == NULL ||
		m_pBaseEx->AESDecryptDataGCMMode == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(!m_pBaseEx->AESDecryptDataGCMMode(pbData, dwData,
			*ppAESState))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;
#else // CSPI_AES_GCM
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GCM

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::FinalizeAESGCMDecryptData(
	AES_MAC						pGCMMAC,
	PAES_STATE					*ppAESState)
{
	CSPI_TRY();

#if defined(CSPI_AES_GET_PARAMETERS) && defined(CSPI_AES_GCM)

	if (m_pBaseEx == NULL ||
		m_pBaseEx->AESGetStateParameters == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pGCMMAC == NULL)
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_BAD_PARAMETERS;
	}

	if(!m_pBaseEx->AESGetStateParameters(*ppAESState,
		pGCMMAC, AES_MODES_PARAMETERS_GCM_MAC))
	{
		Base.F.AESReleaseState(*ppAESState);
		*ppAESState = NULL;
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	Base.F.AESReleaseState(*ppAESState);
	*ppAESState = NULL;

	return CSPI_NO_ERROR;
#else // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_AES_GET_PARAMETERS && CSPI_AES_GCM

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::ECDSACouplePart1EncryptKey(
	RSA_NUMBER pPaillierPublicKey,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey1,
	PAILLIER_NUMBER pEncryptedPrivateKey1)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSACouplePart1EncryptKeyCtx(
		&Context, pPaillierPublicKey,
		pParameters, pPrivateKey1,
		pEncryptedPrivateKey1);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACouplePart1EncryptKeyCtx(
	PCSPI_CTX pContext,
	RSA_NUMBER pPaillierPublicKey,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey1,
	PAILLIER_NUMBER pEncryptedPrivateKey1)
{
	CSPI_TRY();

#ifdef CSPI_ECDSA_COUPLE
	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->ECDSACouplePart1EncryptKey == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

	ECDSA_ACQUIRE_STATE();

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pParameters,
			ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
		!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pPrivateKey1,
			ECDSA_PARAMETERS_TYPE_KEY_D))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pContext->pPRNGState,
			ECDSA_PARAMETERS_TYPE_PRNG) ||
		!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pPaillierPublicKey,
			ECDSA_PARAMETERS_TYPE_PAILLIER_PUBLIC_KEY) ||
		!m_pBaseEx->ECDSACouplePart1EncryptKey(
			pECDSAState, pEncryptedPrivateKey1))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	ECDSA_RELEASE_STATE();

	return CSPI_NO_ERROR;
#else // CSPI_ECDSA_COUPLE
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_ECDSA_COUPLE

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACouplePart1Step1(
	PECDSA_PARAMETERS pParameters,
	ECDSA_NUMBER pKeyK1,
	ECDSA_ENCODED_POINT pComponentR1)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSACouplePart1Step1Ctx(
		&Context, pParameters, pKeyK1, pComponentR1);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACouplePart1Step1Ctx(
	PCSPI_CTX pContext,
	PECDSA_PARAMETERS pParameters,
	ECDSA_NUMBER pKeyK1,
	ECDSA_ENCODED_POINT pComponentR1)
{
	CSPI_TRY();

#ifdef CSPI_ECDSA_COUPLE
	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->ECDSACouplePart1Step1 == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

	ECDSA_ACQUIRE_STATE();

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pParameters,
			ECDSA_PARAMETERS_TYPE_PARAMETERS))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pContext->pPRNGState,
			ECDSA_PARAMETERS_TYPE_PRNG) ||
		!m_pBaseEx->ECDSACouplePart1Step1(
			pECDSAState, pComponentR1) ||
		!Base.F.ECDSAGetStateParameters(
			pECDSAState, (PVOID) pKeyK1,
			ECDSA_PARAMETERS_TYPE_KEY_K))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	ECDSA_RELEASE_STATE();

	return CSPI_NO_ERROR;
#else // CSPI_ECDSA_COUPLE
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_ECDSA_COUPLE

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACouplePart2Step(
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_NUMBER pPaillierPublicKey,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey2,
	ECDSA_ENCODED_POINT pComponentR1,
	PAILLIER_NUMBER pEncryptedPrivateKey1,
	ECDSA_NUMBER pCommonComponentR,
	PAILLIER_NUMBER pComponentS2)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSACouplePart2StepCtx(
		&Context, dwHash, pHash, pPaillierPublicKey,
		pParameters, pPrivateKey2, pComponentR1,
		pEncryptedPrivateKey1, pCommonComponentR,
		pComponentS2);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACouplePart2StepCtx(
	PCSPI_CTX pContext,
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_NUMBER pPaillierPublicKey,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKey2,
	ECDSA_ENCODED_POINT pComponentR1,
	PAILLIER_NUMBER pEncryptedPrivateKey1,
	ECDSA_NUMBER pCommonComponentR,
	PAILLIER_NUMBER pComponentS2)
{
	UINT uiHash;

	CSPI_TRY();

#ifdef CSPI_ECDSA_COUPLE
	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pContext == NULL)
		return CSPI_ERROR_BAD_PARAMETERS;

	if(pPrivateKey2 == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareECDSACouple;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_ECDSA_COUPLE,
			bHardwareECDSACouple);
		if (!bHardwareECDSACouple)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->ECDSACouplePart2Step(
				dwHash, pHash, pPaillierPublicKey,
				pParameters, pComponentR1,
				pEncryptedPrivateKey1,
				pCommonComponentR, pComponentS2))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(m_pBaseEx == NULL ||
			m_pBaseEx->ECDSACouplePart2Step == NULL)
		{
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		if(pContext->pPRNGState == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		ECDSA_ACQUIRE_STATE();

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pParameters,
				ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pPrivateKey2,
				ECDSA_PARAMETERS_TYPE_KEY_D))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		uiHash = dwHash;

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pContext->pPRNGState,
				ECDSA_PARAMETERS_TYPE_PRNG) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) &uiHash,
				ECDSA_PARAMETERS_TYPE_HASH_LENGTH) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pHash,
				ECDSA_PARAMETERS_TYPE_HASH) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pPaillierPublicKey,
				ECDSA_PARAMETERS_TYPE_PAILLIER_PUBLIC_KEY) ||
			!m_pBaseEx->ECDSACouplePart2Step(
				pECDSAState, pComponentR1,
				pEncryptedPrivateKey1,
				pCommonComponentR, pComponentS2))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		ECDSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;
#else // CSPI_ECDSA_COUPLE
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_ECDSA_COUPLE

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACouplePart1Step2(
	PRSA_PRIVATE_KEY pPaillierPrivateKey,
	PECDSA_PARAMETERS pParameters,
	ECDSA_NUMBER pKeyK1,
	ECDSA_NUMBER pCommonComponentR,
	PAILLIER_NUMBER pComponentS2,
	PECDSA_SIGNATURE pSignature)
{
	CSPI_TRY();

#ifdef CSPI_ECDSA_COUPLE
	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->ECDSACouplePart1Step2 == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	ECDSA_ACQUIRE_STATE();

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pParameters,
			ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
		!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pKeyK1,
			ECDSA_PARAMETERS_TYPE_KEY_K))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_WRONG_PARAMETERS;
	}

	if(!Base.F.ECDSASetStateParameters(
			pECDSAState, (PVOID) pPaillierPrivateKey,
			ECDSA_PARAMETERS_TYPE_PAILLIER_PRIVATE_KEY) ||
		!m_pBaseEx->ECDSACouplePart1Step2(
			pECDSAState, pCommonComponentR, pComponentS2) ||
		!Base.F.ECDSAGetStateParameters(
			pECDSAState, (PVOID) pSignature,
			ECDSA_PARAMETERS_TYPE_SIGNATURE))
	{
		ECDSA_RELEASE_STATE();
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	ECDSA_RELEASE_STATE();

	return CSPI_NO_ERROR;
#else // CSPI_ECDSA_COUPLE
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_ECDSA_COUPLE

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACoupleMakeCommonPublicKey(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKeyA,
	ECDSA_KEY_Q pPublicKeyB,
	ECDSA_KEY_Q pCommonPublicKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = ECDSACoupleMakeCommonPublicKeyCtx(
		&Context, pParameters, pPrivateKeyA,
		pPublicKeyB, pCommonPublicKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::ECDSACoupleMakeCommonPublicKeyCtx(
	PCSPI_CTX pContext,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_D pPrivateKeyA,
	ECDSA_KEY_Q pPublicKeyB,
	ECDSA_KEY_Q pCommonPublicKey)
{
	CSPI_TRY();

#ifdef CSPI_ECDSA_COUPLE
	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(pPrivateKeyA == NULL)
	{
		if(pContext->pHardwareCSP == NULL)
			return CSPI_ERROR_NOT_INITIALIZED;

		BOOL	bHardwareECDSACouple;

		CSPI_CHECK_COMPATIBLE_CTX(this, pContext,
			CSPI_COMPATIBLE_LEVEL_HARDWARE_ECDSA_COUPLE,
			bHardwareECDSACouple);
		if (!bHardwareECDSACouple)
			return CSPI_ERROR_PROGRAM_FAILURE;

		if(!pContext->pHardwareCSP->ECDSACoupleMakeCommonPublicKey(
				pParameters, pPublicKeyB, pCommonPublicKey))
		{
			return CSPI_ERROR_HARDWARE_CSP_FAILURE;
		}
	}
	else
	{
		if(m_pBaseEx == NULL ||
			m_pBaseEx->ECDSACoupleMakeCommonKey == NULL)
		{
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		ECDSA_ACQUIRE_STATE();

		if(!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pParameters,
				ECDSA_PARAMETERS_TYPE_PARAMETERS) ||
			!Base.F.ECDSASetStateParameters(
				pECDSAState, (PVOID) pPrivateKeyA,
				ECDSA_PARAMETERS_TYPE_KEY_D))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_WRONG_PARAMETERS;
		}

		if(!m_pBaseEx->ECDSACoupleMakeCommonKey(
				pECDSAState, pPublicKeyB, pCommonPublicKey))
		{
			ECDSA_RELEASE_STATE();
			return CSPI_ERROR_PROGRAM_FAILURE;
		}

		ECDSA_RELEASE_STATE();
	}

	return CSPI_NO_ERROR;
#else // CSPI_ECDSA_COUPLE
	return CSPI_ERROR_PROGRAM_FAILURE;
#endif // CSPI_ECDSA_COUPLE

	CSPI_CATCH_DWORD();
}

//==============================================================================

DWORD WINAPI CSPI::PBKDF2SHADeriveKey(
	DWORD dwHash,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	DWORD dwDeriverdKey,
	PBYTE pDerivedKey)
{
	CSPI_TRY();

	CSPI_CTX Context;
	DWORD dwError;

	CSPI_CTX_INITIALIZE(Context);

	dwError = PBKDF2SHADeriveKeyCtx(
		&Context, dwHash, pbPassword,
		dwPassword, pbSalt, dwSalt,
		blGenerateSalt, dwCounter,
		dwDeriverdKey, pDerivedKey);
	if (dwError != CSPI_NO_ERROR)
		return dwError;

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//------------------------------------------------------------------------------

DWORD WINAPI CSPI::PBKDF2SHADeriveKeyCtx(
	PCSPI_CTX pContext,
	DWORD dwHash,
	PBYTE pbPassword,
	DWORD dwPassword,
	PBYTE pbSalt,
	DWORD dwSalt,
	BOOL blGenerateSalt,
	DWORD dwCounter,
	DWORD dwDerivedKey,
	PBYTE pDerivedKey)
{
	CSPI_TRY();

	DWORD dwError;

	if(!(m_dwState & CSPI_STATE_CSP_LIBRARIES_LOADED))
		return CSPI_ERROR_LIBRARIES_NOT_LOADED;

	if(m_pBaseEx == NULL ||
		m_pBaseEx->PBKDF2SHADeriveKey == NULL)
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	if(blGenerateSalt && pbSalt && dwSalt)
	{
		dwError = GenerateRPRNSequenceCtx(
			pContext, pbSalt, dwSalt);
		if(dwError != CSPI_NO_ERROR)
			return dwError;
	}

	if (!m_pBaseEx->PBKDF2SHADeriveKey(
			dwHash, pbPassword, dwPassword,
			pbSalt, dwSalt, dwCounter,
			dwDerivedKey, pDerivedKey))
	{
		return CSPI_ERROR_PROGRAM_FAILURE;
	}

	return CSPI_NO_ERROR;

	CSPI_CATCH_DWORD();
}

//==============================================================================
