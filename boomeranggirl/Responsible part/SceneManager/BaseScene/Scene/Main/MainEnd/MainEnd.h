#include"../../../BaseScene.h"
#include "../../../../../Field/FieldManager.h"
#include "../../../../../EnemyManager/EnemyManeger.h"
#include "../../../../../PlayerManager/PlayerManeger.h"
#include "../../../../../UI/UI.h"
class MainEnd :public BaseScene
{
public:
	MainEnd();
	virtual ~MainEnd();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
private:
	//SPRITE bg;
	FieldManeger* fieldManeger;
	PlayerManager* playermanager;
	EnemyManager* enemymanager;

	CAMERA camera;
	ANIMATIONMODEL player;
	UI ui;
};