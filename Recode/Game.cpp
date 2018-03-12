#include "Game.h"

#include <Windows.h>

#include "Globals.h"

#include "XorStr.h"

Game::Game( HWND window, DWORD pid, HANDLE handle ) : hWindow{ window }, dwPid{ pid }, hGame{ handle } {

}

Game::~Game() {

	this->closeHandle();
}

bool Game::closeHandle() {

	return CloseHandle( this->hGame );
}

bool Game::Initialize() {

	// Creating now Window, Process Id and the handle to the game.

	HWND hTemp = g_pMemory->findWindow(XorStr("Counter-Strike: Global Offensive") );
	if ( !hTemp ) { return false; }

	g_pGame->setWindow( hTemp );

	DWORD dwTemp = g_pMemory->findProcessID( hTemp );
	if ( !dwTemp ) { return false; }

	g_pGame->setProcessID( dwTemp );

	HANDLE handleTemp = g_pMemory->findHandle( dwTemp );
	if ( handleTemp == INVALID_HANDLE_VALUE ) { return false; }

	g_pGame->setHandle( handleTemp );

	// Now after checking for invalidation, we're goint to define our names for the two game modules.
	// After that we're going to check if the module was found in the binary and if so we are going to update our module data.
	 
	g_pGame->gM_Client->name = XorStr("client.dll");

	g_pGame->gM_Engine->name = XorStr("engine.dll");

	if ( !g_pMemory->findModule( g_pGame->gM_Client->name ) || !g_pMemory->findModule( g_pGame->gM_Engine->name ) ) { return false; }

	g_pMemory->UpdateModule( g_pGame->gM_Client );

	g_pMemory->UpdateModule( g_pGame->gM_Engine );

	return true;
}

void Game::setWindow( const HWND& window ) {

	this->hWindow = ( window != 0 && window != this->getWindow() ) ? window : this->hWindow ;
}

void Game::setProcessID( const DWORD& pid ) {

	this->dwPid = ( pid != 0 && pid != this->getProcessID() ) ? pid : this->dwPid;
}

void Game::setHandle( const HANDLE& handle ) {

	this->hGame = ( handle != INVALID_HANDLE_VALUE && handle != 0 ) ? handle : this->hGame;
}

GameModule* Game::gM_Client = new GameModule;

GameModule* Game::gM_Engine = new GameModule;

Game* g_pGame = new Game;