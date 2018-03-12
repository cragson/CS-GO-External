#pragma once

#include "Game.h"

#ifndef MEMORY_HEADER

#define MEMORY_HEADER

class Memory {

public:

	template< class T >

	T Read( std::uintptr_t A ) {

		T tBuff;

		ReadProcessMemory( g_pGame->getHandle(), reinterpret_cast< LPCVOID >( A ), &tBuff, sizeof( tBuff ), 0 );

		return tBuff;
	}

	template< class T >

	bool Write( std::uintptr_t A, T V ) {

		return WriteProcessMemory( g_pGame->getHandle(), reinterpret_cast< LPVOID >( A ), &V, sizeof( V ), 0 );
	}

	HWND findWindow( std::string windowname );

	DWORD findProcessID( HWND windowName );

	HANDLE findHandle( DWORD processid );

	bool findModule( std::string modulename );

	bool UpdateModule( GameModule* gamemodule );

protected:

private:

};

extern Memory* g_pMemory;

#endif // ! MEMORY_HEADER