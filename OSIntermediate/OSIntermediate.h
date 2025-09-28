#ifndef OS_INTERMEDIATE_H
#define OS_INTERMEDIATE_H

//===============================================================================

#ifdef OS_NIX

//===============================================================================

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif // _THREAD_SAFE

#ifndef _REENTERANT
#define _REENTERANT
#endif // _REENTERANT

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <limits.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>
#include <dlfcn.h>
#include <fnmatch.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wchar.h>
#include <stdint.h>
#include <signal.h>
#include <stddef.h>

#ifdef OS_LINUX
#include <linux/rtc.h>
#include <sys/ioctl.h>
#endif

#ifdef HS_USB_DEVICE
typedef struct
{
    int iProduct;
    int iSerialNumber;
} USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;
#endif

#ifdef OS_UNIX
#include <netinet/in.h>

#ifdef OS_SUNOS
#include <atomic.h>
#endif // OS_SUNOS

#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif // OS_UNIX

#ifdef OS_AIX
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#define HP_BIG_ENDIAN
#endif // OS_AIX

#ifdef OS_HPUX
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#define HP_BIG_ENDIAN
#endif // SPARC

#ifdef EM_SDK
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif // EM_SDK

#ifdef HP_SPARC
#define HP_BIG_ENDIAN
#endif // SPARC

#ifdef HP_AVR
#define HP_BIG_ENDIAN
#endif // HP_AVR

//===============================================================================

#ifdef __GNUC__
#define IGNORE_RESULT(x) ({ typeof(x) z = x; (void)sizeof z; })
#define PACKED __attribute__((packed))
#else
#define IGNORE_RESULT(x) x
#define PACKED
#endif // __GNUC__

//===============================================================================

#ifndef ANDROID_NDK
#define CONSTRUCTOR(x) void __attribute__((constructor)) x()
#define DESTRUCTOR(x) void __attribute__((destructor)) x()
#else // ANDROID_NDK
#define CONSTRUCTOR(x) void x()
#define DESTRUCTOR(x) void x()
#endif // ANDROID_NDK

//===============================================================================

#ifndef OS_SYSTEM_DIRECTORY
	#if (defined(X86_64) && defined(OS_LINUX)) || defined(OS_RHEL4)
		#define OS_SYSTEM_DIRECTORY "/lib64"
	#elif defined(ANDROID_NDK)
		#define OS_SYSTEM_DIRECTORY "/system/lib"
	#else
		#define OS_SYSTEM_DIRECTORY "/lib"
	#endif
#endif // OS_SYSTEM_DIRECTORY

//===============================================================================

#ifdef HP_BIG_ENDIAN
#define SWAP_DWORDS_64(dwl) ((((dwl) << 32) & 0xFFFFFFFF00000000LL) |   \
	(((dwl >> 32)) & 0x00000000FFFFFFFFLL))
#define SWAP_DWORDS_64_P(pll) \
		SET_BYTES_AS_ULONGLONG((pll), 0, SWAP_DWORDS_64(\
			GET_BYTES_AS_ULONGLONG((pll), 0)))

#define SWAP_BYTES_32(dw) 						\
	((((dw) << 24) & 0xFF000000) | (((dw) << 8) & 0x00FF0000) | 	\
	(((dw) >> 8) & 0x0000FF00) | (((dw) >> 24) & 0x000000FF))

#define SWAP_BYTES_32_P(pdw) \
		SET_BYTES_AS_DWORD((pdw), 0, SWAP_BYTES_32(GET_BYTES_AS_DWORD((pdw), 0)))

#define SWAP_BYTES_32_ARRAY_SIZE(arr, size)                             \
    {                                                                   \
        DWORD dwSAIndex;                                                \
        for(dwSAIndex = 0; dwSAIndex < (size); dwSAIndex ++)            \
        {                                                               \
            SWAP_BYTES_32_P(((PUINT) (arr)) + dwSAIndex);               \
        }                                                               \
    }

#define SWAP_BYTES_32_ARRAY(arr)                                        \
    SWAP_BYTES_32_ARRAY_SIZE(arr, (sizeof((arr)) / sizeof(UINT)))

#define SWAP_BYTES_16(w) ((((w) << 8) & 0xFF00) | (((w) >> 8) & 0x00FF))
#define SWAP_BYTES_16_P(pw) *(pw) = SWAP_BYTES_16(*(pw));
#define SWAP_BYTES_16_ARRAY_SIZE(arr, size)                             \
    {                                                                   \
        DWORD dwSAIndex;                                                \
        for(dwSAIndex = 0; dwSAIndex < (size); dwSAIndex ++)            \
        {                                                               \
            SWAP_BYTES_16_P(((PWORD) (arr)) + dwSAIndex);               \
        }                                                               \
    }
#define SWAP_BYTES_16_ARRAY(arr)                                        \
    SWAP_BYTES_16_ARRAY_SIZE(arr, (sizeof((arr)) / sizeof(WORD)))

#define SWAP_WORDS_32(dw) 						\
	((((dw) << 16) & 0xFFFF0000) | (((dw >> 16)) & 0x0000FFFF))
#define SWAP_WORDS_32_P(pdw) \
		SET_BYTES_AS_DWORD((pdw), 0, SWAP_WORDS_32(GET_BYTES_AS_DWORD((pdw), 0)))
#define SWAP_WORDS_32_ARRAY_SIZE(arr, size)                             \
    {                                                                   \
        DWORD dwSAIndex;                                                \
        for(dwSAIndex = 0; dwSAIndex < (size); dwSAIndex ++)            \
        {                                                               \
            SWAP_WORDS_32_P(((PUINT) (arr)) + dwSAIndex);               \
        }                                                               \
    }
#define SWAP_WORDS_32_ARRAY(arr)                                        \
    SWAP_WORDS_32_ARRAY_SIZE(arr, (sizeof((arr)) / sizeof(UINT)))

#define SWAP_SYSTEMTIME(time)                   \
    do {                                        \
        SWAP_PWORD(&(time).wYear);              \
        SWAP_PWORD(&(time).wMonth);             \
        SWAP_PWORD(&(time).wDayOfWeek);         \
        SWAP_PWORD(&(time).wDay);               \
        SWAP_PWORD(&(time).wHour);              \
        SWAP_PWORD(&(time).wMinute);            \
        SWAP_PWORD(&(time).wSecond);            \
        SWAP_PWORD(&(time).wMilliseconds);      \
    } while (0)

#define SWAP_PWORD(pw)                          \
    do                                          \
    {                                           \
        SWAP_BYTES_16_P(pw);                    \
    } while (0)

#define SWAP_PDWORD(pdw)                        \
    do                                          \
    {                                           \
        SWAP_BYTES_32_P(pdw);                   \
    } while (0)

#define SWAP_PUINT(pdw) SWAP_PDWORD(pdw)
#define SWAP_PBOOL(pbl) SWAP_PDWORD(pbl)

#define SWAP_PSYSTEMTIME(time)                  \
    do                                          \
    {                                           \
        SWAP_PWORD(&(time)->wYear);             \
        SWAP_PWORD(&(time)->wMonth);            \
        SWAP_PWORD(&(time)->wDayOfWeek);        \
        SWAP_PWORD(&(time)->wDay);              \
        SWAP_PWORD(&(time)->wHour);             \
        SWAP_PWORD(&(time)->wMinute);           \
        SWAP_PWORD(&(time)->wSecond);           \
        SWAP_PWORD(&(time)->wMilliseconds);     \
    } while (0)


#define SWAP_DWORDLONG(ull)                     \
    ((ull >> 56)                                \
    | ((ull << 40) & 0x00FF000000000000)        \
    | ((ull << 24) & 0x0000FF0000000000)        \
    | ((ull << 8) & 0x000000FF00000000)         \
    | ((ull >> 8) & 0x00000000FF000000)         \
    | ((ull >> 24) & 0x0000000000FF0000)        \
    | ((ull >> 40) & 0x000000000000FF00)        \
    | (ull << 56))

#define SWAP_PDWORDLONG(pdwl)                   \
    *(pdwl) = SWAP_DWORDLONG(*(pdwl))
#endif // HP_BIG_ENDIAN

