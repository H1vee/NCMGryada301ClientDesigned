//======================================================================================================================

#include "CSPBase.h"

//======================================================================================================================

#ifdef OS_MAC
#define CSP_BASE_LIBRARY_NAME "cspb.dylib"
#define CSP_EXTENSION_LIBRARY_NAME "cspe.dylib"
#elif defined (ANDROID_NDK)
#define CSP_BASE_LIBRARY_NAME "libcspb.so"
#define CSP_EXTENSION_LIBRARY_NAME "libcspe.so"
#elif defined (OS_NIX)
#define CSP_BASE_LIBRARY_NAME "cspb.so"
#define CSP_EXTENSION_LIBRARY_NAME "cspe.so"
#else // OS_NIX
#ifdef PC_LIBS_IN_CURRENT
#define CSP_BASE_LIBRARY_NAME L"CSPBase.dll"
#define CSP_EXTENSION_LIBRARY_NAME L"CSPExtension.dll"
#else // PC_LIBS_IN_CURRENT
#define CSP_BASE_LIBRARY_NAME "CSPBase.dll"
#define CSP_EXTENSION_LIBRARY_NAME "CSPExtension.dll"
#endif // PC_LIBS_IN_CURRENT
#endif // OS_NIX

//======================================================================================================================

CSPBase::CSPBase()
{
#ifndef PC_STATIC_LIBS
	m_hBaseLibrary = NULL;
	m_hExtensionLibrary = NULL;
#endif // PC_STATIC_LIBS
}

//----------------------------------------------------------------------------------------------------------------------

