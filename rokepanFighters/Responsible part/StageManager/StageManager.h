//! @file   StageManager.h
//! @brief  ステージの表示物の管理
//! @author 岩井瑞希
//! @date   2021/12/1

#pragma once

#include"../../Managers/ManagerBase.h"
#include"../../Stage/StageBase.h"

class HitBox;
class ItemCounter;

class StageManager : public ManagerBase
{
public:
	StageManager() {};
	~StageManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override{};

private:
	void ItemSet();
	void FallBlock();
	void FallItem();

	ItemCounter*                _itemcounter;

	std::list<StageBase*>	    _stages;
	std::vector<cstring>		_mapdate; //! マップデータの読み込み

	MEDIA                       _bg_movie;

	int                         _random_fall_time = 0;
	std::vector<Vector3>        _random_block_position;
	bool                        _fall_flag = false;
};