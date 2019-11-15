#pragma once
#include "QuadricSurface.h"

class  Cylinder : public QuadricSurface
{
public:
	double r, height;
	Cylinder(const dvec3& position, double r, double height, const color& mat);

	virtual HitRecord findIntersect(const Ray& ray);



};