#ifdef HP_BIG_ENDIAN
	#define GET_BYTES_AS_DWORD(arr, idx) \
		(	((PBYTE)arr)[idx + 0]	<< 24 |	\
			((PBYTE)arr)[idx + 1]	<< 16 |	\
			((PBYTE)arr)[idx + 2]	<<  8 | \
			((PBYTE)arr)[idx + 3]	<<  0	)
	#define GET_BYTES_AS_ULONGLONG(arr, idx) \
		(	(ULONGLONG)(((PBYTE)arr)[idx + 0])	<< 56 |	\
			(ULONGLONG)(((PBYTE)arr)[idx + 1])	<< 48 |	\
			(ULONGLONG)(((PBYTE)arr)[idx + 2])	<< 40 | \
			(ULONGLONG)(((PBYTE)arr)[idx + 3])	<< 32 | \
			(ULONGLONG)(((PBYTE)arr)[idx + 4])	<< 24 |	\
			(ULONGLONG)(((PBYTE)arr)[idx + 5])	<< 16 |	\
			(ULONGLONG)(((PBYTE)arr)[idx + 6])	<<  8 | \
			(ULONGLONG)(((PBYTE)arr)[idx + 7])	<<  0	)
	#define GET_WORDS_AS_DWORD(arr, idx) ( arr[idx] << 16 | arr[idx + 1] )
	#define GET_DWORDS_AS_ULONGLONG(arr, idx) ( arr[idx] << 32 | arr[idx + 1] )
	#define SET_BYTES_AS_DWORD(arr, idx, val)	\
	do {										\
		const DWORD dwValue = val;				\
		((PBYTE)arr)[idx + 0] = (dwValue >> 24) & 0xFF;	\
		((PBYTE)arr)[idx + 1] = (dwValue >> 16) & 0xFF;	\
		((PBYTE)arr)[idx + 2] = (dwValue >>  8) & 0xFF;	\
		((PBYTE)arr)[idx + 3] = (dwValue >>  0) & 0xFF;	\
	} while (0)
	#define SET_BYTES_AS_ULONGLONG(arr, idx, val)	\
	do {										\
		const ULONGLONG ullValue = val;				\
		((PBYTE)arr)[idx + 0] = (ullValue >> 56) & 0xFF;	\
		((PBYTE)arr)[idx + 1] = (ullValue >> 48) & 0xFF;	\
		((PBYTE)arr)[idx + 2] = (ullValue >> 40) & 0xFF;	\
		((PBYTE)arr)[idx + 3] = (ullValue >> 32) & 0xFF;	\
		((PBYTE)arr)[idx + 4] = (ullValue >> 24) & 0xFF;	\
		((PBYTE)arr)[idx + 5] = (ullValue >> 16) & 0xFF;	\
		((PBYTE)arr)[idx + 6] = (ullValue >>  8) & 0xFF;	\
		((PBYTE)arr)[idx + 7] = (ullValue >>  0) & 0xFF;	\
	} while (0)
	#define SET_ULONGLONG_AS_DWORDS(arr, idx, val)	\
	do {										\
		const ULONGLONG ullValue = val;				\
		arr[idx + 0] = (ullValue >> 32) & 0xFFFFFFFF;	\
		arr[idx + 1] = (ullValue >>  0) & 0xFFFFFFFF;	\
	} while (0)
	#define SET_DWORD_AS_WORDS(arr, idx, val)	\
	do {										\
		const DWORD dwValue = val;				\
		arr[idx + 0] = (dwValue >> 16) & 0xFFFF;	\
		arr[idx + 1] = (dwValue >>  0) & 0xFFFF;	\
	} while (0)
	#define XOR_DWORD_AS_WORDS(arr, idx, val)	\
	do {										\
		const DWORD dwValue = val;				\
		arr[idx + 0] ^= (dwValue >> 16) & 0xFFFF;	\
		arr[idx + 1] ^= (dwValue >>  0) & 0xFFFF;	\
	} while (0)
	#define XOR_DWORD_AS_BYTES(_arr, val)	\
	do {										\
		const DWORD dwValue = val;				\
		PBYTE arr = (PBYTE)(_arr);			\
		arr[0] ^= (dwValue >> 24) & 0xFF;	\
		arr[1] ^= (dwValue >> 16) & 0xFF;	\
		arr[2] ^= (dwValue >>  8) & 0xFF;	\
		arr[3] ^= (dwValue >>  0) & 0xFF;	\
	} while(0)
#else
	#define GET_BYTES_AS_DWORD(arr, idx) \
		(	((PBYTE)arr)[idx + 3]	<< 24 |	\
			((PBYTE)arr)[idx + 2]	<< 16 |	\
			((PBYTE)arr)[idx + 1]	<<  8 | \
			((PBYTE)arr)[idx + 0]	<<  0	)
	#define GET_WORDS_AS_DWORD(arr, idx) ( arr[idx + 1] << 16 | arr[idx] )
	#define SET_BYTES_AS_DWORD(arr, idx, val)	\
	do {										\
		const DWORD dwValue = val;				\
		((PBYTE)arr)[idx + 3] = (dwValue >> 24) & 0xFF;	\
		((PBYTE)arr)[idx + 2] = (dwValue >> 16) & 0xFF;	\
		((PBYTE)arr)[idx + 1] = (dwValue >>  8) & 0xFF;	\
		((PBYTE)arr)[idx + 0] = (dwValue >>  0) & 0xFF;	\
	} while (0)
	#define SET_DWORD_AS_WORDS(arr, idx, val)	\
	do {										\
		const DWORD dwValue = val;				\
		arr[idx + 1] = (dwValue >> 16) & 0xFFFF;	\
		arr[idx + 0] = (dwValue >>  0) & 0xFFFF;	\
	} while (0)
	#define XOR_DWORD_AS_WORDS(arr, idx, val)	\
	do {										\
		const DWORD dwValue = val;				\
		arr[idx + 1] ^= (dwValue >> 16) & 0xFFFF;	\
		arr[idx + 0] ^= (dwValue >>  0) & 0xFFFF;	\
	} while (0)
	#define XOR_DWORD_AS_BYTES(_arr, val)	\
	do {										\
		const DWORD dwValue = val;				\
		PBYTE arr = (PBYTE)(_arr);			\
		arr[3] ^= (dwValue >> 24) & 0xFF;	\
		arr[2] ^= (dwValue >> 16) & 0xFF;	\
		arr[1] ^= (dwValue >>  8) & 0xFF;	\
		arr[0] ^= (dwValue >>  0) & 0xFF;	\
	} while(0)
#endif


#ifdef HP_BIG_ENDIAN
#define SWAP_TYPED_TO(type, x) do { SWAP_##type((type) x);  } while(0)
#define SWAP_TYPED_FROM(type, x) do { SWAP_##type((type) x);  } while(0)
#endif

//===============================================================================

#define OSI_PREFIX(Name) Name

//===============================================================================

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//===============================================================================

#ifndef DEFFILEMODE
#define DEFFILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#endif // DEFFILEMODE

//-------------------------------------------------------------------------------

#define WINAPI
#define EXTERN_C extern "C"

//-------------------------------------------------------------------------------

#define PURE = 0

//-------------------------------------------------------------------------------

#define FALSE 0
#define TRUE 1

//-------------------------------------------------------------------------------

#ifdef OS_NO_TLS
#define __thread
#endif // OS_NO_TLS

#ifndef __try
#define __try try
#endif

#ifndef __except
#define __except catch
#endif

#define EXCEPTION_EXECUTE_HANDLER ...

//-------------------------------------------------------------------------------

#define UNREFERENCED_PARAMETER(PARAM) ((void) PARAM)

//-------------------------------------------------------------------------------

#define MEM_COMMIT 0x1000
#define MEM_RELEASE 0x8000

#define PAGE_EXECUTE_READ (PROT_READ | PROT_EXEC)
#define PAGE_EXECUTE_READWRITE (PROT_READ | PROT_WRITE | PROT_EXEC)
#define PAGE_READONLY  (PROT_READ)
#define PAGE_READWRITE (PROT_READ | PROT_WRITE)

#define MAGIC_MMAP 0xfefefe01
#define MAGIC_FILE_MMAP 0x02efefef

//-------------------------------------------------------------------------------

