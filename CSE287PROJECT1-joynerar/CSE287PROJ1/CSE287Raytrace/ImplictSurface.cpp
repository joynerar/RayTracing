#include "ImplicitSurface.h"


ImplicitSurface::ImplicitSurface(const color & diffuseColor)
	:	material( diffuseColor )
{
}

ImplicitSurface::ImplicitSurface( const Material & mat )
: material( mat )
{
}

HitRecord ImplicitSurface::findIntersect( const Ray & ray )
{
	HitRecord hitRecord;
	hitRecord.t = INFINITY;

	return hitRecord;
}



