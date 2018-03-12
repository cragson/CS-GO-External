#pragma once

#include "Game.h"

#ifndef LOG_HEADER

#define LOG_HEADER

class Log {

public:

	void printLine( const std::string message ) const;

	void print( const std::string message ) const;

	void printColor( const std::string message, __int8 color1 = 0, __int8 color2 = 1 );

	void printColorLine( const std::string message, __int8 color1 = 0, __int8 color2 = 1 );

	void DebugInfo( const std::string message ) const;

	void Success( const std::string message ) const;

	void Error( const std::string message ) const;

	void Warning( const std::string message ) const;

	void changeFGColor( __int8 background, __int8 foreground );

	void cleanColor();

protected:

private:

};

#endif // !LOG_HEADER