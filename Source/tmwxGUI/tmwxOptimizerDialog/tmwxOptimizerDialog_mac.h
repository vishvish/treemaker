/*******************************************************************************
File:         tmwxOptimizerDialog_mac.h
Project:      TreeMaker 5.x
Purpose:      Header file for Mac-specific implementation of tmwxOptimizerDialog
Author:       Robert J. Lang
Modified by:  
Created:      2004-04-22
Copyright:    ©2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#ifndef _TMWXOPTIMIZERDIALOG_MAC_H_
#define _TMWXOPTIMIZERDIALOG_MAC_H_

#include "tmwxOptimizerDialog.h"

/**********
class tmwxOptimizerDialogMac
Mac-specific implementation of tmwxOptimizerDialog
**********/
class tmwxOptimizerDialogMac : public tmwxOptimizerDialog {
public:
  tmwxOptimizerDialogMac(tmwxDoc* aDoc, tmOptimizer* aOptimizer, 
    const wxString& descr) : tmwxOptimizerDialog(aDoc, aOptimizer, descr) {}
    
protected:
  void DoStartModal() override;
  void DoEventLoopModal() override;
  void DoEventLoopOnce() override;
  void DoFinishModal() override;
};

#endif // _TMWXOPTIMIZERDIALOG_MAC_H_
