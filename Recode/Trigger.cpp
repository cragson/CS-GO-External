#include "Trigger.h"

#include "Globals.h"

#include "CVars.h"

#include "Localplayer.h"

#include "Entity.h"

#include "Math.h"

#include "Game.h"

#include "CClient.h"

void Trigger::Action() {

	std::uintptr_t entity{ 0x0 };

	int entity_team{ -1 };

	int entity_life{ -1 };

	size_t trigger_delay{ 0 };


	while ( true ) {

		// Checking if Csgo is active Window and if Key is pressed with flag 0x8000

		if ( g_pGlobals->g_pWorker->isCSGO() && ( GetAsyncKeyState( 0x6 ) & 0x8000 ) && g_pCvars->Trigger->enabled ) {

			// Setting global var to active state

			g_pCvars->Trigger->active = true;

			// Just setting the delay to zero, so no anomalies can exist.. hopefully

			trigger_delay = 0;

			// Getting the entity in crosshair, the team and the health of it.

			entity = g_pLocalPlayer->getPlayerInCrosshair();

			if ( !entity ) { 

				Sleep( 1 );

				continue;
			}


			entity_team = g_pEntity->getTeam( entity );

			entity_life = g_pEntity->getHealth( entity );

			if ( entity_life <= 0 || entity_life > 100 ) { 
				
				Sleep( 1 );

				continue; 
			}

			// Checking if the trigger delay is enabled

			if ( g_pCvars->Trigger->enable_delay ) {

				// Here we set our trigger delay to the delay from the cvars.

				trigger_delay = g_pCvars->Trigger->delay;
			}


			// Checking if random delay is enabled

			if ( g_pCvars->Trigger->enable_random_delay ) {

				// Here we add to our current delay the random delay on top.

				trigger_delay += g_pMath->randomNumber< int >( g_pCvars->Trigger->random_delay_maximum );

			}

			Sleep( trigger_delay );

			if ( g_pCvars->Trigger->ignore_team ) {

				g_pCClient->SimulateLeftMouseClick();
			}

			if ( !g_pCvars->Trigger->ignore_team && entity_team != g_pLocalPlayer->getTeam() ) {
	
				g_pCClient->SimulateLeftMouseClick();
			}

			// Deactivating now global var.

			g_pCvars->Trigger->active = false;
		}

		Sleep( 1 );
	}

}