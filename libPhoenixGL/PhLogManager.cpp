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

#include "PhLogManager.h"
using namespace phoenix;
using namespace std;

PhLogManager::PhLogManager()
{
}

PhLogManager::~PhLogManager()
{
	deleteLogs();
}

PhLog* PhLogManager::openLog(std::string logName, std::string logFileName)
{
	PhLog* logFile = new PhLog(this);
	logFile->setName(logName.c_str());
	
	if (logFile->openFile(logFileName.c_str()) == false)
		logFile->setName("FAILEDTOLOAD");
		
	return logFile;
}

void PhLogManager::addLog(PhLog* log)
{
	mLogList.push_back(log);
}

void PhLogManager::removeLog(PhLog* log)
{
	for (unsigned int i = 0; i < mLogList.size(); i++)
	{
		if (mLogList[i] == log)
		{
			mLogList.erase(mLogList.begin()+i, mLogList.begin()+i+1);
		}
	}
}

void PhLogManager::deleteLogs()
{
	for (unsigned int i = 0; i < mLogList.size(); i++)
	{
		if (mLogList[i] != NULL)
		{
			delete mLogList[i];
		}
	}
	
	mLogList.clear();
}

PhLog* PhLogManager::findLog(string n)
{
	for (unsigned int i = 0; i < mLogList.size(); i++)
	{
		if ((mLogList[i] != NULL) && (mLogList[i]->getName() == n))
		{
			return mLogList[i];
		}
	}
	
	return NULL;
}
