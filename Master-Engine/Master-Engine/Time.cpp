#include "pch.h"
#include "Time.h"
#include <chrono>

float Time::deltaTime{};
long long Time::startTime{};
long long Time::frameTime{ };

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

float Time::DeltaTime()
{
	return deltaTime;
}

long long Time::StartupTime()
{
	return startTime;
}

long long Time::SystemTime()
{
	return NOW;
}

long long Time::FrameTime()
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
	frameTime = startTime;
}
