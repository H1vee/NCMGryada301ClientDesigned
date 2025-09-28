#ifndef CSP_PARAMETERS_H
#define CSP_PARAMETERS_H

//======================================================================================================================

class CSP;

//======================================================================================================================

#include "CSPBase.h"

//======================================================================================================================

#ifdef CSP_PARAMETERS_EXT
	#define CSP_PARAMETERS_MAX_NAME_LENGTH	128
	#define CSP_PARAMETERS_MAX_OID_LENGTH	128
#endif // CSP_PARAMETERS_EXT

//----------------------------------------------------------------------------------------------------------------------

#define DSTUS_SUB_SBOX_LENGTH 256
#define DSTUS_SUB_SBOX_COUNT 4

typedef BYTE DSTUS_SUB_SBOX[DSTUS_SUB_SBOX_LENGTH];
typedef BYTE DSTUS_SBOX[DSTUS_SUB_SBOX_COUNT]
	[DSTUS_SUB_SBOX_LENGTH];

#define DSTUS_SBOX_MIN_NONLINEARITY 100 // 102

//======================================================================================================================

class CSPParameters
{
private:
	CSP		*m_pCSP;

private:
	VOID	GOST28147(
			FILE						*pFile,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	VOID	DSTU4145(
			FILE 						*pFile,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP);

private:
	BOOL	OpenFile(
			PCSTR						pszFileName,
			DWORD						dwDesiredAccess,
			DWORD						dwShareMode,
			DWORD						dwCreationDisposition,
			DWORD						dwFlagsAndAttributes,
			PHANDLE						phFile);

	BOOL	ReadDataFromFile(
			PCHAR 						pcFileName,
			PVOID 						pvData,
			DWORD 						cbData);
	BOOL	WriteDataToFile(
			PCHAR 						pcFileName,
			PVOID 						pvData,
			DWORD 						cbData);

	BOOL	IsDataPasswordProtected();
	BOOL	ReadPasswordProtectedDataFromFile(
			PCHAR 						pcFileName,
			PVOID 						pvData,
			DWORD 						cbData);
	BOOL	WritePasswordProtectedDataToFile(
			PCHAR 						pcFileName,
			PVOID 						pvData,
			DWORD 						cbData);
	BOOL	ReadDSTU7624PasswordProtectedDataFromFile(
			PCHAR						pcFileName,
			PVOID						pvData,
			DWORD						cbData);
	BOOL	WriteDSTU7624PasswordProtectedDataToFile(
			PCHAR						pcFileName,
			PVOID						pvData,
			DWORD						cbData);

	BOOL	ReadDataFromFile(
			PCHAR						pcFileName,
			PBYTE						pbData,
			PDWORD						pcbData);
	BOOL	UnprotectDSTU7624PasswordProtectedData(
			PBYTE						pbData,
			DWORD						cbData,
			PBYTE						*ppbUnprotectedData,
			PDWORD						pcbData);

private:
	BOOL	GOST28147ExternalFile(
			FILE						*pFile,
			GOST28147_COMPRESSED_SBOX 	pSBox);

private:
	VOID	DSTUSBoxesPerformFWHT(
			DSTUS_SUB_SBOX 				pTruthTable,
			PINT 						pSpectre);
	INT 	DSTUSBoxesGetNonlinearity(
			DSTUS_SUB_SBOX 				pSBox);
	BOOL 	DSTUSBoxesCheckBijectivity(
			DSTUS_SUB_SBOX 				pSBox);

	BOOL	DSTU7624Check(
			DSTU7624_SBOX				pSBox);
	BOOL	DSTU8845Check(
			DSTU8845_SBOX				pSBox);
			
public:
	CSPParameters();
	~CSPParameters();

public:
	virtual BOOL 	WINAPI GOST28147(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI DSTU4145(
			PCHAR 						pcFileName,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI ECDH(
			PCHAR 						pcFileName,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI DSTU4145Standart(
			BOOL 						bPolinomial,
			DWORD 						dwID,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP);

	virtual VOID 	WINAPI SetCSP(
			CSP 						*pCSP);

	virtual BOOL 	WINAPI GOST28147Protected(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI GOST28147Hashed(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI DSTU4145Hashed(
			PCHAR 						pcFileName,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI ECDHProtected(
			PCHAR 						pcFileName,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI GOST28147SaveProtected(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI GOST28147SaveHashed(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI DSTU4145SaveHashed(
			PCHAR 						pcFileName,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI ECDHSaveProtected(
			PCHAR 						pcFileName,
			PDSTU4145_PARAMETER_EC 		pParameterEC,
			PDSTU4145_PARAMETER_P 		pParameterP,
			GOST28147_COMPRESSED_SBOX 	pSBox);

#ifdef CSP_PARAMETERS_EXT
	virtual BOOL 	WINAPI DSTU4145StandartEnum(
			BOOL 						bPolinomial,
			DWORD 						dwID,
			PDWORD						pdwBits,
			PCHAR						pszName,
			PCHAR						pszOID);

	virtual BOOL 	WINAPI DSTU4145StandartFindByOID(
			PCHAR						pszOID,
			PBOOL 						pbPolinomial,
			PDWORD 						pdwID);

	virtual BOOL 	WINAPI GOST28147FixedEnum(
			DWORD						dwID,
			GOST28147_COMPRESSED_SBOX	pSBox);
#endif // CSP_PARAMETERS_EXT

	virtual BOOL 	WINAPI GOST28147External(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL	WINAPI GOST28147SaveExternal(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL	WINAPI DSTU4145SaveDSTU7564Hashed(
			PCHAR						pcFileName,
			PDSTU4145_PARAMETER_EC		pParameterEC,
			PDSTU4145_PARAMETER_P		pParameterP);

	virtual BOOL	WINAPI DSTU7624Protected(
			PCHAR						pcFileName,
			DSTU7624_SBOX				pSBox);

	virtual BOOL	WINAPI DSTU7624SaveProtected(
			PSTR						pszFileName,
			DSTU7624_SBOX				pSBox);

	virtual BOOL	WINAPI DSTU8845SaveProtected(
			PSTR						pszFileName,
			DSTU8845_SBOX				pSBox);

	virtual BOOL 	WINAPI DSTU7624External(
			PSTR						pszFileName,
			DSTU7624_SBOX				pSBox);

	virtual BOOL 	WINAPI DSTU8845External(
			PSTR						pszFileName,
			DSTU8845_SBOX				pSBox);

	virtual BOOL	WINAPI IsDefaultDSTU7624(
			DSTU7624_SBOX				pSBox);

	virtual BOOL	WINAPI IsDefaultDSTU8845(
			DSTU8845_SBOX				pSBox);

	virtual BOOL	WINAPI DSTU4145DHashed(
			PCHAR						pcFileName,
			PBYTE						pbParameters,
			PDWORD						pdwParameters);

	virtual BOOL	WINAPI DSTU4145DSaveDSTU7564Hashed(
			PCHAR						pcFileName,
			PBYTE						pbParameters,
			DWORD						dwParameters);
};

//======================================================================================================================

#include "CSP.h"

//======================================================================================================================

#endif // CSP_PARAMETERS_H
