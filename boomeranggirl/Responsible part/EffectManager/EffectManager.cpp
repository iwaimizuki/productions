#include "EffectManager.h"
#include"../Data/MyAlgorithm.h"

bool EffectManager::Initialize()
{
	_effect.insert(std::make_pair(EffectTag::HIT,
		std::move(SetEffectInitialize("Effect/hit_0528/hit.efk", 0.5f, 0.1f))));

	_effect.insert(std::make_pair(EffectTag::EXPLOSION,
		std::move(SetEffectInitialize("Effect/explosion/explosion.efk", 0.5f, 0.3f))));

	_effect.insert(std::make_pair(EffectTag::SMALLEXPLOSION,
		std::move(SetEffectInitialize("Effect/explosion/explosion.efk", 1.0f, 0.1f))));

	return true;
}

/**
* @fn �@�@Effect
* @brief  �G�t�F�N�g���Đ�����
* @param  (string tag) �Đ�����^�O
* @param  (Vector3 pos) �G�t�F�N�g�̍��W
*/
void EffectManager::Create(string tag, Vector3 pos)
{
	_effect.at(tag)->Play();
	_effect.at(tag)->SetPosition(pos);
	_effect.at(tag)->Draw();
}

/**
* @fn �@�@Effect
* @brief  �G�t�F�N�g�̏�����
* @param  (string filename) �t�@�C����
* @param  (float speed) �G�t�F�N�g�̍Đ����x
* @param  (float scale) �G�t�F�N�g�̑傫��
* @return �ǂݍ��񂾃G�t�F�N�g��Ԃ�
*/
ParticleSystem* EffectManager::SetEffectInitialize(string filename, float speed, float scale)
{
	auto&& particle = Effekseer.CreateEffectFromFile(ConvertStringFileName(filename));
	ParticleSystem* effect = new ParticleSystem;

	effect->RegisterParticle(particle);
	effect->SetSpeed(speed);
	effect->SetScale(scale);

	return effect;
}
