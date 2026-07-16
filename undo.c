#include "undo.h"

Status undoEdit(TextEditor *editor)
{
    Action undoAction;

    if(popStack(&editor->undoStack, &undoAction) == FAILURE)
    {
        return FAILURE;
    }

    if(jumpToLine(editor, undoAction.cursorLine) == FAILURE)
    {
        free(undoAction.text);
        undoAction.text = NULL;
        return FAILURE;
    }

    editor->cursorPos = undoAction.cursorPos;

    if(undoAction.operation == OP_INSERT)
    {
        if(deleteCharacters(editor, strlen(undoAction.text)) == FAILURE)
        {
            free(undoAction.text);
            undoAction.text = NULL;
            return FAILURE;
        }

        printf("[SUCCESS] : Undo Insert Operation Successfull\n");
    }
    else if(undoAction.operation == OP_DELETE)
    {
        if(insertText(editor, undoAction.text) == FAILURE)
        {
            free(undoAction.text);
            undoAction.text = NULL;
            return FAILURE;
        }
        printf("[SUCCESS] : Undo Delete Operation Successfull\n");
    }

    free(undoAction.text);
    undoAction.text = NULL;
    return SUCCESS;
}