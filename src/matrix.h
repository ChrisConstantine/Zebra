/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Zebra
 *    > Created Time:   2017-02-28 21:30:15
**/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "vector.h"

namespace Zebra {

class Matrix
{
	public:
		union {
			Float m_[4][4];
			Float _m[16];
		};

		Matrix() { }
		Matrix(	Float m00, Float m10, Float m20, Float m30, \
            Float m01, Float m11, Float m21, Float m31, \
            Float m02, Float m12, Float m22, Float m32, \
            Float m03, Float m13, Float m23, Float m33) {
			m_[0][0] = m00, m_[1][0] = m10, m_[2][0] = m20, m_[3][0] = m30,
			m_[0][1] = m01; m_[1][1] = m11, m_[2][1] = m21, m_[3][1] = m31,
			m_[0][2] = m02; m_[1][2] = m12, m_[2][2] = m22, m_[3][2] = m32,
			m_[0][3] = m03; m_[1][3] = m13, m_[2][3] = m23, m_[3][3] = m33;
		}

		Matrix operator*(const Matrix &m) const {
			Matrix M;
			for (size_t i = 0; i < 4; ++i)
				for (size_t j = 0; j < 4; ++j)
					M.m_[j][i] =  m_[0][i] * m.m_[j][0] +
												m_[1][i] * m.m_[j][1] +
												m_[2][i] * m.m_[j][2] +
												m_[3][i] * m.m_[j][3];
			return M;
		}

		Matrix& operator*=(const Matrix &m) {
			return *this = operator*(m);
		}

		Vector TransformVector(const Vector &p) const {
			Float x = m_[0][0] * p.x_ + m_[1][0] * p.y_ + m_[2][0] * p.z_ + m_[3][0];
			Float y = m_[0][1] * p.x_ + m_[1][1] * p.y_ + m_[2][1] * p.z_ + m_[3][1];
			Float z = m_[0][2] * p.x_ + m_[1][2] * p.y_ + m_[2][2] * p.z_ + m_[3][2];
			return Vector(x, y, z);
		}

