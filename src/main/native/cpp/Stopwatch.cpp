#include "ctre/phoenix/Stopwatch.h"
#include <ratio>

namespace ctre {
namespace phoenix {

void Stopwatch::Start(){
	_t0 = std::chrono::steady_clock::now();
}
long long int Stopwatch::DurationMs(){
	_t1 = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(_t1 - _t0).count();
}
double Stopwatch::Duration(){
	_t1 = std::chrono::steady_clock::now();
	return std::chrono::duration<double>(_t1 - _t0).count();
}

} // namespace phoenix
}
