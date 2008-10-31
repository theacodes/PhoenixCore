#include "PhLight.h"

using namespace phoenix;

PhLight::PhLight(PhLightManager* l, PhTexture* t, PhVector2d p, PhColor c, PhVector2d s): lmgr(l), texture(t), position(p), color(c), scale(s)
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
    return position;
}

void PhLight::setPosition(PhVector2d p)
{
    position = p;
}

PhColor PhLight::getColor()
{
    return color;
}

void PhLight::setColor(PhColor c)
{
    color = c;
}

PhVector2d PhLight::getScale()
{
    return scale;
}

void PhLight::setScale(PhVector2d s)
{
    scale = s;
}
