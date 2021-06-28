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
* @fn 　　Effect
* @brief  エフェクトを再生する
* @param  (string tag) 再生するタグ
* @param  (Vector3 pos) エフェクトの座標
*/
void EffectManager::Create(string tag, Vector3 pos)
{
	_effect.at(tag)->Play();
	_effect.at(tag)->SetPosition(pos);
	_effect.at(tag)->Draw();
}

/**
* @fn 　　Effect
* @brief  エフェクトの初期化
* @param  (string filename) ファイル名
* @param  (float speed) エフェクトの再生速度
* @param  (float scale) エフェクトの大きさ
* @return 読み込んだエフェクトを返す
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
