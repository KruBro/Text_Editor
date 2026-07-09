#ifndef CURSOR_NAVIGATIONS_H
#define CURSOR_NAVIGATIONS_H

#include "text_editor.h"

void moverCursorUP(TextEditor *editor);
void moveCursroDwon(TextEditor *editor);
void clampCursorPos(TextEditor *editor);

#endif