#define TIME_UNIX_EPOCHE 116444736000000000LL
#define FILETIME_TO_UNIXTIME(t) ((UINTS_TO_UINT64(			\
	 t.dwLowDateTime,						\
	 t.dwHighDateTime) - TIME_UNIX_EPOCHE) / 10000000LL)
#define UNIXTIME_TO_FILETIME(t, ft)					\
	do {								\
		LARGE_UINTEGER ConvLarge;					\
		ConvLarge.QuadPart = t * 10000000LL + TIME_UNIX_EPOCHE;	\
		ft.dwHighDateTime = ConvLarge.HighPart;			\
		ft.dwLowDateTime = ConvLarge.LowPart;			\
	} while(0)

//-------------------------------------------------------------------------------

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

#ifndef MAP_ANON
#define MAP_ANON MAP_ANONYMOUS
#endif

//-------------------------------------------------------------------------------

#define GENERIC_READ 0x80000000L
#define GENERIC_WRITE 0x40000000L
#define GENERIC_ALL (GENERIC_READ | GENERIC_WRITE)

#define OPEN_EXISTING 0
#define OPEN_ALWAYS O_CREAT
#define CREATE_ALWAYS (O_CREAT | O_TRUNC)
#define CREATE_NEW (O_CREAT | O_EXCL)

#define INVALID_HANDLE_VALUE ((PVOID)-1)
#define INVALID_FILE_SIZE ((DWORD)-1)
#define INVALID_SET_FILE_POINTER ((DWORD)-1)

#define INFINITE ((DWORD)-1)

#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004

#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_DEVICE 0x00000040
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define INVALID_FILE_ATTRIBUTES ((DWORD) -1)

#define FILE_FLAG_WRITE_THROUGH 0

#define FILE_BEGIN SEEK_SET
#define FILE_CURRENT SEEK_CUR
#define FILE_END SEEK_END

#define FILE_NOTIFY_CHANGE_FILE_NAME 0x0001
#define FILE_NOTIFY_CHANGE_SIZE 0x0008
#define FILE_NOTIFY_CHANGE_LAST_WRITE 0x0010

//-------------------------------------------------------------------------------

#define FILE_MAP_ALL_ACCESS (PROT_READ | PROT_WRITE)
#define FILE_MAP_COPY (MAP_PRIVATE << 8)
#define FILE_MAP_READ PROT_READ
#define FILE_MAP_WRITE PROT_WRITE
#define FILE_MAP_EXECUTE PROT_EXEC

#define FILE_FLAGS_TO_MMAP_FLAGS(x)								\
	((((x) >> 8) & (MAP_PRIVATE | MAP_SHARED)) == MAP_PRIVATE?	\
		MAP_PRIVATE : MAP_SHARED)
#define ACCESS_FLAGS_TO_MMAP_FLAGS(x)							\
	((x) & (PROT_EXEC | PROT_READ | PROT_WRITE | PROT_NONE))
#define MMAP_FLAGS_TO_FCNTL_FLAGS(x)								\
	(((x) & FILE_MAP_ALL_ACCESS) == FILE_MAP_ALL_ACCESS ? O_RDWR :	\
		(((x) & PROT_READ) ? O_RDONLY : O_WRONLY))

//-------------------------------------------------------------------------------

#define CP_ACP 0
#define CP_UTF8 65001

//-------------------------------------------------------------------------------

#define WC_ERR_INVALID_CHARS      0x00000080

//-------------------------------------------------------------------------------

#define MAX_PATH 260
#define MAXWORD 65535

#define MAX_SHM_NAME    MAX_PATH

//-------------------------------------------------------------------------------

#define MB_OK 0x00000000
#define MB_OKCANCEL 0x00000001
#define MB_ABORTRETRYIGNORE 0x00000002
#define MB_YESNOCANCEL 0x00000003
#define MB_YESNO 0x00000004
#define MB_RETRYCANCEL 0x00000005
#define MB_CANCELTRYCONTINUE 0x00000006 
#define MB_HELP 0x00004000 
#define MB_ICONHAND 0x00000010
#define MB_ICONQUESTION 0x00000020
#define MB_ICONEXCLAMATION 0x00000030
#define MB_ICONASTERISK 0x00000040
#define MB_USERICON 0x00000080
#define MB_ICONWARNING MB_ICONEXCLAMATION
#define MB_ICONERROR MB_ICONHAND
#define MB_ICONINFORMATION MB_ICONASTERISK
#define MB_ICONSTOP MB_ICONHAND
#define MB_APPMODAL 0x00000000
#define MB_SYSTEMMODAL 0x00010000
#define MB_TASKMODAL 0x00020000
#define MB_DEFBUTTON1 0x00000000
#define MB_DEFBUTTON2 0x00000100
#define MB_DEFBUTTON3 0x00000200
#define MB_DEFBUTTON4 0x00000300
		
#define MB_TOPMOST 0x00040000
#define MB_SETFOREGROUND 0x00010000
#define MB_SERVICE_NOTIFICATION 0x00200000

#define IDOK 1
#define IDCANCEL 2
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define IDYES 6
#define IDNO 7
#define IDTRYAGAIN  10
#define IDCONTINUE 11
#define IDHELP 12

//-------------------------------------------------------------------------------

#define KEY_QUERY_VALUE 0x0001
#define KEY_SET_VALUE 0x0002
#define KEY_CREATE_SUB_KEY 0x0004
#define KEY_ENUMERATE_SUB_KEYS 0x0008

#define KEY_WOW64_32KEY 0x0200

#define KEY_READ (KEY_QUERY_VALUE | \
    KEY_ENUMERATE_SUB_KEYS)

#define KEY_WRITE (KEY_SET_VALUE | \
    KEY_CREATE_SUB_KEY)

#define KEY_ALL_ACCESS (KEY_READ | KEY_WRITE)

#define REG_SZ 1
#define REG_DWORD 4

#define REG_OPTION_NON_VOLATILE 0

//-------------------------------------------------------------------------------

#define THREAD_TERMINATION_NOTIFICATION SIGRTMIN+0

#define NO_ERROR      ERROR_SUCCESS
#define ERROR_SUCCESS 0x00000000
#define ERROR_FAILURE 0xFFFFFFFF

#define WAIT_OBJECT_0 0x00000000
#define WAIT_ABANDONED 0x00000080

#define ERROR_FILE_NOT_FOUND 2L
#define ERROR_PATH_NOT_FOUND 3L
#define ERROR_TOO_MANY_OPEN_FILES 4L
#define ERROR_INVALID_HANDLE 6L
#define ERROR_NO_MORE_FILES 18L
#define ERROR_INVALID_PARAMETER 87L
#define ERROR_BUFFER_OVERFLOW 111L
#define ERROR_DIR_NOT_EMPTY 145L
#define ERROR_ALREADY_EXISTS 183L
#define ERROR_MORE_DATA 234L
#define WAIT_TIMEOUT 258L
#define ERROR_NO_MORE_ITEMS 259L
#define ERROR_DIRECTORY 267L
#define WAIT_FAILED -1L

//-------------------------------------------------------------------------------

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define closesocket close

//-------------------------------------------------------------------------------

#define HTTP_STATUS_CONTINUE 100
#define HTTP_STATUS_SWITCH_PROTOCOLS 101

#define HTTP_STATUS_OK 200
#define HTTP_STATUS_CREATED 201
#define HTTP_STATUS_ACCEPTED 202
#define HTTP_STATUS_PARTIAL 203
#define HTTP_STATUS_NO_CONTENT 204
#define HTTP_STATUS_RESET_CONTENT 205
#define HTTP_STATUS_PARTIAL_CONTENT 206

#define HTTP_STATUS_AMBIGUOUS 300
#define HTTP_STATUS_MOVED 301
#define HTTP_STATUS_REDIRECT 302
#define HTTP_STATUS_REDIRECT_METHOD 303
#define HTTP_STATUS_NOT_MODIFIED 304
#define HTTP_STATUS_USE_PROXY 305
#define HTTP_STATUS_REDIRECT_KEEP_VERB 307

