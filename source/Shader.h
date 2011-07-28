/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHSHADER_H__
#define __PHSHADER_H__

#include <string>
#include "config.h"
#include "Resource.h"

namespace phoenix
{


/*! Shader Interface
*/
class Shader
	: public Resource
{

public:

	Shader( ResourceManager& _r )
		: Resource(_r, ERT_SHADER), vertex_shader(0), fragment_shader(0), shader_program(0)
	{}

	virtual ~Shader(){
	}

	/*! Checks if the shader is ready */
	inline const bool ready(){
		return ( GLEW_VERSION_2_0 && vertex_shader && fragment_shader && shader_program );
	}

	/*! Makes the shader the currently active shader program, will activate the default (ffp) program if this shader isn't ready.
	*/
	void activate();

	/*! Activates FFP
	*/
	void deactivate();


	/*! Loads shader files, compiles them and links them
	*/
	bool load( const std::string& vertex_file, const std::string& fragment_file );

	/*! Loads shaders from a string, compiles, and links them */
	bool loadFromString( const std::string& vertex_source, const std::string& fragment_source );

	/*! Compiles a specific shader, usually not called directly
	*/
	GLuint compile( GLenum _type, const std::string& _source );

	/*! Links the shader program
	*/
	GLuint link();

	inline const std::string& getErrors(){
		return errors;
	}

protected:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;
	std::string errors;

	/* Adds a string to the error log */
	void addError( const std::string& _error );

	/*! Retrieves errors from OpenGL */
	void show_info_log(
		GLuint object,
		PFNGLGETSHADERIVPROC glGet__iv,
		PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
	);

	/* Reads and entire file and returns it as a string */
	const std::string getFileContents( const std::string& file_name );

}; // class Shader

//! Friendly Shader pointer
typedef boost::intrusive_ptr<Shader> ShaderPtr;

} //namespace phoenix
#endif // __PHSHADER_H__
