//==============================================================================

#include "CSPIBase.h"

//==============================================================================

#ifdef OS_MAC
#define CSPI_BASE_LIBRARY_NAME "cspib.dylib"
#define CSP_EXTENSION_LIBRARY_NAME "cspe.dylib"
#elif defined (ANDROID_NDK)
#define CSPI_BASE_LIBRARY_NAME "libcspib.so"
#define CSP_EXTENSION_LIBRARY_NAME "libcspe.so"
#elif defined (OS_NIX)
#define CSPI_BASE_LIBRARY_NAME "cspib.so"
#define CSP_EXTENSION_LIBRARY_NAME "cspe.so"
#else // OS_NIX
#ifdef PC_LIBS_IN_CURRENT
#define CSPI_BASE_LIBRARY_NAME L"CSPIBase.dll"
#define CSP_EXTENSION_LIBRARY_NAME L"CSPExtension.dll"
#else // PC_LIBS_IN_CURRENT
#define CSPI_BASE_LIBRARY_NAME "CSPIBase.dll"
#define CSP_EXTENSION_LIBRARY_NAME "CSPExtension.dll"
#endif // PC_LIBS_IN_CURRENT
#endif // OS_NIX

//==============================================================================

CSPIBase::CSPIBase()
{
#ifndef PC_STATIC_LIBS
	m_hBaseLibrary = NULL;
	m_hExtensionLibrary = NULL;
#endif // PC_STATIC_LIBS
}

//------------------------------------------------------------------------------

