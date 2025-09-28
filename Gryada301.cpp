//==============================================================================

#include "Gryada301.h"

//==============================================================================

#ifdef KM_LOGGABLE_RESULT
#include "LoggableResult.h"

#define LOGGABLE_RESULT(Var, Description)	\
	LoggableResult Var(Description);
#else // KM_LOGGABLE_RESULT
#define LOGGABLE_RESULT(Var, Description)	\
	DWORD Var; \
	UNREFERENCED_PARAMETER(Var);
#endif // KM_LOGGABLE_RESULT

//==============================================================================

HINSTANCE Gryada301::hDLL = NULL;
G301_FUNCTIONS Gryada301::F;

//==============================================================================

Gryada301::Gryada301()
{
	hModule = NULL;

	pCSPInterface = NULL;
	pHRNGInterface = NULL;
	pCSPIInterface = NULL;

	blCompat2Checked = FALSE;
	blCompatible2 = FALSE;

	blCompat3Checked = FALSE;
	blCompatible3 = FALSE;

	blCompat4Checked = FALSE;
	blCompatible4 = FALSE;

	blCompat5Checked = FALSE;
	blCompatible5 = FALSE;

	blCompat6Checked = FALSE;
	blCompatible6 = FALSE;

	blCompat7Checked = FALSE;
	blCompatible7 = FALSE;

	blCompat8Checked = FALSE;
	blCompatible8 = FALSE;

	blRev1Checked = FALSE;
	blRevision1 = FALSE;

	uiImageVersion = 0;
}

//------------------------------------------------------------------------------

Gryada301::~Gryada301()
{
	if(pCSPInterface != NULL)
		delete (CSPHardwareImplementationGryada301*) pCSPInterface;

	if(pHRNGInterface != NULL)
		delete (CSPHardwareRNGImplementationGryada301*) pHRNGInterface;

	if(pCSPIInterface != NULL)
		delete (CSPIHardwareImplementationGryada301*) pCSPIInterface;
}

//==============================================================================

