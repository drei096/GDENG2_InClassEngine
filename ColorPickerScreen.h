#pragma once
#include "AUIScreen.h"

class ColorPickerScreen : public AUIScreen
{
public:
	ColorPickerScreen(std::string name);
	void drawUI() override;

private:
	float my_color[4];
};