#define HTTP_STATUS_BAD_REQUEST 400
#define HTTP_STATUS_DENIED 401
#define HTTP_STATUS_PAYMENT_REQ 402
#define HTTP_STATUS_FORBIDDEN 403
#define HTTP_STATUS_NOT_FOUND 404
#define HTTP_STATUS_BAD_METHOD 405
#define HTTP_STATUS_NONE_ACCEPTABLE 406
#define HTTP_STATUS_PROXY_AUTH_REQ 407
#define HTTP_STATUS_REQUEST_TIMEOUT 408
#define HTTP_STATUS_CONFLICT 409
#define HTTP_STATUS_GONE 410
#define HTTP_STATUS_LENGTH_REQUIRED 411
#define HTTP_STATUS_PRECOND_FAILED 412
#define HTTP_STATUS_REQUEST_TOO_LARGE 413
#define HTTP_STATUS_URI_TOO_LONG 414
#define HTTP_STATUS_UNSUPPORTED_MEDIA 415
#define HTTP_STATUS_RETRY_WITH 449

#define HTTP_STATUS_SERVER_ERROR 500
#define HTTP_STATUS_NOT_SUPPORTED 501
#define HTTP_STATUS_BAD_GATEWAY 502
#define HTTP_STATUS_SERVICE_UNAVAIL 503
#define HTTP_STATUS_GATEWAY_TIMEOUT 504
#define HTTP_STATUS_VERSION_NOT_SUP 505

//===============================================================================

#define SECURITY_DESCRIPTOR_REVISION 1
#define SECURITY_DESCRIPTOR_MIN_LENGTH 20

//===============================================================================

#ifdef UTF16
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

#define TEXT(x) x

typedef unsigned long DWORD;
typedef DWORD *PDWORD, *LPDWORD;
typedef const DWORD *PCDWORD;

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef const ULONG *PCULONG;

typedef int INT;
typedef INT *PINT;
typedef const INT *PCINT;

typedef unsigned int UINT;
typedef UINT *PUINT;
typedef const UINT *PCUINT;

#ifndef OBJECTIVE_C_MIXED_CODE
typedef int BOOL;
#endif
typedef BOOL *PBOOL, *LPBOOL;
typedef const BOOL *PCBOOL, *LPCBOOL;

typedef unsigned short WORD;
typedef WORD *PWORD;
typedef const WORD *PCWORD;

typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef const USHORT *PCUSHORT;

typedef unsigned char BYTE;
typedef BYTE *PBYTE, *LPBYTE;
typedef const BYTE *PCBYTE, *LPCBYTE;
typedef const TCHAR *LPCTSTR;

typedef char CHAR;
typedef CHAR *PCHAR, *PSTR, *LPSTR;
typedef const CHAR *PCCHAR, *PCSTR, *LPCSTR;

typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef const UCHAR *PCUCHAR;

typedef wchar_t WCHAR;
typedef WCHAR *PWCHAR, *PWSTR, *LPWSTR;
typedef const WCHAR *PCWCHAR, *PCWSTR, *LPCWSTR;

typedef void VOID;
typedef VOID *PVOID, *LPVOID;
typedef const VOID *PCVOID, *LPCVOID;
typedef PVOID *PPVOID;

typedef long LONG;
typedef LONG *PLONG;
typedef const LONG *PCLONG;

typedef long long INT64, *PINT64;

#if !defined(OS_HPUX) || !defined(__LP64__)
typedef unsigned long long UINT64;
#endif
typedef unsigned long long *PUINT64;


typedef long long LONGLONG;
typedef LONGLONG *PLONGLONG;

typedef unsigned long long DWORDLONG;
typedef DWORDLONG *PDWORDLONG;

typedef unsigned long long ULONGLONG;
typedef ULONGLONG *PULONGLONG;

typedef PVOID HMODULE;
typedef PVOID HINSTANCE;
typedef PVOID HWND;

typedef PVOID HANDLE;
typedef PVOID *PHANDLE;

typedef int SOCKET;

typedef size_t SIZE_T;

typedef PVOID HKEY;
typedef HKEY *PHKEY;
typedef DWORD REGSAM;

typedef LPVOID LPOVERLAPPED;

typedef double DOUBLE;

//===============================================================================

typedef struct _SECURITY_DESCRIPTOR {
	DWORD dwUnixAccessMode;
} SECURITY_DESCRIPTOR, *PSECURITY_DESCRIPTOR, *PISECURITY_DESCRIPTOR;

typedef struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES,*PSECURITY_ATTRIBUTES,*LPSECURITY_ATTRIBUTES;

typedef PVOID PACL;

//===============================================================================

typedef int (WINAPI *FARPROC) ();

typedef PVOID (* PTHREAD_START_ROUTINE) (PVOID);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

//===============================================================================

#ifndef OS_LARGE_INTEGER
typedef union _LARGE_INTEGER {
	struct {
#ifdef HP_BIG_ENDIAN
		INT  HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		INT  HighPart;
#endif
	};
	struct {
#ifdef HP_BIG_ENDIAN
		INT  HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		INT  HighPart;
#endif
	} u;
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

#define OS_LARGE_INTEGER
#endif // OS_LARGE_INTEGER

#ifndef OS_LARGE_UINTEGER
typedef union _LARGE_UINTEGER {
	struct {
#ifdef HP_BIG_ENDIAN
		UINT HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		UINT  HighPart;
#endif
	};
	struct {
#ifdef HP_BIG_ENDIAN
		UINT HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		UINT HighPart;
#endif
	} u;
	LONGLONG QuadPart;
} LARGE_UINTEGER, *PLARGE_UINTEGER;

#define OS_LARGE_UINTEGER
#endif // OS_LARGE_UINTEGER

inline static UINT64 UINTS_TO_UINT64(UINT l, UINT h)
{
	LARGE_UINTEGER ConvLarge;

    ConvLarge.HighPart = h;
    ConvLarge.LowPart = l;
    return ConvLarge.QuadPart;
}

inline static ULONGLONG DWORDS_TO_ULONGLONG(DWORD l, DWORD h)
{
	LARGE_UINTEGER ConvLarge;

    ConvLarge.HighPart = h;
    ConvLarge.LowPart = l;
    return ConvLarge.QuadPart;
}

inline static void UINT64_TO_PUINTS(UINT64 lh, PUINT l, PUINT h)
{
	LARGE_UINTEGER ConvLarge;
	ConvLarge.QuadPart = lh;

    if (l)
        *l = ConvLarge.LowPart;
    if (h)
        *h = ConvLarge.HighPart;
}

inline static void LONGLONG_TO_PLONGS(LONGLONG lh, PLONG l, PLONG h)
{
    UINT _l;
    UINT _h;
    UINT64 _lh = (UINT64)lh;
    UINT64_TO_PUINTS(_lh, &_l, &_h);
    if (l)
        *l = _l;
    if (h)
        *h = _h;
}

//===============================================================================

#ifndef FILE_TIME
typedef struct _FILETIME
{
#ifdef HP_BIG_ENDIAN
	UINT dwHighDateTime;
	UINT dwLowDateTime;
#else
	UINT dwLowDateTime;
	UINT dwHighDateTime;
#endif // HP_BIG_ENDIAN
} FILETIME, *PFILETIME, *LPFILETIME;

typedef const FILETIME *PCFILETIME;

#define FILE_TIME
#endif // FILE_TIME

#ifndef SYSTEM_TIME
typedef struct _SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
}SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef const SYSTEMTIME *PCSYSTEMTIME;

#define SYSTEM_TIME
#endif // SYSTEM_TIME

#ifndef OS_BLOB
typedef struct tagBLOB
{
	ULONG cbSize;
	PBYTE pBlobData;
}BLOB, *PBLOB, *LPBLOB;

typedef const BLOB *PCBLOB;

typedef struct _CRYPTOAPI_BLOB
{
	DWORD cbData;
	PBYTE pbData;
}DATA_BLOB, *PDATA_BLOB;

#define OS_BLOB
#endif // OS_BLOB

#ifndef OS_CRITICAL_SECTION
typedef struct
{
	pthread_mutex_t pThreadMutex;
}CRITICAL_SECTION, *PCRITICAL_SECTION, *LPCRITICAL_SECTION;

#define OS_CRITICAL_SECTION
#endif // OS_CRITICAL_SECTION

