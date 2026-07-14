#include "text_editor.h"
#include "cursor_navigations.h"
#include "insert.h"
#include "delete.h"
#include "file_ops.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
        return 1;
    
    TextEditor editor;

    editor.head = NULL;
    editor.tail = NULL;

    editor.cursorLine = 1;
    editor.cursorPos = 0;
    
    editor.cursor = editor.head;

    openFile(&editor, argv[1]);

    print_list(&editor);
    saveFile(&editor);
    return 0;
}