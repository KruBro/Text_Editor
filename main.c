#include "text_editor.h"


int main()
{
    TextEditor editor;

    editor.head = NULL;
    editor.tail = NULL;

    editor.cursor = editor.head;
    editor.cursorLine = 1;
    editor.cursorPos = 0;
    
    addLine(&editor, "Hello World");
    addLine(&editor, "Hello World");
    addLine(&editor, "Hello World");

    print_list(&editor);
    return 0;
}