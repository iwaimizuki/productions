//! @file   FirstScore.h
//! @brief  1位のスコア表示
//! @author 岩井瑞希
//! @date   2021/2/8

#pragma once
#include"../ObjectBase.h"
class FirstScore : public ObjectBase
{
public:
	friend class ResultPlayer;
	FirstScore();
	~FirstScore();
	bool Initialize()override;
	int Update()override;
	void Draw2D()override;
private:
	//スコア部分
	SPRITE _score_sprite;
	RectWH _rect[SCORE::DIGITS];

	const Vector3 _centerpos = Vector3(32, 32, 0);
	const Vector3 _basepos = Vector3(150, 600, 0);
	const float _scale = 1.5f;
	const float _move_x = 96;

	//回転
	int _rotation_time = 0;

	const int _rotation_max_time = 576;
	const int _rotation_speed = 10;
};