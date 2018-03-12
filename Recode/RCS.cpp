#include "RCS.h"

#include "Globals.h"

#include "Localplayer.h"

#include "CVars.h"

#include "Math.h"

void RCS::Action() {

	Vector aimPunch, oldAimPunch, playerViewAngles, deltaVec;

	float flSpeed{ 0.f };

	oldAimPunch.x = 0;

	oldAimPunch.y = 0;

	while ( true ) {

		if ( g_pCvars->Rcs->enabled ) {

			flSpeed = g_pLocalPlayer->getSpeed();

			if ( g_pLocalPlayer->getShotsfired() > g_pCvars->Rcs->active_after_shots ) {

				if ( g_pCvars->Trigger->active ) {
					
					Sleep( 1 ); // CPU Usage dirty fix

					continue;
				}

				if ( g_pCvars->Rcs->enable_velocity_mode && flSpeed > g_pCvars->Rcs->lower_velocity ) { 

					Sleep( 1 ); // CPU Usage dirty fix

					continue;
				}

				playerViewAngles = g_pLocalPlayer->getViewAngles();

				aimPunch = g_pLocalPlayer->getAimPunch() * 2.f;

				if ( g_pCvars->Rcs->enable_smooth ) {

					aimPunch.x /= g_pCvars->Rcs->smooth_y;

					aimPunch.y /= g_pCvars->Rcs->smooth_x;
				}

				playerViewAngles = ( playerViewAngles + oldAimPunch ) - aimPunch;

				oldAimPunch = aimPunch;

				if ( g_pMath->ClampAngles( playerViewAngles ) ) {

					g_pLocalPlayer->setViewAngles( playerViewAngles );
				}
			}
			else {

				oldAimPunch.x = 0.f;

				oldAimPunch.y = 0.f;
			}
		}

		Sleep( 1 );
	}

}