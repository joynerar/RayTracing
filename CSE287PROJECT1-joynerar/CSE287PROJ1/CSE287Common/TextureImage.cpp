/****************************************************
 * 2016-2018 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <fstream>
#include <utility>
#include <set>
#include "TextureImage.h"

double map(double x, double xLow, double xHigh, double yLow, double yHigh);
void map(double x, double xLow, double xHigh, double yLow, double yHigh, double& y);


static unsigned int getNextChar(std::ifstream& input, string& str) {
	const int N = 2000;
	char buf;
	input.read(&buf, 1);
	unsigned int result = (unsigned char)buf;
	return result;
}

static void p3(std::ifstream& input, TextureImage& im) {
	const int N = 100;
	char buf[N + 1];

	int maxValue;
	input >> im.W >> im.H >> maxValue;
	input.getline(buf, N);

	im.texels = new color[im.W * im.H];
	color* p = im.texels;
	for (int row = 0; row < im.H; row++) {
		for (int col = 0; col < im.W; col++, p++) {
			int r, g, b;
			input >> r >> g >> b;
			double R = map((double)r, 0.0, (double)maxValue, 0.0, 1.0);
			double G = map((double)g, 0.0, (double)maxValue, 0.0, 1.0);
			double B = map((double)b, 0.0, (double)maxValue, 0.0, 1.0);
			*p = color(R, G, B, 1.0);
		}
	}
}

static void p6(std::ifstream& input, TextureImage& im) {
	const int N = 100;
	char buf[N + 1];

	int maxValue;
	input >> im.W >> im.H >> maxValue;
	input.getline(buf, N);

	im.texels = new color[im.W * im.H];
	string buffer;
	color* p = im.texels;
	for (int row = 0; row < im.H; row++) {
		for (int col = 0; col < im.W; col++, p++) {
			int r, g, b;
			r = getNextChar(input, buffer);
			g = getNextChar(input, buffer);
			b = getNextChar(input, buffer);
			double R = map((double)r, 0.0, (double)maxValue, 0.0, 1.0);
			double G = map((double)g, 0.0, (double)maxValue, 0.0, 1.0);
			double B = map((double)b, 0.0, (double)maxValue, 0.0, 1.0);
			*p = color(R, G, B, 1.0);
		}
	}
}

/**
 * @fn	Image::Image(char *ppmFileName)
 * @brief	Constructs and image given the name of a PPM file. The file must be
 * 			P3 or P6.
 * @param [in,out]	ppmFileName	Filename of the ppm file.
 */

bool TextureImage::loadTextureImage(const char* ppmFileName)
{
	const int N = 100;
	char buf1[N + 1];
	char buf2[N + 1];
	std::ifstream input(ppmFileName, std::ios::binary);
	input.getline(buf1, N);
	int type = 3;

	while (input.peek() == '#') {
		input.getline(buf2, N);
	}
	string header(buf1);
	header = header.substr(0, 2);
	if (header == "P3") {
		p3(input, *this);
	}
	else if (header == "P6") {
		p6(input, *this);
	}
	else {
		std::cerr << "Problem with PPM file: " << ppmFileName << "(" << header << ")" << endl;

		return false;
	}

	cout << ppmFileName << " loaded successfully: " << W << " x " << H << endl;
	input.close();

	return true;
}

#include <assert.h>
/**
 * @fn	color Image::getPixelUV(double u, double v) const
 * @brief	Gets the color that corresponds to the coordinate (u, v). This is
 * 			done by finding the texel whose center is closest to (u, v). In the
 * 			event of a tie, picks one of these.
 * @param	u	The u in (u, v).
 * @param	v	The v in (u, v).
 * @return	The color corresponding to the position (u, v).
 */
color TextureImage::getTexel(const dvec2& uv) const {
	//int s = (uv.s == 1) ? W-1 : (int)(W*uv.s);
	//int t = (uv.t == 1) ? H-1 : (int)(H*uv.t);

	int s = (int)fmod(uv.s * W, W);
	int t = (int)fmod(uv.t * H, H);

	// Clamp values to avoid illegal memory access
	s = glm::clamp(s, 0, W - 1);
	t = glm::clamp(t, 0, H - 1);

	return texels[t * W + s];
}

/**
 * @fn	double map(double x, double xLow, double xHigh, double yLow, double yHigh)
 * @brief	Linearly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	xLow 	The low value of the x range.
 * @param 		  	xHigh	The high value of the x range.
 * @param 		  	yLow 	The low value of the y range.
 * @param 		  	yHigh	The high value of the y range.
 * @test	map(2, 0, 5, 10, 11) --> 10.4
 */
double map(double x, double xLow, double xHigh, double yLow, double yHigh)
{
	return (x - xLow) / (xHigh - xLow) * (yHigh - yLow) + yLow;
}

/**
 * @fn	void map(double x, double xLow, double xHigh, double yLow, double yHigh, double &y)
 * @brief	Linearlly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	xLow 	The low value of the x range.
 * @param 		  	xHigh	The high value of the x range.
 * @param 		  	yLow 	The low value of the y range.
 * @param 		  	yHigh	The high value of the y range.
 * @param [in,out]	y	 	The mapped value in the y range.
 * @test	map(2, 0, 5, 10, 11, y) --> y = 10.4
 */
void map(double x, double xLow, double xHigh, double yLow, double yHigh, double& y)
{
	y = map(x, xLow, xHigh, yLow, yHigh);
}