#include"StageFactory.h"
#include"../StageBase.h"
#include"../../Data/MyAlgorithm.h"
#include"../../Stage/Stage_1/Block/Block.h"
#include"../../Stage/Stage_1/Indestructible/Indestructible.h"
#include"../../Stage/Stage_1/Metal/Metal.h"

/**
 * @fn 　　Factory
 * @brief  ステージの生成と初期化
 * @param  (std::string tag) 生成するステージのタグ
 * @param  (Vector3 position) 生成する座標
 * @return StageBaseの派生クラス
 */
StageBase* StageFactory::Create(std::string tag, Vector3 position)
{
	StageBase* stagebase = CreateProduct(tag);

	stagebase->SetPosition(position);
	stagebase->Initialize();

	return stagebase;
}

/**
 * @fn 　　Factory
 * @brief  タグごとに派生クラスを返す
 * @param  (std::string tag)生成するステージのタグ
 * @return StageBaseの派生クラス
 */
StageBase* StageFactory::CreateProduct(std::string tag)
{
	string stagename = GetTag(tag);

	if (stagename == BLOCK) { return new Block(tag); }

	if (stagename == INDESTRUCTIBIEPILLAR) { return new Indestructible(tag); }

	if (stagename == STAGE) { return new Stage(); }

	ASSERT(FALSE && "nostagetag");
}


