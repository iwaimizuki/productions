//! @file   ResultScene.h
//! @brief  リザルトで表示する表示物の管理
//! @author 岩井瑞希
//! @date   2021/2/7

#pragma once

#include "../BaseScene.h"
#include"../../Data/IData.h"
#include"ProduceObject/ObjectBase.h"
class ParticleSystem;

class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	bool Initialize() override;
	int  Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:
	std::list<ObjectBase*>_object;
	SPRITE                _background;
	SPRITE                _score_sprite;
	Vector3               _background_position;
};