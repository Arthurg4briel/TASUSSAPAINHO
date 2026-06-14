/*****************************************************************************
 *   libvistar.c                              Version 20180714.101818        *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libvistar.h"

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Creates a new text buffer
 * @details Allocates and initializes the text buffer structure
 * @return Pointer to the newly created TextBuffer, or NULL on error
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
TextBuffer *create_buffer(void)
{
    TextBuffer *buffer;
    buffer = malloc(sizeof(TextBuffer));
    if(buffer == NULL) return NULL;
    buffer->num_lines = 1;
    buffer->top_line = 0;
    buffer->lines = malloc(sizeof(char* ));
    buffer->line_lengths = malloc(sizeof(int));
    buffer->lines[0] = malloc(1);
    buffer->lines[0][0] = '\0';
    buffer->line_lengths[0] = 0;
    memset(buffer->markers, 0, sizeof(buffer->markers));
    return buffer;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Frees the text buffer memory
 * @details Deallocates all lines and the text buffer structure
 * @param buffer Pointer to the TextBuffer to be freed
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void free_buffer(TextBuffer *buffer)
{
    int i;
    for(i = 0; i < buffer->num_lines; i++) {
        free(buffer->lines[i]);
    }
    free(buffer->lines);
    free(buffer->line_lengths);
    free(buffer);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Inserts a character
 * @details Inserts a character at the specified line and column position
 * @param buffer Pointer to the TextBuffer
 * @param c Character to be inserted
 * @param line Target line
 * @param col Target column
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void insert_char(TextBuffer *buffer, char c, int line, int col)
{
    char *current;
    int len;

    if(line >= buffer->num_lines) return;
    current = buffer->lines[line];
    len = buffer->line_lengths[line];
    if(col > len) col = len; /* Seguranca */

    current = realloc(current, len + 2);
    if(current == NULL) return;
    buffer->lines[line] = current;

    memmove(&current[col + 1], &current[col], len - col + 1);
    current[col] = c;
    buffer->line_lengths[line]++;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Deletes a character
 * @details Removes a character from the text buffer at the specified position, with a specific direction
 * @param buffer Pointer to the TextBuffer
 * @param line Target line
 * @param col Target column
 * @param direction Deletion direction (-1 for backspace, positive for delete forward)
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void delete_char(TextBuffer *buffer, int line, int col, int direction)
{
    char *current;
    int len;

    if(line >= buffer->num_lines) return;
    current = buffer->lines[line];
    len = buffer->line_lengths[line];

    if(direction < 0) { /* backspace */
        if(col <= 0 || col > len) return;
        memmove(&current[col - 1], &current[col], len - col + 1);
    } else { /* delete forward */
        if(col < 0 || col >= len) return;
        memmove(&current[col], &current[col + 1], len - col);
    }
    buffer->line_lengths[line]--;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Inserts a line break
 * @details Breaks the current line at the specified column, creating a subsequent new line
 * @param buffer Pointer to the TextBuffer
 * @param line Line to be broken
 * @param col Column where the break will occur
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void insert_newline(TextBuffer *buffer, int line, int col)
{
     int i;
     char *current;
     char *new_line;

     if(line >= buffer->num_lines) return;
     current = buffer->lines[line];
     if(col > buffer->line_lengths[line]) col = buffer->line_lengths[line];

     new_line = strdup(&current[col]);
     current[col] = '\0';
     buffer->line_lengths[line] = col;

     buffer->num_lines++;
     buffer->lines = realloc(buffer->lines, buffer->num_lines * sizeof(char *));
     buffer->line_lengths = realloc(buffer->line_lengths, buffer->num_lines * sizeof(int));

     for(i = buffer->num_lines - 1; i > line + 1; i--) {
         buffer->lines[i] = buffer->lines[i - 1];
         buffer->line_lengths[i] = buffer->line_lengths[i - 1];
}
     buffer->lines[line + 1] = new_line;
     buffer->line_lengths[line + 1] = strlen(new_line);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Deletes a line
 * @details Completely removes the specified line, adjusting the buffer
 * @param buffer Pointer to the TextBuffer
 * @param line Number of the line to be removed
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void delete_line(TextBuffer *buffer, int line)
{
     int i;
     if(line >= buffer->num_lines || buffer->num_lines <= 1) return;
     free(buffer->lines[line]);
     for(i = line; i < buffer->num_lines - 1; i++) {
         buffer->lines[i] = buffer->lines[i + 1];
         buffer->line_lengths[i] = buffer->line_lengths[i + 1];
}
     buffer->num_lines--;
     buffer->lines = realloc(buffer->lines, buffer->num_lines * sizeof(char *));
     buffer->line_lengths = realloc(buffer->line_lengths, buffer->num_lines * sizeof(int));
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Deletes a word
 * @details Deletes the word from the current cursor position to the next whitespace
 * @param buffer Pointer to the TextBuffer
 * @param line Target line
 * @param col Target column
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void delete_word(TextBuffer *buffer, int line, int col)
{
     char *current;
     int len;
     int end_col;
     if(line >= buffer->num_lines) return;
     current = buffer->lines[line];
     len = buffer->line_lengths[line];
     if(col >= len) return;
     end_col = col;
     while(end_col < len && current[end_col] != ' ' && current[end_col] != '\t') {
           end_col++;
}
     while(end_col < len && (current[end_col] == ' ' || current[end_col] == '\t')) {
           end_col++;
}
     memmove(&current[col], &current[end_col], len - end_col + 1);
     buffer->line_lengths[line] -= (end_col - col);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Joins adjacent lines
 * @details Appends the content of the next line to the end of the current line and removes the next line
 * @param buffer Pointer to the TextBuffer
 * @param line Current line number
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void join_lines(TextBuffer *buffer, int line)
{
     char *current;
     char *next;
     int len1, len2;
     if(line >= buffer->num_lines - 1) return;
     current = buffer->lines[line];
     next = buffer->lines[line + 1];
     len1 = buffer->line_lengths[line];
     len2 = buffer->line_lengths[line + 1];
     current = realloc(current, len1 + len2 + 1);
     if(!current) return;
     strcpy(&current[len1], next);
     buffer->lines[line] = current;
     buffer->line_lengths[line] = len1 + len2;
     delete_line(buffer, line + 1);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Sets a position marker
 * @details Associates a marker index with line and column coordinates in the buffer
 * @param buffer Pointer to the TextBuffer
 * @param marker Marker index (0-9)
 * @param line Marker line
 * @param col Marker column
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void set_marker(TextBuffer *buffer, int marker, int line, int col)
{
    if(marker < 0 || marker > 9) return;
    buffer->markers[marker].line = line;
    buffer->markers[marker].col = col;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Goes to a position marker
 * @details Retrieves the line and column coordinates associated with a marker index
 * @param buffer Pointer to the TextBuffer
 * @param marker Marker index (0-9)
 * @param line Pointer to the variable that will receive the line
 * @param col Pointer to the variable that will receive the column
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void goto_marker(TextBuffer *buffer, int marker, int *line, int *col)
{
    if(marker < 0 || marker > 9) return;
    *line = buffer->markers[marker].line;
    *col = buffer->markers[marker].col;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Saves the file to disk
 * @details Writes the text buffer content to the file with the provided name
 * @param buffer Pointer to the TextBuffer
 * @param filename File name
 * @return 1 if saved successfully, 0 on error
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
int save_file(TextBuffer *buffer, const char *filename)
{
   FILE *fp;
   int i;
   fp = fopen(filename, "w");
   if(fp == NULL) return 0;
   for(i = 0; i < buffer->num_lines; i++) {
     fprintf(fp, "%s\n", buffer->lines[i]);
   }
   fclose(fp);
   return 1;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Loads a file from disk
 * @details Reads the file content and fills the text buffer
 * @param buffer Pointer to the TextBuffer
 * @param filename File name
 * @return 1 if read successfully, 0 on error
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
int load_file(TextBuffer *buffer, const char *filename)
{
   FILE *fp;
   char buf[2048];
   fp = fopen(filename, "r");
   if(fp == NULL) return 0;

   new_file(buffer); /* Limpa o buffer primeiro */

   if (fgets(buf, sizeof(buf), fp) != NULL) {
       buf[strcspn(buf, "\r\n")] = '\0';
       buffer->lines[0] = realloc(buffer->lines[0], strlen(buf) + 1);
       strcpy(buffer->lines[0], buf);
       buffer->line_lengths[0] = strlen(buf);
       while(fgets(buf, sizeof(buf), fp) != NULL) {
           buf[strcspn(buf, "\r\n")] = '\0';
           insert_newline(buffer, buffer->num_lines - 1, buffer->line_lengths[buffer->num_lines - 1]);
           buffer->lines[buffer->num_lines - 1] = realloc(buffer->lines[buffer->num_lines - 1], strlen(buf) + 1);
           strcpy(buffer->lines[buffer->num_lines - 1], buf);
           buffer->line_lengths[buffer->num_lines - 1] = strlen(buf);
       }
   }
   fclose(fp);
   return 1;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Clears the current buffer (New file)
 * @details Resets the text buffer by clearing the information and preparing it empty
 * @param buffer Pointer to the TextBuffer
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void new_file(TextBuffer *buffer)
{
    int i;
    for(i = 0; i < buffer->num_lines; i++) {
        free(buffer->lines[i]);
    }
    buffer->num_lines = 1;
    buffer->top_line = 0;
    buffer->lines = realloc(buffer->lines, sizeof(char *));
    buffer->line_lengths = realloc(buffer->line_lengths, sizeof(int));
    buffer->lines[0] = malloc(1);
    buffer->lines[0][0] = '\0';
    buffer->line_lengths[0] = 0;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Copies a text block
 * @details Extracts a portion of the buffer and stores it in the clipboard
 * @param buffer Pointer to the TextBuffer
 * @param clip Destination clipboard
 * @param start_line Start line
 * @param start_col Start column
 * @param end_line End line
 * @param end_col End column
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void copy_block(TextBuffer *buffer, Clipboard *clip, int start_line, int start_col, int end_line, int end_col)
{
    int i;

    /* Sanitizacao e limites */
    if(start_line >= buffer->num_lines) start_line = buffer->num_lines - 1;
    if(end_line >= buffer->num_lines) end_line = buffer->num_lines - 1;
    if(start_line < 0) start_line = 0;
    if(end_line < 0) end_line = 0;
    if(start_col > buffer->line_lengths[start_line]) start_col = buffer->line_lengths[start_line];
    if(end_col > buffer->line_lengths[end_line]) end_col = buffer->line_lengths[end_line];
    if(start_col < 0) start_col = 0;
    if(end_col < 0) end_col = 0;

    /* Inverte se marcou de tras pra frente */
    if(start_line > end_line || (start_line == end_line && start_col > end_col)) {
    int tl = start_line; start_line = end_line; end_line = tl;
    int tc = start_col; start_col = end_col; end_col = tc;
    }

    free_clipboard(clip);
    if(start_line == end_line && start_col == end_col) return;

    clip->num_lines = end_line - start_line + 1;
    clip->lines = malloc(clip->num_lines * sizeof(char *));
    clip->line_lengths = malloc(clip->num_lines * sizeof(int));

    if(clip->num_lines == 1) {
        int len = end_col - start_col;
        clip->lines[0] = malloc(len + 1);
        strncpy(clip->lines[0], &buffer->lines[start_line][start_col], len);
        clip->lines[0][len] = '\0';
        clip->line_lengths[0] = len;
    } else {
        int len_first = buffer->line_lengths[start_line] - start_col;
        clip->lines[0] = malloc(len_first + 1);
        strcpy(clip->lines[0], &buffer->lines[start_line][start_col]);
        clip->line_lengths[0] = len_first;

        for(i = 1; i < clip->num_lines - 1; i++) {
            clip->lines[i] = strdup(buffer->lines[start_line + i]);
            clip->line_lengths[i] = buffer->line_lengths[start_line + i];
        }

        int len_last = end_col;
        clip->lines[clip->num_lines - 1] = malloc(len_last + 1);
        strncpy(clip->lines[clip->num_lines - 1], buffer->lines[end_line], len_last);
        clip->lines[clip->num_lines - 1][len_last] = '\0';
        clip->line_lengths[clip->num_lines - 1] = len_last;
   }
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Cuts a text block
 * @details Copies the portion to the clipboard and then removes it from the source buffer
 * @param buffer Pointer to the TextBuffer
 * @param clip Destination clipboard
 * @param start_line Start line
 * @param start_col Start column
 * @param end_line End line
 * @param end_col End column
 * @param cursor_y Current cursor Y position to be adjusted
 * @param cursor_x Current cursor X position to be adjusted
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void cut_block(TextBuffer *buffer, Clipboard *clip, int start_line, int start_col, int end_line, int end_col, int *cursor_y, int *cursor_x)
{
    /* Sanitizacao e limites (mesmo do copy) */
    if(start_line >= buffer->num_lines) start_line = buffer->num_lines - 1;
    if(end_line >= buffer->num_lines) end_line = buffer->num_lines - 1;
    if(start_line < 0) start_line = 0;
    if(end_line < 0) end_line = 0;
    if(start_col > buffer->line_lengths[start_line]) start_col = buffer->line_lengths[start_line];
    if(end_col > buffer->line_lengths[end_line]) end_col = buffer->line_lengths[end_line];
    if(start_col < 0) start_col = 0;
    if(end_col < 0) end_col = 0;

    if(start_line > end_line || (start_line == end_line && start_col > end_col)) {
        int tl = start_line; start_line = end_line; end_line = tl;
        int tc = start_col; start_col = end_col; end_col = tc;
    }

    if(start_line == end_line && start_col == end_col) {
        free_clipboard(clip);
        return;
    }

    copy_block(buffer, clip, start_line, start_col, end_line, end_col);
    if(clip->num_lines == 0) return;

    if(start_line == end_line) {
        int len = end_col - start_col;
        char *current = buffer->lines[start_line];
        memmove(&current[start_col], &current[end_col], buffer->line_lengths[start_line] - end_col + 1);
        buffer->line_lengths[start_line] -= len;
    } else {
        char *last_rem;
        int last_len;
        int i;

        buffer->lines[start_line][start_col] = '\0';
        buffer->line_lengths[start_line] = start_col;

        last_rem = strdup(&buffer->lines[end_line][end_col]);
        last_len = buffer->line_lengths[end_line] - end_col;

        for(i = start_line + 1; i <= end_line; i++) {
            delete_line(buffer, start_line + 1);
        }

        buffer->lines[start_line] = realloc(buffer->lines[start_line], start_col + last_len + 1);
        strcpy(&buffer->lines[start_line][start_col], last_rem);
        buffer->line_lengths[start_line] += last_len;
        free(last_rem);
    }
    *cursor_y = start_line;
    *cursor_x = start_col;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Pastes a text block
 * @details Inserts the content stored in the clipboard at the cursor position
 * @param buffer Pointer to the TextBuffer
 * @param clip Source clipboard
 * @param cursor_y Y position (line) where pasting will occur and will be adjusted
 * @param cursor_x X position (column) where pasting will occur and will be adjusted
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void paste_block(TextBuffer *buffer, Clipboard *clip, int *cursor_y, int *cursor_x)
{
    int line = *cursor_y;
    int col = *cursor_x;
    int i;

    if(!clip || clip->num_lines == 0) return;

    if(clip->num_lines == 1) {
        int len = clip->line_lengths[0];
        char *current = buffer->lines[line];
        current = realloc(current, buffer->line_lengths[line] + len + 1);
        memmove(&current[col + len], &current[col], buffer->line_lengths[line] - col + 1);
        memcpy(&current[col], clip->lines[0], len);
        buffer->lines[line] = current;
        buffer->line_lengths[line] += len;
        *cursor_x += len;
    } else {
        char *rem = strdup(&buffer->lines[line][col]);
        int last_line;
        int rem_len;

        buffer->lines[line][col] = '\0';
        buffer->lines[line] = realloc(buffer->lines[line], col + clip->line_lengths[0] + 1);
        strcpy(&buffer->lines[line][col], clip->lines[0]);
        buffer->line_lengths[line] = col + clip->line_lengths[0];

        for(i = 1; i < clip->num_lines; i++) {
            insert_newline(buffer, line + i - 1, buffer->line_lengths[line + i - 1]);
            buffer->lines[line + i] = realloc(buffer->lines[line + i], clip->line_lengths[i] + 1);
            strcpy(buffer->lines[line + i], clip->lines[i]);
            buffer->line_lengths[line + i] = clip->line_lengths[i];
        }

        last_line = line + clip->num_lines - 1;
        rem_len = strlen(rem);
        buffer->lines[last_line] = realloc(buffer->lines[last_line], buffer->line_lengths[last_line] + rem_len + 1);
        strcpy(&buffer->lines[last_line][buffer->line_lengths[last_line]], rem);
        buffer->line_lengths[last_line] += rem_len;

        *cursor_y = last_line;
        *cursor_x = clip->line_lengths[clip->num_lines - 1];
        free(rem);
    }
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Frees the clipboard memory
 * @details Deallocates the clipboard content
 * @param clip Pointer to the Clipboard to be freed
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
void free_clipboard(Clipboard *clip)
{
    int i;
    if(!clip) return;
    for(i = 0; i < clip->num_lines; i++) {
        free(clip->lines[i]);
    }
    if(clip->num_lines > 0) {
        free(clip->lines);
        free(clip->line_lengths);
    }
    clip->num_lines = 0;
    clip->lines = NULL;
    clip->line_lengths = NULL;
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Performs a text search
 * @details Searches for the first occurrence of the given term, starting from the search position in the buffer
 * @param buffer Pointer to the TextBuffer
 * @param term String to be searched
 * @param line Reference to the line from which to start the search and which will receive the value upon success
 * @param col Reference to the column from which to start the search and which will receive the value upon success
 * @return 1 if found, 0 otherwise
 * @author Equipe Blossom
 * @date 2026-06-14
 *
 */
int search_text(TextBuffer *buffer, const char *term, int *line, int *col)
{
    int i;
    char *found;
    if(!buffer || !term || !line || !col || term[0] == '\0') return 0;
    /* Busca a partir da posicao atual ate o fim do buffer */
    for(i = *line; i < buffer->num_lines; i++) {
        int start_col = (i == *line) ? *col : 0;
        found = strstr(buffer->lines[i] + start_col, term);
        if(found) {
            *line = i;
            *col = (int)(found - buffer->lines[i]);
            return 1;
        }
    }
    /* Busca circular: do inicio ate a linha original */
    for(i = 0; i < *line; i++) {
        found = strstr(buffer->lines[i], term);
        if(found) {
            *line = i;
            *col = (int)(found - buffer->lines[i]);
            return 1;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline    */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20180716.101436   */

