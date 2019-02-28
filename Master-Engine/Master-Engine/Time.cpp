#include "pch.h"
#include "Time.h"
#include <chrono>

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

float Time::DeltaTime()
{
	return deltaTime;
}

long Time::StartupTime()
{
	return startTime;
}

long Time::SystemTime()
{
	return NOW;
}

long Time::FrameTime()
{
	return frameTime;
}

void Time::Update()
{
	const auto now = NOW;

	deltaTime = static_cast<float>(now - frameTime) / 1000;
	frameTime = now;
}

void Time::StartUp()
{
	startTime = NOW;
}
