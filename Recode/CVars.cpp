#include "CVars.h"

#include "Config.h"

#include "Globals.h"

#include "XorStr.h"

void CVars::UpdateCvars() {

	while ( true ) {

		g_pCvars->Bhop->enabled = g_pGlobals->g_pConfig->getCvarAsBool(XorStr(" Bhop"), XorStr("enabled") );

		g_pCvars->Bhop->enable_humanize = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Bhop"), XorStr("enable_humanize") );

		g_pCvars->Bhop->fail_chance = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsInt(XorStr("Bhop"), XorStr("fail_chance") ), 1, 100 );


		g_pCvars->Trigger->enabled = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Trigger"), XorStr("enabled") );

		g_pCvars->Trigger->enable_delay = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Trigger"), XorStr("enable_delay") );

		g_pCvars->Trigger->enable_random_delay = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Trigger"), XorStr("enable_random_delay") );

		g_pCvars->Trigger->delay = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsInt(XorStr("Trigger"), XorStr("delay") ), 1, 750 );

		g_pCvars->Trigger->random_delay_maximum = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsInt(XorStr("Trigger"), XorStr("random_delay_maximum") ), 1, 750 );

		g_pCvars->Trigger->ignore_team = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Trigger"), XorStr("ignore_team") );


		g_pCvars->Glow->enabled = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("enabled") );

		g_pCvars->Glow->show_enemies = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("show_enemies") );

		g_pCvars->Glow->show_team = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("show_team") );

		g_pCvars->Glow->health_mode = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("health_mode") );

		g_pCvars->Glow->health_alpha = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("health_alpha") ), 0.f, 1.f );

		g_pCvars->Glow->healthOccluded = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("health_occluded") );

		g_pCvars->Glow->healthUnoccluded = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("health_unoccluded") );

		g_pCvars->Glow->custom_mode = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("custom_mode"));

		g_pCvars->Glow->enemyRed = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("enemy_red") ), 0.00f, 1.f);

		g_pCvars->Glow->enemyBlue = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("enemy_blue") ), 0.00f, 1.f);

		g_pCvars->Glow->enemyGreen = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("enemy_green") ), 0.00f, 1.f);

		g_pCvars->Glow->enemyAlpha = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("enemy_alpha") ), 0.00f, 1.f);

		g_pCvars->Glow->enemyUnoccluded = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("enemy_unoccluded") );

		g_pCvars->Glow->enemyOccluded = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("enemy_occluded") );

		g_pCvars->Glow->friendRed = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("friend_red") ), 0.00f, 1.f );

		g_pCvars->Glow->friendBlue = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("friend_blue") ), 0.00f, 1.f );

		g_pCvars->Glow->friendGreen = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("friend_green") ), 0.00f, 1.f );

		g_pCvars->Glow->friendAlpha = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("friend_alpha") ), 0.00f, 1.f );

		g_pCvars->Glow->friendUnoccluded = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("friend_unoccluded") );

		g_pCvars->Glow->friendOccluded = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("friend_occluded") );

		g_pCvars->Glow->enable_bomb_glow = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("Glow"), XorStr("enable_bomb_glow"));

		g_pCvars->Glow->bombRed = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("bomb_red") ), 0.f, 1.f );

		g_pCvars->Glow->bombBlue = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("bomb_blue") ), 0.f, 1.f );

		g_pCvars->Glow->bombGreen = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("bomb_green") ), 0.f, 1.f );

		g_pCvars->Glow->bombAlpha = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("Glow"), XorStr("bomb_alpha") ), 0.f, 1.f );

		
		g_pCvars->Rcs->enabled = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("RCS"), XorStr("enabled"));

		g_pCvars->Rcs->active_after_shots = g_pGlobals->g_pConfig->isValid(g_pGlobals->g_pConfig->getCvarAsInt(XorStr("RCS"), XorStr("active_after_shots")), 1, 30);

		g_pCvars->Rcs->enable_smooth = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("RCS"), XorStr("enable_smooth"));

		g_pCvars->Rcs->smooth_x = g_pGlobals->g_pConfig->isValid(g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("RCS"), XorStr("smooth_x") ), 1.f, 15.f );

		g_pCvars->Rcs->smooth_y = g_pGlobals->g_pConfig->isValid(g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("RCS"), XorStr("smooth_y") ), 1.f, 15.f );

		g_pCvars->Rcs->enable_velocity_mode = g_pGlobals->g_pConfig->getCvarAsBool(XorStr("RCS"), XorStr("enable_velocity_mode") );

		g_pCvars->Rcs->lower_velocity = g_pGlobals->g_pConfig->isValid( g_pGlobals->g_pConfig->getCvarAsFloat(XorStr("RCS"), XorStr("lower_velocity") ), 0.f, 300.f );

		Sleep( 500 );
	}
	
}

CBhop* CVars::Bhop = new CBhop;

CTrigger* CVars::Trigger = new CTrigger;

CGlow* CVars::Glow = new CGlow;

CRcs* CVars::Rcs = new CRcs;

CVars* g_pCvars = new CVars;