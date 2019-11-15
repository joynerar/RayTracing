#pragma once
#include "ImplicitSurface.h"

/**
 * @class	QuadricSurface
 *
 * @brief	A quadric surface. Super class to support intersection testing with 
 * 			quadric surfaces. These shapes can be described by the general 
 * 			quadric surface equation 

Ax2 + By2 + Cz2 + Dxy+ Exz + Fyz + Gx + Hy + Iz + J = 0
 */
class QuadricSurface : 	public ImplicitSurface
{
public:

	/**
	 * @fn	QuadricSurface::QuadricSurface(const dvec3 & position, const color & mat);
	 *
	 * @brief	Constructor for the sphere.
	 *
	 * @param	position	Specifies an xyz position of the center of the surface.
	 * @param	mat			Material properties of the plane.
	 */
	QuadricSurface(const dvec3 & position, const color & mat);

	/**
	 * @fn	virtual HitRecord QuadricSurface::findClosestIntersection( const Ray & ray );
	 *
	 * @brief	Checks a ray for intersection with the surface. Finds the 
	 * 			closest point of intersection if one exits. Returns a 
	 * 			HitRecord with the t parameter set to INFINITY if there 
	 * 			is no intersection.
	 *
	 * @param	ray	- The ray being check for intersection.
	 *
	 * @returns	The found intersection.
	 */
	virtual HitRecord findIntersect( const Ray & ray );

	protected:

	/**
	 * @property	double A, B, C, D, E, F, G, H, I, J
	 *
	 * @brief	Coefficients in the  quadric surface equation 
	 * 			Ax2 + By2 + Cz2 + Dxy + Exz + Fyz + Gx + Hy + Iz + J = 0
	 */
	double A, B, C, D, E, F, G, H, I, J;

	/** @brief	xyz location of the center of the surface */
	dvec3 center;

};

