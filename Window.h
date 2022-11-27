#pragma once
#define NOMINMAX
#include <Windows.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"



class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	bool broadcast();
	//Release the window
	bool release();
	bool isRunning();

	//EVENTS
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();
	virtual void OnFocus();
	virtual void OnKillFocus();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	HWND getHWND();

	~Window();

public:
	static int WIDTH;
	static int HEIGHT;

protected:
	HWND m_hwnd;
	bool m_isRunning;
};

