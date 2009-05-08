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
			inline void useTabs(const bool& tabs) { mUseTabs = tabs; }

			//! Use spaces.
			/*!
				Specifies whether spaces should be used when writing to the file.
				\param spaces True = yes, False = no.
				\sa useTabs()
			*/
			inline void useSpaces(const bool& spaces) { mUseSpaces = spaces; }

			//! Are tabs used.
			/*!
				Tells whether tabs are used or not.
				\return Whether tabs are enabled.
			*/
			inline const bool& areTabsUsed() const { return mUseTabs; }

			//! Are spaces used.
			/*!
				Tells whether spaces are used or not
				\return Whether spaces are enabled.
			*/
			inline const bool& areSpacesUsed() const { return mUseSpaces; }

			//! Set number of tabs.
			/*!
				Sets the number of tabs to be used when writing to the file.
				\param numTabs Specify the number of tabs to use.
			*/
			inline void setNumberOfTabs(const int& numTabs) { mNumTabs = numTabs; }

			//! Set number of spaces.
			/*!
				Sets the number of spaces to be used when writing to the file.
				\param numSpaces Specify the number of spaces to use.
			*/
			inline void setNumberOfSpaces(const int& numSpaces) { mNumSpaces = numSpaces; }

			//! Get number of tabs.
			/*!
				Returns the number of tabs used when writing to the file.
				\return The number of tabs used.
			*/
			inline const int& getNumberOfTabs() const { return mNumTabs; }

			//! Get number of spaces.
			/*!
				Returns the number of spaces used when writing to the file.
				\return The number of spaces used.
			*/
			inline const int& getNumberOfSpaces() const { return mNumSpaces; }

			//! Set number of spaces per tab.
			/*!
				This value must be set when using the tree view. (Default:
				5).
				\param spacesPerTab Specify the number of spaces you want per tab
				\sa getNumberOfSpacesPerTab()
			*/
			inline void setNumberOfSpacesPerTab(const int& spacesPerTab) { mNumSpacesPerTab = spacesPerTab; }

			//! Get number of spaces per tab.
			/*!
				Returns the number of spaces per tab.
				\return The number of spaces per tab that are used.
				\sa setNumberOfSpacesPerTab()
			*/
			inline const int& getNumberOfSpacesPerTab() const { return mNumSpacesPerTab; }

			//! Set tree view.
			/*!
				Set a parameter specifying whether or not to display the log file
				in tree view or not. (Note: Tree view looks cool!)
				\param treeView Enable or disable tree view.
			*/
			inline void setTreeView(const bool& treeView) { mTreeView = treeView; }

			//! Get tree view.
			/*!
				Tells whether tree view is enabled or disabled.
				\return Is tree view enabled or not.
			*/
			inline const bool& getTreeView() const { return mTreeView; }

			//! Set name.
			/*!
				Sets the name that will be used to look up this log with PhLogManager.
				\param n The name you want for the log.
			*/
			inline void setName(const std::string& n) { name = n; }

			//! Get name.
			/*!
				Returns the name of this log.
				\return The name of this log.
			*/
			inline const std::string& getName() { return name; }

	};

}

#endif
