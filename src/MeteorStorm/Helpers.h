#pragma once
#include <string>

class Helpers
{
public:
    static std::string GetString(int val);
    static int getRandomValue(int min, int max);
    static void countCharsInString(const char* str, int& count);
};
