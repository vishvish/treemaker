/*******************************************************************************
File:         tmwxConditionEdgeLengthFixedPanel.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for tmConditionEdgeLengthFixed inspector panel
Author:       Robert J. Lang
Modified by:  
Created:      2003-12-22
Copyright:    2003 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmwxConditionEdgeLengthFixedPanel.h"

// Additional wxWidgets classes
#include "wx/statline.h"

// Additional TreeMaker classes
#include "tmModel.h"
#include "tmwxStr.h"
#include "tmwxTextCtrl.h"
#include "tmwxStaticText.h"
#include "tmwxDoc.h"
#include "tmwxApp.h"
#include "tmwxDocManager.h"


/*****
Constructor
*****/
tmwxConditionEdgeLengthFixedPanel::tmwxConditionEdgeLengthFixedPanel(
  wxWindow* parent) : 
  tmwxInspectorPanel(parent), mConditionEdgeLengthFixed(0)
{
  AddTextPair(wxT("Condition Index = "), mIndex, wxEmptyString);
  AddTextPair(wxT("Edge = "), mEdge, wxEmptyString);
  AddApplyButton();
  AddSpacer(5);
  AddStaticText(mIsFeasible);
#if tmwxINSPECTOR_EXTRA
#endif
  SetSizerAndFit(mPanelSizer);
  Layout();
  Fit();
}


/*****
Fill the panel from aConditionEdgeLengthFixed, which can be NULL.
*****/
void tmwxConditionEdgeLengthFixedPanel::Fill(
  tmConditionEdgeLengthFixed* aConditionEdgeLengthFixed)
{
  mConditionEdgeLengthFixed = aConditionEdgeLengthFixed;
  Fill();
}


/*****
Fill the panel from mConditionEdgeLengthFixed, which can be NULL.
*****/
void tmwxConditionEdgeLengthFixedPanel::Fill()
{
  if (!mConditionEdgeLengthFixed) return;
  mPanelBox->SetLabel(wxT("Condition: Edge Length Fixed"));
  mIndex->SetValue(mConditionEdgeLengthFixed->GetIndex());
  mEdge->SetValue(mConditionEdgeLengthFixed->GetEdge()->GetIndex());
  mIsFeasible->SetLabelFeasible(mConditionEdgeLengthFixed);
}


/*****
If one of our text controls received an Enter key, update the structure with
all text values
*****/
void tmwxConditionEdgeLengthFixedPanel::OnApply(wxCommandEvent&)
{
  if (!mConditionEdgeLengthFixed) return;
  
  tmTree* theTree = mConditionEdgeLengthFixed->GetTree();
  if (!theTree) return;

  // Validate edge exists before accessing
  tmEdge* currentEdge = mConditionEdgeLengthFixed->GetEdge();
  if (!currentEdge) {
    mEdge->SetValue(static_cast<tmFloat>(-1));
    return;
  }

  // Validation
  size_t newIndex;
  if (!mIndex->ValidateConditionIndex(theTree, newIndex)) {
    mIndex->SetValue(mConditionEdgeLengthFixed->GetIndex());
    return;
  }
  tmEdge* newEdge;
  if (!mEdge->ValidateEdgeIndexForCondition(theTree, newEdge)) {
    mEdge->SetValue(currentEdge->GetIndex());
    return;
  }
  
  // Updating
  bool modIndex = !mIndex->SameValue(mConditionEdgeLengthFixed->GetIndex());
  bool modEdge = 
    !mEdge->SameValue(currentEdge->GetIndex());
  bool modSomething = modIndex || modEdge;
  if (modSomething) {
    {
      tmTreeCleaner tc(theTree);
      if (modIndex) {
        theTree->SetConditionIndex(mConditionEdgeLengthFixed, newIndex);
      }
      if (modEdge) {
        mConditionEdgeLengthFixed->SetEdge(newEdge);
      }
    }
    gDocManager->GetCurrentDocumentLocal()->
      SubmitCommand(wxT("Edit Edge Condition"));
    Fill();
  } 
}


/*****
Event table
*****/
BEGIN_EVENT_TABLE(tmwxConditionEdgeLengthFixedPanel, wxPanel)
  EVT_BUTTON(wxID_APPLY, tmwxConditionEdgeLengthFixedPanel::OnApply)
  EVT_TEXT_ENTER(wxID_ANY, tmwxConditionEdgeLengthFixedPanel::OnApply)
END_EVENT_TABLE()
