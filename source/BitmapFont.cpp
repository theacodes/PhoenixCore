/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include <algorithm>
#include "BitmapFont.h"
#include "BMFontLoader.h"

using namespace phoenix;
using namespace std;
using namespace boost;

/*
	Easy constructor
*/
BitmapFont::BitmapFont( RenderSystem& _r, std::string _fnt )
	: Font( _r, 3), pages(), characters(256), kernings(), line_height(16.0f), spacing( 10.0f )
{
	std::fill( characters.begin(), characters.end(), BitmapFont::Character() );
	load( _r, _fnt );
}


/*
	Loading routine
*/
void BitmapFont::load( RenderSystem& _r, std::string _fnt ){
	if( _fnt == "" ) return;

	BMFontLoader ldr(_r, this);
	ldr.load(_fnt);
}

/*
	Dimensions calculation
*/
const Vector2d BitmapFont::getTextDimensions( const std::string& _s, const Vector2d& _scale )
{
	// Set up variables
	Vector2d old_scale = scale;
	if( _scale != Vector2d(0,0) ) scale = _scale;
    float culmative_x = 0.0f;
	float culmative_y = 0.0f;
	float max_x = 0.0f;

    //Iterate over each character, calculating size
    for( unsigned int i = 0; i < _s.size(); ++i)
    {

		const unsigned char glyph = _s[i];

		if( glyph == '\n' ){
			culmative_y += line_height * scale.getY();
			max_x = max( max_x, culmative_x );
			culmative_x = 0;
			continue;
		}

		Character c = characters[glyph];

		float x = culmative_x + ( c.xoffset * scale.getX() );
		float y = culmative_y + c.yoffset * scale.getY();
		float w = c.width * scale.getX();
		float h = c.height * scale.getY();

		//adjust culmative x value
		float x_inc = (float) c.xadvance;
		if( i < _s.size()-1 ){
			x_inc += (float) getKerning( glyph, _s[i+1] );
		}
		culmative_x += x_inc * scale.getX();
    }

	//Add one line of height. We do this because we want the total height and the culmative y is (at this point) the y at the *top* of the last line.
	culmative_y += line_height * scale.getY();

	//reset state
	scale = old_scale;

	return Vector2d(max_x,culmative_y);
}

/*
	Text drawing routine
*/
BatchGeometryPtr BitmapFont::drawText( const string& s, const Vector2d& p, const Color& _c, const Vector2d& _scale )
{

	// setup pages
	unsigned int page_count = pages.size();
	std::vector<BatchGeometryPtr> geoms;

	// return empty geom if we can't draw
	if( ! getTexture() || page_count == 0 ){
		return new BatchGeometry( *renderer, GL_QUADS, getTexture(), getGroup(), getDepth() );
	}

	// build a geom for each page.
	for( unsigned int i = 0; i < page_count; i++ ){
		BatchGeometryPtr geom = new BatchGeometry( *renderer, GL_QUADS, pages[i], getGroup(), getDepth() );
		geom->setImmediate( true );
		geoms.push_back( geom );
	}

	// Set up variables
	Vector2d old_scale = scale;
	if( _scale != Vector2d(0,0) ) scale = _scale;
    float culmative_x = 0;
	float culmative_y = 0;
	float tw = (float)getTexture()->getWidth();
	float th = (float)getTexture()->getHeight();

    //Now for the fun part.
    for( unsigned int i = 0; i < s.size(); ++i)
    {

		const unsigned char glyph = s[i];

		if( glyph == '\n' ){
			culmative_y += line_height * scale.getY();
			culmative_x = 0;
			continue;
		}

		Character c = characters[glyph];

		// get the geom for the active page.
		BatchGeometryPtr geom = geoms[c.page];

		// calculate stuff
		float u = c.x/tw;
		float v = c.y/th;
		float u2 = (c.x + c.width) / tw;
		float v2 = (c.y + c.height) / th;
		float x = culmative_x + ( c.xoffset * scale.getX() );
		float y = culmative_y + c.yoffset * scale.getY();
		float w = c.width * scale.getX();
		float h = c.height * scale.getY();

		//adjust culmative x value
		float x_inc = (float) c.xadvance;
		if( i < s.size()-1 ){
			x_inc += (float) getKerning( glyph, s[i+1] );
		}
		culmative_x += x_inc * scale.getX();

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

	//Create a composite
	BatchGeometryCompositePtr geom_composite = new BatchGeometryComposite( *renderer );
	geom_composite->setImmediate( true );
	geom_composite->getChildren() = geoms;

	//Translate, colorize the composite, and return it.
	geom_composite->translate( p );
	geom_composite->colorize( _c );

	//reset state
	scale = old_scale;

	return geom_composite;
}
