#pragma once
#include "config.h"

class IWaveObjectPlacer
{
public:
    virtual std::vector<FPOINT> GetSpawnPoints(int spawnAmount) = 0;
};

class Stage1Wave1ObjectPlacer : public IWaveObjectPlacer
{
    FPOINT initalPosLeft;
    FPOINT marginBetweenSpawn;
    std::vector<FPOINT> spawnPoints; 
public:
    void Init();
    std::vector<FPOINT> GetSpawnPoints(int spawnAmount) override;
};