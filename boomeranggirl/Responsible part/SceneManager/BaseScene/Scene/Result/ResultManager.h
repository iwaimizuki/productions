//! @file   ResultManager.h
//! @brief  ���U���g�V�[���̊Ǘ�
//! @author ��䐐��
//! @date   2021/5/11

#include"../../BaseScene.h"
class ResultManager :public BaseScene
{
public:
	ResultManager();
	~ResultManager() {};

	bool Initialize() override;
	void Draw2D() override;

private:
};