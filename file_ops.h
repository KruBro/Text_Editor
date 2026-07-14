#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "text_editor.h"

#define MAX_BUFFER_SIZE 1024

Status openFile(TextEditor *editor, char *file_name);
Status saveFile(TextEditor *editor);

#endif