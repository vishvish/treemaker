/*******************************************************************************
File:         tmwxOptimizerDialog_mac.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for class tmwxOptimizerDialog (Mac-specific implementation)
Author:       Stefan Csomor
Modified by:  Robert J. Lang
Created:     (original), 2004-04-22 (modifications)
Copyright (original):       2004 by Stefan Csomor, 
                              released under the wxWidgets license
Copyright (modifications):  2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#ifdef __WXMAC__

#include "tmwxOptimizerDialog_mac.h"
#include "wx/evtloop.h"

/**********
class tmwxOptimizerDialogMac
Mac-specific implementation
**********/

/*****
Start the modal dialog
*****/
void tmwxOptimizerDialogMac::DoStartModal()
{
  Show();
}


/*****
Run the event loop for the modal dialog
*****/
void tmwxOptimizerDialogMac::DoEventLoopModal()
{
  while (GetStatus() == IN_LOOP) {
    DoEventLoopOnce();
  }
}


/*****
Process one event in the modal dialog
*****/
void tmwxOptimizerDialogMac::DoEventLoopOnce()
{
  wxEventLoopBase::GetActive()->Dispatch();
}


/*****
Clean up after the modal dialog
*****/
void tmwxOptimizerDialogMac::DoFinishModal()
{
  Hide();
}

#endif // __WXMAC__
