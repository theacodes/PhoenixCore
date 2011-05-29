/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "BMFontLoader.h"

using namespace phoenix;
using namespace std;
using namespace boost;

/* Loads a FNT file */
void BMFontLoader::load( const std::string& fnt_file ){
	fstream fh;
	string line;

	fh.open(fnt_file, fstream::in);

	if( !fh ) return;

	while( fh.good() ){
		getline( fh, line );
		
		//tokenize, parse.
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> sep(" =");
		tokenizer tokens(line, sep);

		for (tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it) {
			string token = *it;

			/* Load character data */
			if( token == "char" ){
				int id = 0;
				BitmapFont::Character c;

				for (++it; it != tokens.end(); ++it) {
					string name = *it; 
					if( name == "id" ){
						id = atoi( (*++it).c_str() );
					}
					else if( name == "x" ){
						c.x = atoi( (*++it).c_str() );
					}
					else if( name == "y" ){
						c.y = atoi( (*++it).c_str() );
					}
					else if( name == "width" ){
						c.width = atoi( (*++it).c_str() );
					}
					else if( name == "height" ){
						c.height = atoi( (*++it).c_str() );
					}
					else if( name == "xoffset" ){
						c.xoffset = atoi( (*++it).c_str() );
					}
					else if( name == "yoffset" ){
						c.yoffset = atoi( (*++it).c_str() );
					}
					else if( name == "xadvance" ){
						c.xadvance = atoi( (*++it).c_str() );
					}
				}
				
				if( id != 0 ){
					font->setCharacterProperties(id,c);
				}
				
				break;
			}

		}
	}

	fh.close();
}