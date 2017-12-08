#pragma once

namespace CTRE {
namespace Phoenix {

class HsvToRgb {
public:
	static void Convert(double hDegrees, double S, double V, float* r, float* g,
			float* b);
};

}
}
