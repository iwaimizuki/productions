#include"Metal.h"

Stage::Stage()
{
	_model = nullptr;
}

Stage::~Stage()
{

}

bool Stage::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/Stage/stage plan A_v2.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定

	Material mat;
	mat.Diffuse = Color(0.25f, 0.25f, 0.25f);
	mat.Ambient = Color(0.25f, 0.25f, 0.25f);
	mat.Specular = Color(0.5f, 0.5f, 0.5f);
	_model->SetMaterial(mat);

	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	return _model != nullptr;
}