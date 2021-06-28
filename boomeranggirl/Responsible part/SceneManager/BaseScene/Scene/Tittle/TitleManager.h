//! @file   BaseScene.h
//! @brief  シーンの基底クラス
//! @author 岩井瑞希
//! @date   2021/5/10

#pragma once

#include"../../BaseScene.h"

class TitleManager:public BaseScene
{
public:
	TitleManager();
	~TitleManager() {};
	bool Initialize() override;
	void Draw2D() override;
private:
};