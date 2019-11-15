#include "RayTracer.h"


RayTracer::RayTracer(FrameBuffer& cBuffer, color defaultColor)
	:colorBuffer(cBuffer), defaultColor(defaultColor), recursionDepth(2)
{

}


void RayTracer::setCameraFrame(const dvec3& viewPosition, const dvec3& viewingDirection, dvec3 up)
{
	eye = viewPosition;

	w = glm::normalize(-viewingDirection);

	u = glm::normalize(glm::cross(up, w));

	v = glm::normalize(glm::cross(w, u));

} // end setCameraFrame


void RayTracer::calculatePerspectiveViewingParameters(const double& verticalFieldOfViewDegrees)
{
	double fovRad = glm::radians(verticalFieldOfViewDegrees);

	distToPlane = 1.0 / tan(fovRad / 2.0); // distance from the view plane based on fov

	topLimit = 1.0;

	rightLimit = topLimit * ((double)colorBuffer.getWindowWidth() / colorBuffer.getWindowHeight()); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit;
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (double)colorBuffer.getWindowWidth();
	ny = (double)colorBuffer.getWindowHeight();

	renderPerspectiveView = true; // generate perspective view rays

} // end calculatePerspectiveViewingParameters


void RayTracer::calculateOrthographicViewingParameters(const double& viewPlaneHeight)
{
	topLimit = fabs(viewPlaneHeight) / 2.0;

	rightLimit = topLimit * ((double)colorBuffer.getWindowWidth() / colorBuffer.getWindowHeight()); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit;
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (double)colorBuffer.getWindowWidth();
	ny = (double)colorBuffer.getWindowHeight();

	distToPlane = 0.0; // Rays start on the view plane

	renderPerspectiveView = false; // generate orthographic view rays

} // end calculateOrthographicViewingParameters


void RayTracer::raytraceScene()
{
	// Iterate through each and every pixel in the rendering window
	for (int y = 0; y < colorBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < colorBuffer.getWindowWidth(); ++x) {

			Ray viewRay;

			if (renderPerspectiveView == false) {

				// Set the rayOrigin and rayDirection for perspective projection
				viewRay = getOrthoViewRay(x, y);
			}
			else {

				// Set the rayOrigin and rayDirection for perspective projection
				viewRay = getPerspectiveViewRay(x, y);
			}

			// Trace a ray for a specific pixel

			//color colorForPixel = traceRay(viewRay, recursionDepth);
			color colorForPixel = BLACK;
			//colorForPixel += traceRay(viewRay, recursionDepth);
			if (antiA) {

				//int numOfExtraRays = 1;
				for (int q = -1; q <= 1; q++) {
					for (int w = -1; w <= 1; w++) {
						viewRay.direct.x = viewRay.direct.x + (q / 1000.0);
						viewRay.direct.y = viewRay.direct.y + (w / 1000.0);
						colorForPixel += traceRay(viewRay, recursionDepth);
						viewRay.direct.x = viewRay.direct.x - (q / 1000.0);
						viewRay.direct.y = viewRay.direct.y - (w / 1000.0);
					}
				}
				colorForPixel = color(colorForPixel.x / 9.0, colorForPixel.y / 9.0, colorForPixel.z / 9.0, 1);
				colorBuffer.setPixel(x, y, colorForPixel);
			}
			else {
				colorForPixel = traceRay(viewRay, recursionDepth);
				colorBuffer.setPixel(x, y, colorForPixel);
			}
			//// Set the pixel color
			//colorForPixel = color(colorForPixel.r / numOfExtraRays,
			//	colorForPixel.g / numOfExtraRays,
			//	colorForPixel.b / numOfExtraRays,
			//	1);
			//
		}
	}

} // end raytraceScene


color RayTracer::traceRay(const Ray& ray, int recursionLevel)
{
	color totalLight = BLACK;
	HitRecord closestHit = findClosestIntersection(ray);

	if (closestHit.t == INFINITY) {
		return defaultColor;
	}

	else {
		//return closestHit.material.getAmbient();
		for (auto& light : lights) {
			double d = light->getLightDistance(closestHit.interceptPoint);

			

			dvec3 shadowFeeler = light->getLightVector(closestHit.interceptPoint);
			HitRecord shadowHit = findClosestIntersection(Ray(closestHit.interceptPoint+closestHit.surfaceNormal*EPSILON,shadowFeeler));
			if (d >= light->getLightDistance(shadowHit.interceptPoint)) {
				totalLight += light->getLocalIllumination(
					-ray.direct, closestHit.interceptPoint,
					closestHit.surfaceNormal,
					closestHit.material, closestHit.uv);
			}
		}
		//double kr = fresnel();


		if (recursionLevel > 0) {

			dvec3 reflectionDirection = glm::reflect(ray.direct, closestHit.surfaceNormal);
			Ray reflectRay(closestHit.interceptPoint + EPSILON * closestHit.surfaceNormal, reflectionDirection);
			totalLight += traceRay(reflectRay, recursionLevel - 1);
		}




		/*dvec3 refractDirection = glm::refract(ray.direct, closestHit.surfaceNormal, );
		Ray reflectRay(closestHit.interceptPoint + EPSILON * closestHit.surfaceNormal, refractDirection);
		totalLight +=
		
		** USE FRESNEL Equation
		
		*/


		return totalLight + closestHit.material.getEmisive();

		
	}
} // end traceRay


HitRecord RayTracer::findClosestIntersection(const Ray& ray)
{

	HitRecord closestHit;
	closestHit.t = INFINITY;

	// Check if the ray intersects any surfaces in the scene
	for (auto& surface : this->surfaces) {

		HitRecord hitRec = surface->findIntersect(ray);

		// Check if it is closer that previous intersection.
		if (hitRec.t < closestHit.t) {

			closestHit = hitRec;
		}

	}

	return closestHit;

} // end findIntersection


Ray RayTracer::getOrthoViewRay(const int& x, const int& y)
{
	Ray orthoViewRay;

	dvec2 uv = getImagePlaneCoordinates(x, y);

	orthoViewRay.origin = eye + uv.x * u + uv.y * v;
	orthoViewRay.direct = glm::normalize(-w);

	return orthoViewRay;

} // end getOrthoViewRay


Ray RayTracer::getPerspectiveViewRay(const int& x, const int& y)
{
	Ray perspectiveViewRay;

	dvec2 uv = getImagePlaneCoordinates(x, y);

	perspectiveViewRay.origin = eye;
	perspectiveViewRay.direct = glm::normalize((-distToPlane) * w + uv.x * u + uv.y * v);

	return perspectiveViewRay;

} // end getPerspectiveViewRay


dvec2 RayTracer::getImagePlaneCoordinates(const int& x, const int& y)
{
	dvec2 s;

	s.x = leftLimit + (rightLimit - leftLimit) * (x + 0.5) / nx;
	s.y = bottomLimit + (topLimit - bottomLimit) * (y + 0.5) / ny;
	return s;

} // end getImagePlaneCoordinates




