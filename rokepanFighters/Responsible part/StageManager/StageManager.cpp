#include "StageManager.h"
#include <fstream>
#include <cstdio>
#include "../../Data/IData.h"
#include "../../Data/WordsTable.h"
#include "../../Data/StructList.h"
#include "../ResouceManager/ResouceManager.h"
#include "../SceneManager/SceneManager.h"
#include "../TimeManager/Time.h"
#include "../../Data/MyAlgorithm.h"
#include"../../Item/ItemCounter/ItemCounter.h"
#include"../../Stage/StageFactory/StageFactory.h"

StageManager::~StageManager()
{
	for (auto stage : _stages)
	{
		delete stage;
	}
}

bool StageManager::Initialize()
{
	MediaManager.Attach(GraphicsDevice);

	_bg_movie  = ResouceManager::Instance().LordMediaFile(_T("MapSprite/bg.wmv"));
	_bg_movie->Play();

	FILE* fp = fopen("MapSprite/Stage/map_A.csv", "r");
	char lordchar[CHAR_MAX + 1];

	while (fgets(lordchar, sizeof lordchar - 1, fp) != NULL)
	{
		if (lordchar[strlen(lordchar) - 1] == '\n')
			lordchar[strlen(lordchar) - 1] = '\0';
		_mapdate.push_back(lordchar);
	}

	//カンマを探索してカンマを消す
	for (int z = 0; z < _mapdate.size(); z++)
	{
		for (int x = 0; x < _mapdate[z].size(); x++)
		{
			if (_mapdate[z][x] == ',')
				_mapdate[z].erase(_mapdate[z].begin() + x);
		}
	}

	fclose(fp);

	unique_ptr<IPrayerData> iplayer_data = make_unique<IPrayerData>();
	unique_ptr<IMapData> imap_data = make_unique<IMapData>();
	unique_ptr<StageFactory> factory = make_unique<StageFactory>();

	int player_num = 1;
	int count = 0;

	for (int z = 0; z < _mapdate.size(); z++)
	{
		for (int x = 0; x < _mapdate[z].size(); x++)
		{
			std::string tag = std::to_string(count);
			switch (_mapdate[z][x]) {
			case CharTag::BLOCK:
				tag = BLOCK + tag;
				_stages.push_back(factory->Create(BLOCK + std::to_string(count), Vector3(x, 0, -z)));
				count++;
				break;
			case CharTag::PLAYER:
				tag = PLAYER_TAG + std::to_string(player_num);
				iplayer_data->SetPosition(tag, Vector3(x, 0, -z));
				imap_data->SetRespawnPosition(tag, Vector3(x, 0, -z));
				player_num++;
				break;
			case CharTag::ITEM:
				_random_block_position.push_back(Vector3(x, 0, -z));
				break;
			}
		}
	}

	imap_data->SetData(_mapdate);
	_stages.push_back(factory->Create(STAGE + std::to_string(0), (Vector3(7, 0, -6))));

	return true;
}

int StageManager::Update()
{
	FallBlock();
	FallItem();

	auto itr = _stages.begin();

	while (itr != _stages.end())
	{
		if ((*itr)->Update() == (*itr)->LIVING)itr++;
		else itr = _stages.erase(itr);
	}

	return 0;
}

void StageManager::Draw2D()
{
	if (_bg_movie->IsComplete())_bg_movie->Replay();

	SpriteBatch.Draw(*_bg_movie, Vector3(0, 0, 10000),1.0f);
}

void StageManager::Draw3D()
{
	//読み込んだブロックの数だけ描画する
	for (auto stage : _stages)
	{
		stage->Draw3D();
	}
}
/**
 * @fn 　　アイテム設置
 * @brief  空いているマップデータを探索してランダムにアイテム設置
 */
void StageManager::ItemSet()
{
	//!使われていないアイテムの座標の探索
	std::vector<Vector3>random_item_pos;
	for (int i = 0; i < _random_block_position.size(); i++)
	{
		int x = _random_block_position[i].x;
		int z = -_random_block_position[i].z;

		if (_mapdate[z][x] == CharTag::ITEM)random_item_pos.push_back(_random_block_position[i]);
	}

	if (random_item_pos.size() == 0) return;

	//!保存した座標をシャッフルする
	for (int i = 0; i < random_item_pos.size(); ++i)
	{
		const auto random_index = MathHelper_Random(random_item_pos.size() - 1);
		const auto work = random_item_pos.at(random_index);
		random_item_pos.at(random_index) = random_item_pos.at(i);
		random_item_pos.at(i) = work;
	}

	float _item_pos_y = 10;

	for (int i = 0; i < MathHelper_Random(1, IETM_COUNT); i++)
	{
		random_item_pos[i].y = _item_pos_y;
		ItemCounter::SetItem(RANDOM_ITEM, random_item_pos[i], 0);
		if (random_item_pos.size() == 1) return;
	}
}

/**
 * @fn 　　ブロック設置
 * @brief  時間指定でブロックを設置する
 */
void StageManager::FallBlock()
{
	unique_ptr<StageFactory> factory = make_unique<StageFactory>();

	if (!_fall_flag && TimeManager::Instance().GetTimeLeft() <= FALL_BLOCK_TIME)
	{
		for (int i = 1; i < FALL_BLOCK_COUNT; i++)
		{
			_stages.push_back(factory->Create(INDESTRUCTIBIEPILLAR + std::to_string(i), 
				FALLBLOCKPOSITION + Vector3(0, i, -i)));
		}
		_fall_flag = true;
	}
}

/**
 * @fn 　　アイテム設置
 * @brief  一定時間でアイテムを生成
 */
void StageManager::FallItem()
{
	_random_fall_time++;]

	if (IntWrap(_random_fall_time, 0, ITEM_INTERVAL) == 0)
	{
		unique_ptr<IMapData> mapdata = make_unique<IMapData>();
		_mapdate = mapdata->GetData();

		ItemSet();
	}
}