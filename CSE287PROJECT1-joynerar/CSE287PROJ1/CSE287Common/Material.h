#pragma once

#include "Defines.h"
#include "TextureImage.h"


enum TEXTURE_MODE { NONE, UV, SINE, CHECKERED };


/**
* Simple struct that represents the materials properties of a surface. Material properties
* deterine the color of and object and how it interacts with light sources in a scene.
*/
struct Material
{
protected:

	/** @brief	Emissive color of the surface */
	color emissiveColor = BLACK;

	/** @brief	Ambient color of the surface (usually the same as the diffuseColor). */
	color ambientColor = GRAY;

	/** @brief	Diffuse color of the surface. */
	color diffuseColor = GRAY;

	/** @brief	Specular color of the surface (white for a shiny surface). */
	color specularColor = WHITE;

public:



	/** @brief	Shininess exponent for specular lighting calculations. */
	double shininess = 128.0;

	/** @brief	The texture mode */
	TEXTURE_MODE textMode = NONE;

	shared_ptr<TextureImage> texture = nullptr;

	/** @brief	index of refraction for the material  */
	double dielecticRefractionIndex = 1.0;


	/** @brief	True if is dielectric and BOTH transmits and reflects light, false if not */
	bool isDielectric = false;
	/**
	 * @fn	Material( const color & diffuseColor = WHITE )
	 *
	 * @brief	Constructor
	 *
	 * @param	diffuseColor	(Optional) The diffuse color of the surface.
	 */
	Material(const color& diffuseColor = WHITE)
		: diffuseColor(diffuseColor), ambientColor(diffuseColor)
	{
		textMode = NONE;
	}

	/**
	 * @fn	Material(char* fileName )
	 *
	 * @brief	Constructor
	 *
	 * @param [in,out]	fileName	If non-null, filename of the file.
	 */
	Material(const char* fileName)
	{
		texture = make_shared<TextureImage>();

		// Load the texture
		if (texture->loadTextureImage(fileName) == true) {

			// Set the texture mode of texture mapping
			textMode = UV;
		}
		else {

			textMode = NONE;
		}
	}



	virtual color getAmbient(const dvec2& uv = dvec2(0.5, 0.5)) const;

	virtual color getDiffuse(const dvec2& uv = dvec2(0.5, 0.5)) const;

	virtual color getSpecular(const dvec2& uv = dvec2(0.5, 0.5)) const;

	virtual color getEmisive(const dvec2& uv = dvec2(0.5, 0.5)) const;

	virtual void setEmisive(color newColor);

	Material& operator+=(const Material& rhs)
	{
		this->ambientColor += rhs.ambientColor;
		this->diffuseColor += rhs.diffuseColor;
		this->specularColor += rhs.specularColor;
		this->emissiveColor += rhs.emissiveColor;
		this->shininess += rhs.shininess;

		//???
		this->textMode = rhs.textMode;
		this->texture = rhs.texture;
		this->dielecticRefractionIndex = rhs.dielecticRefractionIndex;
		this->isDielectric = rhs.isDielectric;

		return *this;
	}

	friend Material operator+(Material lhs, const Material& rhs);
	friend Material operator-(Material lhs, const Material& rhs);
	friend Material operator*(double scalar, const Material& rhs);

};