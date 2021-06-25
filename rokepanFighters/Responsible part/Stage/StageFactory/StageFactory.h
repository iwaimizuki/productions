//! @file   ResultScene.h
//! @brief  ステージ生成
//! @author 岩井瑞希
//! @date   2021/1/16

#pragma once
#include"../../../ESGLib.h"
class StageBase;

class StageFactory
{
public:
	StageFactory() {};
	~StageFactory() {};

	StageBase* Create(std::string tag, Vector3 position);
private:
	StageBase* CreateProduct(std::string tag);
};