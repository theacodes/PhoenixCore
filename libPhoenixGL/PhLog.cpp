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

#include "PhLog.h"
using namespace phoenix;
using namespace std;

PhLog::PhLog(PhLogManager* lmgr, string filename)
	: mNumTabs(0), mNumSpaces(0), mUseTabs(true), mUseSpaces(false), mTreeView(false),
		mNumSpacesPerTab(5)
{
	logManager = lmgr;
	logManager->addLog(this);
	if( filename != string("") )
		openFile( filename);
}

PhLog::~PhLog()
{
	if (mLogFile)
		fclose(mLogFile);
	logManager->removeLog(this);
}

bool PhLog::openFile(string logFileName)
{
	mLogFile = fopen(logFileName.c_str(), "w");

	if (!mLogFile)
		return false;

	return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	I really don't even want to explain how
	Denzel did this.
*/
void PhLog::writeToLog(string text)
{
	if (mUseTabs == true && mTreeView == false)
	{
		for (int i = 0; i < mNumTabs; i++)
			fputc('\t', mLogFile);
	} else if (mUseSpaces == true && mTreeView == false) {
		for (int i = 0; i < mNumSpaces; i++)
			fputc(' ', mLogFile);
	} else if (mUseTabs == true && mTreeView == true) {
		for (int i = 0; i < (mNumTabs * mNumSpacesPerTab) - 1; i++)
			fputc('-', mLogFile);
		fputc('+', mLogFile);
		fputc(' ', mLogFile);
	} else if (mUseSpaces == true && mTreeView == true) {
		for (int i = 0; i < mNumSpaces - 1; i++)
			fputc('-', mLogFile);
		fputc('+', mLogFile);
		fputc(' ', mLogFile);
	}

	fwrite(text.c_str(), sizeof(char), text.length(), mLogFile);
	fputc('\n', mLogFile);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Parameters.
*/
void PhLog::useTabs(bool tabs) { mUseTabs = tabs; }
void PhLog::useSpaces(bool spaces) { mUseSpaces = spaces; }
bool PhLog::areTabsUsed() { return mUseTabs; }
bool PhLog::areSpacesUsed() { return mUseSpaces; }
void PhLog::setNumberOfTabs(int numTabs) { mNumTabs = numTabs; }
void PhLog::setNumberOfSpaces(int numSpaces) { mNumSpaces = numSpaces; }
int PhLog::getNumberOfTabs() { return mNumTabs; }
int PhLog::getNumberOfSpaces() { return mNumSpaces; }
void PhLog::setNumberOfSpacesPerTab(int spacesPerTab) { mNumSpacesPerTab = spacesPerTab; }
int PhLog::getNumberOfSpacesPerTab() { return mNumSpacesPerTab; }

void PhLog::setTreeView(bool treeView) { mTreeView = treeView; }
bool PhLog::getTreeView() { return mTreeView; }

void PhLog::setName(string n) { name = n; }
string PhLog::getName() { return name; }

