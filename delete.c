#include "delete.h"

Status deleteCharacters(TextEditor *editor, int n)
{
    int old_len = strlen(editor->cursor->text);
    if(old_len == 0)
        return FAILURE;
    
    if(n > editor->cursorPos || n <= 0)
        return FAILURE;
    
    Action newAction;
    newAction.text = malloc(sizeof(char) * (n + 1));
    if(newAction.text == NULL)
        return FAILURE;
    
    strncpy(newAction.text ,editor->cursor->text + (editor->cursorPos - n), n);
    newAction.text[n] = '\0';
    newAction.operation = OP_DELETE;
    newAction.cursorLine = editor->cursorLine;

    char *dest = editor->cursor->text + (editor->cursorPos - n);
    char *src = editor->cursor->text + editor->cursorPos;
    int count = old_len - editor->cursorPos + 1;

    memmove(dest, src, count);
    
    editor->cursorPos = editor->cursorPos - n;
    newAction.cursorPos = editor->cursorPos;

    pushStack(&editor->undoStack, &newAction);
    return SUCCESS;
}