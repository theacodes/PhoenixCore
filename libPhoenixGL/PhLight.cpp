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

PhTexture* PhLight::getTexture() const
{
    return texture;
}

void PhLight::setTexture(PhTexture* t)
{
    texture = t;
}

const PhVector2d& PhLight::getPosition() const
{
    return position;
}

void PhLight::setPosition(const PhVector2d& p)
{
    position = p;
}

const PhColor& PhLight::getColor() const
{
    return color;
}

void PhLight::setColor(const PhColor& c)
{
    color = c;
}

const PhVector2d& PhLight::getScale() const
{
    return scale;
}

void PhLight::setScale(const PhVector2d& s)
{
    scale = s;
}
