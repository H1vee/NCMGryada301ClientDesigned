//======================================================================================================================

#include "CSPParameters.h"

//======================================================================================================================

#define CSP_PARAMETERS_MAX_DATA_SIZE 4096

//======================================================================================================================

typedef struct
{
	GOST28147_COMPRESSED_SBOX SBox;
	GOST28147_BLOCK DataAligment;
	UINT dwDataAligment;
	GOST28147_MAC MAC;
} CSP_GOST28147_PROTECTED_SBOX, *PCSP_GOST28147_PROTECTED_SBOX;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	GOST28147_COMPRESSED_SBOX SBox;
	GOST34311_HASH Hash;
} CSP_GOST28147_HASHED_SBOX, *PCSP_GOST28147_HASHED_SBOX;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	DSTU4145_PARAMETER_EC ParameterEC;
	DSTU4145_PARAMETER_P ParameterP;
	GOST28147_COMPRESSED_SBOX SBox;
	GOST34311_HASH Hash;
} CSP_DSTU4145_HASHED_PARAMETERS,
*PCSP_DSTU4145_HASHED_PARAMETERS;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	DSTU4145_PARAMETER_EC ParameterEC;
	DSTU4145_PARAMETER_P ParameterP;
	BYTE Hash[DSTU7564_HASH_256_LENGTH];
} CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS,
*PCSP_DSTU4145_DSTU7564_HASHED_PARAMETERS;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	DSTU4145_PARAMETER_EC ParameterEC;
	DSTU4145_PARAMETER_P ParameterP;
	GOST28147_COMPRESSED_SBOX SBox;
	GOST28147_BLOCK DataAligment;
	UINT dwDataAligment;
	GOST28147_MAC MAC;
} CSP_DSTU4145_PROTECTED_PARAMETERS, *PCSP_DSTU4145_PROTECTED_PARAMETERS;

//----------------------------------------------------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct
{
	DSTU7624_SBOX SBox;
	DSTU7624_SBOX InverseSBox;
	UINT uiCRC;
} DSTU7624_EXTERNAL_SBOX, *PDSTU7624_EXTERNAL_SBOX;

//----------------------------------------------------------------------------------------------------------------------

typedef struct
{
	DSTU7624_SBOX SBox;
	DSTU7624_SBOX InverseSBox;
	UINT uiCRC;
} DSTU8845_EXTERNAL_SBOX, *PDSTU8845_EXTERNAL_SBOX;
#pragma pack(pop)

//======================================================================================================================

#ifdef CSP_SBOX_UA

static GOST28147_COMPRESSED_SBOX EncryptParametersSBox =
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

static GOST28147_COMPRESSED_SBOX EncryptParametersSBox =
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

//----------------------------------------------------------------------------------------------------------------------

static GOST28147_KEY EncryptParametersKey =
{
	0x654CF7D4, 0xAEF2D212, 0xDBD1B9E5, 0xC1C9FA34,
	0x864690C5, 0x3C9B1513, 0x7F936DC2, 0x83F66DA4
};

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_SBOX_UA

static GOST28147_COMPRESSED_SBOX HashParametersSBox =
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

static GOST28147_COMPRESSED_SBOX HashParametersSBox =
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

//----------------------------------------------------------------------------------------------------------------------

static GOST34311_HASH InitialHash =
{
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000
};

//----------------------------------------------------------------------------------------------------------------------

static BYTE DSTU7624EncryptParametersKey[
	DSTU7624_KEY_256_LENGTH] =
{
	0xD5, 0xAE, 0xC8, 0x8B, 0xAD, 0xFC, 0x38, 0x65,
	0x24, 0x25, 0x92, 0x01, 0x83, 0xF0, 0x16, 0xE1,
	0x68, 0xE5, 0xD5, 0x6D, 0xB8, 0x89, 0x05, 0xD9,
	0x51, 0x22, 0x82, 0x6E, 0x10, 0xA0, 0x5E, 0xEF
};

//----------------------------------------------------------------------------------------------------------------------

static DSTU7624_SBOX DSTU7624DefaultSBox =
{
	0xA8, 0x43, 0x5F, 0x06, 0x6B, 0x75, 0x6C, 0x59,
	0x71, 0xDF, 0x87, 0x95, 0x17, 0xF0, 0xD8, 0x09,
	0x6D, 0xF3, 0x1D, 0xCB, 0xC9, 0x4D, 0x2C, 0xAF,
	0x79, 0xE0, 0x97, 0xFD, 0x6F, 0x4B, 0x45, 0x39,
	0x3E, 0xDD, 0xA3, 0x4F, 0xB4, 0xB6, 0x9A, 0x0E,
	0x1F, 0xBF, 0x15, 0xE1, 0x49, 0xD2, 0x93, 0xC6,
	0x92, 0x72, 0x9E, 0x61, 0xD1, 0x63, 0xFA, 0xEE,
	0xF4, 0x19, 0xD5, 0xAD, 0x58, 0xA4, 0xBB, 0xA1,
	0xDC, 0xF2, 0x83, 0x37, 0x42, 0xE4, 0x7A, 0x32,
	0x9C, 0xCC, 0xAB, 0x4A, 0x8F, 0x6E, 0x04, 0x27,
	0x2E, 0xE7, 0xE2, 0x5A, 0x96, 0x16, 0x23, 0x2B,
	0xC2, 0x65, 0x66, 0x0F, 0xBC, 0xA9, 0x47, 0x41,
	0x34, 0x48, 0xFC, 0xB7, 0x6A, 0x88, 0xA5, 0x53,
	0x86, 0xF9, 0x5B, 0xDB, 0x38, 0x7B, 0xC3, 0x1E,
	0x22, 0x33, 0x24, 0x28, 0x36, 0xC7, 0xB2, 0x3B,
	0x8E, 0x77, 0xBA, 0xF5, 0x14, 0x9F, 0x08, 0x55,
	0x9B, 0x4C, 0xFE, 0x60, 0x5C, 0xDA, 0x18, 0x46,
	0xCD, 0x7D, 0x21, 0xB0, 0x3F, 0x1B, 0x89, 0xFF,
	0xEB, 0x84, 0x69, 0x3A, 0x9D, 0xD7, 0xD3, 0x70,
	0x67, 0x40, 0xB5, 0xDE, 0x5D, 0x30, 0x91, 0xB1,
	0x78, 0x11, 0x01, 0xE5, 0x00, 0x68, 0x98, 0xA0,
	0xC5, 0x02, 0xA6, 0x74, 0x2D, 0x0B, 0xA2, 0x76,
	0xB3, 0xBE, 0xCE, 0xBD, 0xAE, 0xE9, 0x8A, 0x31,
	0x1C, 0xEC, 0xF1, 0x99, 0x94, 0xAA, 0xF6, 0x26,
	0x2F, 0xEF, 0xE8, 0x8C, 0x35, 0x03, 0xD4, 0x7F,
	0xFB, 0x05, 0xC1, 0x5E, 0x90, 0x20, 0x3D, 0x82,
	0xF7, 0xEA, 0x0A, 0x0D, 0x7E, 0xF8, 0x50, 0x1A,
	0xC4, 0x07, 0x57, 0xB8, 0x3C, 0x62, 0xE3, 0xC8,
	0xAC, 0x52, 0x64, 0x10, 0xD0, 0xD9, 0x13, 0x0C,
	0x12, 0x29, 0x51, 0xB9, 0xCF, 0xD6, 0x73, 0x8D,
	0x81, 0x54, 0xC0, 0xED, 0x4E, 0x44, 0xA7, 0x2A,
	0x85, 0x25, 0xE6, 0xCA, 0x7C, 0x8B, 0x56, 0x80,
	0xCE, 0xBB, 0xEB, 0x92, 0xEA, 0xCB, 0x13, 0xC1,
	0xE9, 0x3A, 0xD6, 0xB2, 0xD2, 0x90, 0x17, 0xF8,
	0x42, 0x15, 0x56, 0xB4, 0x65, 0x1C, 0x88, 0x43,
	0xC5, 0x5C, 0x36, 0xBA, 0xF5, 0x57, 0x67, 0x8D,
	0x31, 0xF6, 0x64, 0x58, 0x9E, 0xF4, 0x22, 0xAA,
	0x75, 0x0F, 0x02, 0xB1, 0xDF, 0x6D, 0x73, 0x4D,
	0x7C, 0x26, 0x2E, 0xF7, 0x08, 0x5D, 0x44, 0x3E,
	0x9F, 0x14, 0xC8, 0xAE, 0x54, 0x10, 0xD8, 0xBC,
	0x1A, 0x6B, 0x69, 0xF3, 0xBD, 0x33, 0xAB, 0xFA,
	0xD1, 0x9B, 0x68, 0x4E, 0x16, 0x95, 0x91, 0xEE,
	0x4C, 0x63, 0x8E, 0x5B, 0xCC, 0x3C, 0x19, 0xA1,
	0x81, 0x49, 0x7B, 0xD9, 0x6F, 0x37, 0x60, 0xCA,
	0xE7, 0x2B, 0x48, 0xFD, 0x96, 0x45, 0xFC, 0x41,
	0x12, 0x0D, 0x79, 0xE5, 0x89, 0x8C, 0xE3, 0x20,
	0x30, 0xDC, 0xB7, 0x6C, 0x4A, 0xB5, 0x3F, 0x97,
	0xD4, 0x62, 0x2D, 0x06, 0xA4, 0xA5, 0x83, 0x5F,
	0x2A, 0xDA, 0xC9, 0x00, 0x7E, 0xA2, 0x55, 0xBF,
	0x11, 0xD5, 0x9C, 0xCF, 0x0E, 0x0A, 0x3D, 0x51,
	0x7D, 0x93, 0x1B, 0xFE, 0xC4, 0x47, 0x09, 0x86,
	0x0B, 0x8F, 0x9D, 0x6A, 0x07, 0xB9, 0xB0, 0x98,
	0x18, 0x32, 0x71, 0x4B, 0xEF, 0x3B, 0x70, 0xA0,
	0xE4, 0x40, 0xFF, 0xC3, 0xA9, 0xE6, 0x78, 0xF9,
	0x8B, 0x46, 0x80, 0x1E, 0x38, 0xE1, 0xB8, 0xA8,
	0xE0, 0x0C, 0x23, 0x76, 0x1D, 0x25, 0x24, 0x05,
	0xF1, 0x6E, 0x94, 0x28, 0x9A, 0x84, 0xE8, 0xA3,
	0x4F, 0x77, 0xD3, 0x85, 0xE2, 0x52, 0xF2, 0x82,
	0x50, 0x7A, 0x2F, 0x74, 0x53, 0xB3, 0x61, 0xAF,
	0x39, 0x35, 0xDE, 0xCD, 0x1F, 0x99, 0xAC, 0xAD,
	0x72, 0x2C, 0xDD, 0xD0, 0x87, 0xBE, 0x5E, 0xA6,
	0xEC, 0x04, 0xC6, 0x03, 0x34, 0xFB, 0xDB, 0x59,
	0xB6, 0xC2, 0x01, 0xF0, 0x5A, 0xED, 0xA7, 0x66,
	0x21, 0x7F, 0x8A, 0x27, 0xC7, 0xC0, 0x29, 0xD7,
	0x93, 0xD9, 0x9A, 0xB5, 0x98, 0x22, 0x45, 0xFC,
	0xBA, 0x6A, 0xDF, 0x02, 0x9F, 0xDC, 0x51, 0x59,
	0x4A, 0x17, 0x2B, 0xC2, 0x94, 0xF4, 0xBB, 0xA3,
	0x62, 0xE4, 0x71, 0xD4, 0xCD, 0x70, 0x16, 0xE1,
	0x49, 0x3C, 0xC0, 0xD8, 0x5C, 0x9B, 0xAD, 0x85,
	0x53, 0xA1, 0x7A, 0xC8, 0x2D, 0xE0, 0xD1, 0x72,
	0xA6, 0x2C, 0xC4, 0xE3, 0x76, 0x78, 0xB7, 0xB4,
	0x09, 0x3B, 0x0E, 0x41, 0x4C, 0xDE, 0xB2, 0x90,
	0x25, 0xA5, 0xD7, 0x03, 0x11, 0x00, 0xC3, 0x2E,
	0x92, 0xEF, 0x4E, 0x12, 0x9D, 0x7D, 0xCB, 0x35,
	0x10, 0xD5, 0x4F, 0x9E, 0x4D, 0xA9, 0x55, 0xC6,
	0xD0, 0x7B, 0x18, 0x97, 0xD3, 0x36, 0xE6, 0x48,
	0x56, 0x81, 0x8F, 0x77, 0xCC, 0x9C, 0xB9, 0xE2,
	0xAC, 0xB8, 0x2F, 0x15, 0xA4, 0x7C, 0xDA, 0x38,
	0x1E, 0x0B, 0x05, 0xD6, 0x14, 0x6E, 0x6C, 0x7E,
	0x66, 0xFD, 0xB1, 0xE5, 0x60, 0xAF, 0x5E, 0x33,
	0x87, 0xC9, 0xF0, 0x5D, 0x6D, 0x3F, 0x88, 0x8D,
	0xC7, 0xF7, 0x1D, 0xE9, 0xEC, 0xED, 0x80, 0x29,
	0x27, 0xCF, 0x99, 0xA8, 0x50, 0x0F, 0x37, 0x24,
	0x28, 0x30, 0x95, 0xD2, 0x3E, 0x5B, 0x40, 0x83,
	0xB3, 0x69, 0x57, 0x1F, 0x07, 0x1C, 0x8A, 0xBC,
	0x20, 0xEB, 0xCE, 0x8E, 0xAB, 0xEE, 0x31, 0xA2,
	0x73, 0xF9, 0xCA, 0x3A, 0x1A, 0xFB, 0x0D, 0xC1,
	0xFE, 0xFA, 0xF2, 0x6F, 0xBD, 0x96, 0xDD, 0x43,
	0x52, 0xB6, 0x08, 0xF3, 0xAE, 0xBE, 0x19, 0x89,
	0x32, 0x26, 0xB0, 0xEA, 0x4B, 0x64, 0x84, 0x82,
	0x6B, 0xF5, 0x79, 0xBF, 0x01, 0x5F, 0x75, 0x63,
	0x1B, 0x23, 0x3D, 0x68, 0x2A, 0x65, 0xE8, 0x91,
	0xF6, 0xFF, 0x13, 0x58, 0xF1, 0x47, 0x0A, 0x7F,
	0xC5, 0xA7, 0xE7, 0x61, 0x5A, 0x06, 0x46, 0x44,
	0x42, 0x04, 0xA0, 0xDB, 0x39, 0x86, 0x54, 0xAA,
	0x8C, 0x34, 0x21, 0x8B, 0xF8, 0x0C, 0x74, 0x67,
	0x68, 0x8D, 0xCA, 0x4D, 0x73, 0x4B, 0x4E, 0x2A,
	0xD4, 0x52, 0x26, 0xB3, 0x54, 0x1E, 0x19, 0x1F,
	0x22, 0x03, 0x46, 0x3D, 0x2D, 0x4A, 0x53, 0x83,
	0x13, 0x8A, 0xB7, 0xD5, 0x25, 0x79, 0xF5, 0xBD,
	0x58, 0x2F, 0x0D, 0x02, 0xED, 0x51, 0x9E, 0x11,
	0xF2, 0x3E, 0x55, 0x5E, 0xD1, 0x16, 0x3C, 0x66,
	0x70, 0x5D, 0xF3, 0x45, 0x40, 0xCC, 0xE8, 0x94,
	0x56, 0x08, 0xCE, 0x1A, 0x3A, 0xD2, 0xE1, 0xDF,
	0xB5, 0x38, 0x6E, 0x0E, 0xE5, 0xF4, 0xF9, 0x86,
	0xE9, 0x4F, 0xD6, 0x85, 0x23, 0xCF, 0x32, 0x99,
	0x31, 0x14, 0xAE, 0xEE, 0xC8, 0x48, 0xD3, 0x30,
	0xA1, 0x92, 0x41, 0xB1, 0x18, 0xC4, 0x2C, 0x71,
	0x72, 0x44, 0x15, 0xFD, 0x37, 0xBE, 0x5F, 0xAA,
	0x9B, 0x88, 0xD8, 0xAB, 0x89, 0x9C, 0xFA, 0x60,
	0xEA, 0xBC, 0x62, 0x0C, 0x24, 0xA6, 0xA8, 0xEC,
	0x67, 0x20, 0xDB, 0x7C, 0x28, 0xDD, 0xAC, 0x5B,
	0x34, 0x7E, 0x10, 0xF1, 0x7B, 0x8F, 0x63, 0xA0,
	0x05, 0x9A, 0x43, 0x77, 0x21, 0xBF, 0x27, 0x09,
	0xC3, 0x9F, 0xB6, 0xD7, 0x29, 0xC2, 0xEB, 0xC0,
	0xA4, 0x8B, 0x8C, 0x1D, 0xFB, 0xFF, 0xC1, 0xB2,
	0x97, 0x2E, 0xF8, 0x65, 0xF6, 0x75, 0x07, 0x04,
	0x49, 0x33, 0xE4, 0xD9, 0xB9, 0xD0, 0x42, 0xC7,
	0x6C, 0x90, 0x00, 0x8E, 0x6F, 0x50, 0x01, 0xC5,
	0xDA, 0x47, 0x3F, 0xCD, 0x69, 0xA2, 0xE2, 0x7A,
	0xA7, 0xC6, 0x93, 0x0F, 0x0A, 0x06, 0xE6, 0x2B,
	0x96, 0xA3, 0x1C, 0xAF, 0x6A, 0x12, 0x84, 0x39,
	0xE7, 0xB0, 0x82, 0xF7, 0xFE, 0x9D, 0x87, 0x5C,
	0x81, 0x35, 0xDE, 0xB4, 0xA5, 0xFC, 0x80, 0xEF,
	0xCB, 0xBB, 0x6B, 0x76, 0xBA, 0x5A, 0x7D, 0x78,
	0x0B, 0x95, 0xE3, 0xAD, 0x74, 0x98, 0x3B, 0x36,
	0x64, 0x6D, 0xDC, 0xF0, 0x59, 0xA9, 0x4C, 0x17,
	0x7F, 0x91, 0xB8, 0xC9, 0x57, 0x1B, 0xE0, 0x61
};

