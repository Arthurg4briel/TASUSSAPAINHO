/*****************************************************************************
 *   vistar.h                                 Version 20180714.101818        *
 *                                                                           *
 *   Brief description                                                       *
 *   Copyright (C) 2016-2025    by Ruben Carlo Benante                       *
 *****************************************************************************
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License.          *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************
 *   To contact the author, please write to:                                 *
 *   Ruben Carlo Benante                                                     *
 *   Email: rcb@beco.cc                                                      *
 *   Webpage: www.beco.cc                                                    *
 *   Phone: +55 (81) 3184-7555                                               *
 *****************************************************************************/

#ifndef VISTAR_H
#define VISTAR_H

/* ------------------------------------------------------------------------- */
/* includes */

#include <ncurses.h>
#include "libvistar.h"
/* ------------------------------------------------------------------------- */
/* defines */

#define CTRL(c) ((c) & 0x1f)

/* ------------------------------------------------------------------------- */
/* globals */
typedef struct vistar_s
{
    WINDOW *help_win;
    WINDOW *status_win;

    bool help_visible;

    TextBuffer *buffer;

    char filename[256];

    bool modified;

    int cursor_x;
    int cursor_y;

    int block_begin_line;
    int block_begin_col;
    int block_end_line;
    int block_end_col;
    bool block_active;

    Clipboard *clipboard;
    char search_term[256];

}

vistar_t;

extern vistar_t editor;

#define help_win editor.help_win
#define status_win editor.status_win
#define help_visible editor.help_visible
#define buffer editor.buffer
#define filename editor.filename
#define modified editor.modified
#define cursor_x editor.cursor_x
#define cursor_y editor.cursor_y

void init_interface(void);
void update_status(void);
void toggle_help(void);
void cleanup(void);
void draw_text(void);
void prompt_filename(char *prompt_msg, char *input_buffer, int max_len);
void prompt_search(char *prompt_msg, char *input_buffer, int max_len);

void help(void);
void copyr(void);
void vistar_init(void);

#endif

/* ------------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline    */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20180716.101436   */