BOOL WINAPI Gryada301::LoadEx(
	HMODULE hModule)
{
	if(hDLL)
	{
		return TRUE;
	}

	CHAR szModulePath[MAX_PATH * 4 + 1];

	if(hModule == NULL ||
		!GetModulePath(hModule, szModulePath) ||
		strcat(szModulePath, G301_DLL_NAME) == NULL ||
		(hDLL = LoadLibraryA(szModulePath)) == NULL)
	{
		hDLL = LoadLibraryA(G301_DLL_NAME);
	}

	if(!hDLL)
	{
		return FALSE;
	}

	F.LocateModules = (PG301_LOCATE_MODULES)
		GetProcAddress(hDLL, "G301LocateModules");

	F.EnumModules = (PG301_ENUM_MODULES)
		GetProcAddress(hDLL, "G301EnumModules");

	F.ConnectModule = (PG301_CONNECT_MODULE)
		GetProcAddress(hDLL, "G301ConnectModule");

	F.DisconnectModule = (PG301_DISCONNECT_MODULE)
		GetProcAddress(hDLL, "G301DisconnectModule");

	F.Format = (PG301_FORMAT) GetProcAddress(hDLL, "G301Format");

	F.LogOn = (PG301_LOG_ON) GetProcAddress(hDLL, "G301LogOn");

	F.LogOff = (PG301_LOG_OFF) GetProcAddress(hDLL, "G301LogOff");

	F.ChangePassword = (PG301_CHANGE_PASSWORD)
		GetProcAddress(hDLL, "G301ChangePassword");

	F.GenerateRNSequence = (PG301_GENERATE_RN_SEQUENCE)
		GetProcAddress(hDLL, "G301GenerateRNSequence");

	F.SetSBoxes = (PG301_SET_SBOXES) GetProcAddress(hDLL, 
		"G301SetSBoxes");

	F.GenerateKeys = (PG301_GENERATE_KEYS)
		GetProcAddress(hDLL, "G301GenerateKeys");

	F.HashPrivateKey = (PG301_HASH_PRIVATE_KEY)
		GetProcAddress(hDLL, "G301HashPrivateKey");

	F.SignHash = (PG301_SIGN_HASH) GetProcAddress(hDLL, 
		"G301SignHash");

	F.CheckPublicKey = (PG301_CHECK_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301CheckPublicKey");

	F.EnumBackupKeyMedias = (PG301_ENUM_BACKUP_KEY_MEDIAS)
		GetProcAddress(hDLL, "G301EnumBackupKeyMedias");

	F.BackupKeys = (PG301_BACKUP_KEYS)
		GetProcAddress(hDLL, "G301BackupKeys");

	F.RestoreKeys = (PG301_RESTORE_KEYS)
		GetProcAddress(hDLL, "G301RestoreKeys");

	F.EraseKeys = (PG301_ERASE_KEYS) GetProcAddress(hDLL, 
		"G301EraseKeys");

	F.ProtectSharedData = (PG301_PROTECT_SHARED_DATA)
		GetProcAddress(hDLL, "G301ProtectSharedData");

	F.UnprotectSharedData = (PG301_UNPROTECT_SHARED_DATA)
		GetProcAddress(hDLL, "G301UnprotectSharedData");

	F.StoreData = (PG301_STORE_DATA) GetProcAddress(hDLL, 
		"G301StoreData");

	F.LoadData = (PG301_LOAD_DATA) GetProcAddress(hDLL, 
		"G301LoadData");

	F.EraseData = (PG301_ERASE_DATA) GetProcAddress(hDLL, 
		"G301EraseData");

	F.SetParams = (PG301_SET_PARAMS) GetProcAddress(hDLL, 
		"G301SetParams");

	for(DWORD dw = 0; dw < (sizeof(G301_FUNCTIONS) /
		sizeof(PVOID)) - G301_EXT_FUNCTIONS_COUNT; dw++)
	{
		if(((PVOID *) &F)[dw] == NULL)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;

			return FALSE;
		}
	}

	F.IsCompatible2 = (PG301_IS_COMPATIBLE2) GetProcAddress(
		hDLL, "G301IsCompatible2");

	F.VerifySign = (PG301_VERIFY_SIGN) GetProcAddress(
		hDLL, "G301VerifySign");

	F.IsCompatible3 = (PG301_IS_COMPATIBLE3) GetProcAddress(
		hDLL, "G301IsCompatible3");

	F.MakeSharedKey = (PG301_MAKE_SHARED_KEY) GetProcAddress(
		hDLL, "G301MakeSharedKey");

	F.IsCompatible4 = (PG301_IS_COMPATIBLE4) GetProcAddress(hDLL,
		"G301IsCompatible4");

	F.SetTime = (PG301_SET_TIME) GetProcAddress(hDLL,
		"G301SetTime");

	F.SetClusterParams = (PG301_SET_CLUSTER_PARAMS) GetProcAddress(hDLL,
		"G301SetClusterParams");

	F.IsCompatible5 = (PG301_IS_COMPATIBLE5) GetProcAddress(hDLL,
		"G301IsCompatible5");

	F.SetParams2 = (PG301_SET_PARAMS2) GetProcAddress(hDLL,
		"G301SetParams2");

	F.Reboot = (PG301_REBOOT) GetProcAddress(hDLL,
		"G301Reboot");

	F.Shutdown = (PG301_SHUTDOWN) GetProcAddress(hDLL,
		"G301Shutdown");

	F.IsCompatible6 = (PG301_IS_COMPATIBLE6) GetProcAddress(
		hDLL, "G301IsCompatible6");

	F.SetUseDSKeysAsKEP = (PG301_SET_SET_USE_DS_KEYS_AS_KEP) GetProcAddress(
		hDLL, "G301SetUseDSKeysAsKEP");

	F.SignHashKEP = (PG301_SIGN_HASH_KEP) GetProcAddress(
		hDLL, "G301SignHashKEP");

#ifdef CSP_ECDH_UA
	F.WrapSharedKey = (PG301_WRAP_SHARED_KEY) GetProcAddress(
		hDLL, "G301WrapSharedKey");

	F.UnwrapSharedKey = (PG301_UNWRAP_SHARED_KEY) GetProcAddress(
		hDLL, "G301UnwrapSharedKey");
#endif // CSP_ECDH_UA

	F.IsCompatible7 = (PG301_IS_COMPATIBLE7) GetProcAddress(
		hDLL, "G301IsCompatible7");

	F.GetClusterParams = (PG301_GET_CLUSTER_PARAMS) GetProcAddress(
		hDLL, "G301GetClusterParams");

	F.GetParams2 = (PG301_GET_PARAMS2) GetProcAddress(
		hDLL, "G301GetParams2");

	F.IsRevision1 = (PG301_IS_REVISION1) GetProcAddress(
		hDLL, "G301IsRevision1");

	F.GetPublicKey = (PG301_GET_PUBLIC_KEY) GetProcAddress(
		hDLL, "G301GetPublicKey");

	F.SetDataLabel = (PG301_SET_DATA_LABEL) GetProcAddress(
		hDLL, "G301SetDataLabel");

	F.SetDataPassword = (PG301_SET_DATA_PASSWORD) GetProcAddress(
		hDLL, "G301SetDataPassword");

	F.ChangeDataPassword = (PG301_CHANGE_DATA_PASSWORD) GetProcAddress(
		hDLL, "G301ChangeDataPassword");

	F.BackupKeysWithPassword = (PG301_BACKUP_KEYS_WITH_PASSWORD)
		GetProcAddress(hDLL, "G301BackupKeysWithPassword");

	F.RestoreKeysWithPassword = (PG301_RESTORE_KEYS_WITH_PASSWORD)
		GetProcAddress(hDLL, "G301RestoreKeysWithPassword");

	F.EraseBackupKeys = (PG301_ERASE_BACKUP_KEYS)
		GetProcAddress(hDLL, "G301EraseBackupKeys");

	F.GenerateRSAKeys = (PG301_GENERATE_RSA_KEYS)
		GetProcAddress(hDLL, "G301GenerateRSAKeys");

	F.RSASignHash = (PG301_RSA_SIGN_HASH)
		GetProcAddress(hDLL, "G301RSASignHash");

	F.CheckRSAPublicKey = (PG301_CHECK_RSA_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301CheckRSAPublicKey");

	F.GetRSAPublicKey = (PG301_GET_RSA_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301GetRSAPublicKey");

	F.RSADecryptData = (PG301_RSA_DECRYPT_DATA)
		GetProcAddress(hDLL, "G301RSADecryptData");

	F.GenerateECDSAKeys = (PG301_GENERATE_ECDSA_KEYS)
		GetProcAddress(hDLL, "G301GenerateECDSAKeys");

	F.ECDSASignHash = (PG301_ECDSA_SIGN_HASH)
		GetProcAddress(hDLL, "G301ECDSASignHash");

	F.CheckECDSAPublicKey = (PG301_CHECK_ECDSA_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301CheckECDSAPublicKey");

	F.GetECDSAPublicKey = (PG301_GET_ECDSA_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301GetECDSAPublicKey");

	F.ECDHCalculateSharedSecret = (PG301_ECDH_CALCULATE_SHARED_SECRET)
		GetProcAddress(hDLL, "G301ECDHCalculateSharedSecret");

	F.StoreModuleData = (PG301_STORE_MODULE_DATA) GetProcAddress(hDLL,
		"G301StoreModuleData");

	F.LoadModuleData = (PG301_LOAD_MODULE_DATA) GetProcAddress(hDLL,
		"G301LoadModuleData");

	F.EraseModuleData = (PG301_ERASE_MODULE_DATA) GetProcAddress(hDLL,
		"G301EraseModuleData");

	F.GetFirstClients = (PG301_GET_FIRST_CLIENTS) GetProcAddress(hDLL,
		"G301GetFirstClients");

	F.GetNextClients = (PG301_GET_NEXT_CLIENTS) GetProcAddress(hDLL,
		"G301GetNextClients");

	F.FreeClients = (PG301_FREE_CLIENTS) GetProcAddress(hDLL,
		"G301FreeClients");

	F.AddClient = (PG301_ADD_CLIENT) GetProcAddress(hDLL,
		"G301AddClient");

	F.ChangeClient = (PG301_CHANGE_CLIENT) GetProcAddress(hDLL,
		"G301ChangeClient");

	F.RemoveClient = (PG301_REMOVE_CLIENT) GetProcAddress(hDLL,
		"G301RemoveClient");

	F.IsCompatible8 = (PG301_IS_COMPATIBLE2) GetProcAddress(
		hDLL, "G301IsCompatible8");

	F.EnumPublicKeys = (PG301_ENUM_PUBLIC_KEYS) GetProcAddress(
		hDLL, "G301EnumPublicKeys");

	F.GetLabeledPublicKey = (PG301_GET_LABELED_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301GetLabeledPublicKey");

	F.GetLabeledRSAPublicKey = (PG301_GET_LABELED_RSA_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301GetLabeledRSAPublicKey");

	F.GetLabeledECDSAPublicKey = (PG301_GET_LABELED_ECDSA_PUBLIC_KEY)
		GetProcAddress(hDLL, "G301GetLabeledECDSAPublicKey");

	F.FindPublicKeyByID = (PG301_FIND_PUBLIC_KEY_BY_ID) GetProcAddress(
		hDLL, "G301FindPublicKeyByID");

	F.GetInfo = (PG301_GET_INFO) GetProcAddress(
		hDLL, "G301GetInfo");

	F.EnumData = (PG301_ENUM_DATA) GetProcAddress(
		hDLL, "G301EnumData");

	F.EraseLabeledData = (PG301_ERASE_LABELED_DATA) GetProcAddress(
		hDLL, "G301EraseLabeledData");

	F.GetClientInfo = (PG301_GET_CLIENT_INFO) GetProcAddress(
		hDLL, "G301GetClientInfo");

	F.CoupleDSMakeComponentS = (PG301_MAKE_COUPLE_SIGN_COMPONENT_S)
		GetProcAddress(hDLL, "G301CoupleDSMakeComponentS");

	F.EnumBackupEKeysLocal = (PG301_ENUM_BACKUP_EKEYS_LOCAL)
		GetProcAddress(hDLL, "G301EnumBackupEKeysLocal");

	F.BackupKeysRemote = (PG301_BACKUP_KEYS_REMOTE)
		GetProcAddress(hDLL, "G301BackupKeysRemote");

	F.RestoreKeysRemote = (PG301_RESTORE_KEYS_REMOTE)
		GetProcAddress(hDLL, "G301RestoreKeysRemote");

	F.EraseBackupKeysLocal = (PG301_ERASE_BACKUP_KEYS_LOCAL)
		GetProcAddress(hDLL, "G301EraseBackupKeysLocal");

	F.ECDSACouplePart2Step = (PG301_ECDSA_COUPLE_PART2_STEP)
		GetProcAddress(hDLL, "G301ECDSACouplePart2Step");

	F.MakeECDSACoupleCommonPublicKey =
		(PG301_MAKE_ECDSA_COUPLE_COMMON_PUB_KEY)
			GetProcAddress(hDLL,
				"G301MakeECDSACoupleCommonPublicKey");

	F.GetClientSecurity = (PG301_GET_CLIENT_SECURITY) GetProcAddress(
		hDLL, "G301GetClientSecurity");

	F.SetClientSecurity = (PG301_SET_CLIENT_SECURITY) GetProcAddress(
		hDLL, "G301SetClientSecurity");

	F.SignDSTUHash = (PG301_SIGN_DSTU_HASH) GetProcAddress(
		hDLL, "G301SignDSTUHash");

	F.VerifyDSTUSign = (PG301_VERIFY_DSTU_SIGN) GetProcAddress(
		hDLL, "G301VerifyDSTUSign");

	F.SignDSTUHashKEP = (PG301_SIGN_DSTU_HASH_KEP) GetProcAddress(
		hDLL, "G301SignDSTUHashKEP");

	F.DSTUWrapSharedKey = (PG301_DSTU_WRAP_SHARED_KEY) GetProcAddress(
		hDLL, "G301DSTUWrapSharedKey");

	F.DSTUUnwrapSharedKey = (PG301_DSTU_UNWRAP_SHARED_KEY) GetProcAddress(
		hDLL, "G301DSTUUnwrapSharedKey");

	F.RSASignHashEx = (PG301_RSA_SIGN_HASH_EX) GetProcAddress(
		hDLL, "G301RSASignHashEx");

	F.RenameData = (PG301_RENAME_DATA) GetProcAddress(
		hDLL, "G301RenameData");

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::Load()
{
	return LoadEx(NULL);
}

//------------------------------------------------------------------------------

VOID WINAPI Gryada301::Unload()
{
	if(hDLL)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
	}
}

//==============================================================================

BOOL WINAPI Gryada301::LocateModules()
{
	return F.LocateModules();
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::EnumModules(
	DWORD iModule,
	PG301_MODULE_INFO pInfo)
{
	return F.EnumModules(iModule, pInfo);
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::ConnectModule(
	DWORD iModule)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ConnectModule");

	if(hModule != NULL)
		return TRUE;

	if(!F.ConnectModule(iModule, &hModule))
		return FALSE;

	blCompat2Checked = FALSE;
	blCompatible2 = FALSE;

	blCompat3Checked = FALSE;
	blCompatible3 = FALSE;

	blCompat4Checked = FALSE;
	blCompatible4 = FALSE;

	blCompat5Checked = FALSE;
	blCompatible5 = FALSE;

	blCompat6Checked = FALSE;
	blCompatible6 = FALSE;

	blCompat7Checked = FALSE;
	blCompatible7 = FALSE;

	blCompat8Checked = FALSE;
	blCompatible8 = FALSE;

	blRev1Checked = FALSE;
	blRevision1 = FALSE;

	uiImageVersion = 0;

	return (hModule != NULL);
}

//------------------------------------------------------------------------------

VOID WINAPI Gryada301::DisconnectModule()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::DisconnectModule");

	if(hModule != NULL)
	{
		F.DisconnectModule(hModule);
		hModule = NULL;

		blCompat2Checked = FALSE;
		blCompatible2 = FALSE;

		blCompat3Checked = FALSE;
		blCompatible3 = FALSE;

		blCompat4Checked = FALSE;
		blCompatible4 = FALSE;

		blCompat5Checked = FALSE;
		blCompatible5 = FALSE;

		blCompat6Checked = FALSE;
		blCompatible6 = FALSE;

		blCompat7Checked = FALSE;
		blCompatible7 = FALSE;

		blCompat8Checked = FALSE;
		blCompatible8 = FALSE;

		blRev1Checked = FALSE;
		blRevision1 = FALSE;

		uiImageVersion = 0;
	}
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::Format(
	PSTR pszPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::Format");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
	{
		dwError = LogOn(pszPassword);
		if(dwError != G301_SUCCESS)
			return dwError;

		dwError = EraseKeys();
		if(dwError != G301_SUCCESS)
		{
			LogOff();

			return dwError;
		}

		LogOff();
	}

	return F.Format(hModule, pszPassword);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::LogOn(
	PSTR pszPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::LogOn");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.LogOn(hModule, pszPassword);
	if(dwError == G301_SUCCESS)
		SetUseDSKeysAsKEP(FALSE);

	return dwError;
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::LogOff()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::LogOff");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.LogOff(hModule));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ChangePassword(
	PSTR pszNewPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ChangePassword");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.ChangePassword(
		hModule, pszNewPassword));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GenerateRNSequence(
	PBYTE pbSequence,
	DWORD cbSequence)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GenerateRNSequence");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.GenerateRNSequence(
		hModule, pbSequence, cbSequence));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetSBoxes(
	GOST28147_COMPRESSED_SBOX pPRNGSBox,
	GOST28147_COMPRESSED_SBOX pDHSBox)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetSBoxes");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.SetSBoxes(
		hModule, pPRNGSBox, pDHSBox));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GenerateKeys(
	BOOL blDSKeys,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GenerateKeys");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	ZeroMemory(pKeyQ, sizeof(DSTU4145_KEY_Q));

	return (dwError = F.GenerateKeys(
		hModule, blDSKeys, pParameterEC,
		pParameterP, pKeyQ));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::HashPrivateKey(
	GOST34311_HASH pHash)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::HashPrivateKey");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.HashPrivateKey(
		hModule, pHash));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SignHash(
	GOST34311_HASH pHash,
	DSTU4145_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SignHash");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.SignHash(
		hModule, pHash, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SignDSTUHash(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	DSTU4145_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SignDSTUHash");

	if(F.SignDSTUHash == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.SignDSTUHash(
		hModule, dwHash, pHash, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::CoupleDSMakeComponentS(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_NUMBER pKeyK,
	DSTU4145_NUMBER pCommonComponentR,
	DSTU4145_NUMBER pComponentS)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::CoupleDSMakeComponentS");

	if(F.CoupleDSMakeComponentS == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE5_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.CoupleDSMakeComponentS(
		hModule, pParameterEC, pParameterP,
		pKeyK, pCommonComponentR,
		pComponentS));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsCompatible2()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible2");

	if(F.IsCompatible2 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat2Checked)
	{
		if(!blCompatible2)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsCompatible2(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat2Checked = TRUE;
			blCompatible2 = FALSE;
		}

		return dwError;
	}

	blCompat2Checked = TRUE;
	blCompatible2 = TRUE;
	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::VerifySign(
	GOST34311_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::VerifySign");

	if(F.VerifySign == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.VerifySign(
		hModule, pHash, pParameterEC,
		pParameterP, pKeyQ, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::VerifyDSTUSign(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ,
	DSTU4145_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::VerifyDSTUSign");

	if(F.VerifyDSTUSign == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.VerifyDSTUSign(
		hModule, dwHash, pHash, pParameterEC,
		pParameterP, pKeyQ, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::CheckPublicKey(
	BOOL blDSKey,
	DSTU4145_KEY_Q pKeyQ)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::CheckPublicKey");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.CheckPublicKey(
		hModule, blDSKey, pKeyQ));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetPublicKey(
	BOOL blDSKey,
	DSTU4145_KEY_Q pKeyQ)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetPublicKey");

	if(F.GetPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetPublicKey(
		hModule, blDSKey, pKeyQ));
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::EnumBackupKeyMedias(
	INT nIndex,
	PSTR pszName)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EnumBackupKeyMedias");

	return F.EnumBackupKeyMedias(nIndex, pszName);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::BackupKeys(
	DWORD dwKeyMedia)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::BackupKeys");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.BackupKeys(
		hModule, dwKeyMedia));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RestoreKeys(
	DWORD dwKeyMedia)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RestoreKeys");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.RestoreKeys(
		hModule, dwKeyMedia));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::BackupKeysWithPassword(
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::BackupKeysWithPassword");

	if(F.BackupKeysWithPassword == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.BackupKeysWithPassword(
		hModule, dwKeyMedia,
		uiKeysAlgos, uiOperation,
		pszPassword));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RestoreKeysWithPassword(
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RestoreKeysWithPassword");

	if(F.RestoreKeysWithPassword == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.RestoreKeysWithPassword(
		hModule, dwKeyMedia,
		uiKeysAlgos, uiOperation,
		pszPassword));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EraseKeys()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseKeys");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.EraseKeys(hModule));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EraseBackupKeys(
	DWORD dwKeyMedia)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseBackupKeys");

	if(F.EraseBackupKeys == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.EraseBackupKeys(
		hModule, dwKeyMedia));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EnumBackupEKeysLocal(
	DWORD dwIndex,
	DWORD dwKeyMedia,
	PSTR pszEKey,
	PSTR pszError)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EnumBackupEKeysLocal");

	strcpy(pszError, "");

	if(F.EnumBackupEKeysLocal == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE7_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(!F.EnumBackupEKeysLocal(
		hModule, dwIndex, dwKeyMedia,
		pszEKey, pszError))
	{
		if(strcmp(pszError, "") != 0)
			return (dwError = G301_INTERNAL_ERROR);
		else
			return (dwError = G301_ERROR_NO_DATA);
	}

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::BackupKeysRemote(
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword,
	PSTR pszEKey1,
	PSTR pszEKey2,
	PSTR pszRemovableDisk,
	PSTR pszError)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::BackupKeysRemote");

	strcpy(pszError, "");

	if(F.BackupKeysRemote == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE7_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.BackupKeysRemote(
		hModule, dwKeyMedia,
		uiKeysAlgos, uiOperation,
		pszPassword,
		pszEKey1, pszEKey2,
		pszRemovableDisk,
		pszError));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RestoreKeysRemote(
	DWORD dwKeyMedia,
	UINT uiKeysAlgos,
	UINT uiOperation,
	PSTR pszPassword,
	PSTR pszEKey1,
	PSTR pszEKey2,
	PSTR pszRemovableDisk,
	PHANDLE	phKeysDBFile,
	PSTR pszError)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RestoreKeysRemote");

	strcpy(pszError, "");

	if(F.RestoreKeysRemote == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE7_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.RestoreKeysRemote(hModule,
		dwKeyMedia,
		uiKeysAlgos, uiOperation,
		pszPassword,
		pszEKey1, pszEKey2,
		pszRemovableDisk,
		phKeysDBFile,
		pszError));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EraseBackupKeysLocal(
	DWORD dwKeyMedia,
	PSTR pszEKey1,
	PSTR pszEKey2,
	PSTR pszRemovableDisk,
	PSTR pszError)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseBackupKeysLocal");

	strcpy(pszError, "");

	if(F.EraseBackupKeysLocal == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE7_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(!F.EraseBackupKeysLocal(
		hModule, dwKeyMedia,
		pszEKey1, pszEKey2,
		pszRemovableDisk,
		pszError))
	{
		return (dwError = G301_INTERNAL_ERROR);
	}

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ProtectSharedData(
	DSTU4145_KEY_Q pKeyQ,
	ECDH_EXTENDED_DATA pData,
	PBYTE pbData,
	DWORD cbData,
	GOST28147_MAC pMAC)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ProtectSharedData");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.ProtectSharedData(
		hModule, pKeyQ, pData, pbData, cbData, pMAC));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::UnprotectSharedData(
	DSTU4145_KEY_Q pKeyQ,
	ECDH_EXTENDED_DATA pData,
	PBYTE pbData,
	DWORD cbData,
	GOST28147_MAC pMAC)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::UnprotectSharedData");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.UnprotectSharedData(
		hModule, pKeyQ, pData, pbData, cbData, pMAC));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsCompatible3()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible3");

	if(F.IsCompatible3 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat3Checked)
	{
		if(!blCompatible3)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsCompatible3(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat3Checked = TRUE;
			blCompatible3 = FALSE;
		}

		return dwError;
	}

	blCompat3Checked = TRUE;
	blCompatible3 = TRUE;
	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::MakeSharedKey(
	DSTU4145_KEY_Q pKeyQ,
	ECDH_EXTENDED_DATA pData,
	GOST28147_KEY pKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::MakeSharedKey");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.MakeSharedKey(
		hModule, pKeyQ, pData, pKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::StoreData(
	PBYTE pbData,
	DWORD cbData)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::StoreData");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.StoreData(
		hModule, pbData, cbData));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::LoadData(
	PBYTE pbData,
	PDWORD pcbData)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::LoadData");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.LoadData(
		hModule, pbData, pcbData));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EraseData()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseData");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	return (dwError = F.EraseData(hModule));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::StoreModuleData(
	UINT uiReserved,
	PBYTE pbData,
	DWORD cbData)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::StoreModuleData");

	if(F.StoreModuleData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.StoreModuleData(
		hModule, uiReserved, pbData, cbData));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::LoadModuleData(
	UINT uiReserved,
	PBYTE pbData,
	PDWORD pcbData)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::LoadModuleData");

	if(F.LoadModuleData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.LoadModuleData(
		hModule, uiReserved, pbData, pcbData));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EraseModuleData(
	UINT uiReserved)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseModuleData");

	if(F.EraseModuleData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.EraseModuleData(hModule, uiReserved));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetParams(
	PG301_MODULE_PARAMS pParams)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseData");

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
		return dwError;

	return (dwError = F.SetParams(hModule, pParams));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsCompatible4()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible4");

	if(F.IsCompatible4 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat4Checked)
	{
		if(!blCompatible4)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsCompatible4(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat4Checked = TRUE;
			blCompatible4 = FALSE;
		}

		return dwError;
	}

	blCompat4Checked = TRUE;
	blCompatible4 = TRUE;

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetTime(
	PSYSTEMTIME pTime)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetTime");

	if(F.SetTime == NULL)
		return G301_ERROR_BAD_REQUEST;

	if(hModule == NULL)
		return G301_INTERNAL_ERROR;

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
		return dwError;

	dwError = IsCompatible4();
	if(dwError != G301_SUCCESS)
		return dwError;

	return F.SetTime(hModule, pTime);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetClusterParams(
	PG301_CLUSTER_PARAMS pClusterParams)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetClusterParams");

	if(F.SetClusterParams == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
		return dwError;

	dwError = IsCompatible4();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.SetClusterParams(
		hModule, pClusterParams));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsCompatible5()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible5");

	if(F.IsCompatible5 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat5Checked)
	{
		if(!blCompatible5)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsCompatible5(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat5Checked = TRUE;
			blCompatible5 = FALSE;
		}

		return dwError;
	}

	blCompat5Checked = TRUE;
	blCompatible5 = TRUE;

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetParams2(
	PG301_MODULE_PARAMS2 pParams2)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetParams2");

	if(F.SetParams2 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
		return dwError;

	dwError = IsCompatible5();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.SetParams2(
		hModule, pParams2));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::Reboot()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::Reboot");

	if(F.Reboot == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsCompatible5();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.Reboot(hModule));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::Shutdown()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::Shutdown");

	if(F.Shutdown == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsCompatible5();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.Shutdown(hModule));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsCompatible6()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible6");

	if(F.IsCompatible6 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat6Checked)
	{
		if(!blCompatible6)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsCompatible6(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat6Checked = TRUE;
			blCompatible6 = FALSE;
		}

		return dwError;
	}

	blCompat6Checked = TRUE;
	blCompatible6 = TRUE;

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetUseDSKeysAsKEP(
	BOOL blUse)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetUseDSKeysAsKEP");

	if(F.SetUseDSKeysAsKEP == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsCompatible6();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.SetUseDSKeysAsKEP(
		hModule, blUse));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SignHashKEP(
	GOST34311_HASH pHash,
	DSTU4145_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SignHashKEP");

	if(F.SignHashKEP == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsCompatible6();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.SignHashKEP(
		hModule, pHash, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SignDSTUHashKEP(
	DWORD dwHash,
	DSTU7564_HASH pHash,
	DSTU4145_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SignDSTUHashKEP");

	if(F.SignDSTUHashKEP == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.SignDSTUHashKEP(
		hModule, dwHash, pHash, pSignature));
}

//------------------------------------------------------------------------------

#ifdef CSP_ECDH_UA
DWORD WINAPI Gryada301::WrapSharedKey(
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	GOST28147_KEY pKey,
	GOST28147_WRAPED_KEY pWrappedKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::WrapSharedKey");

	if(F.WrapSharedKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsCompatible6();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.WrapSharedKey(
		hModule, dwParameterECM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, cbSharedInfo,
		pKey, pWrappedKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::UnwrapSharedKey(
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::UnwrapSharedKey");

	if(F.UnwrapSharedKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsCompatible6();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.UnwrapSharedKey(
		hModule, dwParameterECM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, cbSharedInfo,
		pWrappedKey, pKey));
}
#endif // CSP_ECDH_UA

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::DSTUWrapSharedKey(
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	PBYTE pKey,
	DWORD dwKey,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::DSTUWrapSharedKey");

	if(F.DSTUWrapSharedKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.DSTUWrapSharedKey(
		hModule, dwParameterECM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, cbSharedInfo,
		pKey, dwKey, pWrappedKey, dwWrappedKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::DSTUUnwrapSharedKey(
	UINT dwParameterECM,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD cbSharedInfo,
	PBYTE pWrappedKey,
	DWORD dwWrappedKey,
	PBYTE pKey,
	DWORD dwKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::DSTUUnwrapSharedKey");

	if(F.DSTUUnwrapSharedKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.DSTUUnwrapSharedKey(
		hModule, dwParameterECM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, cbSharedInfo,
		pWrappedKey, dwWrappedKey, pKey, dwKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsCompatible7()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible7");

	if(F.IsCompatible7 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat7Checked)
	{
		if(!blCompatible7)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsCompatible7(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat7Checked = TRUE;
			blCompatible7 = FALSE;
		}

		return dwError;
	}

	blCompat7Checked = TRUE;
	blCompatible7 = TRUE;

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetClusterParams(
	PG301_CLUSTER_PARAMS pClusterParams)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetClusterParams");

	if(F.GetClusterParams == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
		return dwError;

	dwError = IsCompatible7();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetClusterParams(
		hModule, pClusterParams));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetParams2(
	PG301_MODULE_PARAMS2 pParams2)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetParams2");

	if(F.GetParams2 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError == G301_SUCCESS)
		return dwError;

	dwError = IsCompatible7();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetParams2(
		hModule, pParams2));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::IsRevision1()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsRevision1");

	if(F.IsRevision1 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blRev1Checked)
	{
		if(!blRevision1)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = F.IsRevision1(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blRev1Checked = TRUE;
			blRevision1 = FALSE;
		}

		return dwError;
	}

	blRev1Checked = TRUE;
	blRevision1 = TRUE;

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetDataLabel(
	BOOL blAppend,
	PSTR pszLabel)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetDataLabel");

	if(F.SetDataLabel == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.SetDataLabel(
		hModule, blAppend, pszLabel));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetDataPassword(
	PSTR pszPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetDataPassword");

	if(F.SetDataPassword == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.SetDataPassword(
		hModule, pszPassword));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ChangeDataPassword(
	PSTR pszNewPassword)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ChangeDataPassword");

	if(F.ChangeDataPassword == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.ChangeDataPassword(
		hModule, pszNewPassword));
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::EnumKeysOwners(
	INT nIndex,
	PSTR pszLabel,
	PSTR pszDescr)
{
	if(pszLabel == NULL && pszDescr == NULL)
		return FALSE;

	switch(nIndex)
	{
	case 0:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_NONE_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_NONE_DESCR);

		return TRUE;

	case 1:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_CA_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_CA_DESCR);

		return TRUE;

	case 2:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_CMP_SERVER_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_CMP_SERVER_DESCR);

		return TRUE;

	case 3:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_TSP_SERVER_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_TSP_SERVER_DESCR);

		return TRUE;

	case 4:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_OCSP_SERVER_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_OCSP_SERVER_DESCR);

		return TRUE;

	case 5:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_RA_ADMIN_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_RA_ADMIN_DESCR);

		return TRUE;

	case 6:
		if(pszLabel != NULL)
			strcpy(pszLabel, G301_KEYS_OWNER_END_USER_LABEL);
		if(pszDescr != NULL)
			strcpy(pszDescr, G301_KEYS_OWNER_END_USER_DESCR);

		return TRUE;
	}

	if(pszLabel != NULL)
		strcpy(pszLabel, "");
	if(pszDescr != NULL)
		strcpy(pszDescr, "");

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::EnumKeysAlgos(
	INT nIndex,
	PSTR pszDescr)
{
	if(pszDescr == NULL)
		return FALSE;

	switch(nIndex)
	{
		case G301_KEYS_ALGOS_STATE:
			strcpy(pszDescr, G301_KEYS_ALGOS_STATE_DESCR);

			return TRUE;

		case G301_KEYS_ALGOS_INTERNATIONAL:
			strcpy(pszDescr, G301_KEYS_ALGOS_INTERNATIONAL_DESCR);

			return TRUE;

		case G301_KEYS_ALGOS_ALL:
			strcpy(pszDescr, G301_KEYS_ALGOS_ALL_DESCR);

			return TRUE;
	}

	strcpy(pszDescr, "");

	return FALSE;
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GenerateRSAKeys(
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GenerateRSAKeys");

	if(F.GenerateRSAKeys == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GenerateRSAKeys(
		hModule, pParameters, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RSASignHash(
	SHA_HASH pHash,
	RSA_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RSASignHash");

	if(F.RSASignHash == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.RSASignHash(
		hModule, pHash, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RSASignHashEx(
	DWORD dwVersion,
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RSASignHashEx");

	if(F.RSASignHashEx == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.RSASignHashEx(
		hModule, dwVersion, dwHash, pHash, pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::CheckRSAPublicKey(
	PRSA_PUBLIC_KEY pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::CheckRSAPublicKey");

	if(F.CheckRSAPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.CheckRSAPublicKey(
		hModule, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetRSAPublicKey(
	PRSA_PUBLIC_KEY pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetRSAPublicKey");

	if(F.GetRSAPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetRSAPublicKey(
		hModule, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RSADecryptData(
	PBYTE pbData,
	PDWORD pdwData,
	PRSA_PARAMETERS pParameters,
	BOOL blUnpadData)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RSADecryptData");

	if(F.RSADecryptData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.RSADecryptData(
		hModule, pbData, pdwData,
		pParameters, blUnpadData));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GenerateECDSAKeys(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GenerateECDSAKeys");

	if(F.GenerateECDSAKeys == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GenerateECDSAKeys(
		hModule, pParameters, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ECDSASignHash(
	DWORD dwHash,
	SHA_HASH pHash,
	PECDSA_SIGNATURE pSignature)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ECDSASignHash");

	if(F.ECDSASignHash == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.ECDSASignHash(
		hModule, dwHash, pHash,
		pSignature));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ECDSACouplePart2Step(
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_NUMBER pPaillierPublicKey,
	ECDSA_ENCODED_POINT pComponentR1,
	PAILLIER_NUMBER pEncryptedPrivateKey1,
	ECDSA_NUMBER pCommonComponentR,
	PAILLIER_NUMBER pComponentS2)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ECDSACouplePart2Step");

	if(F.ECDSACouplePart2Step == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE8_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.ECDSACouplePart2Step(
		hModule, dwHash, pHash,
		pPaillierPublicKey, pComponentR1,
		pEncryptedPrivateKey1,
		pCommonComponentR, pComponentS2));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::CheckECDSAPublicKey(
	ECDSA_KEY_Q pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::CheckECDSAPublicKey");

	if(F.CheckECDSAPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.CheckECDSAPublicKey(
		hModule, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetECDSAPublicKey(
	ECDSA_KEY_Q pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetECDSAPublicKey");

	if(F.GetECDSAPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetECDSAPublicKey(
		hModule, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::MakeECDSACoupleCommonPublicKey(
	ECDSA_KEY_Q pPublicKeyB,
	ECDSA_KEY_Q pCommonPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::MakeECDSACoupleCommonPublicKey");

	if(F.MakeECDSACoupleCommonPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE8_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.MakeECDSACoupleCommonPublicKey(
		hModule, pPublicKeyB,
		pCommonPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ECDHCalculateSharedSecret(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pRecipientPublicKey,
	ECDSA_NUMBER pSharedSecret)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ECDHCalculateSharedSecret");

	if(F.ECDHCalculateSharedSecret == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.ECDHCalculateSharedSecret(
		hModule, pParameters,
		pRecipientPublicKey, pSharedSecret));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetFirstClients(
	PDWORD pdwClients,
	PG301_CLIENT *ppClients)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetFirstClients");

	if(F.GetFirstClients == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetFirstClients(
		hModule, pdwClients,
		ppClients));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetNextClients(
	PDWORD pdwClients,
	PG301_CLIENT *ppClients)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetNextClients");

	if(F.GetNextClients == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetNextClients(
		hModule, pdwClients,
		ppClients));
}

//------------------------------------------------------------------------------

VOID WINAPI Gryada301::FreeClients(
	PG301_CLIENT *ppClients)
{
	if(F.FreeClients == NULL)
		return;

	F.FreeClients(ppClients);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::AddClient(
	PG301_CLIENT pClient)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::AddClient");

	if(F.AddClient == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.AddClient(
		hModule, pClient));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::ChangeClient(
	PSTR pszClientName,
	PG301_CLIENT pChangedClient)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::ChangeClient");

	if(F.ChangeClient == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.ChangeClient(
		hModule, pszClientName,
		pChangedClient));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RemoveClient(
	PSTR pszClientName)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RemoveClient");

	if(F.RemoveClient == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.RemoveClient(
		hModule, pszClientName));
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::EnumClientsTypes(
	INT nIndex,
	PSTR pszDescr,
	PSTR pszDescrTitle)
{
	if(pszDescr == NULL && pszDescrTitle == NULL)
		return FALSE;

	switch(nIndex + 1)
	{
	case G301_CLIENT_TYPE_ADMINISTRATOR:
		if(pszDescr != NULL)
		{
			strcpy(pszDescr,
				G301_CLIENT_TYPE_ADMINISTRATOR_DESCRIPTION);
		}
		if(pszDescrTitle != NULL)
		{
			strcpy(pszDescrTitle,
			G301_CLIENT_TYPE_ADMINISTRATOR_DESCRIPTION_TITLE);
		}

		return TRUE;

	case G301_CLIENT_TYPE_OPERATOR:
		if(pszDescr != NULL)
		{
			strcpy(pszDescr,
				G301_CLIENT_TYPE_OPERATOR_DESCRIPTION);
		}
		if(pszDescrTitle != NULL)
		{
			strcpy(pszDescrTitle,
				G301_CLIENT_TYPE_OPERATOR_DESCRIPTION_TITLE);
		}

		return TRUE;

	case G301_CLIENT_TYPE_BOTH:
		if(pszDescr != NULL)
		{
			strcpy(pszDescr,
				G301_CLIENT_TYPE_BOTH_DESCRIPTION);
		}
		if(pszDescrTitle != NULL)
		{
			strcpy(pszDescrTitle,
				G301_CLIENT_TYPE_BOTH_DESCRIPTION_TITLE);
		}

		return TRUE;
	}

	if(pszDescr != NULL)
		strcpy(pszDescr, "");
	if(pszDescrTitle != NULL)
		strcpy(pszDescrTitle, "");

	return FALSE;
}

//==============================================================================

DWORD WINAPI Gryada301::IsCompatible8()
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::IsCompatible8");

	if(F.IsCompatible8 == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(blCompat8Checked)
	{
		if(!blCompatible8)
			return (dwError = G301_ERROR_BAD_REQUEST);

		return (dwError = G301_SUCCESS);
	}

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = F.IsCompatible8(hModule);
	if(dwError != G301_SUCCESS)
	{
		if(dwError == G301_ERROR_BAD_REQUEST)
		{
			blCompat8Checked = TRUE;
			blCompatible8 = FALSE;
		}

		return dwError;
	}

	blCompat8Checked = TRUE;
	blCompatible8 = TRUE;

	return (dwError = G301_SUCCESS);
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EnumPublicKeys(
	BOOL blFirst,
	UINT uiType,
	BOOL blAppendedLabel,
	PSTR pszSubLabel,
	PUINT puiType,
	PSTR pszAppendedLabel,
	PSTR pszPartialLabel)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EnumPublicKeys");

	if(F.EnumPublicKeys == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	if(pszSubLabel == NULL)
		pszSubLabel = const_cast<PSTR>("");

	if(pszAppendedLabel == NULL &&
		pszPartialLabel == NULL)
	{
		return (dwError = G301_INTERNAL_ERROR);
	}

	CHAR	szAppendedLabel[G301_POINT_NAME_LENGTH +
			G301_DATA_LABEL_DELIMITER_LENGTH +
				G301_MAX_DATA_LABEL_LENGTH + 1],
		szPartialLabel[G301_MAX_DATA_LABEL_LENGTH + 1];

	if(pszAppendedLabel == NULL)
		pszAppendedLabel = szAppendedLabel;

	if(pszPartialLabel == NULL)
		pszPartialLabel = szPartialLabel;

	return (dwError = F.EnumPublicKeys(
		hModule, blFirst,
		uiType, blAppendedLabel, pszSubLabel,
		puiType, pszAppendedLabel, pszPartialLabel));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetLabeledPublicKey(
	BOOL blDSKey,
	PSTR pszLabel,
	BOOL blAppendLabel,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetLabeledPublicKey");

	if(F.GetLabeledPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetLabeledPublicKey(
		hModule, blDSKey,
		pszLabel, blAppendLabel,
		pParameterEC, pParameterP,
		pKeyQ));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetLabeledRSAPublicKey(
	PSTR pszLabel,
	BOOL blAppendLabel,
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetLabeledRSAPublicKey");

	if(F.GetLabeledRSAPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetLabeledRSAPublicKey(
		hModule,
		pszLabel, blAppendLabel,
		pParameters, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetLabeledECDSAPublicKey(
	PSTR pszLabel,
	BOOL blAppendLabel,
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetLabeledECDSAPublicKey");

	if(F.GetLabeledECDSAPublicKey == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetLabeledECDSAPublicKey(
		hModule,
		pszLabel, blAppendLabel,
		pParameters, pPublicKey));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::FindPublicKeyByID(
	UINT uiType,
	BOOL blAppendedLabel,
	PSTR pszSubLabel,
	PBYTE pbKeyID,
	UINT cbKeyID,
	PUINT puiType,
	PSTR pszAppendedLabel,
	PSTR pszPartialLabel)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::FindPublicKeyByID");

	if(F.FindPublicKeyByID == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	if(pszSubLabel == NULL)
		pszSubLabel = const_cast<PSTR>("");

	if(pszAppendedLabel == NULL &&
		pszPartialLabel == NULL)
	{
		return (dwError = G301_INTERNAL_ERROR);
	}

	CHAR	szAppendedLabel[G301_POINT_NAME_LENGTH +
			G301_DATA_LABEL_DELIMITER_LENGTH +
				G301_MAX_DATA_LABEL_LENGTH + 1],
		szPartialLabel[G301_MAX_DATA_LABEL_LENGTH + 1];

	if(pszAppendedLabel == NULL)
		pszAppendedLabel = szAppendedLabel;

	if(pszPartialLabel == NULL)
		pszPartialLabel = szPartialLabel;

	return (dwError = F.FindPublicKeyByID(
		hModule,
		uiType, blAppendedLabel, pszSubLabel,
		pbKeyID, cbKeyID,
		puiType, pszAppendedLabel, pszPartialLabel));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetInfo(
	PSTR pszName,
	PSTR pszSN,
	PSTR pszImageVersion,
	PDWORDLONG pdwlTotalConfigMemory,
	PDWORDLONG pdwlFreeConfigMemory)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetInfo");

	if(F.GetInfo == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetInfo(
		hModule, pszName, pszSN, pszImageVersion,
		pdwlTotalConfigMemory, pdwlFreeConfigMemory));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EnumData(
	BOOL blFirst,
	UINT uiType,
	BOOL blAppendedLabel,
	PSTR pszSubLabel,
	PUINT puiType,
	PSTR pszAppendedLabel,
	PSTR pszPartialLabel)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EnumData");

	if(F.EnumData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	if(pszSubLabel == NULL)
		pszSubLabel = const_cast<PSTR>("");

	if(pszAppendedLabel == NULL &&
		pszPartialLabel == NULL)
	{
		return (dwError = G301_INTERNAL_ERROR);
	}

	CHAR	szAppendedLabel[G301_POINT_NAME_LENGTH +
			G301_DATA_LABEL_DELIMITER_LENGTH +
				G301_MAX_DATA_LABEL_LENGTH + 1],
		szPartialLabel[G301_MAX_DATA_LABEL_LENGTH + 1];

	if(pszAppendedLabel == NULL)
		pszAppendedLabel = szAppendedLabel;

	if(pszPartialLabel == NULL)
		pszPartialLabel = szPartialLabel;

	return (dwError = F.EnumData(
		hModule, blFirst,
		uiType, blAppendedLabel, pszSubLabel,
		puiType, pszAppendedLabel, pszPartialLabel));
}

//------------------------------------------------------------------------------

PSTR WINAPI Gryada301::GetDataTypeDescr(
	UINT uiType,
	PSTR pszDescr)
{
	if(pszDescr == NULL)
		return NULL;

	switch(uiType)
	{
		case G301_PUBLIC_KEY_TYPE_DS:
			strcpy(pszDescr,
				G301_PUBLIC_KEY_TYPE_DS_DESCRIPTION);
			break;

		case G301_PUBLIC_KEY_TYPE_KEP:
			strcpy(pszDescr,
				G301_PUBLIC_KEY_TYPE_KEP_DESCRIPTION);
			break;

		case G301_PUBLIC_KEY_TYPE_RSA:
			strcpy(pszDescr,
				G301_PUBLIC_KEY_TYPE_RSA_DESCRIPTION);
			break;

		case G301_PUBLIC_KEY_TYPE_ECDSA:
			strcpy(pszDescr,
				G301_PUBLIC_KEY_TYPE_ECDSA_DESCRIPTION);
			break;

		case G301_KEYS_TYPE_DS:
			strcpy(pszDescr, G301_KEYS_TYPE_DS_DESCRIPTION);
			break;

		case G301_KEYS_TYPE_KEP:
			strcpy(pszDescr, G301_KEYS_TYPE_KEP_DESCRIPTION);
			break;

		case G301_KEYS_TYPE_RSA:
			strcpy(pszDescr, G301_KEYS_TYPE_RSA_DESCRIPTION);
			break;

		case G301_KEYS_TYPE_ECDSA:
			strcpy(pszDescr, G301_KEYS_TYPE_ECDSA_DESCRIPTION);
			break;

		case G301_DATA_TYPE_CLIENT:
			strcpy(pszDescr, G301_DATA_TYPE_CLIENT_DESCRIPTION);
			break;

		case G301_DATA_TYPE_MODULE:
			strcpy(pszDescr, G301_DATA_TYPE_MODULE_DESCRIPTION);
			break;

		case G301_KEYS_TYPE_SBOXES:
			strcpy(pszDescr, G301_KEYS_TYPE_SBOXES_DESCRIPTION);
			break;

		default:
			strcpy(pszDescr, "�� ����������");
			break;
	}

	return pszDescr;
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::EraseLabeledData(
	UINT uiType,
	PSTR pszLabel,
	BOOL blAppendLabel)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::EraseLabeledData");

	if(F.EraseLabeledData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	if((pszLabel == NULL ||
		strlen(pszLabel) == 0) &&
			blAppendLabel)
	{
		return (dwError = G301_INTERNAL_ERROR);
	}

	if(pszLabel == NULL)
		pszLabel = const_cast<PSTR>("");

	return (dwError = F.EraseLabeledData(
		hModule, uiType,
		pszLabel, blAppendLabel));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::RenameData(
	UINT uiType,
	PSTR pszLabel,
	BOOL blAppendLabel,
	PSTR pszNewLabel)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::RenameData");

	if(F.RenameData == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE11_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if((pszLabel == NULL ||
			strlen(pszLabel) == 0) ||
		(pszNewLabel == NULL ||
			strlen(pszNewLabel) == 0))
	{
		return (dwError = G301_INTERNAL_ERROR);
	}

	return (dwError = F.RenameData(
		hModule, uiType,
		pszLabel, blAppendLabel, pszNewLabel));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetClientInfo(
	PG301_CLIENT_INFO pClientInfo)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetClientInfo");

	if(F.GetClientInfo == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return dwError;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return dwError;

	return (dwError = F.GetClientInfo(
		hModule, pClientInfo));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::GetClientSecurity(
	PG301_CLIENT_SECURITY pSecurity)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::GetClientSecurity");

	if(F.GetClientSecurity == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE9_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.GetClientSecurity(
		hModule,
		pSecurity));
}

//------------------------------------------------------------------------------

DWORD WINAPI Gryada301::SetClientSecurity(
	PG301_CLIENT_SECURITY pSecurity)
{
	LOGGABLE_RESULT(dwError,
		"Gryada301::SetClientSecurity");

	if(F.SetClientSecurity == NULL)
		return (dwError = G301_ERROR_BAD_REQUEST);

	if(hModule == NULL)
		return (dwError = G301_INTERNAL_ERROR);

	if(GetImageVersion() < G301_IMAGE_COMPATIBLE9_VERSION)
		return (dwError = G301_ERROR_BAD_REQUEST);

	return (dwError = F.SetClientSecurity(
		hModule,
		pSecurity));
}

//------------------------------------------------------------------------------

BOOL WINAPI Gryada301::StringToImageVersion(
	PSTR pszVersion,
	PUINT puiVersion)
{
	if(strlen(pszVersion) < G301_IMAGE_MIN_VERSION_LENGTH ||
		strlen(pszVersion) > G301_IMAGE_VERSION_LENGTH)
	{
		return FALSE;
	}

	UINT	uiVersion, uiSubVersion1,
		uiSubVersion2, uiSubVersion3;

	if (sscanf(pszVersion, G301_IMAGE_VERSION_FORMAT,
		&uiVersion, &uiSubVersion1,
		&uiSubVersion2, &uiSubVersion3) != 4)
	{
		return FALSE;
	}

	*puiVersion = (uiVersion << 24) |
		(uiSubVersion1 << 16) | (uiSubVersion2 << 8) |
		uiSubVersion3;

	if(*puiVersion < G301_IMAGE_MIN_VERSION ||
		*puiVersion > G301_IMAGE_MAX_VERSION)
	{
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------------------

UINT WINAPI Gryada301::GetImageVersion()
{
	if(hModule == NULL)
		return 0;

	if(uiImageVersion != 0)
		return uiImageVersion;

	DWORD	dwError;

	dwError = IsRevision1();
	if(dwError != G301_SUCCESS)
		return 0;

	dwError = IsCompatible8();
	if(dwError != G301_SUCCESS)
		return 0;

	CHAR	szImageVersion[G301_IMAGE_VERSION_LENGTH + 1];

	dwError = GetInfo(NULL, NULL,
		szImageVersion, NULL, NULL);
	if(dwError == G301_SUCCESS)
	{
		if(!StringToImageVersion(szImageVersion,
			&uiImageVersion))
		{
			uiImageVersion = 0;
		}
	}
	else
		uiImageVersion = 0;

	return uiImageVersion;
}

//==============================================================================

ICSPHardware* WINAPI Gryada301::GetCSPInterface()
{
	if(pCSPInterface == NULL)
	{
		pCSPInterface = (ICSPHardware*)(new
			CSPHardwareImplementationGryada301(this));
	}

	return pCSPInterface;
}

//------------------------------------------------------------------------------

ICSPHardwareRNG* WINAPI Gryada301::GetHRNGInterface()
{
	if(pHRNGInterface == NULL)
	{
		pHRNGInterface = (ICSPHardwareRNG*)(new
			CSPHardwareRNGImplementationGryada301(this));
	}

	return pHRNGInterface;
}

//------------------------------------------------------------------------------

BOOL Gryada301::GetModulePath(
	HMODULE hModule,
	PSTR pszPath)
{
	if (GetModuleFileNameA(hModule,
			pszPath, MAX_PATH * 4 + 1) == 0 ||
		strrchr(pszPath, '\\') == NULL)
	{
		return FALSE;
	}

	*strrchr(pszPath, '\\') = '\0';
	strcat(pszPath, "\\");

	return TRUE;
}

//------------------------------------------------------------------------------

CSPHardwareImplementationGryada301::CSPHardwareImplementationGryada301(
	Gryada301 *pGryada301)
{
	this->pGryada301 = pGryada301;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::GenerateDSKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	DWORD dwError;

	if(pKeyQ == NULL)
	{
		if(pParameterEC->dwM == 0)
		{
			switch(pParameterP->dwBits)
			{
			case 5:
				if (pGryada301->IsCompatible6() !=
					G301_SUCCESS ||
					pGryada301->SetUseDSKeysAsKEP(
					FALSE) != G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case 6:
				if (pGryada301->IsCompatible6() !=
					G301_SUCCESS ||
					pGryada301->SetUseDSKeysAsKEP(
					TRUE) != G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case CSP_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY:
				if (pGryada301->IsRevision1() !=
					G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case CSP_COMPATIBLE_LEVEL_HARDWARE_DS_COUPLE:
				if(pGryada301->F.CoupleDSMakeComponentS == NULL)
					return FALSE;

				if(pGryada301->GetImageVersion() <
					G301_IMAGE_COMPATIBLE5_VERSION)
				{
					return FALSE;
				}
				break;

			case CSP_COMPATIBLE_LEVEL_HARDWARE_SIGN_DSTU_HASH:
				if(pGryada301->F.SignDSTUHash == NULL)
					return FALSE;

				if(pGryada301->GetImageVersion() <
					G301_IMAGE_COMPATIBLE10_VERSION)
				{
					return FALSE;
				}
				break;

			case CSP_COMPATIBLE_LEVEL_HARDWARE_DSTU7624_WRAP_KEY:
				if(pGryada301->F.DSTUWrapSharedKey == NULL)
					return FALSE;

				if(pGryada301->GetImageVersion() <
					G301_IMAGE_COMPATIBLE10_VERSION)
				{
					return FALSE;
				}
				break;

			default:
				return FALSE;
			}
		}

		return TRUE;
	}

	dwError = pGryada301->GenerateKeys(TRUE, pParameterEC, pParameterP,
		pKeyQ);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::GenerateKEPKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	DWORD dwError;

	if(pKeyQ == NULL)
	{
		if(pParameterEC->dwM == 0)
		{
			switch(pParameterP->dwBits)
			{
			case 2:
				if(pGryada301->IsCompatible2() !=
					G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case 3:
				if(pGryada301->IsCompatible3() !=
					G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case 5:
				if(pGryada301->IsCompatible6() !=
					G301_SUCCESS ||
					pGryada301->SetUseDSKeysAsKEP(
					FALSE) != G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case 6:
				if(pGryada301->IsCompatible6() !=
					G301_SUCCESS ||
					pGryada301->SetUseDSKeysAsKEP(
					TRUE) != G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case CSP_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY:
				if(pGryada301->IsRevision1() !=
					G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			default:
				return FALSE;
			}
		}

		return TRUE;
	}

	dwError = pGryada301->GenerateKeys(FALSE,
		pParameterEC, pParameterP, pKeyQ);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::SignHash(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST34311_HASH pHash,
	DSTU4145_SIGNATURE pSignature)
{
	DWORD dwError;

	if(pHash == NULL && pSignature == NULL)
		return FALSE;

	if(pParameterEC->dwCF == 0xFFFFFFFF)
	{
		pParameterEC->dwCF = 2;

		DSTU4145_KEY_Q KeyQ;

		CopyMemory(KeyQ, ((PBYTE) pParameterEC) +
			sizeof(DSTU4145_PARAMETER_EC), sizeof(DSTU4145_KEY_Q));

		dwError = pGryada301->VerifySign(pHash,
			pParameterEC, pParameterP, KeyQ, pSignature);
		if(dwError != G301_SUCCESS)
			return FALSE;

		return TRUE;
	}

	if(pParameterEC->dwCF == (UINT) (-5))
	{
		dwError = pGryada301->SignHashKEP(pHash, pSignature);
		if(dwError != G301_SUCCESS)
			return FALSE;

		return TRUE;
	}

	dwError = pGryada301->SignHash(pHash, pSignature);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::ProtectSharedData(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_MAC pMAC)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterEC);
	UNREFERENCED_PARAMETER(pParameterP);

	if(pMAC == NULL && dwData == sizeof(GOST28147_KEY))
	{
		dwError = pGryada301->MakeSharedKey(pKeyQb, pData,
			(PUINT) pbData);
		if(dwError != G301_SUCCESS)
			return FALSE;

		return TRUE;
	}

	dwError = pGryada301->ProtectSharedData(pKeyQb, pData, pbData,
		(WORD) dwData, pMAC);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::UnprotectSharedData(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQb,
	ECDH_EXTENDED_DATA pData,
	PBYTE pbData,
	DWORD dwData,
	GOST28147_MAC pMAC)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterEC);
	UNREFERENCED_PARAMETER(pParameterP);

	dwError = pGryada301->UnprotectSharedData(pKeyQb, pData, pbData,
		(WORD) dwData, pMAC);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::CheckDSKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterP);

	dwError = pGryada301->CheckPublicKey(TRUE, pKeyQ);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::CheckKEPKeys(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterP);

	dwError = pGryada301->CheckPublicKey(FALSE, pKeyQ);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::SetSBoxes(
	GOST28147_COMPRESSED_SBOX pEncryptionSBox,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST28147_COMPRESSED_SBOX pECDHSBox,
	GOST28147_COMPRESSED_SBOX pPRNGSBox)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pEncryptionSBox);
	UNREFERENCED_PARAMETER(pHashSBox);

	dwError = pGryada301->SetSBoxes(pPRNGSBox, pECDHSBox);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::HashKEPKey(
	GOST34311_HASH pHash)
{
	DWORD dwError;

	dwError = pGryada301->HashPrivateKey(pHash);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

#ifdef CSP_ECDH_UA
BOOL WINAPI CSPHardwareImplementationGryada301::WrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_KEY pKey,
	GOST28147_WRAPED_KEY pWrappedKey)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterP);
	UNREFERENCED_PARAMETER(pHashSBox);
	UNREFERENCED_PARAMETER(pWrapSBox);

	dwError = pGryada301->WrapSharedKey(pParameterEC->dwM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo,
		pKey, pWrappedKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::UnwrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQb,
	BOOL blCofactorMethod,
	PBYTE pbSharedInfo,
	DWORD dwSharedInfo,
	GOST28147_COMPRESSED_SBOX pHashSBox,
	GOST28147_COMPRESSED_SBOX pWrapSBox,
	GOST28147_WRAPED_KEY pWrappedKey,
	GOST28147_KEY pKey)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterP);
	UNREFERENCED_PARAMETER(pHashSBox);
	UNREFERENCED_PARAMETER(pWrapSBox);

	dwError = pGryada301->UnwrapSharedKey(pParameterEC->dwM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo,
		pWrappedKey, pKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}
#endif // CSP_ECDH_UA

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::GetEncryptionSBox(
	GOST28147_EXTENDED_SBOX pSBox)
{
	UNREFERENCED_PARAMETER(pSBox);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::InitializeEncryptData(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV,
	BOOL blGenerateKeyAndIV)
{
	UNREFERENCED_PARAMETER(pSBox);
	UNREFERENCED_PARAMETER(pKey);
	UNREFERENCED_PARAMETER(pIV);
	UNREFERENCED_PARAMETER(blGenerateKeyAndIV);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::ContinueEncryptData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_KEY pKey)
{
	UNREFERENCED_PARAMETER(pbData);
	UNREFERENCED_PARAMETER(dwData);
	UNREFERENCED_PARAMETER(pKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::ContinueEncryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_KEY pKey,
	DWORDLONG dwlDataOffset)
{
	UNREFERENCED_PARAMETER(pbData);
	UNREFERENCED_PARAMETER(dwData);
	UNREFERENCED_PARAMETER(pKey);
	UNREFERENCED_PARAMETER(dwlDataOffset);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::FinalizeEncryptData(
	GOST28147_KEY pKey)
{
	UNREFERENCED_PARAMETER(pKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::InitializeDecryptData(
	GOST28147_COMPRESSED_SBOX pSBox,
	GOST28147_KEY pKey,
	GOST28147_IV pIV)
{
	UNREFERENCED_PARAMETER(pSBox);
	UNREFERENCED_PARAMETER(pKey);
	UNREFERENCED_PARAMETER(pIV);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::ContinueDecryptData(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_KEY pKey)
{
	UNREFERENCED_PARAMETER(pbData);
	UNREFERENCED_PARAMETER(dwData);
	UNREFERENCED_PARAMETER(pKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::ContinueDecryptDataByOffset(
	PBYTE pbData,
	DWORD dwData,
	GOST28147_KEY pKey,
	DWORDLONG dwlDataOffset)
{
	UNREFERENCED_PARAMETER(pbData);
	UNREFERENCED_PARAMETER(dwData);
	UNREFERENCED_PARAMETER(pKey);
	UNREFERENCED_PARAMETER(dwlDataOffset);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::FinalizeDecryptData(
	GOST28147_KEY pKey)
{
	UNREFERENCED_PARAMETER(pKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::RecoverDSPublicKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterEC);
	UNREFERENCED_PARAMETER(pParameterP);

	dwError = pGryada301->GetPublicKey(TRUE, pKeyQ);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::RecoverKEPPublicKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_KEY_Q pKeyQ)
{
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterEC);
	UNREFERENCED_PARAMETER(pParameterP);

	dwError = pGryada301->GetPublicKey(FALSE, pKeyQ);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::CoupleDSMakeComponentS(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DSTU4145_NUMBER	pKeyK,
	DSTU4145_NUMBER	pCommonComponentR,
	DSTU4145_NUMBER	pComponentS)
{
	DWORD dwError;

	dwError = pGryada301->CoupleDSMakeComponentS(
		pParameterEC, pParameterP,
		pKeyK, pCommonComponentR,
		pComponentS);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::SignDSTUHash(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	DWORD dwHash,
	DSTU7564_HASH pHash,
	DSTU4145_SIGNATURE pSignature)
{
	DWORD dwError;

	if(pHash == NULL && pSignature == NULL)
		return FALSE;

	if(pParameterEC->dwCF == 0xFFFFFFFF)
	{
		pParameterEC->dwCF = 2;

		DSTU4145_KEY_Q KeyQ;

		CopyMemory(KeyQ, ((PBYTE) pParameterEC) +
			sizeof(DSTU4145_PARAMETER_EC), sizeof(DSTU4145_KEY_Q));

		dwError = pGryada301->VerifyDSTUSign(dwHash, pHash,
			pParameterEC, pParameterP, KeyQ, pSignature);
		if(dwError != G301_SUCCESS)
			return FALSE;

		return TRUE;
	}

	if(pParameterEC->dwCF == (UINT) (-5))
	{
		dwError = pGryada301->SignDSTUHashKEP(dwHash, pHash,
			pSignature);
		if(dwError != G301_SUCCESS)
			return FALSE;

		return TRUE;
	}

	dwError = pGryada301->SignDSTUHash(dwHash, pHash, pSignature);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::DSTU7624WrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
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
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterP);
	UNREFERENCED_PARAMETER(pWrapSBox);

	dwError = pGryada301->DSTUWrapSharedKey(pParameterEC->dwM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo,
		pKey, dwKey, pWrappedKey, dwWrappedKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareImplementationGryada301::DSTU7624UnwrapSharedKey(
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
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
	DWORD dwError;

	UNREFERENCED_PARAMETER(pParameterP);
	UNREFERENCED_PARAMETER(pWrapSBox);

	dwError = pGryada301->DSTUUnwrapSharedKey(pParameterEC->dwM,
		pKeyQb, blCofactorMethod,
		pbSharedInfo, dwSharedInfo,
		pWrappedKey, dwWrappedKey, pKey, dwKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//==============================================================================

CSPHardwareRNGImplementationGryada301::CSPHardwareRNGImplementationGryada301(
	Gryada301 *pGryada301)
{
	this->pGryada301 = pGryada301;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPHardwareRNGImplementationGryada301::GenerateSequence(
	PBYTE pbSequence,
	DWORD dwSequence)
{
	DWORD dwError;

	dwError = pGryada301->GenerateRNSequence(pbSequence, dwSequence);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//============================================================================

ICSPIHardware* WINAPI Gryada301::GetCSPIInterface()
{
	if(pCSPIInterface == NULL)
	{
		pCSPIInterface = (ICSPIHardware*)(new
			CSPIHardwareImplementationGryada301(this));
	}

	return pCSPIInterface;
}

//------------------------------------------------------------------------------

CSPIHardwareImplementationGryada301::CSPIHardwareImplementationGryada301(
	Gryada301 *pGryada301)
{
	this->pGryada301 = pGryada301;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::SetSBoxes(
	GOST28147_COMPRESSED_SBOX pPRNGSBox)
{
	UNREFERENCED_PARAMETER(pPRNGSBox);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::RSAGenerateKeys(
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey)
{
	DWORD dwError;

	if(pPublicKey == NULL)
	{
		if(pParameters->dwHash == 0)
		{
			switch(pParameters->dwBits)
			{
			case CSPI_COMPATIBLE_LEVEL_HARDWARE_RECOVER_PUBLIC_KEY:
			case CSPI_COMPATIBLE_LEVEL_HARDWARE_RSA_DECRYPT_DATA:
				if (pGryada301->IsRevision1() !=
					G301_SUCCESS)
				{
					return FALSE;
				}
				break;

			case CSPI_COMPATIBLE_LEVEL_HARDWARE_ECDSA_COUPLE:
				if(pGryada301->
					F.ECDSACouplePart2Step == NULL ||
						pGryada301->
					F.MakeECDSACoupleCommonPublicKey ==
						NULL)
				{
					return FALSE;
				}

				if(pGryada301->GetImageVersion() <
					G301_IMAGE_COMPATIBLE8_VERSION)
				{
					return FALSE;
				}
				break;

			case CSPI_COMPATIBLE_LEVEL_HARDWARE_RSA_PSS_SIGN:
				if(pGryada301->F.RSASignHashEx == NULL)
					return FALSE;

				if(pGryada301->GetImageVersion() <
					G301_IMAGE_COMPATIBLE10_VERSION)
				{
					return FALSE;
				}
				break;

			default:
				return FALSE;
			}
		}

		return TRUE;
	}

	dwError = pGryada301->GenerateRSAKeys(pParameters, pPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::RSASignHash(
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	RSA_SIGNATURE pSignature)
{
	DWORD dwError;

	if((pGryada301->F.RSASignHashEx == NULL) ||
		(pGryada301->GetImageVersion() <
			G301_IMAGE_COMPATIBLE10_VERSION))
	{
		dwError = pGryada301->RSASignHash(pHash, pSignature);
		if(dwError != G301_SUCCESS)
			return FALSE;
	}
	else
	{
		dwError = pGryada301->RSASignHashEx(RSA_PKCS1_V15_VERSION,
			pParameters->dwHash / 8,
			pHash, pSignature);
		if(dwError != G301_SUCCESS)
			return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::RSACheckKeys(
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY	pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->CheckRSAPublicKey(pPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::DSASignHash(
	DWORD dwHash,
	SHA_HASH pHash,
	PDSA_PARAMETERS pParameters,
	PDSA_SIGNATURE pSignature)
{
	UNREFERENCED_PARAMETER(dwHash);
	UNREFERENCED_PARAMETER(pHash);
	UNREFERENCED_PARAMETER(pParameters);
	UNREFERENCED_PARAMETER(pSignature);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::DSAGenerateKeys(
	PDSA_PARAMETERS	pParameters,
	PDSA_PUBLIC_KEY pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);
	UNREFERENCED_PARAMETER(pPublicKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::DSACheckKeys(
	PDSA_PARAMETERS	pParameters,
	PDSA_PUBLIC_KEY	pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);
	UNREFERENCED_PARAMETER(pPublicKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDSASignHash(
	DWORD dwHash,
	SHA_HASH pHash,
	PECDSA_PARAMETERS pParameters,
	PECDSA_SIGNATURE pSignature)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->ECDSASignHash(dwHash, pHash,
		pSignature);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDSAGenerateKeys(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey)
{
	DWORD dwError;

	if(pPublicKey == NULL)
		return TRUE;

	dwError = pGryada301->GenerateECDSAKeys(pParameters,
		pPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDSACheckKeys(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->CheckECDSAPublicKey(pPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDHCalculateSharedSecret(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pRecipientPublicKey,
	ECDSA_NUMBER pSharedSecret)
{
	DWORD dwError;

	dwError = pGryada301->ECDHCalculateSharedSecret(pParameters,
		pRecipientPublicKey, pSharedSecret);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::DHCalculateSharedSecret(
	PDSA_PARAMETERS	pParameters,
	DSA_NUMBER pRecipientPublicKey,
	DSA_NUMBER pSharedSecret)
{
	UNREFERENCED_PARAMETER(pParameters);
	UNREFERENCED_PARAMETER(pRecipientPublicKey);
	UNREFERENCED_PARAMETER(pSharedSecret);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::RSARecoverPublicKey(
	PRSA_PARAMETERS pParameters,
	PRSA_PUBLIC_KEY pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->GetRSAPublicKey(pPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::DSARecoverPublicKey(
	PDSA_PARAMETERS	pParameters,
	PDSA_PUBLIC_KEY	pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);
	UNREFERENCED_PARAMETER(pPublicKey);

	return FALSE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDSARecoverPublicKey(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->GetECDSAPublicKey(pPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::RSADecryptData(
	PBYTE pbData,
	PDWORD pdwData,
	PRSA_PARAMETERS pParameters,
	BOOL blUnpadData)
{
	DWORD dwError;

	dwError = pGryada301->RSADecryptData(pbData, pdwData,
		pParameters, blUnpadData);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::RSAPSSSignHash(
	SHA_HASH pHash,
	PRSA_PARAMETERS pParameters,
	RSA_SIGNATURE pSignature)
{
	if(pGryada301->GetImageVersion() < G301_IMAGE_COMPATIBLE10_VERSION)
		return FALSE;

	DWORD dwError;

	dwError = pGryada301->RSASignHashEx(RSA_PKCS1_V21_VERSION,
		pParameters->dwHash / 8,
		pHash, pSignature);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDSACouplePart2Step(
	DWORD dwHash,
	SHA_HASH pHash,
	RSA_NUMBER pPaillierPublicKey,
	PECDSA_PARAMETERS pParameters,
	ECDSA_ENCODED_POINT pComponentR1,
	PAILLIER_NUMBER pEncryptedPrivateKey1,
	ECDSA_NUMBER pCommonComponentR,
	PAILLIER_NUMBER pComponentS2)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->ECDSACouplePart2Step(
		dwHash, pHash,
		pPaillierPublicKey, pComponentR1,
		pEncryptedPrivateKey1,
		pCommonComponentR, pComponentS2);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL WINAPI CSPIHardwareImplementationGryada301::ECDSACoupleMakeCommonPublicKey(
	PECDSA_PARAMETERS pParameters,
	ECDSA_KEY_Q pPublicKeyB,
	ECDSA_KEY_Q pCommonPublicKey)
{
	UNREFERENCED_PARAMETER(pParameters);

	DWORD dwError;

	dwError = pGryada301->MakeECDSACoupleCommonPublicKey(
		pPublicKeyB,
		pCommonPublicKey);
	if(dwError != G301_SUCCESS)
		return FALSE;

	return TRUE;
}

//==============================================================================

