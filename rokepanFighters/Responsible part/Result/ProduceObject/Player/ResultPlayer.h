//! @file   ResultManager.h
//! @brief  プレイヤーモデルの表示
//! @author 岩井瑞希
//! @date   2021/2/7

#pragma once
#include"../ObjectBase.h"

class ParticleSystem;

class ResultPlayer : public ObjectBase
{
public:
	ResultPlayer();
	~ResultPlayer();
	bool Initialize()override;
	int Update()override;
	void Draw3D()override;
private:
	enum VictoryAnimation{NUMBER = 5};

	EFFECT                _shader;

	double _animation_count = 0;
	ANIMATIONMODEL        _player_model;
	SPRITE                _texture;

	std::unique_ptr<ParticleSystem>_effect;
	float                 _effect_time = 0.0f;

	const float           _effecttimemax = 160;
};