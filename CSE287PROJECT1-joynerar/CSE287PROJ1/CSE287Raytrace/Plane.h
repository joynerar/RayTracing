#pragma once
#include "ImplicitSurface.h"

/**
 * @class	Plane
 *
 * @brief	Sub-class of ImplicitSurface that represents implicit description of a plane.
 */
class Plane : public ImplicitSurface
{
	public:

	/**
	 * @fn	Plane::Plane(const dvec3 & point, const dvec3 & normal, const color & material);
	 *
	 * @brief	Constructor for the plane.
	 *
	 * @param	point   	point: specifies an xyz position that is on the plane.
	 * @param	normal  	normal: unit Vector that is perpendicular to the front face of the plane.
	 * @param	material	material: color of the plane.
	 */
	Plane(const dvec3 & point, const dvec3 & normal, const color & material);

	Plane(std::vector<dvec3> vertices, const color & material);

	/**
	 * @fn	virtual HitRecord Plane::findClosestIntersection( const Ray & ray );
	 *
	 * @brief	Checks a ray for intersection with the surface. Finds the closest point of
	 * 			intersection if one exits. Returns a HitRecord with the t parameter set to INFINITY
	 * 			if there is no intersection.
	 *
	 * @param	ray	- Origin of the ray being check for intersetion.
	 *
	 * @returns	HitRecord containing information about the point of intersection.							
	 */
	virtual HitRecord findIntersect( const Ray & ray ) override;

	/** @brief	Point on the plane */
	dvec3 a;

	/** @brief	A dvec3 to process */
	dvec3 n;
};

