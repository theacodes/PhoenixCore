/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHSHADER_H__
#define __PHSHADER_H__

#include <string>
#include <sstream>
#include <fstream>
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
	bool ready(){
		return ( GLEW_VERSION_2_0 && vertex_shader && fragment_shader && shader_program );
	}

	/*! Makes the shader the currently active shader program, will activate the default (ffp) program if this shader isn't ready.
	*/
	void activate(){
		if( !GLEW_VERSION_2_0 ) return;
		if( shader_program ){
			glUseProgram(shader_program);
		} else {
			glUseProgram( 0 );
		}
	};

	/*! Activates FFP
	*/
	void deactivate(){
		if( !GLEW_VERSION_2_0 ) return;
		glUseProgram( 0 );
	}


	/*! Loads shader files, compiles them and links them
	*/
	bool load( const std::string& vertex_file, const std::string& fragment_file ){
		vertex_shader = compile( GL_VERTEX_SHADER, getFileContents( vertex_file ) );
		fragment_shader = compile( GL_FRAGMENT_SHADER, getFileContents( fragment_file ) );

		if( !vertex_shader || ! fragment_shader ) return false;

		shader_program = link();

		if( !shader_program ) return false;

		return true;
	}

	/*! Loads shaders from a string, compiles, and links them */
	bool loadFromString( const std::string& vertex_source, const std::string& fragment_source ){
		vertex_shader = compile( GL_VERTEX_SHADER, vertex_source );
		fragment_shader = compile( GL_FRAGMENT_SHADER, fragment_source );

		if( !vertex_shader || ! fragment_shader ) return false;

		shader_program = link();

		if( !shader_program ) return false;

		return true;
	}

	/*! Compiles a specific shader, usually not called directly
	*/
	GLuint compile( GLenum _type, const std::string& _source ){
		if( !GLEW_VERSION_2_0 ) return 0;

		// create a shader object
		GLuint shader = glCreateShader(_type);

		// compile it
		const GLchar* src = _source.c_str();
		const GLint size = _source.size(); 
		glShaderSource(shader, 1, &src, &size);
		glCompileShader(shader);

		//check it
		GLint shader_ok;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
		if (!shader_ok) {
			addError("Failed to compile shader object:");
			show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	/*! Links the shader program
	*/
	GLuint link(){
		if( !GLEW_VERSION_2_0 ) return 0;
		GLint program_ok;

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
		if (!program_ok) {
			addError("Failed to link shader program:");
			show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
			glDeleteProgram(program);

			shader_program = 0;
			return 0;
		} else {
			shader_program = program;
			return program;
		}
	}

	const std::string& getErrors(){
		return errors;
	}

protected:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;
	std::string errors;

	/* Adds a string to the error log */
	void addError( const std::string& _error ){
		errors += _error + std::string("\n");
	}

	/*! Retrieves errors from OpenGL */
	void show_info_log(
		GLuint object,
		PFNGLGETSHADERIVPROC glGet__iv,
		PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
	)
	{
		GLint log_length;
		char *log;

		glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
		log = (char *)malloc(log_length);
		glGet__InfoLog(object, log_length, NULL, log);
		addError(log);
		free(log);
	}

	/* Reads and entire file and returns it as a string */
	const std::string getFileContents( const std::string& file_name ){
		std::ifstream file;
		file.open( file_name.c_str(), std::ios::in );

		if( !file.is_open() || !file.good() ) return std::string("");

		std::stringstream buffer;
		buffer << file.rdbuf();

		return buffer.str();
	}

}; // class Shader

//! Friendly BitmapFont pointer
typedef boost::intrusive_ptr<Shader> ShaderPtr;

} //namespace phoenix
#endif // __PHSHADER_H__
