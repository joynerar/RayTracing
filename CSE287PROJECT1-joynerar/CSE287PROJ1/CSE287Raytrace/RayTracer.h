#pragma once

#include "FrameBuffer.h"
#include "LightSource.h"
#include "HitRecord.h"
#include "ImplicitSurface.h"
#include "Ray.h"

/**
 * @class	RayTracer
 *
 * @brief	Class that supports simple ray tracing of a scene containing a number of object
 * 			(surfaces) and light sources.
 */
class RayTracer
{
	public:

	/**
	 * @fn	RayTracer::RayTracer(FrameBuffer & cBuffer, color defaultColor = BLACK);
	 *
	 * @brief	Constructor.
	 *
	 * @param [in,out]	cBuffer			buffer to which the ray tracer will be render.
	 * @param 		  	defaultColor	(Optional) color to which pixel will be set when there it no
	 * 									intersection for a ray associated with a particular pixel.
	 */
	RayTracer(FrameBuffer & cBuffer, color defaultColor = BLACK);


	/**
	 * @fn	void RayTracer::raytraceScene();
	 *
	 * @brief	Ray traces a scene containing a number of surfaces and light sources. Sets every
	 * 			pixel in the rendering window. Pixels that are not associated with a ray/surface
	 * 			intersection are set to a default color.
	 */
	void raytraceScene( );


	/**
	 * @fn	void RayTracer::setCameraFrame(const dvec3 & viewPosition, const dvec3 & viewingDirection, dvec3 up);
	 *
	 * @brief	Sets the w, u, and v orthonormal basis vectors associated with the coordinate frame
	 * 			that is tied to the viewing position and the eye data member of the class.
	 *
	 * @param	viewPosition		xyz position of the view point.
	 * @param	viewingDirection	vector that points in the viewing direction.
	 * @param	up					approximation of the up vector (cannot be parallel to viewing
	 * 								direction)
	 */
	void setCameraFrame(const dvec3 & viewPosition, const dvec3 & viewingDirection, dvec3 up);


	/**
	 * @fn	void RayTracer::calculateOrthographicViewingParameters(const double & viewPlaneHeight = 10.0);
	 *
	 * @brief	Set the following members of the class: topLimit, bottomLimit, rightLimit, leftLimit,
	 * 			distToPlane, nx, and ny based the distance form the middle of the projection plane to
	 * 			the top of the projection plane and width of the rendering window.
	 *
	 * @param	viewPlaneHeight	(Optional) - distance to the top of the projection plane.
	 */
	void calculateOrthographicViewingParameters(const double & viewPlaneHeight = 10.0);

	/**
	 * @fn	void RayTracer::calculatePerspectiveViewingParameters(const double & verticalFieldOfViewDegrees = 45.0);
	 *
	 * @brief	Set the following members of the class: topLimit, bottomLimit, rightLimit, leftLimit,
	 * 			distToPlane, nx, and ny based of the specified vertical field of view and height and
	 * 			width of the rendering window.
	 *
	 * @param	verticalFieldOfViewDegrees	(Optional) - vertical field of view in degrees.
	 */
	void calculatePerspectiveViewingParameters(const double & verticalFieldOfViewDegrees = 45.0);


	/**
	 * @fn	void RayTracer::setDefaultColor(color defaultColor)
	 *
	 * @brief	Set the color to which pixels are set when the associated ray does not intersect any
	 * 			object in the scene.
	 *
	 * @param	defaultColor	color for pixels for which no ray-object intersections occur.
	 */
	void setDefaultColor(const color & defaultColor) { this->defaultColor = defaultColor; }


	/**
	 * @fn	void RayTracer::setRecursionDepth( int recursionDepth )
	 *
	 * @brief	Sets the recusion depth to determine how many reflected and refracted bounces for
	 * 			viewing rays. Values of zero or less result in no reflection of refracted rays being
	 * 			traced.
	 *
	 * @param	recursionDepth	Number of times refracted and reflected rays will be generated for
	 * 							each view ray.
	 */
	void setRecursionDepth( const int & recursionDepth ) { this->recursionDepth = recursionDepth; }


	/** @brief	List of the surfaces in the scene that is being ray traced */
	SurfaceVector surfaces;

	/** @brief	List of the light sources in the scene that is being ray traced */
	LightVector lights;

	bool antiA = false;

protected:

