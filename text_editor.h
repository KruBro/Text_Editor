#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents ONE line of text — like one train car
typedef struct Node {
    char *text;         // the actual line content, e.g. "Hello World"
    struct Node *next;  // pointer to the line after this one
    struct Node *prev;  // pointer to the line before this one
} Node;

// Represents the WHOLE document — like the train itself
typedef struct {
    Node *head;    // pointer to the FIRST line node
    Node *tail;    // pointer to the LAST line node
    Node *cursor;  // pointer to whichever line the cursor is on
    int cursorLine;
    int cursorPos;
} TextEditor;

typedef enum{
    SUCCESS,
    FAILURE
} Status;

Node* create_node(const char *str);
Status append_node(TextEditor *editor, Node *new);
void print_list(TextEditor *editor);
Status addLine(TextEditor *editor, char *str);

#endif