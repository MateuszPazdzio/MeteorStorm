#include "Helpers.h"
#include <random>
#include <sstream>
int Helpers::getRandomValue(int min, int max) {
	static std::random_device rd;  // Seed for random number engine
	static std::mt19937 rng(rd()); // Mersenne Twister PRNG
	std::uniform_int_distribution<int> dist(min, max);
	int val = dist(rng);

	return val;
}
std::string Helpers::GetString(int val) {
    std::stringstream ss;
    ss << val;
    return ss.str();
}

void Helpers::countCharsInString(const char* str, int& count) {
    while (*str) {
        count++;
        str += 1;
    }
}
