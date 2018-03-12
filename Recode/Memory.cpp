#include "Memory.h"

#include "Globals.h"

#include <TlHelp32.h>

#include "Game.h"

HWND Memory::findWindow( std::string windowname ) {

	HWND hWnd = FindWindowA( 0, windowname.c_str() );
	if ( !hWnd ) { return 0; }

	return hWnd;
}

DWORD Memory::findProcessID( HWND windowName ) {

	DWORD dwPid;
	if ( !GetWindowThreadProcessId( windowName, &dwPid ) ) { return 0; }

	return dwPid;
}

HANDLE Memory::findHandle( DWORD processid ) {

	HANDLE hTemp = OpenProcess( PROCESS_ALL_ACCESS, false, g_pGame->getProcessID() );
	if ( hTemp == INVALID_HANDLE_VALUE ) { return 0; }

	return hTemp;
}

bool Memory::findModule( std::string modulename ) {

	MODULEENTRY32 me32 = { sizeof( MODULEENTRY32 ) };

	HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPALL, g_pGame->getProcessID() );
	if ( hSnap == INVALID_HANDLE_VALUE ) { return 0; }

	if ( Module32First( hSnap, &me32 ) ) {
		 
		do {

			std::wstring wTemp = std::wstring( me32.szModule );

			std::string strModule = std::string( wTemp.begin(), wTemp.end() );

			if (strModule == modulename) { return true; }

		} while ( Module32Next( hSnap, &me32 ) );
	}
	
	CloseHandle( hSnap );
	
	return false;
}

bool Memory::UpdateModule( GameModule* gameModule ) {

	MODULEENTRY32 me32 = { sizeof( MODULEENTRY32 ) };

	HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPALL, g_pGame->getProcessID() );
	if ( hSnap == INVALID_HANDLE_VALUE ) { return false; }

	if ( Module32First( hSnap, &me32 ) ) {

		do {

			std::wstring wTemp{ me32.szModule };

			std::string strModule = std::string( wTemp.begin(), wTemp.end() );

			if ( gameModule->name == strModule ) {

				gameModule->baseAddress = ( std::uintptr_t )me32.modBaseAddr;

				gameModule->size = ( std::uintptr_t )me32.modBaseSize;
			}

		} while ( Module32Next( hSnap, &me32 ) );
	}

	CloseHandle( hSnap );

	return true;
}

Memory* g_pMemory = new Memory;