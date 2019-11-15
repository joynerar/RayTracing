#pragma once

#include "ImplicitSurface.h"

/**
* Sub-class of ImplicitSurface that represents implicit description of a sphere.
*/
class Sphere : 	public ImplicitSurface
{
	public:

	/**
	* Constructor for the sphere.
	* @param - point: specifies an xyz position of the center of the sphere
	* @param - radius: radius of the sphere
	* @param - material: color of the plane.
	*/
	Sphere(const dvec3 & position = dvec3(0.0, 0.0, -5.0),
			double radius = 1.0, 
			const color & material = color(1.0, 1.0, 1.0, 1.0) );

	/**
	* Checks a ray for intersection with the surface. Finds the closest point of intersection
	* if one exits. Returns a HitRecord with the t parameter set to INFINITY if there is no
	* intersection.
	* @param rayOrigin - Origin of the ray being check for intersection
	* @param rayDirection - Unit vector representation the direction of the ray.
	* returns HitRecord containing information about the point of intersection.
	*/
	virtual HitRecord findIntersect( const Ray & ray ) override;

	/**
	* Radius of the sphere
	*/
	double radius;

	/**
	* xyz location of the center of the sphere
	*/
	dvec3 center;
};

