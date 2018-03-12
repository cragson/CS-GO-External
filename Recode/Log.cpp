#include "Globals.h"

#include <Windows.h>

#include "XorStr.h"

void Log::printLine( const std::string message ) const {

	std::cout << message.c_str() << std::endl;
}

void Log::print( const std::string message ) const {

	std::cout << message.c_str();
}

void Log::printColor( const std::string message, __int8 color1, __int8 color2 ) {

	g_pGlobals->g_pLog->changeFGColor( color1, color2 );

	std::cout << message.c_str();

	g_pGlobals->g_pLog->cleanColor();
}

void Log::printColorLine( const std::string message, __int8 color1, __int8 color2 ) {

	g_pGlobals->g_pLog->changeFGColor( color1, color2 );

	std::cout << message.c_str() << std::endl;

	g_pGlobals->g_pLog->cleanColor();
}

void Log::DebugInfo( const std::string message ) const {

	g_pGlobals->g_pLog->changeFGColor( CC_BLACK, CC_CYAN );

	std::cout << XorStr("\n { DEBUG } ") << message.c_str() << std::endl;

	g_pGlobals->g_pLog->cleanColor();
}

void Log::Success( const std::string message ) const {

	g_pGlobals->g_pLog->changeFGColor( CC_BLACK, CC_GREEN );

	std::cout << XorStr("\n { SUCCESS } ") << message.c_str() << std::endl;

	g_pGlobals->g_pLog->cleanColor();
}

void Log::Error( const std::string message ) const {

	g_pGlobals->g_pLog->changeFGColor( CC_BLACK, CC_RED );

	std::cout << XorStr("\n { ERROR } ") << message.c_str() << std::endl;

	g_pGlobals->g_pLog->cleanColor();
}

void Log::Warning( const std::string message ) const {

	g_pGlobals->g_pLog->changeFGColor( CC_BLACK, CC_YELLOW );

	std::cout << XorStr("\n { WARNING } ") << message.c_str() << std::endl;

	g_pGlobals->g_pLog->cleanColor();
}

void Log::changeFGColor( __int8 background, __int8 foreground ) {

	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ( ( 16 * background ) + foreground ) );
}

void Log::cleanColor() {

	g_pGlobals->g_pLog->changeFGColor( CC_BLACK, CC_WHITE );
}