	/**
	 * @fn	color RayTracer::traceIndividualRay( const Ray & ray, int recursionLevel = 0);
	 *
	 * @brief	Once the closest point of intersection is found a color is returned based on
	 * 			calculated interactions between the intersected surface and the light sources in the
	 * 			scene.
	 * 			
	 * 			Can be called recursively to trace rays associated with reflection and refraction.
	 *
	 * @param	ray			  	Ray being traced.
	 * @param	recursionLevel	(Optional) - control number of additional rays that will be traced
	 * 							for the point of intersection of the ray with a surface.
	 *
	 * @returns	color for the point of intersection.
	 */
	color traceRay( const Ray & ray, int recursionLevel = 0);


	/**
	 * @fn	HitRecord RayTracer::findIntersection( const Ray & ray);
	 *
	 * @brief	Checks the ray for intersection against every Surface in the 
	 * 			scene. It does this by repeatedly passing the Ray to 
	 * 			findClosestIntersection methods of ImplicitSurface class and its 
	 * 			sub-classes.
	 *
	 * @param	ray	- origin of the ray being checked for interse.
	 *
	 * @returns	HitRecord for the intersection, if one exists, or a HitRecord 
	 * 			with t of INFINITY otherwise.
	 *
	 */
	HitRecord findClosestIntersection( const Ray & ray);


	/**
	 * @fn	Ray RayTracer::getOrthoViewRay( const int x, const int y);
	 *
	 * @brief	Gets the rayOrigin and rayDirection data members of the class based on row and column
	 * 			of a specified pixel.These two data members together represent a parametric
	 * 			description of a ray to be checked for intersection with objects in the scene. The
	 * 			ray is calculated for a orthographic projection.
	 *
	 * @param	x	column of a pixel in the rendering window.
	 * @param	y	row of a pixel in the rendering window.
	 *
	 * @returns	The ortho view ray.
	 */
	Ray getOrthoViewRay( const int & x, const int & y);


	/**
	 * @fn	Ray RayTracer::getPerspectiveViewRay( const int x, const int y);
	 *
	 * @brief	Gets the rayOrigin and rayDirection data members of the class 
	 * 			based on row and column of a specified pixel.These two data members 
	 * 			together represent a parametric description of a ray to be checked 
	 * 			for intersection with objects in the scene. The ray is calculated 
	 * 			for a perspective projection.
	 *
	 * @param	x	column of a pixel in the rendering window.
	 * @param	y	row of a pixel in the rendering window.
	 *
	 * @returns	The perspective view ray.
	 */
	Ray getPerspectiveViewRay( const int & x, const int & y);


	/**
	 * @fn	dvec2 RayTracer::getImagePlaneCoordinates(const int x, const int y);
	 *
	 * @brief	Finds the projection plane coordinates, u and v, for the pixel identified by the
	 * 			input arguments.
	 *
	 * @param	x	column of a pixel in the rendering window.
	 * @param	y	row of a pixel in the rendering window.
	 *
	 * @returns	two dimensional vector containing the projection plane coordinates.
	 */
	dvec2 getImagePlaneCoordinates(const int & x, const int & y);


	/** @brief	Alias for an object that controls memory that stores a rgba color value f or every pixel. */
	FrameBuffer & colorBuffer;

	/** @brief	Color to which a pixel is set if there is no intersection for a traced pixel ray. */
	color defaultColor;

	/* View frame parameters */

	/** @brief	position of the viewpoint */
	dvec3 eye;

	/** @brief	"right" direction relative to the viewing direction */
	dvec3 u;

	/** @brief	"up" direction relative to the viewing vector */
	dvec3 v;

	/** @brief	"back" direction relative to the viewing vector. 
	Camera looks in the negative w direction */
	dvec3 w;

	/*  Projection plane parameters */

	/** @brief	 Distance from center of projection plane to the right limit 
	of the projection plane; measured relative to u (right) */
	double rightLimit = 1.0;

	/** @brief	 Distance from center of projection plane to the left limit
	of the projection plane; measured relative to u (right) */
	double leftLimit = -1.0;

	/** @brief	 Distance from center of projection plane to the top limit
	of the projection plane; measured relative to v (up) */
	double topLimit = 1.0;

	/** @brief	 Distance from center of projection plane to the bottom limit
	of the projection plane; measured relative to v (up) */
	double bottomLimit = -1.0;

	/* Rendering window parameters */
	
	/** @brief	Floating point width of the window in pixels */
	double nx = 1.0;

	/** @brief	Floating point height of the window in pixel */
	double ny = 1.0;

	/** @brief	Distance from the viewpoint to the projection plane */
	double distToPlane = 1.0;

	/** @brief	True to generate rays for perspective viewing. Fall for orthographic viewing. */
	bool renderPerspectiveView = true;

	/** @brief	Max recursion depth */
	int recursionDepth;

	

}; // end RayTracer class


