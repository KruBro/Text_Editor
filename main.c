#include "main.h"

int main(int argc, char *argv[])
{
    // if(argc < 2)
    //     return 1;
    
    TextEditor editor;

    if(initEditor(&editor) == FAILURE)
    {
        printf("[ERROR] : Editor Initiliazation Failed\n");
        return 1;
    }

    printf("[SUCCESS] : Editor Initiliazation\n");

    addLine(&editor, "Hello World");
    insertText(&editor, " Beautiful"); 
    editor.cursorPos = 10;
    deleteCharacters(&editor, 5);           // edit 2
    printf(">> after edits: undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=2, redo=0

    undoEdit(&editor);   // undo edit 2
    printf(">> undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=1, redo=1
    undoEdit(&editor);   // undo edit 1
    printf(">> undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=0, redo=2

    undoEdit(&editor);   // nothing left — should print "Undo Stack Empty" and NOT change sizes
    printf(">> undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=0, redo=2 (unchanged)

    redoEdit(&editor);   // redo edit 1
    printf(">> undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=1, redo=1
    redoEdit(&editor);   // redo edit 2
    printf(">> undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=2, redo=0

    redoEdit(&editor);   // nothing left — should print "Redo Stack is Empty" and NOT crash
    printf(">> undo=%d redo=%d\n", editor.undoStack.size, editor.redoStack.size);   // expect undo=2, redo=0 (unchanged)

    freeEditor(&editor);
    freeStack(&editor.undoStack);
    freeStack(&editor.redoStack);
    return 0;
}