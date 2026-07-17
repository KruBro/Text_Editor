#include "undo.h"

Status undoEdit(TextEditor *editor)
{
    Action undoAction;

    if(popStack(&editor->undoStack, &undoAction) == FAILURE)
    {
        printf("[INFO] : Undo Stack Empty\n");
        return FAILURE;
    }

    printf("[DEBUG] popped text ptr = %p\n", (void*)undoAction.text);

    if(jumpToLine(editor, undoAction.cursorLine) == FAILURE)
    {
        printf("[ERROR] : Out of Bound Jump Detected\n");
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

        Action redoAction;
        if(popStack(&editor->undoStack, &redoAction) == FAILURE)
        {
            printf("[ERROR] : Undo Stack Empty\n");
            return FAILURE;
        }

        if(pushStack(&editor->redoStack, &redoAction) == FAILURE)
        {
            printf("[ERROR] : pushStack Failed\n");
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

        Action redoAction;
        if(popStack(&editor->undoStack, &redoAction) == FAILURE)
        {
            printf("[ERROR] : Undo Stack Empty\n");
            return FAILURE;
        }

        if(pushStack(&editor->redoStack, &redoAction) == FAILURE)
        {
            printf("[ERROR] : pushStack Failed\n");
        }

        printf("[SUCCESS] : Undo Delete Operation Successfull\n");
    }

    free(undoAction.text);
    undoAction.text = NULL;

    printf("[DEBUG] popped text ptr = %p\n", (void*)undoAction.text);
    return SUCCESS;
}