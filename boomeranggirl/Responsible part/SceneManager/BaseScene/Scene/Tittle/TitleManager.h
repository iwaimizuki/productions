//! @file   BaseScene.h
//! @brief  �V�[���̊��N���X
//! @author ��䐐��
//! @date   2021/5/10

#pragma once

#include"../../BaseScene.h"

class TitleManager:public BaseScene
{
public:
	TitleManager();
	~TitleManager() {};
	bool Initialize() override;
	void Draw2D() override;
private:
};