//======================================================================================================================

#define DSTU4145_NAMED_CURVES_P_COUNT	10
#define DSTU4145_NAMED_CURVES_N_COUNT	5

//======================================================================================================================

static DSTU4145_PARAMETER_EC NamedCurvesP[DSTU4145_NAMED_CURVES_P_COUNT] =
{
	{1,
	{0xC1455D21, 0x5E638A19, 0x0AB40392, 0x2A2DC821,
	0xFF610846, 0x00000005}, 163, 7, 6, 3, 2},

	{1,
	{0x5A827DAC, 0x30F1A431, 0x20518A09, 0x0811759F,
	0xE3CEEB23, 0x0000006E}, 167, 6, 0, 0, 2},

	{0,
	{0x6FB437D9, 0xBB278F6B, 0xDDF6853B, 0xDB2FC16E,
	0x76C80499, 0x00001085}, 173, 10, 2, 1, 4},

	{1,
	{0x72BEB710, 0x2D041845, 0x07A341E3, 0x6F2F88DD,
	0x85652643, 0x0004A6E0}, 179, 4, 2, 1, 2},

	{1,
	{0x50FEFC03, 0x27E04827, 0x6B4981FF, 0xD5890E8B,
	0x02902EC4, 0x7BC86E21}, 191, 9, 0, 0, 2},

	{1,
	{0xCE454D2C, 0x26AA936E, 0xDD3B8A03, 0x1BD54EF5,
	0xCF7E64A2, 0x675534C7, 0x73B15095, 0x00000069}, 233, 9, 4, 1, 2},

	{0,
	{0xDBE3BE10, 0x1F9EEA6A, 0x458C5786, 0xFF9425C1,
	0xA7942394, 0x18F938D7, 0x0115657E, 0xCEF49472, 0x00000001},
	257, 12, 0, 0, 4},

	{1,
	{0x904968BB, 0xBDC90186, 0xF18B6090, 0xE241050D,
	0xC599E2E2, 0x4F4296C0, 0x6C6D3DE9, 0xB5054B5E, 0xF7D53666,
	0x000393C7}, 307, 8, 4, 2, 2},

	{1,
	{0x56995136, 0x9755437B, 0x394C79A7, 0xB8F93D92,
	0xFE42CADA, 0xA64B0C2A, 0x47BF6AA4, 0x4447556B, 0x627AD565,
	0xB7A6F3D1, 0x8AD242B0, 0x000043FC}, 367, 21, 0, 0, 2},

	{1,
	{0xC640CAF3, 0x17DAA469, 0x12CA4931, 0x18AE2DC3,
	0x6BAC536B, 0x975936C6, 0x8AAEAEDE, 0xF988D8D2, 0x0134D5BF,
	0xC4F94E69, 0xFE8C3D27, 0x708FC26D, 0x10490F6A, 0x000003CE},
	431, 5, 3, 1, 2}
};

//----------------------------------------------------------------------------------------------------------------------

static DSTU4145_PARAMETER_P NamedBasePointsP[DSTU4145_NAMED_CURVES_P_COUNT] =
{
	{{0xF35823BE, 0x29DAF8A3, 0xA5C42372, 0xD74CE983,
	0xE2F85F5D, 0x00000002},
	{0x39BCF14D, 0x2BE2262D, 0x0002BEC1, 0x00000000,
	0x00000000, 0x00000004}, 163},

	{{0x8B21CD54, 0x30B2A201, 0x03910A3D, 0x6A681928,
	0x1F665378, 0x0000007A},
	{0x9FF7701F, 0xBCC7D7F2, 0xFFFFB12E, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000003F}, 166},

	{{0xD37389CA, 0x567A9181, 0x8FA22FAD, 0x6EADF044,
	0x1A619BCC, 0x000004D4},
	{0x25BB2831, 0x67606E38, 0x00189B4E, 0x00000000,
	0x00000000, 0x00000800}, 172},

	{{0x022C7D02, 0xA9954667, 0x7F48819B, 0x2BD26DC5,
	0xFE51464B, 0x0006BA06},
	{0xB64236EF, 0x0435FE5A, 0xFFB98196, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0003FFFF}, 178},

	{{0xDAEB7128, 0xC2FCFE76, 0xAC58B9B5, 0x7912A6D2,
	0x62F2FF4A, 0x714114B7},
	{0x88F7474F, 0xC1DABC67, 0x69A779CA, 0x00000000,
	0x00000000, 0x40000000}, 191},

	{{0xB25EFE96, 0x28D003EE, 0x3545F327, 0x3C31761D,
	0x118DF35B, 0xCDF83BA1, 0xCDA526B6, 0x0000003F},
	{0x03CFE0D7, 0x22031D26, 0xE72F8A69, 0x0013E974,
	0x00000000, 0x00000000, 0x00000000, 0x00000100},
	233},

	{{0xD8D20FB6, 0x34A9E8DC, 0x1B10C623, 0x7AC491CA,
	0x306C7E00, 0x55CD260B, 0x7D0E9B6C, 0x2A29EF20},
	{0x907D470D, 0xD3E17714, 0xF182E987, 0x6759213A,
	0x00000000, 0x00000000, 0x00000000, 0x80000000}, 256},

	{{0x6E7232AA, 0x3C52C02D, 0x6D316774, 0x7A239B27,
	0xCD825A08, 0xD16BF75C, 0x4C1E92F1, 0x1A022498, 0x8B189D29,
	0x000216EE},
	{0x4022B7B7, 0xA588D460, 0x0D390FBB, 0xF3825DA7,
	0xFFC079C2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0x0003FFFF}, 306},

	{{0x41B3B9A0, 0xBF4A3735, 0x9A109F78, 0xB5FE12E5,
	0x81E09639, 0x1A400CA6, 0x413E7BE8, 0x61197A76, 0x9AE0D3F9,
	0xF08C49A9, 0x6EDDD512, 0x0000324A},
	{0x049B2D49, 0x2245EF44, 0xD28CE881, 0x4F22428F,
	0x75A3FA82, 0x009C300B, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00004000}, 367},

	{{0x947C857C, 0xFD3B43C5, 0xC2171E99, 0x58068426,
	0x49A2A950, 0x49C27BED, 0x874E5AAE, 0x72F88986, 0x24D57AEF,
	0x03C32E08, 0xE7ED9A8E, 0x33A16BBA, 0xBA79D981, 0x00001A62},
	{0x110504CF, 0xD90C7A95, 0x1FCBAF80, 0x2F81AA8A,
	0xC0A724F0, 0x458009A8, 0xFFBA3175, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00003FFF}, 430}
};

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_PARAMETERS_EXT
static CHAR szNamedCurveNamesP[DSTU4145_NAMED_CURVES_P_COUNT]
	[CSP_PARAMETERS_MAX_NAME_LENGTH] =
{
	"ÏÁ, 163 á³òà",
	"ÏÁ, 167 á³ò",
	"ÏÁ, 173 á³òà",
	"ÏÁ, 179 á³ò",
	"ÏÁ, 191 á³ò",
	"ÏÁ, 233 á³òà",
	"ÏÁ, 257 á³ò",
	"ÏÁ, 307 á³ò",
	"ÏÁ, 367 á³ò",
	"ÏÁ, 431 á³ò",
};

