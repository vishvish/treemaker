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

#include "tmwxOptimizerDialog.h"
#include "tmwxDoc.h"
#include "tmwxDesignFrame.h"
#include "tmOptimizer.h"
#include "tmwxStr.h"

#include "wx/app.h"
#include "wx/evtloop.h"

/**********
class tmwxOptimizerDialog
A dialog for long, cancellable calculations
**********/

/*****
Constructor
*****/
tmwxOptimizerDialog::tmwxOptimizerDialog(tmwxDoc* aDoc, tmOptimizer* aOptimizer, 
  const wxString& descr) : 
  wxDialog(NULL, wxID_ANY, wxT("Optimizing..."), wxDefaultPosition, 
    wxDefaultSize, wxCAPTION | wxSYSTEM_MENU),
  mDoc(aDoc),
  mOptimizer(aOptimizer),
  mStatus(IN_LOOP),
  mReason(0)
{
  // Create the dialog box contents
  wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(topSizer);
  
  // Add text for showing progress
  mProgress = new tmwxStaticText(this, wxID_ANY, descr);
  topSizer->Add(mProgress, 0, wxALL | wxEXPAND, 10);
  
  // Size the dialog box to fit its contents
  topSizer->Fit(this);
  topSizer->SetSizeHints(this);
  
  // Center the dialog box on the screen
  Center();
}


/*****
Event table
*****/
BEGIN_EVENT_TABLE(tmwxOptimizerDialog, wxDialog)
  EVT_KEY_DOWN(tmwxOptimizerDialog::OnKeyDown)
END_EVENT_TABLE()


/*****
Event handlers
*****/
void tmwxOptimizerDialog::OnKeyDown(wxKeyEvent& event)
{
  if (event.GetKeyCode() == WXK_ESCAPE) {
    SetStatus(USER_CANCELLED);
    SetReason(0);
  }
  event.Skip();
}


/*****
Set the status
*****/
void tmwxOptimizerDialog::SetStatus(int aStatus)
{
  mStatus = aStatus;
}


/*****
Set the reason
*****/
void tmwxOptimizerDialog::SetReason(int aReason)
{
  mReason = aReason;
}


/*****
Start the modal dialog
*****/
void tmwxOptimizerDialog::DoStartModal()
{
  Show();
}


/*****
Run the event loop for the modal dialog
*****/
void tmwxOptimizerDialog::DoEventLoopModal()
{
  while (mStatus == IN_LOOP) {
    DoEventLoopOnce();
  }
}


/*****
Process one event in the modal dialog
*****/
void tmwxOptimizerDialog::DoEventLoopOnce()
{
  wxEventLoopBase::GetActive()->Dispatch();
}


/*****
Clean up after the modal dialog
*****/
void tmwxOptimizerDialog::DoFinishModal()
{
  Hide();
}


/*****
End the modal dialog
*****/
void tmwxOptimizerDialog::EndModal(int retCode)
{
  SetStatus(retCode);
}


/*****
Show the modal dialog
*****/
int tmwxOptimizerDialog::ShowModal()
{
  DoStartModal();
  DoEventLoopModal();
  DoFinishModal();
  return GetStatus();
}


/*****
Update the UI
*****/
void tmwxOptimizerDialog::UpdateUI()
{
  mProgress->SetLabel(mOptimizer->GetStatusStr());
  DoEventLoopOnce();
}

#endif // __WXMAC__
