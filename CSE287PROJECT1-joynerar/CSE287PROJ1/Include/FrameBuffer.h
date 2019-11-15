#pragma once

#include "Defines.h"

/**
* Preprocessor statement for text substitution
*
* Number of bytes per pixel. Set to three when
* storing red, green, and blue values. Set to four
* when storing red, green, blue, and alpha values.
*/
const int BYTES_PER_PIXEL = 4;

/**
 * @struct	Window
 *
 * @brief	Structure to hold the width and height of the rendering window
 * 			
 * 			Structures are very similar to classes with the exceptions that: 
 * 			1. Members of a class are private by default and members of struct are public by default. 
			2. When deriving a struct from a class/struct, default access-specifier for a base
 * 			class/struct is public and when deriving a class, default access specifier is
 * 			private.
 */
struct Window {
	int width;
	int height;
};

/**
* Class which controls memory that stores a color value depth value 
* for every pixel in a rendering window with a specified width and height.
* setBufferSize is used to match the size of the memory to the size of the
* window. clearColorBuffer to the color that is specifed using setClearColor.
* showColorBuffer copies the memory into the color buffer for display
* by the graphics card.
*/
class FrameBuffer
{
public:

	/**
	 * @fn	FrameBuffer::FrameBuffer(const int width, const int height);
	 *
	 * @brief	Constructor. Allocates memory for storing pixel values.
	 *
	 * @param	width 	of the rendering window in pixels.
	 * @param	height	of the rendering window in pixels.
	 */
	FrameBuffer(const int width, const int height);


	/**
	 * @fn	FrameBuffer::~FrameBuffer(void);
	 *
	 * @brief	Deallocates dynamically memory associated with the class.
	 */
	~FrameBuffer(void);


	/**
	 * @fn	void FrameBuffer::setFrameBufferSize(const int width, const int height);
	 *
	 * @brief	Sizes the color buffer to match the window size. Deallocates any memory that was
	 * 			previsouly allocated.
	 *
	 * @param	width 	of the rendering window in pixels.
	 * @param	height	of the rendering window in pixels.
	 */
	void setFrameBufferSize(const int width, const int height);


	/**
	 * @fn	void FrameBuffer::setClearColor(const color & clearColor);
	 *
	 * @brief	Sets the color to which the window will be cleared. Does NOT actually clear the window
	 *
	 * @param	clearColor	The clear color.
	 */
	void setClearColor(const color & clearColor);


	/**
	 * @fn	color FrameBuffer::getClearColor( );
	 *
	 * @brief	Returns the color to which the window is being cleared.
	 *
	 * @returns	The clear color.
	 */
	color getClearColor(  );

	/**
	 * @fn	void FrameBuffer::clearColorAndDepthBuffers();
	 *
	 * @brief	Clears the window to the clear color.
	 */
	void clearColorAndDepthBuffers();


	/**
	 * @fn	void FrameBuffer::showColorBuffer();
	 *
	 * @brief	Copies memory into frame buffer and updates the window using an 
	 * 			OpenGL command.
	 */
	void showColorBuffer();


	/**
	 * @fn	int FrameBuffer::getWindowWidth()
	 *
	 * @brief	Returns the width of the rendering window in pixels
	 * 			@ return width of the rendering window
	 *
	 * @returns	The window width.
	 */
	int getWindowWidth(){ return window.width; }


	/**
	 * @fn	int FrameBuffer::getWindowHeight()
	 *
	 * @brief	Returns the height of the rendering window in pixels
	 * 			
	 * @returns	The window height.
	 */
	int getWindowHeight(){ return window.height; }


	/**
	 * @fn	void FrameBuffer::setPixel(const int x, const int y, const color & rgba);
	 *
	 * @brief	Sets an individual pixel value in the color buffer. Origin (0,0)
	 * 			is the lower left hand corner of the window. Color values are 
	 * 			clamped to range [0, 1] before be written to the color buffer.
	 *
	 * @param	x   	coordinate of the pixel.
	 * @param	y   	coordinate of the pixel.
	 * @param	rgba	to which the pixel is to be set.
	 */
	void setPixel(const int & x, const int & y, const color & rgba);


	/**
	 * @fn	color FrameBuffer::getPixel(const int x, const int y);
	 *
	 * @brief	Returns the stored RGBA color valute for an individual pixel position in the color
	 * 			buffer. Origin (0,0) is the lower left hand corner of the window.
	 *
	 * @param	x	coordinate of the pixel.
	 * @param	y	coordinate of the pixel.
	 * 				@ return color that is stored for the pixel position.
	 *
	 * @returns	The pixel.
	 */
	color getPixel(const int & x, const int & y);


	/**
	 * @fn	void FrameBuffer::setDepth(const float x, const float y, const float depth);
	 *
	 * @brief	Set the depth value for a specified pixel.
	 *
	 * @param	x	 	coordinate of the pixel.
	 * @param	y	 	coordinate of the pixel.
	 * @param	depth	to which the pixel is to be set.
	 */
	void setDepth(const float & x, const float & y, const float & depth);


	/**
	 * @fn	void FrameBuffer::setDepth(const int x, const int y, const float depth);
	 *
	 * @brief	Set the depth value for a specified pixel.
	 *
	 * @param	x	 	coordinate of the pixel.
	 * @param	y	 	coordinate of the pixel.
	 * @param	depth	to which the pixel is to be set.
	 */
	void setDepth(const int & x, const int & y, const float & depth);


	/**
	 * @fn	float FrameBuffer::getDepth(const int x, const int y);
	 *
	 * @brief	Returns the depth value for a specified pixel position.
	 *
	 * @param	x	coordinate of the pixel.
	 * @param	y	coordinate of the pixel.
	 * 				@ return depth that is stored for the pixel position.
	 *
	 * @returns	The depth.
	 */
	float getDepth(const int & x, const int & y);


	/**
	 * @fn	float FrameBuffer::getDepth(const float x, const float y);
	 *
	 * @brief	Returns the depth value for a specified pixel position.
	 *
	 * @param	x	coordinate of the pixel.
	 * @param	y	coordinate of the pixel.
	 * 				@ return depth that is stored for the pixel position.
	 *
	 * @returns	The depth.
	 */
	float getDepth(const float & x, const float & y);

	protected:

	/**
	* Check if specified pixel position is in the rendering window
	* Function should not be necessary.
	* @param x coordinate of the pixel.
	* @param y coordinate of the pixel.
	* @ return true if the position is in the window
	*/
	inline bool checkInWindow(const int & x, const int & y);

	/** @brief	Struct that maintains the width and height of the rendering window */
	Window window;

	/** @brief	Color to which memory is cleared when clearColorBuffer is called. */
	GLubyte clearColor[BYTES_PER_PIXEL];

	/** @brief	Storage for red, green, blue, alpha color values */
	GLubyte* colorBuffer;

	/** @brief	Buffer for depth data */
	float* depthBuffer;

}; // end FrameBuffer class

