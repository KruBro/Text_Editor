#include "text_editor.h"
#include "cursor_navigations.h"
#include "insert.h"
#include "delete.h"

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
    printf("Cursor Pos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);

    if(deleteCharacters(&editor, 5) == FAILURE)
    {
        printf("Delete Failed\n");
    }
    printf("Cursor Pos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);

    if(deleteCharacters(&editor, 0) == FAILURE)
    {
        printf("Delete Failed\n");
    }
    printf("Cursor Pos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);

    if(deleteCharacters(&editor, 999) == FAILURE)
    {
        printf("Delete Failed\n");
    }
    printf("Cursor Pos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);

    if(deleteCharacters(&editor, -3) == FAILURE)
    {
        printf("Delete Failed\n");
    }
    printf("Cursor Pos -> %d, CursorLine -> %d\n", editor.cursorPos, editor.cursorLine);

    print_list(&editor);
    return 0;
}