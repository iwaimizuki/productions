//! @file   SmallScore.h
//! @brief  1位以外のスコア表示
//! @author 岩井瑞希
//! @date   2021/2/8

#pragma once
#include"../ObjectBase.h"
class SmallScore : public ObjectBase
{
public:
	SmallScore();
	~SmallScore();
	bool Initialize()override;
	int Update()override;
	void Draw2D()override;
private:
	SPRITE          _score_sprite;
	SPRITE          _robot_fece;

	std::vector<int>_player_rectwh;
	int _smallacorenum = 2;

	RectWH          _rect = RectWH(0, 0, 64, 64);

	const Vector3   _robot_fece_basepos = Vector3(850, 105, 10000);
	const Vector3   _score_basepos = Vector3(1012, 155, 0);
	const Vector3   _move_vector3  = Vector3(32, 210,0);

	float           _acceleration[PLAYER_COUNT_MAX - 1];
	float           _scale[PLAYER_COUNT_MAX - 1];

	const float     _smallspeed = 0.5;
	const float     _minscale = 0.5;
	const float     _displaysclae = 5.0;
	const float     _robot_fece_move_y = 205;
};