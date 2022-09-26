#include "InputSystem.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::GetInstance()
{
    static InputSystem system;
    return &system;
}

void InputSystem::addListener(InputListener* listener)
{
    m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
    m_set_listeners.erase(listener);
}

void InputSystem::update()
{
	//FOR RECOGNIZING MOUSE MOVE
	POINT current_mouse_pos = {};
	GetCursorPos(&current_mouse_pos);

	if(isFirstTime)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		isFirstTime = false;
	}

	if(current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		//THERE IS MOUSE MOVE EVENT
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);


	//FOR RECOGNIZING KEY INPUTS
    if(GetKeyboardState(m_keys_state))
    {
	    for(unsigned int i = 0; i < 256; i++)
	    {
			//KEY IS DOWN
		    if(m_keys_state[i] & 0x80)
		    {
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					if(i == VK_LBUTTON) //MOUSE LEFT IS DOWN
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON) //MOUSE RIGHT IS DOWN
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else //FOR KEY INPUT DOWN
					{
						(*it)->onKeyDown(i);
					}
					++it;
				}
		    }
			else //KEY IS UP
			{
				if(m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						if (i == VK_LBUTTON) //MOUSE LEFT IS DOWN
						{
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else if (i == VK_RBUTTON) //MOUSE RIGHT IS DOWN
						{
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else //FOR KEY INPUT UP
						{
							(*it)->onKeyUp(i);
							
						}
						++it;
					}
				}
			}

	    }

		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
    }
}

void InputSystem::setCursorPosition(const Point& pos)
{
	SetCursorPos(pos.m_x, pos.m_y);
}
