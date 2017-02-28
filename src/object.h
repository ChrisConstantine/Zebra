/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Zebra
 *    > Created Time:  2016-12-31 23:25:32
**/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vector.h"
#include "ray.h"
#include "interaction.h"

namespace Zebra {

enum BSDF { Diffuse, Reflect, Refract };

class Object
{
	public:
		Object(BSDF t, const Spectrum &e, const Spectrum &c):t_(t), e_(e), c_(c) { }

		bool IsLight() const { return e_.y_ > 0; }
		bool IsDelta() const { return t_ != Diffuse; }

		virtual bool Intersect(Ray &r, Interaction *i) const = 0;
		virtual Vector SampleLi(const Vector &n, const Vector2 &u, Float *pdf, Float *dis)const=0;
		virtual bool IntersectP(const Ray &r) const = 0;
		virtual ~Object() { }

		Vector SampleF(const Vector &d, const Vector &n, const Vector2 &u) const {
			switch (t_) {
				case Diffuse: {
					Vector x, y, z(n);
					if (Abs(z.x_) > Abs(z.y_))
						x = Normalize(Cross(Vector(0, 1, 0), z));
					else
						x = Normalize(Cross(Vector(1, 0, 0), z));
					y = Cross(z, x);

					Float m = Sqrt(u.x_);
					Float phi = 2 * PI * u.y_;

					return Normalize(x*(m*Cos(phi)) + y*(m*Sin(phi)) + z*Sqrt(1 - m));
				}
				case Reflect: {
					return Normalize(d - n * (2 * Dot(n, d)));
				}
				case Refract: {
					Float cosi = Dot(n, d);
					bool entering = cosi < 0;

					cosi = entering ? -cosi : cosi;
					Float etai = entering ? 1.0 : 1.3;
					Float etat = entering ? 1.3 : 1.0;

					Float eta = etai / etat;

					Float sini = std::max(Float(0), 1 - cosi * cosi);
					Float sint = eta * eta * sini;

					if (sint >= 1) return Normalize(d - n * (2 * Dot(n, d)));

					Float cost = Sqrt(1 - sint);
					Float term1 = etai * cost;
					Float term2 = etat * cosi;
					Float term3 = etai * cosi;
					Float term4 = etat * cost;

					Float parl = (term2 - term1) / (term2 + term1);
					Float perp = (term3 - term4) / (term3 + term4);
					Float re = (parl * parl + perp * perp) * 0.5;
					if (u.x_ < re)
						return Normalize(d - n * (2 * Dot(n, d)));
					else
						return Normalize(d * eta - n * ((entering ? 1 : -1) * ((eta * cosi) + cost)));
				}
				default:
					assert(0);
			}
		}

		BSDF     t_;
		Spectrum e_;
		Spectrum c_;
};

class Sphere : public Object
{
	public:
		Sphere(BSDF t, const Point &p, Float r, const Spectrum &e, const Spectrum &c)
		:Object(t, e, c), p_(p), r_(r) { }

		Vector SampleLi(const Point &p, const Vector2 &u, Float *pdf, Float *dis) const {
			Vector x, y, z(p_ - p);
			if (Abs(z.x_) > Abs(z.y_))
				x = Normalize(Cross(Vector(0, 1, 0), z));
			else
				x = Normalize(Cross(Vector(1, 0, 0), z));
			y = Cross(z, x);

			Float tmp = z.Length2();
			Float cos_a_max = Sqrt(1 - r_ * r_ / tmp);
			Float cos_a = 1 - u.x_ + u.x_ * cos_a_max;
			Float sin_a = Sqrt(1 - cos_a * cos_a);
			Float phi = 2 * PI * u.y_;
			*pdf = 2 * (1 - cos_a_max);
			*dis = Sqrt(tmp) - r_;
			return Normalize(x*(sin_a*Cos(phi)) + y*(sin_a*Sin(phi)) + z*cos_a);
		}

		bool Intersect(Ray &r, Interaction *i) const override {
			Vector l = p_ - r.o_;
			Float s = Dot(l, r.d_);
			Float l2 = l.Length2();
			Float r2 = r_ * r_;
			if (s < 0 && l2 > r2)
				return false;
			Float q2 = l2 - s * s;
			if (q2 > r2)
				return false;
			Float q = std::sqrt(double(r2) - q2);
			Float d = l2 > r2 ? (s - q) : (s + q);

			if (d > r.m_) return false;

			r.m_ = d;
			Point p = r.o_ + r.d_ * d;
			*i = Interaction(p, Normalize(p - p_), this);
			return true;
		}

		bool IntersectP(const Ray &r) const override {
			Vector l = p_ - r.o_;
			Float s = Dot(l, r.d_);
			Float l2 = l.Length2();
			Float r2 = r_ * r_;
			if (s < 0 && l2 > r2)
				return false;
			Float q2 = l2 - s * s;
			if (q2 > r2)
				return false;
			Float q = std::sqrt(double(r2) - q2);
			Float d = l2 > r2 ? (s - q) : (s + q);

			return d < r.m_ ? true : false;
		}

		Point p_;
		Float r_;
};

} // namespace Zebra

#endif /* _OBJECT_H_ */