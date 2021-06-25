#include"SceneManager.h"
#include"BaseScene/Scene/Tittle/TitleManager.h"
#include"BaseScene/Scene/Main/MainManager.h"
#include"BaseScene/Scene/Result/ResultManager.h"
#include"../Data/MyAlgorithm.h"

SceneManager::SceneManager()
{
	_scene = nullptr;
	SetCombo(0);
	SetDeathEnemy(0);
}

void SceneManager::ChangeScene(string scene)
{
	_scene.reset();

	if (scene == SceneNumber::TITLE)		_scene = std::make_unique<TitleManager>();
	else if (scene == SceneNumber::MAIN)	_scene = std::make_unique<MainManager>();
	else if (scene == SceneNumber::RESULT)	_scene = std::make_unique<ResultManager>();

	assert(_scene && "ŠY“–scene‚È‚µ");

	_scene->Initialize();
}
bool SceneManager::Initialize(string scene)
{
	Effekseer.Attach(GraphicsDevice, 8192);

	ChangeScene(scene);

	return 0;
}

int SceneManager::Update()
{
	Effekseer.Update();

	if (_scene->Update() == _scene->NEXT)ChangeScene(_scene->GetNextScene());

	_combo_reset_time += GameTimer.GetElapsedSecond();

	if (_combo_reset_time >= COMBORESETTIMEMAX)_combo = 0;

	_combo_reset_time = FloatWrap(_combo_reset_time, 0, COMBORESETTIMEMAX);

	return 0;
}

void SceneManager::Draw()
{
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	_scene->Draw3D();

	SpriteBatch.Begin();

	_scene->Draw2D();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}

void SceneManager::AddCombo()
{
	_combo_reset_time = 0.0f;
	++_combo;

	MaximumCombo();
}

int SceneManager::MaximumCombo()
{
	if (_combo <= _max_combo)return _max_combo;

	return _max_combo = _combo;
}