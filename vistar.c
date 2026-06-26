/*****************************************************************************
 *   exN.c                                    Version 20180714.101818        *
 *                                                                           *
 *   Brief description                                                       *
 *   Copyright (C) 2016-2018    by Ruben Carlo Benante                       *
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

/* ------------------------------------------------------------------------- */
/**
 * @file exN.c
 * @ingroup GroupUnique
 * @brief Brief description
 * @details This program really do a nice job as a template, and template only!
 * @version 20160908.182830
 * @date 2016-09-08
 * @author Ruben Carlo Benante <<rcb@beco.cc>>
 * @par Webpage
 * <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @copyright (c) 2016 GNU GPL v2
 * @note This program is free software: you can redistribute it
 * and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA. 02111-1307, USA.
 * Or read it online at <<http://www.gnu.org/licenses/>>.
 *
 *
 * @todo Now that you have the template, hands on! Programme!
 * @warning Be carefull not to lose your mind in small things.
 * @bug This file right now does nothing usefull
 *
 */

/*
 * Instrucoes para compilar:
 *   $gcc exN.c -o exN.x -Wall
 *        -Wextra -ansi -pedantic-errors -g -O0 -DDEBUG=1 -DVERSION="0.1.160612.142044"
 *   ou preferencialmente inclua um makefile e use:
 *   $make
 *
 * Modelo de indentacao:
 * Estilo: --style=allman ou -A1
 *
 * Opcoes: -A1 -s4 -k3 -xj -SCNeUpv
 *
 *  * No vi use:
 *      :% !astyle -A1 -s4 -k3 -xj -SCNeUpv
 *  * No linux:
 *      $astlye -A1 -s4 -k3 -xj -SCNeUpv exN.c
 */

/* ------------------------------------------------------------------------- */
/* includes */

/* #include <bits/getopt_core.h> */
#include <curses.h>
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Miscellaneous functions (rand, malloc, srand)*/
#include <getopt.h> /* get options from system argc/argv */
#include <bits/getopt_core.h>
#include <ncurses.h> /* Screen handling and optimisation functions */
#include <string.h> /* Strings functions definitions */
#include "vistar.h" /* To be created for this template if needed */
#include "libvistar.h" /* library for the editor */

/* #include <time.h> */ /* Time and date functions */
/* #include <math.h> */ /* Mathematics functions */
/* #include <malloc.h> */ /* Dynamic memory allocation */
/* #include <unistd.h> */ /* UNIX standard function */
/* #include <limits.h> */ /* Various C limits */
/* #include <ctype.h> */ /* Character functions */
/* #include <errno.h> */ /* Error number codes errno */
/* #include <signal.h> */ /* Signal processing */
/* #include <stdarg.h> */ /* Functions with variable arguments */
/* #include <fcntl.h> */ /* File control definitions */
/* #include <termios.h> */ /* Terminal I/O definitions POSIX */
/* #include <sys/stat.h> */ /* File status and information */
/* #include <float.h> */ /* Float constants to help portability */
/* #include <stddef.h> */ /* Various types and MACROS */
/* #include <libintl.h> */ /* Internationalization / translation */
/* #include <locale.h> */ /* MACROS LC_ for location specific settings */
/* #include "libeco.h" */ /* I/O, Math, Sound, Color, Portable Linux/Windows */

#include <ctype.h>

vistar_t editor = {0};
int verb = 0;
/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This is the main event of the evening
 * @details Ladies and Gentleman... It's tiiiime!
 * Fightiiiiing at the blue corner,
 * he, who has compiled more C code than any other adversary in the history,
 * he, who has developed UNIX and Linux, and is an inspiration to maaany languages
 * and compilers, the GNU C Compiler, GCC!
 * Fightiiiiing at the red corner, the challenger, in his first fight, lacking of any
 * valid experience but angrily, blindly, and no doubtfully, will try to
 * compile this program without errors. He, the student, the apprentice,
 * the developer, beco!!
 *
 * @param[in] argc Argument counter
 * @param[in] argv Argument strings (argument values)
 *
 * @retval 0 If succeed (EXIT_SUCCESS).
 * @retval 1 Or another error code if failed.
 *
 * @par Example
 * @code
 *    $./exN -h
 * @endcode
 *
 * @warning   Be carefull with...
 * @bug There is a bug with...
 * @todo Need to do...
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Arthur Gabriel Damascena Alves Da Costa
 * @version 20160908.182830
 * @date 2026-06-25
 *
 */
