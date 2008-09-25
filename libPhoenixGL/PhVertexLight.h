#ifndef PhVertexLight_H
#define PhVertexLight_H

#include "PhVertexLightSystem.h"
#include "PhColor.h"
#include "PhVector2d.h"

using namespace phoenix;

class PhVertexLight
{
    public:
        PhVertexLight(PhVertexLightSystem* l, PhVector2d Position = PhVector2d(0.0f,0.0f), PhColor c = PhColor(255,255,255,255));
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

#endif // PhVertexLight_H
