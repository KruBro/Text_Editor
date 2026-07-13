#ifndef CURSOR_NAVIGATIONS_H
#define CURSOR_NAVIGATIONS_H

#include "text_editor.h"

void cursorMoveUp(TextEditor *editor);
void cursorMoveDown(TextEditor *editor);
void clampCursorPos(TextEditor *editor);
void cursorMoveRight(TextEditor *editor);
void cursorMoveLeft(TextEditor *editor);

#endif