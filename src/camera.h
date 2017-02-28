/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Zebra
 *    > Created Time:  2017-01-01 09:08:57
**/

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"
#include "matrix.h"

namespace Zebra {

class Camera
{
	public:
		Camera(int x = 512, int y = 384):x_(x), y_(y) {
			auto raster_to_screen = Scale(Float(x_)/y_*0.5135, -0.5135, 1) *
			                        Transform(-.5, -.5, 0) *
			                        Scale(1./x_, 1./y_, 1);
			auto perspective  = Perspective(0.5135, 1, 10000);

			raster_to_world_ = Inverse(perspective) * raster_to_screen;
			world_to_raster_ = Inverse(raster_to_world_);
		}

		Vector RasterToWorld(Float x, Float y) const {
			return Normalize(raster_to_world_.TransformPoint(Point(x, y, 0)));
		}

		int RasterToIndex(int x, int y) const { return y * x_ + x; }

		const int x_;
		const int y_;

	private:
		Matrix world_to_raster_;
		Matrix raster_to_world_;
};

} // namespace Zebra

#endif /* _CAMERA_H_ */