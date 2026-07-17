#include "main.h"

Status redoEdit(TextEditor *editor)
{
    Action redoAction;
    if(popStack(&editor->redoStack, &redoAction) == FAILURE)
    {
        printf("[INFO] : Redo Stack is Empty\n");
        return FAILURE;
    }

    // in redoEdit, immediately after popStack succeeds:
    printf("[DEBUG] popped text ptr = %p\n", (void*)redoAction.text);
    if(jumpToLine(editor, redoAction.cursorLine) == FAILURE)
    {
        printf("[ERROR] : Out of Bound Jump Detected\n");
        free(redoAction.text);
        redoAction.text = NULL;
        return FAILURE;
    }

    editor->cursorPos = redoAction.cursorPos;

    if(redoAction.operation == OP_INSERT)
    {
        if(deleteCharacters(editor, strlen(redoAction.text)) == FAILURE)
        {
            printf("[ERROR] : DeleteOperation Failed\n");
            free(redoAction.text);
            redoAction.text = NULL;
            return FAILURE;
        }

        printf("[SUCCESS] : Redo Insert\n");
    }
    else
    {
        if(insertText(editor, redoAction.text) == FAILURE)
        {
            printf("[ERROR] : Delete Operation Failed\n");
            free(redoAction.text);
            redoAction.text = NULL;
            return FAILURE;
        }

        printf("[SUCCESS] : Redo Delete\n");
    }

    free(redoAction.text);
    redoAction.text = NULL;

    return SUCCESS;
}