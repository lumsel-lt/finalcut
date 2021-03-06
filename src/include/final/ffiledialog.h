/***********************************************************************
* ffiledialog.h - Widget FFileDialog (a file chooser dialog)           *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2014-2020 Markus Gans                                      *
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
 *       ▕ FWindow ▏
 *       ▕▁▁▁▁▁▁▁▁▁▏
 *            ▲
 *            │
 *       ▕▔▔▔▔▔▔▔▔▔▏
 *       ▕ FDialog ▏
 *       ▕▁▁▁▁▁▁▁▁▁▏
 *            ▲
 *            │
 *     ▕▔▔▔▔▔▔▔▔▔▔▔▔▔▏
 *     ▕ FFileDialog ▏
 *     ▕▁▁▁▁▁▁▁▁▁▁▁▁▁▏
 */

#ifndef FFILEDIALOG_H
#define FFILEDIALOG_H

#if !defined (USE_FINAL_H) && !defined (COMPILE_FINAL_CUT)
  #error "Only <final/final.h> can be included directly."
#endif

#include <sys/param.h>
#include <sys/types.h>

#include <dirent.h>
#include <fnmatch.h>
#include <libgen.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "final/fbutton.h"
#include "final/fcheckbox.h"
#include "final/fdialog.h"
#include "final/flineedit.h"
#include "final/flistbox.h"
#include "final/fmessagebox.h"
#include "final/fstatusbar.h"
#include "final/fterm.h"

namespace finalcut
{

// class forward declaration
class FSystem;

//----------------------------------------------------------------------
// class FFileDialog
//----------------------------------------------------------------------

class FFileDialog : public FDialog
{
  public:
    // Enumeration
    enum DialogType
    {
      Open = 0,
      Save = 1
    };

    // Constructors
    explicit FFileDialog (FWidget* = nullptr);
    FFileDialog (const FFileDialog&);  // copy constructor
    FFileDialog ( const FString&
                , const FString&
                , DialogType = FFileDialog::Open
                , FWidget* = nullptr );

    // Destructor
    ~FFileDialog() override;

    // Assignment operator (=)
    FFileDialog& operator = (const FFileDialog&);

    // Accessors
    const FString        getClassName() const override;
    const FString        getPath() const;
    const FString        getFilter() const;
    const FString        getSelectedFile() const;
    bool                 getShowHiddenFiles();

    // Mutators
    void                 setPath (const FString&);
    void                 setFilter (const FString&);
    bool                 setShowHiddenFiles(bool);
    bool                 setShowHiddenFiles();
    bool                 unsetShowHiddenFiles();

    // Event handler
    void                 onKeyPress (FKeyEvent*) override;

    // Methods
    static const FString fileOpenChooser ( FWidget*
                                         , const FString& = FString()
                                         , const FString& = FString() );
    static const FString fileSaveChooser ( FWidget*
                                         , const FString& = FString()
                                         , const FString& = FString() );

  protected:
    // Method
    void                 adjustSize() override;

  private:
    // Typedef
    struct dir_entry
    {
      char* name;
      // Type of file
      uChar fifo             : 1;
      uChar character_device : 1;
      uChar directory        : 1;
      uChar block_device     : 1;
      uChar regular_file     : 1;
      uChar symbolic_link    : 1;
      uChar socket           : 1;
      uChar                  : 1;  // padding bits
    };

    typedef std::vector<dir_entry> dirEntries;

    // Methods
    void                 init();
    void                 widgetSettings (const FPoint&);
    void                 initCallbacks();
    bool                 pattern_match (const char* const, char[]);
    void                 clear();
    sInt64               numOfDirs();
    void                 sortDir();
    int                  readDir();
    void                 getEntry (const char* const, struct dirent*);
    void                 followSymLink (const char* const, dir_entry&);
    void                 dirEntriesToList();
    void                 selectDirectoryEntry (const char* const);
    int                  changeDir (const FString&);
    void                 printPath (const FString&);
    static const FString getHomeDir();

    // Callback methods
    void                 cb_processActivate (FWidget*, FDataPtr);
    void                 cb_processRowChanged (FWidget*, FDataPtr);
    void                 cb_processClicked (FWidget*, FDataPtr);
    void                 cb_processCancel (FWidget*, FDataPtr);
    void                 cb_processOpen (FWidget*, FDataPtr);
    void                 cb_processShowHidden (FWidget*, FDataPtr);

    // Data members
    static FSystem*  fsystem;
    DIR*             directory_stream{nullptr};
    dirEntries       dir_entries{};
    FString          directory{};
    FString          filter_pattern{};
    FLineEdit        filename{this};
    FListBox         filebrowser{this};
    FCheckBox        hidden_check{this};
    FButton          cancel_btn{this};
    FButton          open_btn{this};
    DialogType       dlg_type{FFileDialog::Open};
    bool             show_hidden{false};

    // Friend functions
    friend bool sortByName ( const FFileDialog::dir_entry&
                           , const FFileDialog::dir_entry& );
    friend bool sortDirFirst ( const FFileDialog::dir_entry&
                             , const FFileDialog::dir_entry& );
    friend const FString fileChooser ( FWidget*
                                     , const FString&
                                     , const FString&
                                     , FFileDialog::DialogType);
};

// FMessageBox inline functions
//----------------------------------------------------------------------
inline const FString FFileDialog::getClassName() const
{ return "FFileDialog"; }

//----------------------------------------------------------------------
inline const FString FFileDialog::getPath() const
{ return directory; }

//----------------------------------------------------------------------
inline const FString FFileDialog::getFilter() const
{ return filter_pattern; }

//----------------------------------------------------------------------
inline bool FFileDialog::setShowHiddenFiles()
{ return setShowHiddenFiles(true); }

//----------------------------------------------------------------------
inline bool FFileDialog::unsetShowHiddenFiles()
{ return setShowHiddenFiles(false); }

//----------------------------------------------------------------------
inline bool FFileDialog::getShowHiddenFiles()
{ return show_hidden; }

}  // namespace finalcut

#endif  // FFILEDIALOG_H
