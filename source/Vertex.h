/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHVERTEX_H__
#define __PHVERTEX_H__

#include "config.h"
#include "Vector2d.h"
#include "Color.h"

namespace phoenix
{

//! Texture Coordinates
class TextureCoords
{
public:
	float u, v, r, q;
	
	TextureCoords( float _u = 0.0f, float _v = 0.0f, float _r = 0.0f, float _q = 1.0f )
		: u(_u), v(_v), r(_r), q(_q)
	{}
};

//! Batch Vertex
/*!
	A very simple class that provides storage of position, color, and texture coordinate data for
	geometry. This class is used by BatchGeometry and BatchRender.
*/
class Vertex
{
public:

	//! U Texture coordinates
	TextureCoords tcoords;

	//! Color.
	Color color;
	
	//! Position.
	Vector2d position;
	
	Vertex( Vector2d _position = Vector2d(0,0), Color _color = Color(255,255,255), TextureCoords _t = TextureCoords(0,0) )
		: tcoords(_t), color( _color ), position( _position )
	{}
};

} //namespace phoenix

#endif // __PHVERTEX_H__