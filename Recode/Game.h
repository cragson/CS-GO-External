#pragma once

#include <Windows.h>

#include <cstdint>

#include <string>

#ifndef GAME_HEADER

#define GAME_HEADER

typedef struct GameModule {

	std::string name;

	std::uintptr_t baseAddress;

	std::uintptr_t size;
}gM_t;

class Game {

public:

	Game( HWND window = 0, DWORD pid = 0, HANDLE handle = 0 );

	~Game();

	HWND getWindow() const;

	DWORD getProcessID() const;

	HANDLE getHandle() const;

	static GameModule* gM_Client;

	static GameModule* gM_Engine;

	bool Initialize();

protected:

	void setWindow( const HWND& window );

	void setProcessID( const DWORD& pid );

	void setHandle( const HANDLE& handle );

	bool closeHandle();

private:

	HWND hWindow{ 0 };

	DWORD dwPid{ 0 };

	HANDLE hGame{ 0x0 };

};

inline HWND Game::getWindow() const {

	return this->hWindow;
}

inline DWORD Game::getProcessID() const {

	return this->dwPid;
}

inline HANDLE Game::getHandle() const {

	return this->hGame;
}

extern Game* g_pGame;

#endif // !GAME_HEADER