		Point TransformPoint(const Point &v) const {
			Float x = m_[0][0] * v.x_ + m_[1][0] * v.y_ + m_[2][0] * v.z_ + m_[3][0];
			Float y = m_[0][1] * v.x_ + m_[1][1] * v.y_ + m_[2][1] * v.z_ + m_[3][1];
			Float z = m_[0][2] * v.x_ + m_[1][2] * v.y_ + m_[2][2] * v.z_ + m_[3][2];
			Float w = m_[0][3] * v.x_ + m_[1][3] * v.y_ + m_[2][3] * v.z_ + m_[3][3];
			if (w != 1.0) {
				Float inv = 1.0 / w;
				x *= inv;
				y *= inv;
				z *= inv;
			}
			return Point(x, y, z);
		}
};

Matrix Inverse(const Matrix &m)
{
	Float inv[16];

	inv[0] = 	m._m[5]  * m._m[10] * m._m[15] -
						m._m[5]  * m._m[11] * m._m[14] -
						m._m[9]  * m._m[6]  * m._m[15] +
						m._m[9]  * m._m[7]  * m._m[14] +
						m._m[13] * m._m[6]  * m._m[11] -
						m._m[13] * m._m[7]  * m._m[10];

	inv[4] = -m._m[4]  * m._m[10] * m._m[15] +
						m._m[4]  * m._m[11] * m._m[14] +
						m._m[8]  * m._m[6]  * m._m[15] -
						m._m[8]  * m._m[7]  * m._m[14] -
						m._m[12] * m._m[6]  * m._m[11] +
						m._m[12] * m._m[7]  * m._m[10];

	inv[8] = 	m._m[4]  * m._m[9]  * m._m[15] -
						m._m[4]  * m._m[11] * m._m[13] -
						m._m[8]  * m._m[5]  * m._m[15] +
						m._m[8]  * m._m[7]  * m._m[13] +
						m._m[12] * m._m[5]  * m._m[11] -
						m._m[12] * m._m[7]  * m._m[9];

	inv[12] = -m._m[4]  * m._m[9]  * m._m[14] +
						 m._m[4]  * m._m[10] * m._m[13] +
						 m._m[8]  * m._m[5]  * m._m[14] -
						 m._m[8]  * m._m[6]  * m._m[13] -
						 m._m[12] * m._m[5]  * m._m[10] +
						 m._m[12] * m._m[6]  * m._m[9];

	inv[1] = -m._m[1]  * m._m[10] * m._m[15] +
						m._m[1]  * m._m[11] * m._m[14] +
						m._m[9]  * m._m[2] *  m._m[15] -
						m._m[9]  * m._m[3] *  m._m[14] -
						m._m[13] * m._m[2] *  m._m[11] +
						m._m[13] * m._m[3] *  m._m[10];

	inv[5] =  m._m[0]  * m._m[10] * m._m[15] -
						m._m[0]  * m._m[11] * m._m[14] -
						m._m[8]  * m._m[2]  * m._m[15] +
						m._m[8]  * m._m[3]  * m._m[14] +
						m._m[12] * m._m[2]  * m._m[11] -
						m._m[12] * m._m[3]  * m._m[10];

	inv[9] = -m._m[0]  * m._m[9]  * m._m[15] +
						m._m[0]  * m._m[11] * m._m[13] +
						m._m[8]  * m._m[1]  * m._m[15] -
						m._m[8]  * m._m[3]  * m._m[13] -
						m._m[12] * m._m[1]  * m._m[11] +
						m._m[12] * m._m[3]  * m._m[9];

	inv[13] = m._m[0]  * m._m[9]  * m._m[14] -
						m._m[0]  * m._m[10] * m._m[13] -
						m._m[8]  * m._m[1]  * m._m[14] +
						m._m[8]  * m._m[2]  * m._m[13] +
						m._m[12] * m._m[1]  * m._m[10] -
						m._m[12] * m._m[2]  * m._m[9];

	inv[2] = m._m[1]  * m._m[6] * m._m[15] -
					 m._m[1]  * m._m[7] * m._m[14] -
					 m._m[5]  * m._m[2] * m._m[15] +
					 m._m[5]  * m._m[3] * m._m[14] +
					 m._m[13] * m._m[2] * m._m[7] -
					 m._m[13] * m._m[3] * m._m[6];

	inv[6] = -m._m[0]  * m._m[6] * m._m[15] +
						m._m[0]  * m._m[7] * m._m[14] +
						m._m[4]  * m._m[2] * m._m[15] -
						m._m[4]  * m._m[3] * m._m[14] -
						m._m[12] * m._m[2] * m._m[7] +
						m._m[12] * m._m[3] * m._m[6];

	inv[10] = m._m[0]  * m._m[5] * m._m[15] -
						m._m[0]  * m._m[7] * m._m[13] -
						m._m[4]  * m._m[1] * m._m[15] +
						m._m[4]  * m._m[3] * m._m[13] +
						m._m[12] * m._m[1] * m._m[7] -
						m._m[12] * m._m[3] * m._m[5];

	inv[14] = -m._m[0]  * m._m[5] * m._m[14] +
						 m._m[0]  * m._m[6] * m._m[13] +
						 m._m[4]  * m._m[1] * m._m[14] -
						 m._m[4]  * m._m[2] * m._m[13] -
						 m._m[12] * m._m[1] * m._m[6] +
						 m._m[12] * m._m[2] * m._m[5];

	inv[3] = -m._m[1] * m._m[6] * m._m[11] +
						m._m[1] * m._m[7] * m._m[10] +
						m._m[5] * m._m[2] * m._m[11] -
						m._m[5] * m._m[3] * m._m[10] -
						m._m[9] * m._m[2] * m._m[7] +
						m._m[9] * m._m[3] * m._m[6];

	inv[7] =  m._m[0] * m._m[6] * m._m[11] -
						m._m[0] * m._m[7] * m._m[10] -
						m._m[4] * m._m[2] * m._m[11] +
						m._m[4] * m._m[3] * m._m[10] +
						m._m[8] * m._m[2] * m._m[7] -
						m._m[8] * m._m[3] * m._m[6];

	inv[11] = -m._m[0] * m._m[5] * m._m[11] +
						 m._m[0] * m._m[7] * m._m[9] +
						 m._m[4] * m._m[1] * m._m[11] -
						 m._m[4] * m._m[3] * m._m[9] -
						 m._m[8] * m._m[1] * m._m[7] +
						 m._m[8] * m._m[3] * m._m[5];

	inv[15] = m._m[0] * m._m[5] * m._m[10] -
	    			m._m[0] * m._m[6] * m._m[9] -
	    			m._m[4] * m._m[1] * m._m[10] +
	    			m._m[4] * m._m[2] * m._m[9] +
	    			m._m[8] * m._m[1] * m._m[6] -
	    			m._m[8] * m._m[2] * m._m[5];

	Float det = m._m[0] * inv[0] + m._m[1] * inv[4] + m._m[2] * inv[8] + m._m[3] * inv[12];

	if (det == 0) { return Matrix(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
	}

	Matrix ret;
	det = 1.0 / det;
	for (int i = 0; i < 16; ++i)
		ret._m[i] = inv[i] * det;
	return ret;
}

Matrix Transform(const Float x, const Float y, const Float z)
{
	return Matrix(1, 0, 0, x,
								0, 1, 0, y,
								0, 0, 1, z,
								0, 0, 0,  1);
}

Matrix Scale(const Float x, const Float y, const Float z)
{
	return Matrix(x, 0, 0, 0,
								0, y, 0, 0,
								0, 0, z, 0,
								0, 0, 0, 1);
}

Matrix Perspective(const Float fov, const Float n, const Float f)
{
	Float n_f = n - f;
	return Matrix(fov, 	0,  0,        0,
								0, 	fov,  0,        0,
								0,  0, 	f/n_f,      1,
								0, 	0, 	(f*n)/n_f,  0);
}

} // namespace Zebra

#endif /* _MATRIX_H_ */