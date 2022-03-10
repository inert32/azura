#ifndef __UI_H__
#define __UI_H__

/* Header file ui.h
   Contain all avaliable UIs:
   min_tui - based on simple console UI
   curses_ui - *curses console UI
   win_ui - Windows-only graphical UI
*/


#ifdef __linux__
	#include <unistd.h>
	#include <ncurses.h>
#else
	#include <Windows.h>
	//#include "pdcurses.h"
#endif

#include "ui_min.h"
#include "ui_curses.h"

#ifndef __linux__
	#include "ui_win.h"
#endif

#endif