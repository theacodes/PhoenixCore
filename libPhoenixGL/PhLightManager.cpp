#include "PhLightManager.h"

using namespace phoenix;

PhLightManager::PhLightManager(PhSceneManager* s, PhVector2d ts) : smgr(s)
{
    PhTexture* target = new PhTexture(smgr->getRenderSystem()->getTextureManager(), (int)ts.getX(), (int)ts.getY());
    rtexture = new PhRenderTexture(smgr->getRenderSystem(), target);
}

PhLightManager::~PhLightManager()
{
    clearLights();
}

void PhLightManager::addLight(PhLight* l)
{
    lights.push_back(l);
}

void PhLightManager::removeLight(PhLight* l)
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i] == l)
        {
            lights.erase(lights.begin()+i,lights.begin()+i+1);
        }
    }
}

void PhLightManager::clearLights()
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i]!=NULL)
        {
            delete lights[i];
        }
    }
    lights.clear();
}

void PhLightManager::generateBuffer()
{
    rtexture->startRender();

    smgr->getRenderSystem()->setBlendMode(GL_SRC_ALPHA,GL_ONE);

    //smgr->getView()->setGLView();

    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i]!=NULL)
        {
            lights[i]->draw();
        }
    }

    smgr->getRenderSystem()->setDefaultBlendMode();

    rtexture->endRender();

}

void PhLightManager::renderBuffer( float depth )
{

    smgr->getRenderSystem()->setBlendMode(GL_DST_COLOR, GL_ZERO);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glScalef(1.0f/smgr->getView()->getScale(),1.0f/smgr->getView()->getScale(),1.0f);

    glTranslatef(smgr->getView()->getX(),smgr->getView()->getY(),depth);

    glEnable(GL_TEXTURE_2D); //enable textures

    rtexture->getTexture()->bindTexture(); //bind the texture.

    //get our width and height
    float width = smgr->getRenderSystem()->getScreenSize().getX();
    float height = smgr->getRenderSystem()->getScreenSize().getY();

    //colors
    GLuint color = PhColor(255,255,255,255).toGLColor();
    GLuint colorarray[] = {color,color,color,color};

    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};

    //vertices
    GLfloat vertices[] =  {0.0f,0.0f,0.0f,
                           width,0.0f,0.0f,
                           width,height,0.0f,
                           0.0f,height,0.0f
                          };
    GLfloat tcoords[] = {
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f};

    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    smgr->getRenderSystem()->drawIndexedTriangleList(vertices,normals,tcoords,colorarray,indexlist, 2 );

    //restore our matricies.

    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    smgr->getRenderSystem()->setDefaultBlendMode();

}

PhTexture* PhLightManager::getBuffer() const
{
    return rtexture->getTexture();
}

PhSceneManager* PhLightManager::getSceneManager() const
{
    return smgr;
}
