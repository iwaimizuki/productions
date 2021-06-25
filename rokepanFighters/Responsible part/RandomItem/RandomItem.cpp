#include "RandomItem.h"
#include "../../Data/WordsTable.h"
#include "../../Players/PlayerBase.h"
#include "../../Scenes/Main/Camera/MainCamera.h"
#include "../../Managers/AudioManager/AudioManager.h"

RandomItem::RandomItem(Vector3 position, std::string name)
{
	_position = Vector3(0,9999,0);
	this->_position = position;
	_tag = name;
	_hit_box.reset(new HitBox());
	_i_player_data = new IPrayerData;
	_i_arm_data = new IArmData;
	_map_data = new IMapData;
	_effect_time = POWERUP_TIME;
	_player_speed = 0.05;
	_arm_speed = 0.1;
}

RandomItem::~RandomItem()
{
	delete _map_data;
	delete _i_arm_data;
	delete _i_player_data;
	_hit_box.reset();
}

bool RandomItem::Initialize()
{
	_speed = 0.1f;

	_map_data->SetMapData(_position,CharTag::ISITEM);

	_model = ResouceManager::Instance().LoadModelFile(_T("Item/Itembox_v2.X"));

	Material material;
	material.Diffuse = Color(0.0f, 0.0f, 0.0f);
	material.Ambient = Color(0.0f, 0.0f, 0.0f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);

	_model->SetMaterial(material);
	_model->SetScale(1.25f);

	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxPosition(_position);

	_hit_box->SetHitBox(1, 1, 1);

	return true;
}

int RandomItem::Update()
{
	if (_position.y <= 0)_position.y = 0;
	else _position.y -= _speed;

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name    = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjectsSquare(name))
		{
			std::string status_name = "";

			auto playeritem = _hit_box->GetHitBoxTag(name)->GetPlayerBase()->GetItemType();
			auto Items = playeritem.probability;
			auto Itemstype = playeritem.type;

			int Index = WeightedPick(Items, Items.size());
			status_name = Itemstype[Index];

			ItemEffectChange(status_name);
			ChangeStatus(status_name, name);

			Removeflag = true;
			_map_data->SetMapData(_position, CharTag::ITEM);
		}
	}

	_hit_box->SetHitBoxPosition(_position);

	return 0;
}

 /**
  * @fn     抽選
  * @brief  重み付けで抽選を行う
  * @param  (std::vector<int> pArray) 抽選する対象の配列
  * @param  (int Length) 配列のサイズ
  * @return 抽選した値
  */
int RandomItem::WeightedPick(std::vector<int> pArray, int Length) {

	int totalWeight = 0;
	int pick = 0;

	for (int i = 0; i < Length; i++) {
		totalWeight += pArray[i];
	}

	int rnd = rand() % totalWeight;

	for (int i = 0; i < Length; i++) 
	{
		if (rnd < pArray[i]) 
		{
			pick = i;
			break;
		}
		rnd -= pArray[i];
	}

	return pick;
}
/**
 * @fn     効果の選定
 * @brief  アイテムごとにステータスを変化させる
 * @param　アイテムのタグ
 */
void RandomItem::ItemEffectChange(std::string tag)
{
	if (tag == "")AudioManager::Instance().MultipleSe(POWERDOWN_SE);
	if (tag == ITEM_PLAYER_SPEEDUP)_player_speed = POWERUP_SPEED;
	if (tag == ITEM_ARM_SPEEDUP)_arm_speed = POWERUP_ARM;
	if (tag == ITEM_THUNDER)_player_speed = POWERDOWN_SPEED;
}
/**
 * @fn     効果の適応
 * @brief  プレイヤーのステータスを変化させる
 * @param　アイテムのタグ
 * @param　アイテムを取得したプレイヤーのタグ
 */
void RandomItem::ChangeStatus(std::string tag, std::string getplayer)
{
	if (tag == ITEM_THUNDER)
	{
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string playertag = PLAYER_TAG + std::to_string(i + 1);
			if (playertag == getplayer)
				continue;
			else
			{
				_effect_time = POWERDOWN_TIME;
				_hit_box->GetHitBoxTag(playertag)->GetPlayerBase()->GetItem(this, tag);
			}
		}
		MainCamera::Instance().TimeReset();

		return;
	}
	else if (tag != "")
	{
		_hit_box->GetHitBoxTag(getplayer)->GetPlayerBase()->GetItem(this, tag);
	}
}