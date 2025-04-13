#include "EasyDifficulty.h"
#include "MeteorStorm.h"

void EasyDifficulty::executeBehavior()
{
    predator_meteor_ratio = 0.3f;
    player_speed = 12;
    meteors_count = 3;
    meteorWidth = 40.0f;
    meteorHeight = 40.0f;
    meteorBaseInitialDistanceFromPlayer = 150;
    MOVE_STEP = 3;
    meteorRandomMovmentBoundry = 1;
}