CSPIBase::~CSPIBase()
{
#ifndef PC_STATIC_LIBS
	if(m_hBaseLibrary != NULL)
		FreeLibrary(m_hBaseLibrary);

	if(m_hExtensionLibrary != NULL)
		FreeLibrary(m_hExtensionLibrary);
#endif // PC_STATIC_LIBS
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIBase::Load()
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

	wcscat(szLibraryFile, CSPI_BASE_LIBRARY_NAME);

	m_hBaseLibrary = LoadLibraryW(szLibraryFile);
#else // OS_NIX
	CHAR szLibraryFile[MAX_PATH * 4];

	GetCurrentDirectory(MAX_PATH * 4, szLibraryFile);

	if(szLibraryFile[strlen(szLibraryFile) - 1] != '\\')
		strcat(szLibraryFile, "\\");

	strcat(szLibraryFile, CSPI_BASE_LIBRARY_NAME);

	m_hBaseLibrary = LoadLibraryA(szLibraryFile);
#endif // OS_NIX
#else // PC_LIBS_IN_CURRENT
	m_hBaseLibrary = LoadLibraryA(CSPI_BASE_LIBRARY_NAME);
#endif // PC_LIBS_IN_CURRENT
	if(!m_hBaseLibrary)
	{
		return FALSE;
	}

	F.DSTU4145PseudoRNGSelfTest = (PDSTU4145_PSEUDO_RNG_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGSelfTest");
	F.DSTU4145PseudoRNGInitialize = (PDSTU4145_PSEUDO_RNG_INITIALIZE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGInitialize");
	F.DSTU4145PseudoRNGDeinitialize = (PDSTU4145_PSEUDO_RNG_DEINITIALIZE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGDeinitialize");
	F.DSTU4145PseudoRNGGenerateSequence = (PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGGenerateSequence");
	F.DSTU4145PseudoRNGGenerateSequenceInBits = (PDSTU4145_PSEUDO_RNG_GENERATE_SEQUENCE_INBITS)
		GetProcAddress(m_hBaseLibrary, "DSTU4145PseudoRNGGenerateSequenceInBits");

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

	F.RSASelfTest = (PRSA_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "RSASelfTest");
	F.RSAAcquireState = (PRSA_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "RSAAcquireState");
	F.RSAReleaseState = (PRSA_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "RSAReleaseState");
	F.RSASetStateParameters = (PRSA_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "RSASetStateParameters");
	F.RSAGetStateParameters = (PRSA_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "RSAGetStateParameters");
	F.RSAGenerateParameters = (PRSA_GENERATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "RSAGenerateParameters");
	F.RSASignHash = (PRSA_SIGN_HASH)
		GetProcAddress(m_hBaseLibrary, "RSASignHash");
	F.RSAVerifySignature = (PRSA_VERIFY_SIGNATURE)
		GetProcAddress(m_hBaseLibrary, "RSAVerifySignature");
	F.RSAEncryptData = (PRSA_ENCRYPT_DATA)
		GetProcAddress(m_hBaseLibrary, "RSAEncryptData");
	F.RSADecryptData = (PRSA_DECRYPT_DATA)
		GetProcAddress(m_hBaseLibrary, "RSADecryptData");

	F.SHASelfTest = (PSHA_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "SHASelfTest");
	F.SHAAcquireState = (PSHA_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "SHAAcquireState");
	F.SHAReleaseState = (PSHA_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "SHAReleaseState");
	F.SHASetStateParameters = (PSHA_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "SHASetStateParameters");
	F.SHAGetStateParameters = (PSHA_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "SHAGetStateParameters");
	F.SHAHashData = (PSHA_HASH_DATA)
		GetProcAddress(m_hBaseLibrary, "SHAHashData");
	F.SHAFinalizeHash = (PSHA_FINALIZE_HASH)
		GetProcAddress(m_hBaseLibrary, "SHAFinalizeHash");

	F.DSAAcquireState = (PDSA_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSAAcquireState");
	F.DSAReleaseState = (PDSA_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "DSAReleaseState");
	F.DSASetStateParameters = (PDSA_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSASetStateParameters");
	F.DSAGetStateParameters = (PDSA_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSAGetStateParameters");
	F.DSAGenerateParameters = (PDSA_GENERATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "DSAGenerateParameters");
	F.DSASignHash = (PDSA_SIGN_HASH)
		GetProcAddress(m_hBaseLibrary, "DSASignHash");
	F.DSAVerifySignature = (PDSA_VERIFY_SIGNATURE)
		GetProcAddress(m_hBaseLibrary, "DSAVerifySignature");
	F.DSASelfTest = (PDSA_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DSASelfTest");

	F.TDEASelfTest = (PTDEA_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "TDEASelfTest");
	F.TDEAAcquireState = (PTDEA_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "TDEAAcquireState");
	F.TDEAReleaseState = (PTDEA_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "TDEAReleaseState");
	F.TDEASetStateParameters = (PTDEA_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "TDEASetStateParameters");
	F.TDEAGetStateParameters = (PTDEA_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "TDEAGetStateParameters");
	F.TDEAEncryptDataSSMode = (PTDEA_ENCRYPT_DATA_SS_MODE)
		GetProcAddress(m_hBaseLibrary, "TDEAEncryptDataSSMode");
	F.TDEADecryptDataSSMode = (PTDEA_DECRYPT_DATA_SS_MODE)
		GetProcAddress(m_hBaseLibrary, "TDEADecryptDataSSMode");
	F.TDEAEncryptDataCBCMode = (PTDEA_ENCRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "TDEAEncryptDataCBCMode");
	F.TDEADecryptDataCBCMode = (PTDEA_DECRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "TDEADecryptDataCBCMode");
	F.TDEAGetDataMAC = (PTDEA_GET_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "TDEAGetDataMAC");

	F.ECDSASelfTest = (PECDSA_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "ECDSASelfTest");
	F.ECDSAAcquireState = (PECDSA_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "ECDSAAcquireState");
	F.ECDSAReleaseState = (PECDSA_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "ECDSAReleaseState");
	F.ECDSASetStateParameters = (PECDSASET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "ECDSASetStateParameters");
	F.ECDSAGenerateParameters = (PECDSA_GENERATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "ECDSAGenerateParameters");
	F.ECDSASignHash = (PECDSA_SIGN_HASH)
		GetProcAddress(m_hBaseLibrary, "ECDSASignHash");
	F.ECDSAVerifySignature = (PECDSA_VERIFY_SIGNATURE)
		GetProcAddress(m_hBaseLibrary, "ECDSAVerifySignature");
	F.ECDSAGetStateParameters = (PECDSAGET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "ECDSAGetStateParameters");
	F.ECDSATestOnStandartParameters = (PECDSA_TEST_ON_STANDART_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "ECDSATestOnStandartParameters");

	F.GOSTR3410SelfTest = (PGOSTR3410_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410SelfTest");
	F.GOSTR3410AcquireState = (PGOSTR3410_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410AcquireState");
	F.GOSTR3410ReleaseState = (PGOSTR3410_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410ReleaseState");
	F.GOSTR3410SetStateParameters = (PGOSTR3410SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410SetStateParameters");
	F.GOSTR3410GetStateParameters = (PGOSTR3410GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410GetStateParameters");
	F.GOSTR3410GenerateParameters = (PGOSTR3410_GENERATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410GenerateParameters");
	F.GOSTR3410SignHash = (PGOSTR3410_SIGN_HASH)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410SignHash");
	F.GOSTR3410VerifySignature = (PGOSTR3410_VERIFY_SIGNATURE)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410VerifySignature");
	F.GOSTR3410TestOnStandartParameters = (PGOSTR3410_TEST_ON_STANDART_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "GOSTR3410TestOnStandartParameters");

	F.AESSelfTest = (PAES_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "AESSelfTest");
	F.AESAcquireState = (PAES_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "AESAcquireState");
	F.AESSetStateParameters = (PAES_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "AESSetStateParameters");
	F.AESReleaseState = (PAES_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "AESReleaseState");
	F.AESEncryptDataECBMode = (PAES_ENCRYPT_DATA_ECB_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEncryptDataECBMode");
	F.AESDecryptDataECBMode = (PAES_DECRYPT_DATA_ECB_MODE)
		GetProcAddress(m_hBaseLibrary, "AESDecryptDataECBMode");
	F.AESEncryptDataCBCMode = (PAES_ENCRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEncryptDataCBCMode");
	F.AESDecryptDataCBCMode = (PAES_DECRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "AESDecryptDataCBCMode");
	F.AESEncryptDataCFB1Mode = (PAES_ENCRYPT_DATA_CFB1_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEncryptDataCFB1Mode");
	F.AESDecryptDataCFB1Mode = (PAES_DECRYPT_DATA_CFB1_MODE)
		GetProcAddress(m_hBaseLibrary, "AESDecryptDataCFB1Mode");
	F.AESEncryptDataCFB8Mode = (PAES_ENCRYPT_DATA_CFB8_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEncryptDataCFB8Mode");
	F.AESDecryptDataCFB8Mode = (PAES_DECRYPT_DATA_CFB8_MODE)
		GetProcAddress(m_hBaseLibrary, "AESDecryptDataCFB8Mode");
	F.AESEncryptDataCFB128Mode = (PAES_ENCRYPT_DATA_CFB128_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEncryptDataCFB128Mode");
	F.AESDecryptDataCFB128Mode = (PAES_DECRYPT_DATA_CFB128_MODE)
		GetProcAddress(m_hBaseLibrary, "AESDecryptDataCFB128Mode");
	F.AESEnDecryptDataOFBMode = (PAES_ENDECRYPT_DATA_OFB_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEnDecryptDataOFBMode");
	F.AESEnDecryptDataCTRMode = (PAES_ENDECRYPT_DATA_CTR_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEnDecryptDataCTRMode");
	F.AESGetDataMAC = (PAES_GET_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "AESGetDataMAC");
	F.AESExpandKey = (PAES_EXPAND_KEY)
		GetProcAddress(m_hBaseLibrary, "AESExpandKey");
	F.AESCipher = (PAES_CIPHER) GetProcAddress(m_hBaseLibrary, "AESCipher");
	F.AESInverseCipher = (PAES_INVERSE_CIPHER)
		GetProcAddress(m_hBaseLibrary, "AESInverseCipher");

	F.DHSelfTest = (PDH_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "DHSelfTest");
	F.DHCalculateSharedSecret = (PDH_CALCULATE_SHARED_SECRET)
		GetProcAddress(m_hBaseLibrary, "DHCalculateSharedSecret");

	F.ECDHSelfTest = (PECDH_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "ECDHSelfTest");
	F.ECDHCalculateSharedSecret = (PECDH_CALCULATE_SHARED_SECRET)
		GetProcAddress(m_hBaseLibrary, "ECDHCalculateSharedSecret");

	for(DWORD dw = 0; dw < sizeof(CSPI_BASE_FUNCTIONS) / sizeof(PVOID); dw++)
	{
		if(((PVOID *) &F)[dw] == NULL)
		{
			FreeLibrary(m_hBaseLibrary);
			m_hBaseLibrary = NULL;
			return FALSE;
		}
	}

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

	for(DWORD dw = 0; dw < sizeof(CSP_EXTENSION_FUNCTIONS) /
		sizeof(PVOID); dw++)
	{
		if(((PVOID *) &ExtensionF)[dw] == NULL)
		{
			FreeLibrary(m_hBaseLibrary);
			m_hBaseLibrary = NULL;
			FreeLibrary(m_hExtensionLibrary);
			m_hExtensionLibrary = NULL;
			return FALSE;
		}
	}
#else // PC_STATIC_LIBS
	
	CSPIInitialize();

	F.DSTU4145PseudoRNGSelfTest = APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGSelfTest);
	F.DSTU4145PseudoRNGInitialize = APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGInitialize);
	F.DSTU4145PseudoRNGDeinitialize = APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGDeinitialize);
	F.DSTU4145PseudoRNGGenerateSequence = APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGGenerateSequence);
	F.DSTU4145PseudoRNGGenerateSequenceInBits = APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGGenerateSequenceInBits);
	
	F.GOST28147SelfTest = APPEND_LIBRARY_PREFIX(GOST28147SelfTest);
	F.GOST28147AcquireState = APPEND_LIBRARY_PREFIX(GOST28147AcquireState);
	F.GOST28147ReleaseState = APPEND_LIBRARY_PREFIX(GOST28147ReleaseState);
	F.GOST28147SetStateParameters = APPEND_LIBRARY_PREFIX(GOST28147SetStateParameters);
	F.GOST28147GetStateParameters = APPEND_LIBRARY_PREFIX(GOST28147GetStateParameters);
	F.GOST28147EncryptDataSSMode = APPEND_LIBRARY_PREFIX(GOST28147EncryptDataSSMode);
	F.GOST28147DecryptDataSSMode = APPEND_LIBRARY_PREFIX(GOST28147DecryptDataSSMode);
	F.GOST28147EncryptDataGMode = APPEND_LIBRARY_PREFIX(GOST28147EncryptDataGMode);
	F.GOST28147EncryptDataGOFBMode = APPEND_LIBRARY_PREFIX(GOST28147EncryptDataGOFBMode);
	F.GOST28147DecryptDataGOFBMode = APPEND_LIBRARY_PREFIX(GOST28147DecryptDataGOFBMode);
	F.GOST28147GetDataMAC = APPEND_LIBRARY_PREFIX(GOST28147GetDataMAC);
	
	F.GOST34311SelfTest = APPEND_LIBRARY_PREFIX(GOST34311SelfTest);
	F.GOST34311AcquireState = APPEND_LIBRARY_PREFIX(GOST34311AcquireState);
	F.GOST34311ReleaseState = APPEND_LIBRARY_PREFIX(GOST34311ReleaseState);
	F.GOST34311SetStateParameters = APPEND_LIBRARY_PREFIX(GOST34311SetStateParameters);
	F.GOST34311GetStateParameters = APPEND_LIBRARY_PREFIX(GOST34311GetStateParameters);
	F.GOST34311HashData = APPEND_LIBRARY_PREFIX(GOST34311HashData);
	F.GOST34311FinalizeHash = APPEND_LIBRARY_PREFIX(GOST34311FinalizeHash);
	
	F.RSASelfTest = RSASelfTest;
	F.RSAAcquireState = RSAAcquireState;
	F.RSAReleaseState = RSAReleaseState;
	F.RSASetStateParameters = RSASetStateParameters;
	F.RSAGetStateParameters = RSAGetStateParameters;
	F.RSAGenerateParameters = RSAGenerateParameters;
	F.RSASignHash = RSASignHash;
	F.RSAVerifySignature = RSAVerifySignature;
	F.RSAEncryptData = RSAEncryptData;
	F.RSADecryptData = RSADecryptData;
	
	F.SHASelfTest = SHASelfTest;
	F.SHAAcquireState = SHAAcquireState;
	F.SHAReleaseState = SHAReleaseState;
	F.SHASetStateParameters = SHASetStateParameters;
	F.SHAGetStateParameters = SHAGetStateParameters;
	F.SHAHashData = SHAHashData;
	F.SHAFinalizeHash = SHAFinalizeHash;
	
	F.DSAAcquireState = DSAAcquireState;
	F.DSAReleaseState = DSAReleaseState;
	F.DSASetStateParameters = DSASetStateParameters;
	F.DSAGetStateParameters = DSAGetStateParameters;
	F.DSAGenerateParameters = DSAGenerateParameters;
	F.DSASignHash = DSASignHash;
	F.DSAVerifySignature = DSAVerifySignature;
	F.DSASelfTest = DSASelfTest;
	
	F.TDEASelfTest = TDEASelfTest;
	F.TDEAAcquireState = TDEAAcquireState;
	F.TDEAReleaseState = TDEAReleaseState;
	F.TDEASetStateParameters = TDEASetStateParameters;
	F.TDEAGetStateParameters = TDEAGetStateParameters;
	F.TDEAEncryptDataSSMode = TDEAEncryptDataSSMode;
	F.TDEADecryptDataSSMode = TDEADecryptDataSSMode;
	F.TDEAEncryptDataCBCMode = TDEAEncryptDataCBCMode;
	F.TDEADecryptDataCBCMode = TDEADecryptDataCBCMode;
	F.TDEAGetDataMAC = TDEAGetDataMAC;
	
	F.ECDSASelfTest = ECDSASelfTest;
	F.ECDSAAcquireState = ECDSAAcquireState;
	F.ECDSAReleaseState = ECDSAReleaseState;
	F.ECDSASetStateParameters = ECDSASetStateParameters;
	F.ECDSAGenerateParameters = ECDSAGenerateParameters;
	F.ECDSASignHash = ECDSASignHash;
	F.ECDSAVerifySignature = ECDSAVerifySignature;
	F.ECDSAGetStateParameters = ECDSAGetStateParameters;
	F.ECDSATestOnStandartParameters = ECDSATestOnStandartParameters;
	
	F.GOSTR3410SelfTest = GOSTR3410SelfTest;
	F.GOSTR3410AcquireState = GOSTR3410AcquireState;
	F.GOSTR3410ReleaseState = GOSTR3410ReleaseState;
	F.GOSTR3410SetStateParameters = GOSTR3410SetStateParameters;
	F.GOSTR3410GetStateParameters = GOSTR3410GetStateParameters;
	F.GOSTR3410GenerateParameters = GOSTR3410GenerateParameters;
	F.GOSTR3410SignHash = GOSTR3410SignHash;
	F.GOSTR3410VerifySignature = GOSTR3410VerifySignature;
	F.GOSTR3410TestOnStandartParameters = GOSTR3410TestOnStandartParameters;
	
	F.AESSelfTest = AESSelfTest;
	F.AESAcquireState = AESAcquireState;
	F.AESSetStateParameters = AESSetStateParameters;
	F.AESReleaseState = AESReleaseState;
	F.AESEncryptDataECBMode = AESEncryptDataECBMode;
	F.AESDecryptDataECBMode = AESDecryptDataECBMode;
	F.AESEncryptDataCBCMode = AESEncryptDataCBCMode;
	F.AESDecryptDataCBCMode = AESDecryptDataCBCMode;
	F.AESEncryptDataCFB1Mode = AESEncryptDataCFB1Mode;
	F.AESDecryptDataCFB1Mode = AESDecryptDataCFB1Mode;
	F.AESEncryptDataCFB8Mode = AESEncryptDataCFB8Mode;
	F.AESDecryptDataCFB8Mode = AESDecryptDataCFB8Mode;
	F.AESEncryptDataCFB128Mode = AESEncryptDataCFB128Mode;
	F.AESDecryptDataCFB128Mode = AESDecryptDataCFB128Mode;
	F.AESEnDecryptDataOFBMode = AESEnDecryptDataOFBMode;
	F.AESEnDecryptDataCTRMode = AESEnDecryptDataCTRMode;
	F.AESGetDataMAC = AESGetDataMAC;
	F.AESExpandKey = AESExpandKey;
	F.AESCipher = AESCipher;
	F.AESInverseCipher = AESInverseCipher;
	
	F.DHSelfTest = DHSelfTest;
	F.DHCalculateSharedSecret = DHCalculateSharedSecret;
	
	F.ECDHSelfTest = APPEND_LIBRARY_PREFIX(ECDHSelfTest);
	F.ECDHCalculateSharedSecret = ECDHCalculateSharedSecret;

#ifndef CSP_H
	ExtensionF.TSCGIsEnable = TSCGIsEnable;
	ExtensionF.TSCGGenerateSequence = TSCGGenerateSequence;
	
	ExtensionF.BSTestSequence = BSTestSequence;
	ExtensionF.BSReleaseStatistic = BSReleaseStatistic;

	ExtensionF.CRC32Count = CRC32Count;
#endif // CSP_H

#endif // PC_STATIC_LIBS
	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIBase::LoadEx(
	PCSPI_BASE_FUNCTIONS_EX *ppBaseEx)
{
	PCSPI_BASE_FUNCTIONS_EX pBaseEx;

	pBaseEx = new CSPI_BASE_FUNCTIONS_EX;
	if(pBaseEx == NULL)
		return FALSE;

	pBaseEx->nSize = 33;
	pBaseEx->nReserved = 0;

#ifdef CSPI_PKCS12
#ifndef PC_STATIC_LIBS
	if(!m_hBaseLibrary)
	{
		delete pBaseEx;

		return FALSE;
	}

	pBaseEx->SHA1HMACAcquireState = (PSHA1_HMAC_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACAcquireState");
	pBaseEx->SHA1HMACReleaseState = (PSHA1_HMAC_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACReleaseState");
	pBaseEx->SHA1HMACSetStateParameters = (PSHA1_HMAC_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACSetStateParameters");
	pBaseEx->SHA1HMACGetStateParameters = (PSHA1_HMAC_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACGetStateParameters");
	pBaseEx->SHA1HMACInitializeDataMac = (PSHA1_HMAC_INITIALIZE_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACInitializeDataMac");
	pBaseEx->SHA1HMACUpdateData = (PSHA1_HMAC_UPDATE_DATA)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACUpdateData");
	pBaseEx->SHA1HMACFinalizeDataMac = (PSHA1_HMAC_FINALIZE_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACFinalizeDataMac");
	pBaseEx->SHA1HMACSelfTest = (PSHA1_HMAC_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "SHA1HMACSelfTest");

	pBaseEx->RC2AcquireState = (PRC2_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "RC2AcquireState");
	pBaseEx->RC2ReleaseState = (PRC2_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "RC2ReleaseState");
	pBaseEx->RC2SetStateParameters = (PRC2_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "RC2SetStateParameters");
	pBaseEx->RC2GetStateParameters = (PRC2_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "RC2GetStateParameters");
	pBaseEx->RC2EncryptDataCBCMode = (PRC2_ENCRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "RC2EncryptDataCBCMode");
	pBaseEx->RC2DecryptDataCBCMode = (PRC2_DECRYPT_DATA_CBC_MODE)
		GetProcAddress(m_hBaseLibrary, "RC2DecryptDataCBCMode");
	pBaseEx->RC2SelfTest = (PRC2_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "RC2SelfTest");

	pBaseEx->PKCS12PBKDFRC2DeriveKey = (PPKCS12_PBKDF_RC2_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFRC2DeriveKey");
	pBaseEx->PKCS12PBKDFRC2DeriveIV = (PPKCS12_PBKDF_RC2_DERIVE_IV)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFRC2DeriveIV");
	pBaseEx->PKCS12PBKDFTDESDeriveKey = (PPKCS12_PBKDF_TDES_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFTDESDeriveKey");
	pBaseEx->PKCS12PBKDFTDESDeriveIV = (PPKCS12_PBKDF_TDES_DERIVE_IV)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFTDESDeriveIV");
	pBaseEx->PKCS12PBKDFSHA1DeriveHMACKey = (PPKCS12_PBKDF_SHA1_DERIVE_HMAC_KEY)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFSHA1DeriveHMACKey");
	pBaseEx->PKCS12PBKDFSelfTest = (PPKCS12_PBKDF_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "PKCS12PBKDFSelfTest");

	pBaseEx->PBKDF2IDeriveKey = (PPBKDF2I_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PBKDF2IDeriveKey");
	pBaseEx->PBKDF2ISelfTest = (PPBKDF2I_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "PBKDF2ISelfTest");

#else //PC_STATIC_LIBS
	pBaseEx->SHA1HMACAcquireState = SHA1HMACAcquireState;
	pBaseEx->SHA1HMACReleaseState = SHA1HMACReleaseState;
	pBaseEx->SHA1HMACSetStateParameters = SHA1HMACSetStateParameters;
	pBaseEx->SHA1HMACGetStateParameters = SHA1HMACGetStateParameters;
	pBaseEx->SHA1HMACInitializeDataMac = SHA1HMACInitializeDataMac;
	pBaseEx->SHA1HMACUpdateData = SHA1HMACUpdateData;
	pBaseEx->SHA1HMACFinalizeDataMac = SHA1HMACFinalizeDataMac;
	pBaseEx->SHA1HMACSelfTest = SHA1HMACSelfTest;

	pBaseEx->RC2AcquireState = RC2AcquireState;
	pBaseEx->RC2ReleaseState = RC2ReleaseState;
	pBaseEx->RC2SetStateParameters = RC2SetStateParameters;
	pBaseEx->RC2GetStateParameters = RC2GetStateParameters;
	pBaseEx->RC2EncryptDataCBCMode = RC2EncryptDataCBCMode;
	pBaseEx->RC2DecryptDataCBCMode = RC2DecryptDataCBCMode;
	pBaseEx->RC2SelfTest = RC2SelfTest;

	pBaseEx->PKCS12PBKDFRC2DeriveKey = PKCS12PBKDFRC2DeriveKey;
	pBaseEx->PKCS12PBKDFRC2DeriveIV = PKCS12PBKDFRC2DeriveIV;
	pBaseEx->PKCS12PBKDFTDESDeriveKey = PKCS12PBKDFTDESDeriveKey;
	pBaseEx->PKCS12PBKDFTDESDeriveIV = PKCS12PBKDFTDESDeriveIV;
	pBaseEx->PKCS12PBKDFSHA1DeriveHMACKey = PKCS12PBKDFSHA1DeriveHMACKey;
	pBaseEx->PKCS12PBKDFSelfTest = PKCS12PBKDFSelfTest;

	pBaseEx->PBKDF2IDeriveKey = PBKDF2IDeriveKey;
	pBaseEx->PBKDF2ISelfTest = PBKDF2ISelfTest;

#endif // PC_STATIC_LIBS
#else // CSPI_PKCS12
	pBaseEx->SHA1HMACAcquireState = NULL;
	pBaseEx->SHA1HMACReleaseState = NULL;
	pBaseEx->SHA1HMACSetStateParameters = NULL;
	pBaseEx->SHA1HMACGetStateParameters = NULL;
	pBaseEx->SHA1HMACInitializeDataMac = NULL;
	pBaseEx->SHA1HMACUpdateData = NULL;
	pBaseEx->SHA1HMACFinalizeDataMac = NULL;
	pBaseEx->SHA1HMACSelfTest = NULL;

	pBaseEx->RC2AcquireState = NULL;
	pBaseEx->RC2ReleaseState = NULL;
	pBaseEx->RC2SetStateParameters = NULL;
	pBaseEx->RC2GetStateParameters = NULL;
	pBaseEx->RC2EncryptDataCBCMode = NULL;
	pBaseEx->RC2DecryptDataCBCMode = NULL;
	pBaseEx->RC2SelfTest = NULL;

	pBaseEx->PKCS12PBKDFRC2DeriveKey = NULL;
	pBaseEx->PKCS12PBKDFRC2DeriveIV = NULL;
	pBaseEx->PKCS12PBKDFTDESDeriveKey = NULL;
	pBaseEx->PKCS12PBKDFTDESDeriveIV = NULL;
	pBaseEx->PKCS12PBKDFSHA1DeriveHMACKey = NULL;
	pBaseEx->PKCS12PBKDFSelfTest = NULL;

	pBaseEx->PBKDF2IDeriveKey = NULL;
	pBaseEx->PBKDF2ISelfTest = NULL;

#endif // CSP_KDF_UA

#ifdef CSPI_REINITIALIZE_PRNG
#ifndef PC_STATIC_LIBS
	if(!m_hBaseLibrary)
	{
		delete pBaseEx;

		return FALSE;
	}

	pBaseEx->DSTU4145PseudoRNGReinitialize =
		(PDSTU4145_PSEUDO_RNG_REINITIALIZE)
			GetProcAddress(m_hBaseLibrary,
				"DSTU4145PseudoRNGReinitialize");

#else //PC_STATIC_LIBS
	pBaseEx->DSTU4145PseudoRNGReinitialize =
		APPEND_LIBRARY_PREFIX(DSTU4145PseudoRNGReinitialize);

#endif // PC_STATIC_LIBS
#else // CSPI_REINITIALIZE_PRNG
	pBaseEx->DSTU4145PseudoRNGReinitialize = NULL;

#endif // CSPI_REINITIALIZE_PRNG

#ifdef CSPI_AES_GET_PARAMETERS
#ifndef PC_STATIC_LIBS
	if(!m_hBaseLibrary)
	{
		delete pBaseEx;

		return FALSE;
	}

	pBaseEx->AESGetStateParameters = (PAES_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "AESGetStateParameters");

#else //PC_STATIC_LIBS
	pBaseEx->AESGetStateParameters = AESGetStateParameters;

#endif // PC_STATIC_LIBS
#else // CSPI_AES_GET_PARAMETERS
	pBaseEx->AESGetStateParameters = NULL;

#endif // CSPI_AES_GET_PARAMETERS

#ifdef CSPI_AES_GCM
#ifndef PC_STATIC_LIBS
	if(!m_hBaseLibrary)
	{
		delete pBaseEx;

		return FALSE;
	}

	pBaseEx->AESEncryptDataGCMMode = (PAES_ENCRYPT_DATA_GCM_MODE)
		GetProcAddress(m_hBaseLibrary, "AESEncryptDataGCMMode");
	pBaseEx->AESDecryptDataGCMMode = (PAES_DECRYPT_DATA_GCM_MODE)
		GetProcAddress(m_hBaseLibrary, "AESDecryptDataGCMMode");

#else //PC_STATIC_LIBS
	pBaseEx->AESEncryptDataGCMMode = AESEncryptDataGCMMode;
	pBaseEx->AESDecryptDataGCMMode = AESDecryptDataGCMMode;

#endif // PC_STATIC_LIBS
#else // CSPI_AES_GCM
	pBaseEx->AESEncryptDataGCMMode = NULL;
	pBaseEx->AESDecryptDataGCMMode = NULL;

#endif // CSPI_AES_GCM

#ifdef CSPI_ECDSA_COUPLE
#ifndef PC_STATIC_LIBS
	pBaseEx->ECDSACouplePart1EncryptKey = (PECDSA_COUPLE_PART1_ENCRYPT_KEY)
		GetProcAddress(m_hBaseLibrary, "ECDSACouplePart1EncryptKey");
	pBaseEx->ECDSACouplePart1Step1 = (PECDSA_COUPLE_PART1_STEP1)
		GetProcAddress(m_hBaseLibrary, "ECDSACouplePart1Step1");
	pBaseEx->ECDSACouplePart2Step = (PECDSA_COUPLE_PART2_STEP)
		GetProcAddress(m_hBaseLibrary, "ECDSACouplePart2Step");
	pBaseEx->ECDSACouplePart1Step2 = (PECDSA_COUPLE_PART1_STEP2)
		GetProcAddress(m_hBaseLibrary, "ECDSACouplePart1Step2");
	pBaseEx->ECDSACoupleMakeCommonKey = (PECDSA_COUPLE_MAKE_COMMON_KEY)
		GetProcAddress(m_hBaseLibrary, "ECDSACoupleMakeCommonKey");
	pBaseEx->ECDSACoupleSelfTest = (PECDSA_COUPLE_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "ECDSACoupleSelfTest");

#else // PC_STATIC_LIBS
	pBaseEx->ECDSACouplePart1EncryptKey = ECDSACouplePart1EncryptKey;
	pBaseEx->ECDSACouplePart1Step1 = ECDSACouplePart1Step1;
	pBaseEx->ECDSACouplePart2Step = ECDSACouplePart2Step;
	pBaseEx->ECDSACouplePart1Step2 = ECDSACouplePart1Step2;
	pBaseEx->ECDSACoupleMakeCommonKey = ECDSACoupleMakeCommonKey;
	pBaseEx->ECDSACoupleSelfTest = ECDSACoupleSelfTest;

#endif // PC_STATIC_LIBS
#else // CSPI_ECDSA_COUPLE
	pBaseEx->ECDSACouplePart1EncryptKey = NULL;
	pBaseEx->ECDSACouplePart1Step1 = NULL;
	pBaseEx->ECDSACouplePart2Step = NULL;
	pBaseEx->ECDSACouplePart1Step2 = NULL;
	pBaseEx->ECDSACoupleMakeCommonKey = NULL;
	pBaseEx->ECDSACoupleSelfTest = NULL;

#endif // CSPI_ECDSA_COUPLE

#ifndef PC_STATIC_LIBS
	pBaseEx->SHAHMACAcquireState = (PSHA_HMAC_ACQUIRE_STATE)
		GetProcAddress(m_hBaseLibrary, "SHAHMACAcquireState");
	pBaseEx->SHAHMACReleaseState = (PSHA_HMAC_RELEASE_STATE)
		GetProcAddress(m_hBaseLibrary, "SHAHMACReleaseState");
	pBaseEx->SHAHMACSetStateParameters = (PSHA_HMAC_SET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "SHAHMACSetStateParameters");
	pBaseEx->SHAHMACGetStateParameters = (PSHA_HMAC_GET_STATE_PARAMETERS)
		GetProcAddress(m_hBaseLibrary, "SHAHMACGetStateParameters");
	pBaseEx->SHAHMACUpdateData = (PSHA_HMAC_UPDATE_DATA)
		GetProcAddress(m_hBaseLibrary, "SHAHMACUpdateData");
	pBaseEx->SHAHMACFinalizeDataMac = (PSHA_HMAC_FINALIZE_DATA_MAC)
		GetProcAddress(m_hBaseLibrary, "SHAHMACFinalizeDataMac");
	pBaseEx->SHAHMACSelfTest = (PSHA_HMAC_SELF_TEST)
		GetProcAddress(m_hBaseLibrary, "SHAHMACSelfTest");

	pBaseEx->PBKDF2SHADeriveKey = (PPBKDF2_SHA_DERIVE_KEY)
		GetProcAddress(m_hBaseLibrary, "PBKDF2SHADeriveKey");
#else // PC_STATIC_LIBS
	pBaseEx->SHAHMACAcquireState = SHAHMACAcquireState;
	pBaseEx->SHAHMACReleaseState = SHAHMACReleaseState;
	pBaseEx->SHAHMACSetStateParameters = SHAHMACSetStateParameters;
	pBaseEx->SHAHMACGetStateParameters = SHAHMACGetStateParameters;
	pBaseEx->SHAHMACUpdateData = SHAHMACUpdateData;
	pBaseEx->SHAHMACFinalizeDataMac = SHAHMACFinalizeDataMac;
	pBaseEx->SHAHMACSelfTest = SHAHMACSelfTest;

	pBaseEx->PBKDF2SHADeriveKey = PBKDF2SHADeriveKey;
#endif // PC_STATIC_LIBS

	*ppBaseEx = pBaseEx;

	return TRUE;
}

//------------------------------------------------------------------------------

VOID WINAPI CSPIBase::Unload()
{
#ifndef PC_STATIC_LIBS
	if(m_hBaseLibrary != NULL)
	{
		FreeLibrary(m_hBaseLibrary);
		m_hBaseLibrary = NULL;
	}

	if(m_hExtensionLibrary != NULL)
	{
		FreeLibrary(m_hExtensionLibrary);
		m_hExtensionLibrary = NULL;
	}
#endif // PC_STATIC_LIBS
}

//------------------------------------------------------------------------------

VOID WINAPI CSPIBase::UnloadEx(
	PCSPI_BASE_FUNCTIONS_EX *ppBaseEx)
{
	if(ppBaseEx == NULL || *ppBaseEx == NULL)
		return;

	delete *ppBaseEx;
	*ppBaseEx = NULL;
}

//==============================================================================
