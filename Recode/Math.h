#pragma once

#include <Windows.h>

#include <time.h>

#include "Vektor.h"

class Math {

public:

	template< class I >
	I randomNumber( I Range ) { 
		
		srand( time( 0 ) + rand() % RAND_MAX + 1 ); // Randomizing intializiation seed with unix timestamp

		return static_cast< I >( rand() % static_cast< int >( Range ) + 1 ); 
	}


	template< class I, class O >
	float getPercentageValue( I GW, O PS ) { return static_cast< float >( ( ( GW / 100 ) ) * PS ); }

	bool isCase( const size_t case_chance, const size_t base = 100 ) const;

	bool SimulateRoll( const size_t win_area, const size_t base_area = 100 ) const;

	/*=================================*/
	//  Credits to Ar1i / Radat for these functions.

	void NormalizeIt( Vector& angles );

	void ClampIt( Vector& angles );

	bool ClampAngles(Vector& angles);

	/*=================================*/

protected:

private:

};

extern Math* g_pMath;