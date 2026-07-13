#include "delete.h"

Status deleteCharacters(TextEditor *editor, int n)
{
    int old_len = strlen(editor->cursor->text);
    if(old_len == 0)
        return FAILURE;
    
    if(n > editor->cursorPos || n <= 0)
        return FAILURE;
    
    
    char *dest = editor->cursor->text + (editor->cursorPos - n);
    char *src = editor->cursor->text + editor->cursorPos;
    int count = old_len - editor->cursorPos + 1;

    memmove(dest, src, count);
    
    editor->cursorPos = editor->cursorPos - n;
    return SUCCESS;
}