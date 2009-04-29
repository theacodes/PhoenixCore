#include "PhVertexLight.h"

using namespace phoenix;

PhVertexLight::PhVertexLight(PhVertexLightSystem* l, const PhVector2d& Position, const PhColor& c)
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

void PhVertexLight::setLight(const int& n)
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
