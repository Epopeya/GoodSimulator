#pragma once
#include <Arduino.h>

class Timer
{
public:
	Timer(int time)
		: time(time)
		, last_time(millis()){};
	int time;
	bool primed()
	{
		unsigned long current_time = millis();
		if ((current_time - last_time) > time)
		{
			last_time = current_time;
			return true;
		}
		else { return false; }
	};

private:
	unsigned long last_time;
};
