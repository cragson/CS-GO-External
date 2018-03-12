#include "Math.h"

#include <iostream>

// Zweck der Funktion: Unter Einfluss einer Fehlschlagchance eine Aussage treffen können.
//
// Beispiel : case_chance := Chance dass es fehlschlägt, delta_chance := Chance dass es nicht fehlschlägt, base := 100, da ich immer von 100% ausgehe.
// 
// case_chance = 10 <=> 10% Chance dass es fehlschlägt.
//
// delta_chance = 100 % - 10 % ( case_chance ) => delta_chance = 90 %, d.h in 90% der Fällen klappt es.
//
// Jetzt lasse ich mir eine Zufallszahl zwischen 1-100 generieren und schaue in welchem Zahlenbereich sie liegt.
//
// Wenn die Zahl kleiner/ kleinergleich( <= ) ist als die delta_chance, dann schlägt es NICHT fehl => return true.
//
// Wenn die Zahl allerdings größer als die delta_chance ist, dann schlägt es fehl => return false.

bool Math::isCase( const size_t case_chance, const size_t base ) const {

	std::cout << " Base : " << base << std::endl;

	std::cout << " Current fail area : " << base - case_chance << std::endl;

	auto delta = g_pMath->randomNumber< size_t >(100);

	std::cout << " Delta : " << delta << std::endl;

	std::cout << "==================================" << std::endl;

	return ( delta <= ( base - case_chance ) ) ? true : false;
}

bool Math::SimulateRoll( const size_t win_area, const size_t base_area ) const {

	return ( win_area <= g_pMath->randomNumber< int >( base_area ) ) ? true : false;
}

void Math::NormalizeIt( Vector& angles ) {

	for ( int i = 0; i < 3; i++ ) {
		if ( angles[ i ] > 180.f )
			 angles[ i ] -= 360;

		if ( angles[ i ] < -180.f )
			 angles[ i ] += 360.f;
	}
}

void Math::ClampIt( Vector& angles ) {

	if ( angles.y > 180.0f )
		angles.y = 180.0f;
	else if ( angles.y < -180.0f )
		angles.y = -180.0f;

	if ( angles.x > 89.0f )
		angles.x = 89.0f;
	else if ( angles.x < -89.0f )
		angles.x = -89.0f;

	angles.z = 0;
}

bool Math::ClampAngles( Vector& angles ) {

	auto a = angles;
	NormalizeIt( a );
	ClampIt( a );

	if ( isnan( a.x ) || isinf( a.x ) ||
		 isnan (a.y ) || isinf( a.y ) ||
		 isnan( a.z ) || isinf( a.z ) ) {
		return false;
	}

	angles = a;
	return true;
}

Math* g_pMath = new Math;