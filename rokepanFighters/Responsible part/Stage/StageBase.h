
#pragma once

#include "../../ESGLib.h"
#include "../Collision/HitBox.h"
#include "../Data/WordsTable.h"
#include "../Managers/ResouceManager/ResouceManager.h"
#include "../Managers/SceneManager/SceneManager.h"
#include "../Data/MyAlgorithm.h"
class StageBase
{
public:
	StageBase() {};
	virtual ~StageBase() {};

	virtual bool Initialize() { return true; };
	virtual int Update();
	virtual void Draw3D();

	void SetPosition(Vector3& position) { _position = position; }
	Vector3 GetPosition() { return _position; }
	enum StageState{ LIVING, DEATH };
protected:
	MODEL _model;//!継承されるモデルのベース
	EFFECT _shader;
	SPRITE _texture;

	float _scale = 1.0f;
	Vector3 _position = vector3(0,0,0);//!継承されるモデルのポジション
	
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
	Material _model_material;
private:
};