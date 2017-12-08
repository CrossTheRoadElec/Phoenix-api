#pragma once

namespace CTRE {
namespace Phoenix {
	
class LinearInterpolation {
public:
	static float Calculate(float x, float x1, float y1, float x2, float y2);
};

}}

