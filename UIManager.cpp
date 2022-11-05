#include "UIManager.h"

#include "GraphicsEngine.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::GetInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::Release()
{
	delete sharedInstance;
}

void UIManager::drawAllUIScreens()
{
	//START IMGUI FRAME
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for(int i = 0; i < this->_uiScreenList.size(); i++)
	{
		if(this->_uiScreenList[i]->toShow == true)
			this->_uiScreenList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::uiScreenList UIManager::getUIList()
{
	return _uiScreenList;
}

UIManager::uiScreenHashTable UIManager::getUIHashTable()
{
	return uiTable;
}

UIManager::UIManager(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::GetInstance()->getRenderingSystem()->getD3D11Device(), GraphicsEngine::GetInstance()->getRenderingSystem()->getD3D11DeviceContext());

	ImGui::StyleColorsDark();

	Credits_UI* credits_uiScreen = new Credits_UI("creditsUI");
	this->uiTable[UINames::CREDITS_SCREEN] = credits_uiScreen;
	this->_uiScreenList.push_back(credits_uiScreen);

	MenuToolbar* menuToolbar = new MenuToolbar("menuToolbar");
	this->uiTable[UINames::MENU_SCREEN] = menuToolbar;
	this->_uiScreenList.push_back(menuToolbar);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen("cpScreen");
	this->uiTable[UINames::COLOR_PICKER_SCREEN] = colorPickerScreen;
	this->_uiScreenList.push_back(colorPickerScreen);
}

UIManager::~UIManager()
{
}


