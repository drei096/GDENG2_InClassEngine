#pragma once

#include "AUIScreen.h"

class PARCMLoaderScreen : public AUIScreen
{
public:
	PARCMLoaderScreen(std::string name);
	void drawUI() override;
};

