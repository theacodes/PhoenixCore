#include "PhLight.h"

using namespace phoenix;

PhLight::PhLight(PhLightManager* l, PhTexture* t, PhVector2d p, PhColor c, float s): lmgr(l), texture(t), position(p-PhVector2d(63.64f,63.64f)), color(c), scale(s)
{
    lmgr->addLight(this);
}

PhLight::~PhLight()
{
    lmgr->removeLight(this);
}

void PhLight::draw()
{
    lmgr->getSceneManager()->getRenderSystem()->drawTexture(texture,position,0.0f,0.0f,scale,color);
}

PhTexture* PhLight::getTexture()
{
    return texture;
}

void PhLight::setTexture(PhTexture* t)
{
    texture = t;
}

PhVector2d PhLight::getPosition()
{
    //compensate for the fact that our method skews positions slightly.
    return position+PhVector2d(63.64f,63.64f);
}

void PhLight::setPosition(PhVector2d p)
{
    //compensate for the fact that our method skews positions slightly.
    position = p-PhVector2d(63.64f,63.64f);
}

PhColor PhLight::getColor()
{
    return color;
}

void PhLight::setColor(PhColor c)
{
    color = c;
}

float PhLight::getScale()
{
    return scale;
}

void PhLight::setScale(float s)
{
    scale = s;
}
