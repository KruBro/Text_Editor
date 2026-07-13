#include "insert.h"

Status insertText(TextEditor *editor, const char *str_input)
{
    int old_len = strlen(editor->cursor->text);
    int insert_len = strlen(str_input);
    int new_len = old_len + insert_len;

    char *temp_buff = realloc(editor->cursor->text, (new_len + 1) * sizeof(char));
    if(temp_buff == NULL)
        return FAILURE;
    
    editor->cursor->text = temp_buff;

    //strlen will gives you the old_len with null character is not counted,
    //So we need to consider it when we are moving the memory
    memmove((editor->cursor->text + editor->cursorPos + insert_len), 
        (editor->cursor->text + editor->cursorPos), 
        (old_len - editor->cursorPos + 1));
    
    //Copy the new string to the cursor text
    strncpy((editor->cursor->text + editor->cursorPos), str_input, insert_len);

    editor->cursorPos  = editor->cursorPos + insert_len;
    return SUCCESS;
}