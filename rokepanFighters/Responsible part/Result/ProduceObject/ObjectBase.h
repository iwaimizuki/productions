//! @file   ResultManager.h
//! @brief  ���U���g�̕\�����̊��N���X
//! @author ��䐐��
//! @date   2021/2/7

#pragma once

#include"../../../../ESGLib.h"
#include"../../../Data/MyAlgorithm.h"
#include"../../../Managers/ResouceManager/ResouceManager.h"
#include"../../../Managers/SceneManager/SceneManager.h"
#include "../../../Managers/AudioManager/AudioManager.h"
class ObjectBase
{
public:
	ObjectBase() {};
	~ObjectBase() {};
	virtual bool Initialize() = 0;
	virtual int Update() = 0;
	virtual void Draw2D() {};
	virtual void Draw3D() {};
	static enum Action { NOW, END };
	bool GetState() { return _next_state; }
	void SetState(bool state) { _next_state = state;}
protected:
	bool _next_state = false;
	enum SCORE { DIGITS = 4 };
private:
};