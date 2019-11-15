#pragma once
#include "Plane.h"

/**
* Sub-class of ImplicitSurface that represents implicit description of a convex
* polygon.
*/
class ConvexPolygon : public Plane
{
public:

	/**
	 * @fn	ConvexPolygon::ConvexPolygon(std::vector<dvec3> vertices, color material = color(1.0, 1.0, 1.0, 1.0));
	 *
	 * @brief	Constructor
	 *
	 * @param	vertices	List of three or more vertices providing positions 
	 * 						of the corners of the polygon. Vertices should 
	 * 						appear in counterclockwise order on the "front"
	 * 						side of the plane.
	 * 						
	 * @param	material	(Optional) The diffuse color of the plane.
	 */
	ConvexPolygon(std::vector<dvec3> vertices, color  material = color(1.0, 1.0, 1.0, 1.0));

	/**
	 * @fn	virtual HitRecord ImplicitSurface::findClosestIntersection(const struct Ray & ray);
	 *
	 * @brief	Checks a ray for intersection with the surface. Finds the
	 * 			closest point of intersection if one exits. Returns a HitRecord
	 * 			with the t parameter set to INFINITY if there is no intersection.
	 *
	 * @param	ray	Ray being check for intersection.
	 *
	 * @returns	HitRecord containing properties of the intersection if found.
	 *
	 */
	virtual HitRecord findClosestIntersection( const Ray & ray );

protected:

	/**
	 * @fn	bool ConvexPolygon::checkInside(const dvec3 & point);
	 *
	 * @brief	Function to check if a vertice is to the "left" of 
	 * 			a counterclockwise edge of the polygon.
	 *
	 * @param	point	The vertice checked.
	 *
	 * @returns	True if vertice is left of the edge. False otherwise.
	 */
	bool checkInside(const dvec3 & point);


	/** @brief	List of vertices defining the "corners" of the
	 *			polygon. 
	*/
	std::vector<dvec3> v;

};

