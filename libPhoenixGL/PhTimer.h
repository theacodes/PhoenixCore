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

#ifndef PHOENIXTIME
#define PHOENIXTIME

namespace phoenix
{

    //! Timer class
    /*!
        A class that provides a simple interface to a real time clock. This class might not ever be used by
        the user but it is used internally for FPS calculations. It's not suggested to do events based on a
        timer because of the fact that everything is done by frames, therefore it is better to do things by
        frames instead of seconds.
    */
    class PhTimer
    {

    private:

        double startTicks, pausedTicks;
        bool paused, started;

    public:

        //! Constructor.
        PhTimer();

        //! Start timer.
        /*!
            Starts the timer.
        */
        void startTimer();

        //! Stop timer.
        /*!
            Stops the timer and sets it to zero.
        */
        void stopTimer();

        //! Pause timer.
        /*!
            Pauses the timer in place.
        */
        void pauseTimer();

        //! Resume Timer.
        /*!
            Resumes the timer from where it stopped.
        */
        void resumeTimer();

        //! Get ticks.
        /*!
            Returns how many ticks (ms) the timer has gone through.
            \return Ticks in miliseconds.
        */
        const double getTicks() const;

        //! Is started.
        /*!
            \return True if the timer has started.
        */
        bool isStarted();

        //! Is paused.
        /*!
            \return True if the timer is paused.
        */
        bool isPaused();

    };

}

#endif