typedef union _ULARGE_UINTEGER
{
	struct
	{
#ifdef HP_BIG_ENDIAN
		UINT HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		UINT HighPart;
#endif // HP_BIG_ENDIAN
	};

	struct
	{
#ifdef HP_BIG_ENDIAN
		UINT HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		UINT HighPart;
#endif // HP_BIG_ENDIAN
	}u;

	ULONGLONG QuadPart;
}ULARGE_INTEGER;

typedef struct _WIN32_FIND_DATA
{
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	CHAR cFileName[MAX_PATH];
	CHAR cAlternateFilename[14];
}WIN32_FIND_DATA, *PWIN32_FIND_DATA, *LPWIN32_FIND_DATA;

#define WIN32_FIND_DATAA WIN32_FIND_DATA
typedef WIN32_FIND_DATAA *PWIN32_FIND_DATAA;

typedef struct
{
    BOOL    fAutoDetect;
    LPWSTR  lpszAutoConfigUrl;
    LPWSTR  lpszProxy;
    LPWSTR  lpszProxyBypass;
} WINHTTP_CURRENT_USER_IE_PROXY_CONFIG;
    
//===============================================================================

#ifdef OS_AIX
#define OSP_PATH_VARIABLE "LIBPATH"
#elif defined(OS_MAC)
#define OSP_PATH_VARIABLE "DYLD_LIBRARY_PATH"
#else
#define OSP_PATH_VARIABLE "LD_LIBRARY_PATH"
#endif // OS_AIX

#define OSPCU_FILE_NAME "ospcu.ini"
#define OSPLM_FILE_NAME "osplm.ini"
#define OSPUS_FILE_NAME "ospus.ini"

//===============================================================================

extern HKEY HKEY_CURRENT_USER;
extern HKEY HKEY_LOCAL_MACHINE;
extern HKEY HKEY_USERS;

//===============================================================================

#if defined(PC_STATIC_LIBS) && defined(PC_MONO_LIB)

#define _ultoa  							OSI__ultoa
#define InitializeSecurityDescriptor		OSI_InitializeSecurityDescriptor
#define SetSecurityDescriptorDacl			OSI_SetSecurityDescriptorDacl
#define GetSystemTimeAsFileTime				OSI_GetSystemTimeAsFileTime
#define GetSystemTime						OSI_GetSystemTime
#define FileTimeToLocalFileTime				OSI_FileTimeToLocalFileTime
#define LocalFileTimeToFileTime				OSI_LocalFileTimeToFileTime
#define GetLocalTime						OSI_GetLocalTime
#define SetLocalTime						OSI_SetLocalTime
#define SetSystemTime						OSI_SetSystemTime
#define FileTimeToSystemTime				OSI_FileTimeToSystemTime
#define SystemTimeToFileTime				OSI_SystemTimeToFileTime
#define CompareFileTime						OSI_CompareFileTime
#define VirtualAlloc						OSI_VirtualAlloc
#define VirtualFree							OSI_VirtualFree
#define GetProcessHeap						OSI_GetProcessHeap
#define HeapAlloc							OSI_HeapAlloc
#define HeapFree							OSI_HeapFree
#define LoadLibrary							OSI_LoadLibrary
#define FreeLibrary							OSI_FreeLibrary
#define GetProcAddress						OSI_GetProcAddress
#define CreateFile							OSI_CreateFile
#if !defined(ANDROID_NDK) && !defined(NACL_SDK)
#define CreateFileMapping					OSI_CreateFileMapping
#define MapViewOfFile						OSI_MapViewOfFile
#define UnmapViewOfFile						OSI_UnmapViewOfFile
#endif // ANDROID_NDK && NACL_SDK
#define CreateMutex							OSI_CreateMutex
#define ReleaseMutex						OSI_ReleaseMutex
#define CloseHandle							OSI_CloseHandle
#define ReadFile							OSI_ReadFile
#define WriteFile							OSI_WriteFile
#define GetFileSize							OSI_GetFileSize
#define SetFilePointer						OSI_SetFilePointer
#define SetFileValidData					OSI_SetFileValidData
#define SetEndOfFile						OSI_SetEndOfFile
#define FlushFileBuffers					OSI_FlushFileBuffers
#define CopyFile							OSI_CopyFile
#define MoveFile							OSI_MoveFile
#define DeleteFile							OSI_DeleteFile
#define SetFileAttributes					OSI_SetFileAttributes
#define GetFileTime							OSI_GetFileTime
#define FindFirstFile						OSI_FindFirstFile
#define FindNextFile						OSI_FindNextFile
#define FindClose							OSI_FindClose
#define FindFirstChangeNotification			OSI_FindFirstChangeNotification
#define FindNextChangeNotification			OSI_FindNextChangeNotification
#define FindCloseChangeNotification			OSI_FindCloseChangeNotification
#define GetLastError						OSI_GetLastError
#ifdef OS_NO_NATIVE_INTERLOCKED
#define InterlockedIncrement				OSI_InterlockedIncrement
#define InterlockedDecrement				OSI_InterlockedDecrement
#define InterlockedExchangeAdd				OSI_InterlockedExchangeAdd
#endif // OS_NO_NATIVE_INTERLOCKED
#define InitializeCriticalSection			OSI_InitializeCriticalSection
#define DeleteCriticalSection				OSI_DeleteCriticalSection
#define EnterCriticalSection				OSI_EnterCriticalSection
#define LeaveCriticalSection				OSI_LeaveCriticalSection
#define GetCurrentProcessId                 OSI_GetCurrentProcessId
#define ExitProcess                         OSI_ExitProcess
#define GetCurrentThreadId                  OSI_GetCurrentThreadId
#define CreateThread                        OSI_CreateThread
#define TerminateThread                     OSI_TerminateThread
#define ExitThread                          OSI_ExitThread
#define WaitForSingleObject                 OSI_WaitForSingleObject
#define MultiByteToWideChar                 OSI_MultiByteToWideChar
#define WideCharToMultiByte                 OSI_WideCharToMultiByte
#define strrev                              OSI_strrev
#define strupr                              OSI_strupr
#define strnicmp                            OSI_strnicmp
#define MessageBox                          OSI_MessageBox
#define MessageBoxW                         OSI_MessageBoxW
#define MessageBeep                         OSI_MessageBeep
#define UpdateWindow                        OSI_UpdateWindow
#define GetCurrentDirectory                 OSI_GetCurrentDirectory
#define SetCurrentDirectory                 OSI_SetCurrentDirectory
#define GetSystemDirectory                  OSI_GetSystemDirectory
#define GetTempPath                         OSI_GetTempPath
#define GetTempFileName                     OSI_GetTempFileName
#define CreateDirectory                     OSI_CreateDirectory
#define RemoveDirectory                     OSI_RemoveDirectory
#define GetFileAttributes                   OSI_GetFileAttributes
#define GetModuleFileName                   OSI_GetModuleFileName
#define GetLoadedModulePath                 OSI_GetLoadedModulePath
#define RegOpenKeyEx                        OSI_RegOpenKeyEx
#define RegCreateKeyEx                      OSI_RegCreateKeyEx
#define RegCloseKey                         OSI_RegCloseKey
#define RegDeleteKey                        OSI_RegDeleteKey
#define RegQueryValueEx                     OSI_RegQueryValueEx
#define RegSetValueEx                       OSI_RegSetValueEx
#define RegEnumKey                          OSI_RegEnumKey
#define RegEnumValue                        OSI_RegEnumValue
#define RegGetRegFilePath                   OSI_RegGetRegFilePath
#define RegSetRegFilePath                   OSI_RegSetRegFilePath
#define Sleep                               OSI_Sleep
#define QueryPerformanceCounter             OSI_QueryPerformanceCounter
#define QueryPerformanceFrequency           OSI_QueryPerformanceFrequency
#if !defined(NACL_SDK) && !defined(EM_SDK)
#define CreateEvent                         OSI_CreateEvent
#define SetEvent                            OSI_SetEvent
#endif // !NACL_SDK && !EM_SDK
#define WinHttpGetIEProxyConfigForCurrentUser OSI_WinHttpGetIEProxyConfigForCurrentUser
#define GlobalFree                          OSI_GlobalFree
#if !defined(NACL_SDK) && !defined(EM_SDK)
#define ResetEvent                          OSI_ResetEvent
#endif // !NACL_SDK && !EM_SDK
#endif // PC_STATIC_LIBS && PC_MONO_LIB

