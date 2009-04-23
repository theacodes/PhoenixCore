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

#ifndef __PHOENIXLOGC__
#define __PHOENIXLOGC__

#include <string>
#include <cstdio>
#include "PhLogManager.h"

namespace phoenix
{

	//! Log class.
	/*!
		This class represents a log file. This can be used for writing debug files
		or anything else you wish to write.
		\sa phoenix::PhLogManager
	*/
	class PhLog
	{
		protected:
			std::string name;
			FILE* mLogFile;
			int mNumTabs;
			int mNumSpaces;
			bool mUseTabs;
			bool mUseSpaces;
			bool mTreeView;
			int mNumSpacesPerTab;
			PhLogManager* logManager;

		public:

			//! Constructor
			PhLog(PhLogManager* lmgr, std::string filename = std::string(""));

			//! Destructor
			~PhLog();

			//! Open file.
			/*!
				Opens a file to write to from the name given.
				\param logFileName The name of the file.
				\return False on fail, and true on success.
			*/
			bool openFile(std::string logFileName );

			//! Write to log.
			/*!
				Writes the given line to the file, taking into account the
				parameters you provide for tabs and spaces.
				\param text The text that you would like to write to the file.
			*/
			void writeToLog(std::string text);

			//! Use tabs.
			/*!
				Specifies whether tabs should be used when writing to the file.
				(Note: Tabs take precedent over spaces when both are enabled.)
				\param tabs True = yes, False = no.
				\sa useSpaces()
			*/
			void useTabs(bool tabs);

			//! Use spaces.
			/*!
				Specifies whether spaces should be used when writing to the file.
				\param spaces True = yes, False = no.
				\sa useTabs()
			*/
			void useSpaces(bool spaces);

			//! Are tabs used.
			/*!
				Tells whether tabs are used or not.
				\return Whether tabs are enabled.
			*/
			bool areTabsUsed();

			//! Are spaces used.
			/*!
				Tells whether spaces are used or not
				\return Whether spaces are enabled.
			*/
			bool areSpacesUsed();

			//! Set number of tabs.
			/*!
				Sets the number of tabs to be used when writing to the file.
				\param numTabs Specify the number of tabs to use.
			*/
			void setNumberOfTabs(int numTabs);

			//! Set number of spaces.
			/*!
				Sets the number of spaces to be used when writing to the file.
				\param numSpaces Specify the number of spaces to use.
			*/
			void setNumberOfSpaces(int numSpaces);

			//! Get number of tabs.
			/*!
				Returns the number of tabs used when writing to the file.
				\return The number of tabs used.
			*/
			int getNumberOfTabs();

			//! Get number of spaces.
			/*!
				Returns the number of spaces used when writing to the file.
				\return The number of spaces used.
			*/
			int getNumberOfSpaces();

			//! Set number of spaces per tab.
			/*!
				This value must be set when using the tree view. (Default:
				5).
				\param spacesPerTab Specify the number of spaces you want per tab
				\sa getNumberOfSpacesPerTab()
			*/
			void setNumberOfSpacesPerTab(int spacesPerTab);

			//! Get number of spaces per tab.
			/*!
				Returns the number of spaces per tab.
				\return The number of spaces per tab that are used.
				\sa setNumberOfSpacesPerTab()
			*/
			int getNumberOfSpacesPerTab();

			//! Set tree view.
			/*!
				Set a parameter specifying whether or not to display the log file
				in tree view or not. (Note: Tree view looks cool!)
				\param treeView Enable or disable tree view.
			*/
			void setTreeView(bool treeView);

			//! Get tree view.
			/*!
				Tells whether tree view is enabled or disabled.
				\return Is tree view enabled or not.
			*/
			bool getTreeView();

			//! Set name.
			/*!
				Sets the name that will be used to look up this log with PhLogManager.
				\param n The name you want for the log.
			*/
			void setName(std::string n);

			//! Get name.
			/*!
				Returns the name of this log.
				\return The name of this log.
			*/
			std::string getName();

	};

}

#endif
