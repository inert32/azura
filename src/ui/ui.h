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

#include "ui_curses.h"

#ifndef __linux__
    #include "ui_win.h"
#endif

#endif
