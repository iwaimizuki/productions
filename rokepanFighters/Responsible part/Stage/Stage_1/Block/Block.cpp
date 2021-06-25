#include "Block.h"
#include "../../../Data/IData.h"
#include "../../../ParticleSystem/Particle.h"
#include "../../../Managers/AudioManager/AudioManager.h"
Block::Block(std::string tag)
{
	_map_data.reset(new IMapData);
	_model  = nullptr;
	_tag = tag;
}

Block::~Block()
{
	_hit_box.reset();
	_effect.reset();
}

bool Block::Initialize()
{
	_speed = 0.1;

	_effect.reset(new ParticleSystem);
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);

	//Xファイルの読み込み
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/DestructionBox.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));
	auto effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_break02/break_effect.efk"));

	_effect->RegisterParticle(effect);
	_effect->SetSpeed(1.0f);
	_effect->SetScale(1.0f);

	//スケールの設定
	_scale = 1.0f;
	_model->SetScale(_scale);

	Material mat;
	mat.Diffuse = Color(0.25f, 0.25f, 0.25f);
	mat.Ambient = Color(0.25f, 0.25f, 0.25f);
	mat.Specular = Color(0.5f, 0.5f, 0.5f);
	_model->SetMaterial(mat);
	//マテリアルの設定
	
	//当たり判定を破壊可能ブロックと同じポジションにする
	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));

	//! shader
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	return _model != nullptr;
}
/**
 * @brief プレイヤーが触れた時の処理
 * @return プレイヤーが触れてない時 (int)0
 * @return プレイヤーが触れた時 (int)1
 */
int Block::Update()
{
	//!上から降ってくるとき
	if (_position.y > 0)
	{
		_position.y += -_speed;
		return 0;
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string arm_tag    = ARM_TAG + std::to_string(i + 1);
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);
		float distance = Vector3_Distance(_i_arm_data->GetPosition(arm_tag), _position);

		if (_map_data->GetMapData(_position) != CharTag::BLOCK)
			return IsDead();

		if (distance > _arm_distance)
			continue;

		if (!_hit_box->Tag_Sarch(arm_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(arm_tag)) 
		{
			std::unique_ptr<IPrayerData> player_data = std::make_unique<IPrayerData>();
			std::unique_ptr<IArmData> arm_data = std::make_unique<IArmData>();

			if (arm_data->GetState(arm_tag) == ArmEnum::PunchState::RETURN_PUNCH)
				return StageState::LIVING;

			arm_data->SetState(arm_tag, ArmEnum::PunchState::RETURN_PUNCH);

			player_data->SetRankingPoint(player_tag, player_data->GetRankingPoint(player_tag) + BLOCK_POINT);
			
			return IsDead();
		}
	}
	return StageState::LIVING;
}

int Block::IsDead()
{
	_effect->SetPosition(_position + Vector3_Up * 0.5f);
	_effect->PlayOneShot();
	_effect->Draw();

	_map_data->SetMapData(_position, CharTag::NONE);
	AudioManager::Instance().MultipleSe(DESTRUCTION_SE);
	return StageState::DEATH;
}
