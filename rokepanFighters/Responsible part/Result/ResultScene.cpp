#include"ResultScene.h"
#include"ProduceObject/Score/SmallScore.h"
#include"ProduceObject/Score/FirstScore.h"
#include"ProduceObject/Player/ResultPlayer.h"
#include"../../Data/WordsTable.h"
#include"../../Managers/ResouceManager/ResouceManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"
ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	SceneManager::Instance().ClearPlayerTexture();
}

/*
* @fn リザルトの初期化
*/
bool ResultScene::Initialize()
{
	//最初に描画するオブジェクト
	_object.push_back(new SmallScore);
	(*_object.begin())->Initialize();

	//file
	_background	= ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/ground.png"));

	//背景の座標
	_background_position = Vector3(0, 0, 10000);
	return true;
}

/*
* @fn リザルトの更新
*/
int ResultScene::Update()
{
	AudioManager::Instance().BgmPlay(RESULT);

	ObjectBase* objectclass[] = {new FirstScore,new ResultPlayer};
	int count = 0;

	for (auto&& ob : _object)
	{
		if (ob->Update() == ObjectBase::Action::END && !ob->GetState())
		{
			ob->SetState(true);
			_object.push_back(objectclass[count]);
			(*_object.rbegin())->Initialize();
		}
		count++;
	}

	return 0;
}

/*
* @fn リザルトの2D描画
*/
void ResultScene::Draw2D()
{
	SpriteBatch.Draw(*_background,_background_position);

	for (auto ob : _object)
	{
		ob->Draw2D();
	}
}
/*
* @fn リザルトの3D描画
*/
void ResultScene::Draw3D()
{
	for (auto ob : _object)
	{
		ob->Draw3D();
	}
}
