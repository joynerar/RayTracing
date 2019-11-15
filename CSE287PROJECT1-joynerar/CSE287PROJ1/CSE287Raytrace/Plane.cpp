#include "Plane.h"


Plane::Plane(const dvec3 & point, const dvec3 & normal, const color & material)
	: ImplicitSurface(material), a(point), n(normalize(normal))
{
}


Plane::Plane(std::vector<dvec3> vertices, const color & material)
	: ImplicitSurface(material)
{
	a = vertices[0];

	n = glm::normalize(glm::cross(vertices[2] - vertices[1], vertices[0] - vertices[1]));
}


HitRecord Plane::findIntersect( const Ray & ray )
{
	HitRecord hitRecord;

	double discriminant = glm::dot(ray.direct, n);
	if (discriminant == 0) {
		hitRecord.t = INFINITY;
	}
	else {
		double t = glm::dot((a - ray.origin), n) / discriminant;
		if (t < 0)
			t = INFINITY;
		else {
			hitRecord.t = t;
			hitRecord.interceptPoint = ray.origin + t * ray.direct;
			if (glm::dot(n, ray.direct) > 0) {

				n = -n; // reverse the normal
				hitRecord.rayStatus = LEAVING;
			}
			else {

				hitRecord.rayStatus = ENTERING;
			}
			hitRecord.surfaceNormal = n;
			hitRecord.material = material;
		}
	}

	return hitRecord;

} // end findClosestIntersection

