#pragma once

#include "Bhop.h"

#include "Trigger.h"

#include "Glow.h"

#include "RCS.h"

#ifndef  HANDLER_HEADER

#define HANDLER_HEADER

class Handler {

public:

	static Bhop* bhop;

	static Trigger* trigger;

	static Glow* glow;

	static RCS* rcs;

protected:

private:

};

#endif // ! HANDLER_HEADER