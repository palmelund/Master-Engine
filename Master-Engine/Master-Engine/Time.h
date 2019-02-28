#pragma once
class Time
{
public:
	Time() = delete;
	~Time() = delete;

	static float DeltaTime();
	static long long StartupTime();
	static long long SystemTime();
	static long long FrameTime();
	static void Update();
	static void StartUp();
private:
	static float deltaTime;
	static long long startTime;
	static long long frameTime;
};

