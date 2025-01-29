/*******************************************************************************
File:         tmwxPersistentFrame.cpp
Project:      TreeMaker 5.x
Purpose:      Implementation file for class tmwxPersistentFrame
Author:       Robert J. Lang
Modified by:  
Created:      2005-02-19
Copyright:    2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmwxPersistentFrame.h"
#include "tmwxDocManager.h"

/**********
class tmwxPersistentFrame
A wxFrame that remembers its position and size in wxConfig.
**********/

/*****
Event table entries for tmwxPersistentFrame<wxFrame>
*****/
template <>
const wxEventTableEntry tmwxPersistentFrame<wxFrame>::sm_eventTableEntries[] = {
  { wxEVT_MOVE, 0, -1, wxNewEventTableFunctor(wxEVT_MOVE, (wxObjectEventFunction)&tmwxPersistentFrame<wxFrame>::OnMove), NULL },
  { wxEVT_SIZE, 0, -1, wxNewEventTableFunctor(wxEVT_SIZE, (wxObjectEventFunction)&tmwxPersistentFrame<wxFrame>::OnSize), NULL },
  { wxEVT_NULL, 0, 0, NULL, NULL }
};

/*****
Event table entries for tmwxPersistentFrame<tmwxDocParentFrame>
*****/
template <>
const wxEventTableEntry tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventTableEntries[] = {
  { wxEVT_MOVE, 0, -1, wxNewEventTableFunctor(wxEVT_MOVE, (wxObjectEventFunction)&tmwxPersistentFrame<tmwxDocParentFrame>::OnMove), NULL },
  { wxEVT_SIZE, 0, -1, wxNewEventTableFunctor(wxEVT_SIZE, (wxObjectEventFunction)&tmwxPersistentFrame<tmwxDocParentFrame>::OnSize), NULL },
  { wxEVT_NULL, 0, 0, NULL, NULL }
};

/*****
Constructor for ordinary wxFrame with persistence
*****/
template <>
tmwxPersistentFrame<wxFrame>::tmwxPersistentFrame(const wxString& title, 
  long style)  : 
  wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, style),
  mPositionAndSizeInitialized(false)
{
#if defined(__LINUX__) || defined(__WXMSW__)
  SetIcon (wxGetApp ().GetAppIcon ());
#endif

  // Create a default sizer to ensure proper layout
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(sizer);
  
  // Set a default minimum size
  SetMinSize(wxSize(100, 100));
  Layout();
}


/*****
Constructor for tmwxDocParentFrame frames
*****/
template <>
tmwxPersistentFrame<tmwxDocParentFrame>::tmwxPersistentFrame(
  wxDocManager* docManager, const wxString& title, long style)  : 
  tmwxDocParentFrame(docManager, NULL, wxID_ANY, title, wxDefaultPosition, 
    wxDefaultSize, style),
  mPositionAndSizeInitialized(false)
{
#if defined(__LINUX__) || defined(__WXMSW__)
  SetIcon (wxGetApp ().GetAppIcon ());
#endif

  // Create a default sizer to ensure proper layout
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(sizer);
  
  // Set a default minimum size
  SetMinSize(wxSize(100, 100));
  Layout();
}

/*
We do our own manual expansion of the BEGIN_EVENT_TABLE() macro because we
need to sprinkle template<> among the declarations.
*/


/*****
Event table for tmwxPersistentFrame<wxFrame>
*****/
template <>
const wxEventTable tmwxPersistentFrame<wxFrame>::sm_eventTable =
    { &wxFrame::sm_eventTable, &tmwxPersistentFrame<wxFrame>::sm_eventTableEntries[0] };
template <>
const wxEventTable *tmwxPersistentFrame<wxFrame>::GetEventTable() const
    { return &tmwxPersistentFrame<wxFrame>::sm_eventTable; }
template <>
wxEventHashTable tmwxPersistentFrame<wxFrame>::sm_eventHashTable(tmwxPersistentFrame<wxFrame>::sm_eventTable);
template <>
wxEventHashTable &tmwxPersistentFrame<wxFrame>::GetEventHashTable() const
    { return tmwxPersistentFrame<wxFrame>::sm_eventHashTable; }


/*****
Event table for tmwxPersistentFrame<tmwxDocParentFrame>
*****/
template <>
const wxEventTable tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventTable =
    { &tmwxDocParentFrame::sm_eventTable, &tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventTableEntries[0] };
template <>
const wxEventTable *tmwxPersistentFrame<tmwxDocParentFrame>::GetEventTable() const
    { return &tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventTable; }
template <>
wxEventHashTable tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventHashTable(tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventTable);
template <>
wxEventHashTable &tmwxPersistentFrame<tmwxDocParentFrame>::GetEventHashTable() const
    { return tmwxPersistentFrame<tmwxDocParentFrame>::sm_eventHashTable; }
