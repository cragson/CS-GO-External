#include "Worker.h"

#include <Windows.h>

#include "Globals.h"

#include "Game.h"

#include "CVars.h"

void Worker::setActiveWindow( const HWND window ) {

	this->hActiveWindow = ( window != 0 && window != this->hActiveWindow ) ? window : this->hActiveWindow;
}

bool Worker::isCSGO() const {

	return this->hActiveWindow == g_pGame->getWindow();
}

void Worker::Work() {

	HWND hForeGround{ 0 };

	/*

			The worker thread is doing some side stuff like updating cvars, checking if window is still active and some other stuff.

	*/

	while ( true ) {

		// Checking if CSGO is active window

		hForeGround = GetForegroundWindow();

		if ( hForeGround != 0 && hForeGround != hActiveWindow ) {

			hActiveWindow = GetForegroundWindow();
		}

		Sleep( 1 );
	}
	
}

HWND Worker::hActiveWindow{ 0 };