#include "MenuToolbar.h"

#include "UIManager.h"

MenuToolbar::MenuToolbar(std::string name) : AUIScreen(name)
{
	toShow = true;
}

void MenuToolbar::drawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("About"))
		{
			ImGui::MenuItem("Credits", NULL, &UIManager::GetInstance()->getUIHashTable()[UIManager::UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		ImGui::MenuItem("Color Picker", NULL, &UIManager::GetInstance()->getUIHashTable()[UIManager::UINames::COLOR_PICKER_SCREEN]->toShow);


		ImGui::EndMainMenuBar();
	}
}