//----------------------------------------------------------------------------------------------------------------------

static CHAR szNamedCurveOIDsP[DSTU4145_NAMED_CURVES_P_COUNT]
	[CSP_PARAMETERS_MAX_OID_LENGTH] =
{
	"1.2.804.2.1.1.1.1.3.1.1.2.0",
	"1.2.804.2.1.1.1.1.3.1.1.2.1",
	"1.2.804.2.1.1.1.1.3.1.1.2.2",
	"1.2.804.2.1.1.1.1.3.1.1.2.3",
	"1.2.804.2.1.1.1.1.3.1.1.2.4",
	"1.2.804.2.1.1.1.1.3.1.1.2.5",
	"1.2.804.2.1.1.1.1.3.1.1.2.6",
	"1.2.804.2.1.1.1.1.3.1.1.2.7",
	"1.2.804.2.1.1.1.1.3.1.1.2.8",
	"1.2.804.2.1.1.1.1.3.1.1.2.9"
};
#endif // CSP_PARAMETERS_EXT

//----------------------------------------------------------------------------------------------------------------------

static DSTU4145_PARAMETER_EC NamedCurvesN[DSTU4145_NAMED_CURVES_N_COUNT] =
{
	{0,
	{0x06E278C7, 0xE1E6651B, 0x44915740, 0xF43BA009,
	0x7E139319, 0x0000043D}, 173, 0, 0, 0, 0},

	{1,
	{0x2182CBCB, 0xC82F2E6B, 0x1762C547, 0x8193D3A6,
	0xBC4FD830, 0x00019C9E}, 179, 0, 0, 0, 0},

	{1,
	{0xA1E31EF8, 0xAE559C13, 0x44F72FDB, 0x740FD574,
	0x29D6CEEA, 0x13871C9D}, 191, 0, 0, 0, 0},

	{1,
	{0x2D4F9A8E, 0xA003E096, 0xA44664F3, 0x18EEA55A,
	0x04A424C0, 0x702C75B7, 0xF920952A, 0x00000080},
	233, 0, 0, 0, 0},

	{1,
	{0xBA5F9299, 0xD5FF8B06, 0x3B43651B, 0xC5E80EFE,
	0x973F2F06, 0x5E53F40F, 0x19536EE6, 0x40810A4C, 0xBD83F1F9,
	0x28378646, 0x26AD6BAD, 0x7000A6F2, 0x7AF7B440, 0x000053FB},
	431, 0, 0, 0, 0}
};

//----------------------------------------------------------------------------------------------------------------------

static DSTU4145_PARAMETER_P NamedBasePointsN[DSTU4145_NAMED_CURVES_N_COUNT]={
	{{0x4E6DEA56, 0xCB6E424B, 0xCAA51917, 0x89B24318,
	0x8B8D7040, 0x00000A3B},
	{0x25BB2831, 0x67606E38, 0x00189B4E, 0x00000000,
	0x00000000, 0x00000800}, 172},

	{{0xB21B66B9, 0xAC4ADE43, 0xD3E39BC4, 0x477159E0,
	0x12265410, 0x00011F41},
	{0xB64236EF, 0x0435FE5A, 0xFFB98196, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0003FFFF}, 178},

	{{0xEB1D85D3, 0x2AF25ABE, 0x1B66B94F, 0x4ADE43B2,
	0xE39BC4AC, 0x3159E0D3},
	{0x88F7474F, 0xC1DABC67, 0x69A779CA, 0x00000000,
	0x00000000, 0x40000000}, 191},

	{{0x2E9992FB, 0xD5F758EC, 0xCA795792, 0x1D90DB35,
	0x256256F2, 0x069F1CDE, 0x823B8ACF, 0x000000A0},
	{0x03CFE0D7, 0x22031D26, 0xE72F8A69, 0x0013E974,
	0x00000000, 0x00000000, 0x00000000, 0x00000100}, 233},

	{{0x7C5ADEA6, 0x090DCFBA, 0x40B835D3, 0x3EE3E17E,
	0x6448C08D, 0xB5814232, 0x2FA9D5EB, 0x4E5C8857, 0x773C595D,
	0xD4C16251, 0x363D4ABF, 0xC724157B, 0x182CFCD7, 0x00002020},
	{0x110504CF, 0xD90C7A95, 0x1FCBAF80, 0x2F81AA8A,
	0xC0A724F0, 0x458009A8, 0xFFBA3175, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00003FFF}, 430}
};

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_PARAMETERS_EXT
static CHAR szNamedCurveNamesN[DSTU4145_NAMED_CURVES_N_COUNT]
	[CSP_PARAMETERS_MAX_NAME_LENGTH] =
{
	"ÎÍÁ, 173 á³òà",
	"ÎÍÁ, 179 á³ò",
	"ÎÍÁ, 191 á³ò",
	"ÎÍÁ, 233 á³òà",
	"ÎÍÁ, 431 á³ò",
};

//----------------------------------------------------------------------------------------------------------------------

static CHAR szNamedCurveOIDsN[DSTU4145_NAMED_CURVES_N_COUNT]
	[CSP_PARAMETERS_MAX_OID_LENGTH] =
{
	"1.2.804.2.1.1.1.1.3.1.2.2.0",
	"1.2.804.2.1.1.1.1.3.1.2.2.1",
	"1.2.804.2.1.1.1.1.3.1.2.2.2",
	"1.2.804.2.1.1.1.1.3.1.2.2.3",
	"1.2.804.2.1.1.1.1.3.1.2.2.4"
};

//======================================================================================================================

#define GOST28147_FIXED_SBOXES_COUNT	10

//======================================================================================================================

static GOST28147_COMPRESSED_SBOX FixedSBoxes[GOST28147_FIXED_SBOXES_COUNT] = 
{
	{
		0x8A, 0x09, 0xCD, 0x46, 0x9E, 0x6B, 0x74, 0xB5, 
		0x2F, 0x31, 0x13, 0xFC, 0x57, 0xE0, 0xA8, 0xD2,
		0x3F, 0x86, 0xD5, 0x98, 0x6E, 0xBB, 0xFA, 0x04, 
		0x2C, 0x50, 0xC3, 0xA7, 0x42, 0xE9, 0x11, 0x7D,
		0x2F, 0x88, 0x9E, 0x79, 0x57, 0xF2, 0x00, 0xBD, 
		0xCC, 0x16, 0xD1, 0xE5, 0xAB, 0x34, 0x63, 0x4A,
		0x13, 0x28, 0x3B, 0xE5, 0x66, 0xD4, 0xBE, 0x8A, 
		0xF2, 0xAC, 0xC1, 0x57, 0x79, 0x9F, 0x0D, 0x40
	},
	{
		0xAE, 0xD9, 0x3C, 0x77, 0x6F, 0xE4, 0x8C, 0x1B, 
		0xF6, 0x3A, 0xBD, 0x41, 0x00, 0x95, 0x58, 0x22, 
		0x44, 0x5B, 0x11, 0xCF, 0x79, 0xE2, 0x9E, 0x2C, 
		0xA6, 0xFA, 0xB8, 0xD7, 0x03, 0x85, 0x60, 0x3D,
		0x8C, 0x7B, 0x33, 0xA9, 0x9F, 0x60, 0xE4, 0x55, 
		0xD7, 0x02, 0x4E, 0xCD, 0x11, 0x2A, 0xF8, 0xB6,
		0x4F, 0x30, 0xEE, 0xD6, 0x58, 0x0D, 0x25, 0xB9, 
		0x1A, 0xA3, 0x71, 0x6C, 0x94, 0xFB, 0x87, 0x2C
	},
	{
		0x7D, 0x89, 0x61, 0xBE, 0x07, 0x32, 0x4C, 0xD5, 
		0x94, 0x5B, 0xF6, 0xEF, 0xA3, 0xC8, 0x2A, 0x10,
		0xBA, 0xA5, 0xC3, 0x1C, 0x59, 0x68, 0x9D, 0xE6, 
		0x24, 0xDF, 0xFE, 0x70, 0x02, 0x4B, 0x31, 0x87,
		0x45, 0x3B, 0xB3, 0xD0, 0x1F, 0xF9, 0x8E, 0x24, 
		0x71, 0xEC, 0xC8, 0x96, 0xA2, 0x0A, 0x67, 0x5D,
		0x63, 0xD7, 0xC8, 0xAB, 0xB1, 0x7E, 0x95, 0x30, 
		0xFD, 0xE4, 0x1C, 0x2A, 0x02, 0x89, 0x4F, 0x56
	},
	{
		0xA9, 0x5C, 0xB3, 0xED, 0x77, 0x66, 0x0E, 0xC1, 
		0x2A, 0x82, 0xF0, 0x44, 0xD8, 0x3F, 0x95, 0x1B,
		0x34, 0x9C, 0x43, 0x50, 0xED, 0x72, 0x8E, 0x6B, 
		0xD7, 0x0F, 0x25, 0xF9, 0xB1, 0xC8, 0xAA, 0x16,
		0xE2, 0x59, 0xDC, 0xBF, 0x1D, 0x9B, 0x44, 0x21, 
		0xF7, 0x85, 0x73, 0x0E, 0x36, 0xC8, 0xAA, 0x60,
		0x1E, 0x96, 0xC5, 0xBA, 0x79, 0x6D, 0x84, 0x38, 
		0x2B, 0xFC, 0xE0, 0x03, 0x57, 0xA1, 0x4F, 0xD2
	},
	{
		0xC3, 0x74, 0x6D, 0x98, 0x3C, 0x87, 0xBA, 0x52, 
		0xF0, 0xAE, 0x09, 0xDF, 0x4B, 0x21, 0x15, 0xE6,
		0x3E, 0x94, 0x68, 0xD7, 0x8B, 0xF3, 0xAA, 0x2C, 
		0x71, 0xE2, 0xC6, 0x09, 0xBD, 0x4F, 0x10, 0x55,
		0x15, 0x8C, 0xBA, 0xE7, 0x72, 0x41, 0xAF, 0x0D, 
		0xCE, 0x33, 0x5B, 0xD4, 0x90, 0xF8, 0x69, 0x26,
		0xE9, 0x9B, 0x1A, 0x8D, 0x55, 0xFE, 0xB2, 0x03, 
		0x60, 0x26, 0xC4, 0x7C, 0xAF, 0x41, 0xD7, 0x38
	},
	{
		0xEF, 0xCC, 0x59, 0x06, 0x7E, 0x42, 0xA1, 0x3B, 
		0x20, 0x6D, 0x14, 0xDA, 0x97, 0xB8, 0xF3, 0x85,
		0x15, 0xF6, 0x7D, 0x49, 0xB2, 0xEE, 0xCA, 0x33, 
		0x6F, 0xB2, 0x98, 0x81, 0x04, 0x50, 0xA7, 0xDC,
		0xBF, 0x09, 0xDE, 0x76, 0xCD, 0xE1, 0x15, 0x48, 
		0x24, 0x32, 0x63, 0x8C, 0xAA, 0x5B, 0xF0, 0x97,
		0x17, 0x5E, 0xEF, 0xB8, 0x2D, 0xC0, 0x3B, 0x83, 
		0xAA, 0x01, 0x94, 0x72, 0xF9, 0x6C, 0x46, 0xD5
	},
	{
		0x2F, 0x5D, 0xAA, 0x05, 0x6C, 0x90, 0x11, 0xF6, 
		0xD9, 0x42, 0x7E, 0xE7, 0xB3, 0x3B, 0x84, 0xC8,
		0x43, 0xAE, 0xB4, 0x9B, 0xF5, 0x29, 0xE1, 0x52, 
		0xDF, 0x16, 0x38, 0x6D, 0x07, 0x70, 0xCA, 0x8C,
		0xCF, 0xB6, 0xF5, 0x48, 0x59, 0x17, 0xEC, 0x9B, 
		0x00, 0x8A, 0xD3, 0x21, 0xA2, 0x74, 0x3D, 0x6E,
		0x1D, 0x52, 0x04, 0xF8, 0x6B, 0xAC, 0x31, 0xE3, 
		0x7A, 0x25, 0xC9, 0xDE, 0xB7, 0x8F, 0x09, 0x46
	},
	{
		0x3E, 0xE4, 0xCB, 0xA2, 0x68, 0x27, 0xD5, 0x1C, 
		0x99, 0x8D, 0x70, 0x43, 0x01, 0xFF, 0x56, 0xBA,
		0xC5, 0xA2, 0x78, 0xD7, 0xE1, 0x3F, 0x0E, 0x26, 
		0x94, 0x5D, 0x1B, 0x60, 0xBA, 0x43, 0xFC, 0x89,
		0x66, 0xD3, 0xFF, 0x17, 0x50, 0x39, 0x8A, 0x08, 
		0xBB, 0xAC, 0xE4, 0x41, 0x95, 0xC2, 0x2D, 0x7E,
		0x32, 0x0F, 0x5C, 0xC5, 0x8B, 0xF1, 0xD3, 0xEE, 
		0xB0, 0x66, 0x2D, 0x9A, 0x77, 0x19, 0x44, 0xA8
	},
	{
		0x39, 0x50, 0x0B, 0xFC, 0x82, 0x74, 0xE3, 0xCF, 
		0xDD, 0xA6, 0x1E, 0x61, 0xBA, 0x27, 0x45, 0x98,
		0x58, 0x44, 0xF5, 0x0A, 0xCE, 0xBB, 0xDA, 0x96, 
		0x1C, 0xEF, 0x87, 0x69, 0x33, 0x21, 0xD2, 0x70,
		0x77, 0x4C, 0x33, 0xB0, 0x66, 0xA8, 0x8E, 0x1B, 
		0x91, 0xCF, 0xED, 0xDA, 0x09, 0xF5, 0x22, 0x54,
		0xE7, 0x2E, 0x89, 0xFF, 0x31, 0x04, 0x78, 0xC3, 
		0xBB, 0xDD, 0x10, 0x52, 0x66, 0x4A, 0x95, 0xAC
	},
	{
		0x78, 0xD4, 0x16, 0x89, 0xAB, 0xEC, 0x41, 0xF2, 
		0x93, 0x07, 0x6E, 0x30, 0x2D, 0xCA, 0xBF, 0x55,
		0x2C, 0xB8, 0x3D, 0x41, 0xCA, 0x72, 0x99, 0xD6, 
		0xF3, 0x84, 0x5E, 0x07, 0x15, 0xEF, 0xA0, 0x6B,
		0x48, 0xC3, 0x9D, 0xBA, 0xEE, 0xAF, 0x75, 0x61, 
		0x34, 0x57, 0x0B, 0xFC, 0x12, 0x20, 0x86, 0xD9,
		0xA5, 0x38, 0x5E, 0x97, 0x03, 0xD0, 0x71, 0x8D, 
		0xCA, 0x46, 0x19, 0x62, 0xBF, 0xFB, 0x2C, 0xE4
	}
};
#endif // CSP_PARAMETERS_EXT