CSPBase::~CSPBase()
{
#ifndef PC_STATIC_LIBS
	if(m_hBaseLibrary != NULL)
		FreeLibrary(m_hBaseLibrary);

	if(m_hExtensionLibrary != NULL)
		FreeLibrary(m_hExtensionLibrary);
#endif // PC_STATIC_LIBS
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPBase::Load()
{
#ifndef PC_STATIC_LIBS
	if((m_hBaseLibrary != NULL) &&
		(m_hExtensionLibrary != NULL))
	{
		return TRUE;
	}

#ifdef PC_LIBS_IN_CURRENT
#ifndef OS_NIX
	WCHAR szLibraryFile[MAX_PATH * 4];

	GetCurrentDirectoryW(MAX_PATH * 4, szLibraryFile);

	if(szLibraryFile[wcslen(szLibraryFile) - 1] != L'\\')
		wcscat(szLibraryFile, L"\\");

	wcscat(szLibraryFile, CSP_BASE_LIBRARY_NAME);

	m_hBaseLibrary = LoadLibraryW(szLibraryFile);
#else // OS_NIX
	CHAR szLibraryFile[MAX_PATH * 4];

	GetCurrentDirectory(MAX_PATH * 4, szLibraryFile);

	if(szLibraryFile[strlen(szLibraryFile) - 1] != '\\')
		strcat(szLibraryFile, "\\");

	strcat(szLibraryFile, CSP_BASE_LIBRARY_NAME);

	m_hBaseLibrary = LoadLibraryA(szLibraryFile);
#endif // OS_NIX
#else // PC_LIBS_IN_CURRENT
	m_hBaseLibrary = LoadLibraryA(CSP_BASE_LIBRARY_NAME);
#endif // PC_LIBS_IN_CURRENT
	if(!m_hBaseLibrary)
	{
		return FALSE;
	}

	F.DSTU4145SelfTest = (PDSTU4145_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU4145SelfTest");
	F.DSTU4145AcquireState = (PDSTU4145_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145AcquireState");
	F.DSTU4145ReleaseState = (PDSTU4145_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145ReleaseState");
	F.DSTU4145SetStateParameters = (PDSTU4145_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU4145SetStateParameters");
	F.DSTU4145GetStateParameters = (PDSTU4145_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU4145GetStateParameters");
	F.DSTU4145GenerateParameters = (PDSTU4145_GENERATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU4145GenerateParameters");
	F.DSTU4145SignHash = (PDSTU4145_SIGN_HASH)
		GetProcAddress(m_hBaseLibrary, "DSTU4145SignHash");
	F.DSTU4145VerifySignature = (PDSTU4145_VERIFY_SIGNATURE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145VerifySignature");
	F.DSTU4145Trace = (PDSTU4145_TRACE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145Trace");
	F.DSTU4145HalfTrace = (PDSTU4145_HALF_TRACE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145HalfTrace");
	F.DSTU4145SolveQuadEqual = (PDSTU4145_SOLVE_QUAD_EQUAL)
		GetProcAddress(m_hBaseLibrary, "DSTU4145SolveQuadEqual");

	F.DSTU4145PseudoRNGSelfTest = (PDSTU4145_PSEUDO_RNG_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGSelfTest");
	F.DSTU4145PseudoRNGInitialize = (PDSTU4145_PSEUDO_RNG_INITIALIZE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGInitialize");
	F.DSTU4145PseudoRNGDeinitialize = (PDSTU4145_PSEUDO_RNG_DEINITIALIZE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGDeinitialize");
	F.DSTU4145PseudoRNGGenerateSequence = 
		(PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE)
			GetProcAddress(m_hBaseLibrary, 
				"DSTU4145PseudoRNGGenerateSequence");

	F.ECDHSelfTest = (PECDH_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "ECDHSelfTest");
	F.ECDHCalculateSharedKey = (PECDH_CALCULATE_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary, "ECDHCalculateSharedKey");

	F.GOST28147SelfTest = (PGOST28147_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "GOST28147SelfTest");
	F.GOST28147AcquireState = (PGOST28147_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOST28147AcquireState");
	F.GOST28147ReleaseState = (PGOST28147_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOST28147ReleaseState");
	F.GOST28147SetStateParameters = (PGOST28147_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOST28147SetStateParameters");
	F.GOST28147GetStateParameters = (PGOST28147_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOST28147GetStateParameters");
	F.GOST28147EncryptDataSSMode = (PGOST28147_ENCRYPT_DATA_SS_MODE)
		GetProcAddress(m_hBaseLibrary, "GOST28147EncryptDataSSMode");
	F.GOST28147DecryptDataSSMode = (PGOST28147_DECRYPT_DATA_SS_MODE)
		GetProcAddress(m_hBaseLibrary, "GOST28147DecryptDataSSMode");
	F.GOST28147EncryptDataGMode = (PGOST28147_ENCRYPT_DATA_G_MODE)
		GetProcAddress(m_hBaseLibrary, "GOST28147EncryptDataGMode");
	F.GOST28147EncryptDataGOFBMode = (PGOST28147_ENCRYPT_DATA_GOFB_MODE)
		GetProcAddress(m_hBaseLibrary, "GOST28147EncryptDataGOFBMode");
	F.GOST28147DecryptDataGOFBMode = (PGOST28147_DECRYPT_DATA_GOFB_MODE)
		GetProcAddress(m_hBaseLibrary, "GOST28147DecryptDataGOFBMode");
	F.GOST28147GetDataMAC = (PGOST28147_GET_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "GOST28147GetDataMAC");

	F.GOST34311SelfTest = (PGOST34311_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "GOST34311SelfTest");
	F.GOST34311AcquireState = (PGOST34311_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOST34311AcquireState");
	F.GOST34311ReleaseState = (PGOST34311_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOST34311ReleaseState");
	F.GOST34311SetStateParameters = (PGOST34311_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOST34311SetStateParameters");
	F.GOST34311GetStateParameters = (PGOST34311_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOST34311GetStateParameters");
	F.GOST34311HashData = (PGOST34311_HASH_DATA)
		GetProcAddress(m_hBaseLibrary, "GOST34311HashData");
	F.GOST34311FinalizeHash = (PGOST34311_FINALIZE_HASH)
		GetProcAddress(m_hBaseLibrary, "GOST34311FinalizeHash");

#ifdef CSP_ECDH_UA
	F.ECDHUASelfTest = (PECDH_UA_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "ECDHUASelfTest");
	F.ECDHUACalculateSharedKey = (PECDH_UA_CALCULATE_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary, "ECDHUACalculateSharedKey");
	F.GOST28147WrapSharedKey = (PGOST28147_WRAP_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary, "GOST28147WrapSharedKey");
	F.GOST28147UnwrapSharedKey = (PGOST28147_UNWRAP_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary, "GOST28147UnwrapSharedKey");
#endif // CSP_ECDH_UA

	DWORD dw;

	for(dw = 0; dw < sizeof(CSP_BASE_FUNCTIONS) / sizeof(PVOID); dw++)
	{
		if(((PVOID *) &F)[dw] == NULL)
		{
			FreeLibrary(m_hBaseLibrary);
			m_hBaseLibrary = NULL;

			return FALSE;
		}
	}

#ifdef CAP_VERIFICATOR
	VerificationF.DSTU4145PPolinomToNumber = (PDSTU4145_P_POLINOM_TO_NUMBER)
		GetProcAddress(m_hBaseLibrary,
			"DSTU4145PPolinomToNumber");
	VerificationF.DSTU4145NPolinomToNumber = (PDSTU4145_N_POLINOM_TO_NUMBER)
		GetProcAddress(m_hBaseLibrary, "DSTU4145NPolinomToNumber");
	VerificationF.DSTU4145SRToD = (PDSTU4145_SR_TO_D)
		GetProcAddress(m_hBaseLibrary, "DSTU4145SRToD");
	VerificationF.DSTU4145IsPolynomPermissible =
		(PDSTU4145_IS_POLYNOM_PERMISSIBLE)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145IsPolynomPermissible");
	VerificationF.DSTU4145CheckN = (PDSTU4145_CHECK_N)
		GetProcAddress(m_hBaseLibrary, "DSTU4145CheckN");
	VerificationF.DSTU4145TestOnStandartParameters =
		(PDSTU4145_TEST_ON_STANDART_PARAMETERS)
			GetProcAddress(m_hBaseLibrary, 
				"DSTU4145TestOnStandartParameters");
	VerificationF.DSTU4145PseudoRNGGenerateSequenceInBits =
		(PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE_INBITS)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145PseudoRNGGenerateSequenceInBits");
	VerificationF.DSTU4145IsInRange = (PDSTU4145_IS_IN_RANGE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145IsInRange");
	VerificationF.DSTU4145IsPrime = (PDSTU4145_IS_PRIME)
		GetProcAddress(m_hBaseLibrary, "DSTU4145IsPrime");
	VerificationF.DSTU4145IsMOV = (PDSTU4145_IS_MOV)
		GetProcAddress(m_hBaseLibrary, "DSTU4145IsMOV");

	for(dw = 0; dw < sizeof(CSP_VERIFICATION_FUNCTIONS) / 
		sizeof(PVOID); dw++)
	{
		if(((PVOID *) &VerificationF)[dw] == NULL)
		{
			fprintf(stderr,"CSPVerification: "
				"Function %d not found\n", dw);
			FreeLibrary(m_hBaseLibrary);
			m_hBaseLibrary = NULL;

			return FALSE;
		}
	}
#endif // CAP_VERIFICATOR

#ifdef PC_LIBS_IN_CURRENT
#ifndef OS_NIX
	GetCurrentDirectoryW(MAX_PATH * 4, szLibraryFile);

	if(szLibraryFile[wcslen(szLibraryFile) - 1] != L'\\')
		wcscat(szLibraryFile, L"\\");

	wcscat(szLibraryFile, CSP_EXTENSION_LIBRARY_NAME);

	m_hExtensionLibrary = LoadLibraryW(szLibraryFile);
#else // OS_NIX
	GetCurrentDirectory(MAX_PATH * 4, szLibraryFile);

	if(szLibraryFile[strlen(szLibraryFile) - 1] != '\\')
		strcat(szLibraryFile, "\\");

	strcat(szLibraryFile, CSP_EXTENSION_LIBRARY_NAME);

	m_hExtensionLibrary = LoadLibraryA(szLibraryFile);
#endif // OS_NIX
#else // PC_LIBS_IN_CURRENT
	m_hExtensionLibrary = LoadLibraryA(CSP_EXTENSION_LIBRARY_NAME);
#endif // PC_LIBS_IN_CURRENT
	if(!m_hExtensionLibrary)
	{
		FreeLibrary(m_hBaseLibrary);
		m_hBaseLibrary = NULL;

		return FALSE;
	}

	ExtensionF.TSCGIsEnable = (PTSCG_IS_ENABLE)
		GetProcAddress(m_hExtensionLibrary, "TSCGIsEnable");
	ExtensionF.TSCGGenerateSequence = (PTSCG_GENERATE_SEQUENCE)
		GetProcAddress(m_hExtensionLibrary, "TSCGGenerateSequence");

	ExtensionF.BSTestSequence = (PBS_TEST_SEQUENCE)
		GetProcAddress(m_hExtensionLibrary, "BSTestSequence");
	ExtensionF.BSReleaseStatistic = (PBS_RELEASE_STATISTIC)
		GetProcAddress(m_hExtensionLibrary, "BSReleaseStatistic");

	ExtensionF.CRC32Count = (PCRC32_COUNT)
		GetProcAddress(m_hExtensionLibrary, "CRC32Count");

	for(dw = 0; dw < sizeof(CSP_EXTENSION_FUNCTIONS) / sizeof(PVOID); dw++)
	{
		if(((PVOID *) &ExtensionF)[dw] == NULL)
		{
			fprintf(stderr,"CSPExtension: "
				"Function %d not found\n", dw);
			FreeLibrary(m_hBaseLibrary);
			m_hBaseLibrary = NULL;

			FreeLibrary(m_hExtensionLibrary);
			m_hExtensionLibrary = NULL;

			return FALSE;
		}
	}
#else // PC_STATIC_LIBS
	CSPInitialize();

	F.DSTU4145SelfTest = DSTU4145SelfTest;
	F.DSTU4145AcquireState = DSTU4145AcquireState;
	F.DSTU4145ReleaseState = DSTU4145ReleaseState;
	F.DSTU4145SetStateParameters = DSTU4145SetStateParameters;
	F.DSTU4145GetStateParameters = DSTU4145GetStateParameters;
	F.DSTU4145GenerateParameters = DSTU4145GenerateParameters;
	F.DSTU4145SignHash = DSTU4145SignHash;
	F.DSTU4145VerifySignature = DSTU4145VerifySignature;
	F.DSTU4145Trace = DSTU4145Trace;
	F.DSTU4145HalfTrace = DSTU4145HalfTrace;
	F.DSTU4145SolveQuadEqual = DSTU4145SolveQuadEqual;
	
	F.DSTU4145PseudoRNGSelfTest = DSTU4145PseudoRNGSelfTest;
	F.DSTU4145PseudoRNGInitialize = DSTU4145PseudoRNGInitialize;
	F.DSTU4145PseudoRNGDeinitialize = DSTU4145PseudoRNGDeinitialize;
	F.DSTU4145PseudoRNGGenerateSequence = DSTU4145PseudoRNGGenerateSequence;
	
	F.ECDHSelfTest = ECDHSelfTest;
	F.ECDHCalculateSharedKey = ECDHCalculateSharedKey;
	
	F.GOST28147SelfTest = GOST28147SelfTest;
	F.GOST28147AcquireState = GOST28147AcquireState;
	F.GOST28147ReleaseState = GOST28147ReleaseState;
	F.GOST28147SetStateParameters = GOST28147SetStateParameters;
	F.GOST28147GetStateParameters = GOST28147GetStateParameters;
	F.GOST28147EncryptDataSSMode = GOST28147EncryptDataSSMode;
	F.GOST28147DecryptDataSSMode = GOST28147DecryptDataSSMode;
	F.GOST28147EncryptDataGMode = GOST28147EncryptDataGMode;
	F.GOST28147EncryptDataGOFBMode = GOST28147EncryptDataGOFBMode;
	F.GOST28147DecryptDataGOFBMode = GOST28147DecryptDataGOFBMode;
	F.GOST28147GetDataMAC = GOST28147GetDataMAC;
	
	F.GOST34311SelfTest = GOST34311SelfTest;
	F.GOST34311AcquireState = GOST34311AcquireState;
	F.GOST34311ReleaseState = GOST34311ReleaseState;
	F.GOST34311SetStateParameters = GOST34311SetStateParameters;
	F.GOST34311GetStateParameters = GOST34311GetStateParameters;
	F.GOST34311HashData = GOST34311HashData;
	F.GOST34311FinalizeHash = GOST34311FinalizeHash;

#ifdef CSP_ECDH_UA
	F.ECDHUASelfTest = ECDHUASelfTest;
	F.ECDHUACalculateSharedKey = ECDHUACalculateSharedKey;
	F.GOST28147WrapSharedKey = GOST28147WrapSharedKey;
	F.GOST28147UnwrapSharedKey = GOST28147UnwrapSharedKey;
#endif // CSP_ECDH_UA

#ifdef CAP_VERIFICATOR
	VerificationF.DSTU4145PPolinomToNumber = DSTU4145PPolinomToNumber;
	VerificationF.DSTU4145NPolinomToNumber = DSTU4145NPolinomToNumber;
	VerificationF.DSTU4145SRToD = DSTU4145SRToD;
	VerificationF.DSTU4145IsPolynomPermissible = DSTU4145IsPolynomPermissible;
	VerificationF.DSTU4145CheckN = DSTU4145CheckN;
	VerificationF.DSTU4145TestOnStandartParameters = DSTU4145TestOnStandartParameters;
	VerificationF.DSTU4145PseudoRNGGenerateSequenceInBits = DSTU4145PseudoRNGGenerateSequenceInBits;
	VerificationF.DSTU4145IsInRange = DSTU4145IsInRange;
	VerificationF.DSTU4145IsPrime = DSTU4145IsPrime;
	VerificationF.DSTU4145IsMOV = DSTU4145IsMOV;
#endif // CAP_VERIFICATOR
	
	ExtensionF.TSCGIsEnable = TSCGIsEnable;
	ExtensionF.TSCGGenerateSequence = TSCGGenerateSequence;
	
	ExtensionF.BSTestSequence = BSTestSequence;
	ExtensionF.BSReleaseStatistic = BSReleaseStatistic;
	
	ExtensionF.CRC32Count = CRC32Count;
#endif // PC_STATIC_LIBS

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPBase::LoadEx(
	PCSP_BASE_FUNCTIONS_EX *ppBaseEx)
{
	PCSP_BASE_FUNCTIONS_EX pBaseEx;

#ifndef PC_STATIC_LIBS
	if(!m_hBaseLibrary)
		return FALSE;
#endif // PC_STATIC_LIBS

	pBaseEx = new CSP_BASE_FUNCTIONS_EX;
	if(pBaseEx == NULL)
		return FALSE;

	pBaseEx->nSize = 80;
	pBaseEx->nReserved = 0;

#ifdef CSP_KDF_UA
#ifndef PC_STATIC_LIBS
	pBaseEx->GOST34311HMACSelfTest = (PGOST34311_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "GOST34311HMACSelfTest");
	pBaseEx->GOST34311HMACAcquireState = (PGOST34311HMAC_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOST34311HMACAcquireState");
	pBaseEx->GOST34311HMACReleaseState = (PGOST34311HMAC_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOST34311HMACReleaseState");
	pBaseEx->GOST34311HMACSetStateParameters =
		(PGOST34311HMAC_SET_STATE_PARAMETERS)
			GetProcAddress(m_hBaseLibrary,
				"GOST34311HMACSetStateParameters");
	pBaseEx->GOST34311HMACGetStateParameters =
		(PGOST34311HMAC_GET_STATE_PARAMETERS)
			GetProcAddress(m_hBaseLibrary,
				"GOST34311HMACGetStateParameters");
	pBaseEx->GOST34311HMACUpdateData = (PGOST34311HMAC_UPDATE_DATA)
		GetProcAddress(m_hBaseLibrary, "GOST34311HMACUpdateData");
	pBaseEx->GOST34311HMACFinalizeDataMac =
		(PGOST34311HMAC_FINALIZE_DATA_MAC)
			GetProcAddress(m_hBaseLibrary,
				"GOST34311HMACFinalizeDataMac");

	pBaseEx->PBKDF2SelfTest = (PPBKDF2_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "PBKDF2SelfTest");
	pBaseEx->PBKDF2DeriveKey = (PPBKDF2_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PBKDF2DeriveKey");

	pBaseEx->PBKDFMACSelfTest = (PPBKDFMAC_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "PBKDFMACSelfTest");
	pBaseEx->PBKDFMACDeriveKey = (PPBKDFMAC_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PBKDFMACDeriveKey");

#else //PC_STATIC_LIBS
	pBaseEx->GOST34311HMACSelfTest = GOST34311HMACSelfTest;
	pBaseEx->GOST34311HMACAcquireState = GOST34311HMACAcquireState;
	pBaseEx->GOST34311HMACReleaseState = GOST34311HMACReleaseState;
	pBaseEx->GOST34311HMACSetStateParameters =
		GOST34311HMACSetStateParameters;
	pBaseEx->GOST34311HMACGetStateParameters =
		GOST34311HMACGetStateParameters;
	pBaseEx->GOST34311HMACUpdateData = GOST34311HMACUpdateData;
	pBaseEx->GOST34311HMACFinalizeDataMac = GOST34311HMACFinalizeDataMac;

	pBaseEx->PBKDF2SelfTest = PBKDF2SelfTest;
	pBaseEx->PBKDF2DeriveKey = PBKDF2DeriveKey;

	pBaseEx->PBKDFMACSelfTest = PBKDFMACSelfTest;
	pBaseEx->PBKDFMACDeriveKey = PBKDFMACDeriveKey;

#endif // PC_STATIC_LIBS
#else // CSP_KDF_UA
	pBaseEx->GOST34311HMACSelfTest = NULL;
	pBaseEx->GOST34311HMACAcquireState = NULL;
	pBaseEx->GOST34311HMACReleaseState = NULL;
	pBaseEx->GOST34311HMACSetStateParameters = NULL;
	pBaseEx->GOST34311HMACGetStateParameters = NULL;
	pBaseEx->GOST34311HMACUpdateData = NULL;
	pBaseEx->GOST34311HMACFinalizeDataMac = NULL;

	pBaseEx->PBKDF2SelfTest = NULL;
	pBaseEx->PBKDF2DeriveKey = NULL;

	pBaseEx->PBKDFMACSelfTest = NULL;
	pBaseEx->PBKDFMACDeriveKey = NULL;

#endif // CSP_KDF_UA

#ifdef CSP_REINITIALIZE_PRNG
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU4145PseudoRNGReinitialize =
		(PDSTU4145_PSEUDO_RNG_REINITIALIZE)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145PseudoRNGReinitialize");

#else //PC_STATIC_LIBS
	pBaseEx->DSTU4145PseudoRNGReinitialize =
		DSTU4145PseudoRNGReinitialize;

#endif // PC_STATIC_LIBS
#else // CSP_REINITIALIZE_PRNG
	pBaseEx->DSTU4145PseudoRNGReinitialize = NULL;

#endif // CSP_REINITIALIZE_PRNG

#ifdef CSP_DSTU4145_COUPLE
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU4145CoupleSelfTest = (PDSTU4145_COUPLE_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU4145CoupleSelfTest");
	pBaseEx->DSTU4145CoupleMakeCommonKeyQ =
		(PDSTU4145_COUPLE_GENERATE_COMMON_KEY_Q)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145CoupleMakeCommonKeyQ");
	pBaseEx->DSTU4145CoupleMakeSignR = (PDSTU4145_COUPLE_MAKE_SIGN_R)
		GetProcAddress(m_hBaseLibrary, "DSTU4145CoupleMakeSignR");
	pBaseEx->DSTU4145CoupleMakeCommonSignR =
		(PDSTU4145_COUPLE_MAKE_COMMON_SIGN_R)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145CoupleMakeCommonSignR");
	pBaseEx->DSTU4145CoupleMakeSignS = (PDSTU4145_COUPLE_MAKE_SIGN_S)
		GetProcAddress(m_hBaseLibrary, "DSTU4145CoupleMakeSignS");
	pBaseEx->DSTU4145CoupleMakeCommonSignS =
		(PDSTU4145_COUPLE_MAKE_COMMON_SIGN_S)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145CoupleMakeCommonSignS");
	pBaseEx->DSTU4145CoupleMakeCommonSign =
		(PDSTU4145_COUPLE_MAKE_COMMON_SIGN)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145CoupleMakeCommonSign");
#else //PC_STATIC_LIBS
	pBaseEx->DSTU4145CoupleSelfTest = DSTU4145CoupleSelfTest;
	pBaseEx->DSTU4145CoupleMakeCommonKeyQ =
		DSTU4145CoupleMakeCommonKeyQ;
	pBaseEx->DSTU4145CoupleMakeSignR = DSTU4145CoupleMakeSignR;
	pBaseEx->DSTU4145CoupleMakeCommonSignR =
		DSTU4145CoupleMakeCommonSignR;
	pBaseEx->DSTU4145CoupleMakeSignS = DSTU4145CoupleMakeSignS;
	pBaseEx->DSTU4145CoupleMakeCommonSignS =
		DSTU4145CoupleMakeCommonSignS;
	pBaseEx->DSTU4145CoupleMakeCommonSign =
		DSTU4145CoupleMakeCommonSign;
#endif // PC_STATIC_LIBS
#else // CSP_DSTU4145_COUPLE
	pBaseEx->DSTU4145CoupleSelfTest = NULL;
	pBaseEx->DSTU4145CoupleMakeCommonKeyQ = NULL;
	pBaseEx->DSTU4145CoupleMakeSignR = NULL;
	pBaseEx->DSTU4145CoupleMakeCommonSignR = NULL;
	pBaseEx->DSTU4145CoupleMakeSignS = NULL;
	pBaseEx->DSTU4145CoupleMakeCommonSignS = NULL;
	pBaseEx->DSTU4145CoupleMakeCommonSign = NULL;
#endif // CSP_DSTU4145_COUPLE

#ifdef CSP_DSTU7624
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU7624SelfTest = (PDSTU7624_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU7624SelfTest");
	pBaseEx->DSTU7624AcquireState = (PDSTU7624_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624AcquireState");
	pBaseEx->DSTU7624ReleaseState = (PDSTU7624_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624ReleaseState");
	pBaseEx->DSTU7624SetStateParameters = (PDSTU7624_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU7624SetStateParameters");
	pBaseEx->DSTU7624GetStateParameters = (PDSTU7624_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU7624GetStateParameters");

	pBaseEx->DSTU7624EncryptDataECBMode = (PDSTU7624_ENCRYPT_DATA_ECB_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataECBMode");
	pBaseEx->DSTU7624DecryptDataECBMode = (PDSTU7624_DECRYPT_DATA_ECB_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataECBMode");
	pBaseEx->DSTU7624EncryptDataCTRMode = (PDSTU7624_ENCRYPT_DATA_CTR_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataCTRMode");
	pBaseEx->DSTU7624DecryptDataCTRMode = (PDSTU7624_DECRYPT_DATA_CTR_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataCTRMode");
	pBaseEx->DSTU7624EncryptDataCFBMode = (PDSTU7624_ENCRYPT_DATA_CFB_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataCFBMode");
	pBaseEx->DSTU7624DecryptDataCFBMode = (PDSTU7624_DECRYPT_DATA_CFB_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataCFBMode");
	pBaseEx->DSTU7624GetDataCMAC = (PDSTU7624_GET_DATA_CMAC)
		GetProcAddress(m_hBaseLibrary, "DSTU7624GetDataCMAC");
	pBaseEx->DSTU7624CheckDataCMAC = (PDSTU7624_CHECK_DATA_CMAC)
		GetProcAddress(m_hBaseLibrary, "DSTU7624CheckDataCMAC");
	pBaseEx->DSTU7624EncryptDataCBCMode = (PDSTU7624_ENCRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataCBCMode");
	pBaseEx->DSTU7624DecryptDataCBCMode = (PDSTU7624_DECRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataCBCMode");
	pBaseEx->DSTU7624EncryptDataOFBMode = (PDSTU7624_ENCRYPT_DATA_OFB_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataOFBMode");
	pBaseEx->DSTU7624DecryptDataOFBMode = (PDSTU7624_DECRYPT_DATA_OFB_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataOFBMode");
	pBaseEx->DSTU7624EncryptDataGCMMode = (PDSTU7624_ENCRYPT_DATA_GCM_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataGCMMode");
	pBaseEx->DSTU7624DecryptDataGCMMode = (PDSTU7624_DECRYPT_DATA_GCM_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataGCMMode");
	pBaseEx->DSTU7624GetDataGMAC = (PDSTU7624_GET_DATA_GMAC)
		GetProcAddress(m_hBaseLibrary, "DSTU7624GetDataGMAC");
	pBaseEx->DSTU7624CheckDataGMAC = (PDSTU7624_CHECK_DATA_GMAC)
		GetProcAddress(m_hBaseLibrary, "DSTU7624CheckDataGMAC");
	pBaseEx->DSTU7624EncryptDataCCMMode = (PDSTU7624_ENCRYPT_DATA_CCM_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataCCMMode");
	pBaseEx->DSTU7624DecryptDataCCMMode = (PDSTU7624_DECRYPT_DATA_CCM_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataCCMMode");
	pBaseEx->DSTU7624EncryptDataXTSMode = (PDSTU7624_ENCRYPT_DATA_XTS_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataXTSMode");
	pBaseEx->DSTU7624DecryptDataXTSMode = (PDSTU7624_DECRYPT_DATA_XTS_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataXTSMode");
	pBaseEx->DSTU7624EncryptDataKWMode = (PDSTU7624_ENCRYPT_DATA_KW_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624EncryptDataKWMode");
	pBaseEx->DSTU7624DecryptDataKWMode = (PDSTU7624_DECRYPT_DATA_KW_MODE)
		GetProcAddress(m_hBaseLibrary, "DSTU7624DecryptDataKWMode");

#else //PC_STATIC_LIBS
	pBaseEx->DSTU7624SelfTest = DSTU7624SelfTest;
	pBaseEx->DSTU7624AcquireState = DSTU7624AcquireState;
	pBaseEx->DSTU7624ReleaseState = DSTU7624ReleaseState;
	pBaseEx->DSTU7624SetStateParameters = DSTU7624SetStateParameters;
	pBaseEx->DSTU7624GetStateParameters = DSTU7624GetStateParameters;

	pBaseEx->DSTU7624EncryptDataECBMode = DSTU7624EncryptDataECBMode;
	pBaseEx->DSTU7624DecryptDataECBMode = DSTU7624DecryptDataECBMode;
	pBaseEx->DSTU7624EncryptDataCTRMode = DSTU7624EncryptDataCTRMode;
	pBaseEx->DSTU7624DecryptDataCTRMode = DSTU7624DecryptDataCTRMode;
	pBaseEx->DSTU7624EncryptDataCFBMode = DSTU7624EncryptDataCFBMode;
	pBaseEx->DSTU7624DecryptDataCFBMode = DSTU7624DecryptDataCFBMode;
	pBaseEx->DSTU7624GetDataCMAC = DSTU7624GetDataCMAC;
	pBaseEx->DSTU7624CheckDataCMAC = DSTU7624CheckDataCMAC;
	pBaseEx->DSTU7624EncryptDataCBCMode = DSTU7624EncryptDataCBCMode;
	pBaseEx->DSTU7624DecryptDataCBCMode = DSTU7624DecryptDataCBCMode;
	pBaseEx->DSTU7624EncryptDataOFBMode = DSTU7624EncryptDataOFBMode;
	pBaseEx->DSTU7624DecryptDataOFBMode = DSTU7624DecryptDataOFBMode;
	pBaseEx->DSTU7624EncryptDataGCMMode = DSTU7624EncryptDataGCMMode;
	pBaseEx->DSTU7624DecryptDataGCMMode = DSTU7624DecryptDataGCMMode;
	pBaseEx->DSTU7624GetDataGMAC = DSTU7624GetDataGMAC;
	pBaseEx->DSTU7624CheckDataGMAC = DSTU7624CheckDataGMAC;
	pBaseEx->DSTU7624EncryptDataCCMMode = DSTU7624EncryptDataCCMMode;
	pBaseEx->DSTU7624DecryptDataCCMMode = DSTU7624DecryptDataCCMMode;
	pBaseEx->DSTU7624EncryptDataXTSMode = DSTU7624EncryptDataXTSMode;
	pBaseEx->DSTU7624DecryptDataXTSMode = DSTU7624DecryptDataXTSMode;
	pBaseEx->DSTU7624EncryptDataKWMode = DSTU7624EncryptDataKWMode;
	pBaseEx->DSTU7624DecryptDataKWMode = DSTU7624DecryptDataKWMode;

#endif // PC_STATIC_LIBS
#else // CSP_DSTU7624
	pBaseEx->DSTU7624SelfTest = NULL;
	pBaseEx->DSTU7624AcquireState = NULL;
	pBaseEx->DSTU7624ReleaseState = NULL;
	pBaseEx->DSTU7624SetStateParameters = NULL;
	pBaseEx->DSTU7624GetStateParameters = NULL;

	pBaseEx->DSTU7624EncryptDataECBMode = NULL;
	pBaseEx->DSTU7624DecryptDataECBMode = NULL;
	pBaseEx->DSTU7624EncryptDataCTRMode = NULL;
	pBaseEx->DSTU7624DecryptDataCTRMode = NULL;
	pBaseEx->DSTU7624EncryptDataCFBMode = NULL;
	pBaseEx->DSTU7624DecryptDataCFBMode = NULL;
	pBaseEx->DSTU7624GetDataCMAC = NULL;
	pBaseEx->DSTU7624CheckDataCMAC = NULL;
	pBaseEx->DSTU7624EncryptDataCBCMode = NULL;
	pBaseEx->DSTU7624DecryptDataCBCMode = NULL;
	pBaseEx->DSTU7624EncryptDataOFBMode = NULL;
	pBaseEx->DSTU7624DecryptDataOFBMode = NULL;
	pBaseEx->DSTU7624EncryptDataGCMMode = NULL;
	pBaseEx->DSTU7624DecryptDataGCMMode = NULL;
	pBaseEx->DSTU7624GetDataGMAC = NULL;
	pBaseEx->DSTU7624CheckDataGMAC = NULL;
	pBaseEx->DSTU7624EncryptDataCCMMode = NULL;
	pBaseEx->DSTU7624DecryptDataCCMMode = NULL;
	pBaseEx->DSTU7624EncryptDataXTSMode = NULL;
	pBaseEx->DSTU7624DecryptDataXTSMode = NULL;
	pBaseEx->DSTU7624EncryptDataKWMode = NULL;
	pBaseEx->DSTU7624DecryptDataKWMode = NULL;

#endif // CSP_DSTU7624

#ifdef CSP_DSTU7564
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU7564SelfTest = (PDSTU7564_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU7564SelfTest");
	pBaseEx->DSTU7564AcquireState = (PDSTU7564_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU7564AcquireState");
	pBaseEx->DSTU7564ReleaseState = (PDSTU7564_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU7564ReleaseState");
	pBaseEx->DSTU7564SetStateParameters = (PDSTU7564_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU7564SetStateParameters");
	pBaseEx->DSTU7564GetStateParameters = (PDSTU7564_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU7564GetStateParameters");

	pBaseEx->DSTU7564HashData = (PDSTU7564_HASH_DATA)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HashData");
	pBaseEx->DSTU7564FinalizeHash = (PDSTU7564_FINALIZE_HASH)
		GetProcAddress(m_hBaseLibrary, "DSTU7564FinalizeHash");

#else //PC_STATIC_LIBS
	pBaseEx->DSTU7564SelfTest = DSTU7564SelfTest;
	pBaseEx->DSTU7564AcquireState = DSTU7564AcquireState;
	pBaseEx->DSTU7564ReleaseState = DSTU7564ReleaseState;
	pBaseEx->DSTU7564SetStateParameters = DSTU7564SetStateParameters;
	pBaseEx->DSTU7564GetStateParameters = DSTU7564GetStateParameters;

	pBaseEx->DSTU7564HashData = DSTU7564HashData;
	pBaseEx->DSTU7564FinalizeHash = DSTU7564FinalizeHash;

#endif // PC_STATIC_LIBS
#else // CSP_DSTU7564
	pBaseEx->DSTU7564SelfTest = NULL;
	pBaseEx->DSTU7564AcquireState = NULL;
	pBaseEx->DSTU7564ReleaseState = NULL;
	pBaseEx->DSTU7564SetStateParameters = NULL;
	pBaseEx->DSTU7564GetStateParameters = NULL;

	pBaseEx->DSTU7564HashData = NULL;
	pBaseEx->DSTU7564FinalizeHash = NULL;
#endif // CSP_DSTU7564

#ifdef CSP_DSTU8845
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU8845SelfTest = (PDSTU8845_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU8845SelfTest");
	pBaseEx->DSTU8845AcquireState = (PDSTU8845_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU8845AcquireState");
	pBaseEx->DSTU8845ReleaseState = (PDSTU8845_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU8845ReleaseState");
	pBaseEx->DSTU8845SetStateParameters = (PDSTU8845_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU8845SetStateParameters");
	pBaseEx->DSTU8845GetStateParameters = (PDSTU8845_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU8845GetStateParameters");

	pBaseEx->DSTU8845EncryptData = (PDSTU8845_ENCRYPT_DATA)
		GetProcAddress(m_hBaseLibrary, "DSTU8845EncryptData");

#else //PC_STATIC_LIBS
	pBaseEx->DSTU8845SelfTest = DSTU8845SelfTest;
	pBaseEx->DSTU8845AcquireState = DSTU8845AcquireState;
	pBaseEx->DSTU8845ReleaseState = DSTU8845ReleaseState;
	pBaseEx->DSTU8845SetStateParameters = DSTU8845SetStateParameters;
	pBaseEx->DSTU8845GetStateParameters = DSTU8845GetStateParameters;

	pBaseEx->DSTU8845EncryptData = DSTU8845EncryptData;

#endif // PC_STATIC_LIBS
#else // CSP_DSTU8845
	pBaseEx->DSTU8845SelfTest = NULL;
	pBaseEx->DSTU8845AcquireState = NULL;
	pBaseEx->DSTU8845ReleaseState = NULL;
	pBaseEx->DSTU8845SetStateParameters = NULL;
	pBaseEx->DSTU8845GetStateParameters = NULL;

	pBaseEx->DSTU8845EncryptData = NULL;

#endif // CSP_DSTU8845

#ifdef CSP_KDF_DSTU7564
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU7564HMACSelfTest = (PDSTU7564_HMAC_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACSelfTest");
	pBaseEx->DSTU7564HMACAcquireState = (PDSTU7564_HMAC_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACAcquireState");
	pBaseEx->DSTU7564HMACReleaseState = (PDSTU7564_HMAC_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACReleaseState");
	pBaseEx->DSTU7564HMACSetStateParameters =
		(PDSTU7564_HMAC_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACSetStateParameters");
	pBaseEx->DSTU7564HMACGetStateParameters =
		(PDSTU7564_HMAC_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACGetStateParameters");

	pBaseEx->DSTU7564HMACUpdateData = (PDSTU7564_HMAC_UPDATE_DATA)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACUpdateData");
	pBaseEx->DSTU7564HMACFinalizeDataMac =
		(PDSTU7564_HMAC_FINALIZE_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "DSTU7564HMACFinalizeDataMac");

	pBaseEx->PKCS5PBKDF2DSTU7564SelfTest =
		(PPKCS5_PBKDF2_DSTU7564_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "PKCS5PBKDF2DSTU7564SelfTest");
	pBaseEx->PKCS5PBKDF2DSTU7564DeriveKey =
		(PPKCS5_PBKDF2_DSTU7564_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PKCS5PBKDF2DSTU7564DeriveKey");

	pBaseEx->PKCS12PBKDFDSTU7564SelfTest =
		(PPKCS12_PBKDF_DSTU7564_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFDSTU7564SelfTest");
	pBaseEx->PKCS12PBKDFDSTU7564DeriveKey =
		(PPKCS12_PBKDF_DSTU7564_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFDSTU7564DeriveKey");

#else
	pBaseEx->DSTU7564HMACSelfTest = DSTU7564HMACSelfTest;
	pBaseEx->DSTU7564HMACAcquireState = DSTU7564HMACAcquireState;
	pBaseEx->DSTU7564HMACReleaseState = DSTU7564HMACReleaseState;
	pBaseEx->DSTU7564HMACSetStateParameters =
		DSTU7564HMACSetStateParameters;
	pBaseEx->DSTU7564HMACGetStateParameters =
		DSTU7564HMACGetStateParameters;

	pBaseEx->DSTU7564HMACUpdateData = DSTU7564HMACUpdateData;
	pBaseEx->DSTU7564HMACFinalizeDataMac = DSTU7564HMACFinalizeDataMac;

	pBaseEx->PKCS5PBKDF2DSTU7564SelfTest = PKCS5PBKDF2DSTU7564SelfTest;
	pBaseEx->PKCS5PBKDF2DSTU7564DeriveKey = PKCS5PBKDF2DSTU7564DeriveKey;

	pBaseEx->PKCS12PBKDFDSTU7564SelfTest = PKCS12PBKDFDSTU7564SelfTest;
	pBaseEx->PKCS12PBKDFDSTU7564DeriveKey = PKCS12PBKDFDSTU7564DeriveKey;

#endif // PC_STATIC_LIBS
#else // CSP_KDF_DSTU7564
	pBaseEx->DSTU7564HMACSelfTest = NULL;
	pBaseEx->DSTU7564HMACAcquireState = NULL;
	pBaseEx->DSTU7564HMACReleaseState = NULL;
	pBaseEx->DSTU7564HMACSetStateParameters = NULL;
	pBaseEx->DSTU7564HMACGetStateParameters = NULL;

	pBaseEx->DSTU7564HMACUpdateData = NULL;
	pBaseEx->DSTU7564HMACFinalizeDataMac = NULL;

	pBaseEx->PKCS5PBKDF2DSTU7564SelfTest = NULL;
	pBaseEx->PKCS5PBKDF2DSTU7564DeriveKey = NULL;

	pBaseEx->PKCS12PBKDFDSTU7564SelfTest = NULL;
	pBaseEx->PKCS12PBKDFDSTU7564DeriveKey = NULL;

#endif // CSP_KDF_DSTU7564

#ifdef CSP_DSTU7624_WRAP
#ifndef PC_STATIC_LIBS
	pBaseEx->ECDHDSTUSelfTest = (PECDH_DSTU_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "ECDHDSTUSelfTest");
	pBaseEx->ECDHKDFDSTU7564CalculateSharedKey =
		(PECDH_KDF_DSTU7564_CALCULATE_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary,
			"ECDHKDFDSTU7564CalculateSharedKey");
	pBaseEx->DSTU7624WrapSharedKey = (PDSTU7624_WRAP_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary, "DSTU7624WrapSharedKey");
	pBaseEx->DSTU7624UnwrapSharedKey = (PDSTU7624_UNWRAP_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary, "DSTU7624UnwrapSharedKey");

#else // PC_STATIC_LIBS
	pBaseEx->ECDHDSTUSelfTest = ECDHDSTUSelfTest;
	pBaseEx->ECDHKDFDSTU7564CalculateSharedKey =
		ECDHKDFDSTU7564CalculateSharedKey;
	pBaseEx->DSTU7624WrapSharedKey = DSTU7624WrapSharedKey;
	pBaseEx->DSTU7624UnwrapSharedKey = DSTU7624UnwrapSharedKey;

#endif // PC_STATIC_LIBS
#else // CSP_DSTU7624_WRAP
	pBaseEx->ECDHDSTUSelfTest = NULL;
	pBaseEx->ECDHKDFDSTU7564CalculateSharedKey = NULL;
	pBaseEx->DSTU7624WrapSharedKey = NULL;
	pBaseEx->DSTU7624UnwrapSharedKey = NULL;

#endif // CSP_DSTU7624_WRAP

#ifdef CSP_MULTI_ALGO_PRNG
#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU4145PseudoRNGAcquireState =
		(PDSTU4145_PSEUDO_RNG_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary,
			"DSTU4145PseudoRNGAcquireState");
	pBaseEx->DSTU4145PseudoRNGLockState =
		(PDSTU4145_PSEUDO_RNG_LOCK_STATE)
		GetProcAddress(m_hBaseLibrary,
			"DSTU4145PseudoRNGLockState");
	pBaseEx->DSTU4145PseudoRNGUnlockState =
		(PDSTU4145_PSEUDO_RNG_UNLOCK_STATE)
		GetProcAddress(m_hBaseLibrary,
			"DSTU4145PseudoRNGUnlockState");
	pBaseEx->DSTU4145PseudoRNGSetStateParameters =
		(PDSTU4145_PSEUDO_RNG_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary,
			"DSTU4145PseudoRNGSetStateParameters");

#else // PC_STATIC_LIBS
	pBaseEx->DSTU4145PseudoRNGAcquireState =
		DSTU4145PseudoRNGAcquireState;
	pBaseEx->DSTU4145PseudoRNGLockState =
		DSTU4145PseudoRNGLockState;
	pBaseEx->DSTU4145PseudoRNGUnlockState =
		DSTU4145PseudoRNGUnlockState;
	pBaseEx->DSTU4145PseudoRNGSetStateParameters =
		DSTU4145PseudoRNGSetStateParameters;

#endif // PC_STATIC_LIBS
#else // CSP_MULTI_ALGO_PRNG
	pBaseEx->DSTU4145PseudoRNGAcquireState = NULL;
	pBaseEx->DSTU4145PseudoRNGLockState = NULL;
	pBaseEx->DSTU4145PseudoRNGUnlockState = NULL;
	pBaseEx->DSTU4145PseudoRNGSetStateParameters = NULL;

#endif // CSP_MULTI_ALGO_PRNG

#ifndef PC_STATIC_LIBS
	pBaseEx->DSTU4145IsDenseNumbersSupported =
		(PDSTU4145_IS_DENSE_NUMBERS_SUPPORTED)
		GetProcAddress(m_hBaseLibrary,
			"DSTU4145IsDenseNumbersSupported");
	pBaseEx->ECDHKDFDSTU7564CalculateDenseSharedKey =
		(PECDH_KDF_DSTU7564_CALCULATE_DENSE_SHARED_KEY)
		GetProcAddress(m_hBaseLibrary,
			"ECDHKDFDSTU7564CalculateDenseSharedKey");

#else // PC_STATIC_LIBS
	pBaseEx->DSTU4145IsDenseNumbersSupported =
		DSTU4145IsDenseNumbersSupported;
	pBaseEx->ECDHKDFDSTU7564CalculateDenseSharedKey =
		ECDHKDFDSTU7564CalculateDenseSharedKey;

#endif // PC_STATIC_LIBS

	*ppBaseEx = pBaseEx;

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

VOID WINAPI CSPBase::Unload()
{
	PCSP_FINALIZE pCSPFinalize;

#ifndef PC_STATIC_LIBS
	if(m_hBaseLibrary != NULL)
	{
		pCSPFinalize = (PCSP_FINALIZE)
			GetProcAddress(m_hBaseLibrary, "CSPFinalize");

		if(pCSPFinalize != NULL)
			pCSPFinalize();

		FreeLibrary(m_hBaseLibrary);
		m_hBaseLibrary = NULL;
	}

	if(m_hExtensionLibrary != NULL)
	{
		FreeLibrary(m_hExtensionLibrary);
		m_hExtensionLibrary = NULL;
	}
#else // PC_STATIC_LIBS
	pCSPFinalize = CSPFinalize;

	pCSPFinalize();
#endif // PC_STATIC_LIBS
}

//----------------------------------------------------------------------------------------------------------------------

VOID WINAPI CSPBase::UnloadEx(
	PCSP_BASE_FUNCTIONS_EX *ppBaseEx)
{
	if(ppBaseEx == NULL || *ppBaseEx == NULL)
		return;

	delete *ppBaseEx;
	*ppBaseEx = NULL;
}

//======================================================================================================================
