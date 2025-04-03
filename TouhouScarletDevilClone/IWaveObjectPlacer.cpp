#include "IWaveObjectPlacer.h"

std::vector<FPOINT> Stage1Wave1ObjectPlacer::GetSpawnPoints(int spawnAmount)
{
    std::vector<FPOINT> result = std::vector<FPOINT>();
    result.push_back(initalPosLeft);
    for (int i=1; i<spawnAmount; ++i)
    {   
        FPOINT newPos = { result.back().x, result.back().y };
        newPos.x += marginBetweenSpawn.x;
        newPos.y += marginBetweenSpawn.y;

        result.push_back(newPos);
    }
    return result;
}

void Stage1Wave1ObjectPlacer::Init()
{
    // add enemypositions
    initalPosLeft = {GAME_RIGHT - 15.f, GAME_TOP - 100.f};
    marginBetweenSpawn = { -50.f, 0};
    // spawnPoints = GetSpawnPoints(spawnAmount);
}
