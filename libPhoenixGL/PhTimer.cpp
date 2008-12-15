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

#include "PhTimer.h"
#include <GL/glfw.h>

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct
////////////////////////////////////////////////////////////////////////////////

PhTimer::PhTimer()
	: startTicks(0), pausedTicks(0), paused(false), started(false)
{
}

////////////////////////////////////////////////////////////////////////////////
//Start the timer
////////////////////////////////////////////////////////////////////////////////

void PhTimer::startTimer()
{
    //Start the timer
    started = true;
    //Unpause the timer
    paused = false;
    //Get the current clock time
    startTicks = glfwGetTime();
}

////////////////////////////////////////////////////////////////////////////////
//Stop the timer
////////////////////////////////////////////////////////////////////////////////

void PhTimer::stopTimer()
{
    //Stop the timer
    started = false;
    //Unpause the timer
    paused = false;
}

////////////////////////////////////////////////////////////////////////////////
//Get the ticks
////////////////////////////////////////////////////////////////////////////////

const double PhTimer::getTicks() const
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return glfwGetTime() - startTicks;
        }
    }
    //If the timer isn't running
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//Pause the timer
////////////////////////////////////////////////////////////////////////////////

void PhTimer::pauseTimer()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
        //Calculate the paused ticks
        pausedTicks = glfwGetTime() - startTicks;
    }
}

////////////////////////////////////////////////////////////////////////////////
//resume the timer
////////////////////////////////////////////////////////////////////////////////

void PhTimer::resumeTimer()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
        //Reset the starting ticks
        startTicks = glfwGetTime() - pausedTicks;
        //Reset the paused ticks
        pausedTicks = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//Duh.
////////////////////////////////////////////////////////////////////////////////

bool PhTimer::isStarted()
{
    return started;
}

bool PhTimer::isPaused()
{
    return paused;
}