#ifdef EM_SDK
#define strupr                              OSI_strupr
#endif // EM_SDK

#if OS_MAC
#define CreateEvent                         OSI_CreateEvent
#define SetEvent                            OSI_SetEvent
#define ResetEvent                          OSI_ResetEvent
#endif // OS_MAC

//===============================================================================

const char *_ultoa(ULONGLONG value, char *str, int radix);

#ifdef UTF16
#define	_tcscat		wcscat
#define _tcschr		wcschr
#define _tcscmp		wcscmp
#define _tcscpy		wcscpy
#define _tcscspn	wcscspn
#define	_tcslen		wcslen
#define	_tcsncat	wcsncat
#define	_tcsncmp	wcsncmp
#define	_tcsncpy	wcsncpy
#define	_tcspbrk	wcspbrk
#define	_tcsrchr	wcsrchr
#define _tcsspn		wcsspn
#define	_tcsstr		wcsstr
#define _tcstok		wcstok
#define _tcscpy_s(d, n, s) wcsncpy(d, s, n)
#else
#define	_tcscat		strcat
#define _tcschr		strchr
#define _tcscmp		strcmp
#define _tcscpy		strcpy
#define _tcscspn	strcspn
#define	_tcslen		strlen
#define	_tcsncat	strncat
#define	_tcsncmp	strncmp
#define	_tcsncpy	strncpy
#define	_tcspbrk	strpbrk
#define	_tcsrchr	strrchr
#define _tcsspn		strspn
#define	_tcsstr		strstr
#define _tcstok		strtok
#define _tcscpy_s(d, n, s) strncpy(d, s, n)
#endif

//===============================================================================

#define stricmp strcasecmp

//===============================================================================

#define ZeroMemory(d, l) memset(d, 0, l)
#define CopyMemory(d, s, l) memcpy(d, s, l)

//===============================================================================

BOOL WINAPI InitializeSecurityDescriptor(
	PSECURITY_DESCRIPTOR pSecurityDescriptor,
	DWORD dwRevision);


BOOL WINAPI SetSecurityDescriptorDacl(
	PSECURITY_DESCRIPTOR pSecurityDescriptor,
	BOOL bDaclPresent,
	PACL pDacl,
	BOOL bDaclDefaulted);

VOID WINAPI GetSystemTimeAsFileTime(
	LPFILETIME lpSystemTimeAsFileTime);

VOID WINAPI GetSystemTime(
	LPSYSTEMTIME lpSystemTime);

BOOL WINAPI FileTimeToLocalFileTime(
	PCFILETIME lpFileTime,
	LPFILETIME lpLocalFileTime);

BOOL WINAPI LocalFileTimeToFileTime(
	PCFILETIME lpLocalFileTime,
	LPFILETIME lpFileTime);

VOID WINAPI GetLocalTime(
	LPSYSTEMTIME lpSystemTime);

BOOL WINAPI SetLocalTime(
	LPSYSTEMTIME lpSystemTime);

BOOL WINAPI SetSystemTime(
	LPSYSTEMTIME 	lpSystemTime);

BOOL WINAPI FileTimeToSystemTime(
	PCFILETIME lpFileTime,
	LPSYSTEMTIME lpSystemTime);

BOOL WINAPI SystemTimeToFileTime(
	PCSYSTEMTIME lpSystemTime,
	LPFILETIME lpFileTime);

LONG WINAPI CompareFileTime(
	PCFILETIME lpFileTime1,
	PCFILETIME lpFileTime2);

//===============================================================================

PVOID WINAPI VirtualAlloc(
	LPVOID lpAddress,
	size_t dwSize,
	DWORD flAllocationType,
	DWORD flProtect);

BOOL WINAPI VirtualFree(
	LPVOID lpAddress,
	size_t dwSize,
	DWORD dwFreeType);

HANDLE GetProcessHeap();

LPVOID HeapAlloc(
	HANDLE hHeap,
	DWORD dwFlags,
	size_t dwBytes);

BOOL HeapFree(
	HANDLE hHeap,
	DWORD dwFlags,
	LPVOID lpMem);

//===============================================================================

typedef BOOL (WINAPI *PDLLMAIN) (
	HINSTANCE hInstance,
	DWORD dwReason,
	PVOID);

#define DLL_PROCESS_ATTACH 1
#define DLL_PROCESS_DETACH 0
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3

//===============================================================================

HMODULE WINAPI LoadLibrary(
	LPCSTR lpLibFileName);

#define LoadLibraryA LoadLibrary

BOOL WINAPI FreeLibrary(
	HMODULE hLibModule);

FARPROC WINAPI GetProcAddress(
	HMODULE hModule,
	LPCSTR lpProcName);

#define GetProcAddressA GetProcAddress

//===============================================================================

HANDLE WINAPI CreateFile(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile);
#define CreateFileA CreateFile

#if !defined(ANRDOID_NDK) && !defined(NACL_SDK)
HANDLE WINAPI CreateFileMapping(
	HANDLE hFile,
	LPSECURITY_ATTRIBUTES lpAttributes,
	DWORD flProtect,
	DWORD dwMaximumSizeHigh,
	DWORD dwMaximumSizeLow,
	LPCTSTR lpName);

LPVOID WINAPI MapViewOfFile(
	HANDLE hFileMappingObject,
	DWORD dwDesiredAccess,
	DWORD dwFileOffsetHigh,
	DWORD dwFileOffsetLow,
	SIZE_T dwNumberOfBytesToMap);

BOOL WINAPI UnmapViewOfFile(
	LPCVOID lpBaseAddress);
#endif // ANRDOID_NDK && NACL_SDK

HANDLE WINAPI CreateMutex(
	LPSECURITY_ATTRIBUTES lpMutexAttributes,
	BOOL bInitialOwner,
	PCSTR lpName);

BOOL WINAPI ReleaseMutex(
	HANDLE hMutex);

BOOL WINAPI CloseHandle(
	HANDLE hObject);

BOOL WINAPI ReadFile(
	HANDLE hFile,
	LPVOID lpBuffer,
	DWORD nNumberOfBytesToRead,
	LPDWORD lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped);

BOOL WINAPI WriteFile(
	HANDLE hFile,
	LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped);

DWORD WINAPI GetFileSize(
	HANDLE hFile,
	LPDWORD lpFileSizeHigh);

DWORD WINAPI SetFilePointer(
	HANDLE hFile,
	LONG lDistanceToMove,
	PLONG lpDistanceToMoveHigh,
	DWORD dwMoveMethod);

BOOL WINAPI SetFileValidData(
	HANDLE hFile,
	LONGLONG llValidFileSize);

BOOL WINAPI SetEndOfFile(
	HANDLE hFile);

BOOL WINAPI FlushFileBuffers(
	HANDLE hFile);

BOOL WINAPI CopyFile(
	LPCSTR lpExistingFileName,
	LPCSTR lpNewFileName,
	BOOL bFailIfExists);

BOOL WINAPI MoveFile(
	LPCSTR lpExistingFileName,
	LPCSTR lpNewFileName);

BOOL WINAPI DeleteFile(
	LPCSTR lpFileName);
#define DeleteFileA DeleteFile

BOOL WINAPI SetFileAttributes(
	LPCSTR lpFileName,
	DWORD dwFileAttributes);
#define SetFileAttributesA SetFileAttributes

BOOL WINAPI GetFileTime(
	HANDLE hFile,
	LPFILETIME lpCreationTime,
	LPFILETIME lpLastAccessTime,
	LPFILETIME lpLastWriteTime);

HANDLE WINAPI FindFirstFile(
	LPCSTR lpFileName,
	LPWIN32_FIND_DATA lpFindFileData);
#define FindFirstFileA FindFirstFile

BOOL WINAPI FindNextFile(
	HANDLE hFindFile,
	LPWIN32_FIND_DATA lpFindFileData);
#define FindNextFileA FindNextFile

BOOL WINAPI FindClose(
	HANDLE hFindFile);

HANDLE WINAPI FindFirstChangeNotification(
	LPCSTR lpPathName,
	BOOL bWatchSubtree,
	DWORD dwNotifyFilter);
#define FindFirstChangeNotificationA FindFirstChangeNotification

BOOL WINAPI FindNextChangeNotification(
	HANDLE hChangeHandle);

