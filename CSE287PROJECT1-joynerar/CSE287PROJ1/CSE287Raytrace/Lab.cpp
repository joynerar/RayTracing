#include "Lab.h"

//Workd with Kay Harper on AA 


//******************* GLOBALS **********************//

// The global variables are visible throughout this file.

// Frame buffer holding the color values for each pixel
FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

// Some predefined colors.
const color LIGHT_BLUE(0.784, 0.784, 1.0, 1.0);

// Raytracer
RayTracer rayTrace(frameBuffer, LIGHT_BLUE );

// Light sources in the scene
shared_ptr<LightSource> ambientLight;
shared_ptr<PositionalLight> lightPos;
shared_ptr<DirectionalLight> lightDir;
shared_ptr<SpotLight> lightSpot;

//*********** END OF GLOBAL DECLARATIONS **********//


/**
 * @fn	static void RenderSceneCB()
 *
 * @brief	Acts as the display function for the window.
 */
static void RenderSceneCB()
{
	int frameStartTime = glutGet( GLUT_ELAPSED_TIME ); // Get start time

	// Clear the color buffer
	//frameBuffer.clearColorAndDepthBuffers( ); // Not necessary for ray tracing

	// Ray trace the scene to determine the color of all the pixels in the scene
	rayTrace.raytraceScene( );

	// Display the color buffer
	frameBuffer.showColorBuffer();

	// Calculate and display time required to render scene.
	int frameEndTime = glutGet( GLUT_ELAPSED_TIME ); // Get end time

	float totalTimeSec = (frameEndTime - frameStartTime) / 1000.0f;

	cout << "Render time: " << totalTimeSec << " sec." << endl;

} // end RenderSceneCB


/**
 * @fn	static void ResizeCB(int width, int height)
 *
 * @brief	Reset viewport limits for full window rendering each time the window 
 * 			is resized. This function is called when the program starts up and 
 * 			each time the window is resized.
 *
 * @param	width 	The window width in pixels.
 * @param	height	The window height in pixels.
 */
static void ResizeCB(int width, int height)
{
	// Size the color buffer to match the window size.
	frameBuffer.setFrameBufferSize( width, height );

	rayTrace.calculatePerspectiveViewingParameters(45.0);

	//rayTrace.calculateOrthographicViewingParameters(20.0);

	// Signal the operating system to re-render the window
	glutPostRedisplay();

} // end ResizeCB


/**
 * @fn	static void KeyboardCB(unsigned char key, int x, int y)
 *
 * @brief	Responds to 'f' and escape keys. 'f' key allows toggling full 
 * 			screen viewing. Escape key ends the program. Allows lights to
 * 			be individually turned on and off by pressing the 'a,' 'p,' 
 * 			'd,' and 's' keys. and  
 *
 * @param	key	The key that was pressed.
 * @param	x  	The x coordinate of the mouse.
 * @param	y  	The y coordinate of the mouse.
 */
static void KeyboardCB(unsigned char key, int x, int y)
{
	switch(key) {

	case('f'): case('F') : // 'f' key to toggle full screen
		glutFullScreenToggle();
		break;
	case(27): // Escape key
		glutLeaveMainLoop();
		break;
	case('0') :
		rayTrace.setRecursionDepth( 0 );
		break;
	case('1') :
		rayTrace.setRecursionDepth( 1 );
		break;
	case('2') :
		rayTrace.setRecursionDepth( 2 );
		break;
	case('3') :
		rayTrace.setRecursionDepth( 3 );
		break;
	case('4') :
		rayTrace.setRecursionDepth( 4 );
		break;
	case( '5' ):
		rayTrace.setRecursionDepth( 5 );
		break;
	case( 'a' ):
		// Toggle light on and off
		ambientLight->enabled = (ambientLight->enabled) ? false : true;
		break;
	case( 'p' ):
		// Toggle light on and off
		lightPos->enabled = ( lightPos->enabled ) ? false : true;
		break;
	case( 'd' ):
		// Toggle light on and off
		lightDir->enabled = ( lightDir->enabled ) ? false : true;
		break;
	case( 's' ):
		// Toggle light on and off
		lightSpot->enabled = ( lightSpot->enabled ) ? false : true;
		break;
	case('n'):
		// Turn on Dark mode
		rayTrace.lights.clear();
		lightPos = make_shared<PositionalLight>(dvec3(-10.0, 10.0, 10.0), color(.1, .1, .1, 1));
		lightDir = make_shared<DirectionalLight>(dvec3(1, 1, 1), color(0.1, 0.1, 0.1, 1));
		lightSpot = make_shared<SpotLight>(dvec3(3, 10.0, -19.0), dvec3(0, -1, 0), glm::cos(glm::radians(15.0)), DARK_GRAY);
		rayTrace.lights.push_back(lightPos);
		rayTrace.lights.push_back(lightDir);
		rayTrace.lights.push_back(lightSpot);

		break;
	case('m'):
		// Turn on Light mode
		rayTrace.lights.clear();
		ambientLight->ambientLightColor = color(0.15, 0.15, 0.15, 1.0);
		lightPos = make_shared<PositionalLight>(dvec3(-10.0, 10.0, 10.0), color(1.0, 1.0, 1.0, 1));
		lightDir = make_shared<DirectionalLight>(dvec3(1, 1, 1), color(0.75, 0.75, 0.75, 1));
		lightSpot = make_shared<SpotLight>(dvec3(3, 10.0, -19.0), dvec3(0, -1, 0), glm::cos(glm::radians(15.0)), WHITE);
		rayTrace.lights.push_back(lightPos);
		rayTrace.lights.push_back(lightDir);
		rayTrace.lights.push_back(ambientLight);
		rayTrace.lights.push_back(lightSpot);
		break;
	case('z'): case('Z'):
		rayTrace.antiA = !rayTrace.antiA;
		break;
	default:
		std::cout << key << " key pressed." << std::endl;
	}

	glutPostRedisplay();

} // end KeyboardCB


