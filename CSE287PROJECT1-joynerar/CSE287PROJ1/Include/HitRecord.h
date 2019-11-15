#pragma once

#include "Defines.h"
#include "Material.h"


enum RAY_STATUS { ENTERING, LEAVING };

/**
 * @struct	HitRecord
 *
 * @brief	Simple struct to hold information about points of intersection.
 */
struct HitRecord {

	/**
	 * @fn	HitRecord()
	 *
	 * @brief	Default constructor Initializes parameter, t, to INFINITY 
	 * 			indicating that the record does not represent a "hit" or 
	 * 			intersection.
	 */
	HitRecord(){ t = INFINITY; }

	/** @brief	xyz location of intersection in World coordinates */
	glm::dvec3 interceptPoint;

	/** @brief	2D texture coordinates for point of intersection. */
	glm::dvec2 uv;

	/** @brief	surface normal at the point of intersection. */
	glm::dvec3 surfaceNormal;

	/** @brief	"Color" of the surface. */
	Material material;

	/** @brief	Paremeter in parametric ray for the point of intersection. */
	double t;

	/** @brief	Indicates whether if the ray is enter an enclosed object or leaving it. */
	RAY_STATUS rayStatus = ENTERING;

};