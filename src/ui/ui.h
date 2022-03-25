#ifndef __UI_H__
#define __UI_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   curses_ui - *curses console UI
   win_ui - Windows-only graphical UI
   
   As well enables UIs if avaliable (based on platform and *curses presence)
*/

#include "ui_base.h"

#include "ui_min.h"

#define az_ui min_tui

#ifdef AZ_GUI_WX
    #undef az_ui
    #include "ui_wx.h"
    #define az_ui wx_gui
#endif

#endif
