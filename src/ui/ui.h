#ifndef __UI_H__
#define __UI_H__

#include "ui_base.h"
#include "../config.h"
#include "../locale.h"

#ifdef AZ_CURSES
    #define AZ_USE_CURSES_UI
    #include <curses.h>
    #include "ui_curses.h"
    #define current_ui curses_ui
#else
    #define AZ_USE_MIN_UI
    #include "ui_min.h"
    #define current_ui min_ui
#endif /* AZ_CURSES */

#endif /* __UI_H__ */