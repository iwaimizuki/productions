#include"BaseScene.h"

/**
* @fn 　　SE
* @brief  1回のみ再生するSE
* @param  (std::list<std::unique_ptr<BaseScene>>& scene) 現在のシーン
* @return シーン遷移の可否
*/
int BaseScene::NextScene(std::list<std::unique_ptr<BaseScene>>& scene)
{
	int next = Scene::NEXT;

	for (auto&& childscene : scene)
	{
		if (childscene->Update() == childscene->NOW)
		{
			next = Scene::NOW;
			break;
		}
	}

	return next;
}
int BaseScene::Update()
{
	return NextScene(_child_scene);
}