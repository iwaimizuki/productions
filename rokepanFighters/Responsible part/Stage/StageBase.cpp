#include "StageBase.h"
#include"../Managers/SceneManager/SceneManager.h"

int StageBase::Update()
{
    return 0;
}

void StageBase::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0,0,0);

	if (_hit_box != nullptr)
	{
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
	}

	auto camera = SceneCamera::Instance().GetCamera();
	Matrix world = _model->GetWorldMatrix();

	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetParameter("wvp", world * camera.GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", camera.GetPosition());
	_shader->SetTechnique("FixModel_S0");

	_model->Draw(_shader);
}
