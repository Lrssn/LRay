#pragma once
#include "../pch.h"

namespace LUtils {
	class LRandomNumberGenerator {
	public:
		LRandomNumberGenerator() {
			engine.seed(r);
		};
		LRandomNumberGenerator(unsigned int _seed) {
			engine.seed(_seed);
		};
		bool fiftyfifty() {
			std::uniform_int_distribution<> distrib(0, 1);
			return distrib(engine);
		};
		int numberBetween(int _a, int _b) {
			std::uniform_int_distribution<> distrib(_a, _b);
			return distrib(engine);
		};

	private:
		std::random_device r;
		std::mt19937_64 engine;
	};
}



