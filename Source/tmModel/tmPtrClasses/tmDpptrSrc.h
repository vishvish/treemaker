/*******************************************************************************
File:         tmDpptrSrc.h
Project:      TreeMaker 5.x
Purpose:      Header file for class tmDpptrSrc
Author:       Robert J. Lang
Modified by:  
Created:      2003-11-15
Copyright:    2003 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#ifndef _TMDPPTRSRC_H_
#define _TMDPPTRSRC_H_

#include "tmDpptrTarget.h"

/**********
class tmDpptrSrc
Base class for any object that implements dangle-proof pointers to objects of
type tmDpptrTarget
**********/
class tmDpptrSrc
{
public:
  virtual ~tmDpptrSrc() {};
protected:
  // Used by subclasses
  void DstAddMeAsDpptrSrc(tmDpptrTarget* aDpptrTarget) {
    if (aDpptrTarget) {
      aDpptrTarget->AddDpptrSrc(this);
    }
  };
  void DstRemoveMeAsDpptrSrc(tmDpptrTarget* aDpptrTarget) {
    // Early return for null pointer
    if (!aDpptrTarget) return;
    
    // Store both pointers as const before any operations
    tmDpptrSrc* const self = this;
    tmDpptrTarget* const target = aDpptrTarget;
    
    // Validate pointers before use
    if (self && target) {
      target->RemoveDpptrSrc(self);
    }
  };

  // Implemented by subclasses
  virtual void RemoveDpptrTarget(tmDpptrTarget*) {};
private:
  friend class tmDpptrTarget;
};

#endif // _TMDPPTRSRC_H_
