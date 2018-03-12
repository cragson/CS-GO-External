#pragma once

#include "Game.h"

#include "XorStr.h"

#ifndef CONFIG_HEADER

#define CONFIG_HEADER

class Config {

public:

	// Handling the reading of cvars from config

	template< class A >

	A isValid( A Value, A Min, A Max ) {

		if ( Value < Min || Value > Max ) { return static_cast< A >( Max ); }

		return Value;
	}

	std::string getCvarAsString( std::string Module, std::string cvar );

	DWORD getCvarAsDword( std::string Module, std::string cvar );

	float getCvarAsFloat( std::string Module, std::string cvar );

	int getCvarAsInt( std::string Module, std::string cvar );

	bool getCvarAsBool( std::string Module, std::string cvar );

	// Handling the Config file itself

	bool createConfigFile();

	bool ExistsConfigFile();

	std::string getConfigFileLocation() const { return this->ConfigFileLocation; }

protected:

	void setConfigFileLocation( const std::string location ) { this->ConfigFileLocation = location; }

private:

	std::string ConfigFileLocation{ XorStr("C:\\_Config.ini") };
};

#endif // !CONFIG_HEADER