//! @file   BaseScene.h
//! @brief  エフェクトの管理
//! @author 岩井瑞希
//! @date   2021/3/20

#pragma once

#include"../PlayerManager/PlayerManeger.h"
#include"../EnemyManager/EnemyManeger.h";
#include"../../ESGLib.h"

class Ovserver {
public:
    Ovserver::Ovserver() {};
    Ovserver::~Ovserver() {};
    int     Update(PlayerManager*, EnemyManager*);
    void    ColisionDetection();
private:
    void    BoomerangEnemyHit();
    void    EnemyPlayerHit();
    PlayerManager* _playerdata = new PlayerManager;
    EnemyManager* _enemydata = new EnemyManager;
};