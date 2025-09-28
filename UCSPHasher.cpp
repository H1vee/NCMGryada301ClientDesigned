//==============================================================================

#include "UCSPHasher.h"

#include <qlogging.h>
#include <QDebug>
#ifdef OS_MAC
#include <QDir>
#endif

//==============================================================================

#ifdef OS_MAC
#include <mach-o/dyld.h>
#include <libgen.h>
#include <string.h>
#include <stdio.h>

char g_csphPath[PATH_MAX];
char g_listPath[PATH_MAX];
char g_reportPath[PATH_MAX];

void UCSPHasherInitPaths() {
    char exePath[PATH_MAX];
    uint32_t size = sizeof(exePath);

    if (_NSGetExecutablePath(exePath, &size) != 0) {
        strcpy(g_csphPath, "./csph.file");
        strcpy(g_listPath, "pi.lst");
        strcpy(g_reportPath, "pic.rep");
        return;
    }

    char exePathCopy[PATH_MAX];
    strncpy(exePathCopy, exePath, sizeof(exePathCopy));
    exePathCopy[sizeof(exePathCopy) - 1] = '\0';

    char* macOSDirC = dirname(exePathCopy);
    QString macOSDir = QString::fromUtf8(macOSDirC);

    QDir::setCurrent(macOSDir);

    QString csphPath = QDir(macOSDir).filePath("csph.file");

    QString resourcesDir = QDir(macOSDir).filePath("../Resources");
    QString listPath = QDir(resourcesDir).filePath("pi.lst");
    QString reportPath = QDir(resourcesDir).filePath("pic.rep");

    csphPath = QDir::cleanPath(csphPath);
    listPath = QDir::cleanPath(listPath);
    reportPath = QDir::cleanPath(reportPath);

    strncpy(g_csphPath, csphPath.toUtf8().constData(), sizeof(g_csphPath));
    g_csphPath[sizeof(g_csphPath) - 1] = '\0';

    strncpy(g_listPath, listPath.toUtf8().constData(), sizeof(g_listPath));
    g_listPath[sizeof(g_listPath) - 1] = '\0';

    strncpy(g_reportPath, reportPath.toUtf8().constData(), sizeof(g_reportPath));
    g_reportPath[sizeof(g_reportPath) - 1] = '\0';
}

#endif // OS_MAC

//==============================================================================

BOOL UCSPHasherExecuteProgramm(
    PSTR    pszCommandLine)
{
#ifndef OS_NIX
    HANDLE    hProcess, hThread;

    STARTUPINFO        si;
    PROCESS_INFORMATION     pi;

    ZeroMemory((PVOID) &si, sizeof(STARTUPINFO));

    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    ZeroMemory((PVOID) &pi, sizeof(PROCESS_INFORMATION));

    if(!CreateProcessA(NULL, pszCommandLine,
            NULL, NULL, FALSE,
            0, NULL, NULL, LPSTARTUPINFOA(&si), &pi))
    {
        return FALSE;
    }


    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD    dwExitCode;    

    if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
        return FALSE;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if(dwExitCode != 0)
        return FALSE;
#else // OS_NIX
    if(system(pszCommandLine) != 0)
        return FALSE;
#endif // OS_NIX

    return TRUE;
}

//==============================================================================

BOOL UCSPHasherHashFiles(
    BOOL    blHashDSTU7564)
{
    CHAR    szCommandLine[MAX_PATH * 4 + 1];

#ifdef OS_MAC
    sprintf(szCommandLine,
        "\"%s\" %s \"%s\" \"%s\" %s",
        g_csphPath,
        CSP_HASHER_HASH_COMMAND,
        g_listPath,
        g_reportPath,
        blHashDSTU7564 ?
            CSP_HASHER_HASH_DSTU7564 :
            CSP_HASHER_HASH_GOST34311);
#else
    sprintf(szCommandLine,
        "%s %s %s %s %s",
        CSP_HASHER_FILE_NAME,
        CSP_HASHER_HASH_COMMAND,
        UCSP_HASHER_LIST_FILE_NAME,
        UCSP_HASHER_REPORT_FILE_NAME,
        blHashDSTU7564 ? 
            CSP_HASHER_HASH_DSTU7564 :
            CSP_HASHER_HASH_GOST34311);
#endif

    if(!UCSPHasherExecuteProgramm(szCommandLine))
    {
        CHAR    szTempFolder[MAX_PATH * 4 + 1];

        GetTempPathA(MAX_PATH * 4, szTempFolder);

        CHAR    szReportFile[MAX_PATH * 4 + 1];

        GetTempFileNameA(szTempFolder, UCSP_HASHER_REPORT_FILE_NAME,
             0, szReportFile);

#ifdef OS_MAC
        sprintf(szCommandLine,
            "\"%s\" %s \"%s\" \"%s\" %s",
            g_csphPath,
            CSP_HASHER_HASH_COMMAND,
            g_listPath,
            szReportFile,
            blHashDSTU7564 ?
                CSP_HASHER_HASH_DSTU7564 :
                CSP_HASHER_HASH_GOST34311);
#else
        sprintf(szCommandLine,
            "%s %s %s %s %s",
            CSP_HASHER_FILE_NAME,
            CSP_HASHER_HASH_COMMAND,
            UCSP_HASHER_LIST_FILE_NAME,
            szReportFile,
            blHashDSTU7564 ? 
                CSP_HASHER_HASH_DSTU7564 :
                CSP_HASHER_HASH_GOST34311);
#endif

        if(!UCSPHasherExecuteProgramm(szCommandLine))
            return FALSE;
    }

    return TRUE;
}

