#include "MenuToolbar.h"

#include "PrimitiveManager.h"
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

		if(ImGui::BeginMenu("Create"))
		{
			if(ImGui::MenuItem("Create Cube", NULL))
			{
				PrimitiveManager::GetInstance()->createObject(PrimitiveManager::CUBE, ShaderTypes::ALBEDO);
			}
			if (ImGui::MenuItem("Create Textured Cube", NULL))
			{
				PrimitiveManager::GetInstance()->createObject(PrimitiveManager::TEXTURED_CUBE, ShaderTypes::FLAT_TEXTURED);
			}
			if (ImGui::MenuItem("Create Plane", NULL))
			{
				PrimitiveManager::GetInstance()->createObject(PrimitiveManager::PLANE, ShaderTypes::ALBEDO);
			}
			if (ImGui::MenuItem("Create Physics Cube", NULL))
			{
				PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::PHYSICS_CUBE, Vector3D(0.0f, 4.0f, 0.0f), ShaderTypes::ALBEDO);
			}
			if (ImGui::MenuItem("Create Physics Plane", NULL))
			{
				PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::PHYSICS_PLANE, Vector3D(0.0f, 0.0f, 0.0f), ShaderTypes::ALBEDO);
			}
			if (ImGui::MenuItem("Create 20 Physics Cubes", NULL))
			{
				for(int i = 0; i < 20; i++)
					PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::PHYSICS_CUBE, Vector3D(0.0f, 10.0f, 0.0f), ShaderTypes::ALBEDO);
			}
			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}
}
