#include"SmallScore.h"

SmallScore::SmallScore()
{
}

SmallScore::~SmallScore()
{
}

bool SmallScore::Initialize()
{
	_score_sprite = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));
	_robot_fece = ResouceManager::Instance().LordSpriteFile(_T("ResultSprite/result_robo.png"));

	for (int i = 1; i < PLAYER_COUNT_MAX; i++)
	{
		_scale[i - 1] = 10.0f;
		std::string name = PLAYER_TAG + to_string(SceneManager::Instance().GetResultData()->ranknum[i]);
		_player_rectwh.push_back(128 * (SceneManager::Instance().GetPlayerTexture(name) - 1));
	}

	return _score_sprite != nullptr && _robot_fece != nullptr;
}

int SmallScore::Update()
{
	if (_smallacorenum >= 0)_scale[_smallacorenum] -= _smallspeed;
	else return Action::END;

	if (_scale[_smallacorenum] <= _minscale)_smallacorenum--;

	for (int i = 0; i < PLAYER_COUNT_MAX - 1; i++)
	{
		_scale[i] = Clamp(_scale[i], _minscale, INT_MAX);
	}
	return Action::NOW;
}

void SmallScore::Draw2D()
{
	for (int i = 0; i < SCORE::DIGITS - 1; i++)
	{
		if (_scale[i] < _displaysclae)continue;

		SpriteBatch.Draw(*_robot_fece, _robot_fece_basepos + Vector3(0, _robot_fece_move_y * i, 0),
			RectWH(_player_rectwh[i], 0, _robot_fece->GetHeight(), _robot_fece->GetWidth()));

		auto point = SceneManager::Instance().GetResultData()->points[i + 1];
		int points[] = { (int)point / 1000,(int)(point % 1000) / 100,
		(int)(point % 1000) % 100 / 10,(int)((point % 1000) % 100 % 10) };
		for (int j = 0; j < PLAYER_COUNT_MAX; j++)
		{
			SpriteBatch.Draw(*_score_sprite, _score_basepos +
				Vector3(_move_vector3.x * j, _move_vector3.y * i, 0), RectWH(points[j] * _score_sprite->GetHeight(), 0,
					_score_sprite->GetHeight(), _score_sprite->GetWidth()),
				(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), _scale[i]);
		}
	}
}