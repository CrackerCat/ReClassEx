#pragma once

//#include <afxribbonbar.h> //used for ribbon bar. comment this out if not used

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "ReClass64_dbg.lib")
#else
#pragma comment(lib, "ReClass64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "ReClass_dbg.lib")
#else
#pragma comment(lib, "ReClass.lib")
#endif
#endif

#define PLUGIN_CC __stdcall

typedef BOOL( PLUGIN_CC *tReadMemoryOperation )(IN LPVOID Address, IN LPVOID Buffer, IN SIZE_T Size, OUT PSIZE_T BytesRead);
typedef BOOL( PLUGIN_CC *tWriteMemoryOperation )(IN LPVOID Address, IN LPVOID Buffer, IN SIZE_T Size, OUT PSIZE_T BytesWritten);
typedef HANDLE( PLUGIN_CC *tOpenProcessOperation )(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN DWORD dwProcessID);
typedef HANDLE( PLUGIN_CC *tOpenThreadOperation )(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN DWORD dwThreadID);

typedef struct _RECLASS_PLUGIN_INFO
{
	#ifdef __cplusplus
	_RECLASS_PLUGIN_INFO( ) : DialogID( -1 ) { }
	#endif
	wchar_t Name[ 260 ];
	wchar_t About[ 2048 ];
	wchar_t Version[ 64 ];
	int DialogID;
} RECLASS_PLUGIN_INFO, *LPRECLASS_PLUGIN_INFO;

BOOL PLUGIN_CC PluginInit( LPRECLASS_PLUGIN_INFO lpRCInfo );
VOID PLUGIN_CC PluginStateChange( BOOL state );
INT_PTR CALLBACK PluginSettingsDlg( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/*
*	Register overides for the read/write memory operations
*	returns false if a plugin has already registered it or one of the paramaters was null
*	returns true if succeeded or if force flag is set
*/
BOOL PLUGIN_CC ReClassOverrideReadMemoryOperation( tReadMemoryOperation MemRead );
BOOL PLUGIN_CC ReClassOverrideWriteMemoryOperation( tWriteMemoryOperation MemWrite );
BOOL PLUGIN_CC ReClassOverrideMemoryOperations( tReadMemoryOperation MemRead, tWriteMemoryOperation MemWrite );

/*
 *	Register overides for the opening of handles for various process/thread operations
 *	returns false if a plugin has already registered it or one of the paramaters was null
 *	returns true if succeeded or if force flag is set
 */
BOOL PLUGIN_CC ReClassOverrideOpenProcessOperation( tOpenProcessOperation ProcessOpen );
BOOL PLUGIN_CC ReClassOverrideOpenThreadOperation( tOpenThreadOperation ThreadOpen );
BOOL PLUGIN_CC ReClassOverrideHandleOperations( tOpenProcessOperation ProcessOpen, tOpenThreadOperation ThreadOpen );

/*
*	Print text to the ReClass console window
*/
VOID PLUGIN_CC ReClassPrintConsole( const wchar_t *format, ... );

/*
 *	Get the current attached process handle, null if not attached
 */
HANDLE PLUGIN_CC ReClassGetProcessHandle( );

/*
 *	Return the main window handle for ReClass
 */
HWND PLUGIN_CC ReClassMainWindow( );

#ifdef _MFC_VER 
/*
 *	Get the ribbon interface for MFC (useful for adding custom buttons and such)
 */
CMFCRibbonBar* PLUGIN_CC ReClassRibbonInterface( );
#endif