int main(int argc, char *argv[])
{
    int opt;
    int ch;

    opterr = 0;
    while((opt = getopt(argc, argv, "vhV")) != EOF)
        switch(opt)
        {
            case 'h': help(); break;
            case 'V': copyr(); break;
            case 'v': verb++; break;
            case '?':
            default:
                printf("Type\n\t$man %s\nor\n\t$%s -h\nfor help.\n\n", argv[0], argv[0]);
                return EXIT_FAILURE;
        }

    vistar_init();
    init_interface();

    if (optind < argc)
    {
        strncpy(filename, argv[optind], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        load_file(buffer, filename);
    }

    bool expect_ctrl_k = false;
    bool expect_ctrl_q = false;

    while(1)
    {
        if(cursor_y < buffer->top_line) {
            buffer->top_line = cursor_y;
        } else {
            int max_visible = LINES - 2 - (help_visible ? 7 : 0);
            if(cursor_y > buffer->top_line + max_visible) {
                buffer->top_line = cursor_y - max_visible;
            }
        }

        draw_text();
        wnoutrefresh(stdscr);
        update_status();
        if(help_visible && help_win) {
            touchwin(help_win); /* Força o ncurses a respeitar a prioridade Z-order do Help */
            wnoutrefresh(help_win);
        }

        int screen_y = cursor_y - buffer->top_line + (help_visible ? 7 : 0);
        move(screen_y, cursor_x);
        doupdate();

        ch = getch();
        if(expect_ctrl_k) {
            expect_ctrl_k = false;
            ch = toupper(ch);
            switch(ch) {
                case 'B':
                    editor.block_begin_line = cursor_y;
                    editor.block_begin_col = cursor_x;
                    editor.block_active = false;
                    break;
                case 'K':
                    editor.block_end_line = cursor_y;
                    editor.block_end_col = cursor_x;
                    editor.block_active = true;
                    break;
                case 'C':
                    if(editor.block_active) {
                        copy_block(buffer, editor.clipboard, editor.block_begin_line, editor.block_begin_col, editor.block_end_line, editor.block_end_col);
                        editor.block_active = false;
                    }
                    break;
                case 'V':
                    paste_block(buffer, editor.clipboard, &cursor_y, &cursor_x);
                    modified = true;
                    break;
                case 'Y':
                    if(editor.block_active) {
                        cut_block(buffer, editor.clipboard, editor.block_begin_line, editor.block_begin_col, editor.block_end_line, editor.block_end_col, &cursor_y, &cursor_x);
                        editor.block_active = false;
                        modified = true;
                    }
                    break;
                case 'S':
                    if(filename[0] == '\0') {
                        prompt_filename("Save file as: ", filename, sizeof(filename));
                    }
                    if(filename[0] != '\0') {
                        if(save_file(buffer, filename)) modified = false;
                    }
                    break;
                case 'O':
                    {
                        char temp_name[256];
                        prompt_filename("Open file: ", temp_name, sizeof(temp_name));
                        if(temp_name[0] != '\0') {
                            if(load_file(buffer, temp_name)) {
                                strcpy(filename, temp_name);
                                cursor_y = 0; cursor_x = 0;
                                modified = false;
                                editor.block_active = false;
                            }
                        }
                    }
                    break;
                case 'N':
                    new_file(buffer);
                    filename[0] = '\0';
                    cursor_y = 0; cursor_x = 0;
                    modified = false;
                    editor.block_active = false;
                    break;
                case 'Q':
                    if(modified) {
                        char resp[10];
                        prompt_filename("Unsaved changes! Quit anyway? (y/n): ", resp, sizeof(resp));
                        if(resp[0] == 'y' || resp[0] == 'Y') goto exit_loop;
                    } else {
                        goto exit_loop;
                    }
                    break;
                default:
                    if(ch >= '0' && ch <= '9') {
                        set_marker(buffer, ch - '0', cursor_y, cursor_x);
                    }
                    break;
            }
        }
        else if(expect_ctrl_q) {
            expect_ctrl_q = false;
            ch = toupper(ch);
            switch(ch) {
                case 'S': cursor_x = 0; break;
                case 'D': cursor_x = buffer->line_lengths[cursor_y]; break;
                case 'R': cursor_y = 0; cursor_x = 0; break;
                case 'C': cursor_y = buffer->num_lines - 1; cursor_x = buffer->line_lengths[cursor_y]; break;
                case 'F':
                    prompt_search("Search for: ", editor.search_term, sizeof(editor.search_term));
                    if(editor.search_term[0] != '\0') {
                        int search_l = cursor_y, search_c = cursor_x;
                        if(search_text(buffer, editor.search_term, &search_l, &search_c)) {
                            cursor_y = search_l; cursor_x = search_c;
                        }
                    }
                    break;
                default:
                    if(ch >= '0' && ch <= '9') {
                        goto_marker(buffer, ch - '0', &cursor_y, &cursor_x);
                    }
                    break;
            }
        }
        else {
            switch(ch) {
                case CTRL('s'): if(cursor_x > 0) cursor_x--; else if(cursor_y > 0) { cursor_y--; cursor_x = buffer->line_lengths[cursor_y]; } break;
                case CTRL('d'): if(cursor_x < buffer->line_lengths[cursor_y]) cursor_x++; else if(cursor_y < buffer->num_lines - 1) { cursor_y++; cursor_x = 0; } break;
                case CTRL('e'): if(cursor_y > 0) { cursor_y--; if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y]; } break;
                case CTRL('x'): if(cursor_y < buffer->num_lines - 1) { cursor_y++; if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y]; } break;
                case CTRL('a'):
                    while(cursor_x > 0 && (buffer->lines[cursor_y][cursor_x - 1] == ' ' || buffer->lines[cursor_y][cursor_x - 1] == '\t')) cursor_x--;
                    while(cursor_x > 0 && buffer->lines[cursor_y][cursor_x - 1] != ' ' && buffer->lines[cursor_y][cursor_x - 1] != '\t') cursor_x--;
                    break;
                case CTRL('f'):
                    while(cursor_x < buffer->line_lengths[cursor_y] && buffer->lines[cursor_y][cursor_x] != ' ' && buffer->lines[cursor_y][cursor_x] != '\t') cursor_x++;
                    while(cursor_x < buffer->line_lengths[cursor_y] && (buffer->lines[cursor_y][cursor_x] == ' ' || buffer->lines[cursor_y][cursor_x] == '\t')) cursor_x++;
                    break;
                case CTRL('g'):
                    if(cursor_x < buffer->line_lengths[cursor_y]) {
                        delete_char(buffer, cursor_y, cursor_x, 1);
                        modified = true;
                    } else if(cursor_y < buffer->num_lines - 1) {
                        join_lines(buffer, cursor_y);
                        modified = true;
                    }
                    break;
                case CTRL('h'):
                case 127:
                case KEY_BACKSPACE:
                    if(cursor_x > 0) {
                        delete_char(buffer, cursor_y, cursor_x, -1);
                        cursor_x--;
                        modified = true;
                    } else if(cursor_y > 0) {
                        cursor_x = buffer->line_lengths[cursor_y - 1];
                        join_lines(buffer, cursor_y - 1);
                        cursor_y--;
                        modified = true;
                    }
                    break;
                case CTRL('t'):
                    delete_word(buffer, cursor_y, cursor_x);
                    modified = true;
                    break;
                case CTRL('y'):
                    delete_line(buffer, cursor_y);
                    if(cursor_y >= buffer->num_lines) cursor_y = buffer->num_lines - 1;
                    if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y];
                    modified = true;
                    break;
                case CTRL('k'): expect_ctrl_k = true; break;
                case CTRL('q'): expect_ctrl_q = true; break;
                case CTRL('l'):
                    if(editor.search_term[0] != '\0') {
                        int search_l = cursor_y, search_c = cursor_x + 1;
                        if(search_c >= buffer->line_lengths[search_l]) { search_l++; search_c = 0; }
                        if(search_l < buffer->num_lines && search_text(buffer, editor.search_term, &search_l, &search_c)) {
                            cursor_y = search_l; cursor_x = search_c;
                        }
                    }
                    break;
                case CTRL('j'):
                    toggle_help();
                    break;
                case '\r':
                case KEY_ENTER:
                    insert_newline(buffer, cursor_y, cursor_x);
                    cursor_y++;
                    cursor_x = 0;
                    modified = true;
                    break;
                case KEY_UP: if(cursor_y > 0) { cursor_y--; if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y]; } break;
                case KEY_DOWN: if(cursor_y < buffer->num_lines - 1) { cursor_y++; if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y]; } break;
                case KEY_LEFT: if(cursor_x > 0) cursor_x--; else if(cursor_y > 0) { cursor_y--; cursor_x = buffer->line_lengths[cursor_y]; } break;
                case KEY_RIGHT: if(cursor_x < buffer->line_lengths[cursor_y]) cursor_x++; else if(cursor_y < buffer->num_lines - 1) { cursor_y++; cursor_x = 0; } break;
                case KEY_PPAGE:
                    {
                        int scroll = LINES - 2 - (help_visible ? 7 : 0);
                        cursor_y -= scroll;
                        if (cursor_y < 0) cursor_y = 0;
                        if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y];
                    }
                    break;
                case KEY_NPAGE:
                    {
                        int scroll = LINES - 2 - (help_visible ? 7 : 0);
                        cursor_y += scroll;
                        if (cursor_y >= buffer->num_lines) cursor_y = buffer->num_lines - 1;
                        if(cursor_x > buffer->line_lengths[cursor_y]) cursor_x = buffer->line_lengths[cursor_y];
                    }
                    break;
                case KEY_RESIZE:
                    clear();
                    if(status_win) delwin(status_win);
                    status_win = newwin(1, COLS, LINES - 1, 0);
                    wbkgd(status_win, COLOR_PAIR(2));
                    if(help_visible) {
                        help_visible = false;
                        if(help_win) delwin(help_win);
                        help_win = NULL;
                        toggle_help(); /* Força recriação limpa geométrica nas novas colunas */
                    }
                    break;
                default:
                    if(ch >= 32 && ch <= 126)
                    {
                        insert_char(buffer, ch, cursor_y, cursor_x);
                        cursor_x++;
                        modified = true;
                    }
                    break;
            }
        }
    }
