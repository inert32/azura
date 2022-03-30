#ifndef __UI_H__
#define __UI_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   wx_gui  - wxWidgets GUI
*/

#include "ui_base.h"

#include "ui_min.h"

#define az_ui min_ui

#ifdef AZ_GUI_WX
    #undef az_ui
    #include "ui_wx.h"
    #define az_ui wx_gui
#endif

#endif
