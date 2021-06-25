#include"MainEnd.h"
#include"../MainGame/MainGame.h"
#include "../../../../../TimeManager/TimeManager.h"
#include"../../../../SceneManager.h"
MainEnd::MainEnd()
{
	playermanager = new PlayerManager;
	fieldManeger = new FieldManeger;
	enemymanager = new EnemyManager;
}

MainEnd::~MainEnd()
{
	delete enemymanager;
	delete playermanager;
	delete fieldManeger;
}

bool MainEnd::Initialize()
{
	playermanager->Initialize();
	fieldManeger->Initialize();
	ui.Initialize();
	TimeManager::Instance().Initialize();
	player = playermanager->GetModel();

	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	camera->SetView(Vector3(0, 0, -650), Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(camera);
	return true;
}

int MainEnd::Update()
{
	if (ui.Update() == 1)
		return Scene::NEXT;

	playermanager->Update();
	enemymanager->Update(playermanager);
	TimeManager::Instance().Update();
	ui.Update();
	return Scene::NOW;
}

void MainEnd::Draw2D()
{
	ui.Draw();
}