#include "Cylinder.h"

Cylinder::Cylinder(const dvec3& position, double r, double height, const color& mat) : 
QuadricSurface::QuadricSurface(position, mat), r(r), height(height)
{
	QuadricSurface::A = (1 / pow(r, 2));
	QuadricSurface::C = (1 / pow(r, 2));
	QuadricSurface::J = -1;
}

HitRecord Cylinder::findIntersect(const Ray& ray)
{
	HitRecord hr = QuadricSurface::findIntersect(ray);
	if (abs(hr.interceptPoint.y - this->center.y) < (height / 2)) {
		return hr;
	}
	else
	{
		hr.t = INFINITY;
		return hr;

	}
}
