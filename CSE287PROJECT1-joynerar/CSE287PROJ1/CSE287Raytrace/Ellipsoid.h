#pragma once
#include "QuadricSurface.h"

class  Ellipsoid : public QuadricSurface
{
public:
	double a, b, c;
	Ellipsoid(const dvec3 & position, double a, double b, double c, const color & mat);

	virtual HitRecord findIntersect(const Ray& ray);

	

};
