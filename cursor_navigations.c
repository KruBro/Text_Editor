#include "cursor_navigations.h"

void clampCursorPos(TextEditor *editor)
{
    int len_of_new_line = strlen(editor->cursor->text);
    if(editor->cursorPos > len_of_new_line)
    {
        editor->cursorPos = len_of_new_line;
    }
}

void cursorMoveUp(TextEditor *editor)
{
    if(editor->cursor->prev != NULL)
    {
        editor->cursor = editor->cursor->prev;
        editor->cursorLine--;
        clampCursorPos(editor);
    }
}

void cursorMoveDown(TextEditor *editor)
{
    if(editor->cursor->next != NULL)
    {
        editor->cursor = editor->cursor->next;
        editor->cursorLine++;
        clampCursorPos(editor);
    }
}