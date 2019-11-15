#pragma once

#include "Defines.h"
#include "Material.h"
//#include "HitRecord.h"

/**
 * @struct	LightSource
 *
 * @brief	Base struct for all types of lights. Supports only specification of the color and
 * 			intensity of light sources. Parent of sub-structs that simulate positional,
 * 			directional, and spot lights.
 * 			
 * 			Instances of this struct an be used to simulate only ambient light. Ambient light is
 * 			described as bounced light that has been scattered so much that it is impossible to
 * 			tell the direction to its source. If using a LightSource instantiation to simulate
 * 			ambient light, the overall intensity of the light should be low in order to avoid
 * 			washing out shadows as well as diffuse and specular effects that can be achieved when
 * 			using children of this struct.
 */
struct LightSource
{
	LightSource(const color & lightColor = BLACK) 
	: diffuseLightColor(lightColor)
	{
	}

	virtual color getLocalIllumination(	const dvec3& eyeVector, const dvec3& position,
										const dvec3& normal, const Material& material,
										const dvec2& uv = dvec2(0.5, 0.5) )
	{
		if (enabled) {
			return ambientLightColor * material.getAmbient(uv);
		}
		else {
			return BLACK;
		}
	}		

	virtual dvec3 getLightVector(dvec3 position) { return dvec3(0.0, 0.0, 0.0); }

	virtual double getLightDistance(dvec3 position) { return 0.0; }


	/** @brief	Ambient color and intensity of the light.*/
	color ambientLightColor = BLACK;

	/** @brief	Diffuse color and intensity of the light. */
	color diffuseLightColor; 

	/** @brief	Specular color and intensity of the light. */
	color specularLightColor = WHITE;

	/** @brief	Shading calculations are performed if true. BLACK (no light) is returned otherwise. */
	bool enabled = true;
		
}; // end LightSource super struct


/**
 * @struct	PositionalLight
 *
 * @brief	Struct for simulating light sources that have an explicit position and shine equally
 * 			in all directions. Instantiations of the struct will have a position property and a
 * 			color and intensity of the light given off by the light.
 */
struct PositionalLight : public LightSource
{
	/**
	 * @fn	PositionalLight(glm::dvec3 position, const color & lightColor)
	 *
	 * @brief	Constructor
	 *
	 * @param	position  	The position of the light source relative to 
	 * 						World coordinates.
	 * @param	lightColor	Ambient and diffuse color of the light.
	 */
	PositionalLight(glm::dvec3 position, const color & lightColor)
	: LightSource(lightColor), lightPosition(position)
	{}

	/**
	 * @fn	virtual color getLocalIllumination(const glm::dvec3 & eyeVector, HitRecord & closestHit)
	 *
	 * @brief	Calculates and returns the combined ambient, diffuse, and 
	 * 			specular reflection for a vertex, fragment, or point of intersection.
	 *
	 * @param 		  	eyeVector 	Direction from the fragment (point 
	 * 								of intersection) to the viewpoint.
	 * @param [in,out]	closestHit	Contains position of the fragment (point
	 * 								of intersection), surface normal and material properties.
	 *
	 * @returns	The local illumination.
	 */
	virtual color getLocalIllumination(	const dvec3& eyeVector, const dvec3& position,
										const dvec3& normal, const Material& material,
										const dvec2& uv = dvec2(0.5, 0.5)) override
	{
		if (enabled) {
			double d = getLightDistance(position);
			double attenutaitionFactor = 1 / (CONSTANT_ATTEN + LINEAR_ATTEN * d + (QUADRATIC_ATTEN * pow(d, 2)));


			dvec3 lightVec = getLightVector(position);
			dvec3 viewVec = glm::normalize(eyeVector);
			dvec3 reflectVec = glm::reflect(-lightVec, normal);
			color ambientReflect = ambientLightColor * material.getAmbient(uv);
			color diffuseReflect = diffuseLightColor * material.getDiffuse(uv) * glm::max(glm::dot(normal, lightVec), 0.0);
			color specularReflect = glm::pow(glm::max(glm::dot(viewVec, reflectVec), 0.0), material.shininess) *
				specularLightColor * material.getSpecular(uv);
			return attenutaitionFactor * (ambientReflect + diffuseReflect + specularReflect);
		}
		else {
			return BLACK;
		}
		



	}


	virtual dvec3 getLightVector(dvec3 position)
	{

		return glm::normalize( lightPosition - position);
	}

	virtual double getLightDistance(dvec3 position)
	{

		return glm::distance( lightPosition, position);
	}


	/** @brief	x, y, z position of the light source. */
	glm::dvec3 lightPosition; 

}; // end PositionalLight struct


