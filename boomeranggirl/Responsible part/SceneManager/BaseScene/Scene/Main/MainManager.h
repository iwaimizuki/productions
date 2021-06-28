//! @file   MainManager.h
//! @brief  ƒQ[ƒ€’†‚ÌŠÇ—
//! @author ŠâˆäŠó
//! @date   2021/5/11

#include"../../BaseScene.h"

class MainManager :public BaseScene
{
public:
	MainManager();
	~MainManager() {};

	bool Initialize() override;
	void Draw2D() override;
	void Draw3D() override;

private:
};