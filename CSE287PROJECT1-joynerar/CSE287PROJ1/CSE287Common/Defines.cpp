#include "Defines.h"

#include <iomanip>


color generateRandomColor()
{
	float red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	return color(red, green, blue, 1.0);

} // end getRandomColor

/**
 * @fn	ostream &operator<< ( ostream &os, const dvec2 &V ) { os << "[ " << V.x << " " << V.y << " ]"; return os;
 *
 * @brief	Output stream for vec2.
 *
 * @param [in,out]	os	Output stream.
 * @param 		  	V 	The vector.
 *
 * @returns	The shifted result.
 */
ostream &operator << ( ostream &os, const dvec2 &V )
{
	os << "[ " << V.x << " " << V.y << " ]";
	return os;
}

/**
 * @fn	ostream &operator<< ( ostream &os, const dvec3 &V ) { os << "[ " << V.x << " " << V.y << " " << V.z << " ]"; return os;
 *
 * @brief	Output stream for vec3.
 *
 * @param [in,out]	os	Output stream.
 * @param 		  	V 	The vector.
 *
 * @returns	The shifted result.
 */
ostream &operator << ( ostream &os, const dvec3 &V )
{
	os << "[ " << V.x << " " << V.y << " " << V.z << " ]";
	return os;
}

/**
 * @fn	ostream &operator<< ( ostream &os, const dvec4 &V ) { os << "[ " << V.x << " " << V.y << " " << V.z << " " << V.w << " ]"; return os;
 *
 * @brief	Output stream for vec4.
 *
 * @param [in,out]	os	Output stream.
 * @param 		  	V 	The vector.
 *
 * @returns	The shifted result.
 */
ostream &operator << ( ostream &os, const dvec4 &V )
{
	os << "[ " << V.x << " " << V.y << " " << V.z << " " << V.w << " ]";
	return os;
}

/**
 * @fn	ostream &operator<< ( ostream &os, const dmat2 &M ) { os << " n"; for( int row = 0; row < 2; row++ ) { os << "| t"; for( int col = 0; col < 2; col++ ) { os << std::setw( 8 ) << std::setprecision( 4 ) << M[col][row] << " t";
 *
 * @brief	Output stream for mat2.
 *
 * @param [in,out]	os	Output stream.
 * @param 		  	M 	The matrix.
 *
 * @returns	The shifted result.
 */
ostream &operator << ( ostream &os, const dmat2 &M )
{
	os << "\n";
	for( int row = 0; row < 2; row++ ) {
		os << "|\t";
		for( int col = 0; col < 2; col++ ) {
			os << std::setw( 8 ) << std::setprecision( 4 ) << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
 * @fn	ostream &operator<< ( ostream &os, const dmat3 &M ) { os << " n"; for( int row = 0; row < 3; row++ ) { os << "| t"; for( int col = 0; col < 3; col++ ) { os << std::setw( 8 ) << std::setprecision( 4 ) << M[col][row] << " t";
 *
 * @brief	Output stream for mat3.
 *
 * @param [in,out]	os	Output stream.
 * @param 		  	M 	The matrix.
 *
 * @returns	The shifted result.
 */
ostream &operator << ( ostream &os, const dmat3 &M )
{
	os << "\n";
	for( int row = 0; row < 3; row++ ) {
		os << "|\t";
		for( int col = 0; col < 3; col++ ) {
			os << std::setw( 8 ) << std::setprecision( 4 ) << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
 * @fn	ostream &operator<< ( ostream &os, const dmat4 &M ) { os << " n"; for( int row = 0; row < 4; row++ ) { os << "| t"; for( int col = 0; col < 4; col++ ) { os << std::setw( 8 ) << std::setprecision( 4 ) << M[col][row] << " t";
 *
 * @brief	Output stream for mat4.
 *
 * @param [in,out]	os	Output stream.
 * @param 		  	M 	The matrix.
 *
 * @returns	The shifted result.
 */
ostream &operator << ( ostream &os, const dmat4 &M )
{
	os << "\n";
	for( int row = 0; row < 4; row++ ) {
		os << "|\t";
		for( int col = 0; col < 4; col++ ) {
			os << std::setw( 8 ) << std::setprecision( 4 ) << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}


// Give three vertices on the face of a polygon in counter clockwise 
// order calculates a normal vector for the polygon.
dvec3 findUnitNormal(dvec3 pZero, dvec3 pOne, dvec3 pTwo)
{
	return glm::normalize(glm::cross(pOne - pZero, pTwo - pOne));

} // end findUnitNormal