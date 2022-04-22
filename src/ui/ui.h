#ifndef __UI_H__
#define __UI_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   wx_gui  - wxWidgets GUI
*/

#include "ui_base.h"

#define start() int main(int argc, char** argv)

#ifdef AZ_GUI_WX
    #include "ui_wx.h"
    #define AZ_CURRENT_UI wx_gui
    #ifdef __VISUALC__
        #undef start()
        #define start() int wmain(int argc, wchar_t **argv)
    #endif /* __VISUALC__ */
#else
    #define AZ_CURRENT_UI min_ui
    #include "ui_min.h"
#endif /* AZ_GUI_WX */

#endif /* __UI_H__ */