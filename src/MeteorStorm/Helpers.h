#pragma once
#include <string>
#include "Meteor.h"

class Helpers
{
public:
    static std::string GetString(int val);
    static int getRandomValue(int min, int max);
    static void countCharsInString(const char* str, int& count);
    static Direction generateRandomDirection();
};
