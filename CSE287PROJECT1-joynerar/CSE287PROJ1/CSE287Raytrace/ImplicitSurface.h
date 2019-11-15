#pragma once

#include "HitRecord.h"
#include "Ray.h"
#include "Material.h"
#include "TextureCoordinateFunctions.h"


/**
 * @class	ImplicitSurface
 *
 * @brief	Super class for all implicitly described surfaces in a scene. Supports intersection
 * 			testing with rays.
 */
class ImplicitSurface
{
public:

	/**
	* Constructor for the surface.
	* @param - diffuseColor: diffuse color of the surface.
	*/
	ImplicitSurface(const color & diffuseColor);

	/**
	* Constructor for the surface.
	* @param - material: material properties of the surface.
	*/
	ImplicitSurface( const Material & mat );

	/**
	 * @fn	virtual HitRecord ImplicitSurface::findClosestIntersection(const struct Ray & ray);
	 *
	 * @brief	Checks a ray for intersection with the surface. Finds the 
	 * 			closest point of intersection if one exits. Returns a HitRecord
	 * 			 with the t parameter set to INFINITY if there is no intersection.
	 *
	 * @param	ray	Ray being check for intersection.
	 *
	 * @returns	HitRecord containing properties of the intersection if found.
	 *
	 */
	virtual HitRecord findIntersect(const struct Ray & ray);

	/** @brief	Material properties of the surface. */
	Material material;
};

