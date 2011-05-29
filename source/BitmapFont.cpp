/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "BitmapFont.h"

using namespace phoenix;
using namespace std;
using namespace boost;

BatchGeometryPtr BitmapFont::drawText( const string& s, const Vector2d& p )
{

	BatchGeometryPtr geom = new BatchGeometry( renderer, GL_QUADS, getTexture(), getGroup(), getDepth() );
	geom->setImmediate( true );

    float culmative_x = 0;

    //Now for the fun part.
    for( unsigned int i = 0; i < s.size(); ++i)
    {

		const unsigned char glyph = s[i];
		Character c = characters[glyph];

		float tw = (float)getTexture()->getWidth();
		float th = (float)getTexture()->getHeight();
		float u = c.x/tw;
		float v = c.y/th;
		float u2 = (c.x + c.width) / tw;
		float v2 = (c.y + c.height) / th;
		float x = culmative_x + ( c.xoffset * scale.getX() );
		culmative_x += c.xadvance * scale.getX();
		float y = 0 + c.yoffset * scale.getY();
		float w = c.width * scale.getX();
		float h = c.height * scale.getY();

		// Top Left Vertex.
		geom->addVertex( Vertex(
			Vector2d( x, y ), 
			color, 
			TextureCoords( u, v) 
			));
		// Top Right
		geom->addVertex( Vertex(
			Vector2d( x+w, y ), 
			color, 
			TextureCoords( u2, v ) 
			));
		// Bottom Right
		geom->addVertex( Vertex(
			Vector2d( x+w, y+h ), 
			color, 
			TextureCoords( u2, v2 ) 
			));
		// Bottom Left
		geom->addVertex( Vertex(
			Vector2d( x, y+h ), 
			color,
			TextureCoords( u, v2 ) 
			));
    }

	geom->translate( p );

	return geom;
}
