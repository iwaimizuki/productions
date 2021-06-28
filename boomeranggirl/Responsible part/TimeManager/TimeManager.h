//! @file   TimeManager.h
//! @brief  �^�C���̊Ǘ�
//! @author ��䐐��
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
	
	//�Q�[���J�n���牽�b�o�������̎擾
	float GetAdvancingTime(){ return _time; }
	//�c�莞�Ԃ̎擾
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

