#include "PhRenderTexture.h"

PhRenderTexture::PhRenderTexture(PhRenderSystem* r): system(r)
{
    texture = new PhTexture(system->getTextureManager(),256,256);
}

PhRenderTexture::PhRenderTexture(PhRenderSystem* r, PhTexture* t): system(r), texture(t)
{
}

PhRenderTexture::~PhRenderTexture()
{
    delete texture;
}

void PhRenderTexture::setTexture(PhTexture* t)
{
    texture = t;
}

PhTexture* PhRenderTexture::getTexture()
{
    return texture;
}

void PhRenderTexture::startRender()
{

    // adjust viewport to texture dimension
    glViewport(0, 0, texture->getWidth(), texture->getHeight());

    // clear the screen
    glClearColor(0.f, 0.f, 0.f, 0.0f);

    // clear the color buffer & depth buffer.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}
void PhRenderTexture::endRender()
{

    // copy the framebuffer pixels to a texture
    glBindTexture(GL_TEXTURE_2D,texture->getTexture());			// Bind the texture

    // Copy Our ViewPort
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, texture->getWidth(), texture->getHeight(), 0);

    // clear the screen.
    glClearColor(0.0f, 0.0f, 0.0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // restore the viewport.

    glViewport(0,0,system->getScreenSize().getX(),system->getScreenSize().getY());

}