//----------------------------------------------------------------------------------------------------------------------

BYTE bDegreesTable[256] =
{
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

//======================================================================================================================

CSPParameters::CSPParameters()
{
	m_pCSP = NULL;
}

//----------------------------------------------------------------------------------------------------------------------

CSPParameters::~CSPParameters()
{
}

//----------------------------------------------------------------------------------------------------------------------

VOID CSPParameters::GOST28147(
	FILE* pFile,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	DWORD dw, dw1, dw2;

	memset((PVOID) pSBox, 0, sizeof(GOST28147_COMPRESSED_SBOX));

	CHAR sz[16384];

	fscanf(pFile, "%s", sz);

	for(dw1 = 0; dw1 < 4; dw1++)
	{
		for(dw2 = 0; dw2 < 16; dw2++)
		{
			fscanf(pFile, "%X", &dw);
			pSBox[dw1 * 16 + dw2] |= (BYTE) (dw & 0xF);
		}

		for(dw2 = 0; dw2 < 16; dw2++)
		{
			fscanf(pFile, "%X", &dw);
			pSBox[dw1 * 16 + dw2] |= (BYTE) (dw << 4);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
#ifndef OS_NO_EXCEPTIONS
	__try
	{
#endif
		FILE *pFile;

		if((pFile = fopen(pcFileName, "rt")) == NULL)
			return FALSE;

		GOST28147(pFile, pSBox);

		fclose(pFile);
		return TRUE;
#ifndef OS_NO_EXCEPTIONS
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
#endif
}

//----------------------------------------------------------------------------------------------------------------------

VOID CSPParameters::DSTU4145(
	FILE *pFile,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP)
{
	DWORD dw;

	memset((PVOID) pParameterEC, 0, sizeof(DSTU4145_PARAMETER_EC));
	memset((PVOID) pParameterP, 0, sizeof(DSTU4145_PARAMETER_P));

	CHAR sz[16384];

	fscanf(pFile, "%s", sz);

	fscanf(pFile, "%s", sz);
	fscanf(pFile, "%d", &pParameterEC->dwM);

	fscanf(pFile, "%s", sz);
	fscanf(pFile, "%d", &pParameterEC->dwA);

	fscanf(pFile, "%s", sz);
	for(dw = 0; dw < ((pParameterEC->dwM + 31) >> 5); dw++)
		fscanf(pFile, "%X", &pParameterEC->B[dw]);

	fscanf(pFile, "%s", sz);
	fscanf(pFile, "%d", &pParameterEC->dwK1);

	fscanf(pFile, "%s", sz);
	fscanf(pFile, "%d", &pParameterEC->dwK2);

	fscanf(pFile, "%s", sz);
	fscanf(pFile, "%d", &pParameterEC->dwK3);

	fscanf(pFile, "%s", sz);
	fscanf(pFile, "%d", &pParameterEC->dwCF);

	fscanf(pFile, "%s", sz);
	for(dw = 0; dw < ((pParameterEC->dwM + 31) >> 5); dw++)
	{
		fscanf(pFile, "%X", &pParameterP->dwX[dw]);
	}

	fscanf(pFile, "%s", sz);
	for(dw = 0; dw < ((pParameterEC->dwM + 31) >> 5); dw++)
	{
		fscanf(pFile, "%X", &pParameterP->dwN[dw]);
	}
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST28147_COMPRESSED_SBOX pSBox)
{
#ifndef OS_NO_EXCEPTIONS
	__try
	{
#endif
		FILE *pFile;

		if((pFile = fopen(pcFileName, "rt")) == NULL)
			return FALSE;

		DSTU4145(pFile, pParameterEC, pParameterP);
		GOST28147(pFile, pSBox);

		fclose(pFile);
		return TRUE;
#ifndef OS_NO_EXCEPTIONS
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
#endif
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::ECDH(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST28147_COMPRESSED_SBOX pSBox)
{
#ifndef OS_NO_EXCEPTIONS
	__try
	{
#endif
		FILE *pFile;

		if((pFile = fopen(pcFileName, "rt")) == NULL)
			return FALSE;

		DSTU4145(pFile, pParameterEC, pParameterP);

		GOST28147(pFile, pSBox);

		fclose(pFile);
		return TRUE;
#ifndef OS_NO_EXCEPTIONS
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
#endif
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145Standart(
	BOOL bPolinomial,
	DWORD dwID,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP)
{
	if(bPolinomial)
	{
		if(dwID > (DSTU4145_NAMED_CURVES_P_COUNT - 1))
			return FALSE;

		memcpy((PVOID) pParameterEC, 
			(PVOID) &NamedCurvesP[dwID], sizeof(DSTU4145_PARAMETER_EC));
		memcpy((PVOID) pParameterP, 
			(PVOID) &NamedBasePointsP[dwID], sizeof(DSTU4145_PARAMETER_P));
	}
	else
	{
		if(dwID > (DSTU4145_NAMED_CURVES_N_COUNT - 1))
			return FALSE;

		memcpy((PVOID) pParameterEC, 
			(PVOID) &NamedCurvesN[dwID], sizeof(DSTU4145_PARAMETER_EC));
		memcpy((PVOID) pParameterP, 
			(PVOID) &NamedBasePointsN[dwID], sizeof(DSTU4145_PARAMETER_P));
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

VOID WINAPI CSPParameters::SetCSP(
	CSP *pCSP)
{
	m_pCSP = pCSP;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::OpenFile(
	PCSTR	pszFileName,
	DWORD	dwDesiredAccess,
	DWORD	dwShareMode,
	DWORD	dwCreationDisposition,
	DWORD	dwFlagsAndAttributes,
	PHANDLE	phFile)
{
	HANDLE hFile;

#ifndef OS_NIX
	PWCHAR pwszFileName;
	INT nFileNameSize;

	nFileNameSize = (INT) strlen(pszFileName) + 1;

	pwszFileName = new WCHAR[nFileNameSize];
	if(pwszFileName == NULL)
		return FALSE;

	if(MultiByteToWideChar(1251, 0,
			pszFileName, nFileNameSize,
			pwszFileName, nFileNameSize) !=
		nFileNameSize)
	{
		delete[] pwszFileName;
		return FALSE;
	}

	hFile = CreateFileW(pwszFileName, dwDesiredAccess,
		dwShareMode, NULL, dwCreationDisposition,
		dwFlagsAndAttributes, NULL);

	delete[] pwszFileName;
#else // OS_NIX
	hFile = CreateFileA(pszFileName, dwDesiredAccess,
		dwShareMode, NULL, dwCreationDisposition,
		dwFlagsAndAttributes, NULL);
#endif // OS_NIX

	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	if(phFile != NULL)
		*phFile = hFile;
	else
		CloseHandle(hFile);

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::ReadDataFromFile(
	PCHAR 	pcFileName,
	PVOID 	pvData,
	DWORD 	cbData)
{
	HANDLE hFile;
	DWORD cb, cbFile;

	if(!OpenFile(pcFileName,
			GENERIC_READ, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, &hFile))
	{
		return FALSE;
	}

	cbFile = GetFileSize(hFile, NULL);

	if(cbFile == 0xFFFFFFFF ||
		cbFile != cbData)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if(!ReadFile(hFile, pvData, cbFile, &cb, NULL) ||
		(cbFile != cb))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::WriteDataToFile(
	PCHAR 	pcFileName,
	PVOID 	pvData,
	DWORD 	cbData)
{
	HANDLE 	hFile;
	DWORD 	cb;

	if(!OpenFile(pcFileName,
			GENERIC_WRITE, 0, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL |
			FILE_FLAG_WRITE_THROUGH, &hFile))
	{
		return FALSE;
	}

	if(!WriteFile(hFile, pvData, cbData, &cb, NULL) ||
		(cbData != cb))
	{
		CloseHandle(hFile);
		DeleteFileA(pcFileName);

		return FALSE;
	}

	CloseHandle(hFile);

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::IsDataPasswordProtected()
{
	BOOL bParamsPasswordCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_PARAMS_PASSWORD,
		bParamsPasswordCompatible);
	if(!bParamsPasswordCompatible ||
		m_pCSP->GetParamsPassword() == NULL ||
		strlen(m_pCSP->GetParamsPassword()) == 0)
	{
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::ReadPasswordProtectedDataFromFile(
	PCHAR 	pcFileName,
	PVOID 	pvData,
	DWORD 	cbData)
{
	HANDLE hFile;
	DWORD cb, cbFile;
	GOST28147_BLOCK DataAligment;
	UINT uiDataAligment;
	GOST28147_MAC MAC;

	if(!IsDataPasswordProtected())
		return FALSE;

	if(!OpenFile(pcFileName,
			GENERIC_READ, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, &hFile))
	{
		return FALSE;
	}

	cbFile = GetFileSize(hFile, NULL);
	if(cbFile == 0xFFFFFFFF ||
		cbFile != cbData +
			sizeof(GOST28147_BLOCK) +
			sizeof(UINT) +
			sizeof(GOST28147_MAC))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if(!ReadFile(hFile, pvData,
			cbData, &cb, NULL) ||
		(cb != cbData) ||
		!ReadFile(hFile, DataAligment,
			sizeof(GOST28147_BLOCK), &cb, NULL) ||
		(cb != sizeof(GOST28147_BLOCK)) ||
		!ReadFile(hFile, &uiDataAligment,
			sizeof(UINT), &cb, NULL) ||
		(cb != sizeof(UINT)) ||
		!ReadFile(hFile, MAC,
			sizeof(GOST28147_MAC), &cb, NULL) ||
		(cb != sizeof(GOST28147_MAC)))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY(MAC);
	SWAP_BYTES_32_ARRAY(DataAligment);
	SWAP_BYTES_32_P(&uiDataAligment);
#endif

	if(m_pCSP->UnprotectData((PBYTE) pvData, cbData,
			EncryptParametersSBox, InitialHash,
			MAC, DataAligment, uiDataAligment,
			(PCHAR) m_pCSP->GetParamsPassword(),
			NULL) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::WritePasswordProtectedDataToFile(
	PCHAR 	pcFileName,
	PVOID 	pvData,
	DWORD 	cbData)
{
	PBYTE pbProtectedData;
	GOST28147_BLOCK DataAligment;
	UINT uiDataAligment;
	DWORD dwDataAligment;
	GOST28147_MAC MAC;
	HANDLE hFile;
	DWORD cb;

	if(!IsDataPasswordProtected())
		return FALSE;

	pbProtectedData = new BYTE[cbData];
	if(pbProtectedData == NULL)
		return FALSE;

	memcpy((PVOID) pbProtectedData, (PVOID) pvData, cbData);
	memset((PVOID) DataAligment, 0, sizeof(GOST28147_BLOCK));

	if(m_pCSP->ProtectData(pbProtectedData, cbData,
			EncryptParametersSBox, InitialHash,
			MAC, DataAligment, &dwDataAligment,
			(PCHAR) m_pCSP->GetParamsPassword(),
			NULL) != CSP_NO_ERROR)
	{
		delete[] pbProtectedData;
		return FALSE;
	}

	uiDataAligment = dwDataAligment;

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY(MAC);
	SWAP_BYTES_32_ARRAY(DataAligment);
	SWAP_BYTES_32_P(&uiDataAligment);
#endif

	if(!OpenFile(pcFileName,
			GENERIC_WRITE, 0, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL |
			FILE_FLAG_WRITE_THROUGH, &hFile))
	{
		delete[] pbProtectedData;
		return FALSE;
	}

	if(!WriteFile(hFile, pbProtectedData,
			cbData, &cb, NULL) ||
		(cb != cbData) ||
		!WriteFile(hFile, DataAligment,
			sizeof(GOST28147_BLOCK), &cb, NULL) ||
		(cb != sizeof(GOST28147_BLOCK)) ||
		!WriteFile(hFile, &uiDataAligment,
			sizeof(UINT), &cb, NULL) ||
		(cb != sizeof(UINT)) ||
		!WriteFile(hFile, MAC,
			sizeof(GOST28147_MAC), &cb, NULL) ||
		(cb != sizeof(GOST28147_MAC)))
	{
		CloseHandle(hFile);
		DeleteFileA(pcFileName);
		delete[] pbProtectedData;
		return FALSE;
	}

	CloseHandle(hFile);
	delete[] pbProtectedData;

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::ReadDSTU7624PasswordProtectedDataFromFile(
	PCHAR pcFileName,
	PVOID pvData,
	DWORD cbData)
{
	HANDLE hFile;
	DWORD cb, cbFile;
	DWORD cbProtectedData;
	DWORD cbUnprotectedData;
	BOOL bCompatible;
	PBYTE pbProtectedData;
	PBYTE pbUnprotectedData;

	if(!IsDataPasswordProtected())
		return FALSE;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	if(!OpenFile(pcFileName,
			GENERIC_READ, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, &hFile))
	{
		return FALSE;
	}

	cbProtectedData = DSTU7624_PROTECTED_DATA(
		cbData, DSTU7624_BLOCK_256_LENGTH);

	cbFile = GetFileSize(hFile, NULL);
	if(cbFile == 0xFFFFFFFF ||
		cbFile != cbProtectedData)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	pbProtectedData = new BYTE[cbProtectedData];
	if(pbProtectedData == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if(!ReadFile(hFile, pbProtectedData,
			cbProtectedData, &cb, NULL) ||
		(cb != cbProtectedData))
	{
		delete[] pbProtectedData;
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);

	if(m_pCSP->DSTU7624UnprotectDataEx(
			pbProtectedData, cbProtectedData,
			&pbUnprotectedData, &cbUnprotectedData,
			NULL, (PCHAR) m_pCSP->GetParamsPassword(),
			NULL, 0) != CSP_NO_ERROR ||
		cbUnprotectedData != cbData)
	{
		memset((PVOID) pbProtectedData, 0, cbProtectedData);
		delete[] pbProtectedData;

		return FALSE;
	}

	memcpy((PVOID) pvData, (PVOID) pbUnprotectedData, cbData);

	memset((PVOID) pbProtectedData, 0, cbProtectedData);
	delete[] pbProtectedData;

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::WriteDSTU7624PasswordProtectedDataToFile(
	PCHAR pcFileName,
	PVOID pvData,
	DWORD cbData)
{
	HANDLE hFile;
	DWORD cb;
	DWORD cbProtectedData;
	BOOL bCompatible;
	PBYTE pbProtectedData;

	if(!IsDataPasswordProtected())
		return FALSE;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	cbProtectedData = DSTU7624_PROTECTED_DATA(
		cbData, DSTU7624_BLOCK_256_LENGTH);

	pbProtectedData = new BYTE[cbProtectedData];
	if(pbProtectedData == NULL)
		return FALSE;

	if(m_pCSP->DSTU7624ProtectDataEx(
			(PBYTE) pvData, cbData,
			pbProtectedData, cbProtectedData,
			NULL, (PCHAR) m_pCSP->GetParamsPassword(),
			NULL, DSTU7624_KEY_256_LENGTH,
			NULL, DSTU7624_IV_256_LENGTH,
			DSTU7624_MAC_256_LENGTH) != CSP_NO_ERROR)
	{
		delete[] pbProtectedData;
		return FALSE;
	}

	if(!OpenFile(pcFileName,
			GENERIC_WRITE, 0, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL |
			FILE_FLAG_WRITE_THROUGH, &hFile))
	{
		delete[] pbProtectedData;
		return FALSE;
	}

	if(!WriteFile(hFile, pbProtectedData,
			cbProtectedData, &cb, NULL) ||
		cb != cbProtectedData)
	{
		CloseHandle(hFile);
		DeleteFileA(pcFileName);
		delete[] pbProtectedData;
		return FALSE;
	}

	CloseHandle(hFile);
	delete[] pbProtectedData;
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::ReadDataFromFile(
	PCHAR pcFileName,
	PBYTE pbData,
	PDWORD pcbData)
{
	HANDLE hFile;
	DWORD cb, cbFile;

	if(!OpenFile(pcFileName,
			GENERIC_READ, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, &hFile))
	{
		return FALSE;
	}

	cbFile = GetFileSize(hFile, NULL);

	if(cbFile == 0xFFFFFFFF ||
		*pcbData < cbFile)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if(!ReadFile(hFile, (PVOID) pbData, cbFile, &cb, NULL) ||
		cbFile != cb)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	*pcbData = cbFile;

	CloseHandle(hFile);
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::UnprotectDSTU7624PasswordProtectedData(
	PBYTE pbData,
	DWORD cbData,
	PBYTE *ppbUnprotectedData,
	PDWORD pcbData)
{
	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	if(m_pCSP->DSTU7624UnprotectDataEx(
			pbData, cbData,
			ppbUnprotectedData, pcbData,
			NULL, (PCHAR) m_pCSP->GetParamsPassword(),
			NULL, 0) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147Protected(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_GOST28147_PROTECTED_SBOX ProtectedSBox;

	memset((PVOID) &ProtectedSBox, 0,
		sizeof(CSP_GOST28147_PROTECTED_SBOX));

	if(!ReadDataFromFile(pcFileName, 
			(PVOID) &ProtectedSBox, 
			sizeof(CSP_GOST28147_PROTECTED_SBOX)) &&
		!ReadPasswordProtectedDataFromFile(pcFileName,
			(PVOID) &ProtectedSBox,
			sizeof(CSP_GOST28147_PROTECTED_SBOX)))
	{
		return FALSE;
	}

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY(ProtectedSBox.MAC);
	SWAP_BYTES_32_ARRAY(ProtectedSBox.DataAligment);
	SWAP_BYTES_32_P(&ProtectedSBox.dwDataAligment);
#endif

	if(m_pCSP->UnprotectData((PBYTE) ProtectedSBox.SBox, 
		sizeof(GOST28147_COMPRESSED_SBOX), 
		EncryptParametersSBox, InitialHash,
		ProtectedSBox.MAC, ProtectedSBox.DataAligment, 
		ProtectedSBox.dwDataAligment,
		NULL, EncryptParametersKey) != CSP_NO_ERROR)	
	{
		return FALSE;
	}	

	memcpy((PVOID) pSBox, (PVOID) ProtectedSBox.SBox, 
		sizeof(GOST28147_COMPRESSED_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147Hashed(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_GOST28147_HASHED_SBOX HashedSBox;

	memset((PVOID) &HashedSBox, 0, 
		sizeof(CSP_GOST28147_HASHED_SBOX));

	if(!ReadDataFromFile(pcFileName,
			(PVOID) &HashedSBox,
			sizeof(CSP_GOST28147_HASHED_SBOX)) &&
		!ReadPasswordProtectedDataFromFile(pcFileName,
			(PVOID) &HashedSBox,
			sizeof(CSP_GOST28147_HASHED_SBOX)))
	{
		return FALSE;
	}

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY(HashedSBox.Hash);
#endif

	if(m_pCSP->CheckDataHash((PBYTE) HashedSBox.SBox,
			sizeof(GOST28147_COMPRESSED_SBOX),
			HashParametersSBox, InitialHash,
			HashedSBox.Hash) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	memcpy((PVOID) pSBox, (PVOID) HashedSBox.SBox,
		sizeof(GOST28147_COMPRESSED_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145Hashed(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_DSTU4145_HASHED_PARAMETERS HashedParameters;
	BOOL bDSTUHash;

	memset((PVOID) &HashedParameters, 0,
		sizeof(CSP_DSTU4145_HASHED_PARAMETERS));

	bDSTUHash = FALSE;

	if(!ReadDataFromFile(pcFileName,
			(PVOID) &HashedParameters,
			sizeof(CSP_DSTU4145_HASHED_PARAMETERS)) &&
		!ReadPasswordProtectedDataFromFile(pcFileName,
			(PVOID) &HashedParameters,
			sizeof(CSP_DSTU4145_HASHED_PARAMETERS)))
	{
		bDSTUHash = TRUE;
	}

	if(bDSTUHash)
	{
		CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS
			DSTU7564HashedParameters;
		BOOL bCompatible;

		CSP_CHECK_COMPATIBLE(m_pCSP,
			CSP_COMPATIBLE_LEVEL_DSTU7564,
			bCompatible);
		if(!bCompatible)
			return FALSE;

		if(!ReadDataFromFile(pcFileName,
				(PVOID) &DSTU7564HashedParameters,
				sizeof(CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS)) &&
			!ReadDSTU7624PasswordProtectedDataFromFile(
				pcFileName, (PVOID) &DSTU7564HashedParameters,
				sizeof(CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS)))
		{
			return FALSE;
		}

		if(m_pCSP->DSTU7564CheckDataHash(
				(PBYTE) &DSTU7564HashedParameters,
				sizeof(DSTU4145_PARAMETER_EC) +
				sizeof(DSTU4145_PARAMETER_P),
				NULL, DSTU7564_HASH_256_LENGTH,
				DSTU7564HashedParameters.Hash) != CSP_NO_ERROR)
		{
			return FALSE;
		}

#ifdef HP_BIG_ENDIAN
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterEC.dwA);
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterEC.dwM);
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterEC.dwK1);
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterEC.dwK2);
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterEC.dwK3);
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterEC.dwCF);
		SWAP_BYTES_32_ARRAY(DSTU7564HashedParameters.ParameterEC.B);

		SWAP_BYTES_32_ARRAY(DSTU7564HashedParameters.ParameterP.dwX);
		SWAP_BYTES_32_ARRAY(DSTU7564HashedParameters.ParameterP.dwN);
		SWAP_BYTES_32_P(&DSTU7564HashedParameters.ParameterP.dwBits);
#endif

		memcpy((PVOID) pParameterEC,
			(PVOID) &DSTU7564HashedParameters.ParameterEC,
			sizeof(DSTU4145_PARAMETER_EC));
		memcpy((PVOID) pParameterP,
			(PVOID) &DSTU7564HashedParameters.ParameterP,
			sizeof(DSTU4145_PARAMETER_P));

		if(pSBox != NULL)
		{
			memcpy((PVOID) pSBox, (PVOID) FixedSBoxes[0],
				sizeof(GOST28147_COMPRESSED_SBOX));
		}
	}
	else
	{
#ifdef HP_BIG_ENDIAN
		SWAP_BYTES_32_ARRAY(HashedParameters.Hash);
#endif

		if(m_pCSP->CheckDataHash(
				(PBYTE) &HashedParameters.ParameterEC,
				sizeof(DSTU4145_PARAMETER_EC) +
				sizeof(DSTU4145_PARAMETER_P) +
				sizeof(GOST28147_COMPRESSED_SBOX),
				HashParametersSBox, InitialHash,
				HashedParameters.Hash) != CSP_NO_ERROR)
		{
			return FALSE;
		}

#ifdef HP_BIG_ENDIAN
		SWAP_BYTES_32_P(&HashedParameters.ParameterEC.dwA);
		SWAP_BYTES_32_P(&HashedParameters.ParameterEC.dwM);
		SWAP_BYTES_32_P(&HashedParameters.ParameterEC.dwK1);
		SWAP_BYTES_32_P(&HashedParameters.ParameterEC.dwK2);
		SWAP_BYTES_32_P(&HashedParameters.ParameterEC.dwK3);
		SWAP_BYTES_32_P(&HashedParameters.ParameterEC.dwCF);
		SWAP_BYTES_32_ARRAY(HashedParameters.ParameterEC.B);

		SWAP_BYTES_32_ARRAY(HashedParameters.ParameterP.dwX);
		SWAP_BYTES_32_ARRAY(HashedParameters.ParameterP.dwN);
		SWAP_BYTES_32_P(&HashedParameters.ParameterP.dwBits);
#endif

		memcpy((PVOID) pParameterEC,
			(PVOID) &HashedParameters.ParameterEC,
			sizeof(DSTU4145_PARAMETER_EC));
		memcpy((PVOID) pParameterP,
			(PVOID) &HashedParameters.ParameterP,
			sizeof(DSTU4145_PARAMETER_P));

		if(pSBox != NULL)
		{
			memcpy((PVOID) pSBox,
				(PVOID) HashedParameters.SBox,
				sizeof(GOST28147_COMPRESSED_SBOX));
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145DHashed(
	PCHAR pcFileName,
	PBYTE pbParameters,
	PDWORD pdwParameters)
{
	if(m_pCSP == NULL)
		return FALSE;

	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7564,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DENSE_NUMBERS,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	PBYTE pbFileData;
	DWORD cbFileData;
	PBYTE pbData;
	DWORD cbData;

	cbFileData = CSP_PARAMETERS_MAX_DATA_SIZE;
	pbFileData = new BYTE[cbFileData];
	if(pbFileData == NULL)
		return FALSE;

	if(!ReadDataFromFile(
			pcFileName, pbFileData, &cbFileData))
	{
		delete[] pbFileData;
		return FALSE;
	}

	if(IsDataPasswordProtected())
	{
		if(!UnprotectDSTU7624PasswordProtectedData(
				pbFileData, cbFileData, &pbData, &cbData))
		{
			memset(pbFileData, 0, cbFileData);
			delete[] pbFileData;
			return FALSE;
		}
	}
	else
	{
		cbData = cbFileData;
		pbData = pbFileData;
	}

	DWORD dwM;
	DWORD cbParameters;

	if(cbData < sizeof(DSTU4145_DENSE_PARAMETERS_DESC))
	{
		memset(pbFileData, 0, cbFileData);
		delete[] pbFileData;
		return FALSE;
	}

	dwM = DSTU4145_DENSE_PARAMETERS_M(pbData);
	cbParameters = sizeof(DSTU4145_DENSE_PARAMETERS_DESC) +
		DSTU4145_DENSE_PARAMETERS_SIZE(dwM);

	if(cbData != cbParameters + DSTU7564_HASH_256_LENGTH)
	{
		memset(pbFileData, 0, cbFileData);
		delete[] pbFileData;
		return FALSE;
	}

	if(m_pCSP->DSTU7564CheckDataHash(
			pbData, cbParameters,
			NULL, DSTU7564_HASH_256_LENGTH,
			pbData + cbData -
				DSTU7564_HASH_256_LENGTH) != CSP_NO_ERROR)
	{
		memset(pbFileData, 0, cbFileData);
		delete[] pbFileData;
		return FALSE;
	}

	if(pbParameters == NULL)
	{
		*pdwParameters = cbParameters;

		memset(pbFileData, 0, cbFileData);
		delete[] pbFileData;
		return TRUE;
	}

	if(*pdwParameters < cbParameters)
	{
		memset(pbFileData, 0, cbFileData);
		delete[] pbFileData;
		return FALSE;
	}

	memcpy((PVOID) pbParameters, (PVOID) pbData,
		cbParameters);
	*pdwParameters = cbParameters;

	memset(pbFileData, 0, cbFileData);
	delete[] pbFileData;
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::ECDHProtected(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_DSTU4145_PROTECTED_PARAMETERS ProtectedParameters;

	memset((PVOID) &ProtectedParameters, 0, 
		sizeof(CSP_DSTU4145_PROTECTED_PARAMETERS));

	if(!ReadDataFromFile(pcFileName, 
			(PVOID) &ProtectedParameters, 
			sizeof(CSP_DSTU4145_PROTECTED_PARAMETERS)) &&
		!ReadPasswordProtectedDataFromFile(pcFileName,
			(PVOID) &ProtectedParameters,
			sizeof(CSP_DSTU4145_PROTECTED_PARAMETERS)))
	{
		return FALSE;
	}

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_ARRAY(ProtectedParameters.MAC);
	SWAP_BYTES_32_ARRAY(ProtectedParameters.DataAligment);
	SWAP_BYTES_32_P(&ProtectedParameters.dwDataAligment);
#endif

	if(m_pCSP->UnprotectData((PBYTE) &ProtectedParameters.ParameterEC, 
		sizeof(DSTU4145_PARAMETER_EC) +
		sizeof(DSTU4145_PARAMETER_P) + 
		sizeof(GOST28147_COMPRESSED_SBOX),
		EncryptParametersSBox, InitialHash,
		ProtectedParameters.MAC, ProtectedParameters.DataAligment, 
		ProtectedParameters.dwDataAligment,
		NULL, EncryptParametersKey) != CSP_NO_ERROR)
	{
		return FALSE;
	}

#ifdef HP_BIG_ENDIAN
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterEC.dwA);
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterEC.dwM);
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterEC.dwK1);
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterEC.dwK2);
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterEC.dwK3);
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterEC.dwCF);
	SWAP_BYTES_32_ARRAY(ProtectedParameters.ParameterEC.B);

	SWAP_BYTES_32_ARRAY(ProtectedParameters.ParameterP.dwX);
	SWAP_BYTES_32_ARRAY(ProtectedParameters.ParameterP.dwN);
	SWAP_BYTES_32_P(&ProtectedParameters.ParameterP.dwBits);
#endif

	memcpy((PVOID) pParameterEC, 
		(PVOID) &ProtectedParameters.ParameterEC, 
		sizeof(DSTU4145_PARAMETER_EC));
	memcpy((PVOID) pParameterP, 
		(PVOID) &ProtectedParameters.ParameterP, 
		sizeof(DSTU4145_PARAMETER_P));
	memcpy((PVOID) pSBox, (PVOID) &ProtectedParameters.SBox, 
		sizeof(GOST28147_COMPRESSED_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147SaveProtected(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_GOST28147_PROTECTED_SBOX ProtectedSBox;

	memset((PVOID) &ProtectedSBox, 0, sizeof(CSP_GOST28147_PROTECTED_SBOX));

	memcpy((PVOID) ProtectedSBox.SBox, (PVOID) pSBox, 
		sizeof(GOST28147_COMPRESSED_SBOX));

	DWORD dwDataAligment;

	dwDataAligment = (DWORD) ProtectedSBox.dwDataAligment;

	if(m_pCSP->ProtectData((PBYTE) ProtectedSBox.SBox, 
		sizeof(GOST28147_COMPRESSED_SBOX), 
		EncryptParametersSBox, InitialHash,
		ProtectedSBox.MAC, ProtectedSBox.DataAligment, &dwDataAligment,
		NULL, EncryptParametersKey) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	ProtectedSBox.dwDataAligment = (UINT) dwDataAligment;

	if(IsDataPasswordProtected())
	{
		if(!WritePasswordProtectedDataToFile(pcFileName,
			(PVOID) &ProtectedSBox,
			sizeof(CSP_GOST28147_PROTECTED_SBOX)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(pcFileName,
			(PVOID) &ProtectedSBox,
			sizeof(CSP_GOST28147_PROTECTED_SBOX)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147SaveHashed(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_GOST28147_HASHED_SBOX HashedSBox;

	memset((PVOID) &HashedSBox, 0, sizeof(CSP_GOST28147_HASHED_SBOX));

	memcpy((PVOID) HashedSBox.SBox, (PVOID) pSBox, 
		sizeof(GOST28147_COMPRESSED_SBOX));

	if(m_pCSP->HashData((PBYTE) HashedSBox.SBox, 
		sizeof(GOST28147_COMPRESSED_SBOX), 
		HashParametersSBox, InitialHash,
		HashedSBox.Hash) != CSP_NO_ERROR)
		return FALSE;

	if(IsDataPasswordProtected())
	{
		if(!WritePasswordProtectedDataToFile(pcFileName,
			(PVOID) &HashedSBox,
			sizeof(CSP_GOST28147_HASHED_SBOX)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(pcFileName,
			(PVOID) &HashedSBox,
			sizeof(CSP_GOST28147_HASHED_SBOX)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145SaveHashed(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_DSTU4145_HASHED_PARAMETERS HashedParameters;

	memset((PVOID) &HashedParameters, 0, 
		sizeof(CSP_DSTU4145_HASHED_PARAMETERS));

	memcpy((PVOID) &HashedParameters.ParameterEC, 
		(PVOID) pParameterEC, sizeof(DSTU4145_PARAMETER_EC));
	memcpy((PVOID) &HashedParameters.ParameterP, 
		(PVOID) pParameterP, sizeof(DSTU4145_PARAMETER_P));
	memcpy((PVOID) HashedParameters.SBox, 
		(PVOID) pSBox, sizeof(GOST28147_COMPRESSED_SBOX));

	if(m_pCSP->HashData((PBYTE) &HashedParameters.ParameterEC, 
		sizeof(DSTU4145_PARAMETER_EC) +
		sizeof(DSTU4145_PARAMETER_P) + sizeof(GOST28147_COMPRESSED_SBOX),
		HashParametersSBox, InitialHash,
		HashedParameters.Hash) != CSP_NO_ERROR)
		return FALSE;

	if(IsDataPasswordProtected())
	{
		if(!WritePasswordProtectedDataToFile(pcFileName,
			(PVOID) &HashedParameters,
			sizeof(CSP_DSTU4145_HASHED_PARAMETERS)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(pcFileName,
			(PVOID) &HashedParameters,
			sizeof(CSP_DSTU4145_HASHED_PARAMETERS)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::ECDHSaveProtected(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_DSTU4145_PROTECTED_PARAMETERS ProtectedParameters;

	memset((PVOID) &ProtectedParameters, 0,
		sizeof(CSP_DSTU4145_PROTECTED_PARAMETERS));

	memcpy((PVOID) &ProtectedParameters.ParameterEC, 
		(PVOID) pParameterEC, sizeof(DSTU4145_PARAMETER_EC));
	memcpy((PVOID) &ProtectedParameters.ParameterP, 
		(PVOID) pParameterP, sizeof(DSTU4145_PARAMETER_P));
	memcpy((PVOID) ProtectedParameters.SBox, 
		(PVOID) pSBox, sizeof(GOST28147_COMPRESSED_SBOX));

	DWORD dwDataAligment;

	dwDataAligment = (DWORD) ProtectedParameters.dwDataAligment;

	if(m_pCSP->ProtectData((PBYTE) &ProtectedParameters.ParameterEC, 
		sizeof(DSTU4145_PARAMETER_EC) +
		sizeof(DSTU4145_PARAMETER_P) + sizeof(GOST28147_COMPRESSED_SBOX),
		EncryptParametersSBox, InitialHash,
		ProtectedParameters.MAC, ProtectedParameters.DataAligment, &dwDataAligment,
		NULL, EncryptParametersKey) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	ProtectedParameters.dwDataAligment = (UINT) dwDataAligment;

	if(IsDataPasswordProtected())
	{
		if(!WritePasswordProtectedDataToFile(pcFileName,
			(PVOID) &ProtectedParameters,
			sizeof(CSP_DSTU4145_PROTECTED_PARAMETERS)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(pcFileName, 
			(PVOID) &ProtectedParameters, 
			sizeof(CSP_DSTU4145_PROTECTED_PARAMETERS)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

#ifdef CSP_PARAMETERS_EXT
BOOL WINAPI CSPParameters::DSTU4145StandartEnum(
	BOOL bPolinomial,
	DWORD dwID,
	PDWORD pdwBits,
	PCHAR pszName,
	PCHAR pszOID)
{
	if(bPolinomial)
	{
		if(dwID > (DSTU4145_NAMED_CURVES_P_COUNT - 1))
			return FALSE;

		if(pdwBits != NULL)
			*pdwBits = NamedBasePointsP[dwID].dwBits;

		if(pszName != NULL)
			strcpy(pszName, szNamedCurveNamesP[dwID]);

		if(pszOID != NULL)
			strcpy(pszOID, szNamedCurveOIDsP[dwID]);
	}
	else
	{
		if(dwID > (DSTU4145_NAMED_CURVES_N_COUNT - 1))
			return FALSE;

		if(pdwBits != NULL)
			*pdwBits = NamedBasePointsN[dwID].dwBits;

		if(pszName != NULL)
			strcpy(pszName, szNamedCurveNamesN[dwID]);

		if(pszOID != NULL)
			strcpy(pszOID, szNamedCurveOIDsN[dwID]);
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145StandartFindByOID(
	PCHAR pszOID,
	PBOOL pbPolinomial,
	PDWORD pdwID)
{
	DWORD dwID;

	for(dwID = 0; dwID < DSTU4145_NAMED_CURVES_P_COUNT; dwID++)
	{
			if(strcmp(pszOID, szNamedCurveOIDsP[dwID]) == 0)
			{
				if(pbPolinomial != NULL)
					*pbPolinomial = TRUE;

				if(pdwID != NULL)
					*pdwID = dwID;

				return TRUE;
			}
	}

	for(dwID = 0; dwID < DSTU4145_NAMED_CURVES_N_COUNT; dwID++)
	{
			if(strcmp(pszOID, szNamedCurveOIDsN[dwID]) == 0)
			{
				if(pbPolinomial != NULL)
					*pbPolinomial = FALSE;

				if(pdwID != NULL)
					*pdwID = dwID;

				return TRUE;
			}
	}

	return FALSE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147FixedEnum(
	DWORD dwID,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	if(dwID > (GOST28147_FIXED_SBOXES_COUNT - 1)) 
		return FALSE;

	CopyMemory((PVOID) pSBox, (PVOID) FixedSBoxes[dwID], 
		sizeof(GOST28147_COMPRESSED_SBOX));
	
	return TRUE;
}
#endif // CSP_PARAMETERS_EXT

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::GOST28147ExternalFile(
	FILE *pFile,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	GOST28147_COMPRESSED_SBOX TempSBox;

	memset((PVOID) pSBox, 0, sizeof(GOST28147_COMPRESSED_SBOX));

	if(fseek(pFile, 0, SEEK_END) != 0 ||
		ftell(pFile) != sizeof(GOST28147_COMPRESSED_SBOX) ||
		fseek(pFile, 0, SEEK_SET) != 0 ||
		fread((PVOID) pSBox, 1,
			sizeof(GOST28147_COMPRESSED_SBOX),
			pFile) != sizeof(GOST28147_COMPRESSED_SBOX))
	{
		return FALSE;
	}

	PBYTE	pbSrc = (PBYTE) pSBox;
	PBYTE	pbDest = (PBYTE) TempSBox;

	for(INT i = 0; i < 4; i++)
	{
		for(INT j = 0; j < 8; j++)
		{
			pbDest[j * 2] = (pbSrc[j] >> 4) |
				(pbSrc[j + 8] & 0xF0);
			pbDest[j * 2 + 1] = (pbSrc[j] & 0x0F) |
				(pbSrc[j + 8] << 4);
		}

		pbSrc += 16;
		pbDest += 16;
	}

	memcpy((PVOID) pSBox, (PVOID) TempSBox, sizeof(GOST28147_COMPRESSED_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147External(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
#ifndef OS_NO_EXCEPTIONS
	__try
	{
#endif
		FILE *pFile;

		if((pFile = fopen(pcFileName, "rb")) == NULL)
			return FALSE;

		if(!GOST28147ExternalFile(pFile, pSBox))
		{
			fclose(pFile);
			return FALSE;
		}

		fclose(pFile);
		return TRUE;
#ifndef OS_NO_EXCEPTIONS
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
#endif
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::GOST28147SaveExternal(
	PCHAR pcFileName,
	GOST28147_COMPRESSED_SBOX pSBox)
{
	GOST28147_COMPRESSED_SBOX ExternalSBox;

	PBYTE	pbSrc = (PBYTE) pSBox;
	PBYTE	pbDest = (PBYTE) ExternalSBox;

	for(INT i = 0; i < 4; i++)
	{
		for(INT j = 0; j < 8; j++)
		{
			pbDest[j] = (pbSrc[j * 2] << 4) |
				(pbSrc[j * 2 + 1] & 0x0F);
			pbDest[j + 8] = (pbSrc[j * 2] & 0xF0) |
				(pbSrc[j * 2 + 1] >> 4);
		}

		pbSrc += 16;
		pbDest += 16;
	}

	if(!WriteDataToFile(pcFileName,
		(PVOID) &ExternalSBox,
		sizeof(GOST28147_COMPRESSED_SBOX)))
	{
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145SaveDSTU7564Hashed(
	PCHAR pcFileName,
	PDSTU4145_PARAMETER_EC pParameterEC,
	PDSTU4145_PARAMETER_P pParameterP)
{
	if(m_pCSP == NULL)
		return FALSE;

	CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS HashedParameters;
	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7564,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	memset((PVOID) &HashedParameters, 0,
		sizeof(CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS));

	memcpy((PVOID) &HashedParameters.ParameterEC,
		(PVOID) pParameterEC, sizeof(DSTU4145_PARAMETER_EC));
	memcpy((PVOID) &HashedParameters.ParameterP,
		(PVOID) pParameterP, sizeof(DSTU4145_PARAMETER_P));

	if(m_pCSP->DSTU7564HashData(
		(PBYTE) &HashedParameters,
		sizeof(DSTU4145_PARAMETER_EC) +
		sizeof(DSTU4145_PARAMETER_P),
		NULL, DSTU7564_HASH_256_LENGTH,
		HashedParameters.Hash) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	if(IsDataPasswordProtected())
	{
		if(!WriteDSTU7624PasswordProtectedDataToFile(
				pcFileName, (PVOID) &HashedParameters,
				sizeof(CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(
				pcFileName, (PVOID) &HashedParameters,
				sizeof(CSP_DSTU4145_DSTU7564_HASHED_PARAMETERS)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

VOID CSPParameters::DSTUSBoxesPerformFWHT(
	DSTUS_SUB_SBOX pTruthTable,
	PINT pnSpectre)
{
	INT nStep = 1, nLeft = 0, nNumOfBlocks;
	INT nRight, nIndex, nStepIndex;
	INT a, b;

	for(nIndex = 0; nIndex < DSTUS_SUB_SBOX_LENGTH; nIndex++)
	{
		pnSpectre[nIndex] = -2 *
			pTruthTable[DSTUS_SUB_SBOX_LENGTH - nIndex - 1] + 1;
	}

	while(nStep < DSTUS_SUB_SBOX_LENGTH) 
	{
		nLeft = 0;
		nNumOfBlocks = (DSTUS_SUB_SBOX_LENGTH / (nStep * 2));

		for(nIndex = 0; nIndex < nNumOfBlocks; nIndex++) 
		{
			nRight = nLeft + nStep;

			for(nStepIndex = 0; nStepIndex < nStep; nStepIndex++) 
			{
				a = pnSpectre[nRight];
				b = pnSpectre[nLeft];
				pnSpectre[nLeft] = a + b;
				pnSpectre[nRight] = a - b;
				nLeft++;
				nRight++;
			}

			nLeft = nRight;
		}

		nStep *= 2;
	}
}

//----------------------------------------------------------------------------------------------------------------------

INT CSPParameters::DSTUSBoxesGetNonlinearity(
	DSTUS_SUB_SBOX pSBox)
{
	DSTUS_SUB_SBOX pTruthTable;
	INT nSpectre[DSTUS_SUB_SBOX_LENGTH];
	INT nMaxSpectre = 0, nIndex;
	INT b;

	nMaxSpectre = 0;
	for(b = 1; b < DSTUS_SUB_SBOX_LENGTH ; b++) 
	{
		for(nIndex = 0; nIndex < DSTUS_SUB_SBOX_LENGTH; nIndex++) 
			pTruthTable[nIndex] = bDegreesTable[pSBox[nIndex] & b] & 0x01;

		DSTUSBoxesPerformFWHT(pTruthTable, nSpectre);

		for(nIndex = 0; nIndex < DSTUS_SUB_SBOX_LENGTH; nIndex++) 
		{
			if(nSpectre[nIndex] < 0)
				nSpectre[nIndex] = -nSpectre[nIndex];

			if(nSpectre[nIndex] > nMaxSpectre)
				nMaxSpectre = nSpectre[nIndex];
		}
	}

	return 128 - nMaxSpectre / 2;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::DSTUSBoxesCheckBijectivity(
	DSTUS_SUB_SBOX pSBox)
{
	INT nCounts[256];
	INT nIndex;
	
	for(nIndex = 0; nIndex < 256; nIndex++) 
		nCounts[nIndex] = 0;

	for(nIndex = 0; nIndex < DSTUS_SUB_SBOX_LENGTH; nIndex++) 
		nCounts[pSBox[nIndex]]++;
	
	for(nIndex = 0; nIndex < DSTUS_SUB_SBOX_LENGTH; nIndex++) 
	{
		if(nCounts[nIndex] != 1)
			return FALSE;
	}
	
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::DSTU7624Check(
	DSTU7624_SBOX pSBox)
{
	DSTUS_SBOX SBox;
	
	memcpy((PVOID) SBox, (PVOID) pSBox, sizeof(DSTUS_SBOX));

	INT nNonlinearity;

	for(INT nSubSBox = 0; nSubSBox < DSTUS_SUB_SBOX_COUNT; nSubSBox++)
	{
		if(!DSTUSBoxesCheckBijectivity(SBox[nSubSBox]))
		{
			memset((PVOID) SBox, 0, sizeof(DSTUS_SBOX));

			return FALSE;
		}
		
		nNonlinearity = DSTUSBoxesGetNonlinearity(SBox[nSubSBox]);
		if(nNonlinearity < DSTUS_SBOX_MIN_NONLINEARITY)
		{
			memset((PVOID) SBox, 0, sizeof(DSTUS_SBOX));

			return FALSE;
		}
	}
	
	memset((PVOID) SBox, 0, sizeof(DSTUS_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL CSPParameters::DSTU8845Check(
	DSTU8845_SBOX pSBox)
{
	DSTUS_SBOX SBox;
	
	memcpy((PVOID) SBox, (PVOID) pSBox, sizeof(DSTUS_SBOX));

	INT nNonlinearity;

	for(INT nSubSBox = 0; nSubSBox < DSTUS_SUB_SBOX_COUNT; nSubSBox++)
	{
		if(!DSTUSBoxesCheckBijectivity(SBox[nSubSBox]))
		{
			memset((PVOID) SBox, 0, sizeof(DSTUS_SBOX));

			return FALSE;
		}
		
		nNonlinearity = DSTUSBoxesGetNonlinearity(SBox[nSubSBox]);
		if(nNonlinearity < DSTUS_SBOX_MIN_NONLINEARITY)
		{
			memset((PVOID) SBox, 0, sizeof(DSTUS_SBOX));

			return FALSE;
		}
	}
	
	memset((PVOID) SBox, 0, sizeof(DSTUS_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU7624Protected(
	PCHAR pcFileName,
	DSTU7624_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	BYTE ProtectedSBox[DSTU7624_PROTECTED_DATA(
		sizeof(DSTU7624_SBOX), DSTU7624_BLOCK_256_LENGTH)];
	PBYTE pUnprotectedSBox;
	DWORD cbUnprotectedSBox;
	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	if(!ReadDataFromFile(
			pcFileName, (PVOID) ProtectedSBox,
			sizeof(ProtectedSBox)) &&
		!ReadDSTU7624PasswordProtectedDataFromFile(
			pcFileName, (PVOID) &ProtectedSBox,
			sizeof(ProtectedSBox)))
	{
		return FALSE;
	}

	if(m_pCSP->DSTU7624UnprotectDataEx(
			ProtectedSBox, sizeof(ProtectedSBox),
			&pUnprotectedSBox, &cbUnprotectedSBox,
			NULL, NULL, DSTU7624EncryptParametersKey,
			DSTU7624_KEY_256_LENGTH) != CSP_NO_ERROR ||
		cbUnprotectedSBox != sizeof(DSTU7624_SBOX))
	{
		memset((PVOID) ProtectedSBox, 0, sizeof(ProtectedSBox));

		return FALSE;
	}

	if(!DSTU7624Check(pUnprotectedSBox))
	{
		memset((PVOID) ProtectedSBox, 0, sizeof(ProtectedSBox));

		return FALSE;
	}

	memcpy((PVOID) pSBox, (PVOID) pUnprotectedSBox,
		sizeof(DSTU7624_SBOX));

	memset((PVOID) ProtectedSBox, 0, sizeof(ProtectedSBox));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU7624SaveProtected(
	PSTR pszFileName,
	DSTU7624_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	if(!DSTU7624Check(pSBox))
		return FALSE;

	BYTE ProtectedSBox[DSTU7624_PROTECTED_DATA(
		sizeof(DSTU7624_SBOX), DSTU7624_BLOCK_256_LENGTH)];
	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	if(m_pCSP->DSTU7624ProtectDataEx(
			pSBox, sizeof(DSTU7624_SBOX),
			ProtectedSBox, sizeof(ProtectedSBox),
			NULL, NULL, DSTU7624EncryptParametersKey,
			DSTU7624_KEY_256_LENGTH, NULL,
			DSTU7624_IV_256_LENGTH,
			DSTU7624_MAC_256_LENGTH) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	if(IsDataPasswordProtected())
	{
		if(!WriteDSTU7624PasswordProtectedDataToFile(
				pszFileName, (PVOID) ProtectedSBox,
				sizeof(ProtectedSBox)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(
				pszFileName, (PVOID) ProtectedSBox,
				sizeof(ProtectedSBox)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU8845SaveProtected(
	PSTR pszFileName,
	DSTU8845_SBOX pSBox)
{
	if(m_pCSP == NULL)
		return FALSE;

	if(!DSTU8845Check(pSBox))
		return FALSE;

	BYTE ProtectedSBox[DSTU7624_PROTECTED_DATA(
		sizeof(DSTU8845_SBOX), DSTU7624_BLOCK_256_LENGTH)];
	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7624_PROTECT_DATA,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	if(m_pCSP->DSTU7624ProtectDataEx(
			pSBox, sizeof(DSTU8845_SBOX),
			ProtectedSBox, sizeof(ProtectedSBox),
			NULL, NULL, DSTU7624EncryptParametersKey,
			DSTU7624_KEY_256_LENGTH, NULL,
			DSTU7624_IV_256_LENGTH,
			DSTU7624_MAC_256_LENGTH) != CSP_NO_ERROR)
	{
		return FALSE;
	}

	if(IsDataPasswordProtected())
	{
		if(!WriteDSTU7624PasswordProtectedDataToFile(
				pszFileName, (PVOID) ProtectedSBox,
				sizeof(ProtectedSBox)))
		{
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(
				pszFileName, (PVOID) ProtectedSBox,
				sizeof(ProtectedSBox)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU7624External(
	PSTR pszFileName,
	DSTU7624_SBOX pSBox)
{
	memset((PVOID) pSBox, 0, sizeof(DSTU7624_SBOX));

	DSTU7624_EXTERNAL_SBOX ExternalSBox;

	if(!ReadDataFromFile(pszFileName,
		(PVOID) &ExternalSBox,
		sizeof(DSTU7624_EXTERNAL_SBOX)))
	{
		memset((PVOID) &ExternalSBox, 0, sizeof(DSTU7624_EXTERNAL_SBOX));

		return FALSE;
	}

	if(ExternalSBox.uiCRC != m_pCSP->Base.ExtensionF.CRC32Count(
		(PBYTE) &ExternalSBox, sizeof(DSTU7624_EXTERNAL_SBOX) - sizeof(UINT)))
	{
		memset((PVOID) &ExternalSBox, 0, sizeof(DSTU7624_EXTERNAL_SBOX));

		return FALSE;
	}

	if(!DSTU7624Check(ExternalSBox.SBox))
	{
		memset((PVOID) &ExternalSBox, 0, sizeof(DSTU7624_EXTERNAL_SBOX));

		return FALSE;
	}

	memcpy((PVOID) pSBox,
		(PVOID) ExternalSBox.SBox, sizeof(DSTU7624_SBOX));

	memset((PVOID) &ExternalSBox, 0, sizeof(DSTU7624_EXTERNAL_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU8845External(
	PSTR pszFileName,
	DSTU8845_SBOX pSBox)
{
	memset((PVOID) pSBox, 0, sizeof(DSTU8845_SBOX));

	DSTU8845_EXTERNAL_SBOX ExternalSBox;

	if(!ReadDataFromFile(pszFileName,
		(PVOID) &ExternalSBox,
		sizeof(DSTU8845_EXTERNAL_SBOX)))
	{
		memset((PVOID) &ExternalSBox, 0, sizeof(DSTU8845_EXTERNAL_SBOX));

		return FALSE;
	}

	if(ExternalSBox.uiCRC != m_pCSP->Base.ExtensionF.CRC32Count(
		(PBYTE) &ExternalSBox, sizeof(DSTU8845_EXTERNAL_SBOX) - sizeof(UINT)))
	{
		memset((PVOID) &ExternalSBox, 0, sizeof(DSTU8845_EXTERNAL_SBOX));

		return FALSE;
	}

	if(!DSTU8845Check(ExternalSBox.SBox))
	{
		memset((PVOID) &ExternalSBox, 0, sizeof(DSTU8845_EXTERNAL_SBOX));

		return FALSE;
	}

	memcpy((PVOID) pSBox,
		(PVOID) ExternalSBox.SBox, sizeof(DSTU8845_SBOX));

	memset((PVOID) &ExternalSBox, 0, sizeof(DSTU8845_EXTERNAL_SBOX));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::IsDefaultDSTU7624(
	DSTU7624_SBOX pSBox)
{
	return (memcmp(pSBox, DSTU7624DefaultSBox,
		sizeof(DSTU7624_SBOX)) == 0);
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::IsDefaultDSTU8845(
	DSTU8845_SBOX pSBox)
{
	return (memcmp(pSBox, DSTU7624DefaultSBox,
		sizeof(DSTU7624_SBOX)) == 0);
}

//----------------------------------------------------------------------------------------------------------------------

BOOL WINAPI CSPParameters::DSTU4145DSaveDSTU7564Hashed(
	PCHAR pcFileName,
	PBYTE pbParameters,
	DWORD dwParameters)
{
	if(m_pCSP == NULL)
		return FALSE;

	BOOL bCompatible;

	CSP_CHECK_COMPATIBLE(m_pCSP,
		CSP_COMPATIBLE_LEVEL_DSTU7564,
		bCompatible);
	if(!bCompatible)
		return FALSE;

	PBYTE pbFileData;
	DWORD cbFileData;

	cbFileData = dwParameters + DSTU7564_HASH_256_LENGTH;
	pbFileData = new BYTE[cbFileData];
	if(pbFileData == NULL)
		return FALSE;

	memcpy((PVOID) pbFileData, (PVOID) pbParameters,
		dwParameters);

	if(m_pCSP->DSTU7564HashData(
			(PBYTE) pbFileData, dwParameters,
			NULL, DSTU7564_HASH_256_LENGTH,
			pbFileData + dwParameters) != CSP_NO_ERROR)
	{
		memset(pbFileData, 0, dwParameters);
		delete[] pbFileData;
		return FALSE;
	}

	if(IsDataPasswordProtected())
	{
		if(!WriteDSTU7624PasswordProtectedDataToFile(
				pcFileName, (PVOID) pbFileData, cbFileData))
		{
			memset(pbFileData, 0, cbFileData);
			delete[] pbFileData;
			return FALSE;
		}
	}
	else
	{
		if(!WriteDataToFile(
				pcFileName, (PVOID) pbFileData, cbFileData))
		{
			memset(pbFileData, 0, cbFileData);
			delete[] pbFileData;
			return FALSE;
		}
	}

	memset(pbFileData, 0, cbFileData);
	delete[] pbFileData;
	return TRUE;
}

//======================================================================================================================
