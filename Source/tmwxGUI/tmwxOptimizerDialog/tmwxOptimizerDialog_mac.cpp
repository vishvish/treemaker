/*******************************************************************************
File:         tmwxOptimizerDialog_mac.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for class tmwxOptimizerDialog, specialization for Mac
                Derived from wx/src/mac/wxDialog
Author:       Stefan Csomor
Modified by:  Robert J. Lang
Created:     (original), 2004-04-22 (modifications)
Copyright (original):       2004 by Stefan Csomor, 
                              released under the wxWidgets license
Copyright (modifications):  2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#ifdef __WXMAC__

// Platform-specific includes
#include <Carbon/Carbon.h>

#include "tmwxOptimizerDialog.h"


/**********
class tmwxOptimizerDialog
Dialog for long, cancellable calculations
**********/

#if !TARGET_CARBON
extern bool s_macIsInModalLoop;
static bool s_formerModal;
#endif

extern wxWindowList wxModalDialogs;


/*****
Constructor
*****/
tmwxOptimizerDialog::tmwxOptimizerDialog(tmwxDesignFrame* parent) : 
  wxDialog(parent, wxID_ANY, wxT("Optimizing..."), wxDefaultPosition, 
    wxDefaultSize, wxCAPTION | wxSYSTEM_MENU)
{
  // Make this dialog modal
  MakeModal(true);

  // Create the dialog box contents
  wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(topSizer);
  
  // Add a gauge for showing progress
  mGauge = new wxGauge(this, wxID_ANY, 100);
  topSizer->Add(mGauge, 0, wxALL | wxEXPAND, 10);
  
  // Add a text field for showing current status
  mText = new wxStaticText(this, wxID_ANY, wxT("Initializing..."));
  topSizer->Add(mText, 0, wxALL | wxEXPAND, 10);
  
  // Add a button for stopping the optimization
  mStopButton = new wxButton(this, wxID_ANY, wxT("Stop"));
  topSizer->Add(mStopButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
  
  // Set up event handlers
  mStopButton->Bind(wxEVT_BUTTON, &tmwxOptimizerDialog::OnStop, this);
  
  // Size the dialog box to fit its contents
  topSizer->Fit(this);
  topSizer->SetSizeHints(this);
  
  // Center the dialog box on the screen
  Center();
}


/*****
Event table
*****/
void tmwxOptimizerDialog::OnStop(wxCommandEvent&)
{
  mStopPressed = true;
}


/*****
Destructor
*****/
tmwxOptimizerDialog::~tmwxOptimizerDialog()
{
  MakeModal(false);
}


/*****
Process one event
*****/
void tmwxOptimizerDialog::ProcessEvent()
{
  wxEventLoopBase::GetActive()->Dispatch();
}


/*****
Set the gauge value
*****/
void tmwxOptimizerDialog::SetGaugeValue(int value)
{
  mGauge->SetValue(value);
}


/*****
Set the text value
*****/
void tmwxOptimizerDialog::SetText(const wxString& text)
{
  mText->SetLabel(text);
}


/*****
Return true if the stop button was pressed
*****/
bool tmwxOptimizerDialog::StopPressed()
{
  return mStopPressed;
}


/*****
Put up and show the modal dialog. This code is basically everything that happens
in a call to wxDialog::ShowModal(), up to the start of the dialog event loop.
*****/
void tmwxOptimizerDialog::DoStartModal()
{
  ::wxBeginBusyCursor();
  SetModal(true);
  if (!wxDialogBase::Show(true)) 
    TMFAIL("error, dialog was already visible in "\
      "tmwxOptimizerDialog::DoStartModal()");
  InitDialog();
  wxModalDialogs.Append(this);
#if TARGET_CARBON
  BeginAppModalStateForWindow((WindowRef) MacGetWindowRef());
#else
  s_formerModal = s_macIsInModalLoop;
  s_macIsInModalLoop = true;
#endif
}


/*****
Process a single event. Subclasses that implement their own event loop must
call this routine periodically through the loop.
*****/
void tmwxOptimizerDialog::DoEventLoopOnce()
{
  wxTheApp->MacDoOneEvent();
}


/*****
Take down the modal dialog and do cleanup. This code is basically 
wxDialog::Show(false), followed by everything
that happens in a call to wxDialog::ShowModal() after the event loop.
*****/
void tmwxOptimizerDialog::DoFinishModal()
{
  if (!wxDialogBase::Show(false))
    TMFAIL("error, dialog was already hidden in "\
      "tmwxOptimizerDialog::DoFinishModal()");
  wxModalDialogs.DeleteObject(this);
  
#if TARGET_CARBON
  EndAppModalStateForWindow((WindowRef) MacGetWindowRef());
#else
  s_macIsInModalLoop = s_formerModal;
#endif
  
  ::wxEndBusyCursor();
}

#endif // __WXMAC__
