#pragma once

#include "Defines.h"

// Enumeration type for specifying the axis about which polar coordinates are to be generated.
enum AXIS { X_AXIS, Y_AXIS, Z_AXIS };

/**
 * @fn	dvec2 calculateSphericalTextureCoordinates(const dvec3& objectCoord, const double& width = 1.0, const double& height = 1.0, AXIS axis = X_AXIS);
 *
 * @brief	Finds uv coordinates of an intercept, vertex, or fragment for a spherically mapped
 * 			texture.
 *
 * @author	Bachmaer
 * @date	7/3/2019
 *
 * @param	objectCoord	The object coordinate.
 * @param	width	   	(Optional) The width.
 * @param	height	   	(Optional) The height.
 * @param	axis	   	(Optional) The axis.
 *
 * @returns	The calculated spherical texture coordinates.
 */
dvec2 calcSphericalTextCoord(const dvec3& objectCoord, const double& width = 1.0, const double& height = 1.0, AXIS axis = X_AXIS);

/**
 * @fn	dvec2 calculatePlanarTextureCoordinates(const dvec3& objectCoord, const double& width = 1.0, const double& height = 1.0, AXIS axis = X_AXIS);
 *
 * @brief	Calculates the planar texture coordinates.
 *
 * @author	Bachmaer
 * @date	7/3/2019
 *
 * @param	objectCoord	The object coordinate.
 * @param	width	   	(Optional) The width.
 * @param	height	   	(Optional) The height.
 * @param	axis	   	(Optional) The axis.
 *
 * @returns	The calculated planar texture coordinates.
 */
dvec2 calcPlanarTextCoord(const dvec3& objectCoord, const double& width = 1.0, const double& height = 1.0, AXIS axis = X_AXIS);

/**
 * @fn	dvec2 calculateCylindricalTextureCoordinates(const dvec3& localCoordinates, const double& height = 1.0, AXIS axis = X_AXIS);
 *
 * @brief	Calculates the cylindrical texture coordinates
 *
 * @author	Bachmaer
 * @date	7/3/2019
 *
 * @param	localCoordinates	The local coordinates.
 * @param	height				(Optional) The height.
 * @param	axis				(Optional) The axis.
 *
 * @returns	The calculated cylindrical texture coordinates.
 */
dvec2 calcCylindricalTextCoord(const dvec3& localCoordinates, const double& height = 1.0, AXIS axis = X_AXIS);

/**
 * @fn	dvec2 calculateSineTextureCoordinates(const dvec3& localCoordinates, const double& height = 1.0, const dvec3 & axis = dvec3(1, 0, 0));
 *
 * @brief	Finds uv coordinates of an intercept for a cylindrically mapped texture.
 *
 * @author	Bachmaer
 * @date	7/3/2019
 *
 * @param	localCoordinates	The local coordinates.
 * @param	height				(Optional) The height.
 * @param	axis				(Optional) The axis.
 *
 * @returns	The calculated sine texture coordinates.
 */
dvec2 calcSineTextCoord(const dvec3& localCoordinates, const double& height = 1.0, const dvec3 & axis = dvec3(1, 0, 0));
