#ifndef __UI_H__
#define __UI_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   wx_gui  - wxWidgets GUI
*/

#include "ui_base.h"

#ifdef AZ_GUI_WX
    #include "ui_wx.h"
#else
    #include "ui_min.h"
    #define AZ_UI_MIN
#endif

#endif
