//! @file   BaseScene.h
//! @brief  �G�t�F�N�g�̊Ǘ�
//! @author ��䐐��
//! @date   2021/4/20

#pragma once

#include"../../ESGLib.h"
#include"../ParticleSystem/Particle.h"

class EffectManager
{
public:
    EffectManager::EffectManager() {};
    EffectManager::~EffectManager() {};

    static EffectManager& Instance() {
        static EffectManager instance;
        return instance;
    };

    bool Initialize();

    void Create(string tag, Vector3 pos);

private:
    std::map<string, ParticleSystem*> _effect;
    ParticleSystem* SetEffectInitialize(string filename,float speed,float scale);
};