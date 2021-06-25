/**
 * @file Block.h
 * @brief ステージベースを継承した破壊できるブロックのクラス
 * @author 岩井瑞希
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include"../../../Item/ItemCounter/ItemCounter.h"
#include"../../../Data/WordsTable.h"
#include "../../../Data/IData.h"

class ParticleSystem;

class Block :public StageBase
{
public:
	Block(std::string tag);
	~Block();
	bool Initialize() override;
	int Update() override;
private:
	int IsDead();
	std::unique_ptr<IMapData>       _map_data;
	std::unique_ptr<ParticleSystem> _effect;
	std::unique_ptr<IArmData>		_i_arm_data;
	std::unique_ptr<ParticleSystem> _aura_effect;
	const int						_arm_distance = 2.5f;
	int                             _speed;
};