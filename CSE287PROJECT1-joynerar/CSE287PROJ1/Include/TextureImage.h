/****************************************************
 * 2016-2018 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#pragma once
#include "Defines.h"

/**
 * @struct	Image
 * @brief	Represents a rectangular RGB image.
 */

struct TextureImage {
	int W = 0, H = 0;
	color * texels = nullptr;
	TextureImage() {}
	bool loadTextureImage(const char* ppmFileName);
	~TextureImage() { delete[] texels; }
	color getTexel(const dvec2& uv) const;
};