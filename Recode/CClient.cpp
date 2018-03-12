#include "CClient.h"

#include "Globals.h"

#include "Game.h"

std::uintptr_t CClient::getEnginePointer() const {

	return g_pMemory->Read< std::uintptr_t >( g_pGame->gM_Engine->baseAddress + Offsets::signatures::dwClientState );
}

std::uintptr_t CClient::getGlowObjectManager() const {

	return g_pMemory->Read< std::uintptr_t >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwGlowObjectManager );
}

void CClient::SimulateLeftMouseClick() const {

	SendMessage( g_pGame->getWindow(), WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM( 0, 0 ) );

	Sleep( 2 );

	SendMessage( g_pGame->getWindow(), WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM( 0, 0 ) );
}

CClient* g_pCClient = new CClient;