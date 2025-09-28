#ifndef CSPI_PARAMETERS_H
#define CSPI_PARAMETERS_H

//======================================================================================================================

class CSPI;

//======================================================================================================================

#include "CSPIBase.h"

//----------------------------------------------------------------------------------------------------------------------

#define CSPI_PARAMETERS_MAX_NAME_LENGTH	128
#define CSPI_PARAMETERS_MAX_OID_LENGTH	128

//======================================================================================================================

class CSPIParameters
{
private:
	CSPI		*m_pCSP;

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

private:
	VOID	GOST28147(
			FILE						*pFile,
			GOST28147_COMPRESSED_SBOX 	pSBox);

public:
	CSPIParameters();
	~CSPIParameters();

public:
	virtual BOOL 	WINAPI GOST28147(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual VOID 	WINAPI SetCSP(
			CSPI 						*pCSP);

	virtual BOOL 	WINAPI GOST28147Protected(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI GOST28147Hashed(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI GOST28147SaveProtected(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI GOST28147SaveHashed(
			PCHAR 						pcFileName,
			GOST28147_COMPRESSED_SBOX 	pSBox);

	virtual BOOL 	WINAPI RSAHashed(
			PCHAR 						pcFileName,
			PRSA_PARAMETERS				pParameters);

	virtual BOOL 	WINAPI RSASaveHashed(
			PCHAR 						pcFileName,
			PRSA_PARAMETERS				pParameters);

	virtual BOOL 	WINAPI RSAFixed(
			DWORD 						dwID,
			PRSA_PARAMETERS				pParameters);

	virtual BOOL	WINAPI RSAFixedEnum(
			DWORD 						dwID,
			PDWORD						pdwBits,
			PDWORD						pdwHash,
			PSTR						pszName,
			PSTR						pszOID);

	virtual BOOL 	WINAPI DSAHashed(
			PCHAR 						pcFileName,
			PDSA_PARAMETERS				pParameters);

	virtual BOOL 	WINAPI DSASaveHashed(
			PCHAR 						pcFileName,
			PDSA_PARAMETERS				pParameters);

	virtual BOOL	WINAPI DSAFixed(
			DWORD 						dwID,
			PDSA_PARAMETERS				pParameters,
			PDWORD						pdwHash);

	virtual BOOL	WINAPI DSAFixedEnum(
			DWORD 						dwID,
			PDWORD						pdwBits,
			PDWORD						pdwHash,
			PSTR						pszName,
			PSTR						pszOID);

	virtual BOOL	WINAPI ECDSAHashed(
			PCHAR						pcFileName,
			PECDSA_PARAMETERS_EX		pParameters);

	virtual BOOL	WINAPI ECDSASaveHashed(
			PCHAR						pcFileName,
			PECDSA_PARAMETERS_EX		pParameters);

	virtual BOOL	WINAPI ECDSAFixed(
			DWORD						dwID,
			PECDSA_PARAMETERS_EX		pParameters);

	virtual BOOL	WINAPI ECDSAFixedEnum(
			DWORD						dwID,
			PDWORD						pdwBits,
			PDWORD						pdwHash,
			PSTR						pszName,
			PSTR						pszOID);

	virtual BOOL	WINAPI ECDSAFixedFindByOID(
			PSTR						pszOID,
			PDWORD						pdwID);
};

//======================================================================================================================

#include "CSPI.h"

//======================================================================================================================

#endif // CSPI_PARAMETERS_H
