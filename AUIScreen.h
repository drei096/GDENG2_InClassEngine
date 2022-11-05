#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>
#include <iostream>

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string getName();

public:
	virtual void drawUI() = 0;

public:
	bool toShow = true;

protected:
	std::string name;

protected:
	friend class UIManager;
};

