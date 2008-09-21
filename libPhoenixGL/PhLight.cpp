#include "PhLight.h"

PhLight::PhLight(PhLightSystem* l, PhVector2d Position, PhColor c)
        : lsys(l), ambient(c), diffuse(c), specular(PhColor(127,127,127,255)), position(Position), catten(1.0f), latten(0.0f), qatten(0.0f), depth(0.0f)
{
    lsys->addLight(this);
}

PhLight::~PhLight()
{
    if (lsys)
    {
        lsys->removeLight(this);
    }
}

void PhLight::setAmbient(PhColor a)
{
    ambient = a;
}
void PhLight::setDiffuse(PhColor d)
{
    diffuse = d;
}
void PhLight::setSpecular(PhColor s)
{
    specular = s;
}
void PhLight::setPosition(PhVector2d p)
{
    position = p;
}
void PhLight::setDepth(float d)
{
    depth = d;
}
void PhLight::setConstantAttenuation(float c)
{
    catten = c;
}
void PhLight::setLinearAttenuation(float l)
{
    latten = l;
}
void PhLight::setQuadraticAttenation(float q)
{
    qatten = q;
}
void PhLight::setAttenuation(float c, float l, float q)
{
    catten = c;
    latten = l;
    qatten = q;
}

PhColor PhLight::getAmbient()
{
    return ambient;
}
PhColor PhLight::getDiffuse()
{
    return diffuse;
}
PhColor PhLight::getSpecular()
{
    return specular;
}
PhVector2d PhLight::getPosition()
{
    return position;
}
float PhLight::getDepth()
{
    return depth;
}
float PhLight::getConstantAttenuation()
{
    return catten;
}
float PhLight::getLinearAttenuation()
{
    return latten;
}
float PhLight::getQuadraticAttenuation()
{
    return qatten;
}

void PhLight::setLight(int n)
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
