#include "Window.h"
#include "EngineTime.h"

//Window* window=nullptr;
int Window::HEIGHT = 768;
int Window::WIDTH = 1024;

Window::Window()
{

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//GetWindowLong(hwnd,)
	switch (msg)
	{
	case WM_CREATE:
	{
		// Event fired when the window is created
		// collected here..
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->OnCreate();
		break;
	}

	case WM_SETFOCUS:
	{
		// Event fired when the window is on focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		// Event fired when the window loses focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnKillFocus();
		break;
	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}


	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}


bool Window::init()
{


	//Setting up WNDCLASSEX object
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
		return false;

	/*if (!window)
		window = this;*/

		//Creation of the window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, NULL, NULL, this);

	//if the creation fail return false
	if (!m_hwnd)
		return false;

	//show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);




	//set this flag to true to indicate that the window is initialized and running
	m_isRunning = true;

	EngineTime::initialize();

	return true;
}

bool Window::broadcast()
{
	EngineTime::LogFrameStart();

	MSG msg;

	this->OnUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	

	Sleep(1);

	EngineTime::LogFrameEnd();

	return true;
}


bool Window::release()
{
	//Destroy the window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::isRunning()
{
	return m_isRunning;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	m_isRunning = false;
}

void Window::OnFocus()
{
}

void Window::OnKillFocus()
{
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

Window::~Window()
{
}