#include"StageFactory.h"
#include"../StageBase.h"
#include"../../Data/MyAlgorithm.h"
#include"../../Stage/Stage_1/Block/Block.h"
#include"../../Stage/Stage_1/Indestructible/Indestructible.h"
#include"../../Stage/Stage_1/Metal/Metal.h"

/**
 * @fn �@�@Factory
 * @brief  �X�e�[�W�̐����Ə�����
 * @param  (std::string tag) ��������X�e�[�W�̃^�O
 * @param  (Vector3 position) ����������W
 * @return StageBase�̔h���N���X
 */
StageBase* StageFactory::Create(std::string tag, Vector3 position)
{
	StageBase* stagebase = CreateProduct(tag);

	stagebase->SetPosition(position);
	stagebase->Initialize();

	return stagebase;
}

/**
 * @fn �@�@Factory
 * @brief  �^�O���Ƃɔh���N���X��Ԃ�
 * @param  (std::string tag)��������X�e�[�W�̃^�O
 * @return StageBase�̔h���N���X
 */
StageBase* StageFactory::CreateProduct(std::string tag)
{
	string stagename = GetTag(tag);

	if (stagename == BLOCK) { return new Block(tag); }

	if (stagename == INDESTRUCTIBIEPILLAR) { return new Indestructible(tag); }

	if (stagename == STAGE) { return new Stage(); }

	ASSERT(FALSE && "nostagetag");
}


