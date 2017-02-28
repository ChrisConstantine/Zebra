/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Zebra
 *    > Created Time:   2017-02-27 18:47:39
**/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <limits>

namespace Zebra {

#ifdef USE_DOUBLE_FLOAT
typedef double Float;
const Float kEplison = 1e-4;
#else
typedef float Float;
const Float kEplison = 1e-3;
#endif

const Float INF = std::numeric_limits<Float>::max();
const Float PI = 3.141592653589793238;

inline Float Abs(Float f) {
	#ifdef USE_DOUBLE_FLOAT
	return std::fabs(f);
	#else
	return fabsf(f);
	#endif
}

inline Float Sqrt(Float f) {
	#ifdef USE_DOUBLE_FLOAT
	return std::sqrt(f);
	#else
	return sqrtf(f);
	#endif
}

inline Float Sin(Float f) {
	#ifdef USE_DOUBLE_FLOAT
	return std::sin(f);
	#else
	return sinf(f);
	#endif
}

inline Float Cos(Float f) {
	#ifdef USE_DOUBLE_FLOAT
	return std::cos(f);
	#else
	return cosf(f);
	#endif
}

} // namespace Zebra

#endif /* _UTIL_H_ */