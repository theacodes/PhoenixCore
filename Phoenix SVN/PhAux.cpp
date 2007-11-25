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

#include "PhAux.h"

using namespace phoenix;
using namespace aux;

///random function
template <class a_type> a_type phoenix::aux::random(a_type low,a_type high)
{
    return (a_type(rand()) % (high - low + a_type(1)) + low);
}

///Build collision data from tilemap
///The second last argument is the list of vectors with the x being tileindices that are solid,
///and the y being the geometric object used to represent it
void phoenix::aux::buildCollisionDataFromTileMap(PhTileMap* tilemap,PhPolygonCollisionHandler* colhandle,std::vector<PhVector2d> solidtiles,std::vector<PhPolygon> geometry,int type)
{
    for (int i = 0; i< tilemap->getMapSize().getY(); i++)
    {
        for (int j = 0; j < tilemap->getMapSize().getX(); j++)
        {
            for (int k = 0; k<solidtiles.size(); k++)
            {
                if (tilemap->getTile(PhVector2d(j,i))==int(solidtiles[k].getX()))
                {
                    PhPolygon pa = geometry[int(solidtiles[k].getY())]; //holy cow that's a long line
                    pa.setPosition(PhVector2d(j*tilemap->getTileSize().getX(),i*tilemap->getTileSize().getY())+PhVector2d(tilemap->getTileSize().getX()/2.0f,tilemap->getTileSize().getY()/2.0f));
                    colhandle->addStaticGeometry(pa,type);
                }
            }
        }
    }
}

///This is a global varible class, simply put, you can store varibles here that can be accessed by any program.

GlobalVariables::GlobalVariables()
{};

GlobalVariables::~GlobalVariables()
{
    variables.clear();
}

void GlobalVariables::setVariable(string name, any val)
{
    variables[name] = val;
}

any GlobalVariables::getVariable(string name)
{
    return variables[name];
}

void GlobalVariables::clear()
{
    variables.clear();
}

///This is a debug manager, basically you can write strings to it and it will write to a file.
DebugManager::DebugManager(string f)
{
    file = fopen(f.c_str(),"w"); //open it
}
DebugManager::~DebugManager()
{
    fclose(file);
}

void DebugManager::addString(string s)
{
    if (file)
    {
        s += "\n";
        fputs(s.c_str(),file);
        fflush(file);
    }
}

