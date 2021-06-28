//! @file   ResultManager.h
//! @brief  リザルトシーンの管理
//! @author 岩井瑞希
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