#include "MediumDifficulty.h"
#include "MeteorStorm.h"

void MediumDifficulty::executeBehavior() {

    predator_meteor_ratio = 0.5f;
    player_speed = 10;
    meteors_count = 5;
    meteorWidth = 50.0f;
    meteorHeight = 50.0f;
    meteorBaseInitialDistanceFromPlayer = 100;
    MOVE_STEP = 4;
    meteorRandomMovmentBoundry = 3;
}