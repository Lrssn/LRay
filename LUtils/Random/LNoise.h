#pragma once
#include "../pch.h"
#include "LRandom.h"

namespace LUtils {
	namespace LMath {
		class LNoise {
		public:
			LNoise() {};
			~LNoise() {};
			int whitenoise() {
				if (this->mRNG.fiftyfifty() == true) {
					return 1;
				} else {
					return 0;
				}
			};
			//TODO: float perlinNoise();
			//TODO: float simplexNoise();
			
		private:
			LRandomNumberGenerator mRNG;
		};

	}
}