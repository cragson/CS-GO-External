#pragma once

#include "Basics.h"

#include "Vektor.h"

#include "Game.h"

#include "Memory.h"

#include "Log.h"

#include "Worker.h"

#include "Config.h"

#include "CVars.h"

#include "ConsoleColors.h"

#include "Offsets.h"

#include "Handler.h"

#ifndef GLOBALS_HEADER

#define GLOBALS_HEADER

class Globals {

public:

	static Log* g_pLog;

	static Worker* g_pWorker;

	static Config* g_pConfig;

	static Handler* g_pHandler;

};

extern Globals* g_pGlobals;

#endif // !GLOBALS_HEADER
