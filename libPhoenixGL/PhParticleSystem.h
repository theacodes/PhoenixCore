/*

Copyright (c) 2007, Jonathan Wayne Parrott.

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

#ifndef PHOENIXPPS
#define PHOENIXPPS

#include "PhSceneManager.h"

namespace phoenix
{

////////////////////////////////////////////////////////////////////////////////
// Particle container, constains information for each particle in the system
////////////////////////////////////////////////////////////////////////////////

struct PhParticle
{
    int x,y,hspeed,vspeed,lifeleft;
    float rot,rotspeed,scale;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Particle Type container, determines the properties particles will have when
// created
////////////////////////////////////////////////////////////////////////////////



struct PhParticleType
{
    int maxlife, minlife, maxhs, maxvs, minhs, minvs, minalpha, minred, minblue, mingreen;
    float minrs, maxrs, minscale, maxscale;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Emitter Definition
////////////////////////////////////////////////////////////////////////////////

class PhParticleEmitter : public PhSceneNode
{

protected:

    //max particles
    int maxparts;

    //particle type definition
    PhParticleType partype;

    //Image to be drawn
    PhTexture* image;

    //Free on destory, it clears the image from memory when this is destroyed
    bool fod;

    //Pointers to the scenemanger and system.
    PhSceneManager* smgr;
    PhRenderSystem* system;

    //Vector to hold our particles
    std::vector<PhParticle*> particles;

    //How many particles we have
    int particlecount;

    //random function
    template <class a_type> a_type random(a_type low,a_type high)
    {
        return (a_type(rand()) % (high - low + a_type(1)) + low);
    }

public:

    //construct and destruct
    PhParticleEmitter(PhSceneManager* s, PhTexture* i, PhParticleType pt, int p = 1, float d=0.0f, bool c=true);
    ~PhParticleEmitter();

    //set the system it belongs too (shold only be set by scenemanager)
    void setRenderSystem(PhRenderSystem* sys);

    //get particles
    int getParticles();
    int getMaxParticles();
    void setMaxParticles(int);

    //functions for taking   care of particles
    PhParticle* getParticle(int);
    void deleteParticle(int);

    //Following functions set and get the properties of the particle type definition

    //set and get max  and min hspeed and vspeed
    int getMaxHSpeed (void);
    int getMaxVSpeed (void);
    void setMaxHSpeed(int a);
    void setMaxVSpeed(int a);
    int getMinHSpeed (void);
    int getMinVSpeed (void);
    void setMinHSpeed(int a);
    void setMinVSpeed(int a);

    //set and get max and minlife
    int getMaxLife();
    void setMaxLife(int);
    int getMinLife();
    void setMinLife(int);

    //set and get max and min rotation speed
    float getMaxRotationSpeed();
    void setMaxRotationSpeed(float a);
    float getMinRotationSpeed();
    void setMinRotationSpeed(float a);

    //set and get the max color stuff
    void setMinAlpha(int a);
    void setMinRed(int a);
    void setMinGreen(int a);
    void setMinBlue(int a);
    int getMinAlpha();
    int getMinRed();
    int getMinGreen();
    int getMinBlue();

    //set and get the max and min scale
    void setMaxScale(float a);
    void setMinScale(float a);
    float getMaxScale();
    float getMinScale();

    //set and get image
    bool setTexture(PhTexture* img);
    PhTexture* getTexture();

    //set Free on Destory
    void setFod(bool a);

    //Obviously, these should be definted by the emitter types

    //PreRender function (Should only be called by scene manager)
    void onPreRender()
    {}

    //Render function (should only be called by scene manager)
    void onRender()
    {}

    //Postrender (should only be called by scene manager)
    void onPostRender()
    {}

};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//This is the effector definition
////////////////////////////////////////////////////////////////////////////////

class PhParticleEffector : public PhSceneNode
{

protected:

    //Particle Emitter we're effecting
    PhParticleEmitter* emitter;

    //Scenemanager
    PhSceneManager* smgr;

public:

    PhParticleEffector(PhSceneManager*, PhParticleEmitter*);
    ~PhParticleEffector();

    virtual void onPreRender()
    {}
    virtual void onRender()
    {}
    virtual void onPostRender()
    {}

};

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// NOTE TO SELF: Put gun to head, and pull trigger before programming a particle
// system ever again.
////////////////////////////////////////////////////////////////////////////////

#endif
