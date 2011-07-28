/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#ifndef __PHSHADERGROUPSTATE_H__
#define __PHSHADERGROUPSTATE_H__

#include "Shader.h"
#include "GroupState.h"
#include "BatchRenderer.h"

namespace phoenix{

//! GroupState for automatically activating and deactivating a Shader.
/*!
	This group state automatically activates a shader for  particular group of geometry
*/
class ShaderGroupState
	: public GroupState
{

public:

	ShaderGroupState( ShaderPtr _s )
		: shader(_s)
	{};
	virtual ~ShaderGroupState(){};

	//! Begin render state.
	/*!
		calls activate for the shader
	*/
	virtual void begin( BatchRenderer& r ){
		if( shader ) shader->activate();
	}

	//! End render state.
	/*!
		calls deactivate on the shader.
	*/
	virtual void end( BatchRenderer& r ){
		if( shader ) shader->deactivate();
	}

	//! Sets the shader. If an empty pointer, the renderer will use the FFP
	inline void setShader( ShaderPtr _s ) { shader = _s; }

	//! Get the shader.
	inline ShaderPtr getShader(){ return shader; }

protected:

	ShaderPtr shader;

}; // class

//! Friendly name for GroupState objects.
typedef boost::shared_ptr<ShaderGroupState> ShaderGroupStatePtr;

} //namespace phoenix

#endif //__PHSHADERGROUPSTATE_H__