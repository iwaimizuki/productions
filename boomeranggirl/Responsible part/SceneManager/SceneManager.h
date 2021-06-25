//! @file   SceneManager.h
//! @brief  ƒV[ƒ“‚ÌŠÇ—
//! @author ŠâˆäŠó
//! @date   2021/5/10

#pragma once

#include"BaseScene/BaseScene.h"
#include "../../ESGLib.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager() {};

	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	};

	bool Initialize(string scene);
	int Update();
	void Draw();

	void ChangeScene(string scene);

	void AddCombo();
	int MaximumCombo();

	void SetCombo(int combo) { _combo = combo; }
	int GetCombo() { return _combo; }

	void AddDeathEnemy() { ++_enemy_count; }
	void SetDeathEnemy(int count) { _enemy_count = count; }
	int GetDeathEnemy() { return _enemy_count; }

private:
	std::unique_ptr<BaseScene> _scene;

	int   _combo = 0;
	int   _max_combo = 0;

	float _combo_reset_time = 0;
	const float COMBORESETTIMEMAX = 3.0f;

	int   _enemy_count = 0;
};