BOOL WINAPI FindCloseChangeNotification(
	HANDLE hChangeHandle);

DWORD WINAPI GetLastError();

//===============================================================================

#ifdef OS_NO_NATIVE_INTERLOCKED
LONG InterlockedIncrement(
	LONG volatile *pAddend);

LONG InterlockedDecrement(
	LONG volatile *pAddend);

LONG InterlockedExchangeAdd(
	LONG volatile *pAddend,
	LONG Value);
#elif defined(OS_SUNOS)
#define InterlockedDecrement(x) atomic_dec_ulong_nv((PULONG) x)
#define InterlockedIncrement(x) atomic_inc_ulong_nv((PULONG) x)
#else
#define InterlockedDecrement(x) __sync_sub_and_fetch(x, 1)
#define InterlockedIncrement(x) __sync_add_and_fetch(x, 1)
#define InterlockedExchangeAdd(x, value) __sync_fetch_and_add (x, value)
#endif // OS_NO_NATIVE_INTERLOCKED

VOID WINAPI InitializeCriticalSection(
	LPCRITICAL_SECTION lpCriticalSection);

VOID WINAPI DeleteCriticalSection(
	LPCRITICAL_SECTION lpCriticalSection);

VOID WINAPI EnterCriticalSection(
	LPCRITICAL_SECTION lpCriticalSection);

VOID WINAPI LeaveCriticalSection(
	LPCRITICAL_SECTION lpCriticalSection);

DWORD WINAPI GetCurrentProcessId();

VOID WINAPI ExitProcess(
	DWORD dwExitCode);

DWORD WINAPI GetCurrentThreadId();

HANDLE WINAPI CreateThread(
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	size_t dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	DWORD dwCreationFlags,
	LPDWORD lpThreadId);

BOOL WINAPI TerminateThread(
	HANDLE hThread,
	DWORD dwExitCode);

VOID WINAPI ExitThread(
	DWORD dwExitCode);

DWORD WINAPI WaitForSingleObject(
	HANDLE hHandle,
	DWORD dwMilliseconds);

//===============================================================================

int WINAPI MultiByteToWideChar(
	UINT CodePage,
	DWORD dwFlags,
	LPCSTR lpMultiByteStr,
	int cbMultiByte,
	LPWSTR lpWideCharStr,
	int cchWideChar);

int WINAPI WideCharToMultiByte(
	UINT CodePage,
	DWORD dwFlags,
	LPCWSTR lpWideCharStr,
	int cchWideChar,
	LPSTR lpMultiByteStr,
	int cbMultiByte,
	LPCSTR lpDefaultChar,
	LPBOOL lpUsedDefaultChar);

//===============================================================================

char* strrev(
	char* s);

char* strupr(
	char* s);

int strnicmp(
	const char* s1,
	const char* s2,
	size_t count);

//===============================================================================

int WINAPI MessageBox(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType);

#define MessageBoxA MessageBox

int WINAPI MessageBoxW(
	HWND hWnd,
	LPWSTR lpwText,
	LPWSTR lpwCaption,
	UINT uType);

BOOL WINAPI MessageBeep(
	UINT uType);

BOOL WINAPI UpdateWindow(
	HWND hWnd);

//===============================================================================

DWORD WINAPI GetCurrentDirectory(
	DWORD nBufferLength,
	LPSTR lpBuffer);
#define GetCurrentDirectoryA GetCurrentDirectory

BOOL WINAPI SetCurrentDirectory(
	LPCSTR lpPathName);
#define SetCurrentDirectoryA SetCurrentDirectory

UINT WINAPI GetSystemDirectory(
	LPSTR lpBuffer,
	UINT uSize);
#define GetSystemDirectoryA GetSystemDirectory

DWORD WINAPI GetTempPath(
	DWORD nBufferLength,
	LPSTR lpBuffer);
#define GetTempPathA GetTempPath

UINT WINAPI GetTempFileName(
	LPCTSTR		lpPathName,
	LPCTSTR		lpPrefixString,
	UINT		uUnique,
	LPSTR		lpTempFileName);
#define GetTempFileNameA GetTempFileName

BOOL WINAPI CreateDirectory(
	LPCSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes);
#define CreateDirectoryA CreateDirectory

BOOL WINAPI RemoveDirectory(
	LPCSTR lpPathName);

DWORD WINAPI GetFileAttributes(
	LPCSTR lpFileName);
#define GetFileAttributesA GetFileAttributes

//===============================================================================

DWORD WINAPI GetModuleFileName(
	HMODULE hModule,
	LPSTR lpFilename,
	DWORD nSize);

#define GetModuleFileNameA GetModuleFileName

DWORD WINAPI GetLoadedModulePath(
	PCSTR	pszModuleName,
	LPSTR	lpModulePath, 
	DWORD	dwSize);

//===============================================================================

LONG WINAPI RegOpenKeyEx(
	HKEY hKey,
	LPCSTR lpSubKey,
	DWORD ulOptions,
	REGSAM samDesired,
	HKEY *phkResult);
#define RegOpenKeyExA RegOpenKeyEx

LONG WINAPI RegCreateKeyEx(
	HKEY hKey,
	LPCSTR lpSubKey,
	DWORD Reserved,
	LPSTR lpClass,
	DWORD dwOptions,
	REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	HKEY *phkResult,
	LPDWORD pldwDisposition);
#define RegCreateKeyExA RegCreateKeyEx

LONG WINAPI RegCloseKey(
	HKEY hKey);

LONG WINAPI RegDeleteKey(
	HKEY hKey,
	LPCSTR lpSubKey);
#define RegDeleteKeyA RegDeleteKey

LONG WINAPI RegQueryValueEx(
	HKEY hKey,
	LPCSTR lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE lpData,
	LPDWORD lpcbData);
#define RegQueryValueExA RegQueryValueEx

LONG WINAPI RegSetValueEx(
	HKEY hKey,
	LPCSTR lpValueName,
	DWORD Reserved,
	DWORD dwType,
	LPBYTE lpData,
	DWORD cbData);
#define RegSetValueExA RegSetValueEx

LONG WINAPI RegEnumKey(
	HKEY hKey,
	DWORD dwIndex,
	LPSTR lpName,
	DWORD cbName);
#define RegEnumKeyA RegEnumKey

LONG WINAPI RegEnumValue(
	HKEY hKey,
	DWORD dwIndex,
	LPSTR lpValueName,
	LPDWORD lpcbValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE lpData,
	LPDWORD lpcbData);
#define RegEnumValueA RegEnumValue

LONG WINAPI RegGetRegFilePath(
	HKEY hKey,
	LPSTR lpRegFilePath);

LONG WINAPI RegSetRegFilePath(
	HKEY hKey,
	LPCSTR lpRegFilePath);

//===============================================================================

VOID WINAPI Sleep(
	DWORD dwMilliseconds);

//===============================================================================

BOOL WINAPI QueryPerformanceCounter(
	LARGE_INTEGER *lpPerformanceCount);

BOOL WINAPI QueryPerformanceFrequency(
	LARGE_INTEGER *lpFrequency);

//==============================================================================

#if !defined(NACL_SDK) && !defined(EM_SDK)

HANDLE WINAPI CreateEvent(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	BOOL bManualReset,
	BOOL bInitialState,
	LPCSTR lpName);
#define CreateEventA CreateEvent

BOOL WINAPI SetEvent(
	HANDLE hEvent);

BOOL WINAPI ResetEvent(
	HANDLE hEvent);

#endif // !NACL_SDK && !EM_SDK

//==============================================================================

BOOL WINAPI WinHttpGetIEProxyConfigForCurrentUser(
	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG *pProxyConfig);

PVOID WINAPI GlobalFree(PVOID hMem);

//===============================================================================

#ifdef HS_USB_DEVICE

#ifdef ANDROID_NDK
VOID SetUSBDevice(
	DWORD dwFd,
	PBYTE pbDescriptors,
	DWORD dwDescriptorsSize);
#endif

HANDLE OpenUSBDevice(
	DWORD iDevice,
	DWORD dwVendorID,
	DWORD dwProductID);

VOID CloseUSBDevice(
	HANDLE hDevice);

struct usb_dev_handle *GetUSBDeviceHandle(
	HANDLE hDevice);

