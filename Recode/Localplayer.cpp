#include "Localplayer.h"

#include "Globals.h"

#include "Memory.h"

#include "Entity.h"

#include "CClient.h"

#include "Movement.h"

std::uintptr_t LocalPlayer::getLocalplayer() const {

	return g_pMemory->Read< std::uintptr_t >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwLocalPlayer );
}

std::uintptr_t LocalPlayer::getPlayerInCrosshair() const {

	return g_pMemory->Read< std::uintptr_t >( 

		g_pGame->gM_Client->baseAddress + Offsets::signatures::dwEntityList 
		+ 
		( ( g_pMemory->Read< std::uintptr_t >( this->getLocalplayer() + Offsets::netvars::m_iCrosshairId ) - 1 ) * 0x10 ) );
}

int LocalPlayer::getHealth() const {

	return g_pMemory->Read< int >( this->getLocalplayer() + Offsets::netvars::m_iHealth );
}

int LocalPlayer::getTeam() const {

	return g_pMemory->Read< int >( this->getLocalplayer() + Offsets::netvars::m_iTeamNum );
}

int LocalPlayer::getFlags() const {

	return g_pMemory->Read< int >( this->getLocalplayer() + Offsets::netvars::m_fFlags );
}

int LocalPlayer::getEntityListIndex() const {
	
	std::uintptr_t localplayer = this->getLocalplayer();
	if ( !localplayer ) { return -1; }

	std::uintptr_t entity{ 0x0 };

	for ( int iterator = 1; iterator <= 64; iterator++ ) {

		entity = g_pEntity->getEntityByIndex( iterator );
		if ( !!entity && entity != localplayer ) { return iterator; }
	}

	return -1;
}

int LocalPlayer::getShotsfired() const {

	return g_pMemory->Read< int >( this->getLocalplayer() + Offsets::netvars::m_iShotsFired );
}

bool LocalPlayer::IsOnGround() const {

	return ( this->getFlags() & FL_ONGROUND ? true : false );
}

bool LocalPlayer::IsShooting() const {

	return g_pMemory->Read< int >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwForceAttack ) == 5;
}

void LocalPlayer::doJump() {

	g_pMemory->Write< int >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwForceJump, 6 );

}

void LocalPlayer::doShoot() {

	SendMessage( g_pGame->getWindow(), WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM( 0, 0 ) );

	Sleep( 2 );

	SendMessage( g_pGame->getWindow(), WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM( 0, 0 ) );
}

void LocalPlayer::setViewAngles( const Vector &Angles ) {

	g_pMemory->Write< Vector >( g_pCClient->getEnginePointer() + Offsets::signatures::dwClientState_ViewAngles, Angles );
}

Vector LocalPlayer::getViewAngles() const {

	return g_pMemory->Read< Vector >( g_pCClient->getEnginePointer() + Offsets::signatures::dwClientState_ViewAngles );
}

Vector LocalPlayer::getAimPunch() const {

	return g_pMemory->Read< Vector >( this->getLocalplayer() + Offsets::netvars::m_aimPunchAngle );
}

Vector LocalPlayer::getPos() const {

	return g_pMemory->Read< Vector >( this->getLocalplayer() + Offsets::netvars::m_vecOrigin );
}

Vector LocalPlayer::getEyePos() const {

	Vector vAlpha, vBeta, vFinal;

	vAlpha = g_pMemory->Read< Vector >(this->getLocalplayer() + Offsets::netvars::m_vecOrigin);

	vBeta = g_pMemory->Read< Vector >(this->getLocalplayer() + Offsets::netvars::m_vecViewOffset);

	vFinal = vAlpha + vBeta;

	return vFinal;
}

float LocalPlayer::getSpeed() const {

	Vector vecTemp{ g_pMemory->Read< Vector >( g_pLocalPlayer->getLocalplayer() + Offsets::netvars::m_vecVelocity ) };

	return sqrtf( vecTemp.x * vecTemp.x + vecTemp.y * vecTemp.y ); // Betrag / Länge des Vektors 2D  -> Keine z-Achse da Verfälschung der Geschwindigkeit.
}

int LocalPlayer::getCurrentItem() const {

	std::uintptr_t ItemHandle = g_pMemory->Read< std::uintptr_t >( g_pLocalPlayer->getLocalplayer() + Offsets::netvars::m_hActiveWeapon );

	std::uintptr_t ItemPtr = g_pMemory->Read< std::uintptr_t >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwEntityList + ( ( ItemHandle & 0xFFF ) - 1 ) * 0x10 );

	return g_pMemory->Read< int >( ItemPtr + Offsets::netvars::m_iItemDefinitionIndex );
}

LocalPlayer* g_pLocalPlayer = new LocalPlayer;