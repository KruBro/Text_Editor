#include "text_editor.h"
#include "cursor_navigations.h"
#include "insert.h"


int main()
{
    TextEditor editor;

    editor.head = NULL;
    editor.tail = NULL;

    editor.cursorLine = 1;
    editor.cursorPos = 0;

    addLine(&editor, "Hello World");
    addLine(&editor, "Hello World");
    addLine(&editor, "Hello World");

    editor.cursor = editor.head;

    print_list(&editor);
    editor.cursorPos = 5;
    if(insertText(&editor, " Beautiful") == FAILURE)
    {
        printf("Insert_text Failed\n");
        return 1;
    }

    print_list(&editor);
    return 0;
}