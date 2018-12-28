/***********************************************************************
* fbutton.h - Widget FButton                                           *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2012-2018 Markus Gans                                      *
*                                                                      *
* The Final Cut is free software; you can redistribute it and/or       *
* modify it under the terms of the GNU Lesser General Public License   *
* as published by the Free Software Foundation; either version 3 of    *
* the License, or (at your option) any later version.                  *
*                                                                      *
* The Final Cut is distributed in the hope that it will be useful,     *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

/*  Inheritance diagram
 *  ═══════════════════
 *
 * ▕▔▔▔▔▔▔▔▔▔▏
 * ▕  FTerm  ▏
 * ▕▁▁▁▁▁▁▁▁▁▏
 *      ▲
 *      │
 * ▕▔▔▔▔▔▔▔▔▔▏ ▕▔▔▔▔▔▔▔▔▔▏
 * ▕ FVTerm  ▏ ▕ FObject ▏
 * ▕▁▁▁▁▁▁▁▁▁▏ ▕▁▁▁▁▁▁▁▁▁▏
 *      ▲           ▲
 *      │           │
 *      └─────┬─────┘
 *            │
 *       ▕▔▔▔▔▔▔▔▔▔▏
 *       ▕ FWidget ▏
 *       ▕▁▁▁▁▁▁▁▁▁▏
 *            ▲
 *            │
 *       ▕▔▔▔▔▔▔▔▔▔▏
 *       ▕ FButton ▏
 *       ▕▁▁▁▁▁▁▁▁▁▏
 */

#ifndef FBUTTON_H
#define FBUTTON_H

#if !defined (USE_FINAL_H) && !defined (COMPILE_FINAL_CUT)
  #error "Only <final/final.h> can be included directly."
#endif

#include "final/fwidget.h"

namespace finalcut
{

//----------------------------------------------------------------------
// class FButton
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FButton : public FWidget
{
  public:
    // Constructors
    explicit FButton (FWidget* = nullptr);
    explicit FButton (const FString&, FWidget* = nullptr);

    // Disable copy constructor
    FButton (const FButton&) = delete;

    // Destructor
    virtual ~FButton();

    // Disable assignment operator (=)
    FButton& operator = (const FButton&) = delete;

    // Overloaded operator
    FButton& operator = (const FString&);

    // Accessors
    const char*  getClassName() const;
    FString&     getText();

    // Mutators
    void         setForegroundColor (FColor);
    void         setBackgroundColor (FColor);
    void         setHotkeyForegroundColor (FColor);
    void         setFocusForegroundColor (FColor);
    void         setFocusBackgroundColor (FColor);
    void         setInactiveForegroundColor (FColor);
    void         setInactiveBackgroundColor (FColor);
    bool         setNoUnderline(bool);
    bool         setNoUnderline();
    bool         unsetNoUnderline();
    virtual bool setEnable(bool);
    virtual bool setEnable();
    virtual bool unsetEnable();
    virtual bool setDisable();
    virtual bool setFocus(bool);
    virtual bool setFocus();
    virtual bool unsetFocus();
    bool         setFlat(bool);
    bool         setFlat();
    bool         unsetFlat();
    bool         setShadow(bool);
    bool         setShadow();
    bool         unsetShadow();
    bool         setDown(bool);
    bool         setDown();
    bool         setUp();
    bool         setClickAnimation(bool);
    bool         setClickAnimation();
    bool         unsetClickAnimation();
    void         setText (const FString&);

    // Inquiries
    bool         isFlat() const;
    bool         isDown() const;
    bool         hasShadow() const;
    bool         hasClickAnimation();

    // Methods
    virtual void hide();

    // Event handlers
    virtual void onKeyPress (FKeyEvent*);
    virtual void onMouseDown (FMouseEvent*);
    virtual void onMouseUp (FMouseEvent*);
    virtual void onMouseMove (FMouseEvent*);
    virtual void onTimer (FTimerEvent*);
    virtual void onAccel (FAccelEvent*);
    virtual void onFocusIn (FFocusEvent*);
    virtual void onFocusOut (FFocusEvent*);

  private:
    // Constants
    static constexpr std::size_t NOT_SET = static_cast<std::size_t>(-1);

    // Methods
    void         init();
    uChar        getHotkey();
    void         setHotkeyAccelerator();
    void         detectHotkey();
    std::size_t  getHotkeyPos (wchar_t[], wchar_t[], std::size_t);
    std::size_t  clickAnimationIndent (FWidget*);
    void         clearRightMargin (FWidget*);
    void         drawMarginLeft();
    void         drawMarginRight();
    void         drawTopBottomBackground();
    void         drawButtonTextLine (wchar_t[]);
    virtual void draw();
    void         updateStatusBar();
    void         updateButtonColor();
    void         processClick();

    // Data Members
    FString      text{};
    bool         button_down{false};
    bool         active_focus{false};
    bool         click_animation{true};
    int          click_time{150};
    int          space_char{int(' ')};
    std::size_t  hotkeypos{NOT_SET};
    std::size_t  indent{0};
    std::size_t  center_offset{0};
    std::size_t  vcenter_offset{0};
    std::size_t  txtlength{0};
    FColor       button_fg{wc.button_active_fg};
    FColor       button_bg{wc.button_active_bg};
    FColor       button_hotkey_fg{wc.button_hotkey_fg};
    FColor       button_focus_fg{wc.button_active_focus_fg};
    FColor       button_focus_bg{wc.button_active_focus_bg};
    FColor       button_inactive_fg{wc.button_inactive_fg};
    FColor       button_inactive_bg{wc.button_inactive_bg};
};
#pragma pack(pop)


// FButton inline functions
//----------------------------------------------------------------------
inline const char* FButton::getClassName() const
{ return "FButton"; }

//----------------------------------------------------------------------
inline FString& FButton::getText()
{ return text; }

//----------------------------------------------------------------------
inline bool FButton::setNoUnderline()
{ return setNoUnderline(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetNoUnderline()
{ return setNoUnderline(false); }

//----------------------------------------------------------------------
inline bool FButton::setEnable()
{ return setEnable(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetEnable()
{ return setEnable(false); }

//----------------------------------------------------------------------
inline bool FButton::setDisable()
{ return setEnable(false); }

//----------------------------------------------------------------------
inline bool FButton::setFocus()
{ return setFocus(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetFocus()
{ return setFocus(false); }

//----------------------------------------------------------------------
inline bool FButton::setFlat()
{ return setFlat(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetFlat()
{ return setFlat(false); }

//----------------------------------------------------------------------
inline bool FButton::setShadow()
{ return setShadow(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetShadow()
{ return setShadow(false); }

//----------------------------------------------------------------------
inline bool FButton::setDown()
{ return setDown(true); }

//----------------------------------------------------------------------
inline bool FButton::setUp()
{ return setDown(false); }

//----------------------------------------------------------------------
inline bool FButton::setClickAnimation(bool enable)
{ return (click_animation = enable); }

//----------------------------------------------------------------------
inline bool FButton::setClickAnimation()
{ return setClickAnimation(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetClickAnimation()
{ return setClickAnimation(false); }

//----------------------------------------------------------------------
inline bool FButton::isFlat() const
{ return flags.flat; }

//----------------------------------------------------------------------
inline bool FButton::isDown() const
{ return button_down; }

//----------------------------------------------------------------------
inline bool FButton::hasShadow() const
{ return flags.shadow; }

//----------------------------------------------------------------------
inline bool FButton::hasClickAnimation()
{ return click_animation; }

}  // namespace finalcut

#endif  // FBUTTON_H
