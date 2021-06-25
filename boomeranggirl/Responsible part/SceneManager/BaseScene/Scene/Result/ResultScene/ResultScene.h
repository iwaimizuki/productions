#include "../../../BaseScene.h"

class ResultScene :public BaseScene {
public:
	ResultScene();
	virtual ~ResultScene();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;

private:
	void SaveScore();
	FONT   font;
	SOUND  dramroll;
	MUSIC  bgm;
	SPRITE result,record;
	bool   appear_flag = false;

	int count = MIN_COUNT;
	enum {MIN_COUNT = 0, MAX_COUNT = 90};
protected:

};