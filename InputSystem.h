#pragma once

#include "InputListener.h"
#include <unordered_set>
#include <Windows.h>
#include "Point.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

public:
	static InputSystem* GetInstance();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void update();

	void setCursorPosition(const Point& pos);

private:
	std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

	Point m_old_mouse_pos;
	bool isFirstTime = true;
};

