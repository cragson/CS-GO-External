#pragma once

#include "Game.h"

#ifndef WORKER_HEADER

#define WORKER_HEADER

class Worker {

public:

	HWND getActiveWindow() const { return hActiveWindow; }

	bool isEqualWindow( const HWND window ) const { return window == hActiveWindow; }

	bool isCSGO() const;

	static void Work();

	static HWND hActiveWindow;

protected:

	void setActiveWindow( const HWND window );	

};

#endif // !WORKER_HEADER