#pragma once

namespace CTRE {
	
class HsvToRgb{
public:
	static void Convert(double hDegrees, double S, double V, float* r, float* g,
		float* b);
};

}
