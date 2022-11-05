#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen(std::string name) : AUIScreen(name)
{
	toShow = false;
}

void ColorPickerScreen::drawUI()
{
	ImGui::Begin("Color");
	ImGui::ColorEdit4("Color", my_color);
	if (ImGui::Button("Close"))
	{
		toShow = false;
	}


	ImGui::End();
}
