#include "Material.h"

color Material::getAmbient(const dvec2& uv) const
{
	switch (textMode)
	{

	case NONE:

		return ambientColor;

		break;

	default:

		return getDiffuse(uv);

	}
}

color Material::getDiffuse(const dvec2& uv) const
{
	double col = (int)(uv.s * 8.0) % 2;
	double row = (int)(uv.t * 8.0) % 2;
	switch (textMode)
	{

	case UV:

		//return texture->getTexel(uv);
		return BLACK;
		break;

	case CHECKERED:

		if ((col == 0 && row != 0) || (col != 0 && row == 0)) {

			return RED;
		}
		else {
			return GREEN;
		}

	default:

		return diffuseColor;

	}
}

color Material::getSpecular(const dvec2& uv) const
{
	return specularColor;
}



color Material::getEmisive(const dvec2& uv) const
{

	switch (textMode)
	{

	case NONE:

		return emissiveColor;

		break;

	default:

		return emissiveColor * getDiffuse(uv);
	}
}

void Material::setEmisive(color newColor)
{
	emissiveColor = newColor;
}


Material operator+(Material lhs, const Material& rhs)
{
	return lhs += rhs;
}


Material operator-(Material lhs, const Material& rhs)
{
	return lhs += -1.0 * rhs;
}

Material operator*(double scalar, const Material& rhs)
{
	Material temp;

	temp.ambientColor = scalar * rhs.ambientColor;
	temp.diffuseColor = scalar * rhs.diffuseColor;
	temp.specularColor = scalar * rhs.specularColor;
	temp.emissiveColor = scalar * rhs.emissiveColor;
	temp.shininess = scalar * rhs.shininess;


	//???
	temp.textMode = rhs.textMode;
	temp.texture = rhs.texture;
	temp.dielecticRefractionIndex = rhs.dielecticRefractionIndex;
	temp.isDielectric = rhs.isDielectric;

	return temp;
}