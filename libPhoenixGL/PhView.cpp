/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

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

#include "PhView.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////

PhView::PhView(PhRenderSystem* s, const PhVector2d& p)
	: pos(p), rot(0.0f), scale(1.0f,1.0f), system(s)
{
}

////////////////////////////////////////////////////////////////////////////////
// Set the view to this.
////////////////////////////////////////////////////////////////////////////////

void PhView::setGLView()
{

    float x = pos.getX();
    float y = pos.getY();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glScalef(scale.getX(),scale.getY(),1.0f);

    glTranslatef(-x + (system->getScreenSize().getX()/2.0f),-y + (system->getScreenSize().getY()/2.0f),0.0f);

    glRotatef(rot,0.0f,0.0f,1.0f);

    glTranslatef(-(system->getScreenSize().getX()/2.0f),-(system->getScreenSize().getY()/2.0f),0.0f);

}
