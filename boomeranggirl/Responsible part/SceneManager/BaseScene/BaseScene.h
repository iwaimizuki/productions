//! @file   BaseScene.h
//! @brief  シーンの基底クラス
//! @author 岩井瑞希
//! @date   2021/5/10

#pragma once

#include"../../../ESGLib.h"

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};

	virtual bool Initialize() = 0;
	virtual int Update();
	virtual void Draw2D() {};
	virtual void Draw3D() {};

	int NextScene(std::list<std::unique_ptr<BaseScene>>& scene);
	string GetNextScene() { return _next_scene;}
	enum Scene { NOW, NEXT };

protected:
	std::list<std::unique_ptr<BaseScene>> _child_scene;
	string _next_scene;

private:
};