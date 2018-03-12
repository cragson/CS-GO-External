#include "Glow.h"

#include "Globals.h"

#include "Localplayer.h"

#include "Entity.h"

#include "CVars.h"

#include "CClient.h"

void Glow::Action() {

	std::uintptr_t entity{ 0x0 };

	size_t entity_team{ 0 };

	size_t entity_health{ 0 };

	size_t local_team{ 0 };

	std::uintptr_t local{ 0x0 };

	size_t classID{ 0 };

	size_t glowObjects{ 0 };

	GlowObject_t glowObject;

	std::uintptr_t glowObjectManager{ 0x0 };


	while ( true ) {

		if ( g_pGlobals->g_pWorker->isCSGO() && g_pCvars->Glow->enabled ) {

			local = g_pLocalPlayer->getLocalplayer();

			local_team = g_pLocalPlayer->getTeam();

			glowObjectManager = g_pCClient->getGlowObjectManager();
			if ( !glowObjectManager ) { 

				Sleep( 1 );

				continue; 
			}

			glowObjects = g_pMemory->Read< int >( g_pGame->gM_Client->baseAddress + Offsets::signatures::dwGlowObjectManager + 0xC );
			if ( !glowObjects || glowObjects <= 0 ) {

				Sleep( 1 );

				continue;
			}

			for( int i = 1; i <= glowObjects; i++ ) {

				glowObject = g_pMemory->Read< GlowObject_t >( glowObjectManager + i * sizeof( GlowObject_t ) );
				
				entity = glowObject.pEntity;

				if ( !entity || entity == local ) { 

					//Sleep( 1 );

					continue; 
				}

				classID = g_pEntity->getClassID( entity );

				if ( g_pCvars->Glow->enable_bomb_glow && ( classID == CPlantedC4 || classID == CC4 ) ) {

					g_pEntity->setGlow( i, g_pCvars->Glow->bombRed, g_pCvars->Glow->bombBlue, g_pCvars->Glow->bombGreen, g_pCvars->Glow->bombAlpha, true, false );

					continue;
				}

				entity_health = g_pEntity->getHealth( entity );

				if ( !entity_health || entity_health <= 0 ) { 

					//Sleep( 1 );

					continue; 
				}

				entity_team = g_pEntity->getTeam( entity );


				if ( !g_pCvars->Glow->custom_mode && g_pCvars->Glow->health_mode ) {

					g_pEntity->setGlowHealth( i, entity_health, g_pCvars->Glow->health_alpha, g_pCvars->Glow->healthOccluded, g_pCvars->Glow->healthUnoccluded );
				}

				if ( g_pCvars->Glow->custom_mode ) {

					if ( entity_team == local_team ) {

						g_pEntity->setGlow(
							i,
							g_pCvars->Glow->friendRed,
							g_pCvars->Glow->friendBlue,
							g_pCvars->Glow->friendGreen,
							g_pCvars->Glow->friendAlpha,
							g_pCvars->Glow->friendOccluded,
							g_pCvars->Glow->friendUnoccluded );
					}

					if ( entity_team != local_team ) {

						g_pEntity->setGlow(
							i,
							g_pCvars->Glow->enemyRed,
							g_pCvars->Glow->enemyBlue,
							g_pCvars->Glow->enemyGreen,
							g_pCvars->Glow->enemyAlpha,
							g_pCvars->Glow->enemyOccluded,
							g_pCvars->Glow->enemyUnoccluded );
					}		

				}

				if ( entity_team == local_team && g_pCvars->Glow->show_team  && !g_pCvars->Glow->custom_mode && !g_pCvars->Glow->health_mode ) {

					g_pEntity->setGlow( i, 0.f, 0.f, 1.0f, 0.766f, true, false );

				}

				if( entity_team != local_team && g_pCvars->Glow->show_enemies && !g_pCvars->Glow->custom_mode && !g_pCvars->Glow->health_mode ) {

					g_pEntity->setGlow( i, 1.f, 0.f, 0.f, 0.766f, true, false );

				}

			}

		}

		Sleep( 1 );
	}

}