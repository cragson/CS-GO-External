#pragma once

#ifndef LOCALPLAYER_HEADER

#define LOCALPLAYER_HEADER

#include "Vektor.h"

class LocalPlayer {

public:

	std::uintptr_t getLocalplayer() const;

	std::uintptr_t getPlayerInCrosshair() const;

	int getHealth() const;

	int getTeam() const;

	int getFlags() const;

	int getEntityListIndex() const;

	int getShotsfired() const;

	bool IsOnGround() const;

	bool IsShooting() const;

	void doJump();

	void doShoot();

	void setViewAngles( const Vector &Angles );

	Vector getViewAngles() const;

	Vector getAimPunch() const;

	Vector getPos() const;

	Vector getEyePos() const;

	float getSpeed() const;

	int getCurrentItem() const;

protected:

private:

};

extern LocalPlayer* g_pLocalPlayer;

#endif // !LOCALPLAYER_HEADER