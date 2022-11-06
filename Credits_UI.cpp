#include "Credits_UI.h"

Credits_UI::Credits_UI(std::string name) : AUIScreen(name)
{
	toShow = false;
	//
}

void Credits_UI::drawUI()
{
	//DRAW HERE
	

	ImGui::Begin("Credits");
	ImGui::Text("GDENG-2_InClassEngine v0.1\n");
	ImGui::Text("Created by Aldrey D. Gaurana - GDENG-2 X22\n");

	Texture* m_wood_tex = GraphicsEngine::GetInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\iC.png");
	ImGui::Image((void*)m_wood_tex->getShaderResourceView(), ImVec2(256, 256));

	ImGui::Text("Acknowledgements:\n");
	ImGui::Text(" - Sir Del Gallego for the course\n");
	ImGui::Text(" - PardCode (https://www.youtube.com/c/PardCode)\n");
	ImGui::Text(" - RedBull (https://www.redbull.com/ph-en/)\n");
	ImGui::Text(" - Google (https://google.com)\n");
	ImGui::Text(" - Stack Overflow (https://stackoverflow.com)\n");
	ImGui::Text(" - IMGUI (https://github.com/ocornut/imgui)\n\n");

	if(ImGui::Button("Close"))
	{
		toShow = false;
	}
	

	ImGui::End();
}
