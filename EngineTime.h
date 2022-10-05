#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
	static void setTimeScale(double timescale);

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};             // copy constructor is private
	EngineTime& operator=(EngineTime const&) {};  // assignment operator is private*/

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;
	double timescale = 1.0f;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
};