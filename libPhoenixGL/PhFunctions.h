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

#ifndef PHOENIXFUNCS
#define PHOENIXFUNCS

#include <cstdlib> //For rand()

namespace phoenix
{

    //! Porportion
    /*! Porportion, it returns a porportional value based on this:
    <br>
    a/b = c/d
    <br>
    Note that if you're looking for something, one of these four will be unknown, it doesn't
    matter what value you pass to it.
    \param a Numerator of first fraction.
    \param b Denominator of first fraction.
    \param c Numerator of second fraction.
    \param d Denominator of second fraction.
    \param find The parameter you wanna find, a being 0 and d being 3.
    \return The value you seek.
    */
    template <class a_type> a_type porportion(a_type a,a_type b,a_type c,a_type d,int find)
    {
        switch (find)
        {
        case 0:
            return ( (b*c)/d );
            break;
        case 1:
            return ( (a*d)/c );
            break;
        case 2:
            return ( (a*d)/b );
            break;
        case 3:
            return ( (b*c)/a );
            break;
        }
        return 0;
    }

    //! Random function.
	/*!
		\param low The lowest possible value.
		\param high The highest possible value.
		\return A pseudo random value between low and high.
	*/
	///random function
	template <class a_type> a_type random(a_type low,a_type high)
	{
		return (a_type(rand()) % (high - low + a_type(1)) + low);
	}

}

#endif
