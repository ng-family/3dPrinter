/*************************
 * advanced_settings.cpp *
 *************************/

/****************************************************************************
 *   Written By Mark Pelletier  2017 - Aleph Objects, Inc.                  *
 *   Written By Marcio Teixeira 2018 - Aleph Objects, Inc.                  *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <https://www.gnu.org/licenses/>.                             *
 ****************************************************************************/

#include "../config.h"
#include "../screens.h"

#ifdef FTDI_BIO_ADVANCED_SETTINGS_MENU

using namespace FTDI;
using namespace Theme;

#define GRID_COLS 2
#define GRID_ROWS 9

void AdvancedSettingsMenu::onRedraw(draw_mode_t what) {
  if (what & BACKGROUND) {
    CommandProcessor cmd;
    cmd.cmd(CLEAR_COLOR_RGB(Theme::bg_color))
       .cmd(CLEAR(true,true,true));
  }

  if (what & FOREGROUND) {
    CommandProcessor cmd;
    cmd.colors(normal_btn)
      .font(Theme::font_medium)

      .tag(2) .button(BTN_POS(1,1), BTN_SIZE(1,1), GET_TEXT_F(MSG_DISPLAY_MENU))
              .enabled(ENABLED(HAS_TRINAMIC_CONFIG))
      .tag(3) .button(BTN_POS(1,2), BTN_SIZE(1,1), GET_TEXT_F(MSG_TMC_CURRENT))
              .enabled(ENABLED(HAS_TRINAMIC_CONFIG))
      .tag(4) .button(BTN_POS(1,3), BTN_SIZE(1,1), GET_TEXT_F(MSG_TMC_HOMING_THRS))
      .tag(5) .button(BTN_POS(1,4), BTN_SIZE(1,1), GET_TEXT_F(MSG_LCD_ENDSTOPS))
              .enabled(ENABLED(HAS_MULTI_HOTEND))
      .tag(6) .button(BTN_POS(1,5), BTN_SIZE(1,1), GET_TEXT_F(MSG_OFFSETS_MENU))


      .tag(7) .button(BTN_POS(2,1), BTN_SIZE(1,1), GET_TEXT_F(MSG_STEPS_PER_MM))
      .tag(8) .button(BTN_POS(2,2), BTN_SIZE(1,1), GET_TEXT_F(MSG_VELOCITY))
      .tag(9) .button(BTN_POS(2,3), BTN_SIZE(1,1), GET_TEXT_F(MSG_ACCELERATION))
      .tag(10) .button(BTN_POS(2,4), BTN_SIZE(1,1), GET_TEXT_F(TERN(HAS_JUNCTION_DEVIATION, MSG_JUNCTION_DEVIATION, MSG_JERK)))
               .enabled(ENABLED(BACKLASH_GCODE))
      .tag(11) .button(BTN_POS(2,5), BTN_SIZE(1,1), GET_TEXT_F(MSG_BACKLASH))
               .enabled(ENABLED(LIN_ADVANCE))
      .tag(12) .button(BTN_POS(1,6), BTN_SIZE(2,1), GET_TEXT_F(MSG_LINEAR_ADVANCE))
      .tag(13) .button(BTN_POS(1,7), BTN_SIZE(2,1), GET_TEXT_F(MSG_INTERFACE))
      .tag(14) .button(BTN_POS(1,8), BTN_SIZE(2,1), GET_TEXT_F(MSG_RESTORE_DEFAULTS))
               .colors(action_btn)
      .tag(1) .button( BTN_POS(1,9), BTN_SIZE(2,1), GET_TEXT_F(MSG_BUTTON_DONE));
  }
}

bool AdvancedSettingsMenu::onTouchEnd(uint8_t tag) {
  using namespace ExtUI;

  switch (tag) {
    case 1: SaveSettingsDialogBox::promptToSaveSettings(); break;
    case 2: GOTO_SCREEN(DisplayTuningScreen);              break;
    #if HAS_TRINAMIC_CONFIG
      case 3: GOTO_SCREEN(StepperCurrentScreen);           break;
      case 4: GOTO_SCREEN(StepperBumpSensitivityScreen);   break;
    #endif
    case 5: GOTO_SCREEN(EndstopStatesScreen);              break;
    #if HAS_MULTI_HOTEND
      case 6: GOTO_SCREEN(NozzleOffsetScreen);             break;
    #endif
    case 7: GOTO_SCREEN(StepsScreen);                      break;
    case 8: GOTO_SCREEN(MaxVelocityScreen);                break;
    case 9: GOTO_SCREEN(DefaultAccelerationScreen);        break;
    case 10: GOTO_SCREEN(TERN(HAS_JUNCTION_DEVIATION, JunctionDeviationScreen, JerkScreen)); break;
    #if ENABLED(BACKLASH_GCODE)
      case 11: GOTO_SCREEN(BacklashCompensationScreen);    break;
    #endif
    #if ENABLED(LIN_ADVANCE)
      case 12: GOTO_SCREEN(LinearAdvanceScreen);           break;
    #endif
    case 13: GOTO_SCREEN(InterfaceSettingsScreen);         break;
    case 14: GOTO_SCREEN(RestoreFailsafeDialogBox);        break;
    default: return false;
  }
  return true;
}

#endif // FTDI_BIO_ADVANCED_SETTINGS_MENU
