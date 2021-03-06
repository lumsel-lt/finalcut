/***********************************************************************
* watch.cpp - A watch with FSwitch widgets                             *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2015-2020 Markus Gans                                      *
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

#include <ctime>
#include <final/final.h>

using finalcut::FPoint;
using finalcut::FSize;


//----------------------------------------------------------------------
// class Watch
//----------------------------------------------------------------------

class Watch : public finalcut::FDialog
{
  public:
    // Constructor
    explicit Watch (finalcut::FWidget* = nullptr);

    // Disable copy constructor
    Watch (const Watch&) = delete;

    // Destructor
    ~Watch() override;

    // Disable assignment operator (=)
    Watch& operator = (const Watch&) = delete;

    // Method
    void printTime();

    // Event handlers
    void onTimer (finalcut::FTimerEvent*) override;
    void onClose (finalcut::FCloseEvent*) override;

    // Callback methods
    void cb_clock (finalcut::FWidget*, FDataPtr);
    void cb_seconds (finalcut::FWidget*, FDataPtr);

  protected:
    // Method
    void adjustSize() override;

  private:
    // Data members
    bool              sec{true};
    finalcut::FLabel  time_label{L"Time", this};
    finalcut::FLabel  time_str{L"--:--:--", this};
    finalcut::FSwitch clock_sw{L"Clock", this};
    finalcut::FSwitch seconds_sw{L"Seconds", this};
    finalcut::FButton quit_btn{L"&Quit", this};
};

//----------------------------------------------------------------------
Watch::Watch (FWidget* parent)
  : finalcut::FDialog(parent)
{
  setText ("Watch");
  const int pw = int(getParentWidget()->getWidth());
  setGeometry (FPoint(1 + (pw - 22) / 2, 3), FSize(22, 13));

  // Labels
  time_label.setGeometry(FPoint(5, 2), FSize(5, 1));
  time_label.setEmphasis();
  time_str.setGeometry(FPoint(10, 2), FSize(8, 1));

  // Checkbox buttons
  clock_sw.setGeometry(FPoint(4, 4), FSize(9, 1));
  seconds_sw.setGeometry(FPoint(2, 6), FSize(11, 1));
  sec = seconds_sw.setChecked();

  // Quit button
  quit_btn.setGeometry(FPoint(6, 9), FSize(9, 1));

  // Connect switch signal "toggled" with a callback member function
  clock_sw.addCallback
  (
    "toggled",
    F_METHOD_CALLBACK (this, &Watch::cb_clock)
  );

  // Connect switch signal "toggled" with a callback member function
  seconds_sw.addCallback
  (
    "toggled",
    F_METHOD_CALLBACK (this, &Watch::cb_seconds)
  );

  // Connect button signal "clicked" with a callback member function
  quit_btn.addCallback
  (
    "clicked",
    F_METHOD_CALLBACK (this, &finalcut::FApplication::cb_exitApp)
  );
}

//----------------------------------------------------------------------
Watch::~Watch()
{
  delOwnTimer();
}

//----------------------------------------------------------------------
void Watch::printTime()
{
  finalcut::FString str{};
  std::tm now{};

  const std::time_t t = std::time(nullptr);  // get current time
  localtime_r(&t, &now);

  if ( sec )
    str.sprintf("%02d:%02d:%02d", now.tm_hour, now.tm_min, now.tm_sec);
  else
    str.sprintf("%02d:%02d   ", now.tm_hour, now.tm_min);

  time_str = str;
  time_str.redraw();
}

//----------------------------------------------------------------------
void Watch::onTimer (finalcut::FTimerEvent*)
{
  printTime();
}

//----------------------------------------------------------------------
void Watch::onClose (finalcut::FCloseEvent* ev)
{
  finalcut::FApplication::closeConfirmationDialog (this, ev);
}

//----------------------------------------------------------------------
void Watch::cb_clock (finalcut::FWidget*, FDataPtr)
{
  if ( clock_sw.isChecked() )
  {
    printTime();
    addTimer(1000);
  }
  else
  {
    delAllTimer();
    time_str = "--:--:--";
    time_str.redraw();
  }
}

//----------------------------------------------------------------------
void Watch::cb_seconds (finalcut::FWidget*, FDataPtr)
{
  if ( seconds_sw.isChecked() )
    sec = true;
  else
    sec = false;

  if ( clock_sw.isChecked() )
    printTime();
  else
  {
    if ( sec )
      time_str = "--:--:--";
    else
      time_str = "--:--   ";

    time_str.redraw();
  }
}

//----------------------------------------------------------------------
void Watch::adjustSize()
{
  const int pw = int(getParentWidget()->getWidth());
  setX (1 + (pw - 22) / 2, false);
  finalcut::FDialog::adjustSize();
}

//----------------------------------------------------------------------
//                               main part
//----------------------------------------------------------------------
int main (int argc, char* argv[])
{
  // Create the application object
  finalcut::FApplication app(argc, argv);

  // Create a simple dialog box
  Watch w(&app);

  // Set dialog w as main widget
  app.setMainWidget(&w);

  // Show and start the application
  w.show();
  return app.exec();
}
