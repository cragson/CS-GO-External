
#include "Globals.h"

#include "Game.h"

#include "Math.h"

#include "Localplayer.h"

#include "XorStr.h"

int main()
{

	std::string title = XorStr(" [ + ] calb external [ + ] ");

	SetConsoleTitleA( title.c_str() );

	g_pGlobals->g_pLog->printColor(XorStr("\n\n Waiting for modules to be loaded.."), CC_BLACK, CC_YELLOW );

	while ( !g_pGame->Initialize() ) {

		g_pGlobals->g_pLog->printColor(XorStr("."), CC_BLACK, CC_YELLOW );

		Sleep( 1250 );
	}

	g_pGlobals->g_pLog->printColorLine(XorStr("found and updated Modules!"), CC_BLACK, CC_GREEN );

	g_pGlobals->g_pLog->printColor(XorStr("\n Now checking for valid Config.."), CC_BLACK, CC_YELLOW );

	if ( !g_pGlobals->g_pConfig->ExistsConfigFile() ) {

		g_pGlobals->g_pLog->Error(XorStr("Whoops! I found no config, so let me create one for you.") );

		g_pGlobals->g_pLog->Warning(XorStr(" BE SURE THIS PROGRAMM HAS ADMINISTRATION RIGHTS! "));

		while (!g_pGlobals->g_pConfig->createConfigFile()) {

			std::cout << XorStr(".");

			Sleep( 500 );
		}

		g_pGlobals->g_pLog->Success(XorStr("Created a fresh config file for you @ ") + g_pGlobals->g_pConfig->getConfigFileLocation() );

		Sleep( 1250 );
	}
	else {
		
		g_pGlobals->g_pLog->printColorLine(XorStr("found a valid config!"), CC_BLACK, CC_GREEN );
	}

	g_pGlobals->g_pLog->printColorLine(XorStr("\n\n --- Some debug related stuff --- \n"), CC_BLACK, CC_BLUE );

	g_pGlobals->g_pLog->printColorLine(XorStr(" Window Handle : ") + std::to_string( ( DWORD )( g_pGame->getWindow() ) ), CC_BLACK, CC_BLUE);

	g_pGlobals->g_pLog->printColorLine(XorStr(" Process ID : ") + std::to_string( g_pGame->getProcessID() ), CC_BLACK, CC_BLUE );

	g_pGlobals->g_pLog->printColorLine(XorStr(" Process Handle : 0x") + std::to_string((DWORD)(g_pGame->getHandle())), CC_BLACK, CC_BLUE);

	g_pGlobals->g_pLog->printColorLine(XorStr(" Client Base @ ") + std::to_string( g_pGame->gM_Client->baseAddress ), CC_BLACK, CC_BLUE );

	g_pGlobals->g_pLog->printColorLine(XorStr(" Engine Base @ ") + std::to_string( g_pGame->gM_Engine->baseAddress ), CC_BLACK, CC_BLUE );

	g_pGlobals->g_pLog->printColorLine(XorStr("----------------------------------------"), CC_BLACK, CC_BLUE );


	g_pGlobals->g_pLog->Warning(XorStr("Starting now the features!") );

	CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )g_pCvars->UpdateCvars, 0, 0, 0 );

	CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )g_pGlobals->g_pWorker->Work, 0, 0, 0 );

	CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )g_pGlobals->g_pHandler->bhop->Action, 0, 0, 0 );

	CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )g_pGlobals->g_pHandler->trigger->Action, 0, 0, 0 );

	CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )g_pGlobals->g_pHandler->glow->Action, 0, 0, 0 );

	CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )g_pGlobals->g_pHandler->rcs->Action, 0, 0, 0 );

	std::cin.get();

    return 0;
}

