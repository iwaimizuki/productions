//! @file   TimeManager.h
//! @brief  タイムの管理
//! @author 岩井瑞希
//! @date   2021/5/21

#pragma once

#include "../../ESGLib.h"

class TimeManager
{
public:
	TimeManager() {};
	~TimeManager() {};

	static TimeManager& Instance() {
		static TimeManager instance;
		return instance;
	};

	bool Initialize();
	int Update();
	
	//ゲーム開始から何秒経ったかの取得
	float GetAdvancingTime(){ return _time; }
	//残り時間の取得
	float GetLimitTime(){ return _limitTime - _time; }

	bool GetGameStartFlag() { return _startTime >= STARTTIMEMAX; }
	bool GetGameEndFlag() { return _time >= _limitTime; }

	void AddTime(float count) { _limitTime += count; }

private:
	TimeManager(const TimeManager&) = delete;
	void operator=(const TimeManager&) = delete;

	const float STARTTIMEMAX = 4;

	float _limitTime = STARTTIMEMAX;
	float _time = 0;

	float _startTime = 0;
};

