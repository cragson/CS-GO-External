#include "Bhop.h"

#include "Globals.h"

#include "Localplayer.h"

#include "Math.h"

#include "Movement.h"

void Bhop::Action() {

	std::uintptr_t LocalPlayer{ 0x0 };

	bool bCase{ false };

	size_t flags{ 0 };

	while ( true ) {

		if ( g_pGlobals->g_pWorker->isCSGO() && g_pCvars->Bhop->enabled ) {

			LocalPlayer = g_pLocalPlayer->getLocalplayer();

			flags = g_pLocalPlayer->getFlags();

			bCase = g_pMath->SimulateRoll( g_pCvars->Bhop->fail_chance );

			if ( ( GetAsyncKeyState( VK_SPACE ) & 0x8000 ) && g_pLocalPlayer->IsOnGround() ) {

				if ( g_pCvars->Bhop->enable_humanize ) {

					if ( bCase ) {

						g_pLocalPlayer->doJump();

						continue;
					}
					
				}		

				if ( !g_pCvars->Bhop->enable_humanize && g_pCvars->Bhop->enabled ) {

					g_pLocalPlayer->doJump();
				}
							
			}
		}
		Sleep( 1 );
	}
}
