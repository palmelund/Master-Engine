#pragma once
class Time
{
public:
	Time() = delete;
	~Time() = delete;

	static float DeltaTime();
	static long StartupTime();
	static long SystemTime();
	static long FrameTime();
	static void Update();
	static void StartUp();
private:
	static float deltaTime;
	static long startTime;
	static long frameTime;
};

