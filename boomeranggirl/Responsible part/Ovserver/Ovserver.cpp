#include"Ovserver.h"
#include"../SceneManager/SceneManager.h"

int Ovserver::Update(PlayerManager* playerdata, EnemyManager* enemydata)
{
	_playerdata = playerdata;
	_enemydata = enemydata;

	ColisionDetection();
	return 0;
}

void Ovserver::ColisionDetection()
{
	BoomerangEnemyHit();
	EnemyPlayerHit();
}

void Ovserver::BoomerangEnemyHit()
{
	if (!_playerdata->GetShootState())return;

	auto a_pos = _playerdata->GetBoomerang().GetCollision()->GetPosition();
	auto a_scale = _playerdata->GetBoomerang().GetCollision()->GetScale();

	for (auto enemy : _enemydata->GetEnemy())
	{
		auto b_pos = enemy->GetCollision()->GetPosition();
		auto b_scale = enemy->GetCollision()->GetScale() / 2;
		//! aとbのボックスの当たり判定
		if (a_pos.x - a_scale.x < b_pos.x + b_scale.x &&
			a_pos.x + a_scale.x > b_pos.x - b_scale.x &&
			a_pos.z - a_scale.z < b_pos.z + b_scale.z &&
			a_pos.z + a_scale.z > b_pos.z - b_scale.z)
		{
			_enemydata->OnCollisionEnter(enemy);
			SceneManager::Instance().AddCombo();
		}
	}
}

void Ovserver::EnemyPlayerHit()
{
	if (_playerdata->GetAnimState() == _playerdata->DAMAGE)return;

	auto a_pos = _playerdata->GetCollision()->GetPosition();
	auto a_scale = _playerdata->GetCollision()->GetScale();

	for (auto enemy : _enemydata->GetEnemy())
	{
		auto b_pos = enemy->GetCollision()->GetPosition();
		auto b_scale = enemy->GetCollision()->GetScale() / 2;
		//! aとbのボックスの当たり判定
		if (a_pos.x - a_scale.x < b_pos.x + b_scale.x &&
			a_pos.x + a_scale.x > b_pos.x - b_scale.x &&
			a_pos.z - a_scale.z < b_pos.z + b_scale.z &&
			a_pos.z + a_scale.z > b_pos.z - b_scale.z)
		{
			_playerdata->OnCollisionEnter();
			break;
		}
	}
}