/**
 * @fn	static void SpecialKeysCB(int key, int x, int y)
 *
 * @brief	Responds to presses of the arrow keys
 *
 * @param	key	The key that was pressed
 * @param	x  	The x coordinate of the mouse.
 * @param	y  	The y coordinate of the mouse.
 */
static void SpecialKeysCB(int key, int x, int y)
{
	switch(key) {
	
	case(GLUT_KEY_RIGHT):
		
		break;
	case(GLUT_KEY_LEFT):
		
		break;
	default:
		cout << key << " key pressed." << endl;
	}

	glutPostRedisplay();

} // end SpecialKeysCB


/**
 * @fn	static void animate()
 *
 * @brief Registered as the "idle" function to have the screen continuously
 * 		  repainted. Due to software rendering, the frame rate will not
 * 		  be fast enough to support motion simulation.
 */
static void animate()
{
	glutPostRedisplay();

} // end animate

/**
 * @fn	void buildScene()
 *
 * @brief	Builds the scene by dynamically allocating ImplicitShape
 * 			objects and Light objects. and adding them to the raytracer 
 * 			surfaces vector.
 * 			
 */
void buildScene()
{
	rayTrace.setRecursionDepth(3);


	// Initialize random seed - used to create random colors
	srand((unsigned int)time(NULL));

	// Set the camera frame by giving the position of the viewpoint, viewing direction, and
	// up direction.
	rayTrace.setCameraFrame(dvec3(0, 0, 0), dvec3(0, 0, -1), dvec3(0, 1, 0));

	// Create a red sphere and it to the list of surfaces in the scene
	shared_ptr<Sphere> redBall = make_shared<Sphere>(dvec3(0.0, 0.0, -10.0), 1.5, RED);
	rayTrace.surfaces.push_back(redBall);
	//redBall//->material.setEmisive(RED);

	shared_ptr<Cylinder> cyl = make_shared<Cylinder>(dvec3(-3, 0, -12), 2, 2, GREEN);
	rayTrace.surfaces.push_back(cyl);
	shared_ptr<Ellipsoid> ellipse = make_shared<Ellipsoid>(dvec3(3,1,-8.0), 1.2, 1.6, 3.3, GREEN);
	rayTrace.surfaces.push_back(ellipse);

	shared_ptr<Sphere> blueBall = make_shared<Sphere>(dvec3(3, 0.0, -17.0), 1.5, BLUE);
	rayTrace.surfaces.push_back(blueBall);
	shared_ptr<Sphere> blueBall2 = make_shared<Sphere>(dvec3(-4.5, 0.0, -17.0), 1.5, BLUE);
	rayTrace.surfaces.push_back(blueBall2);

	shared_ptr<Plane> plane = make_shared<Plane>(dvec3(0, -5, 0.0), dvec3(0, 1, 0), YELLOW);
	rayTrace.surfaces.push_back(plane);


	// Create light sources and add them to the scene.
	ambientLight = make_shared<LightSource>(BLACK);
	ambientLight->ambientLightColor = color(0.15, 0.15, 0.15, 1.0);
	lightPos = make_shared<PositionalLight>(dvec3(-10.0, 10.0, 10.0), color(1.0, 1.0, 1.0, 1));
	lightDir = make_shared<DirectionalLight>(dvec3(1, 1, 1), color(0.75, 0.75, 0.75, 1));
	lightSpot = make_shared<SpotLight>(dvec3(3, 10.0, -19.0), dvec3(0, -1, 0), glm::cos(glm::radians(15.0)), WHITE);


	rayTrace.lights.push_back(lightPos);
	rayTrace.lights.push_back(lightDir);
	rayTrace.lights.push_back(ambientLight);
	rayTrace.lights.push_back(lightSpot);


}



/**
 * @fn	int main(int argc, char** argv)
 *
 * @brief	Main entry-point for this application. Creates a rendering window
 * 			and initializes OpenGL through Glut function calls. Registers
 * 			callback functions (functions that are called by the operating
 * 			system) for specific events. Builds a scene and then enters the 
 * 			rendering loop.
 *
 * @param	argc	The number of command-line arguments provided.
 * @param	argv	An array of command-line argument strings.
 *
 * @returns	Exit-code for the process - 0 for success, else an error code.
 */

int main(int argc, char** argv)
{
	// freeGlut and Window initialization ***********************





    // Pass any applicable command line arguments to GLUT. These arguments
	// are platform dependent.
    glutInit(&argc, argv);

	// Set the initial display mode.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA );

	// Set the initial window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create a window using a string and make it the current window.
	GLuint world_Window = glutCreateWindow("Ray Trace");

	// Indicate to GLUT that the flow of control should return to the program after
	// the window is closed and the GLUTmain loop is exited.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Request that the window be made full screen
	//glutFullScreenToggle();

	// Set red, green, blue, and alpha to which the color buffer is cleared.
	frameBuffer.setClearColor( BLACK );

	// Set the color to which pixels will be cleared if there is no intersection.
	rayTrace.setDefaultColor(BLACK);

	// Callbacks for window redisplay and other events
	glutDisplayFunc(RenderSceneCB);		
	glutReshapeFunc(ResizeCB);
	glutKeyboardFunc(KeyboardCB);
	glutSpecialFunc(SpecialKeysCB);
	//glutIdleFunc( animate );

	// Create the objects and light sources.
	buildScene();

	// Enter the GLUT main loop. Control will not return until the window is closed.
    glutMainLoop();
 
	return 0;

} // end main