/**
 * @struct	DirectionalLight
 *
 * @brief	Struct for simulating light sources that do not have an explicit position. Such light
 * 			sources have only a direction against which they are shinning. Instantiations of the
 * 			struct will have this direction properties along with a color and intensity of the
 * 			light given off by the light source.
 */
struct DirectionalLight : public LightSource
{
	DirectionalLight(dvec3 direction, const color & lightColor)
	: LightSource(lightColor), lightDirection(glm::normalize(direction))
	{}


	/**
	 * @fn	virtual color getLocalIllumination(const glm::dvec3 & eyeVector, HitRecord & closestHit)
	 *
	 * @brief	Calculates and returns the combined ambient, diffuse, and
	 * 			specular reflection for a vertex, fragment, or point of intersection.
	 *
	 * @param 		  	eyeVector 	Direction from the fragment (point
	 * 								of intersection) to the viewpoint.
	 * @param [in,out]	closestHit	Contains position of the fragment (point
	 * 								of intersection), surface normal and material properties.
	 *
	 * @returns	The local illumination.
	 */
	virtual color getLocalIllumination(	const dvec3& eyeVector, const dvec3& position,
										const dvec3& normal, const Material& material,
										const dvec2& uv = dvec2(0.5, 0.5)) override
	{
		//dvec3 lightVec = glm::normalize(lightPosition - position);
		if (enabled) {
			dvec3 viewVec = glm::normalize(eyeVector);
			dvec3 reflectVec = glm::reflect(-lightDirection, normal);
			color ambientReflect = ambientLightColor * material.getAmbient(uv);
			color diffuseReflect = diffuseLightColor * material.getDiffuse(uv) * glm::max(glm::dot(normal, lightDirection), 0.0);
			color specularReflect = glm::pow(glm::max(glm::dot(reflectVec, viewVec), 0.0), material.shininess) *
				specularLightColor * material.getSpecular(uv);
			return ambientReflect + diffuseReflect + specularReflect;
		}
		else
		{
			return BLACK;
		}
		
	}

	virtual dvec3 getLightVector(dvec3 position)
	{

		return lightDirection;
	}

	virtual double getLightDistance(dvec3 position)
	{

		return INFINITY;
	}

	/**
	 * @brief	Unit vector that points in the direction that is opposite the direction in which the
	 * 			light is shining.
	 */
	glm::dvec3 lightDirection; 

}; // end DirectionalLight struct

/**
 * @struct	SpotLight
 *
 * @brief	Struct for simulating light sources that have an explicit position and shine in a
 * 			specified direction.Width of the associated beam of light is controlled using a spot
 * 			cutoff cosine. Instantiations of the struct will have position and direction
 * 			properties along with a color and intensity of the light given off by the light
 * 			source.
 */
struct SpotLight : public PositionalLight
{
	SpotLight( dvec3 position, dvec3 direction, double cutOffCosineRadians, const color & colorOfLight )
		: PositionalLight( position, colorOfLight ), spotDirection( glm::normalize( direction ) ), cutOffCosineRadians( cutOffCosineRadians )
	{
	}

	/**
	 * @fn	virtual color getLocalIllumination( const dvec3& eyeVector, const dvec3& interceptPoint, const dvec3& surfaceNormal, const dvec2& uv, const Material& material)
	 *
	 * @brief	Calculates and returns the combined ambient, diffuse, and specular reflection for a
	 * 			vertex, fragment, or point of intersection.
	 *
	 * @param	eyeVector	  	Direction from the fragment (point of intersection) to the viewpoint.
	 * @param	interceptPoint	Contains position of the fragment (point of intersection), surface
	 * 							normal and material properties.
	 * @param	surfaceNormal 	The surface normal.
	 * @param	uv			  	The uv.
	 * @param	material	  	The material.
	 *
	 * @returns	The local illumination.
	 */
	virtual color getLocalIllumination(const dvec3& eyeVector, const dvec3& position,
		const dvec3& normal, const Material& material,
		const dvec2& uv = dvec2(0.5, 0.5)) override
	{
		dvec3 lightVec = glm::normalize(lightPosition - position);
		


		if (glm::dot(spotDirection,-lightVec) > cutOffCosineRadians && enabled) {
			double spotCos = glm::dot(lightVec, spotDirection);
			double exp = 128;
			double falloffFac = glm::pow(spotCos, exp);
			return  falloffFac * PositionalLight::getLocalIllumination(eyeVector, position, normal, material, uv);
				
				//* PositionalLight::getLocalIllumination(eyeVector, position, normal, material, uv);
			//return PositionalLight::getLocalIllumination(eyeVector, position, normal, material, uv);
		}
		else {
			return BLACK;
		}

	}

	/** @brief	Unit vector that points in the direction in which the light is shining. */
	dvec3 spotDirection;

	/** @brief	Angle in radians of half the spot light beam */
	double cutOffCosineRadians;

}; // end SpotLight struct

