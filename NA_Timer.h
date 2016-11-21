#pragma once

class NA_Timer
{
private:
	unsigned int duration;
	unsigned int start;
public:
	NA_Timer(void);
	explicit NA_Timer(int d);
	~NA_Timer(void);
	void setDuration(int d);
	bool hasElapsed();
	void restart();
	void wait(); //pause until timer elapses
};

