#include"BaseScene.h"

/**
* @fn �@�@SE
* @brief  1��̂ݍĐ�����SE
* @param  (std::list<std::unique_ptr<BaseScene>>& scene) ���݂̃V�[��
* @return �V�[���J�ڂ̉�
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