exit_loop:
    cleanup();
    return EXIT_SUCCESS;
}
/* Write your functions here... */

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints help information and exit
 * @details Prints help information (usually called by opt -h)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 *
 */

void help(void)
{
    IFDEBUG("help()");
    printf("%s - %s\n", "ViStar", "Brief description");
    printf("\nUsage: %s [-h|-v]\n", "ViStar");
    printf("\nOptions:\n");
    printf("\t-h,  --help\n\t\tShow this help.\n");
    printf("\t-V,  --version\n\t\tShow version and copyright information.\n");
    printf("\t-v,  --verbose\n\t\tSet verbose level (cumulative).\n");
    /* add more options here */
    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_FAILURE);
}


/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints version and copyright information and exit
 * @details Prints version and copyright information (usually called by opt -V)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 *
 */
void copyr(void)
{
    IFDEBUG("copyr()");
    printf("%s - Version %s\n", "ViStar", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2016, "Ruben Carlo Benante", "rcb@beco.cc");
    if(verb > 3) printf("copyr(): Verbose: %d\n", verb); /* -vvvv */
    exit(EXIT_FAILURE);
}
/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This function initializes some operations before start
 * @details Details to be written in
 * multiple lines
 *
 * @pre You need to call foo() before calling this function
 *
 * @param[in] i Input parameter that does bla
 * @param[out] o Parameter that outputs ble
 * @param[in,out] z The @a z variable is used as input and output
 *
 * @retval 0 Returned when bli
 * @retval 1 Error code: function returned blo
 *
 * @par Example
 * @code
 *    if(x == funcexample(i, o, z))
 *       printf("And that is it\n");
 * @endcode
 *
 * @return Void
 *
 * @warning Be carefull with blu
 * @todo Need to implement it. Its empty now. This doxygen tags are overwhelming.
 * Mandatory tags are: ingroup, brief, details, param, return, author and date.
 * The others are optional.
 *
 * @deprecated This function will be deactivated in version +11
 * @see help()
 * @see copyr()
 * @bug There is a bug with x greater than y
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 *
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 * @copyright Use this tag only if not the same as the whole file
 *
 */
