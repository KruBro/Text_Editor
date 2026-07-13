#include "text_editor.h"
#include "cursor_navigations.h"


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

    printf("CursorPos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);
    cursorMoveLeft(&editor);
    printf("CursorPos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);
    editor.cursorPos = 11;
    printf("CursorPos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);
    cursorMoveRight(&editor);
    printf("CursorPos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);
    cursorMoveLeft(&editor);
    printf("CursorPos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);

    return 0;
}