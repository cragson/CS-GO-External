#pragma once

#include <cstdint>

class CClient {

public:

	std::uintptr_t getEnginePointer() const;

	std::uintptr_t getGlowObjectManager() const;

	void SimulateLeftMouseClick() const;

protected:

private:

};

extern CClient* g_pCClient;