void vistar_init(void)
{
    IFDEBUG("vistar_init()");
    return;
}
/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints version and copyright information and exit
 * @details Prints version and copyright information (usually called by opt -V)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 *
 */
void init_interface(void)
{
    initscr();
    raw();
    nonl();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);

    status_win = newwin(1, COLS, LINES - 1, 0);
    wbkgd(status_win, COLOR_PAIR(2));

    buffer = create_buffer();
    editor.clipboard = malloc(sizeof(Clipboard));
    editor.clipboard->num_lines = 0;

    filename[0] = '\0';
    cursor_x = 0;
    cursor_y = 0;
    modified = false;
    help_visible = false;
}

void update_status(void)
{
    werase(status_win);
    mvwprintw(status_win, 0, 0, " %s | Line: %d Col: %d%s",
              filename[0] ? filename : "[No Name]", cursor_y + 1, cursor_x + 1, modified ? " | Modified" : "");
    wnoutrefresh(status_win);
}

void toggle_help(void)
{
    help_visible = !help_visible;
    if(help_visible)
    {
        help_win = newwin(7, COLS, 0, 0);
        wbkgd(help_win, COLOR_PAIR(1));
        wprintw(help_win, "  MOVE                        EDIT                    BLOCK                 FILE\n");
        wprintw(help_win, "  ^S left  ^D right           ^G del char            ^KB begin             ^KS save\n");
        wprintw(help_win, "  ^E up    ^X down            ^H backspace           ^KK end               ^KO open\n");
        wprintw(help_win, "  ^A <word ^F >word           ^T del word            ^KC copy              ^KN new\n");
        wprintw(help_win, "  ^QS bol  ^QD eol            ^Y del line            ^KV paste             ^KQ exit\n");
        wprintw(help_win, "  ^QR top  ^QC bottom         ^QF search             ^KY cut               ^J toggle help\n");
        wprintw(help_win, "                             ^K0-9 set mark\n");
        wprintw(help_win, "                             ^Q0-9 goto mark\n");
        wnoutrefresh(help_win);
    }
    else
    {
        delwin(help_win);
        help_win = NULL;
    }
}

