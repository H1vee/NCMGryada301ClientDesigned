#ifndef UCSP_HASHER_H
#define UCSP_HASHER_H

//==============================================================================

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#ifdef OS_MAC
#include <limits.h>
extern char g_csphPath[PATH_MAX];
extern char g_listPath[PATH_MAX];
extern char g_reportPath[PATH_MAX];
void UCSPHasherInitPaths();
#endif
#else // OS_NIX
#include <windows.h>
#include <stdio.h>
#endif // OS_NIX

//==============================================================================

#ifndef OS_NIX
#define CSP_HASHER_FILE_NAME "CSPHasher.exe"
#define UCSP_HASHER_LIST_FILE_NAME "PInstall.lst"
#define UCSP_HASHER_REPORT_FILE_NAME "PInstallCheck.rep"
#else // OS_NIX
#ifdef OS_MAC
#define CSP_HASHER_FILE_NAME "./csph.file"
#else
#define CSP_HASHER_FILE_NAME "./csph"
#endif
#define UCSP_HASHER_LIST_FILE_NAME "pi.lst"
#define UCSP_HASHER_REPORT_FILE_NAME "pic.rep"
#endif // OS_NIX

#define CSP_HASHER_HASH_COMMAND "/hash /files"
#define CSP_HASHER_CHECK_COMMAND "/check /files"
#define CSP_HASHER_HASH_GOST34311 "/hgost34311"
#define CSP_HASHER_HASH_DSTU7564 "/hdstu7564"

//==============================================================================

BOOL UCSPHasherHashFiles(BOOL blHashDSTU7564 = FALSE);
BOOL UCSPHasherCheckFiles(BOOL blHashDSTU7564 = FALSE);

//==============================================================================

#endif // UCSP_HASHER_H