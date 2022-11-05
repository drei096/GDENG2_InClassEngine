#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Window.h"
#include "AUIScreen.h"
#include "Credits_UI.h"
#include "MenuToolbar.h"
#include "ColorPickerScreen.h"


class UIManager
{
public:
	enum UINames
	{
		PROFILER_SCREEN,
		MENU_SCREEN,
		INSPECTOR_SCREEN,
		HIERARCHY_SCREEN,
		CREDITS_SCREEN,
		COLOR_PICKER_SCREEN,
	};

	typedef std::vector<AUIScreen*> uiScreenList;
	typedef std::unordered_map<UINames, AUIScreen*> uiScreenHashTable;

public:
	static UIManager* GetInstance();
	static void initialize(HWND hwnd);
	static void Release();

	void drawAllUIScreens();
	uiScreenList getUIList();
	uiScreenHashTable getUIHashTable();

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;

private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;


private:
	uiScreenList _uiScreenList;
	uiScreenHashTable uiTable;
};

