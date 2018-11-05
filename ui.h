/*
 * Copyright (c) 2018 Tristan Le Guern <tleguern@bouledef.eu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef UI_H__
#define UI_H__

#include <time.h>

struct level;

void ui_alert(const char *);
void ui_cleanup(void);
void ui_draw(struct level *);
void ui_init(void);
void ui_menu_options(void);
void ui_menu_help(void);
void ui_message(const char *, ...);
void ui_clearmessage(void);
void ui_look(struct level *, int, int);
void ui_look_elsewhere(struct level *, int, int);
int ui_get_input(void);
int ui_get_lines(void);
int ui_get_cols(void);
void ui_pause(time_t, long);

#endif

