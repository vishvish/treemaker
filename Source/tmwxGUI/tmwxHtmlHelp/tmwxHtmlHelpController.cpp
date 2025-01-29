/*******************************************************************************
File:         tmwxHtmlHelpController.cpp
Project:      TreeMaker 5.x
Purpose:      Implementation file for class tmwxHtmlHelpController
Author:       Robert J. Lang
Modified by:  
Created:      2005-11-23
Copyright:    2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmwxHtmlHelpController.h"
#include "tmwxHtmlHelpFrame.h"
#include "tmwxApp.h"

/*****
Constructor
*****/
tmwxHtmlHelpController::tmwxHtmlHelpController() : 
  wxHtmlHelpController(wxHF_TOOLBAR | wxHF_CONTENTS | wxHF_SEARCH | 
    wxHF_BOOKMARKS | wxHF_PRINT),
  mHtmlHelpFrame(0),
  mHtmlEasyPrinting(0)
{
}


/*****
Return a help frame. We override this so that we can set up the printer
parameters that go with this frame.
*****/
wxHtmlHelpFrame* tmwxHtmlHelpController::CreateHelpFrame(wxHtmlHelpData* data)
{
  mHtmlHelpFrame = new tmwxHtmlHelpFrame(data);
  mHtmlEasyPrinting = new wxHtmlEasyPrinting();
  mHtmlEasyPrinting->SetFooter(
    wxT("<hr><p align=\"right\">page @PAGENUM@ of @PAGESCNT@</p>"), 
    wxPAGE_ALL);
  int fontsizes[] = { 6, 8, 10, 12, 14, 16, 18 }; 
  mHtmlEasyPrinting->SetFonts(wxEmptyString, wxEmptyString, fontsizes);
  mHtmlHelpFrame->SetHtmlHelpPrinter(mHtmlEasyPrinting);
  return mHtmlHelpFrame;
}


/*****
Override from base class to create our own help frame
*****/
wxWindow* tmwxHtmlHelpController::CreateHelpWindow()
{
  wxHtmlHelpFrame* frame = CreateHelpFrame(GetHelpData());
  frame->SetController(this);
  return frame;
}
