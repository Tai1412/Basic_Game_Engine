#include "timerFps.h"
#include "parentFunction.h"
timerFps::timerFps()
{
	//set constructor
	startTick = 0;
	pauseTick = 0;
	isPause = false;
	isStart = false;
}


timerFps::~timerFps()
{
}
void timerFps::startRun()
{
	isStart = true;
	isPause = false;
	startTick = SDL_GetTicks();//number of milisec

}
void timerFps::stopRun()
{
	isPause = false;
	isStart = false;
}
void timerFps::pause()
{
	if (isStart == true && isPause == false)
	{
		isPause = true;
		pauseTick = SDL_GetTicks() - startTick;
	}

}
void timerFps::unpause()
{
	if (isPause == true)
	{
		isPause = false;
		startTick = SDL_GetTicks() - pauseTick;
		pauseTick = 0;
	}
}

int timerFps::getTick()
{
	if (isStart == true)
	{
		if (isPause == true)
		{
			return pauseTick;
		}
		else
		{
			return SDL_GetTicks() - startTick;
		}
	}
	return 0;
}
bool timerFps::isStartF()
{
	return isStart;
}
bool timerFps::isPauseF()
{
	return isPause;
}
