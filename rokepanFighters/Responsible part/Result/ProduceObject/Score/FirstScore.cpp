#include"FirstScore.h"

FirstScore::FirstScore()
{
}

FirstScore::~FirstScore()
{
}

bool FirstScore::Initialize()
{
	_score_sprite = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber_vertical.png"));

	return _score_sprite != nullptr;
}

int FirstScore::Update()
{
	float scoreheight = _score_sprite->GetHeight();
	float scorewidth = _score_sprite->GetHeight();

	if (!AudioManager::Instance().OneSe(DRAMROLL))
	{
		auto point = SceneManager::Instance().GetResultData()->points;
		int points[] = { (int)point[0] / 1000,(int)(point[0] % 1000) / 100,
		(int)(point[0] % 1000) % 100 / 10,(int)((point[0] % 1000) % 100 % 10) };
		for (int i = 0; i < SCORE::DIGITS; i++)
		{
			_rect[i] = RectWH(0, points[i] * scoreheight, scoreheight, scorewidth);
		}
		return Action::END;
	}

	_rotation_time += _rotation_speed;
	_rotation_time = IntWrap(_rotation_time, 0, _rotation_max_time);

	for (int i = 0; i < SCORE::DIGITS; i++)
	{
		_rect[i] = RectWH(0, _rotation_time, scoreheight, scorewidth);
	}

	return Action::NOW;
}

void FirstScore::Draw2D()
{
	for (int i = 0; i < SCORE::DIGITS; i++)
	{
		Vector3 pos = _basepos + Vector3(_move_x * i, 0, 0);

		SpriteBatch.Draw(*_score_sprite, pos, _rect[i],
			(DWORD)Color_White, Vector3_Zero, _centerpos, _scale);
	}
}