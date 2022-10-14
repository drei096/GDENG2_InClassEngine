#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{
		
	}

	~InputListener()
	{
		
	}

	//PURE VIRTUAL FUNCTIONS FOR KEYBOARD
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//PURE VIRTUAL FUNCTIONS FOR MOUSE
	virtual void onMouseMove(const Point& mouse_pos) = 0;
	virtual void onLeftMouseDown(const Point& mouse_pos) = 0;
	virtual void onLeftMouseUp(const Point& mouse_pos) = 0;
	virtual void onRightMouseDown(const Point& mouse_pos) = 0;
	virtual void onRightMouseUp(const Point& mouse_pos) = 0;

};