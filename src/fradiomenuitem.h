// File: fradiomenuitem.h
// Provides: class FRadioMenuItem
//
//  Inheritance diagram
//  ═══════════════════
//
// ▕▔▔▔▔▔▔▔▔▔▏ ▕▔▔▔▔▔▔▔▔▔▏
// ▕ FObject ▏ ▕  FTerm  ▏
// ▕▁▁▁▁▁▁▁▁▁▏ ▕▁▁▁▁▁▁▁▁▁▏
//      ▲           ▲
//      │           │
//      └─────┬─────┘
//            │
//       ▕▔▔▔▔▔▔▔▔▔▏
//       ▕ FWidget ▏
//       ▕▁▁▁▁▁▁▁▁▁▏
//            ▲
//            │
//      ▕▔▔▔▔▔▔▔▔▔▔▔▏
//      ▕ FMenuItem ▏
//      ▕▁▁▁▁▁▁▁▁▁▁▁▏
//            ▲
//            │
//    ▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏*       1▕▔▔▔▔▔▔▔▏
//    ▕ FRadioMenuItem ▏- - - - -▕ FMenu ▏
//    ▕▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏         ▕▁▁▁▁▁▁▁▏

#ifndef _FRADIOMENUITEM_H
#define _FRADIOMENUITEM_H

#include "fmenuitem.h"


//----------------------------------------------------------------------
// class FRadioMenuItem
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FRadioMenuItem : public FMenuItem
{
 private:
   FRadioMenuItem (const FRadioMenuItem&);
   FRadioMenuItem& operator = (const FRadioMenuItem&);
   void init (FWidget*);
   void processToggle();
   void processClicked();

 public:
   explicit FRadioMenuItem (FWidget* = 0);
   FRadioMenuItem (FString&, FWidget* = 0);
   FRadioMenuItem (const std::string&, FWidget* = 0);
   FRadioMenuItem (const char*, FWidget* = 0);
   virtual ~FRadioMenuItem();
   const char* getClassName() const;
};
#pragma pack(pop)


// FRadioMenuItem inline functions
//----------------------------------------------------------------------
inline const char* FRadioMenuItem::getClassName() const
{ return "FRadioMenuItem"; }

#endif  // _FRADIOMENUITEM_H