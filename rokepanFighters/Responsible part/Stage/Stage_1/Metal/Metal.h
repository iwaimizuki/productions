/**
 * @file Floor.h
 * @brief �X�e�[�W�x�[�X���p�������O�ǂ̃N���X
 * @author ��䐐��
 * @date 2020/11/11
 */
#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"

class Stage :public StageBase
{
public:
	Stage();
	~Stage();
	bool Initialize() override;
private:
};