BOOL SetUSBDeviceContext(
	HANDLE hDevice,
	PVOID pvContext);

PVOID GetUSBDeviceContext(
	HANDLE hDevice);

INT USBControlMessage(
	HANDLE hDevice,
	INT iRequestType,
	INT iRequest,
	INT iValue,
	INT iIdx,
	PCHAR pcBytes,
	ULONG ulSize,
	INT iTimeout);

INT USBGetString(
	HANDLE hDevice,
	INT iIdx,
	PCHAR pcBuf,
	ULONG ulBufLen);

INT USBBulkMessageWrite(
	HANDLE hDevice,
	INT nEndPoint,
	PVOID pvData,
	DWORD dwDataSize,
	INT nTimeout);

INT USBBulkMessageRead(
	HANDLE hDevice,
	INT nEndPoint,
	PVOID pvData,
	DWORD dwDataSize,
	INT nTimeout);

INT USBGetDeviceDescriptor(
	HANDLE hDevice,
	PUSB_DEVICE_DESCRIPTOR *ppDescriptor);
VOID USBFreeDeviceDescriptor(
	PUSB_DEVICE_DESCRIPTOR pDescriptor);

struct usb_device* GetUSBDevice(HANDLE hDevice);

#endif // HS_USB_DEVICE

//===============================================================================

#ifdef OS_MAC

typedef DWORD HRESULT;

#define S_OK    0x00000000
#define E_FAIL  0x80004005

#define SUCCEEDED(Result)    \
((Result) == S_OK)

#define CSIDL_PERSONAL 5
#define CSIDL_APPDATA 26
#define CSIDL_COMMON_APPDATA 35
#define CSIDL_COMMON_DOCUMENTS 46

HRESULT SHGetFolderPath(
  HWND hwndOwner,
  int nFolder,
  HANDLE hToken,
  DWORD dwFlags,
  LPSTR pszPath
);

#endif // OS_MAC

//===============================================================================

#ifdef OS_IOS
BOOL IsSharedMemorySupported();
#endif // OS_IOS

//===============================================================================

#ifdef __cplusplus
}
#endif // __cplusplus

//===============================================================================

#else // OS_NIX

#ifndef HP_ARMV4I

//===============================================================================

#include <windows.h>

//===============================================================================

#define OSI_PREFIX(Name) RF##Name

#define ERROR_FAILURE 0xFFFFFFFF

//===============================================================================

#define OSPCU_FILE_NAME "ospcu.ini"
#define OSPLM_FILE_NAME "osplm.ini"
#define OSPUS_FILE_NAME "ospus.ini"

//===============================================================================

extern HKEY OSI_PREFIX(HKEY_CURRENT_USER);
extern HKEY OSI_PREFIX(HKEY_LOCAL_MACHINE);
extern HKEY OSI_PREFIX(HKEY_USERS);

//===============================================================================

typedef LONG (WINAPI *PREG_OPEN_KEY_EX)(
	HKEY hKey,
	LPCSTR lpSubKey,
	DWORD ulOptions,
	REGSAM samDesired,
	HKEY *phkResult);

typedef LONG (WINAPI *PREG_CREATE_KEY_EX)(
	HKEY hKey,
	LPCSTR lpSubKey,
	DWORD Reserved,
	LPSTR lpClass,
	DWORD dwOptions,
	REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	HKEY *phkResult,
	LPDWORD pldwDisposition);

typedef LONG (WINAPI *PREG_CLOSE_KEY)(
	HKEY hKey);

typedef LONG (WINAPI *PREG_QUERY_VALUE_EX)(
	HKEY hKey,
	LPCSTR lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE lpData,
	LPDWORD lpcbData);

typedef LONG (WINAPI *PREG_SET_VALUE_EX)(
	HKEY hKey,
	LPCSTR lpValueName,
	DWORD Reserved,
	DWORD dwType,
	LPBYTE lpData,
	DWORD cbData);

typedef LONG (WINAPI *PREG_ENUM_KEY)(
	HKEY hKey,
	DWORD dwIndex,
	LPSTR lpName,
	DWORD cbName);

typedef LONG (WINAPI *PREG_ENUM_VALUE)(
	HKEY hKey,
	DWORD dwIndex,
	LPSTR lpValueName,
	LPDWORD lpcbValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE lpData,
	LPDWORD lpcbData);

typedef LONG (WINAPI *PREG_GET_REG_FILE)(
	HKEY hKey,
	LPSTR lpRegFile);

typedef LONG (WINAPI *PREG_GET_REG_FILE_PATH)(
	HKEY hKey,
	LPSTR lpRegFilePath);

typedef LONG (WINAPI *PREG_SET_REG_FILE_PATH)(
	HKEY hKey,
	LPCSTR lpRegFilePath);

//===============================================================================

#else // HP_ARMV4I

//===============================================================================

#include <windows.h>

//===============================================================================

#define TIME_UNIX_EPOCHE 116444736000000000

//===============================================================================

INT WINAPI MultiByteToWideCharI(
	UINT		CodePage,
	DWORD		dwFlags,
	LPCSTR		lpMultiByteStr,
	INT			cbMultiByte,
	LPWSTR		lpWideCharStr,
	INT			cchWideChar);

INT WINAPI WideCharToMultiByteI(
	UINT		CodePage,
	DWORD		dwFlags,
	LPCWSTR		lpWideCharStr,
	INT			cchWideChar,
	LPSTR		lpMultiByteStr,
	INT			cbMultiByte,
	LPCSTR		lpDefaultChar,
	LPBOOL		lpUsedDefaultChar);

//===============================================================================

#endif // HP_ARMV4I

#endif // OS_NIX

//==============================================================================

#ifndef InitializeListHead

//------------------------------------------------------------------------------

#ifdef OS_NIX

#ifndef CONTAINING_RECORD
typedef struct _LIST_ENTRY
{
	struct _LIST_ENTRY *Flink;
	struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY;
#endif // CONTAINING_RECORD

#endif // OS_NIX

//------------------------------------------------------------------------------

#define CONTAINING_RECORD(Address, Type, Field)     \
    ((Type *)((PCHAR)(Address) -                    \
    (PCHAR)(&((Type *)0)->Field)))

#define InitializeListHead(ListHead) (              \
    (ListHead)->Flink = (ListHead)->Blink = (ListHead))

#define IsListEmpty(ListHead)                       \
    ((ListHead)->Flink == (ListHead))

#define RemoveHeadList(ListHead)                    \
    (ListHead)->Flink;                              \
    {RemoveEntryList((ListHead)->Flink)}

#define RemoveTailList(ListHead)                    \
    (ListHead)->Blink;                              \
    {RemoveEntryList((ListHead)->Blink)}

#define RemoveEntryList(Entry) {                    \
    PLIST_ENTRY	_EX_Blink;                          \
    PLIST_ENTRY _EX_Flink;                          \
    _EX_Flink = (Entry)->Flink;                     \
    _EX_Blink = (Entry)->Blink;                     \
    _EX_Blink->Flink = _EX_Flink;                   \
    _EX_Flink->Blink = _EX_Blink;                   \
    }

#define InsertTailList(ListHead,Entry) {            \
    PLIST_ENTRY _EX_Blink;                          \
    PLIST_ENTRY _EX_ListHead;                       \
    _EX_ListHead = (ListHead);                      \
    _EX_Blink = _EX_ListHead->Blink;                \
    (Entry)->Flink = _EX_ListHead;                  \
    (Entry)->Blink = _EX_Blink;                     \
    _EX_Blink->Flink = (Entry);                     \
    _EX_ListHead->Blink = (Entry);                  \
    }

#define InsertHeadList(ListHead, Entry) {           \
    PLIST_ENTRY	_EX_Flink;                          \
    PLIST_ENTRY _EX_ListHead;                       \
    _EX_ListHead = (ListHead);                      \
    _EX_Flink = _EX_ListHead->Flink;                \
    (Entry)->Flink = _EX_Flink;                     \
    (Entry)->Blink = _EX_ListHead;                  \
    _EX_Flink->Blink = (Entry);                     \
    _EX_ListHead->Flink = (Entry);                  \
    }

//------------------------------------------------------------------------------

#endif // InitializeListHead

//==============================================================================

#endif // OS_INTERMEDIATE_H

