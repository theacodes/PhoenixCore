#include "PhVertexLight.h"

using namespace phoenix;

PhVertexLight::PhVertexLight(PhVertexLightSystem* l, PhVector2d Position, PhColor c)
        : lsys(l), ambient(c), diffuse(c), specular(PhColor(127,127,127,255)), position(Position), catten(1.0f), latten(0.0f), qatten(0.0f), depth(0.0f)
{
    lsys->addLight(this);
}

PhVertexLight::~PhVertexLight()
{
    if (lsys)
    {
        lsys->removeLight(this);
    }
}

void PhVertexLight::setAmbient(PhColor a)
{
    ambient = a;
}
void PhVertexLight::setDiffuse(PhColor d)
{
    diffuse = d;
}
void PhVertexLight::setSpecular(PhColor s)
{
    specular = s;
}
void PhVertexLight::setPosition(PhVector2d p)
{
    position = p;
}
void PhVertexLight::setDepth(float d)
{
    depth = d;
}
void PhVertexLight::setConstantAttenuation(float c)
{
    catten = c;
}
void PhVertexLight::setLinearAttenuation(float l)
{
    latten = l;
}
void PhVertexLight::setQuadraticAttenation(float q)
{
    qatten = q;
}
void PhVertexLight::setAttenuation(float c, float l, float q)
{
    catten = c;
    latten = l;
    qatten = q;
}

PhColor PhVertexLight::getAmbient()
{
    return ambient;
}
PhColor PhVertexLight::getDiffuse()
{
    return diffuse;
}
PhColor PhVertexLight::getSpecular()
{
    return specular;
}
PhVector2d PhVertexLight::getPosition()
{
    return position;
}
float PhVertexLight::getDepth()
{
    return depth;
}
float PhVertexLight::getConstantAttenuation()
{
    return catten;
}
float PhVertexLight::getLinearAttenuation()
{
    return latten;
}
float PhVertexLight::getQuadraticAttenuation()
{
    return qatten;
}

void PhVertexLight::setLight(int n)
{

    GLfloat light_position[] = { position.getX(), position.getY(), 0.0f, 1.0f };
    GLfloat light_ambient[] = { ambient.getRed()/255.0f, ambient.getGreen()/255.0f, ambient.getBlue()/255.0f, ambient.getAlpha()/255.0f };
    GLfloat light_diffuse[] = { diffuse.getRed()/255.0f, diffuse.getGreen()/255.0f, diffuse.getBlue()/255.0f, diffuse.getAlpha()/255.0f };
    GLfloat light_specular[] = { specular.getRed()/255.0f, specular.getGreen()/255.0f, specular.getBlue()/255.0f, specular.getAlpha()/255.0f };

    glLightfv(GL_LIGHT0+n, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0+n, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0+n, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0+n, GL_POSITION, light_position);

    glLightf(GL_LIGHT0+n, GL_CONSTANT_ATTENUATION, catten);
    glLightf(GL_LIGHT0+n, GL_LINEAR_ATTENUATION, latten);
    glLightf(GL_LIGHT0+n, GL_QUADRATIC_ATTENUATION, qatten);

    glEnable(GL_LIGHT0+n);

}
