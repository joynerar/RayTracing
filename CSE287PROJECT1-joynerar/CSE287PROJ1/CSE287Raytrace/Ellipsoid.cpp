#include "Ellipsoid.h"


Ellipsoid::Ellipsoid(const dvec3& position, double a, double b, double c, const color& mat) :
	QuadricSurface::QuadricSurface(position, mat), a(a), b(b), c(c)
{
	QuadricSurface::A = (1 / pow(a, 2));
	QuadricSurface::B = (1 / pow(b, 2));
	QuadricSurface::C = (1 / pow(c, 2));
	QuadricSurface::J = -1;



}

HitRecord Ellipsoid::findIntersect(const Ray& ray)
{
	return QuadricSurface::findIntersect(ray);
}
