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
    addLine(&editor, "Hello Worlddddd");
    addLine(&editor, "Hello Worldsss");

    print_list(&editor);

    insertText(&editor, " Beautiful");
    print_list(&editor);
    undoEdit(&editor);
    print_list(&editor);
    editor.cursorPos = 10;
    deleteCharacters(&editor, 5);
    print_list(&editor);
    undoEdit(&editor);
    print_list(&editor);
    freeEditor(&editor);
    freeStack(&editor.undoStack);
    return 0;
}