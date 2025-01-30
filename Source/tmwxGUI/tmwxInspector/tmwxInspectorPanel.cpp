/*******************************************************************************
File:         tmwxInspectorPanel.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for any panel that goes in the Inspector
Author:       Robert J. Lang
Modified by:  
Created:      2005-12-07
Copyright:    2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

// Additional wxWidgets classes
#include "wx/statline.h"

// TreeMaker GUI classes
#include "tmwxInspectorPanel.h"
#include "tmwxStr.h"
#include "tmwxStaticText.h"
#include "tmwxTextCtrl.h"
#include "tmwxButtonSmall.h"
#include "tmwxCheckBoxSmall.h"
#include "tmwxConditionListBox.h"
#include "tmwxApp.h"
#include "tmwxDocManager.h"

/*****
Event table
*****/
wxBEGIN_EVENT_TABLE(tmwxInspectorPanel, tmwxPalettePanel)
wxEND_EVENT_TABLE()


/*****
Constructor
*****/
tmwxInspectorPanel::tmwxInspectorPanel(wxWindow* parent)
  : tmwxPalettePanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                     wxTAB_TRAVERSAL | wxNO_BORDER)
{
  SetBackgroundColour(parent->GetBackgroundColour());
  
  // Create panel box and sizers
  mPanelBox = new wxStaticBox(this, wxID_ANY, wxT("-"));
  mPanelSizer = new wxStaticBoxSizer(mPanelBox, wxVERTICAL);
  mContentSizer = new wxBoxSizer(wxVERTICAL);
  mPanelSizer->Add(mContentSizer, 1, wxEXPAND | wxALL, 5);
  
#if tmwxINSPECTOR_EXTRA
  mGridExtraSizer = nullptr;
#endif // tmwxINSPECTOR_EXTRA

  // Set up sizer hierarchy - make sure to delete the base class sizer first
  wxSizer* oldSizer = GetSizer();
  if (oldSizer) {
    SetSizer(nullptr, false);  // Detach but don't delete old sizer's windows
    delete oldSizer;
  }
  SetSizer(mPanelSizer);
  
  // Set minimum size to prevent collapsing
  SetMinSize(wxSize(200, 100));
  
  Layout();
}


/*****
Fill the panel with its contents. Base class does nothing.
*****/
void tmwxInspectorPanel::Fill()
{
  // Base class does nothing
}


/*****
Add a tmwxStaticText caption and tmwxTextCtrl in a single row.
*****/
void tmwxInspectorPanel::AddTextPair(const wxString& caption, 
  tmwxTextCtrl*& textctrl, const wxString& format)
{
  Freeze();
  wxFlexGridSizer* gridsizer = new wxFlexGridSizer(2, wxSize(5,5));  // 2 columns with 5px spacing
  gridsizer->AddGrowableCol(1);  // Make second column growable
  
  auto* label = new tmwxStaticText(this, 11, caption);
  label->SetMinSize(wxSize(80, -1));
  gridsizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL | wxFIXED_MINSIZE, 5);
  
  textctrl = new tmwxTextCtrl(this, format);
  textctrl->SetMinSize(wxSize(100, -1));
  gridsizer->Add(textctrl, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL | wxFIXED_MINSIZE, 5);
  
  mContentSizer->Add(gridsizer, 0, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add a checkbox.
*****/
void tmwxInspectorPanel::AddCheckBox(wxCheckBox*& checkbox, 
  const wxString& caption)
{
  Freeze();
  checkbox = new tmwxCheckBoxSmall(this, caption);
  checkbox->SetMinSize(checkbox->GetBestSize());
  mContentSizer->Add(checkbox, 0, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add a twmxCheckboxSmall and a twmxTextCtrl in a single row.
*****/
void tmwxInspectorPanel::AddCheckPair(wxCheckBox*& checkbox, 
  const wxString& caption, tmwxTextCtrl*& textctrl, const wxString& format)
{
  Freeze();
  wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);
  
  checkbox = new tmwxCheckBoxSmall(this, caption);
  checkbox->SetMinSize(checkbox->GetBestSize());
  rowSizer->Add(checkbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  
  textctrl = new tmwxTextCtrl(this, format);
  textctrl->SetMinSize(wxSize(100, -1));
  rowSizer->Add(textctrl, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 5);
  
  mContentSizer->Add(rowSizer, 0, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add a twmxStaticText element in standard size.
*****/
void tmwxInspectorPanel::AddStaticText(tmwxStaticText*& stattext)
{
  Freeze();
  stattext = new tmwxStaticText(this, 11, wxEmptyString);
  mContentSizer->Add(stattext, 0, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add an "Apply" button to the panel.
*****/
void tmwxInspectorPanel::AddApplyButton()
{
  Freeze();
  wxButton* button = new wxButton(this, wxID_APPLY);
  button->SetMinSize(button->GetBestSize());
  mContentSizer->Add(button, 0, wxALIGN_CENTER | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add a tmwxConditionListBox.
*****/
void tmwxInspectorPanel::AddConditionListBox(tmwxConditionListBox*& clistbox, 
  const wxSize size)
{
  Freeze();
  clistbox = new tmwxConditionListBox(this, size);
  clistbox->SetMinSize(size);
  mContentSizer->Add(clistbox, 1, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add a static line divider
*****/
void tmwxInspectorPanel::AddStatLine()
{
  Freeze();
  wxStaticLine* line = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, 
    wxDefaultSize, wxLI_HORIZONTAL);
  mContentSizer->Add(line, 0, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add some blank space
*****/
void tmwxInspectorPanel::AddSpacer(int size)
{
  mContentSizer->AddSpacer(size);
  Layout();
}

#if tmwxINSPECTOR_EXTRA
/*****
Start the section of extra data
*****/
void tmwxInspectorPanel::InitExtra()
{
  mGridExtraSizer = new wxFlexGridSizer(2, wxSize(5,5));  // 2 columns with 5px spacing
  mGridExtraSizer->AddGrowableCol(1);  // Make second column growable
  mContentSizer->Add(mGridExtraSizer, 0, wxEXPAND | wxALL, 5);
}


/*****
Add a twmxStaticText element in "extra" size to the extra sizer.
*****/
void tmwxInspectorPanel::AddStatTextGridExtra(tmwxStaticText*& stattext)
{
  Freeze();
  stattext = new tmwxStaticText(this, 9, wxEmptyString);
  mGridExtraSizer->Add(stattext, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  Layout();
  Thaw();
}


/*****
Add a twmxStaticText element in "extra" size to the extra sizer, but giving
it an entire row (used for array data).
*****/
void tmwxInspectorPanel::AddStatTextRowExtra(tmwxStaticText*& stattext)
{
  Freeze();
  stattext = new tmwxStaticText(this, 9, wxEmptyString);
  mGridExtraSizer->Add(stattext, 0, wxEXPAND | wxALL, 5);
  Layout();
  Thaw();
}

#endif // tmwxINSPECTOR_EXTRA
