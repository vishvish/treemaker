/*******************************************************************************
File:         tmwxOptimizerDialog_cmn.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for class tmwxOptimizerDialog (common implementation)
Author:       Robert J. Lang
Modified by:  
Created:      2004-04-22
Copyright:    2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmwxOptimizerDialog.h"
#include "tmwxDoc.h"
#include "tmwxDesignFrame.h"
#include "tmOptimizer.h"
#include "tmwxStr.h"

#include "wx/app.h"
#include "wx/stattext.h"

/**********
class tmwxOptimizerDialog
Common implementation
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
  mProgress = new wxStaticText(this, wxID_ANY, descr);
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
  // Update the progress text and process events
  if (mOptimizer && mOptimizer->GetNLCO()) {
    mProgress->SetLabel(wxT("Optimizing..."));
    DoEventLoopOnce();
  }
}
