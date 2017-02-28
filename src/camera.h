/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Zebra
 *    > Created Time:  2017-01-01 09:08:57
**/

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"

namespace Zebra {

class Camera
{
	public:
		Camera(int x = 512, int y = 384):x_(x), y_(y) { }

		Vector RasterToWorld(Float x, Float y) const {
			static const Float cx = Float(x_) * 0.5135 / y_;
			static const Float cy = 0.5135;
			return Normalize(Vector(cx * ((x / x_) - 0.5),
                              cy * (0.5 - (y / y_)),
                              1));
		}

		int RasterToIndex(int x, int y) const { return y * x_ + x; }

		const int x_;
		const int y_;
};

} // namespace Zebra

#endif /* _CAMERA_H_ */