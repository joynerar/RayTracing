#pragma once

#include "Defines.h"

/**
 * @struct	Ray
 *
 * @brief	Simple struct that represents a ray.
 */
struct Ray
{

	/** @brief	starting point for this ray. */
	dvec3 origin;
	

	/** @brief	direction for this ray, given it's origin. */
	dvec3 direct;


	Ray( const dvec3 &rayOrigin = dvec3( 0.0, 0.0, 0.0 ), const dvec3 &rayDirection = dvec3( 0.0, 0.0, -1.0 )/*, RayType rayType = VIEW*/ ) :
		origin( rayOrigin ), direct( glm::normalize( rayDirection ) )
	{
	}

	friend ostream& operator<<(ostream& os, const Ray& ray);

};

static ostream& operator<<(ostream& os, const Ray& ray)
{
	os << "origin: " << ray.origin << " direction: " << ray.direct;

	return os;
}



