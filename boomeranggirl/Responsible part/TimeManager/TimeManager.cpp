#include "TimeManager.h"
#include"../Data/WordsTable.h"

bool TimeManager::Initialize()
{
	_limitTime  = MAXTIME;
	_time       = 0.0f;

	_startTime  = 0.0f;

	return true;
}

int TimeManager::Update()
{
	if (GetGameEndFlag()) return 0;

	if (GetGameStartFlag()) _time += GameTimer.GetElapsedSecond();
	else _startTime += GameTimer.GetElapsedSecond();

	return 0;
}



