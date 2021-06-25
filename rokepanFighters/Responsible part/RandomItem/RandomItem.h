//! @file   RandomItem.h
//! @brief  ランダムなアイテム効果を適応
//! @author 岩井瑞希
//! @date   2021/2/1
#pragma once

#include "../Itembase.hpp"

class RandomItem : public ItemBase
{
public:
	RandomItem(Vector3 position, std::string name);
	~RandomItem();

	bool Initialize() override;
	void ItemEffect(std::string name) override { _i_player_data->SetSpeed(name, _i_player_data->GetSpeed(name) + _speed); }
	int Update() override;

private:
	int WeightedPick(std::vector<int> pArray, int Length);
	void ChangeStatus(std::string tag, std::string getplayer);
	void ItemEffectChange(std::string tag);
	float _rotation;
	string _tag = "";
};