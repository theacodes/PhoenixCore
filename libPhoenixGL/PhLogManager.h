/*

Copyright (c) 2008, Jonathan Wayne Parrott, Denzel Morris.

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

#ifndef __PHOENIXLMC__
#define __PHOENIXLMC__

#include <string>
#include <vector>

namespace phoenix
{
	
	class PhLog;
	
	//! Log manager.
	/*!
		This takes care of cleaning up after all the logs when the program exits.
		\sa PhLog
	*/
	class PhLogManager
	{
		protected:
			
			//! List of all the logs currently open.
			std::vector<PhLog*> mLogList;
			
		public:
			//! Constructor
			PhLogManager();
			
			//!Destructor
			/*!
				When this object is destroyed it will automatically delete all 
				the logs currently loaded.
			*/
			~PhLogManager();
			
        	//! Open log.
        	/*!
        		Opens a log and adds it to the log manager for garbage collection.
        		\param logName The name associated with the log.
        		\param logFileName The name of the log in memory.
        	*/
        	PhLog* openLog(std::string logName, std::string logFileName);
			
			void addLog(PhLog* log);
			void removeLog(PhLog* log);
			void deleteLogs();
			PhLog* findLog(std::string n);
	};
	
}

#include "PhLog.h"

#endif
