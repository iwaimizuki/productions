#pragma once

#include"../../../BaseScene.h"
#include "../../../../../Field/FieldManager.h"
#include "../../../../../PlayerManager/PlayerManeger.h"
#include "../../../../../UI/UI.h"
class MainStart :public BaseScene
{
public:
	MainStart();
	virtual ~MainStart();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
private:
	//SPRITE bg;
	FieldManeger* fieldManeger;
	PlayerManager* playermanager;

	CAMERA camera;
	ANIMATIONMODEL player;
	SOUND start;
	UI ui;
};