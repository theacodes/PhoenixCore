#ifndef PhVertexLight_H
#define PhVertexLight_H

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
        PhVertexLight(PhVertexLightSystem* l, PhVector2d Position = PhVector2d(0.0f,0.0f), PhColor c = PhColor(255,255,255,255));

        //! Destructor.
        virtual ~PhVertexLight();

        void setAmbient(PhColor a);
        void setDiffuse(PhColor d);
        void setSpecular(PhColor s);
        void setPosition(PhVector2d p);
        void setDepth(float d);
        void setConstantAttenuation(float c);
        void setLinearAttenuation(float l);
        void setQuadraticAttenation(float q);
        void setAttenuation(float c, float l, float q);

        PhColor getAmbient();
        PhColor getDiffuse();
        PhColor getSpecular();
        PhVector2d getPosition();
        float getDepth();
        float getConstantAttenuation();
        float getLinearAttenuation();
        float getQuadraticAttenuation();

        void setLight(int n);


    protected:
        PhVertexLightSystem* lsys;
        PhColor ambient, diffuse, specular;
        PhVector2d position;
        float catten, latten, qatten, depth;

    private:
    };

}

#endif // PhVertexLight_H
