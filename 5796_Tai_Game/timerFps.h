#pragma once
#ifndef TIMER_FPS_H_
#define TIMER_FPS_H_
class timerFps
{
public:
	timerFps();
	~timerFps();

	void startRun();
	void stopRun();
	void pause();
	void unpause();

	int getTick();
	bool isStartF();//isStartFunction
	bool isPauseF();//isPauseFunction
private:
	int startTick;
	int pauseTick;
	bool isPause;
	bool isStart;
};



#endif

