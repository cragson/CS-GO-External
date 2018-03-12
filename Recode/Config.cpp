#include "Config.h"

#include "Globals.h"

#include <Windows.h>

#include <string>

#include <fstream>

#include "XorStr.h"

std::string Config::getCvarAsString( std::string Module, std::string cvar ) {

	char szBuff[ 256 ];

	if ( !GetPrivateProfileStringA( Module.c_str(),
		cvar.c_str(),
		0,
		szBuff,
		sizeof( szBuff ),
		this->ConfigFileLocation.c_str() ) ) { return std::string(XorStr("1") ); }

	return std::string( szBuff );
}

DWORD Config::getCvarAsDword( std::string Module, std::string cvar ) {

	return static_cast< DWORD >( GetPrivateProfileIntA( Module.c_str(), cvar.c_str(), 0, this->ConfigFileLocation.c_str() ) );
}

float Config::getCvarAsFloat( std::string Module, std::string cvar ) {

	return std::stof( this->getCvarAsString(Module, cvar).c_str() );
}

int Config::getCvarAsInt( std::string Module, std::string cvar ) {

	return GetPrivateProfileIntA( Module.c_str(), cvar.c_str(), 0, this->ConfigFileLocation.c_str() );
}

bool Config::getCvarAsBool( std::string Module, std::string cvar ) {

	int i = this->getCvarAsInt( Module, cvar );

	if ( i != 1 ) { return false; }
	if ( i == 1 ) { return true; }

	return false; // Just to ignore the warning from VS. -.-"

}

bool Config::createConfigFile() {

	std::ofstream of_config;

	of_config.open( this->ConfigFileLocation );

	if ( of_config.fail() ) { return false; }

	of_config << XorStr(" [ + ] calb external [ + ] \n\n") << std::endl;

	of_config << XorStr(" [ - ] Settings [ - ] \n") << std::endl;

	of_config << XorStr("[Bhop]") << std::endl;

	of_config << XorStr("enabled=0") << std::endl;

	of_config << XorStr("enable_humanize=0") << std::endl;

	of_config << XorStr("fail_chance=1\t\t\t Minimum: 1, Maximum: 100") << std::endl;

	of_config << XorStr("\n[Trigger]") << std::endl;

	of_config << XorStr("enabled=0") << std::endl;

	of_config << XorStr("enable_delay=0") << std::endl;

	of_config << XorStr("enable_random_delay=0") << std::endl;

	of_config << XorStr("random_delay_maximum=50\t\t milliseconds; Minimum: 1, Maximum: 750") << std::endl;

	of_config << XorStr("delay=20\t\t\t\t milliseconds; Minimum: 1, Maximum: 750") << std::endl;

	of_config << XorStr("ignore_team=0\n") << std::endl;

	of_config << XorStr("[Glow]\n") << std::endl;

	of_config << XorStr("enabled=0") << std::endl;

	of_config << XorStr("show_enemies=1") << std::endl;

	of_config << XorStr("show_team=0\n") << std::endl;

	of_config << XorStr("health_mode=0\n") << std::endl;

	of_config << XorStr("health_alpha=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("health_occluded=0") << std::endl;

	of_config << XorStr("health_unoccluded=0\n") << std::endl;

	of_config << XorStr("custom_mode=0\n") << std::endl;

	of_config << XorStr("enemy_red=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("enemy_blue=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("enemy_green=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("enemy_alpha=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("enemy_occluded=1") << std::endl;

	of_config << XorStr("enemy_unoccluded=0\n") << std::endl;

	of_config << XorStr("friend_red=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("friend_blue=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("friend_green=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("friend_alpha=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("friend_occluded=1") << std::endl;

	of_config << XorStr("friend_unoccluded=0\n") << std::endl;

	of_config << XorStr("enable_bomb_glow=0\n") << std::endl;

	of_config << XorStr("bomb_alpha=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("bomb_red=0.0000\t\t     Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("bomb_blue=0.0000\t\t Minimum: 0, Maximum: 1") << std::endl;

	of_config << XorStr("bomb_green=0.0000\t\t Minimum: 0, Maximum: 1\n") << std::endl;

	of_config << XorStr("[RCS]\n") << std::endl;

	of_config << XorStr("enabled=0") << std::endl;

	of_config << XorStr("active_after_shots=1\t Minimum: 1, Maximum: 30") << std::endl;

	of_config << XorStr("enable_smooth=0") << std::endl;

	of_config << XorStr("smooth_x=1.0000\t\t\t Minimum: 1, Maximum: 15") << std::endl;

	of_config << XorStr("smooth_y=1.0000\t\t\t Minimum: 1, Maximum: 15") << std::endl;

	of_config << XorStr("enable_velocity_mode=0\t\t Activates RCS if your velocity/speed are lower or equal with lower_velocity.") << std::endl;

	of_config << XorStr("lower_velocity=0.000\t\t Minimum: 0, Maximum: 300") << std::endl;

	of_config << XorStr("\n\n A fun Project made by cragson / calb, \n\n\t have fun and thank you for using this cheat. ") << std::endl;

	
	of_config.close();

	return true;
}

bool Config::ExistsConfigFile() {

	DWORD dwConfigFile = GetFileAttributesA( this->ConfigFileLocation.c_str() );
	
	if ( dwConfigFile == INVALID_FILE_ATTRIBUTES ) { return false; }

	return true;
}