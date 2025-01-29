/*******************************************************************************
File:         tmwxPalettePanel.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for any panel that goes in a tool palette
Author:       Robert J. Lang
Modified by:  
Created:      2004-04-14
Copyright:    2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

// TreeMaker GUI classes
#include "tmwxPalettePanel.h"

/*****
Constructor
*****/
tmwxPalettePanel::tmwxPalettePanel(wxWindow* parent)
  : wxPanel(parent, wxID_ANY)
{
  // Create a default sizer to ensure proper layout
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(sizer);
}


/*****
Fill the panel with its contents. Default implementation does nothing.
*****/
void tmwxPalettePanel::Fill()
{
  // Default implementation does nothing
}
