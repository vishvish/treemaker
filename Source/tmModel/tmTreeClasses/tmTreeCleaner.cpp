/*******************************************************************************
File:         tmTreeCleaner.cpp
Project:      TreeMaker 5.x
Purpose:      Implementation file for the tmTreeCleaner class
Author:       Robert J. Lang
Modified by:  
Created:      2003-12-04
Copyright:    2003 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmTreeCleaner.h"
#include "tmTree.h"

/**********
class tmTreeCleaner
A stack class that handles cleaning up a tmTree after editing
**********/

/*****
Record the tmTree and its state of cleanup needed
*****/
tmTreeCleaner::tmTreeCleaner(tmTree* aTree)
{
  mTree = aTree;
  mNeedsCleanup = mTree->mNeedsCleanup;
  mTree->mNeedsCleanup = true;
}


/*****
If tmTree wasn't marked for cleanup when this was created, call CleanupAfterEdit().
*****/
tmTreeCleaner::~tmTreeCleaner()
{
  if (mNeedsCleanup) return;
  mTree->CleanupAfterEdit();
  mTree->mNeedsCleanup = false;
}
