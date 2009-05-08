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

#include "PhPolygonCollision.h"
#include <vector>

using namespace phoenix;
using namespace std;

///////////////////////////////////////////////

//defualt constructor
PhPolygonCollisionHandler::PhPolygonCollisionHandler()
{
}

//destructor
PhPolygonCollisionHandler::~PhPolygonCollisionHandler()
{
    //remove all the nodes........
    for (unsigned int i=0;i<colobjs.size();i++)
    {
        if (colobjs[i]!=NULL)
        {
            delete colobjs[i];
        }
    }
    colobjs.clear();
    level.clear();
}

///
///user-mode functions for collision detections
///

///polygon to polygon, can be called if you don't want to use collision object but just want some simple tests
PhCollisionData PhPolygonCollisionHandler::isColliding(PhPolygon A, PhPolygon B)
{

    PhVector2d sep; //separation vector
    float t; //serpation mag

    if (PolygonCollision(A,B,sep,t))
    {
        PhCollisionData d;
        d.collision = true;
        d.sep = sep;
        d.sepmag = t;
        return d;
    }
    else
    {
        PhCollisionData d;
        d.collision = false;
        return d;
    }
}

///Collision object to static geom, performs callbacks
///can be called directly, but this function is called by testObjectCollisions
void PhPolygonCollisionHandler::testObjectCollidingStatic(PhCollisionObject* A)
{
    float t; //seperation mag
    PhVector2d s; //seperation normal
    for (unsigned int i = 0; i < level.size(); i++) //walk through each static geom object
    {
        if (PolygonCollision(level[i].polygon,*(A->getPolygon()),s,t)) //test collision
        {
            PhCollisionData d; //collision data
            d.collision = true;
            d.sep = s;
            d.sepmag = t;
            d.objA = *A;
            //make a object out of the static geometry
            d.objB = PhCollisionObject((&level[i].polygon),(level[i].type),NULL,NULL);
            if((A->getCallback())!=NULL){(A->getCallback())(d);} //call A's callback
        }
    }
}

///Collision object to collision object, calls both callbacks for the objects.
///can be called directly, but this function is called by testObjectCollisions
bool PhPolygonCollisionHandler::isColliding(PhCollisionObject* A, PhCollisionObject* B)
{
    float t; //seperation mag
    PhVector2d s; //seperation normal
    if (PolygonCollision(*(A->getPolygon()),*(B->getPolygon()),s,t))
    { //test collision
        PhCollisionData d; //collision data
        d.collision = true; //we collided, so true
        d.sep = -s;
        d.sepmag = t;
        d.objA = *A;
        d.objB = *B;
        if((A->getCallback())!=NULL){(A->getCallback())(d);} //call A's callback
        //for object B, we make sure that
        //1) A is always equal to the object's collision obj
        //2) Seperation vector is always correct
        d.objA = *B;
        d.objB = *A;
        d.sep = s;
        if((B->getCallback())!=NULL){(B->getCallback())(d);} //call B's callback

        return true;
    }
    return false;
}

///This functions tests all the collision objects against each other and against the
///Static geometry, it performs callbacks.
void PhPolygonCollisionHandler::testCollisions(){

    for(unsigned int i = 0; i < colobjs.size(); i++){

        //test against all other objects
        for(unsigned int j = i; j < colobjs.size(); j++){
            isColliding(colobjs[i],colobjs[j]);
        }

        //test against static geometry
        testObjectCollidingStatic(colobjs[i]);

    }

}


///these functions add and remove objects from the list
void PhPolygonCollisionHandler::addObject(PhCollisionObject* a)
{
    colobjs.push_back(a);
}

void PhPolygonCollisionHandler::removeObject(PhCollisionObject* a)
{
    for (unsigned int i=0;i<colobjs.size();i++)
    {
        if (colobjs[i]==a)
        {
            colobjs.erase(colobjs.begin()+i);
            break;
        }
    }
}

///these functions add and remove static geometry

//add static geometry given a polygon and a type (type 1 usually means a solid block, and is the default)
void PhPolygonCollisionHandler::addStaticGeometry(PhPolygon p, int t)
{
    PhStaticGeometry sg;
    sg.polygon = p;
    sg.type = t;
    level.push_back(sg);
}

//add static geometry
void PhPolygonCollisionHandler::addStaticGeometry(PhStaticGeometry g)
{
    level.push_back(g);
}

//remove static geometry
void PhPolygonCollisionHandler::removeStaticGeometry(PhStaticGeometry g)
{
    for (unsigned int i = 0; i < level.size(); i++)
    {
        if (level[i] == g)
        {
            level.erase(level.begin()+i);
            break;
        }
    }
}

