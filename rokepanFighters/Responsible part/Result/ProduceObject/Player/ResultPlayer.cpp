#include"ResultPlayer.h"
#include"../../../../ParticleSystem/Particle.h"
#include"../Score/FirstScore.h"
#include "../../../../Managers/InputManager/InputManager.h"

ResultPlayer::ResultPlayer()
{
	_effect.reset(new ParticleSystem);
}

ResultPlayer::~ResultPlayer()
{
	_effect.reset();
	_player_model->SetTrackPosition(5, 0);
	_player_model->SetTrackEnable(5, false);
}

bool ResultPlayer::Initialize()
{
	//! camera
	Viewport view = GraphicsDevice.GetViewport();
	Vector3  camera_pos = Vector3(0, 0, -10);
	Vector3  look_pos = Vector3_Zero;

	SceneCamera::Instance().SetLookAt(camera_pos, look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/AnimationStandardShader.hlsl"));
	_player_model = ResouceManager::Instance().LoadAnimationModelFile(_T("Player/Robo_animation.X"));
	auto&& effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/Confetti/confetti_01.efk"));

	//!ロボUI初期設定
	std::string first_name = PLAYER_TAG + to_string(SceneManager::Instance().GetResultData()->ranknum[0]);

	std::string player_number = PLAYER_TAG + to_string(SceneManager::Instance().GetPlayerTexture(first_name));
	auto path = ConvertFilePath("Player/", player_number, ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	//! material
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f); // 陰影のグラデーション 明るい部分
	material.Ambient = Color(1.0f, 1.0f, 1.0f); // ベースの色　暗い部分
	material.Specular = Color(1.0f, 1.0f, 1.0f); // テカリ
	material.Power = 10.0f;                   // テカリの効果の強さ

	_player_model->SetMaterial(material);

	for (int i = 0; i < VictoryAnimation::NUMBER; i++)
	{
		_player_model->SetTrackPosition(i, 0);
		_player_model->SetTrackEnable(i, false);
	}

	//!プレイヤーの初期設定
	_player_model->SetScale(5.0f);
	_player_model->SetPosition(Vector3(-5, -3, 0));
	_player_model->SetRotation(0, 180, 0);
	_player_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	_player_model->SetTrackEnable(VictoryAnimation::NUMBER, TRUE);

	//! effect
	_effect->RegisterParticle(effect);
	_effect->SetSpeed(1.0f);
	_effect->SetScale(2.0f);
	_effect->SetPosition(Vector3(-5, -1.5, 0));
	_effect->SetRotation(Vector3(0, 0, 0));
	return false;
}

int ResultPlayer::Update()
{
	if (!AudioManager::Instance().OneSe(CRACKER))
	{
		for (int i = 0; i < PLAYER_COUNT_MAX; i++)
		{
			auto pad = InputManager::Instance().GetGamePad(PLAYER_TAG + std::to_string(i + 1));
			pad->Refresh();
			if (pad->ButtonDown(BUTTON_INFO::BUTTON_A))
			{
				SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
			}
		}
	}
	_effect->PlayOneShot();
	_effect_time++;
	if(FloatWrap(_effect_time,0,_effecttimemax) <= 0)
		_effect->Stop();
	return Action::NOW;
}
void ResultPlayer::Draw3D()
{
	Matrix vp = SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix();
	SceneCamera::Instance().SetSceneCamera();

	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("vp", vp);
	_shader->SetTechnique("UnlitAnimationModel");
	_player_model->SetTrackPosition(VictoryAnimation::NUMBER, _animation_count);
	_animation_count += GameTimer.GetElapsedSecond();
	_player_model->Draw(_shader);
	_effect->Draw();
}