void cleanup(void)
{
    if(help_win) delwin(help_win);
    if(status_win) delwin(status_win);
    if(buffer) free_buffer(buffer);
    if(editor.clipboard) {
        free_clipboard(editor.clipboard);
        free(editor.clipboard);
    }
    endwin();
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Draws the text buffer on the screen
 * @details Renders the visible portion of the text buffer, taking into
 * account the current top line and screen size. If the help window is
 * visible, adjusts the drawing area accordingly. Also highlights the
 * selected block using reverse video attributes.
 * @return Void
 * @author Cesar Henrique Soares Pereira
 * @version 20260609.000000
 * @date 2026-06-09
 *
 */
void draw_text(void)
{
    int start_line = buffer->top_line;
    int end_line = start_line + LINES - 2;
    int i;

    if (help_visible) {
        end_line -= 7;
    }

    for(i = start_line; i <= end_line; i++) {
        int screen_y = i - start_line + (help_visible ? 7 : 0);
        move(screen_y, 0);
        clrtoeol();

        if (i < buffer->num_lines) {
            int j;
            for(j = 0; j < buffer->line_lengths[i]; j++) {
                bool in_block = false;
                if(editor.block_active) {
                    if((i > editor.block_begin_line || (i == editor.block_begin_line && j >= editor.block_begin_col)) &&
                       (i < editor.block_end_line || (i == editor.block_end_line && j < editor.block_end_col))) {
                        in_block = true;
                    }
                }
                if(in_block) attron(A_REVERSE);
                addch(buffer->lines[i][j]);
                if(in_block) attroff(A_REVERSE);
            }
        }
    }
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prompts the user for a filename
 * @details Displays a prompt message in the status window and allows the
 * user to enter a filename. Supports character insertion, backspace
 * editing, and cancellation with the ESC key.
 * @param prompt_msg Message displayed to the user.
 * @param input_buffer Buffer that stores the user input.
 * @param max_len Maximum size of the input buffer.
 * @return Void
 * @author Cesar Henrique Soares Pereira
 * @version 20260609.000000
 * @date 2026-06-09
 *
 */
void prompt_filename(char *prompt_msg, char *input_buffer, int max_len)
{
    int ch;
    int pos = 0;
    input_buffer[0] = '\0';

    werase(status_win);
    mvwprintw(status_win, 0, 0, "%s", prompt_msg);
    wrefresh(status_win);

    while((ch = getch()) != '\n' && ch != '\r' && ch != 27) {
        if((ch == '\b' || ch == 127 || ch == CTRL('h')) && pos > 0) {
            pos--;
            input_buffer[pos] = '\0';
        } else if(ch >= 32 && ch <= 126 && pos < max_len - 1) {
            input_buffer[pos++] = ch;
            input_buffer[pos] = '\0';
        }
        werase(status_win);
        mvwprintw(status_win, 0, 0, "%s%s", prompt_msg, input_buffer);
        wrefresh(status_win);
    }

    if (ch == 27) { /* ESC cancels */
        input_buffer[0] = '\0';
    }
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prompts the user for a search string
 * @details Requests a search term from the user by reusing the filename
 * prompt functionality. The entered string can then be used by the
 * editor search routines.
 * @param prompt_msg Message displayed to the user.
 * @param input_buffer Buffer that stores the search string.
 * @param max_len Maximum size of the input buffer.
 * @return Void
 * @author Cesar Henrique Soares Pereira
 * @version 20260609.000000
 * @date 2026-06-09
 *
 */
void prompt_search(char *prompt_msg, char *input_buffer, int max_len)
{
    prompt_filename(prompt_msg, input_buffer, max_len);
}


/* ------------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline    */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20180716.101436   */
