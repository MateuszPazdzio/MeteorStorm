#include "HardDifficulty.h"
#include "MeteorStorm.h"


void HardDifficulty::executeBehavior() {

    predator_meteor_ratio = 0.8f;
    player_speed = 8;
    meteors_count = 8;
    meteorWidth = 60.0f;
    meteorHeight = 60.0f;
    meteorBaseInitialDistanceFromPlayer = 70;
    MOVE_STEP = 5;
    meteorRandomMovmentBoundry = 5;

}