#pragma once

#include <Windows.h>

#ifndef CVARS_HEADER

#define CVARS_HEADER

typedef struct CVarBhop {

	bool enabled, enable_humanize;

	int fail_chance;

}CBhop;

typedef struct CVarTrigger {

	bool enabled, enable_delay, enable_random_delay, ignore_team, active{ false };

	int delay;

	int random_delay_maximum;

}CTrigger;

typedef struct CVarGlow {

	bool enabled;

	bool show_enemies;

	bool show_team;

	bool custom_mode, health_mode;

	float health_alpha;

	bool healthOccluded, healthUnoccluded;

	float friendRed, friendBlue, friendGreen, friendAlpha;

	bool friendUnoccluded, friendOccluded;

	float enemyRed, enemyBlue, enemyGreen, enemyAlpha;

	bool enemyUnoccluded, enemyOccluded;

	bool enable_bomb_glow;

	float bombRed, bombGreen, bombBlue, bombAlpha;


}CGlow;

typedef struct CVarRcs {

	bool enabled;

	int active_after_shots;

	bool enable_smooth;

	float smooth_x;

	float smooth_y;

	bool enable_velocity_mode;

	float lower_velocity;

}CRcs;

class CVars {

public:

	static CBhop* Bhop;

	static CTrigger* Trigger;

	static CGlow* Glow;
	
	static CRcs* Rcs;

	static void UpdateCvars();

protected:

private:

};

extern CVars* g_pCvars;

#endif // !CVARS_HEADER