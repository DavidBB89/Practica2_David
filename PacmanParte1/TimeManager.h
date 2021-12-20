#pragma once
#include <chrono>

class TimeManager
{
	std::chrono::high_resolution_clock::time_point start
		= std::chrono::high_resolution_clock::now();
public:
	int frameCount = 0;
	float deltaTime = 0;
	float time = 0;
	static TimeManager& getInstance();
	void NextFrame();
};

