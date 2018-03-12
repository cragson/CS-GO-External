#include "Entity.h"

#include "Globals.h"

#include "CClient.h"

std::uintptr_t Entity::getEntityByIndex( int index ) const {

	return g_pMemory->Read< std::uintptr_t >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwEntityList + ( index * 0x10 ) );
}

int Entity::getTeam( std::uintptr_t entity ) const {

	return g_pMemory->Read< int >( entity + Offsets::netvars::m_iTeamNum);
}

int Entity::getHealth( std::uintptr_t entity ) const {

	return g_pMemory->Read< int >( entity + Offsets::netvars::m_iHealth );
}

int Entity::getGlowIndex( std::uintptr_t entity ) const {

	return g_pMemory->Read< int >( entity + Offsets::netvars::m_iGlowIndex );
}

int Entity::getClassID( std::uintptr_t entity ) const {

	return g_pMemory->Read< int >( g_pMemory->Read< int > ( g_pMemory->Read< int >( g_pMemory->Read< int >( entity + 0x8 ) + 0x8 ) + 0x1 ) + 0x14 );
}

void Entity::setGlow( int index = 0, float red = 0.00f, float blue = 0.00f, float green = 0.00f, float alpha = 0.00f, bool a1 = false, bool a2 = false ) {

	std::uintptr_t pGlowArray = g_pCClient->getGlowObjectManager();


	g_pMemory->Write< float >( pGlowArray + ( index * sizeof( GlowObject_t ) + 0x4 ), red );

	g_pMemory->Write< float >( pGlowArray + ( index * sizeof( GlowObject_t ) + 0x8 ), green );

	g_pMemory->Write< float >( pGlowArray + ( index * sizeof( GlowObject_t ) + 0xC ), blue );

	g_pMemory->Write< float >( pGlowArray + ( index * sizeof( GlowObject_t ) + 0x10 ), alpha );


	g_pMemory->Write< bool >( pGlowArray + ( index * sizeof( GlowObject_t ) + 0x24 ), a1 );

	g_pMemory->Write< bool >( pGlowArray + ( index * sizeof( GlowObject_t ) + 0x25 ), a2 );

}

void Entity::setGlowHealth( int index, int health, float alpha, bool a1, bool a2 ) {

	float delta_green = static_cast< float >( health / 100.0 ); 

	float delta_red = static_cast< float >( 1.0 - delta_green );

	this->setGlow( index, delta_red, 0.00f, delta_green, alpha, a1, a2 );

}

Entity* g_pEntity = new Entity;