//------------------------------------------------------------------------------

BOOL UCSPHasherCheckFiles(
    BOOL    blHashDSTU7564)
{
    CHAR    szCommandLine[MAX_PATH * 4 + 1];

#ifdef OS_MAC
    sprintf(szCommandLine,
        "\"%s\" %s \"%s\" \"%s\" %s",
        g_csphPath,
        CSP_HASHER_CHECK_COMMAND,
        g_listPath,
        g_reportPath,
        blHashDSTU7564 ?
            CSP_HASHER_HASH_DSTU7564 :
            CSP_HASHER_HASH_GOST34311);
#else
    sprintf(szCommandLine,
        "%s %s %s %s %s",
        CSP_HASHER_FILE_NAME,
        CSP_HASHER_CHECK_COMMAND,
        UCSP_HASHER_LIST_FILE_NAME,
        UCSP_HASHER_REPORT_FILE_NAME,
        blHashDSTU7564 ? 
            CSP_HASHER_HASH_DSTU7564 :
            CSP_HASHER_HASH_GOST34311);
#endif

    if(!UCSPHasherExecuteProgramm(szCommandLine))
    {
        CHAR    szTempFolder[MAX_PATH * 4 + 1];

        GetTempPathA(MAX_PATH * 4, szTempFolder);
        CHAR    szReportFile[MAX_PATH * 4 + 1];

        GetTempFileNameA(szTempFolder, UCSP_HASHER_REPORT_FILE_NAME,
            0, szReportFile);

#ifdef OS_MAC
        sprintf(szCommandLine,
            "\"%s\" %s \"%s\" \"%s\" %s",
            g_csphPath,
            CSP_HASHER_CHECK_COMMAND,
            g_listPath,
            szReportFile,
            blHashDSTU7564 ?
                CSP_HASHER_HASH_DSTU7564 :
                CSP_HASHER_HASH_GOST34311);
#else
        sprintf(szCommandLine,
            "%s %s %s %s %s",
            CSP_HASHER_FILE_NAME,
            CSP_HASHER_CHECK_COMMAND,
            UCSP_HASHER_LIST_FILE_NAME,
            szReportFile,
            blHashDSTU7564 ? 
                CSP_HASHER_HASH_DSTU7564 :
                CSP_HASHER_HASH_GOST34311);
#endif

        if(!UCSPHasherExecuteProgramm(szCommandLine))
            return FALSE;
    }

    return TRUE;
}

//==============================================================================

#ifdef UCSP_HASHER_TEST
INT main(INT argc, PCHAR argv[])
{
    printf("UCSPHasher: Hashing files (HF GOST 34.311-95)...\n");

    if(!UCSPHasherHashFiles())
    {
        printf("UCSPHasher: Failed to hash files\n");

        return -1;
    }

    printf("UCSPHasher: Checking files (HF GOST 34.311-95)...\n");

    if(!UCSPHasherCheckFiles())
    {
        printf("UCSPHasher: Failed to check files\n");

        return -1;
    }

    printf("UCSPHasher: Hashing files (HF DSTU 7564:2014)...\n");

    if(!UCSPHasherHashFiles(TRUE))
    {
        printf("UCSPHasher: Failed to hash files\n");

        return -1;
    }

    printf("UCSPHasher: Checking files (HF DSTU 7564:2014)...\n");

    if(!UCSPHasherCheckFiles(TRUE))
    {
        printf("UCSPHasher: Failed to check files\n");

        return -1;
    }

    printf("CSPHasher: Completed successfully.\n"
        "\tFiles were hashed and checked");

    return 0;
}
#endif // UCSP_HASHER_TEST

//==============================================================================