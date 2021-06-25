#include"Indestructible.h"
#include "../../../Managers/AudioManager/AudioManager.h"
Indestructible::Indestructible(std::string tag)
{
	_tag = tag;
	_model = nullptr;
}

Indestructible::~Indestructible()
{
	_hit_box.reset();
}

bool Indestructible::Initialize()
{
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);
	//Xファイルの読み込み
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/Indestructible.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定

	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(0.25f, 0.25f, 0.25f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);
	
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	return _model != nullptr;
}

int Indestructible::Update()
{
	//当たり判定を破壊可能ブロックと同じポジションにする
	if (_hit_box != nullptr)
	_hit_box->SetHitBoxPosition(_position);

	_position.y += -_speed;
	if (_position.y <= _minposy)
	{
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

			//!プレイヤーとの接触時にプレイヤーを倒す
			if (_hit_box->IsHitObjectsSquare(player_tag))
			{
				std::unique_ptr<IPrayerData> playerdata = std::make_unique<IPrayerData>();
				if (!playerdata->GetInvincibleMode(player_tag))
				{
					playerdata->SetState(player_tag, PlayerEnum::Animation::DEATH);
					if (playerdata->GetRankingPoint(player_tag) >= 300)
						playerdata->SetRankingPoint(player_tag, playerdata->GetRankingPoint(player_tag) - 300);
					else
						playerdata->SetRankingPoint(player_tag, 0);
					break;
				}
			}
		}
		std::unique_ptr<IMapData> map_data = std::make_unique<IMapData>();
		map_data->SetMapData(_position, CharTag::INDESTRUCTIBIEPILLAR);

		_position.y = _minposy;
	}
	return 0;
}