//get all the static geometry
vector<PhStaticGeometry>* PhPolygonCollisionHandler::getStaticGeometry()
{
    return &level;
}

//remove all the static geometry
void PhPolygonCollisionHandler::clearStaticGeometry()
{
    level.clear();
}

///
/// Internal functions used to do the math needed for polygon collision detection
///

///Does polygon collision test, needs a pointer to a vector and a float, and it sets those to the
///normal and the magnitude of the seperation vector
///returns true if a collision occured

///This code is based on tutorial and code by Olivier Renault

bool PhPolygonCollisionHandler::PolygonCollision(PhPolygon A, PhPolygon B,PhVector2d& N,float& t)
{

    ///step one, Premilimary Circular Exclusion
    //we can do a preliminary collision test using circles, this is much faster and uses the radius of the polygons
    if (!((A.getPosition()-B.getPosition()).getMagnitude() < (A.getRadius() + B.getRadius())))
    {
        return false;
    }

    ///Step two, separating axis theorem
    // All the separation axes
    vector<PhVector2d> xAxis;
    vector<float>  taxis;
    xAxis.reserve(A.getVertexCount() + B.getVertexCount());
    taxis.reserve(A.getVertexCount() + B.getVertexCount());
    int    iNumAxes=0;

    // test separation axes of A
    for (int j = A.getVertexCount()-1, i = 0; i < A.getVertexCount(); j = i, i ++)
    {
        PhVector2d E0 = A.getVertex(j);
        PhVector2d E1 = A.getVertex(i);
        PhVector2d E  = E1 - E0;
        xAxis.push_back(PhVector2d(-E.getY(), E.getX()));

        if (!IntervalIntersect(	A, B, xAxis[iNumAxes],taxis[iNumAxes]))
        {
            return false;
        }

        iNumAxes++;
    }

    // test separation axes of B
    for (int j = B.getVertexCount()-1, i = 0; i < B.getVertexCount(); j = i, i ++)
    {
        PhVector2d E0 = B.getVertex(j);
        PhVector2d E1 = B.getVertex(i);
        PhVector2d E  = E1 - E0;
        xAxis.push_back(PhVector2d(-E.getY(), E.getX()));

        if (!IntervalIntersect(	A, B, xAxis[iNumAxes],taxis[iNumAxes]))
        {
            return false;
        }

        iNumAxes++;
    }

    ///Step three, minimum translation distance
    if (!FindMTD(&xAxis, &taxis, iNumAxes, N, t))
        return false;

    // make sure the polygons gets pushed away from each other.
    if (N * (A.getPosition() - B.getPosition()) < 0.0f){
        N = -N;
    }

    return true;
}


/// calculates the projection range of a polygon along an axis
void PhPolygonCollisionHandler::GetInterval(PhPolygon P, const PhVector2d& xAxis, float& min, float& max)
{
    min = max = (P.getVertex(0) * xAxis);

    for (int i = 1; i < P.getVertexCount(); i ++)
    {
        float d = (P.getVertex(i) * xAxis);
        if (d < min) min = d;
        else if (d > max) max = d;
    }
}

bool PhPolygonCollisionHandler::IntervalIntersect(PhPolygon A,
        PhPolygon B,
        const PhVector2d& xAxis,
        float& taxis)
{
    float min0, max0;
    float min1, max1;
    GetInterval(A, xAxis, min0, max0);
    GetInterval(B, xAxis, min1, max1);

    float h = (A.getPosition() - B.getPosition()) * xAxis;
    min0 += h;
    max0 += h;

    float d0 = min0 - max1;
    float d1 = min1 - max0;

    if (d0 > 0.0f || d1 > 0.0f)
    {
        return false;
    }
    else
    {
        taxis = (d0 > d1)? d0 : d1;

        return true;
    }
}

///used by above function to find the minimum translation distance (the shortest vector that
///seperates the polygons)

bool PhPolygonCollisionHandler::FindMTD(vector<PhVector2d> * xAxis, vector<float> * taxis, int iNumAxes, PhVector2d& N, float& t)
{
    // nope, find overlaps
    int mini = -1;

    t = 0.0f;
    N = PhVector2d(0, 0);

    for (int i = 0; i < iNumAxes; i ++)
    {
        float n = (*xAxis)[i].normalize();
        (*taxis)[i] /= n;

        if ((*taxis)[i] > t || mini == -1)
        {
            mini = i;
            t = (*taxis)[i];
            N = (*xAxis)[i];
        }
    }

    return (mini != -1);
}

