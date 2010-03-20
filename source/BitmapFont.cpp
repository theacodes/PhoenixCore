/*

Copyright (c) 2009, Jonathan Wayne Parrott

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

    static float ratio = 1.0f/16.0f;

    //Now for the fun part.
    for( unsigned int i = 0; i < s.size(); ++i)
    {

		const unsigned char glyph = s[i];

		// Top Left Vertex.
		geom->addVertex( Vertex(
			Vector2d( (i*spacing)*scale.getX(), 0 ), 
			color, 
			TextureCoords( glyph*ratio, floor(glyph/16.0f) * ratio) 
			));
		// Top Right
		geom->addVertex( Vertex(
			Vector2d( (((i)*spacing)*scale.getX())+(16*scale.getX()), 0 ), 
			color, 
			TextureCoords( (glyph+1)*ratio, floor(glyph/16.0f) * ratio ) 
			));
		// Bottom Right
		geom->addVertex( Vertex(
			Vector2d( (((i)*spacing)*scale.getX())+(16*scale.getX()),(16*scale.getY()) ), 
			color, 
			TextureCoords( (glyph+1)*ratio, (floor(glyph/16.0f) * ratio)+ratio ) 
			));
		// Bottom Left
		geom->addVertex( Vertex(
			Vector2d( (i*spacing)*scale.getX(),(16*scale.getY()) ), 
			color,
			TextureCoords( glyph*ratio, (floor(glyph/16.0f) * ratio)+ratio ) 
			));
    }

	geom->translate( p );

	return geom;
}
