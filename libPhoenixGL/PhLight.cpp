#include "PhLight.h"

using namespace phoenix;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	All we have to do is add the light.
*/
PhLight::PhLight(PhLightManager* l, PhTexture* t, PhVector2d p, PhColor c, PhVector2d s):
	lmgr(l), texture(t), position(p), color(c), scale(s)
{
    lmgr->addLight(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Dtor
	All we have to do is remove the light from the list.
*/
PhLight::~PhLight()
{
    lmgr->removeLight(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Draw function.
	All we have to do here is draw the texture
	just like we normally would with a node.
*/
void PhLight::draw()
{
    lmgr->getSceneManager()->getRenderSystem()->drawTexture(texture,position-(texture->getSize()/2.0f),0.0f,0.0f,scale,color);
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
