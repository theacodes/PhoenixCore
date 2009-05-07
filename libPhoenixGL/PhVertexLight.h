/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef __PhVertexLight_H__
#define __PhVertexLight_H__

#include "PhVertexLightSystem.h"
#include "PhColor.h"
#include "PhVector2d.h"

namespace phoenix
{

    //! Vertex-based light class.
    /*!
        Provides an interface to opengl vertex lighting. This is not the perferred method of lighting in
        phoenix or 2d graphics, it's highly suggested that you use phoenix::PhLight instead. This class is
        here for completeness and for 3d functionality.
        \sa phoenix::PhVertexLightSystem, phoenix::PhLight
    */
    class PhVertexLight
    {
    public:

        //! Constructor.
        /*!
            Creates a new light and binds it to the lighting system.
            \param l A pointer to the light system (usually obtained from the render system).
            \param Position Position of the light.
            \param c Color of the light.
        */
        PhVertexLight(PhVertexLightSystem* l, const PhVector2d& Position = PhVector2d(0.0f,0.0f), const PhColor& c = PhColor(255,255,255,255));

        //! Destructor.
        virtual ~PhVertexLight();

        //! Set ambient
        /*!
			Set the ambient color of the light.
			\sa getAmbient()
        */
        inline void setAmbient(const PhColor& a) { ambient = a; }

        //! Set diffuse
        /*!
			Set the diffuse color of the light.
			\sa getDiffuse()
        */
        inline void setDiffuse(const PhColor& d) { diffuse = d; }

        //! Set specular
        /*!
			Set the specular color of the light.
			\sa getSpecular()
        */
        inline void setSpecular(const PhColor& s) { specular = s; }

        //! Set position
        /*!
			Set the location of the light.
			\sa getPosition()
        */
        inline void setPosition(const PhVector2d& p) { position = p; }

        //! Set depth
        /*!
			Sets the depth of the light.
			\sa getDepth()
        */
        inline void setDepth(const float& d) { depth = d; }

        //! Set constant attenuation
        /*!
			Sets the constant attenuation.
			\sa getConstantAttenuation()
        */
        inline void setConstantAttenuation(const float& c) { catten = c; }

        //! Set linear attenuation
        /*!
			Sets the linear attenuation.
			\sa getLinearAttenuation()
        */
        inline void setLinearAttenuation(const float& l) { latten = l; }

        //! Set quadratic attenuation
        /*!
			Sets the quadratic attenuation.
			\sa get()
        */
        inline void setQuadraticAttenuation(const float& q) { qatten = q; }

        //! Set attenuation
        /*!
			Sets constant, linear, and quadratic attenuation. OpenGL
			will handle all the gory math involved, if you want more
			reference on this please consult the red book.
			\param c Constant attenuation
			\param l Linear attenuation
			\param q Quadratic attenuation
        */
        inline void setAttenuation(const float& c, const float& l, const float& q)
        {
        	catten = c;
        	latten = l;
        	qatten = q;
        }

        //! Get Ambient color
        inline const PhColor& getAmbient() const { return ambient; }

        //! Get Diffuse color
        inline const PhColor& getDiffuse() const { return diffuse; }

        //! Get Specular color
        inline const PhColor& getSpecular() const { return specular; }

        //! Get light position
        inline const PhVector2d& getPosition() const { return position; }

        //! Get light depth
        inline const float& getDepth() const { return depth; }

        //! Get constant attenuation
        inline const float& getConstantAttenuation() const { return catten; }

        //! Get linear attenuation
        inline const float& getLinearAttenuation() const { return latten; }

        //! Get quadratic attenuation
        inline const float& getQuadraticAttenuation() const { return qatten; }

        virtual void setLight(const int& n);


    protected:
        PhVertexLightSystem* lsys;
        PhColor ambient, diffuse, specular;
        PhVector2d position;
        float catten, latten, qatten, depth;

    private:
    };

}

#endif // PhVertexLight_H
